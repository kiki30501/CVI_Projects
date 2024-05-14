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
#define  PANEL_STRING_IN                  2       /* control type: string, callback function: (none) */
#define  PANEL_STRING_OUT                 3       /* control type: string, callback function: (none) */
#define  PANEL_QUIT                       4       /* control type: command, callback function: MyQuit */
#define  PANEL_B_COPY                     5       /* control type: command, callback function: MyCopy */
#define  PANEL_B_UP                       6       /* control type: command, callback function: MyUp */
#define  PANEL_B_LOW                      7       /* control type: command, callback function: MyLow */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK MyCopy(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MyLow(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MyQuit(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MyUp(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif