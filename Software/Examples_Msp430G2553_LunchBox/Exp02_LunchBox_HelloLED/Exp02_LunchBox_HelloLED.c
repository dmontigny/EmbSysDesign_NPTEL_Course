#include <msp430g2553.h>

/*@brief entry point for the code*/
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;       //! Stop Watchdog (Not recommended for code in production and devices working in field)

    P1OUT &=~ 0x41;                  // turn off LEDs

    //P1DIR |= BIT6;
    P1DIR |= 0x41;                  // Set P1.0 & P1.6 to output direction

    P1OUT |= BIT6;
    //P1OUT |= 0x40;                  // Set P1.6 to HIGH voltage

    P1OUT |= BIT0;
    //P1OUT |= 0x01;                  // Set P1.0 to HIGH voltage

    //P1OUT &=~ BIT6;
    P1OUT &=~ 0x41;                  // turn off LEDs


    return 0;
}
