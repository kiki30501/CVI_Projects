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
#define  PANEL_TABLE                      2       /* control type: table, callback function: (none) */
#define  PANEL_COMMANDBUTTON              3       /* control type: command, callback function: quit */
#define  PANEL_TABLE_3                    4       /* control type: table, callback function: (none) */
#define  PANEL_TABLE_2                    5       /* control type: table, callback function: (none) */
#define  PANEL_CALCX                      6       /* control type: command, callback function: calc */
#define  PANEL_CALCB                      7       /* control type: command, callback function: calc */
#define  PANEL_TEXTMSG                    8       /* control type: textMsg, callback function: (none) */
#define  PANEL_Print                      9       /* control type: command, callback function: Print */
#define  PANEL_TAB                        10      /* control type: tab, callback function: (none) */
#define  PANEL_TEXTMSG_2                  11      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

#define  CTRLARRAY                        1

     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK calc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Print(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK quit(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
