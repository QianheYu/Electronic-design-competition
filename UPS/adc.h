/*
 * adc.h
 *
 *  Created on: 2020Äê10ÔÂ12ÈÕ
 *      Author: ASUS
 */

#ifndef ADC_H_
#define ADC_H_

#include <system_config.h>

#define Accycle_num 3

void ADC_Init(void);
void CH0_Alternating_Operation(void);
void CH1_Alternating_Operation(void);
void CH2_Direct_Operation(void);

#endif /* ADC_H_ */
