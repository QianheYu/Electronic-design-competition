#include <system_config.h>
#include <clock.h>
#include <gpio.h>
#include <timer.h>
#include <adc.h>
#include <math.h>

/**
 * main.c
 */
extern volatile unsigned int sin_table[SIN_POINT];
extern float ac0;
extern float ac1;
extern unsigned int count;
void Sin_Tab(void)
{
    unsigned int i;
    float sine;
    float interval = 2 * 3.14159 / SIN_POINT;

    float Proportion = 0.9;
//    float Proportion = (0.9 + Speed_PI(ac0, 1.5));
    if(Proportion > 1){
        Proportion = 1;
    }
    else if(Proportion < 0){
        Proportion = 0;
    }
    for(i = 0; i < SIN_POINT; i++)
    {
        sine = sin(i * interval)*0.9;

//        sine = sin(i*interval)*Proportion;
        sin_table[i] = (unsigned int) ((1 + sine) * TB_PERIOD / 2);
    }
}

void main(void)
{
//	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	Clock_Init();
	GPIO_Init();
	
	TimerA_Init();
	TimerB_Init();
	ADC_Init();

	__enable_interrupt();

	while(1){
	    if (Switch_Control() == 1)
		{
			TA0CCTL0 |= CCIE;
		}
		else
		{
			TA0CCTL0 &= ~CCIE;
		}
		Sin_Tab();
		ADC12CTL0 |= ADC12SC;
	    if(count == 256){
	        CH0_Alternating_Operation();
	        CH1_Alternating_Operation();
	        CH2_Direct_Operation();
	        count = 0;
	    }
	}
}
