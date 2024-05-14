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
#define  PANEL_BQUIT                      2       /* control type: command, callback function: MyQuit */
#define  PANEL_CalcDisplay                3       /* control type: string, callback function: (none) */
#define  PANEL_bdivide                    4       /* control type: command, callback function: MyActionButtons */
#define  PANEL_bequal                     5       /* control type: command, callback function: MyActionButtons */
#define  PANEL_bdel                       6       /* control type: command, callback function: MyActionButtons */
#define  PANEL_bclr                       7       /* control type: command, callback function: MyActionButtons */
#define  PANEL_bnum_0                     8       /* control type: command, callback function: MyNumButtons */
#define  PANEL_bnum_dot                   9       /* control type: command, callback function: MyNumButtons */
#define  PANEL_btimes                     10      /* control type: command, callback function: MyActionButtons */
#define  PANEL_bnum_9                     11      /* control type: command, callback function: MyNumButtons */
#define  PANEL_bnum_8                     12      /* control type: command, callback function: MyNumButtons */
#define  PANEL_bnum_7                     13      /* control type: command, callback function: MyNumButtons */
#define  PANEL_bminus                     14      /* control type: command, callback function: MyActionButtons */
#define  PANEL_bnum_6                     15      /* control type: command, callback function: MyNumButtons */
#define  PANEL_bnum_5                     16      /* control type: command, callback function: MyNumButtons */
#define  PANEL_bplus                      17      /* control type: command, callback function: MyActionButtons */
#define  PANEL_bnum_4                     18      /* control type: command, callback function: MyNumButtons */
#define  PANEL_bnum_3                     19      /* control type: command, callback function: MyNumButtons */
#define  PANEL_bnum_2                     20      /* control type: command, callback function: MyNumButtons */
#define  PANEL_bnum_1                     21      /* control type: command, callback function: MyNumButtons */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK MyActionButtons(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MyNumButtons(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MyQuit(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif