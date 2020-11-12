/*
 * file: Exp06_HelloSwitch_PullUp.c
 *   adapted from Exp07_LunchBox_HelloSwitch_PullUp2.c
 *
 * purpose: toggles on board LED when external switch is pressed. Input pin
 *   is pulled up
 *
 *  David Montigny
 *  dmontigny27@gmail.com
 *  2020-11-10
 */
#include <msp430g2553.h>

#define SW  BIT6                    // Switch -> P1.6 (External Switch, Pull-Up
                                    // configuration)
#define LED BIT0                    // Green LED -> P1.0 (External Switch,
                                    // Active-High configuration)

/*@brief entry point for the code*/
void main(void) {
    WDTCTL = WDTPW | WDTHOLD;       //! Stop Watchdog (Not recommended for code
                                    // in production and devices
                                    // working in field)

    P1DIR |= LED;                   // Set LED pin -> Output

    P1DIR &= ~SW;                   // Set SW pin -> Input
    P1REN |= SW;                    // Enable Resistor for SW pin
    P1OUT |= SW;                    // Select Pull Up for SW pin
    P1OUT &= ~LED;                  // Initialize LED off

    while(1)
    {
        if(!(P1IN & SW))    // If SW is Pressed
        {

            __delay_cycles(20000);  // Wait 20ms to debounce
            while(!(P1IN & SW));    // Wait till SW Released
            __delay_cycles(20000);  // Wait 20ms to debounce
            P1OUT ^= LED;           // Toggle LED
        }
    }
}
