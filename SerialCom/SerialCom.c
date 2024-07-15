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
int ColorSize, BitSize, MaskSize;
int ByteInRow, Pixel, pWidth, pHeight;
int ByteInRowRx, PixelRx, pWidthRx, pHeightRx, BitSizeRx;
unsigned char *MyPicDataTx, *MyPicDataRx;
int CanvasSizeX, CanvasSizeY;
static int Top=0, Left=0, Width=128, Height=128;

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

void RecvImageRx ()
{
	// Receive the data over the COM link and save the result to an image
	// The data is received in the following order: ByteInRowRx, PixelRx,
 	// pWidthRx, pHeightRx, PicDataRx
	int N;
	static char LastBuff[100];
	char RecBuff[100];
	//int RecvData[10];

	if (!strcmp(LastBuff, "ByteInRow"))
	{
		N = ComRdTerm (RecvCom, RecBuff, 100, 0);
		RecBuff[N] = 0;
		strcpy((char *)(&ByteInRowRx), RecBuff);
		strcpy(LastBuff, "0");
	}
	else if (!strcmp(LastBuff, "Pixel"))
	{
		ComRdTerm (RecvCom, (char *)(&PixelRx), 100, 0);
		strcpy(LastBuff, "0");
	}
	else if (!strcmp(LastBuff, "pWidth"))
	{
		ComRdTerm (RecvCom, (char *)(&pWidthRx), 100, 0);
		strcpy(LastBuff, "0");
	}
	else if (!strcmp(LastBuff, "pHeight"))
	{
		ComRdTerm (RecvCom, (char *)(&pWidthRx), 100, 0);
		strcpy(LastBuff, "0");
	}
	else if (!strcmp(LastBuff, "BitSize"))
	{
		ComRdTerm (RecvCom, (char *)(&BitSizeRx), 100, 0);
		strcpy(LastBuff, "0");
	}
	else if (!strcmp(LastBuff, "MyPicData"))
	{
		MyPicDataRx = (unsigned char*) malloc(BitSizeRx);
		ComRdTerm (RecvCom, (char *)(&MyPicDataRx), BitSize, 0);
		SetCtrlVal (panelHandleRx, PANEL_Rx_LED, 1);
		strcpy(LastBuff, "0");
	}
	else
	{
		N = ComRdTerm (RecvCom, RecBuff, 100, 0);
		RecBuff[N] = 0;
		strcpy (LastBuff, RecBuff);
	}
	
	return;	
}

/*********************************************************************/

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "SerialCom.uir", PANEL)) < 0)
		return -1;
	if ((panelHandleRx = LoadPanel (0, "SerialCom.uir", PANEL_Rx)) < 0)
		return -1;
	if ((panelHandleTx = LoadPanel (0, "SerialCom.uir", PANEL_Tx)) < 0)
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
	int Parity;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_COM_Rx, &RecvCom);
			GetCtrlVal (panelHandle, PANEL_COM_Tx, &SendCom);
			GetCtrlVal (panelHandle, PANEL_Parity_Toggle, &Parity);
			
			Err = OpenComConfig (SendCom, "", 9600, Parity, 8, 1, 512, 512);
			Err = OpenComConfig (RecvCom, "", 9600, Parity, 8, 1, 512, 512);
			
			SetCtrlAttribute (panelHandle, PANEL_SENDSTRING, ATTR_DIMMED, 0);
			SetCtrlAttribute (panelHandle, PANEL_Q4_numeric, ATTR_DIMMED, 0);
			SetCtrlAttribute (panelHandle, PANEL_MODE_SELECT, ATTR_DIMMED, 0);
			SetCtrlAttribute (panelHandleRx, PANEL_Rx_Rx_SelectPic, ATTR_DIMMED, 0);
			SetCtrlAttribute (panelHandleTx, PANEL_Tx_Tx_SelectPic, ATTR_DIMMED, 0);
			SetCtrlAttribute (panelHandleTx, PANEL_Tx_SendButton, ATTR_DIMMED, 0);
			SetCtrlAttribute (panelHandle, PANEL_Parity_Toggle, ATTR_DIMMED, 1);
			SetCtrlAttribute (panelHandle, PANEL_COM_Rx, ATTR_DIMMED, 1);
			SetCtrlAttribute (panelHandle, PANEL_COM_Tx, ATTR_DIMMED, 1);
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
int CVICALLBACK RecTimer_2 (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	// We tried to use a callback function, but on our PC callback functions
	// don't work for some reason. we tried running even the original
	// unmodified version of this project but it just won't work, so we switched to a timer.
	char RecBuff[100];
	int N;
	switch (event)
	{
		case EVENT_TIMER_TICK:
			N = GetInQLen (RecvCom);
			if (!N)  return(0);
			RecvImageRx ();
			break;
	}
	return 0;
}

/*********************************************************************/
int CVICALLBACK RecMode (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int Mode;
	switch (event)
	{
		case EVENT_VAL_CHANGED:
			GetCtrlVal (panelHandle, PANEL_MODE_SELECT, &Mode);
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, !Mode); // if in polling mode then enable the timer
			SetCtrlAttribute (panelHandle, PANEL_TIMER_2, ATTR_ENABLED, Mode == 2);
			switch (Mode)
			{
				case 0: //polling
					InstallComCallback (RecvCom, LWRS_RXFLAG, 0, 0, 0, 0); 
					break;
				
				case 1: //callback
					InstallComCallback (RecvCom, LWRS_RXFLAG, 0, 0, MyCallback, 0);
					break;
				
				case 2: //Image
					InstallComCallback (RecvCom, LWRS_RXFLAG, 0, 0, 0, 0);
					break;
			}
			break;
	}
	return 0;
}
/*********************************************************************/

int CVICALLBACK SendNumeric (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	// This section is implemented with sprintf. The function for the image transmission
	// we've made using the method of sending casted portions of the data.
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
	char FileName[260];
	switch (event)
	{
		case EVENT_COMMIT:
			FileSelectPopup ("", "*.jpg", "", "", VAL_LOAD_BUTTON, 0, 0, 1, 1, FileName);
			GetBitmapFromFile (FileName, &bmpHandlerRx);
			CanvasDrawBitmap (panelHandleRx, PANEL_Rx_CANVAS, bmpHandlerRx, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
			break;
	}
	return 0;
}

/*********************************************************************/

int CVICALLBACK SendBmp (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	int Len;
	int mydata[] = {11,24,546546,23,11312,9876,2112,56342,887,4598};
	switch (event)
	{
		case EVENT_COMMIT:
			// In the transmission the data we need to send is all the arguments
			// needed in the the function NewBitmap which include both the details
			// of the image and the image data (pixels).
			// To send data types that aren't char*, it's possible to use the following cast: (char *)(&x)
			
			// Create the array of messages to send
			char *SendArray[] = {
				"ByteInRow",
				(char *)(&ByteInRow),
				"Pixel",
				(char *)(&Pixel),
				"pWidth",
				(char *)(&pWidth),
				"pHeight",
				(char *)(&pHeight),
				"BitSize",
				(char *)(BitSize),
				};
			
			for (int i=0; i<8; i+=2)
			{
				Len = strlen(SendArray[i]);
				ComWrt (SendCom, SendArray[i], Len+1);
				Delay(0.1);
				Len = sizeof(int);
				ComWrt (SendCom, SendArray[i], Len);
				Delay(0.1);
			}
			Len = strlen("MyPicData");
			ComWrt (SendCom, "MyPicData", Len+1);
			// Delay(0.1);
			// ComWrt (SendCom, (char *)(MyPicDataTx), BitSize);
			// break;
			
			ComWrt (SendCom, (char *)(mydata), sizeof(mydata));
			Delay(0.1);
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
			GetBitmapFromFile (FileName, &bmpHandlerTx);
			GetBitmapInfo (bmpHandlerTx, &ColorSize, &BitSize, &MaskSize);
			MyPicDataTx = (unsigned char*) malloc(BitSize);
			GetBitmapData (bmpHandlerTx, &ByteInRow, &Pixel, &pWidth, &pHeight, NULL, MyPicDataTx, NULL);
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
			HidePanel (panelHandleTx);
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
			HidePanel (panelHandleRx);
			break;
	}
	return 0;
}
