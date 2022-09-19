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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
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

// constants in preprocessor
#define LIGHT_HIGH 750
#define LIGHT_LOW 250

// Global variable to hold ADC results
adc_result_t adcRawLight;
unsigned char dD_IN;
unsigned char dD_LOW;
unsigned char dD_HIGH;

// function prototypes
void setup( void );
void loop( void );

// main application
void main(void)
{
    SYSTEM_Initialize(); // initialize the device

    setup();
    
    do 
    {
        loop();
    }while( 1 );
    
    return;
}

void setup( void )
{
    INIT_GLOBAL_VARS:
        adcRawLight = 0;
    SET_UP_ADC:
        ADC_SelectChannel(LIGHT); // Starts conversion
        ADC_StartConversion(); // Returns true when the conversion is completed otherwise false.
    SET_UP_DIGITAL_PINS: // Digital pins configurations
        // --
        WATER_SetDigitalInput(); // Macro generated in the pin_manager.h file
        // --
        LED_WATER_SetDigitalOutput(); // set the led of water as a digital output
        LED_WATER_SetLow(); // the default value of water led indicator is turned off
        // --
        LED_LIGHT_1_SetDigitalOutput(); // Set led 1 when there is not enough light as a digital output
        LED_LIGHT_1_SetHigh(); // Set the default value to the custom light and the led 1 is turned on
        // --
        LED_LIGHT_2_SetDigitalOutput(); // set led 2 when there is so much light as a digital output
        LED_LIGHT_2_SetHigh(); // set the default led 2 turned on, wich is the custom light value
    return;
}

void loop( void )
{
    unsigned char ucTmp;
    SENSING:
    // ADC
        if ( ADC_IsConversionDone() ) // Returns the ADC conversion value.
        {
            adcRawLight = ADC_GetConversionResult(); //  Returns the ADC conversion value, also allows selection of a channel for conversion.
            ADC_StartConversion(); // Returns true when the conversion is completed otherwise false.
        }
    // -- Digital
        dD_IN = WATER_GetValue(); // If logic level: 0 or 1
    PROCESSING:
        adcRawLight &= 0xFF00; // global viariable asigned to the address 0xFF
        ucTmp = adcRawLight >> 8; // adcRawLight es desplazado 8 posiciones a la derecha
    ACTING:
    // If water reservoir is empty, Turn Water Reserve LED on
        if (dD_IN)
        {
            LED_WATER_SetHigh(); // If water reservoir is empty, turn water reserve LED on
        }
        else
        {
            LED_WATER_SetLow(); // If water reservoir is not empty, LED keeps turned off
        }
        // If LIGHT is too less, turn on LOW LED 
        // If LIGHT is in the good LIGHT range, turn on LOW and HIGH LEDS
        // If LIGHT is too MUCH turn on HIGH LED
        if ( ADC_GetConversion(LIGHT) > LIGHT_HIGH )
        {
            LED_LIGHT_1_SetHigh();
            LED_LIGHT_2_SetLow();
        }
        else if ( ADC_GetConversion(LIGHT) < LIGHT_LOW )
        {
            LED_LIGHT_2_SetHigh();
            LED_LIGHT_1_SetLow();
            
        }
        else
        {
            LED_LIGHT_2_SetHigh();
            LED_LIGHT_1_SetHigh();
        }
    return;
}