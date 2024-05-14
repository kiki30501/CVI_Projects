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
#define  PANEL_QUIT                       2       /* control type: command, callback function: MyQuit */
#define  PANEL_Result_box                 3       /* control type: numeric, callback function: (none) */
#define  PANEL_Input_box2                 4       /* control type: numeric, callback function: (none) */
#define  PANEL_Input_box1                 5       /* control type: numeric, callback function: (none) */
#define  PANEL_Btimes                     6       /* control type: command, callback function: MyArithButtons */
#define  PANEL_Bminus                     7       /* control type: command, callback function: MyArithButtons */
#define  PANEL_Bdivide                    8       /* control type: command, callback function: MyArithButtons */
#define  PANEL_Bplus                      9       /* control type: command, callback function: MyArithButtons */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK MyArithButtons(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MyQuit(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif