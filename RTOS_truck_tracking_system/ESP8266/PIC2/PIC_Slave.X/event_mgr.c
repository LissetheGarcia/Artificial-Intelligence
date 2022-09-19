/*
 * File:   event_mgr.c
 * Author: Terra.Drakko
 *
 * Created on July 21, 2020, 12:05 AM
 */


#include "mcc_generated_files/mcc.h"
#include "OS_uKaos.h"
#include "event_mgr.h"

    void 
incRippleCount( void ) 
    {
    usRippleCount++;
    }

    void
storeSensorVal( void )
    {
    readLocation = EUSART1_Read();
    i2c1WrData = readLocation;
    }