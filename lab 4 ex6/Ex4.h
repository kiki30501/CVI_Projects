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

#define  Graphs                           1
#define  Graphs_GRAPH                     2       /* control type: graph, callback function: (none) */
#define  Graphs_FFTGRAPH                  3       /* control type: graph, callback function: (none) */
#define  Graphs_quit_graph_button         4       /* control type: command, callback function: quit_graph_button */

#define  PANEL                            2
#define  PANEL_Gauge                      2       /* control type: scale, callback function: (none) */
#define  PANEL_length_num                 3       /* control type: numeric, callback function: (none) */
#define  PANEL_dt_num                     4       /* control type: numeric, callback function: (none) */
#define  PANEL_mass_num                   5       /* control type: numeric, callback function: (none) */
#define  PANEL_QUITBUTTON                 6       /* control type: command, callback function: QuitCallback */
#define  PANEL_graph_button               7       /* control type: command, callback function: graph_button */
#define  PANEL_timeShow                   8       /* control type: numeric, callback function: (none) */
#define  PANEL_TIMER                      9       /* control type: timer, callback function: timer */
#define  PANEL_start_button               10      /* control type: textButton, callback function: start_func */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK graph_button(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK quit_graph_button(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK start_func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK timer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
