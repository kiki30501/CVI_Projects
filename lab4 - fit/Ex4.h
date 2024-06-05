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
#define  PANEL_fit_button                 2       /* control type: command, callback function: fit_button */
#define  PANEL_QUITBUTTON                 3       /* control type: command, callback function: QuitCallback */
#define  PANEL_clear_button               4       /* control type: command, callback function: clear_button */
#define  PANEL_load_button                5       /* control type: command, callback function: load_button */
#define  PANEL_TAB                        6       /* control type: tab, callback function: (none) */

     /* tab page panel controls */
#define  exp_e_num                        2       /* control type: numeric, callback function: (none) */
#define  exp_d_num                        3       /* control type: numeric, callback function: (none) */
#define  exp_a_num                        4       /* control type: numeric, callback function: (none) */
#define  exp_GRAPH                        5       /* control type: graph, callback function: (none) */

     /* tab page panel controls */
#define  lin_e_num                        2       /* control type: numeric, callback function: (none) */
#define  lin_i_num                        3       /* control type: numeric, callback function: (none) */
#define  lin_s_num                        4       /* control type: numeric, callback function: (none) */
#define  lin_GRAPH                        5       /* control type: graph, callback function: (none) */

     /* tab page panel controls */
#define  poly_e_num                       2       /* control type: numeric, callback function: (none) */
#define  poly_c_num_0                     3       /* control type: numeric, callback function: (none) */
#define  poly_c_num_7                     4       /* control type: numeric, callback function: (none) */
#define  poly_c_num_6                     5       /* control type: numeric, callback function: (none) */
#define  poly_c_num_5                     6       /* control type: numeric, callback function: (none) */
#define  poly_c_num_4                     7       /* control type: numeric, callback function: (none) */
#define  poly_c_num_3                     8       /* control type: numeric, callback function: (none) */
#define  poly_c_num_2                     9       /* control type: numeric, callback function: (none) */
#define  poly_c_num_1                     10      /* control type: numeric, callback function: (none) */
#define  poly_GRAPH                       11      /* control type: graph, callback function: (none) */
#define  poly_o_num                       12      /* control type: numeric, callback function: (none) */


     /* Control Arrays: */

#define  CTRLARRAY                        1

     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK clear_button(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fit_button(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK load_button(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif