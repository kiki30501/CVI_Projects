#include <cvirte.h>		
#include <userint.h>
#include "Question3.h"

static int panelHandle;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Question3.uir", PANEL)) < 0)
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

int CVICALLBACK MyArithButtons (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		double arg1, arg2, result;
		case EVENT_COMMIT:
			
			// Read both values from box1 and box2
			GetCtrlVal (panelHandle, PANEL_Input_box1, &arg1);
			GetCtrlVal (panelHandle, PANEL_Input_box2, &arg2);
			
			// Test what button we pressed and preform the math operation
			switch (control)
			{
				case PANEL_Bplus:
					result = arg1 + arg2;
					break;
					
				case PANEL_Bminus:
					result = arg1 - arg2;
					break;
					
				case PANEL_Btimes:
					result = arg1 * arg2;
					break;
					
				case PANEL_Bdivide:
					result = arg1 / arg2;
					break;
					
				default: 
					result = 1199;
					break;
			}
			
			// Assign the resulting value to the result box
			SetCtrlVal (panelHandle, PANEL_Result_box, result);

			break;
	}
	return 0;
}
