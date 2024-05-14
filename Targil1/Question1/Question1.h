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

#define  Question1                        1
#define  Question1_HELLO                  2       /* control type: string, callback function: (none) */
#define  Question1_QUIT                   3       /* control type: command, callback function: MyQuit */
#define  Question1_PrintString            4       /* control type: command, callback function: MyTextPrint */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK MyQuit(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MyTextPrint(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif