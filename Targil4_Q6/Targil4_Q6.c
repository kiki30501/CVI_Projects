#include <cvirte.h>		
#include <userint.h>
#include <math.h>
#include "Targil4_Q6.h"

#define plotlength (1024*128)
#define gravity 9.81
#define PI 3.14159265359

static int ph1, ph2, n;
double length, mass, dt, t, theta, theta_approx, omega, omega_approx, fftarr[plotlength], timearr[plotlength];
double timearr_approx[plotlength], fftarr_approx[plotlength];

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((ph1 = LoadPanel (0, "Targil4_Q6.uir", PANEL)) < 0)
		return -1;
	if ((ph2 = LoadPanel (0, "Targil4_Q6.uir", PANEL_2)) < 0)
		return -1;
	DisplayPanel (ph1);
	RunUserInterface ();
	DiscardPanel (ph1);
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

int CVICALLBACK RunSim (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
			omega += -1 * pow(omega, 2) * sin(theta) * dt;
			theta += omega * dt;
			//omega_approx = -1 * pow(omega_approx, 2) * theta_approx * dt;
			theta_approx += omega_approx * dt;
			SetCtrlVal (ph1, PANEL_MyPendulum, theta);
			timearr[n] = theta;
			timearr_approx[n] = theta_approx;
			n += (n < plotlength - 1);
			t += dt;
			SetCtrlVal (ph1, PANEL_CurrTime, t);
			break;
	}
	return 0;
}

int CVICALLBACK ToggleSimRun (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	static int x = 0;
	switch (event)
	{
		case EVENT_COMMIT:
			x = x ? 0 : 1;
			GetCtrlVal (ph1, PANEL_MyLength, &length);
			GetCtrlVal (ph1, PANEL_MyMass, &mass);
			GetCtrlVal (ph1, PANEL_CtrlInterval, &dt);
			GetCtrlVal (ph1, PANEL_MyPendulum, &theta);
			SetCtrlAttribute (ph1, PANEL_TIMER, ATTR_INTERVAL, dt);
			SetCtrlAttribute (ph1, PANEL_TIMER, ATTR_ENABLED, x);
			omega = omega_approx = sqrt(gravity/length);
			theta_approx = theta;
			break;
	}
	return 0;
}

int CVICALLBACK SimReset (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			n = 0;
			t = 0;
			DeleteGraphPlot (ph2, PANEL_2_GRAPH, -1, VAL_IMMEDIATE_DRAW);
			SetCtrlAttribute (ph1, PANEL_TIMER, ATTR_ENABLED, 0); // Stop the timer
			DefaultCtrl (ph1, PANEL_MyPendulum);
			break;
	}
	return 0;
}

int CVICALLBACK HideGraphPanel (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			HidePanel (ph2);
			break;
	}
	return 0;
}

int CVICALLBACK CursorGet (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	double x1, x2, y1, y2;
	switch (event)
	{
		case EVENT_COMMIT:
			GetGraphCursor (ph2, PANEL_2_GRAPH, 1, &x1, &y1);
			GetGraphCursor (ph2, PANEL_2_GRAPH, 2, &x2, &y2);
			SetCtrlVal (ph2, PANEL_2_CursorX1, x1);
			SetCtrlVal (ph2, PANEL_2_CursorY1, y1);
			SetCtrlVal (ph2, PANEL_2_CursorX2, x2);
			SetCtrlVal (ph2, PANEL_2_CursorY2, y2);
			break;
	}
	return 0;
}

void CVICALLBACK OpenGraphPanel (int menuBar, int menuItem, void *callbackData,
								 int panel)
{
	DisplayPanel(ph2);
}

int CVICALLBACK MyPlots (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	DeleteGraphPlot (ph2, PANEL_2_GRAPH, -1, VAL_IMMEDIATE_DRAW);
	switch (event)
	{
		case EVENT_COMMIT:
			switch (control)
			{
				case PANEL_2_FFT:
					
					break;
					
				case PANEL_2_TimePlot:
					PlotWaveform (ph2, PANEL_2_GRAPH, timearr, n, VAL_DOUBLE, 1.0, 0.0, 0.0, dt, VAL_FAT_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_BLUE);
					PlotWaveform (ph2, PANEL_2_GRAPH, timearr_approx, n, VAL_DOUBLE, 1.0, 0.0, 0.0, dt, VAL_FAT_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_DK_YELLOW);
					break;
			}
			break;
	}
	return 0;
}
