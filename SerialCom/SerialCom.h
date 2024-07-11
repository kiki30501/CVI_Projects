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

#define  PANEL_Rx                         2
#define  PANEL_Rx_Rx_SelectPic            2       /* control type: command, callback function: RxSelectFile */
#define  PANEL_Rx_QUITBUTTON              3       /* control type: command, callback function: ClosePanelRx */
#define  PANEL_Rx_CANVAS                  4       /* control type: canvas, callback function: (none) */
#define  PANEL_Rx_LED                     5       /* control type: LED, callback function: (none) */

#define  PANEL_Tx                         3
#define  PANEL_Tx_QUITBUTTON              2       /* control type: command, callback function: ClosePanelTx */
#define  PANEL_Tx_Tx_SelectPic            3       /* control type: command, callback function: TxSelectFile */
#define  PANEL_Tx_SendButton              4       /* control type: command, callback function: SendBmp */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_MENU1                    2
#define  MENUBAR_MENU1_ITEM1              3
#define  MENUBAR_MENU1_ITEM1_SUBMENU      4
#define  MENUBAR_MENU1_ITEM1_ITEM2        5       /* callback function: RxPanel */
#define  MENUBAR_MENU1_ITEM1_ITEM3        6       /* callback function: TxPanel */


     /* Callback Prototypes: */

int  CVICALLBACK ClosePanelRx(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ClosePanelTx(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Config(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RecMode(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RecTimer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK RxPanel(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK RxSelectFile(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SendBmp(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SendNumeric(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SendString(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK TxPanel(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK TxSelectFile(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif