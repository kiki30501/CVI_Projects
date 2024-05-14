#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "Question2.h"

static int panelHandle;
char s[50];

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Question2.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK MyQuit (int panel, int control, int event,
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

int CVICALLBACK MyCopy (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_STRING_IN,  s);
			SetCtrlVal (panelHandle, PANEL_STRING_OUT, s);
			break;
	}
	return 0;
}

int CVICALLBACK MyUp (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_STRING_OUT, s);
			int i;
			for(i = 0 ; (s[i] = toupper(s[i])) ; i++);
			SetCtrlVal (panelHandle, PANEL_STRING_OUT, s);
			break;
	}
	return 0;
}

int CVICALLBACK MyLow (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_STRING_OUT, s);
			int i;
			for(i = 0 ; (s[i] = tolower(s[i])) ; i++);
			SetCtrlVal (panelHandle, PANEL_STRING_OUT, s);
			break;
	}
	return 0;
}
