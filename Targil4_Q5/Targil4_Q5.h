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
#define  PANEL_MyGraph                    3       /* control type: graph, callback function: (none) */
#define  PANEL_B_FOPEN                    4       /* control type: command, callback function: FileOpen */
#define  PANEL_MyMode                     5       /* control type: numeric, callback function: (none) */
#define  PANEL_MyMedian                   6       /* control type: numeric, callback function: (none) */
#define  PANEL_MyStdDev                   7       /* control type: numeric, callback function: (none) */
#define  PANEL_MyMean                     8       /* control type: numeric, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK FileOpen(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif