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
#define  PANEL_TAB_GRAPHS                 3       /* control type: tab, callback function: (none) */
#define  PANEL_NUMERIC_BPM                4       /* control type: numeric, callback function: (none) */
#define  PANEL_BTN_CONNECT_MONITOR        5       /* control type: command, callback function: connect_monitor_com */
#define  PANEL_NUMERIC_COM_MONITOR        6       /* control type: numeric, callback function: (none) */
#define  PANEL_DECORATION_2               7       /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION_3               8       /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION                 9       /* control type: deco, callback function: (none) */
#define  PANEL_BTN_PAUSE                  10      /* control type: pictButton, callback function: graph_run_stop */
#define  PANEL_BTN_PLAY                   11      /* control type: pictButton, callback function: graph_run_stop */
#define  PANEL_TIMER_PLOTS                12      /* control type: timer, callback function: monitor_timer_func */

#define  PANEL_EMUL                       2
#define  PANEL_EMUL_QUITBUTTON            2       /* control type: command, callback function: QuitCallback */
#define  PANEL_EMUL_NUMERIC_COM_EMULATOR  3       /* control type: numeric, callback function: (none) */
#define  PANEL_EMUL_DECORATION_2          4       /* control type: deco, callback function: (none) */
#define  PANEL_EMUL_DECORATION            5       /* control type: deco, callback function: (none) */
#define  PANEL_EMUL_BTN_DISCONNECT_EMUL   6       /* control type: command, callback function: emulator_com_control */
#define  PANEL_EMUL_BTN_EMUL_FILE         7       /* control type: command, callback function: emulator_file_open */
#define  PANEL_EMUL_BTN_CONNECT_EMUL      8       /* control type: command, callback function: emulator_com_control */
#define  PANEL_EMUL_BTN_PAUSE_EMUL        9       /* control type: pictButton, callback function: emul_run_stop */
#define  PANEL_EMUL_BTN_PLAY_EMUL         10      /* control type: pictButton, callback function: emul_run_stop */
#define  PANEL_EMUL_TIMER_EMULATOR        11      /* control type: timer, callback function: emulator_timer_func */
#define  PANEL_EMUL_STRING                12      /* control type: string, callback function: (none) */

     /* tab page panel controls */
#define  TAB_MONITO_GRAPH_MONITOR         2       /* control type: strip, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_MENU_DIAG                2
#define  MENUBAR_MENU_DIAG_ITEM_TESTER    3       /* callback function: open_tester_panel */
#define  MENUBAR_MENU_ABOUT               4       /* callback function: open_about_panel */


     /* Callback Prototypes: */

int  CVICALLBACK connect_monitor_com(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK emul_run_stop(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK emulator_com_control(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK emulator_file_open(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK emulator_timer_func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK graph_run_stop(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK monitor_timer_func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK open_about_panel(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK open_tester_panel(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif