/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules 
 *  selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F15313
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software 
 *  and any derivatives exclusively with Microchip products. It is your 
 *  responsibility to comply with third party license terms applicable to 
 *  your use of third party software (including open source software) that 
 *  may accompany Microchip software.
    
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
unsigned char temp;

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
        // Starts conversion
        ADC_SelectChannel(LIGHT); 
        // Returns true when the conversion is completed otherwise false.
        ADC_StartConversion(); 
    SET_UP_DIGITAL_PINS: // Digital pins configurations
        // --// Set led 1 when there is not enough light as a digital output
        LED_LIGHT_1_SetDigitalOutput(); 
        // Set the default value to the custom light and the led 1 is turned on
        LED_LIGHT_1_SetHigh(); 
        // --
        // set led 2 when there is so much light as a digital output
        LED_LIGHT_2_SetDigitalOutput(); 
        // set the default led 2 turned on, wich is the custom light value
        LED_LIGHT_2_SetHigh(); 
    return;
}

void loop( void )
{
    uint16_t dutycycle;
    //clear out any stored value
    dutycycle = 0;
    unsigned char ucTmp;
    SENSING:
    // ADC
        // Returns the ADC conversion value.
        if ( ADC_IsConversionDone() ) 
        {
            //  Returns the ADC conversion value, also allows 
            // selection of a channel for conversion.
            adcRawLight = ADC_GetConversionResult(); 
            // Returns true when the conversion is completed otherwise false.
            ADC_StartConversion(); 
        }
    PROCESSING:
        // global viariable asigned to the address 0xFF
        adcRawLight &= 0xFF00; 
        // adcRawLight es desplazado 8 posiciones a la derecha
        ucTmp = adcRawLight >> 8; 
    ACTING:
        // If LIGHT is too less, turn on LOW LED 
        // If LIGHT is in the good LIGHT range, turn on LOW and HIGH LEDS
        // If LIGHT is too MUCH turn on HIGH LED
        do{
            if ( ADC_GetConversion(LIGHT) >= LIGHT_HIGH )
            {
                LED_LIGHT_1_SetHigh();
                LED_LIGHT_2_SetLow();
                // Si el nivel de luz es bajo, hay que abrir el domo
                for( dutycycle = 30; dutycycle < 65; dutycycle ++)
                {  //cycle duty cycle from 30 to 65
                    PWM6_LoadDutyValue(dutycycle);
                    __delay_ms(20);
                }
                //printf("Nivel de luz BAJO\n");
                //__delay_ms(5000);
                break;
            }
            if( ADC_GetConversion(LIGHT) < LIGHT_LOW )
            {
                LED_LIGHT_2_SetHigh();
                LED_LIGHT_1_SetLow();
                // Si el nivel de luz es alto, hay que cerrar/modular la 
                // apertura del domo para la entrada de luz
                for( dutycycle = 65; dutycycle > 30; dutycycle --)
                { //cycle duty cycle from 65 to 30
                PWM6_LoadDutyValue(dutycycle);
                __delay_ms(20);
                }
                
                //__delay_ms(5000);
                break;
            }
            if(ADC_GetConversion(LIGHT) < LIGHT_HIGH || 
                    ADC_GetConversion(LIGHT) > LIGHT_LOW)
            {
                LED_LIGHT_2_SetHigh();
                LED_LIGHT_1_SetHigh();
                //servoRotate0(); //0 Degree
                // printf("Nivel de luz ADECUADO\n");
                //__delay_ms(5000);
                break;
            }
        }while(0);
    return;
}