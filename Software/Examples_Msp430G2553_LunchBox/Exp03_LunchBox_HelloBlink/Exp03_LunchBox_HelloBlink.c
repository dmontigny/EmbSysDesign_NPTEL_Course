// Intro to Embedded Systems course
#include <msp430.h> 


/*@brief entry point for the code*/
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	//! Stop Watchdog (Not recommended for code in production and devices working in field)

    P1OUT &=~ 0x41;                  // turn off LEDs

	//P1DIR |= BIT6;
	P1DIR |= 0x41;            // P1.6 (Red LED)

    while(1)
    {
        volatile unsigned long i;

        //P1OUT |= BIT6;
        P1OUT |= 0x40;              //Red LED -> ON
        for(i = 0; i<10000; i++);   //delay

        //P1OUT &=~ BIT6;
        P1OUT &= ~0x40;             //Red LED -> OFF
        for(i = 0; i<10000; i++);   //delay

        //P1OUT |= BIT0;
        P1OUT |= 0x01;              //Green LED -> ON
        for(i = 0; i<10000; i++);   //delay

        P1OUT &= ~0x01;             //Green LED -> OFF
        for(i = 0; i<10000; i++);   //delay

    }
}
