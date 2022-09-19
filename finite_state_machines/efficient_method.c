/*
 * File:   efficient_method.c
 * Author: lisse
 *
 * Created on 29 de septiembre de 2021, 01:38 PM
 */


#include <xc.h>
#include <stdio.h>
//#include <pic16f15313.h>


void main(void) 
{
    int n1, n2;
    
    start:
    {
        printf("Start\n ");
        goto calculate;
    }
    calculate:
    {
        printf("Calculate\n ");
        printf("Ingrese 2 enteros: ");
        scanf("%d", &n1, "%d", &n2);
        if(n1 > n2)
        {
            goto result;
        }
        else
        {
            goto close;
        }
    }
    result:
    {
        printf("Result\n");
        printf("n1 es menor a n2 \n");
        goto calculate;
    }
    close:
    {
        printf("Close\n");
        goto end;
    }
    end:
    {
        printf("End\n");
        return;
    }
    //return;
}
