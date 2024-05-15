#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "Question1.h"

static int panelHandle, arrayHandle;
double v1, v2, i, dt, Q, c1, c2, r;
double  *values[] = {&v1, &v2, &dt, &c1, &c2, &r};


int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel(0, "Question1.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	arrayHandle = GetCtrlArrayFromResourceID (panelHandle, CTRLARRAY);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

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

int CVICALLBACK RunCalculation (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	char s[12];
	switch (event)
	{
		case EVENT_TIMER_TICK:
			GetCtrlVal(panelHandle, PANEL_V1, &v1);
			GetCtrlVal(panelHandle, PANEL_V2, &v2);
			i = (v1 - v2) / r;
			sprintf(s, "%.3e", i);
			SetCtrlVal (panelHandle, PANEL_STRING, s);
			Q = i * dt;
			v1 -= Q / c1;
			v2 += Q / c2;
			SetCtrlVal(panelHandle, PANEL_V1, v1);
			SetCtrlVal(panelHandle, PANEL_V2, v2);
			break;
	}
	return 0;
}


int CVICALLBACK StartSim (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	int x;
	int manual;
	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panelHandle, PANEL_GOB, ATTR_CMD_BUTTON_COLOR, VAL_RED);
			GetNumCtrlArrayItems (arrayHandle, &x);
			for(x-- ; x >= 0 ; x--)
				GetCtrlVal (panelHandle, GetCtrlArrayItem (arrayHandle, x), values[x]);				
			GetCtrlVal (panelHandle, PANEL_MANUAL_DT, &manual);
			// if manual mode then use the value as it was written, else calculate a fitting value
			dt = manual ? dt : (((c1<c2) ? c1 : c2) * r / 100.0);
			SetCtrlAttribute (panelHandle, PANEL_RUN_TIMER, ATTR_INTERVAL, dt);
			SetCtrlVal (panelHandle, PANEL_DT, dt);
			SetCtrlAttribute (panelHandle, PANEL_RUN_TIMER, ATTR_ENABLED, 1); // Start the timer
			break;
	}
	return 0;
}


int CVICALLBACK ResetSim (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panelHandle, PANEL_RUN_TIMER, ATTR_ENABLED, 0); // Stop the timer
			SetCtrlAttribute (panelHandle, PANEL_GOB, ATTR_CMD_BUTTON_COLOR, VAL_GREEN);
			DefaultCtrl (panelHandle, PANEL_V1);
			DefaultCtrl (panelHandle, PANEL_V2);
			DefaultCtrl (panelHandle, PANEL_STRING);
			break;
	}
	return 0;
}
