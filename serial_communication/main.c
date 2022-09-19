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
#include <stdio.h>

// constants in preprocessor
#define LIGHT_HIGH 750
#define LIGHT_LOW 250

// Global variable to hold ADC results
adc_result_t adcRawLight;
unsigned char dD_IN;
unsigned char dD_LOW;
unsigned char dD_HIGH;

// function prototypes

void loop( void );

// main application
void main(void)
{
    SYSTEM_Initialize(); // initialize the device

    
    do 
    {
        loop();
    }while( 1 );
    
    return;
}

void loop( void )
{
    int action;
    int opc, items;
    ACTING:
        do{
            printf("2. Para control de luz automatico\n "
                    "1. Para control de luz manual.\n");
            items = scanf("%u", &opc);
            /*if(opc == 1)
            {
                printf("Teclee 1 para abrir el domo de luz.\n"
                        "Teclee 2 para cerrar el domo de luz\n");
                scanf("%d", &action);
                if(action == 1) 
                {
                    printf("Abriendo el domo de luz\n");
                    break;
                }
                else
                {
                    printf("Cerrando el domo de luz");
                    break;
                }
            }
            if(opc == 2)
                {break;}*/
 

        }while(1);
}
