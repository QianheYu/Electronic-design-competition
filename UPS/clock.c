/*
 * clock.c
 *
 *  Created on: 2020Äê10ÔÂ12ÈÕ
 *      Author: QianheYu
 */


#include<MSP430F5529.h>

void Clock_Init(void)
{
    P5SEL |= BIT2 + BIT3 + BIT4 + BIT5;               //select function
    UCSCTL6 &= ~XT1DRIVE_3;                           // Clear XT1drive field
    UCSCTL6 |= XT1DRIVE_0;                           // Set requested value
    UCSCTL6 &= ~XT1OFF;                                // Enable XT1
    //P5SEL |= BIT2 + BIT3;

    UCSCTL6 &= ~XT2OFF;                               //Enable XT2

    __bis_SR_register(SCG0);
    UCSCTL0 = DCO0 + DCO1 + DCO2 + DCO3 + DCO4;
    UCSCTL1 = DCORSEL_4;
    UCSCTL2 = FLLD_4 + 1;
    UCSCTL3 = SELREF_5 + FLLREFDIV_3;
    UCSCTL4 = SELA_0 + SELS_3 + SELM_3;
    UCSCTL5 = DIVA_5;

    __bic_SR_register(SCG0);                //Enable the FLL control loop

    do {
        UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG); //Clear XT2,XT1,DCO fault flags
        SFRIFG1 &= ~OFIFG;                          //Clear fault flags
    } while (SFRIFG1 & OFIFG);

}

