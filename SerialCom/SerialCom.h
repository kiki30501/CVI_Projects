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
#define  PANEL_SENDSTRING                 2       /* control type: string, callback function: SendString */
#define  PANEL_QUITBUTTON                 3       /* control type: command, callback function: QuitCallback */
#define  PANEL_CONFIG                     4       /* control type: command, callback function: Config */
#define  PANEL_RECIVER                    5       /* control type: textBox, callback function: (none) */
#define  PANEL_Q4_numeric                 6       /* control type: numeric, callback function: SendNumeric */
#define  PANEL_COM_Rx                     7       /* control type: numeric, callback function: (none) */
#define  PANEL_COM_Tx                     8       /* control type: numeric, callback function: (none) */
#define  PANEL_Parity_Toggle              9       /* control type: radioButton, callback function: (none) */
#define  PANEL_MODE_SELECT                10      /* control type: ring, callback function: RecMode */
#define  PANEL_TIMER                      11      /* control type: timer, callback function: RecTimer */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Config(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RecMode(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RecTimer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SendNumeric(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SendString(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif