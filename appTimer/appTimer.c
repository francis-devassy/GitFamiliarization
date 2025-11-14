//**************************** PROJECT DISPLAY SYSTEM TIME ********************
//  Copyright (c) 2025 Trenser Technology Solutions 
//  All Rights Reserved 
//***************************************************************************** 
// 
// File    : appTimer.c
// Summary : Program to print system time
// Note    : Print time in GMT, IST and PST formats
// Author  : Francis V D
// Date    : 13-11-2025
// 
//***************************************************************************** 
 
//******************************* Include Files ******************************* 
#include <stdbool.h> 
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "appTimer.h"
#include "customTypes.h"
//******************************* Local Types ********************************* 
#define MAX_TIMESTRING_SIZE (20)
#define MAX_DATESTRING_SIZE (20)
 
//***************************** Local Constants ******************************* 
 
//***************************** Local Variables ******************************* 
 
//****************************** Local Functions ****************************** 
//******************************.FUNCTION_HEADER.******************************
//Purpose : Prints the system time adjusted to a given time zone offset.
//Inputs  : lRawTime      (int32)  – Epoch time in seconds since 1 Jan 1970.
//Inputs  : lOffsetHours  (int32)  – Hour offset from UTC (-12 to +14).
//Inputs  : ulOffsetMinutes (uint32) – Minute offset from UTC (0 to 59).
//Inputs  : pucLabel      (const uint8*) – Label string describing the time zone.
//Outputs : None (prints formatted time and date directly to stdout).
//Return  : bool – true if printing succeeded, false if input validation failed.
//Return  : bool – false if input validation failed.
//Notes   : Prints the system time adjusted to a given time zone offset.
//**********************************************************************************

bool appTimerPrintTimeZone(int32 lRawTime, 
                           int32 lOffsetHours,
                           uint32 ulOffsetMinutes, 
                           const uint8* pucLabel)
{
    uint8 pucTimeStr[MAX_TIMESTRING_SIZE] = { 0 };
    uint8 pucDateStr[MAX_DATESTRING_SIZE] = { 0 };    
    bool blReturnValue = false;

    // Validate arguments
    if (!(lRawTime <= 0 || 
        pucLabel == NULL ||
        lOffsetHours < -12 ||
        lOffsetHours > 14 ||
        ulOffsetMinutes < 0 ||
        ulOffsetMinutes > 59))
    {
        // Adjust time by offset
        lRawTime += lOffsetHours * 3600 + ulOffsetMinutes * 60;

        // Convert the adjusted raw time (epoch seconds) into a UTC time structure.
        // gmtime() returns a pointer to a statically allocated struct tm.
        struct tm* psTimeInfo = gmtime(&lRawTime); 
        
        // Format the time portion (hours, minutes, seconds, AM/PM) into a string.
        // - pucTimeStr: destination buffer
        // - sizeof(pucTimeStr): maximum size of buffer
        // - "%I:%M:%S %p": format string (12-hour clock with AM/PM)
        // - psTimeInfo: pointer to the struct tm containing UTC time    
        strftime(pucTimeStr,
                    sizeof(pucTimeStr),
                    "%I:%M:%S %p", 
                    psTimeInfo);

        // Format the date portion (day/month/year) into a string.
        // - pucDateStr: destination buffer
        // - sizeof(pucDateStr): maximum size of buffer
        // - "%d/%m/%Y": format string (day/month/year)
        // - psTimeInfo: pointer to the struct tm containing UTC time
        strftime(pucDateStr,
                    sizeof(pucDateStr), 
                    "%d/%m/%Y", 
                    psTimeInfo);

        

        printf("%s\n", pucLabel);
        printf("---------------------------\n");
        printf("Time : %s\n", pucTimeStr);
        printf("Date : %s\n\n", pucDateStr);

        blReturnValue = true;

    }

    return blReturnValue;
}

//******************************.FUNCTION_HEADER.******************************
//Purpose : Prints the system time in UTC format along with the epoch value.
//Inputs  : lRawTime (int32) – Epoch time in seconds since 1 Jan 1970.
//Outputs : None (prints formatted UTC time and date directly to stdout).
//Return  : bool – true if printing succeeded, false if input validation failed.
//Notes   : Prints the system time in UTC format along with the epoch value.
//**********************************************************************************
bool appTimerPrintUtcTime(int32 lRawTime)
{
    char pucTimeStr[MAX_TIMESTRING_SIZE] = { 0 };
    char pucDateStr[MAX_DATESTRING_SIZE] = { 0 };
    bool blReturnValue = false;
    struct tm* psUtcTimeInfo = NULL;

    // Validate raw time
    if (!(lRawTime <= 0)) 
    {
        // Convert to UTC time 
        psUtcTimeInfo = gmtime(&lRawTime);
        // Format time and date
        strftime(pucTimeStr,
                sizeof(pucTimeStr),
                "%I:%M:%S %p",
                psUtcTimeInfo);
        strftime(pucDateStr,
                sizeof(pucDateStr),
                "%d/%m/%Y",
                psUtcTimeInfo);
        // Print results
        printf("UTC (0:00)\n");
        printf("---------------------------\n");
        printf("Time : %s\n", pucTimeStr);
        printf("Date : %s\n", pucDateStr);
        printf("Epoch: %ld\n\n", (long)lRawTime);
        blReturnValue = true;        
    }
    return blReturnValue;
}

// EOF 