#include <advanlys.h>
#include <ansi_c.h>
#include <utility.h>
#include <cvirte.h>     
#include <userint.h>
#include <rs232.h>
#include <string.h>
#include <math.h>

#include "heart_monitor_v1.h"
#include "wav_handling.h"

/*=============================================================================================*/

/*  The frequency range of the heart rate and the BPF.
    These values were obtained from Application Note 223 By BIOPAC Systems, Inc.*/
#define FREQ_MIN    0.7
#define FREQ_MAX    35.0
#define FILTER_LEN	8000
#define NUM_COEFF	10


/*=============================================================================================*/

static int panelHandle_main, panelHandle_emul, panelHandle_about;
static int handle_tab_monitor, handle_tab_bpm;
static int handle_dimmed_main, handle_dimmed_emul, handle_dimmed_emul_2;
static int threadFunctionId_run;
int Err, exiting;
int run_emulator_thread, run_main_thread, run_read_thread;
int com_port_monitor = 3;
int com_port_emulator = 4;
char recv_buff[2];
double Ts = 250e-6; // default value = 1/4000 seconds
int    Fs = 4000;   // default value = 4000Hz
double coeff[FILTER_LEN];
double * monitor_waveform;
double * filtered_waveform;
int time_window_size = 8000; // size of time window = 2 seconds * Byte rate; default value = 4000*2=8000
double WF_gain = 1.0;

wav_file emulator_wav;
FILE *fp;

static int CVICALLBACK read_from_com (void *functionData);
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
    
    GetPanelHandleFromTabPage (panelHandle_main, PANEL_MAIN_TAB_GRAPHS, 0, &handle_tab_monitor);
    GetPanelHandleFromTabPage (panelHandle_main, PANEL_MAIN_TAB_GRAPHS, 1, &handle_tab_bpm);
    
    handle_dimmed_main = GetCtrlArrayFromResourceID   (panelHandle_main, DIMMED_MAIN);
    handle_dimmed_emul = GetCtrlArrayFromResourceID   (panelHandle_emul, DIMMED_EMUL);
    handle_dimmed_emul_2 = GetCtrlArrayFromResourceID (panelHandle_emul, DIMMED_EMUL_2);
    
    monitor_waveform =  (double *) malloc (time_window_size * sizeof(double));
    filtered_waveform = (double *) malloc (FILTER_LEN * sizeof(double));
	

    run_read_thread = 1;
    CmtScheduleThreadPoolFunction (DEFAULT_THREAD_POOL_HANDLE,
                        read_from_com, NULL, &threadFunctionId_run);
	
	
    DisplayPanel (panelHandle_main);
    RunUserInterface ();

    CmtWaitForThreadPoolFunctionCompletion (DEFAULT_THREAD_POOL_HANDLE, threadFunctionId_run,
                                                OPT_TP_PROCESS_EVENTS_WHILE_WAITING);
    CmtReleaseThreadPoolFunctionID (DEFAULT_THREAD_POOL_HANDLE, threadFunctionId_run);
    
    // At the end of the program finish\close\free everything.
    free(monitor_waveform);
    free(filtered_waveform);
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
            run_read_thread = 0;
			run_main_thread = 0;
			run_emulator_thread = 0;
            
            QuitUserInterface (0);
            break;
    }
    return 0;
}

/*=============================================================================================*/
int CVICALLBACK update_wf_gain (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
            GetCtrlVal (panel, control, &WF_gain);
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
                SetCtrlVal (panel, PANEL_EMUL_TOGGLE_EMUL, 0);
                run_emulator_thread = 0;
                CloseCom (*com_device);
                SetCtrlArrayAttribute (ctrl_array, ATTR_DIMMED, 1);
                SetCtrlArrayAttribute (handle_dimmed_emul_2, ATTR_DIMMED, 1);
                SetCtrlAttribute (panel, numeric, ATTR_TEXT_BGCOLOR, VAL_WHITE);
                SetCtrlVal (panel, PANEL_EMUL_DURATION, "--:--:--");
            }
            else
            {   // if the button is NOT labeled "Disconnect" then:
                GetCtrlVal (panel, numeric, com_device);
                if ((Err = OpenComConfig (*com_device, "", 115200, 1, 8, 1, 512, 512)) < 0)
                    return Err;
                if ((Err = InstallComCallback (*com_device, LWRS_RECEIVE, 2, 0, 0, 0)) < 0)
                    return Err;
                SetCtrlArrayAttribute (ctrl_array, ATTR_DIMMED, 0);
                SetCtrlAttribute (panel, numeric, ATTR_TEXT_BGCOLOR, VAL_GREEN);
            }
            break;
    }
    return 0;
}

/*=============================================================================================*/

int CVICALLBACK emulator_file_open (int panel, int control, int event,
                                    void *callbackData, int eventData1, int eventData2)
{
    char path[MAX_PATHNAME_LEN];
    int duration_file = 0;
    char duration_file_string[10];
    static int flag = 0;
    switch (event)
    {
        case EVENT_COMMIT:
            if (flag == 1)
                free_wav_data(emulator_wav);
            SetCtrlVal (panel, PANEL_EMUL_TOGGLE_EMUL, 0);
            //SetCtrlVal (panel, PANEL_MAIN_TOGGLE_MAIN, 0);
            
            FileSelectPopupEx ("", "*.wav", "*.wav", "Select test source waveform", VAL_LOAD_BUTTON, 0, 1, path);
            if (path[1] != ':')
            {
                MessagePopup ("Error", "Bad path");
                return -1;
            }    
            FILE *fp = fopen(path, "rb");
            if (fp == NULL)
            {
                MessagePopup ("Error", "Could not open file");
                return -1;
            }
            // Read the wav file
            emulator_wav = get_wav_from_file(fp, get_wav_header_from_file(fp));
            Fs = emulator_wav.header.sample_rate.int_value;
            time_window_size = 2 * Fs;
            flag = 1;
            // Set the timer interval to the sample rate of the wav
            Ts = 1.0/(double)(Fs);
            // Set the duration of the file in seconds
            duration_file = emulator_wav.header.subchunk2_size.int_value / emulator_wav.header.byte_rate.int_value;
            sprintf(duration_file_string, "%02d:%02d:%02d", duration_file/3600, (duration_file%3600)/60, duration_file%60);
            SetCtrlVal (panel, PANEL_EMUL_DURATION, duration_file_string);
            SetCtrlArrayAttribute (handle_dimmed_emul_2, ATTR_DIMMED, 0);
            
            monitor_waveform = (double *) realloc (monitor_waveform, time_window_size * sizeof(double));
            memset (monitor_waveform, 0, time_window_size);
            filtered_waveform = (double *) realloc (filtered_waveform, FILTER_LEN * sizeof(double));
            memset (filtered_waveform, 0, FILTER_LEN * sizeof(double));
            
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

/*=============================================================================================*/

// Functions to be executed in multi-threaded operation: //

/*=============================================================================================*/

static int CVICALLBACK emulator_tick (void *functionData)
{
    //static int i;
	int i;
    int k;
    char send_buff[2];
	int end = emulator_wav.header.subchunk2_size.int_value;
    for (i=0; run_emulator_thread ; i++)
        {
        k = i % end;
        memcpy(send_buff, emulator_wav.data[k].short_bytes, sizeof(short));
        ComWrt (com_port_emulator, send_buff, sizeof(short));
        Delay(Ts);
        }
	//SetCtrlVal (panelHandle_emul, PANEL_EMUL_TOGGLE_EMUL, 0);
	//run_emulator_thread = 0;
    return 0;
}

/*=============================================================================================*/
int CVICALLBACK toggle_emulator (int panel, int control, int event,
        void *callbackData, int eventData1, int eventData2)
{
    static int threadFunctionId = 0;
    switch (event)
        {
        case EVENT_VAL_CHANGED:
            GetCtrlVal (panel, control, &run_emulator_thread);
            
            if(run_emulator_thread)
            {
                threadFunctionId = 0;
                CmtScheduleThreadPoolFunction (DEFAULT_THREAD_POOL_HANDLE,
                                    emulator_tick, NULL, &threadFunctionId);
            }
            else
            {
                CmtWaitForThreadPoolFunctionCompletion (DEFAULT_THREAD_POOL_HANDLE,
                                                threadFunctionId,
                                                OPT_TP_PROCESS_EVENTS_WHILE_WAITING);
                CmtReleaseThreadPoolFunctionID (DEFAULT_THREAD_POOL_HANDLE, threadFunctionId);
            }
            break;
        }
    return 0;
}

/*=============================================================================================*/
static int CVICALLBACK read_from_com (void *functionData)
{
    short temp;
	while(run_read_thread)
    {
        if((Q = GetInQLen(com_port_monitor)) >= 2)
	            ComRd (com_port_monitor, recv_buff, sizeof(short));
	        else
	            memset(recv_buff, 0, sizeof(short));
	        memcpy (&temp, recv_buff, 2);
	        Shift (monitor_waveform, time_window_size, -1, monitor_waveform);
	            
	        monitor_waveform[time_window_size - 1] = (double)(temp);

	        // Apply the band pass filter
			WindFIR_Filtering ((&monitor_waveform[time_window_size - (FILTER_LEN - NUM_COEFF-1)]), (FILTER_LEN - NUM_COEFF-1), NUM_COEFF, BANDPASS, Fs, FREQ_MIN, FREQ_MAX, HAMMING____, 0.0,
						   filtered_waveform);
    }
	return 0;
}

/*=============================================================================================*/
static int CVICALLBACK monitor_graph_tick (void *functionData)
{
    static int m;
    int n;
    int Q;
    short temp;
    memset (monitor_waveform, 0, sizeof(monitor_waveform));
    for (m=0; run_main_thread; m++)
        {
	        // n = (m < time_window_size) ? m : time_window_size - 1;
	        // if((Q = GetInQLen(com_port_monitor)) >= 2)
	        //     ComRd (com_port_monitor, recv_buff, sizeof(short));
	        // else
	        //     memset(recv_buff, 0, sizeof(short));
	        // memcpy (&temp, recv_buff, 2);
	        
	        // Shift (monitor_waveform, time_window_size, -1, monitor_waveform);
	            
	        // monitor_waveform[time_window_size - 1] = (double)(temp);

	        // // Apply the band pass filter
			// WindFIR_Filtering ((&monitor_waveform[time_window_size - (FILTER_LEN - NUM_COEFF-1)]), (FILTER_LEN - NUM_COEFF-1), NUM_COEFF, BANDPASS, Fs, FREQ_MIN, FREQ_MAX, HAMMING____, 0.0,
			// 			   filtered_waveform);
			
			PlotStripChartPoint (handle_tab_monitor, TAB_MONITO_STRIPCHART, WF_gain * filtered_waveform[FILTER_LEN - NUM_COEFF-1]);
	        Delay(Ts);
        }
    return 0;
}

/*=============================================================================================*/
static int CVICALLBACK bpm_graph_tick (void *functionData)
{
    
    /*for (int i=0; i<time_window_size; i++)
        {// SingleToneInfo (, , , , , , );
        
        }*/
    double bpm, phase, amp;
    while (run_main_thread)
    {
        SearchType freq_search;
        freq_search.centerFrequency = (FREQ_MIN + FREQ_MAX)/2.0;
        freq_search.frequencyWidth  = FREQ_MAX - FREQ_MIN;
		//Bw_BPF (Convolve (coef, FILTER_LEN, (monitor_waveform + time_window_size - FILTER_LEN), time_window_size - FILTER_LEN, filtered_waveform), FILTER_LEN, Fs, FREQ_MIN, FREQ_MAX, NUM_COEFF, filtered_waveform);
		//Convolve (coeff, FILTER_LEN, (monitor_waveform + time_window_size - FILTER_LEN), FILTER_LEN, filtered_waveform);
		/*WindFIR_Filtering ((&monitor_waveform[time_window_size - (FILTER_LEN - NUM_COEFF-1)]), (FILTER_LEN - NUM_COEFF-1), NUM_COEFF, BANDPASS, Fs, FREQ_MIN, FREQ_MAX, HAMMING____, 0.0,
						   filtered_waveform);*/
		
        SingleToneInfo (filtered_waveform, FILTER_LEN, Ts, &freq_search, &bpm, &amp, &phase);
		//SingleToneInfo (filtered_waveform, FILTER_LEN, Ts, NULL, &bpm, &amp, &phase);
        SetCtrlVal (panelHandle_main, PANEL_MAIN_NUMERIC_BPM, bpm);
        Delay(1.0);
    }
    return 0;
}

/*=============================================================================================*/
int CVICALLBACK toggle_monitor (int panel, int control, int event,
        void *callbackData, int eventData1, int eventData2)
{
    static int threadFunctionId_A, threadFunctionId_B;
    switch (event)
        {
        case EVENT_VAL_CHANGED:
            GetCtrlVal (panel, control, &run_main_thread);
            
            if(run_main_thread)
            {
                threadFunctionId_A = 1;
                CmtScheduleThreadPoolFunction (DEFAULT_THREAD_POOL_HANDLE,
                                    monitor_graph_tick, NULL, &threadFunctionId_A);
                threadFunctionId_B = 2;
                CmtScheduleThreadPoolFunction (DEFAULT_THREAD_POOL_HANDLE,
                                    bpm_graph_tick, NULL, &threadFunctionId_B);
            }
            else
            {
                CmtWaitForThreadPoolFunctionCompletion (DEFAULT_THREAD_POOL_HANDLE,
                                                threadFunctionId_A,
                                                OPT_TP_PROCESS_EVENTS_WHILE_WAITING);
                CmtReleaseThreadPoolFunctionID (DEFAULT_THREAD_POOL_HANDLE, threadFunctionId_A);
                
                CmtWaitForThreadPoolFunctionCompletion (DEFAULT_THREAD_POOL_HANDLE,
                                                threadFunctionId_B,
                                                OPT_TP_PROCESS_EVENTS_WHILE_WAITING);
                CmtReleaseThreadPoolFunctionID (DEFAULT_THREAD_POOL_HANDLE, threadFunctionId_B);
            }
            break;
        }
    return 0;
}