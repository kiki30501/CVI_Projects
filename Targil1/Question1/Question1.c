#include <cvirte.h>		
#include <userint.h>
#include "Question1.h"

static int question1;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((question1 = LoadPanel (0, "Question1.uir", Question1)) < 0)
		return -1;
	DisplayPanel (question1);
	RunUserInterface ();
	DiscardPanel (question1);
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

int CVICALLBACK MyTextPrint (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	static int flag = 0;
	switch (event)
	{
		case EVENT_COMMIT:
			flag = ~flag;
			SetCtrlVal (question1, Question1_HELLO, (flag ? "Hello World" : ""));
			break;
	}
	return 0;
}
