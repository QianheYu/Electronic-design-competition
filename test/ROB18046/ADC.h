#ifndef ADC_H_
#define ADC_H_

extern unsigned int index;
extern float Vpp_ac0;
extern float Vpp_ac1;
extern float Vpp_dc;

extern void ADC_Init(void);
extern void Vpp_AC0_Operation(void);
extern void Vpp_AC1_Operation(void);
extern void Vpp_DC_Operation(void);
extern void ADC12_ISR(void);

#endif
