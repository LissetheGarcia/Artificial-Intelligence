/*
 * File:   task_list_1s.c
 * Author: Terra.Drakko
 *
 * Created on July 21, 2020, 10:43 AM
 */


#include "mcc_generated_files/mcc.h"
#include "OS_uKaos.h"

    
    void
alarmLEDMgr()
    {
    ubAlarmLED = i2c1RdData;
    led_RA1_SetLow();
    if  ( ubAlarmLED ) led_RA1_SetHigh();
    }

    void 
task_list_1s(void)                                // Round Robin scheduling
    {
 // waterLevelSense();
    alarmLEDMgr();
    }
