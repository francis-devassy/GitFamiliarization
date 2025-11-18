//**************************** PROJECT GitFamiliarization *********************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File    : main.c
// Summary : Program to prints the message Hello World and System Time
// Note    : Program to prints the message Hello World and System Time
// Author  : Francis V D
// Date    : 13-11-2025
//
//*****************************************************************************
//******************************* Include Files *******************************
#ifdef _WIN32
#include <windows.h>
#define SLEEP(seconds) Sleep((seconds) * MS_PER_SECOND)   
#else
#include <unistd.h>
#define SLEEP(seconds) sleep(seconds)                     
#endif
#include <stdio.h>
#include <time.h>
#include "appTimer.h"
#include "customTypes.h"

//******************************* Local Types *********************************

//***************************** Local Constants *******************************
#define OFFSET_HOURS_IST        (5)
#define OFFSET_MINUTES_IST      (30)
#define OFFSET_HOURS_PST        (-8)
#define OFFSET_MINUTES_PST      (0)
#define WAIT_TIME               (1)
#define MS_PER_SECOND           (1000)
#define LABEL_IST                     "IST (+5:30)"
#define LABEL_PST                     "PST (-8:00)"

//***************************** Local Variables *******************************

//****************************** Local Functions ******************************

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Main function print Hello World and System Time
//Inputs  : None
//Outputs : None
//Return  : return 0 at time of successfull execution
//Notes   : Main function print Hello World and System Time
//******************************************************************************
int main(void) 
{
    time_t lRawTime = 0;
	bool blLedStatus = false;
    printf(" Hello, World!\n");

    while (1) 
    {
        //Toggle and display LED status every 1 second
		blLedStatus = DisplayToggledLedStatus(blLedStatus);

		time(&lRawTime); 
        // Print time
        appTimerPrintUtcTime(lRawTime);        
        appTimerPrintTimeZone(lRawTime, OFFSET_HOURS_IST, OFFSET_MINUTES_IST, 
                              (const uint8*)LABEL_IST);        
        appTimerPrintTimeZone(lRawTime, OFFSET_HOURS_PST, OFFSET_MINUTES_PST, 
                              (const uint8*)LABEL_PST);
        // Refresh every second
        SLEEP(WAIT_TIME); 
    }
    return 0;
}
// EOF 