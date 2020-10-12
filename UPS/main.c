//#include <system_config.h>
#include <msp430f5529.h>
#include <clock.h>
#include <gpio.h>
#include <timer.h>
#include <adc.h>
#include <math.h>

/**
 * main.c
 */
extern volatile unsigned int sin_table[SIN_POINT] = {};
extern float ac0;

void Sin_Tab(void)
{
    unsigned int i;
    float sine;
    float interval = 2 * 3.14159 / SIN_POINT;
//    float pidParameter = Speed_PI();
    for(i = 0; i < SIN_POINT; i++)
    {
//        sine = sin(i * interval)*0.9;
        float Proportion = (0.9 + Speed_PI(ac0, 1.5));
        if(Proportion > 1){
            Proportion = 1;
        }
        else if(Proportion < 0){
            Proportion = 0;
        }
        sine = sin(i*interval)*Proportion;
        sin_table[i] = (unsigned int) ((1 + sine) * TB_PERIOD / 2);
    }
}

int main(void)
{
//	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	Clock_Init();
//	GPIO_Init();


	return 0;
}
