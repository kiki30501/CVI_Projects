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
#define  PANEL_LED_0                      3       /* control type: LED, callback function: Digital_Leds */
#define  PANEL_LED_6                      4       /* control type: LED, callback function: Digital_Leds */
#define  PANEL_LED_5                      5       /* control type: LED, callback function: Digital_Leds */
#define  PANEL_LED_4                      6       /* control type: LED, callback function: Digital_Leds */
#define  PANEL_LED_3                      7       /* control type: LED, callback function: Digital_Leds */
#define  PANEL_LED_2                      8       /* control type: LED, callback function: Digital_Leds */
#define  PANEL_LED_1                      9       /* control type: LED, callback function: Digital_Leds */
#define  PANEL_LED_7                      10      /* control type: LED, callback function: Digital_Leds */
#define  PANEL_TEXT_0                     11      /* control type: textMsg, callback function: (none) */
#define  PANEL_DIN_0                      12      /* control type: radioButton, callback function: Digital_Buttons */
#define  PANEL_DIN_1                      13      /* control type: radioButton, callback function: Digital_Buttons */
#define  PANEL_DIN_2                      14      /* control type: radioButton, callback function: Digital_Buttons */
#define  PANEL_DIN_3                      15      /* control type: radioButton, callback function: Digital_Buttons */
#define  PANEL_DIN_4                      16      /* control type: radioButton, callback function: Digital_Buttons */
#define  PANEL_DIN_5                      17      /* control type: radioButton, callback function: Digital_Buttons */
#define  PANEL_DIN_6                      18      /* control type: radioButton, callback function: Digital_Buttons */
#define  PANEL_DIN_7                      19      /* control type: radioButton, callback function: Digital_Buttons */
#define  PANEL_ANALOG_OUT_0               20      /* control type: numeric, callback function: Analog_Numerics */
#define  PANEL_ANALOG_OUT_1               21      /* control type: numeric, callback function: Analog_Numerics */
#define  PANEL_ANALOG_IN_0                22      /* control type: scale, callback function: Analog_Knobs */
#define  PANEL_ANALOG_IN_1                23      /* control type: scale, callback function: Analog_Knobs */
#define  PANEL_CONNECT                    24      /* control type: command, callback function: Connect_COM */
#define  PANEL_TesterCOM                  25      /* control type: numeric, callback function: (none) */
#define  PANEL_TEXT_2                     26      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

#define  Analog_knob_array                1
#define  Analog_numeric_array             2
#define  Digital_button_array             3
#define  Led_array                        4

     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Analog_Knobs(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Analog_Numerics(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Connect_COM(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Digital_Buttons(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Digital_Leds(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif