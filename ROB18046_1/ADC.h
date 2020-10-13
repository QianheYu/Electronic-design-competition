#ifndef ADC_H_
#define ADC_H_

extern unsigned int index;

extern void ADC_Init(void);
extern void Vpp_AC0_Operation(void);
extern void Vpp_AC1_Operation(void);
void Direct_Operation(void);
extern void ADC12_ISR(void);

#endif
