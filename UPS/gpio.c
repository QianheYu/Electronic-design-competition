/*
 * gpio.c
 *
 *  Created on: 2020Äê10ÔÂ12ÈÕ
 *      Author: ASUS
 */
#include <gpio.h>

unsigned int flag = 0;
void GPIO_Init(void){
    P1DIR |= BIT2;
    P1SEL |= BIT2;

    P3DIR |= BIT5 + BIT6;
    P3SEL |= BIT5 + BIT6;

    P6SEL |= BIT0 + BIT1 + BIT2;
}

void Switch_Control(void){
	if (flag == 0 && ac1 < 2)
	{
		P1OUT &= ~BIT0;
		flag = 1;
	}
	else{
		P1OUT |= BIT0;
		flag = 0;
	}
    return flag;
}
