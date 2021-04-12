/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#endif

#include "user.h"


#include <plib/timers.h>
#include <plib/delays.h>





/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */
    TRISD = 0x00;
    PORTD = 0x00;
    /* Setup analog functionality and port direction */

    /* Initialize peripherals */

    /* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */

    /* Enable interrupts */

    /*Timer0*/

    T0CONbits.TMR0ON = 0; //stop timer0
    T0CONbits.T08BIT = 0; //16-bit
    T0CONbits.T0CS   = 0; //use system clock
    T0CONbits.PSA    = 0; //use prescaler
    T0CONbits.T0PS   = 0b000;  //128 prescaler
    TMR0 = -746; //initial timer value
    INTCONbits.T0IF = 0; //clear the overflow bit
    T0CONbits.TMR0ON = 1; //start timer0

//    /*Timer1*/
//    T1CONbits.TMR1ON = 0; //Timer1 OFF
//    T1CONbits.RD16 = 1; //16 bits mode
//    T1CONbits.TMR1CS = 0; //Fosc/4 internal oscillator
//    T1CONbits.T1CKPS = 0b01; //Timer1 prescaler = 2
//    PIR1bits.TMR1IF = 0; //Borra flag de TIMER1 clear overflow bit
//    TMR1 = -750;
//    T1CONbits.TMR1ON = 1; //Timer1 OFF


}

