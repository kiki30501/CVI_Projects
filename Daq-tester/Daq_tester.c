#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include <rs232.h>
#include <math.h>
#include <utility.h>
#include "Daq_tester.h"

/*=============================================================================================*/

// Necessary Defines:
#define num_bits 	12
#define vmax 		10.0
#define vmin 		-10.0

// Peripheral Addresses:
#define digital_out 	0x01 // Tester buttons -> DAQ LEDs
#define digital_in  	0x02 // DAQ buttons -> Tester LEDs
#define analog_out_ch0  0x03 // Tester knob ch0 -> DAQ display ch0
#define analog_out_ch1  0x04 // Tester knob ch1 -> DAQ display ch1
#define analog_in_ch0   0x05 // DAQ knob ch0 -> Tester display ch0
#define analog_in_ch1   0x06 // DAQ knob ch1 -> Tester display ch1

// These are all commands that are sent from the Tester to the DAQ
// The commands that return values from the DAQ are needed because
// the DAQ doesn't send any data unless it gets a command from the
// tester to do so.

/*=============================================================================================*/

static int panelHandle, button_arr_handle, LED_arr_handle;

int my_com = 3;
int Err;
char SendBuff[3], RecvBuff[2];
double ratio;

/*=============================================================================================*/

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Daq_tester.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	
	ratio = pow(2, num_bits) / (vmax - vmin);
	button_arr_handle = GetCtrlArrayFromResourceID (panelHandle, Digital_button_array);
	LED_arr_handle = GetCtrlArrayFromResourceID (panelHandle, Led_array);
	
	RunUserInterface ();
	DiscardPanel (panelHandle);
	
	CloseCom(my_com);
	
	return 0;
}

/*=============================================================================================*/

int CVICALLBACK QuitCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface (0);
			break;
	}
	return 0;
}

/*=============================================================================================*/

// Just a simple function to connect to the COM port to the tester.
int CVICALLBACK Connect_COM (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			OpenComConfig (my_com, "", 115200, 0, 8, 1, 512, 512);
			InstallComCallback (my_com, LWRS_RXFLAG, 0, 0, 0, 0);
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 1);
			
			SetCtrlAttribute (panelHandle, PANEL_TesterCOM, ATTR_TEXT_BGCOLOR, VAL_GREEN);
			SetCtrlArrayAttribute (button_arr_handle, ATTR_DIMMED, 0);
			SetCtrlAttribute (panelHandle, PANEL_ANALOG_OUT_0, ATTR_DIMMED, 0);
			SetCtrlAttribute (panelHandle, PANEL_ANALOG_OUT_1, ATTR_DIMMED, 0);
			break;
	}
	return 0;
}

/*=============================================================================================*/

short format_12to16(short data)
{
	// Converts 12-bit data to 16-bit data but WITH sign extension for 16bit
	// This is used as a function to prepare the data to be sent to the DUT

	data <<= 4;
	data >>= 4;
	return data;
}

/*=============================================================================================*/

short tester_ADC(double sample)
{
	// This function has 2 roles: 
	// 	1. convert the analog reading to a 12 bit value (like an ADC).
	// 	2. pretend that it's actually 12 bit (and not 16) by deleting setting the last 4 bits to 0.
	
	short data = (short)(sample * ratio);
	data &= 0x0FFF;
	return data;
}

/*=============================================================================================*/

char button_values_to_char()
{
	// Take a control array handle and convert the 8 int values
	// to the bits of a char variable.
	
	char c = 0;
	int x;
	for(int i=0; i<8; i++)
	{
		GetCtrlVal(panelHandle, GetCtrlArrayItem(button_arr_handle, i), &x);
		c += x<<i;
	}
	return c;
}

/*=============================================================================================*/

int CVICALLBACK cmnd_digital_out (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{ // Send to DAQ the values of the buttons to the DAQ LEDs
	char data;
	switch (event)
	{
		case EVENT_COMMIT:
			
			data = button_values_to_char(button_arr_handle);
			SendBuff[0] = digital_out;
			SendBuff[1] = data;
			for(int i=0; i<2; i++)
				ComWrtByte (my_com, SendBuff[i]);
			Delay(0.1);
			memset(SendBuff, 0, sizeof SendBuff);
			break;
	}
	return 0;
}

/*=============================================================================================*/

int CVICALLBACK cmnd_analog_out (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{ // Send either analog channel's knob value to DAQ display
	double x;
	short val;
	switch (event)
	{
		case EVENT_COMMIT:
			
			GetCtrlVal (panelHandle, control, &x);
			val = tester_ADC(x);
			val = format_12to16(val);
			SendBuff[0] = (control == PANEL_ANALOG_OUT_0) ? (analog_out_ch0) : (analog_out_ch1);
			SendBuff[1] = (char)(0xFF & val);
			SendBuff[2] = (char)(0xFF & (val>>8));
			for(int i=0; i<3; i++)
				ComWrtByte (my_com, SendBuff[i]);
			Delay(0.1);
			memset(SendBuff, 0, sizeof SendBuff);
			break;
	}
	return 0;
}

/*=============================================================================================*/

void my_refresh()
{
	// This function sends the requests to the DAQ for return values.
	// The returned values are read and applied by my_callback().
	
	char data_digital;
	int data_analog;
	double display_data;
	int LED_name;
	
	// Digital:
	ComWrtByte(my_com, digital_in);
	Delay(0.01);
	RecvBuff[0] = (char)(ComRdByte(my_com));
	for(int i=0; i<8; i++) // Set the LEDs of the tester
	{
		LED_name = GetCtrlArrayItem (LED_arr_handle, i);
		data_digital = 0x1 & (RecvBuff[0]>>i);
		SetCtrlVal (panelHandle, LED_name, data_digital);
	}
	memset(RecvBuff, 0, sizeof RecvBuff);
	
	// Analog channel 0:
	ComWrtByte(my_com, analog_in_ch0);
	Delay(0.01);
	ComRd (my_com, RecvBuff, 2); // Analog channel 0 data
	data_analog = (RecvBuff[1]<<8) + (RecvBuff[0] & 0xFF);
	display_data = (double)(data_analog/ratio);
	SetCtrlVal (panelHandle, PANEL_ANALOG_IN_0, display_data);
	memset(RecvBuff, 0, sizeof RecvBuff);
	
	// Analog channel 1:
	ComWrtByte(my_com, analog_in_ch1);
	Delay(0.01);
	ComRd (my_com, RecvBuff, 2); // Analog channel 1 data
	data_analog = (RecvBuff[1]<<8) + (RecvBuff[0] & 0xFF);
	display_data = (double)(data_analog/ratio);
	SetCtrlVal (panelHandle, PANEL_ANALOG_IN_1, display_data);
	memset(RecvBuff, 0, sizeof RecvBuff);
	
}


/*=============================================================================================*/

int CVICALLBACK refresh_timer (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
			my_refresh();
			break;
	}
	return 0;
}

/*=============================================================================================*/