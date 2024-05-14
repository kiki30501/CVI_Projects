#include <cvirte.h>		
#include <userint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Question4.h"

static int panelHandle;
char button_label[2];
char DisplayValue[50] = "\0";

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Question4.uir", PANEL)) < 0)
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

int CVICALLBACK MyActionButtons (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	
	static int temp = PANEL_bplus;
	static double result = 0;
	
	switch (event)
	{
		case EVENT_COMMIT:
			if(control == PANEL_bclr)
			{	// Clear all the variables and display
				temp = PANEL_bplus;
				strcpy(button_label, "");
				result = 0;
				SetCtrlVal(panelHandle, PANEL_CalcDisplay, "");
			}
			else
			{
				GetCtrlVal(panelHandle, PANEL_CalcDisplay, DisplayValue);
				if(DisplayValue[0] != '\0') // Checks if the Display is empty
				{
					SetCtrlVal(panelHandle, PANEL_CalcDisplay, ""); // Clear Display
					switch (temp) // Perform the math operation of choice
					{
						case PANEL_bplus:
							result += atof(DisplayValue);
						break;
						
						case PANEL_bminus:
							result -= atof(DisplayValue);
						break;
						
						case PANEL_btimes:
							result *= atof(DisplayValue);
						break;
						
						case PANEL_bdivide:
							result /= atof(DisplayValue);
						break;
					}
					temp = (control == PANEL_bdel) ? temp : control; // Prevents assigning "delete" to temp
					if(control == PANEL_bdel)
					{
						DisplayValue[strlen(DisplayValue) - 1] = '\0';
						SetCtrlVal(panelHandle, PANEL_CalcDisplay, DisplayValue);
					}
					if (control == PANEL_bequal)
					{
						sprintf(DisplayValue, "%f", result);
						SetCtrlVal(panelHandle, PANEL_CalcDisplay, DisplayValue);
					}
				}
			}
		break;
	}
	return 0;
}

int CVICALLBACK MyNumButtons (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			// Check what number button was pressed
			GetCtrlAttribute (panelHandle, control, ATTR_LABEL_TEXT, button_label);
			// Get current displayed value
			GetCtrlVal (panelHandle, PANEL_CalcDisplay, DisplayValue);
			strcat(DisplayValue, button_label);
			SetCtrlVal (panelHandle, PANEL_CalcDisplay, DisplayValue);
			break;
	}
	return 0;
}

