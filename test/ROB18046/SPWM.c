#include<MSP430F5529.h>
#include<variate_init.h>
#include<math.h>

volatile unsigned int sin_table[SIN_NUM] = {};
extern float K_S;

void PWM_TA_init(void)
{
    TA0CTL = TACLR;
    TA0CTL = TASSEL_2  + MC_1 + ID_0;    // ACLK + Up
    TA0CCTL1 = OUTMOD_3;PWM12_SET;
//    TA0CCTL2 = OUTMOD_3;PWM13_SET;
//    TA0CCTL3 = OUTMOD_3;PWM14_SET;
//    TA0CCTL4 = OUTMOD_7;PWM15_SET;

    TA0CCR0 = Period_A;
    TA0CCR1 = Percent12;
//    TA0CCR2 = Percent13;
//    TA0CCR3 = Percent14;
//    TA0CCR4 = Percent15;
}

void PWM_TB_init(void)
{
    TB0CTL = TBCLR;
    TB0CTL = TBSSEL_2  + MC_1 + ID_0;
//    TB0CCTL2 = OUTMOD_7;PWM74_SET;
    TB0CCTL5 = OUTMOD_7;PWM35_SET;
    TB0CCTL6 = OUTMOD_3;PWM36_SET;

    TB0CCR0 = Period_B;
//    TB0CCR2 = Percent74;
    TB0CCR5 = Percent35;
    TB0CCR6 = Percent36;
}

#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void)
{
    ADC12CTL0 &= ~ADC12ENC;

    static unsigned int i = 0;
    TB0CCR5 = sin_table[i];
    TB0CCR6 = sin_table[i];
    i = (++i) % SIN_NUM;

    ADC12CTL0 |= ADC12ENC;
}

void Sin_Table(void)
{
    unsigned int i;
    float sine;
    float interval = 2 * 3.14159 / SIN_NUM;
    for(i = 0; i < SIN_NUM; i++)
    {
        sine = sin(i * interval) * 0.9;
        sin_table[i] = (unsigned int) ((1 + sine) * Period_B / 2);
    }
}
