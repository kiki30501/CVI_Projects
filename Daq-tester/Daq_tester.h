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
#define  PANEL_LED_0                      3       /* control type: LED, callback function: (none) */
#define  PANEL_LED_6                      4       /* control type: LED, callback function: (none) */
#define  PANEL_LED_5                      5       /* control type: LED, callback function: (none) */
#define  PANEL_LED_4                      6       /* control type: LED, callback function: (none) */
#define  PANEL_LED_3                      7       /* control type: LED, callback function: (none) */
#define  PANEL_LED_2                      8       /* control type: LED, callback function: (none) */
#define  PANEL_LED_1                      9       /* control type: LED, callback function: (none) */
#define  PANEL_LED_7                      10      /* control type: LED, callback function: (none) */
#define  PANEL_DIN_0                      11      /* control type: radioButton, callback function: cmnd_digital_out */
#define  PANEL_DIN_1                      12      /* control type: radioButton, callback function: cmnd_digital_out */
#define  PANEL_DIN_2                      13      /* control type: radioButton, callback function: cmnd_digital_out */
#define  PANEL_DIN_3                      14      /* control type: radioButton, callback function: cmnd_digital_out */
#define  PANEL_DIN_4                      15      /* control type: radioButton, callback function: cmnd_digital_out */
#define  PANEL_DIN_5                      16      /* control type: radioButton, callback function: cmnd_digital_out */
#define  PANEL_DIN_6                      17      /* control type: radioButton, callback function: cmnd_digital_out */
#define  PANEL_DIN_7                      18      /* control type: radioButton, callback function: cmnd_digital_out */
#define  PANEL_ANALOG_IN_0                19      /* control type: numeric, callback function: (none) */
#define  PANEL_ANALOG_IN_1                20      /* control type: numeric, callback function: (none) */
#define  PANEL_ANALOG_OUT_0               21      /* control type: scale, callback function: cmnd_analog_out */
#define  PANEL_ANALOG_OUT_1               22      /* control type: scale, callback function: cmnd_analog_out */
#define  PANEL_CONNECT                    23      /* control type: command, callback function: Connect_COM */
#define  PANEL_TesterCOM                  24      /* control type: numeric, callback function: (none) */
#define  PANEL_TEXT_0                     25      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXT_2                     26      /* control type: textMsg, callback function: (none) */
#define  PANEL_TIMER                      27      /* control type: timer, callback function: refresh_timer */


     /* Control Arrays: */

#define  Digital_button_array             1
#define  Led_array                        2

     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK cmnd_analog_out(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK cmnd_digital_out(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Connect_COM(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK refresh_timer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif