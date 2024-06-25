#include <analysis.h>
#include <ansi_c.h>
#include <userint.h>
#include "Ex4.h"

#define PI 3.14159265359 
#define G_FORCE 9.81
#define SIZE 10000

static int panelHandle, panelGraphsHandle, plotHandle, plotHandle_n, plotFFTHandle, plotFFTHandle_n;

double t, dt, length, theta, theta_0, omega, omega_0;
// double m;	// Not used?
double t_value[SIZE], theta_value[SIZE];
double fft_value[SIZE], fft_im_value[SIZE], magnitude[SIZE], phase[SIZE];
double theta_n, theta_n_value[SIZE], fft_n_value[SIZE], fft_im_n_value[SIZE], magnitude_n[SIZE], phase_n[SIZE];

int i = 0;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Ex4.uir", PANEL)) < 0)
		return -1;
	if ((panelGraphsHandle = LoadPanel (0, "Ex4.uir", Graphs)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	SetPanelAttribute(panelHandle, ATTR_TITLE, "Pendulum");
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


int CVICALLBACK quit_graph_button (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			HidePanel (panelGraphsHandle);
			break;
	}
	return 0;
}


void calc_theta_n()
{
	// Function to numerical calculate theta
	omega = omega - omega_0 * omega_0 * sin(theta_n) * dt;
	theta_n = theta_n + omega * dt; 
}


int FFT_graphs(double amplitude_value[], int i, double fft_arr[], double fft_img_arr[], double magnitude_arr[], double phase_arr[], int color)
{
	int handle;
	
	// Calc.
	Copy1D (amplitude_value, i, fft_arr);
	ReFFT (fft_arr, fft_img_arr, i);
	ToPolar1D (fft_arr, fft_img_arr, i, magnitude_arr, phase_arr);
	LinEv1D (magnitude_arr, i, 2.0/i, 0.0, magnitude_arr);
	
	// Plot
	handle = PlotY (panelGraphsHandle, Graphs_FFTGRAPH, magnitude_arr, 101, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, color);
	
	return handle;
}


int CVICALLBACK timer (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
			
			// Real calc.
			theta_n_value[i] = theta_n * (180/PI);
			calc_theta_n();
			
			// Approx. for small theta
			theta_value[i] = theta * (180/PI);
			theta = theta_0 * sin(omega_0*t); 
			
			// Time calc.
			t_value[i] = t;
			t = t + dt;
			i++;
			
			// Update UI values
			SetCtrlVal (panelHandle, PANEL_Gauge, theta * (180/PI));
			SetCtrlVal (panelHandle, PANEL_timeShow, t);
			break;
	}
	return 0;
}


int CVICALLBACK start_func (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	static int x = 0;
	switch (event)
	{
		case EVENT_COMMIT:
			
			// Start/Stop
			if (!x)
				i = 0;
			x = !x;
			
			// Allow Graphs
			SetCtrlAttribute (panelHandle, PANEL_graph_button, ATTR_DIMMED, 0);
			
			// Values
			GetCtrlVal (panelHandle, PANEL_dt_num, &dt);
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_INTERVAL, dt);
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, x);
			GetCtrlVal (panelHandle, PANEL_length_num, &length);
			// GetCtrlVal (panelHandle, PANEL_mass_num, &m);	// Not used?
			GetCtrlAttribute (panelHandle, PANEL_Gauge, ATTR_CTRL_VAL, &theta_0);
			
			// Initial values
			theta_0 = theta_0 * (PI/180);
			omega_0 = sqrt(G_FORCE/length);
			omega = omega_0;
			theta = theta_0;
			theta_n = theta_0;

			break;
	}
	return 0;
}


int CVICALLBACK graph_button (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			// Open graphs panel
			DisplayPanel (panelGraphsHandle);
			SetPanelAttribute(panelGraphsHandle, ATTR_TITLE, "Graphs");
	
			// Time
			if (plotHandle || plotHandle_n)
				DeleteGraphPlot (panelGraphsHandle, Graphs_GRAPH, plotHandle, VAL_IMMEDIATE_DRAW);
			
			// FFT
			if (plotFFTHandle || plotFFTHandle_n)
				DeleteGraphPlot (panelGraphsHandle, Graphs_FFTGRAPH, plotFFTHandle, VAL_IMMEDIATE_DRAW);
			
			// Time
			plotHandle = PlotXY (panelGraphsHandle, Graphs_GRAPH, t_value, theta_value, i, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_RED);
			plotHandle_n = PlotXY (panelGraphsHandle, Graphs_GRAPH, t_value, theta_n_value, i, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_BLUE);
			
			// FFT
			plotFFTHandle = FFT_graphs(theta_value, i, fft_value, fft_im_value, magnitude, phase, VAL_RED);
			plotFFTHandle_n =  FFT_graphs(theta_n_value, i, fft_n_value, fft_im_n_value, magnitude_n, phase_n, VAL_BLUE);
			break;
	}
	return 0;
}
