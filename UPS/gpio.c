/*
 * gpio.c
 *
 *  Created on: 2020��10��12��
 *      Author: ASUS
 */
#include <gpio.h>

void GPIO_Init(){
    P1DIR |= BIT2;
    P1SEL |= BIT2;

    P3DIR |= BIT5 + BIT6;
    P3SEL |= BIT5 + BIT6;

    P6SEL |= BIT0 + BIT1 + BIT2;
}


