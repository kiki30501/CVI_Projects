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
#define  PANEL_V2                         3       /* control type: scale, callback function: (none) */
#define  PANEL_V1                         4       /* control type: scale, callback function: (none) */
#define  PANEL_I_SRC2                     5       /* control type: numeric, callback function: (none) */
#define  PANEL_C2                         6       /* control type: numeric, callback function: (none) */
#define  PANEL_I_SRC1                     7       /* control type: numeric, callback function: (none) */
#define  PANEL_C1                         8       /* control type: numeric, callback function: (none) */
#define  PANEL_RUN_TIMER                  9       /* control type: timer, callback function: RunCalculation */
#define  PANEL_R1                         10      /* control type: numeric, callback function: (none) */
#define  PANEL_MANUAL_DT                  11      /* control type: radioButton, callback function: (none) */
#define  PANEL_DT                         12      /* control type: numeric, callback function: (none) */
#define  PANEL_PIC_RESISTOR               13      /* control type: picture, callback function: (none) */
#define  PANEL_RESET_SIM                  14      /* control type: command, callback function: ResetSim */
#define  PANEL_GOB                        15      /* control type: command, callback function: StartSim */
#define  PANEL_STRING                     16      /* control type: string, callback function: (none) */

#define  PANEL_2                          2
#define  PANEL_2_GRAPH                    2       /* control type: graph, callback function: MyCursors */
#define  PANEL_2_close_graph_panel        3       /* control type: command, callback function: close_graph */
#define  PANEL_2_PLOTI_RES                4       /* control type: command, callback function: PlotNow */
#define  PANEL_2_PLOTVDIFF                5       /* control type: command, callback function: PlotNow */
#define  PANEL_2_PLOTV2                   6       /* control type: command, callback function: PlotNow */
#define  PANEL_2_PLOTV1                   7       /* control type: command, callback function: PlotNow */
#define  PANEL_2_LINLOGSWITCH             8       /* control type: binary, callback function: LinLogXAxis */
#define  PANEL_2_Cursor2_Y                9       /* control type: numeric, callback function: (none) */
#define  PANEL_2_Cursor1_Y                10      /* control type: numeric, callback function: (none) */
#define  PANEL_2_Cursor2_X                11      /* control type: numeric, callback function: (none) */
#define  PANEL_2_Cursor1_X                12      /* control type: numeric, callback function: (none) */
#define  PANEL_2_PlotSlope                13      /* control type: numeric, callback function: (none) */
#define  PANEL_2_TauDiff                  14      /* control type: numeric, callback function: (none) */
#define  PANEL_2_CalcTau                  15      /* control type: numeric, callback function: (none) */
#define  PANEL_2_Print2File               16      /* control type: command, callback function: FileSave */


     /* Control Arrays: */

#define  CTRLARRAY                        1

     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR1                         1
#define  MENUBAR1_MENU1                   2
#define  MENUBAR1_MENU1_B_open_graph      3       /* callback function: open_panel_graph */


     /* Callback Prototypes: */

int  CVICALLBACK close_graph(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK FileSave(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK LinLogXAxis(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MyCursors(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK open_panel_graph(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK PlotNow(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ResetSim(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RunCalculation(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StartSim(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif