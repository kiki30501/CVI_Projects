#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "Picture.h"

static int panelHandle;
static int bmpHandler, bmpHandlerTemp;
int ColorSize, BitSize, MaskSize;
int ByteInRow, Pixel, pWidth, pHeight;
unsigned char *MyPicData;

int CanvasSizeX, CanvasSizeY;
static int Top=0, Left=0, Width=128, Height=128;


/*******************************************************************************************/
int SatInt (int Num, int Min, int Max)
{
	
	if (Num>Max)
		return Max;
	if (Num<Min)
		return Min;
	return Num;
}
/*******************************************************************************************/
int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Picture.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	GetCtrlAttribute (panelHandle, PANEL_CANVAS1, ATTR_HEIGHT, &CanvasSizeY);
	GetCtrlAttribute (panelHandle, PANEL_CANVAS1, ATTR_WIDTH, &CanvasSizeX);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	free(MyPicData);
	return 0;
}
/*******************************************************************************************/
int CVICALLBACK QuitCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface (0);
			break;
		case EVENT_RIGHT_CLICK:

			break;
	}
	return 0;
}
/*******************************************************************************************/
int CVICALLBACK LoadPic (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
char FileName[260];
	switch (event)
	{
		case EVENT_COMMIT:
			FileSelectPopup ("", "*.jpg", "", "", VAL_LOAD_BUTTON, 0, 0, 1, 1, FileName);
			GetBitmapFromFile (FileName, &bmpHandler);
			CanvasDrawBitmap (panelHandle, PANEL_CANVAS1, bmpHandler, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
			
	// BitSize = pWidth * pHeight * (Pixel/8)
	// ByteInRow = pWidth * (Pixel/8)
			GetBitmapInfo (bmpHandler, &ColorSize, &BitSize, &MaskSize);
			MyPicData = (unsigned char*) malloc(BitSize);
			GetBitmapData (bmpHandler, &ByteInRow, &Pixel, &pWidth, &pHeight, NULL, MyPicData, NULL);
			
			SetCtrlAttribute (panelHandle, PANEL_CANVAS1, ATTR_PEN_COLOR, VAL_DK_YELLOW);
			SetCtrlAttribute (panelHandle, PANEL_CANVAS1, ATTR_PEN_MODE, VAL_XOR_MODE);
			CanvasDrawRect (panelHandle, PANEL_CANVAS1, MakeRect (Top, Left, Height, Width), VAL_DRAW_FRAME);
			break;
	}
	return 0;
}
/*******************************************************************************************/
int CVICALLBACK Xor (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int k,j;
unsigned char *TempPicData;
	switch (event)
	{
		case EVENT_COMMIT:
			TempPicData = MyPicData;
			for (k=0; k<pHeight; k++)
				for (j=0; j<pWidth; j++)
					((unsigned int *)TempPicData)[k*pWidth+j] ^= 0xFFFFFFFF;	
			
			NewBitmap (ByteInRow, Pixel, pWidth, pHeight, NULL, TempPicData, NULL,
					   &bmpHandlerTemp);
			
			CanvasDrawBitmap (panelHandle, PANEL_CANVAS2, bmpHandlerTemp,
							  VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
			
			DiscardBitmap (bmpHandlerTemp);
	
			break;
	}
	return 0;
}
/*******************************************************************************************/
int MakeZoomBmp ()
{
int k,j,i;
unsigned char *TempPicData;
int relTop, relLeft,relWidth, relHeight;

	//normalize the picture size to canvas size
	relWidth = Width*pWidth/CanvasSizeX;
	relHeight = Height*pHeight/CanvasSizeY;
	relLeft = Left*pWidth/CanvasSizeX;
	relTop = Top*pHeight/CanvasSizeY;

	TempPicData = (unsigned char*) malloc(relWidth*relHeight*(Pixel/8));
	i = 0;
	for (k=relTop; k<relHeight+relTop; k++)
		for (j=relLeft; j<relWidth+relLeft; j++)
			((unsigned int *)TempPicData)[i++] = ((unsigned int *)MyPicData)[k*pWidth+j];	

	NewBitmap (relWidth * (Pixel/8), Pixel, relWidth, relHeight, NULL, TempPicData, NULL, &bmpHandlerTemp);

	CanvasDrawBitmap (panelHandle, PANEL_CANVAS2, bmpHandlerTemp,VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);

	DiscardBitmap (bmpHandlerTemp);
	free(TempPicData);

	return 0;
}
/*******************************************************************************************/
int CVICALLBACK MoveRect (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
static int Pointer = 0;
static int Mode;
	
	switch (event)
	{
		case EVENT_LEFT_CLICK:
			Pointer = 1;
			GetCtrlVal (panelHandle, PANEL_MODE, &Mode);
			break;

		case EVENT_MOUSE_POINTER_MOVE:
			if (Pointer)
				{
				CanvasDrawRect (panelHandle, PANEL_CANVAS1, MakeRect (Top, Left, Height, Width), VAL_DRAW_FRAME);
				GetRelativeMouseState (panelHandle, PANEL_CANVAS1, &Left, &Top, NULL, NULL, NULL);
				Left = SatInt(Left, 0, CanvasSizeX-Width);
				Top = SatInt(Top, 0, CanvasSizeY-Height);
				//Top=eventData1; Left=eventData2;
				CanvasDrawRect (panelHandle, PANEL_CANVAS1, MakeRect (Top, Left, Height, Width), VAL_DRAW_FRAME);
				
				if (Mode)
					MakeZoomBmp ();	
				}
			break;

		case EVENT_LEFT_CLICK_UP:
			MakeZoomBmp ();
			Pointer = 0;
			break;
	}
	
	return 0;
}
/*******************************************************************************************/
int CVICALLBACK SavePic (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
char FileName[260];
	switch (event)
	{
		case EVENT_COMMIT:
			FileSelectPopup ("", "*.jpg", "", "", VAL_SAVE_BUTTON, 0, 0, 1, 1, FileName);
			GetCtrlBitmap (panelHandle, PANEL_CANVAS2, NULL, &bmpHandlerTemp);
			SaveBitmapToJPEGFile (bmpHandlerTemp, FileName, JPEG_DCTFLOAT, 100);
			DiscardBitmap (bmpHandlerTemp);
			break;
	}
	return 0;
}
/*******************************************************************************************/

int CVICALLBACK MyCtrls (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	int tempPixel, posCalcA, posCalcB;
	unsigned char *TempPicData, *TempRotPicData;
	int j, k;
	switch (event)
	{
		case EVENT_COMMIT:
			
			TempPicData = MyPicData;
			
			switch (control)
			{
				case PANEL_MIRX: 	// Mirror image horizontally
					for (k=0; k<pHeight; k++)
						for (j=0; j<(pWidth/2); j++)
						{
							posCalcA  = k*pWidth;
							posCalcB  = (k+1)*pWidth - j - 1;
							tempPixel = ((unsigned int *)TempPicData)[posCalcA];
							((unsigned int *)TempPicData)[posCalcA] = ((unsigned int *)TempPicData)[posCalcB];
							((unsigned int *)TempPicData)[posCalcB] = tempPixel;
						}	
					NewBitmap (ByteInRow, Pixel, pWidth, pHeight, NULL, TempPicData, NULL,
					   &bmpHandlerTemp);

					CanvasDrawBitmap (panelHandle, PANEL_CANVAS2, bmpHandlerTemp,
											  VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
					break;
				
				case PANEL_MIRY: 	// Mirror image vertically
					for (k=0; k<(pHeight/2); k++)
						for (j=0; j<pWidth; j++)
						{
							posCalcA  = k*pWidth;
							posCalcB  = (pHeight-k-1)*pWidth+j;
							tempPixel = ((unsigned int *)TempPicData)[posCalcA];
							((unsigned int *)TempPicData)[posCalcA] = ((unsigned int *)TempPicData)[posCalcB];
							((unsigned int *)TempPicData)[posCalcB] = tempPixel;
							
							
						}
					NewBitmap (ByteInRow, Pixel, pWidth, pHeight, NULL, TempPicData, NULL,
							   &bmpHandlerTemp);
			
					CanvasDrawBitmap (panelHandle, PANEL_CANVAS2, bmpHandlerTemp,
							  				VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
					break;
				
				case PANEL_ROT90CW: // Rotate image 90 deg clockwise
					TempRotPicData = TempPicData;
					for (k=0; k<(pHeight); k++)
						for (j=0; j<pWidth; j++)
						{
							posCalcA = k*pWidth+j;
							posCalcB = pHeight*(j+1) - k - 1;
							((unsigned int *)TempRotPicData)[posCalcB] = ((unsigned int *)TempPicData)[posCalcA];
						}
					NewBitmap (ByteInRow*pHeight/pWidth, Pixel, pHeight, pWidth, NULL, TempRotPicData, NULL,
							   &bmpHandlerTemp);
			
					CanvasDrawBitmap (panelHandle, PANEL_CANVAS2, bmpHandlerTemp,
							  				VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
					break;
			
				case PANEL_ROTXDEG:	// Rotate image X  deg clockwise
				
					break;
			}
			
			
			
			DiscardBitmap (bmpHandlerTemp);
			break;
	}
	return 0;
}
