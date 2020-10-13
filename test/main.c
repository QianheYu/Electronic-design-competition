#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1DIR |= BIT0;
	P1DIR &= ~BIT1;

	P1REN = BIT1;
	P1OUT = BIT0 + BIT1;



	return 0;
}


#pragma vector=
