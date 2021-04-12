/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#endif

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

#ifndef BOOL
#define BOOL bool
#define FALSE 0
#define TRUE  1
#endif

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

char c = 0, c1 = 0,c2 = 0;
char c90 = 0;

 BOOL isHigh = FALSE;

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    /* TODO <INSERT USER APPLICATION CODE HERE> */

    while(1)
    {


     

        if(INTCONbits.T0IF == 1)
        {
            TMR0 = -746;                      //Freq 4KHz T =
            INTCONbits.T0IF = 0;

            isHigh = !isHigh;                   //high pulse or low pulse

            if(isHigh)
            {
                PORTDbits.RD2 =!PORTDbits.RD2; //Freq = 2kHz phase = 0
                if(PORTDbits.RD2 == 0)
                {
                  PORTDbits.RD4 = !PORTDbits.RD4;
                  if(PORTDbits.RD4 == 0)
                  {
                      PORTDbits.RD0 = !PORTDbits.RD0;
                      if(PORTDbits.RD0 == 0)
                      {
                          PORTDbits.RD6 = !PORTDbits.RD6;
                      }else{
                          PORTDbits.RD7 = !PORTDbits.RD7;
                      }
                  }else{
                      PORTDbits.RD1 = !PORTDbits.RD1;
                  }

                }else{
                  PORTDbits.RD5 = !PORTDbits.RD5;
                }
            }else{
                PORTDbits.RD3 =!PORTDbits.RD3;  //Freq = 2kHz phase = 90
            }



        }//end Timer if


    } //end while

}

