#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include <rs232.h>
#include "Daq_tester.h"

/*=============================================================================================*/

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

int my_com = 2;
int Err;

range analog0, analog1;
analog0 = make_range(-10.0, 10.0);
analog1 = make_range(-10.0, 10.0);


/*=============================================================================================*/

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Daq_tester.uir", PANEL)) < 0)
		return -1;
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
// using a callback (instead of polling)
void CVICALLBACK MyCallback (int portNumber, int eventMask, void *callbackData)
{
	
}

/*=============================================================================================*/

int CVICALLBACK Connect_COM (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			OpenComConfig (my_com, "", 115200, 0, 8, 1, 512, 512);
			

			break;
	}
	return 0;
}

/*=============================================================================================*/

int CVICALLBACK Digital_Leds (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

/*=============================================================================================*/

int CVICALLBACK Digital_Buttons (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

/*=============================================================================================*/

int CVICALLBACK Analog_Numerics (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

/*=============================================================================================*/

int CVICALLBACK Analog_Knobs (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

/*=============================================================================================*/
