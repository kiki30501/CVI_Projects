/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1
#define  PANEL_QUITBUTTON                 2       /* control type: command, callback function: QuitCallback */
#define  PANEL_CANVAS2                    3       /* control type: canvas, callback function: (none) */
#define  PANEL_CANVAS1                    4       /* control type: canvas, callback function: MoveRect */
#define  PANEL_SAVE                       5       /* control type: command, callback function: SavePic */
#define  PANEL_LOAD                       6       /* control type: command, callback function: LoadPic */
#define  PANEL_ROTXDEG                    7       /* control type: command, callback function: MyCtrls */
#define  PANEL_ROT90CW                    8       /* control type: command, callback function: MyCtrls */
#define  PANEL_MIRY                       9       /* control type: command, callback function: MyCtrls */
#define  PANEL_MIRX                       10      /* control type: command, callback function: MyCtrls */
#define  PANEL_XOR                        11      /* control type: command, callback function: Xor */
#define  PANEL_MODE                       12      /* control type: binary, callback function: (none) */
#define  PANEL_DEGVAL                     13      /* control type: numeric, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK LoadPic(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MoveRect(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MyCtrls(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SavePic(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Xor(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
