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

#define  PANEL_EMUL                       1
#define  PANEL_EMUL_QUITBUTTON            2       /* control type: command, callback function: quit_panel */
#define  PANEL_EMUL_NUMERIC_COM_EMULATOR  3       /* control type: numeric, callback function: (none) */
#define  PANEL_EMUL_DECORATION_2          4       /* control type: deco, callback function: (none) */
#define  PANEL_EMUL_DECORATION            5       /* control type: deco, callback function: (none) */
#define  PANEL_EMUL_BTN_DISCONNECT_EMUL   6       /* control type: command, callback function: com_control */
#define  PANEL_EMUL_BTN_EMUL_FILE         7       /* control type: command, callback function: emulator_file_open */
#define  PANEL_EMUL_BTN_CONNECT_EMUL      8       /* control type: command, callback function: com_control */
#define  PANEL_EMUL_TOGGLE_EMUL           9       /* control type: binary, callback function: toggle_emulator */
#define  PANEL_EMUL_DURATION              10      /* control type: string, callback function: (none) */

#define  PANEL_MAIN                       2
#define  PANEL_MAIN_QUITBUTTON            2       /* control type: command, callback function: QuitCallback */
#define  PANEL_MAIN_TAB_GRAPHS            3       /* control type: tab, callback function: (none) */
#define  PANEL_MAIN_NUMERIC_BPM           4       /* control type: numeric, callback function: (none) */
#define  PANEL_MAIN_BTN_CONNECT_MONITOR   5       /* control type: command, callback function: com_control */
#define  PANEL_MAIN_WF_GAIN               6       /* control type: numeric, callback function: update_wf_gain */
#define  PANEL_MAIN_NUMERIC_COM_MONITOR   7       /* control type: numeric, callback function: (none) */
#define  PANEL_MAIN_DECORATION_2          8       /* control type: deco, callback function: (none) */
#define  PANEL_MAIN_DECORATION_3          9       /* control type: deco, callback function: (none) */
#define  PANEL_MAIN_DECORATION            10      /* control type: deco, callback function: (none) */
#define  PANEL_MAIN_TOGGLE_MAIN           11      /* control type: binary, callback function: toggle_monitor */

#define  PNL_ABOUT                        3
#define  PNL_ABOUT_QUITBUTTON             2       /* control type: command, callback function: quit_panel */
#define  PNL_ABOUT_TEXTBOX                3       /* control type: textBox, callback function: (none) */

     /* tab page panel controls */
#define  TAB_BPM_GRAPH_BPM                2       /* control type: graph, callback function: (none) */

     /* tab page panel controls */
#define  TAB_MONITO_STRIPCHART            2       /* control type: strip, callback function: (none) */


     /* Control Arrays: */

#define  DIMMED_EMUL                      1
#define  DIMMED_EMUL_2                    2
#define  DIMMED_MAIN                      3

     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_MENU_DIAG                2
#define  MENUBAR_MENU_DIAG_ITEM_TESTER    3       /* callback function: open_tester_panel */
#define  MENUBAR_MENU_ABOUT               4       /* callback function: open_about_panel */


     /* Callback Prototypes: */

int  CVICALLBACK com_control(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK emulator_file_open(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK open_about_panel(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK open_tester_panel(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK quit_panel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK toggle_emulator(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK toggle_monitor(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK update_wf_gain(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif