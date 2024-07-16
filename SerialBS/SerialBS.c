#include <cvirte.h>		
#include <userint.h>
#include <rs232.h>
#include <ansi_c.h>
#include <utility.h>
#include "SerialBS.h"


static int panelHandle;
int SendCom = 2;
int RecvCom = 3;
int Err;
int data[] = {10, 20, 40, 50, 70, 80, 100, 110, 130, 140, 1000000 ,'\0'};

int x = 0;
void MyPolling(int N)
{
	int M;
	static char newnew[48];
	char RecBuff[200];
	
	//newnew[x]= (char)(ComRdByte (3));
	ComRd (3, newnew, N);
	int *newdata = (int*)newnew;
	
	//x++;
	
	/*if(x == sizeof(data)-1)
	{
		SetCtrlVal (panelHandle, PANEL_LED, 1);
		int *newdata = (int*)newnew;
		for (int i = 0; i < 10; i++)
		{
			printf("New data %d: %d\n", i, newdata[i]);
		}
	}*/
}

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "SerialBS.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	Err = CloseCom (SendCom);
	Err = CloseCom (RecvCom);
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

int CVICALLBACK SendIntArr (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	char SendBuff[200];
	int Len;
	switch (event)
	{
		case EVENT_COMMIT:
			
			
			char *Sendy = (char*)data;
			Len = sizeof(data);
			ComWrt(SendCom, Sendy, sizeof(data));
			
			Delay(0.1);
			break;
	}
	return 0;
}

int CVICALLBACK Config (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			// Included parity bits
			Err = OpenComConfig (SendCom, "", 9600, 1, 8, 1, 512, 512);
			Err = OpenComConfig (RecvCom, "", 9600, 1, 8, 1, 512, 512);
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 1);
			
			break;
	}
	return 0;
}



int CVICALLBACK RecTimer (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	int N;
	switch (event)
	{
		case EVENT_TIMER_TICK:
			N = GetInQLen (RecvCom);
			if (!N)  return(0);
			MyPolling (N);
			break;
	}
	return 1;
}
