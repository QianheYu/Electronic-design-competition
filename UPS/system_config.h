/*
 * system_config.h
 *
 *  Created on: 2020Äê10ÔÂ12ÈÕ
 *      Author: ASUS
 */

#ifndef SYSTEM_CONFIG_H_
#define SYSTEM_CONFIG_H_


#define PWM12_SET P1DIR |= BIT2;P1SEL |= BIT2;
//#define PWM13_SET P1DIR |= BIT3;P1SEL |= BIT3;
//#define PWM14_SET P1DIR |= BIT4;P1SEL |= BIT4;
//#define PWM15_SET P1DIR |= BIT5;P1SEL |= BIT5;
//#define PWM74_SET P7DIR |= BIT4;P7SEL |= BIT4;
#define PWM35_SET P3DIR |= BIT5;P3SEL |= BIT5;
#define PWM36_SET P3DIR |= BIT6;P3SEL |= BIT6;

#define Percent12 192
//#define Percent13 1650
//#define Percent14 1650
//#define Percent15 1650
#define Period_A 320

//#define Percent74 1600
#define Percent35 1600
#define Percent36 1600
#define Period_B 3200

#define SIN_NUM 100

#define Vpp_num 3

#define SetValue 1.5


#endif /* SYSTEM_CONFIG_H_ */
