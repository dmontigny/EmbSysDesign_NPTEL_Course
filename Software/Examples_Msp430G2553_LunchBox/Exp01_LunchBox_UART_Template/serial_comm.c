/*
 * serial_comm.c
 *
 * echoes back received characters to host
 *
 *  Created on: Nov 4, 2020
 *      Author: dmontylx
 *
 * ***** SERIAL JUMPERS MUST BE HORIZONTAL ********
 *
 */

#include <msp430g2553.h>

const char greet[] = { "\n\nHello Dave!\r\n\n" };
unsigned int x = 0;

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  if (CALBC1_1MHZ==0xFF)                    // If calibration constant erased
  {
    while(1);                               // do not load, trap CPU!!
  }
  DCOCTL = 0;                               // Select lowest DCOx and MODx settings
  BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
  DCOCTL = CALDCO_1MHZ;
  P1SEL = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
  P1SEL2 = BIT1 + BIT2 ;                    // P1.1 = RXD, P1.2=TXD
  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  UCA0BR0 = 104;                            // 1MHz 9600
  UCA0BR1 = 0;                              // 1MHz 9600
  UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt

  P1OUT &=~ 0x41;                  // turn off LEDs

  //P1DIR |= BIT6;
  P1DIR |= 0x41;            // P1.6 (Red LED)


  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, interrupts enabled
}

#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void)
{
   P1OUT |= BIT0;
     UCA0TXBUF = greet[x++]; // TX next character
    if (x == sizeof greet - 1) // TX over?
        IE2 &= ~UCA0TXIE; // Disable USCI_A0 TX interrupt
    P1OUT &= ~BIT0;
}

//  Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    volatile unsigned long wt;

    P1OUT |= BIT6;              //Red LED -> ON
    for(wt = 0; wt<10000; wt++);   //delay

    //P1OUT &=~ BIT6;
    P1OUT &= ~BIT6;             //Red LED -> OFF

  while (!(IFG2&UCA0TXIFG));                // USCI_A0 TX buffer ready?
  if(UCA0RXBUF == 'd'){                     // TX -> RXed character
      x = 0;
      IE2 |= UCA0TXIE; // Enable USCI_A0 TX interrupt
      UCA0TXBUF = greet[x++];
  }
  else
  {
      UCA0TXBUF = UCA0RXBUF;                    // TX -> RXed character
  }
}


