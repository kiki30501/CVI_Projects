#include <formatio.h>
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include <math.h>
#include "Question1.h"

#define plot_length 1000

static int panelHandle, arrayHandle, ph2, plot_I_res, plot_v1, plot_v2, plot_vdiff, dest_file;
int n;
double v1, v2, i, dt, Q1, Q2, c1, c2, r, i_src1, i_src2, tau1, tau2;
double  *values[] = {&v1, &v2, &dt, &c1, &c2, &r, &i_src1, &i_src2};
double I_res_vals[plot_length], v1_vals[plot_length], v2_vals[plot_length], vdiff_vals[plot_length];


int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel(0, "Question1.uir", PANEL)) < 0)
		return -1;
	if ((ph2 = LoadPanel(0, "Question1.uir", PANEL_2)) < 0)
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
			Q1 = (i - i_src1) * dt;
			Q2 = (i + i_src2) * dt;
			v1 -= Q1 / c1;
			v2 += Q2 / c2;
			SetCtrlVal(panelHandle, PANEL_V1, v1);
			SetCtrlVal(panelHandle, PANEL_V2, v2);
			
			I_res_vals[n] = i;
			v1_vals[n] = v1;
			v2_vals[n] = v2;
			vdiff_vals[n] = v1 - v2;
			
			
			
			n += (n < plot_length-1); // increment n so long as it's below the limit for the plot length
			break;
	}
	return 0;
}


int CVICALLBACK StartSim (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	int x, manual;
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
			tau2 = (c1+c2)/(r*c1*c2);
			SetCtrlVal (ph2, PANEL_2_CalcTau, tau2); // Calculate tau2 and set it to the control
			
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
			n = 0;
			DeleteGraphPlot (ph2, PANEL_2_GRAPH, -1, VAL_IMMEDIATE_DRAW);
			SetCtrlAttribute (panelHandle, PANEL_RUN_TIMER, ATTR_ENABLED, 0); // Stop the timer
			SetCtrlAttribute (panelHandle, PANEL_GOB, ATTR_CMD_BUTTON_COLOR, VAL_GREEN);
			DefaultCtrl (panelHandle, PANEL_V1);
			DefaultCtrl (panelHandle, PANEL_V2);
			DefaultCtrl (panelHandle, PANEL_STRING);
			break;
	}
	return 0;
}

void CVICALLBACK open_panel_graph (int menuBar, int menuItem, void *callbackData,
								   int panel)
{
	DisplayPanel (ph2);
}

int CVICALLBACK close_graph (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			HidePanel(ph2);
			break;
	}
	return 0;
}



int CVICALLBACK PlotNow (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			DeleteGraphPlot (ph2, PANEL_2_GRAPH, -1, VAL_NO_DRAW);
			switch(control)
			{
				case PANEL_2_PLOTI_RES:
					plot_I_res = 	PlotWaveform (ph2, PANEL_2_GRAPH, I_res_vals, 	n, VAL_DOUBLE, 1.0, 0.0, 0.0, dt, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 10, VAL_RED);
					break;
				case PANEL_2_PLOTV1:
					plot_v1 = 		PlotWaveform (ph2, PANEL_2_GRAPH, v1_vals, 		n, VAL_DOUBLE, 1.0, 0.0, 0.0, dt, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 10, VAL_GREEN);
					break;
				case PANEL_2_PLOTV2:
					plot_v2 = 		PlotWaveform (ph2, PANEL_2_GRAPH, v2_vals, 		n, VAL_DOUBLE, 1.0, 0.0, 0.0, dt, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 10, VAL_BLUE);
					break;
				case PANEL_2_PLOTVDIFF:
					plot_vdiff = 	PlotWaveform (ph2, PANEL_2_GRAPH, vdiff_vals, 	n, VAL_DOUBLE, 1.0, 0.0, 0.0, dt, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 10, VAL_YELLOW);
					// Calculate Log plot slope based on vdiff (should result in the same value as "tau")
					tau1 = -1 * (log(vdiff_vals[n-1]) - log(vdiff_vals[0])) / (n * dt);
					SetCtrlVal (ph2, PANEL_2_PlotSlope, tau1);
					SetCtrlVal (ph2, PANEL_2_TauDiff, (tau1-tau2));
					break;
			}
			break;
	}
	return 0;
}

int CVICALLBACK LinLogXAxis (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	int x;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (ph2, PANEL_2_LINLOGSWITCH, &x);
			SetCtrlAttribute (ph2, PANEL_2_GRAPH, ATTR_YMAP_MODE, x);
			break;
	}
	return 0;
}

int CVICALLBACK MyCursors (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	static double x1, x2, y1, y2;
	switch (event)
	{
		case EVENT_COMMIT:
			GetGraphCursor (ph2, PANEL_2_GRAPH, 1, &x1, &y1);
			GetGraphCursor (ph2, PANEL_2_GRAPH, 2, &x2, &y2);
			SetCtrlVal (ph2, PANEL_2_Cursor1_X, x1);
			SetCtrlVal (ph2, PANEL_2_Cursor1_Y, y1);
			SetCtrlVal (ph2, PANEL_2_Cursor2_X, x2);
			SetCtrlVal (ph2, PANEL_2_Cursor2_Y, y2);
			break;
	}
	return 0;
}

int CVICALLBACK FileSave (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			break;
	}
	return 0;
}
