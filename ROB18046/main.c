#include<MSP430F5529.h>
#include<variate_init.h>
#include<CLOCK.h>
#include<SPWM.h>
#include<ADC.h>

extern unsigned int test;
extern unsigned int alternat;
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;

    Init_Clock();
    P2DIR |= BIT2;
    P2SEL |= BIT2;
    Sin_Table();
    PWM_TA_init();
    PWM_TB_init();

    TB0CCTL0 = CCIE;

    ADC_Init();
    __enable_interrupt();

    while(1)
    {
        ADC12CTL0 |= ADC12SC;
        if(alternat == 256)
        {
            alternat = 0;
            Vpp_AC0_Operation();
            Vpp_AC1_Operation();
            Direct_Operation();
        }
    }
}
