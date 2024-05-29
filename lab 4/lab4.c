#include <ansi_c.h>
#include <analysis.h>
#include <cvirte.h>		
#include <userint.h>
#include "lab4.h"

static int panelHandle, ctrlarray;

double A[9],B[3] , C[3];

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "lab4.uir", PANEL)) < 0)
		return -1;
	ctrlarray = GetCtrlArrayFromResourceID (panelHandle, CTRLARRAY);
	DisplayPanel (panelHandle);
	//MessagePopup ("sadsda", "gggggggaa");

	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK quit (int panel, int control, int event,
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

int CVICALLBACK calc (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	double x;
	switch (event)
	{
		case EVENT_COMMIT:
			
			switch (control)
			{
				case PANEL_CALCB:
					
					GetTableCellRangeVals (panelHandle, PANEL_TABLE, MakeRect (1, 1, 3, 3), A, VAL_ROW_MAJOR);
					GetTableCellRangeVals (panelHandle, PANEL_TABLE_2, MakeRect (1, 1, 3, 1), B, VAL_ROW_MAJOR);
					MatrixMul (A, B, 3, 3, 1, C);
					SetTableCellRangeVals (panelHandle, PANEL_TABLE_3, MakeRect (1, 1, 3, 1), C, VAL_COLUMN_MAJOR);
					break;
				
				case PANEL_CALCX:
					GetTableCellRangeVals (panelHandle, PANEL_TABLE, MakeRect (1, 1, 3, 3), A, VAL_ROW_MAJOR);
					GetTableCellRangeVals (panelHandle, PANEL_TABLE_3, MakeRect (1, 1, 3, 1), B, VAL_ROW_MAJOR);
					Determinant (A, 3,&x) ;
					if (!fabs(x))
					  MessagePopup ("Singular matrix", "Det = 0");
					else 
					{
						InvMatrix (A, 3, A);
						MatrixMul (A, B, 3, 3, 1, C);
						SetTableCellRangeVals (panelHandle, PANEL_TABLE_2, MakeRect (1, 1, 3, 1), C, VAL_COLUMN_MAJOR);
					}
			}				  
			break;
	}
	return 0;
}

int CVICALLBACK Print (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	
	FILE *fp;
	switch (event)
	{
			
			
		case EVENT_COMMIT:
			 fp = fopen ("Data.txt", "w");
			   int k=0;
			 
			 while (1)
			 {
				 k++;
				 fprintf(fp,"Henlo pls\t%d\n",k);
				 fprintf(stdout,"Henlo pls\t%d\n",k); 
				 
				 
			 }
			 
			 
			 

			 
			 fclose (fp);
			 
			break;
	}
	return 0;
}
