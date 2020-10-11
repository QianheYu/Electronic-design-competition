#ifndef SPWM_H_
#define SPWM_H_

extern unsigned int sin_table[SIN_NUM];
extern void PWM_TA_init(void);
extern void PWM_TB_init(void);
extern void Sin_Table(void);
extern void Timer0_B0_ISR(void);

#endif
