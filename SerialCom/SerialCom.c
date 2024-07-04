#include <utility.h>
#include <ansi_c.h>
#include <rs232.h>
#include <cvirte.h>		
#include <userint.h>
#include "SerialCom.h"

static int panelHandle, panelHandleRx, panelHandleTx;
static int bmpHandlerTx, bmpHandlerRx;
int SendCom = 5;
int RecvCom = 6;
int Err;
int LineNum = 0;

/*********************************************************************/
void CVICALLBACK MyCallback (int portNumber, int eventMask, void *callbackData)
{
char RecBuff[100];
int N;
	N = ComRdTerm (RecvCom, RecBuff, 100, 0);
	RecBuff[N] = 0;
	InsertTextBoxLine (panelHandle, PANEL_RECIVER, -1, RecBuff);
	SetCtrlAttribute (panelHandle, PANEL_RECIVER, ATTR_FIRST_VISIBLE_LINE, LineNum++);
	return;
}
/*********************************************************************/
void MyPolling ()
{
char RecBuff[100];
int N;
	N = ComRdTerm (RecvCom, RecBuff, 100, 0);
	RecBuff[N] = 0;
	InsertTextBoxLine (panelHandle, PANEL_RECIVER, -1, RecBuff);
	SetCtrlAttribute (panelHandle, PANEL_RECIVER, ATTR_FIRST_VISIBLE_LINE, LineNum++);
	return;
}
/*********************************************************************/
int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "SerialCom.uir", PANEL)) < 0)
		return -1;
	if ((panelHandleRx = LoadPanel (0, "SerialCom.uir", PANEL_2)) < 0)
		return -1;
	if ((panelHandleTx = LoadPanel (0, "SerialCom.uir", PANEL_3)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	Err = CloseCom (SendCom);
	Err = CloseCom (RecvCom);
	
	return 0;
}
/*********************************************************************/
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
/*********************************************************************/
int CVICALLBACK Config (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			Err = OpenComConfig (SendCom, "", 9600, 0, 7, 1, 512, 512);
			Err = OpenComConfig (RecvCom, "", 9600, 0, 7, 1, 512, 512);
			
			SetCtrlAttribute (panelHandle, PANEL_SENDSTRING, ATTR_DIMMED, 0);
			SetCtrlAttribute (panelHandle, PANEL_Q4_numeric, ATTR_DIMMED, 0);
			SetCtrlAttribute (panelHandle, PANEL_BINARYSWITCH, ATTR_DIMMED, 0);
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 1);
			break;
	}
	return 0;
}
/*********************************************************************/
int CVICALLBACK SendString (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
char SendBuff[100];
int Len;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_SENDSTRING, SendBuff);
			Len = strlen(SendBuff);
			ComWrt (SendCom, SendBuff, Len+1);
			Delay(0.1);
			break;
	}
	return 0;
}
/*********************************************************************/
int CVICALLBACK RecTimer (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
char RecBuff[100];
int N;
	switch (event)
	{
		case EVENT_TIMER_TICK:
			N = GetInQLen (RecvCom);
			if (!N)  return(0);
			MyPolling ();
			break;
	}
	return 1;
}
/*********************************************************************/
int CVICALLBACK RecMode (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int Mode;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_BINARYSWITCH, &Mode);
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, !Mode);
			if (Mode)
				InstallComCallback (RecvCom, LWRS_RXFLAG, 0, 0, MyCallback, 0);
			else
				InstallComCallback (RecvCom, LWRS_RXFLAG, 0, 0, 0, 0); 
			break;
	}
	return 0;
}
/*********************************************************************/

int CVICALLBACK SendNumeric (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	double NumBuff;
	char SendBuff[100];
	int Len;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_Q4_numeric, &NumBuff);
			sprintf(SendBuff, "%f", NumBuff);
			Len = strlen(SendBuff);
			ComWrt (SendCom, SendBuff, Len+1);
			Delay(0.1);
			break;
	}
	return 0;
}

/*********************************************************************/

void CVICALLBACK RxPanel (int menuBar, int menuItem, void *callbackData,
						  int panel)
{
	 DisplayPanel (panelHandleRx);
}

/*********************************************************************/

void CVICALLBACK TxPanel (int menuBar, int menuItem, void *callbackData,
						  int panel)
{
	DisplayPanel (panelHandleTx);
}

/*********************************************************************/

int CVICALLBACK RxSelectFile (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

/*********************************************************************/

int CVICALLBACK SendFile (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

/*********************************************************************/

int CVICALLBACK TxSelectFile (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	char FileName[260];
	switch (event)
	{
		case EVENT_COMMIT:
			FileSelectPopup ("", "*.jpg", "", "", VAL_LOAD_BUTTON, 0, 1, 1, 0, FileName);
			GetBitmapFromFile (FileName, &bmpHandler);
			

			break;
	}
	return 0;
}

/*********************************************************************/

int CVICALLBACK ClosePanelTx (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			HidePanel (PanelHandleTx);
			break;
	}
	return 0;
}

/*********************************************************************/

int CVICALLBACK ClosePanelRx (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			HidePanel (PanelHandleRx);
			break;
	}
	return 0;
}
