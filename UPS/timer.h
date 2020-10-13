/*
 * timer.h
 *
 *  Created on: 2020Äê10ÔÂ12ÈÕ
 *      Author: ASUS
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <system_config.h>

#define TA_PERIOD 320
#define TA_PERCENT 192

#define TB_PERIOD 3200
#define TB_PERCENT 1600

#define SIN_POINT 100

void TimerA_Init(void);
void TimerB_Init(void);

#endif /* TIMER_H_ */
