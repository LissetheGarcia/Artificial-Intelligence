/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F15313
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB 	          :  MPLAB X 5.45	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set LED_WATER aliases
#define LED_WATER_TRIS                 TRISAbits.TRISA0
#define LED_WATER_LAT                  LATAbits.LATA0
#define LED_WATER_PORT                 PORTAbits.RA0
#define LED_WATER_WPU                  WPUAbits.WPUA0
#define LED_WATER_OD                   ODCONAbits.ODCA0
#define LED_WATER_ANS                  ANSELAbits.ANSA0
#define LED_WATER_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define LED_WATER_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define LED_WATER_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define LED_WATER_GetValue()           PORTAbits.RA0
#define LED_WATER_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define LED_WATER_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define LED_WATER_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define LED_WATER_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define LED_WATER_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define LED_WATER_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define LED_WATER_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define LED_WATER_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set LED_LIGHT_1 aliases
#define LED_LIGHT_1_TRIS                 TRISAbits.TRISA1
#define LED_LIGHT_1_LAT                  LATAbits.LATA1
#define LED_LIGHT_1_PORT                 PORTAbits.RA1
#define LED_LIGHT_1_WPU                  WPUAbits.WPUA1
#define LED_LIGHT_1_OD                   ODCONAbits.ODCA1
#define LED_LIGHT_1_ANS                  ANSELAbits.ANSA1
#define LED_LIGHT_1_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define LED_LIGHT_1_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define LED_LIGHT_1_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define LED_LIGHT_1_GetValue()           PORTAbits.RA1
#define LED_LIGHT_1_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define LED_LIGHT_1_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define LED_LIGHT_1_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define LED_LIGHT_1_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define LED_LIGHT_1_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define LED_LIGHT_1_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define LED_LIGHT_1_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define LED_LIGHT_1_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set LED_LIGHT_2 aliases
#define LED_LIGHT_2_TRIS                 TRISAbits.TRISA2
#define LED_LIGHT_2_LAT                  LATAbits.LATA2
#define LED_LIGHT_2_PORT                 PORTAbits.RA2
#define LED_LIGHT_2_WPU                  WPUAbits.WPUA2
#define LED_LIGHT_2_OD                   ODCONAbits.ODCA2
#define LED_LIGHT_2_ANS                  ANSELAbits.ANSA2
#define LED_LIGHT_2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define LED_LIGHT_2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define LED_LIGHT_2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define LED_LIGHT_2_GetValue()           PORTAbits.RA2
#define LED_LIGHT_2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define LED_LIGHT_2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define LED_LIGHT_2_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define LED_LIGHT_2_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define LED_LIGHT_2_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define LED_LIGHT_2_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define LED_LIGHT_2_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define LED_LIGHT_2_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set WATER aliases
#define WATER_TRIS                 TRISAbits.TRISA4
#define WATER_LAT                  LATAbits.LATA4
#define WATER_PORT                 PORTAbits.RA4
#define WATER_WPU                  WPUAbits.WPUA4
#define WATER_OD                   ODCONAbits.ODCA4
#define WATER_ANS                  ANSELAbits.ANSA4
#define WATER_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define WATER_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define WATER_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define WATER_GetValue()           PORTAbits.RA4
#define WATER_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define WATER_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define WATER_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define WATER_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define WATER_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define WATER_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define WATER_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define WATER_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set LIGHT aliases
#define LIGHT_TRIS                 TRISAbits.TRISA5
#define LIGHT_LAT                  LATAbits.LATA5
#define LIGHT_PORT                 PORTAbits.RA5
#define LIGHT_WPU                  WPUAbits.WPUA5
#define LIGHT_OD                   ODCONAbits.ODCA5
#define LIGHT_ANS                  ANSELAbits.ANSA5
#define LIGHT_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define LIGHT_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define LIGHT_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define LIGHT_GetValue()           PORTAbits.RA5
#define LIGHT_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define LIGHT_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define LIGHT_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define LIGHT_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define LIGHT_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define LIGHT_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define LIGHT_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define LIGHT_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/