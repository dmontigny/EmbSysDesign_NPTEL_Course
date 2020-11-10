/*
 * file: Exp06_HelloSwitch_PullDown.c
 *   adapted from Exp06_LunchBox_HelloSwitch_PullDown.c
 *
 * purpose: toggles on board LED when external switch is pressed. Input pin
 *   is pulled down
 *
 *  David Montigny
 *  dmontigny27@gmail.com
 *  2020-11-10
 */
#include <msp430g2553.h>

// *********** need external switch connected ***********
#define SW  BIT4                    // Switch -> P1.4 (External Switch,
                                    // Pull-Down configuration)
#define LED BIT6                    // Red LED -> P1.6 (External Switch,
                                    // Active-High configuration)

/*@brief entry point for the code*/
void main(void) {
    WDTCTL = WDTPW | WDTHOLD;       //! Stop Watchdog (Not recommended for code
                                    // in production and devices
                                    // working in field)

    P1DIR |= LED;                   // Set LED pin -> Output

    P1DIR &= ~SW;                   // Set SW pin -> Input
    P1REN |= SW;                    // Enable Resistor for SW pin
    P1OUT &=~ SW;                   // Select Pull down for SW pin
    P1OUT &= ~LED;                  // Initialize LED off

    while(1)
    {
        if(P1IN & SW)               // If SW is Pressed
        {
            __delay_cycles(20000);  // Wait 20ms to debounce
            while((P1IN & SW));     // Wait till SW Released
            __delay_cycles(20000);  // Wait 20ms to debounce
            P1OUT ^= LED;           // Toggle LED
        }
    }
}
