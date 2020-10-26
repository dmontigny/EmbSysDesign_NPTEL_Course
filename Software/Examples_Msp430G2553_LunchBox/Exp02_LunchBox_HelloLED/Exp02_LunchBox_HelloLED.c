#include <msp430g2553.h>

/*@brief entry point for the code*/
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;       //! Stop Watchdog (Not recommended for code in production and devices working in field)

    P1OUT &=~ 0x41;                  // turn off LEDs

    //P1DIR |= BIT6;
    P1DIR |= 0x41;                  // Set P1.0 & P1.6 to output direction

    //P1OUT |= BIT7;
    P1OUT |= 0x40;                  // Set P1.7 to HIGH voltage

    //P1OUT |= BIT0;
    P1OUT |= 0x01;                  // Set P1.0 to HIGH voltage

    //P1OUT &=~ BIT6;
    //P1OUT &=~ 0x41;                  // turn off LEDs



/*
    //P1DIR |= BIT7;
    P1DIR |= 0x80;                  // Set P1.7 to output direction

    //P1OUT |= BIT7;
   //P1OUT |= 0x80;                  // Set P1.7 to HIGH voltage

    //P1OUT &=~ BIT7;
    P1OUT &=~ 0x80;                  // Set P1.7 to LOW voltage
*/

    return 0;
}
