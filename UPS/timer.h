/*
 * timer.h
 *
 *  Created on: 2020Äê10ÔÂ12ÈÕ
 *      Author: ASUS
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <msp430f5529.h>

#define TA_Period 320
#define TA_Percent 192

#define TB_Period 3200
#define TB_Percent 1600

void TimerA_init(void);
void TimerB_init(void);

#endif /* TIMER_H_ */
