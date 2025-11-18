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
#define MESSAGE_LED_ON                "LED ON"
#define MESSAGE_LED_OFF               "LED OFF"
 
//***************************** Local Constants ******************************* 
 
//***************************** Local Variables ******************************* 
 
//****************************** Local Functions ****************************** 
//******************************.FUNCTION_HEADER.*******************************
//Purpose : Display the received LED status and then toggle it.
//Inputs  : blLedStatus (bool) – LED status.
//Outputs : None (prints LED status directly to stdout).
//Return  : bool – true if toggled LED status is true.
//Return  : bool – false if toggled LED status is false.
//Notes   : Prints the system time in UTC format along with the epoch value.
//******************************************************************************
bool DisplayToggledLedStatus(bool blLedStatus)
{
	if(blLedStatus == 0 || blLedStatus ==1)
	{
		if(blLedStatus == 0 )
		{
			printf("%s\n\n",MESSAGE_LED_OFF);
			blLedStatus = 1;
		}
		else
		{
			printf("%s\n\n",MESSAGE_LED_ON);
			blLedStatus = 0;
		}		
		
	}
	
	return blLedStatus;

}

//******************************.FUNCTION_HEADER.*******************************
//Purpose : Prints a formatted time zone label, time string, and date string.
//Inputs  : pucLabel     (const uint8*) – Label describing the time zone.
//Inputs  : pucTimeStr   (const uint8*) – Formatted time string (HH:MM:SS AM/PM).
//Inputs  : pucDateStr   (const uint8*) – Formatted date string (DD/MM/YYYY).
//Outputs : None (prints directly to stdout).
//Return  : bool – true if printing succeeded 
//Return  : bool – false if any input pointer is NULL
//Notes   : This is a static helper function, private to the file, used by
//          higher-level time printing routines to display formatted results.
//******************************************************************************
static bool printTimeZoneInfo(const uint8* pucLabel,
                              const uint8* pucTimeStr,
                              const uint8* pucDateStr)
{
    bool blPrintSuccess = false;

    if (pucLabel && pucTimeStr && pucDateStr)
    {
		printf("%s\n", pucLabel);
		printf("---------------------------\n");
		printf("Time : %s\n", pucTimeStr);
		printf("Date : %s\n\n", pucDateStr);

		blPrintSuccess = true;

    }

    return blPrintSuccess;
}
//******************************.FUNCTION_HEADER.******************************
//Purpose : Prints the system time adjusted to a given time zone offset.
//Inputs  : lRawTime      (int32)  – Epoch time in seconds since 1 Jan 1970.
//Inputs  : lOffsetHours  (int32)  – Hour offset from UTC (-12 to +14).
//Inputs  : ulOffsetMinutes (uint32) – Minute offset from UTC (0 to 59).
//Inputs  : pucLabel      (const uint8*) – Label string describing 
//          the time zone
//Outputs : None (prints formatted time and date directly to stdout).
//Return  : bool – true if printing succeeded, false if input validation failed.
//Return  : bool – false if input validation failed.
//Notes   : Prints the system time adjusted to a given time zone offset.
//******************************************************************************
bool appTimerPrintTimeZone(int32 lRawTime, int32 lOffsetHours,
                           uint32 ulOffsetMinutes, const uint8* pucLabel)
{
    uint8 pucTimeStr[MAX_TIMESTRING_SIZE] = { 0 };
	uint8 pucDateStr[MAX_DATESTRING_SIZE] = { 0 };
    struct tm* psTimeInfo = NULL;    
    bool blReturnValue = false;
    //Validate arguments
    if (lRawTime > 0 && pucLabel != NULL && lOffsetHours >= -12 &&
        lOffsetHours <= 14 && ulOffsetMinutes <= 59)
    {
        //Adjust time by offset
        lRawTime += lOffsetHours * 3600 + ulOffsetMinutes * 60;
        //Convert the adjusted raw time (epoch seconds) into a UTC time 
        psTimeInfo = gmtime(&lRawTime);         
        //Format the time portion (hours, minutes, seconds, AM/PM) into 
        strftime((char *)pucTimeStr, sizeof(pucTimeStr),
                    "%I:%M:%S %p", psTimeInfo);
        //Format the date portion (day/month/year) into a string.		
        strftime((char *)pucDateStr, sizeof(pucDateStr), 
                    "%d/%m/%Y", psTimeInfo); 
		//Print results
		blReturnValue = printTimeZoneInfo(pucLabel, pucTimeStr, pucDateStr);
    }
    return blReturnValue;
}

//******************************.FUNCTION_HEADER.*******************************
//Purpose : Prints the system time in UTC format along with the epoch value.
//Inputs  : lRawTime (int32) – Epoch time in seconds since 1 Jan 1970.
//Outputs : None (prints formatted UTC time and date directly to stdout).
//Return  : bool – true if printing succeeded, false if input validation failed.
//Notes   : Prints the system time in UTC format along with the epoch value.
//******************************************************************************
bool appTimerPrintUtcTime(int32 lRawTime)
{
    char pucTimeStr[MAX_TIMESTRING_SIZE] = { 0 };
    char pucDateStr[MAX_DATESTRING_SIZE] = { 0 };
    bool blReturnValue = false;
    struct tm* psUtcTimeInfo = NULL;

    //Validate raw time
    if (lRawTime > 0)
    {
        //Convert to UTC time 
        psUtcTimeInfo = gmtime(&lRawTime);
        //Format time and date
        strftime(pucTimeStr, sizeof(pucTimeStr), "%I:%M:%S %p",
                psUtcTimeInfo);
        strftime(pucDateStr, sizeof(pucDateStr), "%d/%m/%Y",
                psUtcTimeInfo);
        //Print results
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