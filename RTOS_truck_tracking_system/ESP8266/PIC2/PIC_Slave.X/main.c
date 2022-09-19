/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.4
        Device            :  PIC16F15313
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "OS_uKaos.h"

// --->> uKaos store area

// This counter is the central part to the ukaos OS.
// Each group of tasks running on the same time slot are triggered
// by the change on sate of the corresponding bit of this counter. 

// Time slot by bit position:
//
//  Hi byte                                                           LO byte
//< 33.5s - 16.7s - 8.3s - 4.1s - 2.0s - 1.0s - 524.2ms - 262.1ms >< 131.0ms - 65.5ms - 32.7ms - 16.3ms - 8.1ms - 4.9ms - 2.0ms - 1.0ms >

    unsigned short int    
usRippleCount = 0
    ;
    
    unsigned short int
usRipplePast = 0
    ;

    unsigned short int
usActiveTaskGroup
    ;
    
// --->> Application store  area
    
    volatile uint8_t
 readLocation = 0
    ;
    
    unsigned char
ubAlarmLED = 0;
    ;
  
// ::::: uKaos OS ::::::::::::::::::::::::::::::::::::::::::::::::::::::   
    
    void 
main(void) 
    {
        
    OS_INT:                                             
        {
        SYSTEM_Initialize();
        
        usRippleCount = 0;                                  // Time base init 
        TMR0_SetInterruptHandler( incRippleCount );
                
        I2C1_Open();
        EUSART1_Initialize();
        
        INTERRUPT_PeripheralInterruptEnable();              // Enable events
        INTERRUPT_GlobalInterruptEnable();
        
        }
    
    idle:                        
        {
        if ( usRippleCount == usRipplePast ) goto idle;     // Wait until a time slot passes
        
        usActiveTaskGroup = usRippleCount;                  // Find active slot
        usActiveTaskGroup ^= usRipplePast;
        usActiveTaskGroup &= usRippleCount;                 
                
        usRipplePast = usRippleCount;
        }
 
    task_1s:              
        {
        if  ( ( usActiveTaskGroup ^ 0x0400 ) == 0 )
            {
            beat_RA2_Toggle();                              // Toggle hearth beat LED 
            }
        }
    task_1min:
        {
        if  ( ( usActiveTaskGroup ^ 0xEA60 ) == 0 )
            {
            task_list_1min();                                // Activate tasks running every minute
            }
        }    
    
    goto idle;                                              // go for the next time slot
    }
/***********************************************************************
 End of File
***********************************************************************/
