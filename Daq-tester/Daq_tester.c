#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include <rs232.h>
#include "Daq_tester.h"

/*=============================================================================================*/

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

// Data structure to store the range of values for the analog channels
typedef struct
{
	double l; // lower bound
	double u; // upper bound
} range;


range make_range(double lower, double upper)
{
	range R;
	R.l = lower;
	R.u = upper;
	return R;
};

/*=============================================================================================*/

static int panelHandle;

int my_com = 3;
int Err;
char SendBuff[3], RecvBuff[3];

range analog0_range, analog1_range;	// assigned values in main

/*=============================================================================================*/

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Daq_tester.uir", PANEL)) < 0)
		return -1;

	// Set analog ranges
	analog0 = make_range(-10.0, 10.0);	// channel 0
	analog1 = make_range(-10.0, 10.0);	// channel 1

	DisplayPanel (panelHandle);
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
int CVICALLBACK connect_COM (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			OpenComConfig (my_com, "", 115200, 0, 8, 1, 512, 512);
			InstallComCallback (my_com, LWRS_RXFLAG, 0, 0, 0, 0);
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 1);
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

int CVICALLBACK send_commands (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			
			break;
	}
	return 0;
}



// Should i go with a partial\full polling scheme?
// The commands for sending data to the DAQ are handled as GUI callback and as such don't need to be a part
// of the COM polling/callback.
// Since the DAQ doesn't send any data unless prompted, to update the tester values in a reasonable
// amount of time, the only real way would be with a polling scheme.
switch(SendBuff[0])
{
	case digital_out:
		
		break;
		
	
	case digital_in:
		
		break;
		
	
	case analog_out_ch0:
		
		break;
		
	
	case analog_out_ch1:
		
		break;
		
	
	case analog_in_ch0:
		
		break;
		
	
	case analog_in_ch1:
		
		break;
}