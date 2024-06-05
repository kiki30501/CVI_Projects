#include <advanlys.h>
#include <formatio.h>
#include <cvirte.h>		
#include <userint.h>
#include <stdio.h>
#include "Targil4_Q5.h"

#define NUM_OF_GRADES 40

static int panelHandle;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Targil4_Q5.uir", PANEL)) < 0)
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
	}
	return 0;
}

int CVICALLBACK FileOpen (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	char FileName[MAX_PATHNAME_LEN];
	FILE *fp;
	int err, hist[10];
	double grades[NUM_OF_GRADES];
 	double x[10];
	double x_mode, x_median, x_mean, x_stddev;
	Set1D (grades, NUM_OF_GRADES, 0.0);
	switch (event)
	{
		case EVENT_COMMIT:
			err = FileSelectPopup ("", "*.txt", "", "Open Grades File", VAL_LOAD_BUTTON, 0, 0, 1, 0, FileName);
			if(err>0)
			{
				// Read file contents into array
				fp = fopen (FileName, "r");
				for (int i = 0; i < NUM_OF_GRADES && fscanf(fp, "%lf", &grades[i]) == 1; i++) {}
				fclose(fp);
				Histogram (grades, NUM_OF_GRADES, 0.0, 100.0, hist, x, 10.0);
				DeleteGraphPlot (panelHandle, PANEL_MyGraph, -1, VAL_IMMEDIATE_DRAW);
				PlotXY (panelHandle, PANEL_MyGraph, x, hist, 10, VAL_DOUBLE, VAL_INTEGER, VAL_VERTICAL_BAR, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_RED);
				StdDev (grades, NUM_OF_GRADES, &x_mean, &x_stddev);
				Median (grades, NUM_OF_GRADES, &x_median);
				Mode (grades, NUM_OF_GRADES, 0.0, 100.0, 10, &x_mode);
				SetCtrlVal (panelHandle, PANEL_MyMean, x_mean);
				SetCtrlVal (panelHandle, PANEL_MyStdDev, x_stddev);
				SetCtrlVal (panelHandle, PANEL_MyMedian, x_median);
				SetCtrlVal (panelHandle, PANEL_MyMode, x_mode);
			}
			
			break;
	}
	return 0;
}
