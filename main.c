//**************************** PROJECT GitFamiliarization *********************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File    : main.c
// Summary : Program to print Hello World and System Time
// Note    : Program to print Hello World and System Time
// Author  : Francis V D
// Date    : 13-11-2025
//
//*****************************************************************************
//******************************* Include Files *******************************
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "appTimer.h"
#include "customTypes.h"

//******************************* Local Types *********************************

//***************************** Local Constants *******************************
#define RETURN_ZERO 0
#define OFFSET_HOURS_IST   5
#define OFFSET_MINUTES_IST 30
#define OFFSET_HOURS_PST  -8
#define OFFSET_MINUTES_PST 0
#define LABEL_IST "IST (+5:30)"
#define LABEL_PST "PST (-8:00)"
#define WAIT_TIME 1

//***************************** Local Variables *******************************

//****************************** Local Functions ******************************

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Main function print Hello World and System Time
//Inputs  : None
//Outputs : None
//Return  : return 0 at time of successfull execution
//Notes   : Main function print Hello World and System Time
//********************************************************************************** 
int main(void) 
{
    
    time_t lRawTime = 0;
    printf(" Hello, World!\n");

    while (1) 
    {
        time(&lRawTime);    

        // Print UTC with epoch
        appTimerPrintUtcTime(lRawTime);
        // // Print IST (+5:30)
        appTimerPrintTimeZone(lRawTime, OFFSET_HOURS_IST, OFFSET_MINUTES_IST, LABEL_IST);
        // Print PST (-8:00)
        appTimerPrintTimeZone(lRawTime, OFFSET_HOURS_PST, OFFSET_MINUTES_PST, LABEL_PST);

        // Refresh every second
        sleep(WAIT_TIME); 
    }

    return RETURN_ZERO;
}
// EOF