#include <ansi_c.h>
#include <utility.h>
#include <cvirte.h>     
#include <userint.h>
#include <rs232.h>
#include <string.h>

#include "heart_monitor_v1.h"
#include "wav_handling.h"

/*=============================================================================================*/

/*  The frequency range of the heart rate and the BPF.
    These values were obtained from Application Note 223 By BIOPAC Systems, Inc.*/
#define FREQ_MIN    0.5     // 30 bpm
#define FREQ_MAX    35.0    // 2100 bpm


/*=============================================================================================*/

static int panelHandle_main, panelHandle_emul, panelHandle_about;
static int handle_dimmed_main, handle_dimmed_emul;
int Err;
int com_port_monitor = 3;
int com_port_emulator = 4;
char recv_buff[2];
wav_file emulator_wav;
FILE *fp;
/*=============================================================================================*/

int main (int argc, char *argv[])
{
    if (InitCVIRTE (0, argv, 0) == 0)
        return -1;  /* out of memory */
    if ((panelHandle_main  = LoadPanel (0, "heart_monitor_v1.uir", PANEL_MAIN)) < 0)
        return -1;
    if ((panelHandle_emul  = LoadPanel (0, "heart_monitor_v1.uir", PANEL_EMUL)) < 0)
        return -1;
    if ((panelHandle_about = LoadPanel (0, "heart_monitor_v1.uir", PNL_ABOUT))  < 0)
        return -1;

    handle_dimmed_main = GetCtrlArrayFromResourceID (panelHandle_main, DIMMED_MAIN);
    handle_dimmed_emul = GetCtrlArrayFromResourceID (panelHandle_emul, DIMMED_EMUL);

    DisplayPanel (panelHandle_main);
    RunUserInterface ();

    free_wav_data(emulator_wav);
    CloseCom(com_port_monitor);
    CloseCom(com_port_emulator);
    DiscardPanel (panelHandle_main);
    DiscardPanel (panelHandle_emul);
    
    return 0;
}

/*=============================================================================================*/

int CVICALLBACK QuitCallback (int panel, int control, int event,
                              void *callbackData, int eventData1, int eventData2)
{
    switch (event)
    {
        case EVENT_COMMIT:
            QuitUserInterface (0);
            break;
    }
    return 0;
}

/*=============================================================================================*/

int CVICALLBACK com_control (int panel, int control, int event,
                                     void *callbackData, int eventData1, int eventData2)
{
    char ctrl_label[20];
    int *com_device, numeric, ctrl_array;
        
    switch (event)
    {
        case EVENT_COMMIT:

            if (panel == panelHandle_main)
            {
                com_device = &com_port_monitor;
                numeric = PANEL_MAIN_NUMERIC_COM_MONITOR;
                ctrl_array = handle_dimmed_main;
            }
            else
            {
                com_device = &com_port_emulator;
                numeric = PANEL_EMUL_NUMERIC_COM_EMULATOR;
                ctrl_array = handle_dimmed_emul;
            }

            GetCtrlAttribute (panel, control, ATTR_LABEL_TEXT, ctrl_label);
            if (!strcmp(ctrl_label, "Disconnect"))
            {   // if the button is labeled "Disconnect" then:
                CloseCom (*com_device);
                SetCtrlArrayAttribute (ctrl_array, ATTR_DIMMED, 1);
                SetCtrlAttribute (panel, numeric, ATTR_TEXT_BGCOLOR, VAL_WHITE);
            }
            else
            {   // if the button is NOT labeled "Disconnect" then:
                GetCtrlVal (panel, numeric, com_device);
                if ((Err = OpenComConfig (*com_device, "", 115200, 1, 8, 1, 512, 512)) < 0)
                    return Err;
                if ((Err = InstallComCallback (*com_device, LWRS_RXFLAG, 0, 0, 0, 0)) < 0)
                    return Err;
                SetCtrlArrayAttribute (ctrl_array, ATTR_DIMMED, 0);
                SetCtrlAttribute (panel, numeric, ATTR_TEXT_BGCOLOR, VAL_GREEN);
            }
            break;
    }
    return 0;
}

/*=============================================================================================*/

int CVICALLBACK timer_toggle (int panel, int control, int event,
                                void *callbackData, int eventData1, int eventData2)
{
    int timer, ena;

    switch (event)
    {
        case EVENT_COMMIT:
            timer = (panel == panelHandle_main) ? PANEL_MAIN_TIMER : PANEL_EMUL_TIMER;
            GetCtrlVal (panel, control, &ena);
            SetCtrlAttribute (panel, timer, ATTR_ENABLED, ena);
            break;
    }
    return 0;
}

/*=============================================================================================*/

int CVICALLBACK monitor_timer_func (int panel, int control, int event,
                                    void *callbackData, int eventData1, int eventData2)
{
    switch (event)
    {
        case EVENT_TIMER_TICK:
            // SingleToneInfo (, , , , , , );
            // 
            break;
    }
    return 0;
}

/*=============================================================================================*/

int CVICALLBACK emulator_timer_func (int panel, int control, int event,
                                     void *callbackData, int eventData1, int eventData2)
{
    static int i;
    char send_buff[2];
    switch (event)
    {
        case EVENT_TIMER_TICK:
            int k = i % emulator_wav.header.subchunk2_size.int_value;
            memcpy(send_buff, emulator_wav.data[k].short_bytes, sizeof(short));
            ComWrt (com_port_emulator, send_buff, sizeof(short));
            i++;
            break;
    }
    return 0;
}

/*=============================================================================================*/

int CVICALLBACK emulator_file_open (int panel, int control, int event,
                                    void *callbackData, int eventData1, int eventData2)
{
    char path[MAX_PATHNAME_LEN];
    
    switch (event)
    {
        case EVENT_COMMIT:
            FileSelectPopupEx ("", "*.wav", "*.wav", "Select test source waveform", VAL_LOAD_BUTTON, 0, 1, path);
            FILE *fp = fopen(path, "rb");
            if (fp == NULL)
            {
                MessagePopup ("Error", "Could not open file");
                return -1;
            }
            emulator_wav = get_wav_from_file(fp, get_wav_header_from_file(fp));
            double temp = 1.0/(double)(emulator_wav.header.byte_rate.int_value);
            SetCtrlAttribute (panel, PANEL_EMUL_TIMER, ATTR_INTERVAL, temp);
            
            fclose(fp);
            break;
    }
    return 0;
}

/*=============================================================================================*/

void CVICALLBACK open_tester_panel (int menuBar, int menuItem, void *callbackData,
                                    int panel)
{
    DisplayPanel (panelHandle_emul);
}

/*=============================================================================================*/

void CVICALLBACK open_about_panel (int menuBar, int menuItem, void *callbackData,
                                   int panel)
{
    DisplayPanel (panelHandle_about);
}

/*=============================================================================================*/

int CVICALLBACK quit_panel (int panel, int control, int event,
                            void *callbackData, int eventData1, int eventData2)
{
    switch (event)
    {
        case EVENT_COMMIT:
            HidePanel(panel);
            break;
    }
    return 0;
}
