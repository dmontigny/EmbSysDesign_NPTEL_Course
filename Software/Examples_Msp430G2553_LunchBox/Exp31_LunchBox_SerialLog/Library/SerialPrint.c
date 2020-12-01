#include <Library/LunchboxCommon.h>
#include <msp430.h> 

#include <stdio.h>
#include <string.h>



#ifdef UART_PRINTF
/**
 *@brief This function overrides fputc()
 *@param *_ptr pointer to the character to be written.
 *@param *_fp  pointer to a FILE object that identifies the stream where the character is to be written.
 *@return length of the character stream
 **/
int fputc(int _c, register FILE *_fp)
{
    while (!(IFG2 & UCA0TXIFG))
        ;
    UCA0TXBUF = (unsigned char) _c;

    return ((unsigned char) _c);
}

/**
 *@brief This function overrides fputs
 *@param *_ptr pointer to the character to be written.
 *@param *_fp  pointer to a FILE object that identifies the stream where the character is to be written.
 *@return length of the character stream
 **/
int fputs(const char *_ptr, register FILE *_fp)
{
    unsigned int i, len;

    len = strlen(_ptr);

    for (i = 0; i < len; i++)
    {
        while (!(IFG2 & UCA0TXIFG))
            ;
        UCA0TXBUF = (unsigned char) _ptr[i];
    }

    return len;
}

#endif


/**
 * @brief
 * These settings are wrt enabling uart on Lunchbox
 **/
void initialise_SerialPrint_on_lunchbox()
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

/*
    P1SEL = BIT1 + BIT2;              // Select UART RX/TX function on P1.1,P1.2
    P1SEL2 = BIT1 + BIT2;

    UCA0CTL1 |= UCSSEL_1;               // UART Clock -> ACLK
    UCA0BR0 = 3;                        // Baud Rate Setting for 1MHz 9600
    UCA0BR1 = 0;                        // Baud Rate Setting for 1MHz 9600
    UCA0MCTL = UCBRF_0 + UCBRS_3;       // Modulation Setting for 1MHz 9600
    UCA0MCTL &= ~UCOS16;
    UCA0CTL1 &= ~UCSWRST;               // Initialize UART Module
    IE2 |= UCA0RXIE;                    // Enable RX interrupt
*/
}

