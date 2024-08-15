#include <cvirte.h>		
#include <userint.h>
#include "Main.h"
#include "MyDll.h"
static int panelHandle;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Main.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
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
		case EVENT_LEFT_DOUBLE_CLICK:

			break;
		}
	return 0;
}

int CVICALLBACK MainPrint (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (panel, PANEL_NUMERIC, &PrintLen);
			DllPrint();
			break;
		case EVENT_LEFT_DOUBLE_CLICK:

			break;
		}
	return 0;
}
