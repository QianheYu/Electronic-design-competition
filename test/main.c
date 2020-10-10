#include<MSP430F5529.h>
#include<variate_init.h>
#include<CLOCK.h>
#include<SPWM.h>

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;

    Init_Clock();

    Sin_Table();
    PWM_TA_init();
    PWM_TB_init();

    TB0CCTL0 = CCIE;
    _enable_interrupts();

    while(1);

}

//#pragma vector = TIMER0_A0_VECTOR
//__interrupt void Timer0_A0_ISR(void)
//{
////    _disable_interrupts();
//
//    static unsigned int i = 0;
//    TA0CCR1 = sin_table[i];
//    TA0CCR2 = sin_table[i];
//    i = (++i) % SIN_NUM;
//
////    _enable_interrupts();
//}
