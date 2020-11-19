#include <msp430.h> 

#define GREEN BIT0
#define RED   BIT6                          // Red LED -> P1.6

/**
 *@brief  This function provides delay
 *@param  unsigned int
 *@return void
 **/

void delay(unsigned int t);                 // Custom delay function

/*@brief entry point for the code*/
void main(void) {
    unsigned int j;
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

    P1DIR |= (RED + GREEN);                 // Set LED pin -> Output

    while(1)
        {

            for(j = 0; j < 256; j++)  // Increasing Intensity
            {
                P1OUT &= ~GREEN;                // LED OFF
                P1OUT |= RED;                   // LED ON
                if (j !=0) delay(j);            // Delay for ON Time
                P1OUT |= GREEN;                 // LED ON
                P1OUT &= ~RED;                  // LED OFF
                if ((255-j)!=0) delay(255-j);   // OFF Time = Period - ON Time
            }
            for(j = 255; j > 0; j--)            // Decreasing Intensity
            {
                P1OUT &= ~GREEN;                // LED OFF
                P1OUT |= RED;                   // LED ON
                if (j !=0) delay(j);            // Delay for ON Time
                P1OUT |= GREEN;                 // LED ON
                P1OUT &= ~RED;                  // LED OFF
                if ((255-j) != 0 ) delay(255-j); // OFF Time = Period - ON Time
            }
        }
}

void delay(unsigned int t)
{
    unsigned int i;
    for(i = t; i > 0; i--)
        __delay_cycles(50);                 /* __delay_cycles accepts
                                                only constants ! */
}
