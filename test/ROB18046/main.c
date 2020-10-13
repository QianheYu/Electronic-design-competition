#include<MSP430F5529.h>
#include<variate_init.h>
#include<CLOCK.h>
#include<SPWM.h>
#include<ADC.h>
#include<PID.h>

unsigned int s = 0;
void main(void)
{

    WDTCTL = WDTPW + WDTHOLD;

    P1DIR |= BIT0;
    P1OUT &= ~BIT0;

    Init_Clock();

    Sin_Table();
    PWM_TA_init();
    PWM_TB_init();

    TB0CCTL0 = CCIE;

    ADC_Init();
    _enable_interrupts();


    while(1)
    {
        ADC12CTL0 |= ADC12SC;
        if(index == 256)
        {
            index = 0;
            Vpp_AC0_Operation();
            Vpp_AC1_Operation();
            Vpp_DC_Operation();
//            Dc_Pwm();
//            Ac_Spwm();
            Exsist_Test();
            Dc_Pwm_Open();
        }
    }
}
