#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include <rs232.h>
#include "Daq_tester.h"

/*=============================================================================================*/

// Peripheral Addresses:
#define digital_out 	0x1 // Leds
#define digital_in  	0x2 // Buttons
#define analog_out_ch0  0x3 // Numeric Channel 0
#define analog_in_ch0   0x4 // Knobs   Channel 0
#define analog_out_ch1  0x5 // Numeric Channel 1
#define analog_in_ch1   0x6 // Knobs   Channel 1

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
char SendBuff[3], RecvBuff[3], address;

range analog0, analog1;	// assigned values in main

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

// This function is resposible to receive data from the DUT (emulator)
// using a callback (instead of polling).
// The function is used when getting data from the DUT after commanding it to return data.
void CVICALLBACK tester_callback (int portNumber, int eventMask, void *callbackData)
{
	
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
			InstallComCallback (my_com, LWRS_RXFLAG, 0, 0, tester_callback, 0);

			break;
	}
	return 0;
}

/*=============================================================================================*/

short format_short(short data)
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




// For the COM of tester (outgoing to the DUT)
switch(address)
{
	case digital_out:
		
		break;
		
	
	case digital_in:
		
		break;
		
	
	case analog_out_ch0:
		
		break;
		
	
	case analog_in_ch0:
		
		break;
		
	
	case analog_out_ch1:
		
		break;
		
	
	case analog_in_ch1:
		
		break;
}