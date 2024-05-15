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
#define  PANEL_C2                         5       /* control type: numeric, callback function: (none) */
#define  PANEL_C1                         6       /* control type: numeric, callback function: (none) */
#define  PANEL_RUN_TIMER                  7       /* control type: timer, callback function: RunCalculation */
#define  PANEL_R1                         8       /* control type: numeric, callback function: (none) */
#define  PANEL_MANUAL_DT                  9       /* control type: radioButton, callback function: (none) */
#define  PANEL_DT                         10      /* control type: numeric, callback function: (none) */
#define  PANEL_PIC_RESISTOR               11      /* control type: picture, callback function: (none) */
#define  PANEL_RESET_SIM                  12      /* control type: command, callback function: ResetSim */
#define  PANEL_GOB                        13      /* control type: command, callback function: StartSim */
#define  PANEL_STRING                     14      /* control type: string, callback function: (none) */


     /* Control Arrays: */

#define  CTRLARRAY                        1

     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ResetSim(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RunCalculation(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StartSim(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif