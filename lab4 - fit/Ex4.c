#include <analysis.h>
#include <ansi_c.h>
#include <cvirte.h>
#include <userint.h>
#include "Ex4.h"

#define SIZE 100

static int panelHandle, tabHandle;
int active;

double X[SIZE], Y[SIZE], R[SIZE];
int LEN;

int lin_en, exp_en, poly_en;


int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Ex4.uir", PANEL)) < 0)
		return -1;

	DisplayPanel (panelHandle);
	SetPanelAttribute(panelHandle, ATTR_TITLE, "Regression");
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


int CVICALLBACK clear_button (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	
	int clear_active;

	switch (event)
	{
		case EVENT_COMMIT:
			
			GetActiveTabPage (panelHandle, PANEL_TAB, &clear_active);
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB, clear_active, &tabHandle);
			  				
			switch (clear_active)
				{
					case 0: // Linear
					{
						DeleteGraphPlot (tabHandle, lin_GRAPH, -1, VAL_IMMEDIATE_DRAW);
						break;
					}

					case 1: // Exponent
					{   
						DeleteGraphPlot (tabHandle, exp_GRAPH, -1, VAL_IMMEDIATE_DRAW);
						break;
					}

					case 2: // Polynomial
					{
						DeleteGraphPlot (tabHandle, poly_GRAPH, -1, VAL_IMMEDIATE_DRAW);
						break;
					}
				}
			break;
	}
	return 0;
}


int CVICALLBACK load_button (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	char FileName[MAX_PATHNAME_LEN];
	FILE *fp;
	int err;

	switch (event)
	{
		case EVENT_COMMIT:
			
			GetActiveTabPage (panelHandle, PANEL_TAB, &active);
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB, active, &tabHandle);

			err = FileSelectPopup ("", "*.txt", "", "File To Load", VAL_OK_BUTTON, 0, 1, 1, 0, FileName);
			if (err > 0)
			{
				fp = fopen (FileName, "r");

				for (LEN = 0; !feof(fp); LEN++)
					fscanf(fp, "%lf%lf", X+LEN, Y+LEN);


				switch (active)
				{
					case 0: // Linear 
					{
						PlotXY (tabHandle, lin_GRAPH, X, Y, LEN, VAL_DOUBLE, VAL_DOUBLE, VAL_SCATTER, VAL_SOLID_SQUARE, VAL_SOLID, 1, VAL_BLUE);
						lin_en = 1;
						exp_en = 0;
						poly_en = 0;	
						break;
					}

					case 1: // Exponent
					{   
						PlotXY (tabHandle, exp_GRAPH, X, Y, LEN, VAL_DOUBLE, VAL_DOUBLE, VAL_SCATTER, VAL_SOLID_SQUARE, VAL_SOLID, 1, VAL_BLUE);
						lin_en = 0;
						exp_en = 1;
						poly_en = 0;
						break;
					}

					case 2: // Polynomial
					{
						PlotXY (tabHandle, poly_GRAPH, X, Y, LEN, VAL_DOUBLE, VAL_DOUBLE, VAL_SCATTER, VAL_SOLID_SQUARE, VAL_SOLID, 1, VAL_BLUE);
						lin_en = 0;
						exp_en = 0;
						poly_en = 1;
						break;
					}
				}

				fclose(fp);
			}
			break;
	}
	return 0;
}



int CVICALLBACK fit_button (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	
	double a, b, c; 
	double C[SIZE];
	int ord;
	
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			GetActiveTabPage (panelHandle, PANEL_TAB, &active);
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB, active, &tabHandle);
			
			switch (active)
				{
					case 0: // Linear
					{
						if (lin_en)
						{
							LinFit (X, Y, LEN, R, &a, &b, &c);
							PlotXY (tabHandle,lin_GRAPH , X, R, LEN, VAL_DOUBLE, VAL_DOUBLE, VAL_FAT_LINE, VAL_SOLID_SQUARE, VAL_SOLID, 1, VAL_RED);
							SetCtrlVal (tabHandle, lin_s_num, a);
							SetCtrlVal (tabHandle, lin_i_num, b);
							SetCtrlVal (tabHandle, lin_e_num, c);
						}
						break;
					}

					case 1: // Exponent
					{   
						if (exp_en)
						{
							ExpFit (X, Y, LEN, R, &a, &b, &c);
							PlotXY (tabHandle, exp_GRAPH, X, R, LEN, VAL_DOUBLE, VAL_DOUBLE, VAL_FAT_LINE, VAL_SOLID_SQUARE, VAL_SOLID, 1, VAL_RED);
							SetCtrlVal (tabHandle, exp_a_num, a);
							SetCtrlVal (tabHandle, exp_d_num, b);
							SetCtrlVal (tabHandle, exp_e_num, c);
						}
						break;
					}

					case 2: // Polynomial
					{
		 				if (poly_en)
						{
							GetCtrlVal(tabHandle, poly_o_num, &ord);
							if (ord >= LEN)
							{
								MessagePopup ("Error", "Order must be smaller number of points");
								return -1;
							}
			
							PolyFit (X, Y, LEN, ord, R, C, &c);
							PlotXY (tabHandle,poly_GRAPH , X, R, LEN, VAL_DOUBLE, VAL_DOUBLE, VAL_FAT_LINE, VAL_SOLID_SQUARE, VAL_SOLID, 1, VAL_RED);
							SetCtrlVal (tabHandle, poly_c_num_0, C[0]);
							SetCtrlVal (tabHandle, poly_c_num_1, C[1]);
							SetCtrlVal (tabHandle, poly_c_num_2, C[2]);
							SetCtrlVal (tabHandle, poly_c_num_3, C[3]);
							SetCtrlVal (tabHandle, poly_c_num_4, C[4]);
							SetCtrlVal (tabHandle, poly_c_num_5, C[5]);
							SetCtrlVal (tabHandle, poly_c_num_6, C[6]);
							SetCtrlVal (tabHandle, poly_c_num_7, C[7]);

							SetCtrlVal (tabHandle, poly_e_num, c);
						}
						break;
					}
				}
			break;
	}
	return 0;
}
