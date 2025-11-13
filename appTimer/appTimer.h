//**************************** PROJECT DISPLAY SYSTEM TIME ********************
//  Copyright (c) 2025 Trenser Technology Solutions
//  All Rights Reserved 
//***************************************************************************** 
// 
// Summary : Program to print system time
// Note    : Print time in GMT, IST and PST formats 
// 
//***************************************************************************** 

#ifndef _APPTIMER_H_
#define _APPTIMER_H_

//******************************* Include Files ******************************* 
#include "customTypes.h"
#include <time.h> 
#include <stdbool.h>
//******************************* Global Types ******************************** 
 
//***************************** Global Constants ****************************** 
 
//***************************** Global Variables ****************************** 
 
//**************************** Forward Declarations *************************** 
// Function to print time in a given timezone offset
bool appTimerPrintTimeZone(int32 lRawTime, 
                           int32 lOffsetHours,
                           uint32 ulOffsetMinutes, 
                           const uint8* pucLabel);

// Function to display UTC time with epoch
bool appTimerPrintUtcTime(int32 lRawTime);

//*********************** Inline Method Implementations *********************** 

#endif // _APPTIMER_H_
// EOF 