/*
 * timer.c
 *
 *  Created on: 2020Äê10ÔÂ12ÈÕ
 *      Author: QianheYu
 */
#include <timer.h>

volatile unsigned int sin_table[SIN_POINT] = {};

void TimerA_Init(void)
{
    TA0CTL = TACLR;
    TA0CTL = TASSEL_2  + MC_1 + ID_0;    // ACLK + Up
    TA0CCTL1 = OUTMOD_3;

    TA0CCR0 = TA_PERIOD;
    TA0CCR1 = TA_PERCENT;
}

void TimerB_Init(void)
{
    TB0CTL = TBCLR;
    TB0CTL = TBSSEL_2  + MC_1 + ID_0;

    TB0CCTL5 = OUTMOD_7;
    TB0CCTL6 = OUTMOD_3;

    TB0CCR0 = TB_PERIOD;

    TB0CCR5 = TB_PERCENT;
    TB0CCR6 = TB_PERCENT;

    TB0CCR0 |= CCIE;
}

#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void)
{
    static unsigned int i = 0;
    TB0CCR5 = sin_table[i];
    TB0CCR6 = sin_table[i];
    i = (++i) % SIN_POINT;
}
