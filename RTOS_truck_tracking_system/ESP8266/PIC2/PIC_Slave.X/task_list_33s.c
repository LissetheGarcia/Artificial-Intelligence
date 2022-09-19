/*
 * File:   task_list_33s.c
 * Author: Terra.Drakko
 *
 * Created on July 21, 2020, 1:40 PM
 */


#include "mcc_generated_files/mcc.h"
#include "OS_uKaos.h"

    void
measureHumidity( void )
    {
    if  ( ADC_IsConversionDone() )
        { ADC_StartConversion(); }
    }

    void 
task_list_33s(void)                               // Round Robin scheduling
    {
    measureHumidity();
    }
