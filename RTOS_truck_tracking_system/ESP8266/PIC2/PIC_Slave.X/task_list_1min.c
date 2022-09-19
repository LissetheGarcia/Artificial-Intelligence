/*
 * File:   task_list_1min.c
 * Author: lisse
 *
 * Created on December 7, 2021, 11:55 PM
 */

#include "mcc_generated_files/mcc.h"
#include "OS_uKaos.h"

    void measureLocation( void )
    {
    if  ( EUSART1_is_tx_ready() )
        { EUSART1_Read(); }
    }

    void task_list_1min(void)                               // Round Robin scheduling
    {
    measureLocation();
    }
