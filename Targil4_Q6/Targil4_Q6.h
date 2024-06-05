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
#define  PANEL_MyPendulum                 3       /* control type: scale, callback function: (none) */
#define  PANEL_B_GO                       4       /* control type: command, callback function: ToggleSimRun */
#define  PANEL_B_RST                      5       /* control type: command, callback function: SimReset */
#define  PANEL_TIMER                      6       /* control type: timer, callback function: RunSim */
#define  PANEL_MyLength                   7       /* control type: numeric, callback function: (none) */
#define  PANEL_MyMass                     8       /* control type: numeric, callback function: (none) */
#define  PANEL_CurrTime                   9       /* control type: numeric, callback function: (none) */
#define  PANEL_CtrlInterval               10      /* control type: numeric, callback function: (none) */

#define  PANEL_2                          2
#define  PANEL_2_GRAPH                    2       /* control type: graph, callback function: CursorGet */
#define  PANEL_2_QUITBUTTON               3       /* control type: command, callback function: HideGraphPanel */
#define  PANEL_2_CursorY2                 4       /* control type: numeric, callback function: (none) */
#define  PANEL_2_CursorX2                 5       /* control type: numeric, callback function: (none) */
#define  PANEL_2_CursorY1                 6       /* control type: numeric, callback function: (none) */
#define  PANEL_2_CursorX1                 7       /* control type: numeric, callback function: (none) */
#define  PANEL_2_TimePlot                 8       /* control type: command, callback function: MyPlots */
#define  PANEL_2_FFT                      9       /* control type: command, callback function: MyPlots */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_MENU1_2                  2
#define  MENUBAR_MENU1_2_MENU1            3       /* callback function: OpenGraphPanel */


     /* Callback Prototypes: */

int  CVICALLBACK CursorGet(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK HideGraphPanel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MyPlots(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK OpenGraphPanel(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RunSim(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SimReset(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ToggleSimRun(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif