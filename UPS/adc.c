/*
 * adc.c
 *
 *  Created on: 2020年10月12日
 *      Author: QianheYu
 */

#include <adc.h>
//volatile unsigned int results_0[256];
//volatile unsigned int results_1[256];
//volatile unsigned int results_2[256];
volatile unsigned int ch0_results[256];
volatile unsigned int ch1_results[256];
volatile unsigned int ch2_results[256];
volatile unsigned int Vpp_Table_Ac0[Vpp_num];
volatile unsigned int Vpp_Table_Ac1[Vpp_num];
float ac0;
float ac1;
float dc;
unsigned int count = 0;
//unsigned int alternat = 0;
//unsigned int direct = 0;
/**
 * ADC12初始化
 */
void ADC_Init(void)
{
    P6SEL |= BIT0 + BIT1 + BIT2;
    ADC12CTL0 = ADC12SHT0_8 + ADC12ON + ADC12MSC;
    ADC12CTL1 = ADC12SHP + ADC12CONSEQ_3 + ADC12SSEL_3;
    ADC12MCTL0 = ADC12INCH_0;
    ADC12MCTL1 = ADC12INCH_1;
    ADC12MCTL2 = ADC12INCH_2 + ADC12EOS;
    ADC12IE = ADC12IE2;

    ADC12CTL0 |= ADC12ENC;
}

/**
 * 遍历ADC读取结果找到峰峰值
 */
void CH0_Vpp_Operation(void)
{
    static unsigned char Vpp_cnt = 0;
    unsigned int j;
    unsigned int V_max = 0;
    unsigned int V_min = 0;
//    V_max = results_0[0];
    V_max = ch0_results[0];
//    V_min = results_0[0];
    V_min = ch1_results[0];
    for(j = 1;j <= 255;j++)
    {
//        if(results_0[j] > V_max)
//        {
//            V_max = results_0[j];
//        }
//        if(results_0[j] < V_min)
//        {
//            V_min = results_0[j];
//        }
        if(ch0_results[j] > V_max)
        {
                V_max = ch0_results[j];
        }
        if(ch0_results[j] < V_min)
        {
                V_min = ch0_results[j];
        }
    }
    Vpp_Table_Ac0[Vpp_cnt] = V_max - V_min;
    Vpp_cnt++;
    if(Vpp_cnt == Vpp_num)
    {
        unsigned int total = 0;
        unsigned int j;
        for(j = 0;j < Vpp_num;j++)
        {
            total = total + Vpp_Table_Ac0[j];
        }
        ac0 = (float) (total / Vpp_num * 3.3 / 4095);
        Vpp_cnt = 0;
    }
}

void CH1_Vpp_Operation(void)
{
    static unsigned char Vpp_cnt = 0;
    unsigned int k;
    unsigned int V_max = 0;
    unsigned int V_min = 0;
//    V_max = results_1[0];
//    V_min = results_1[0];
    V_max = ch1_results[0];
    V_min = ch1_results[0];
    for(k = 1;k <= 255;k++)
    {
//        if(results_1[k] > V_max)
//        {
//            V_max = results_1[k];
//        }
//        if(results_1[k] < V_min)
//        {
//            V_min = results_1[k];
//        }
        if(ch1_results[k] > V_max)
        {
            V_max = ch1_results[k];
        }
        if(ch1_results[k] < V_min)
        {
                V_min = ch1_results[k];
        }
    }
    Vpp_Table_Ac1[Vpp_cnt] = V_max - V_min;
    Vpp_cnt++;
    if(Vpp_cnt == Vpp_num)
    {
        unsigned int total = 0;
        unsigned int j;
        for(j = 0;j < Vpp_num;j++)
        {
            total = total + Vpp_Table_Ac1[j];
        }
        ac1 = (float) (total / Vpp_num * 3.3 / 4095);
        Vpp_cnt = 0;
    }
}

void CH2_Direct_Operation(void){

    static unsigned int i = 0;
    unsigned int j = 0;
    static unsigned long int sum[5];
    unsigned int average = 0;

    for(j = 0; j < 256; j++){
        sum[i] += ch2_results[j];
    }
    sum[i] = sum[i]/256;
    i++;
    if(i == 4){
        for(j = 1; j < i; j++){
            average += sum[j];
            sum[j] = 0;
        }
        i = 0;
        dc = (float)(average/3*3.3/4096);
        average = 0;
    }

}


#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
//    __enable_interrupt();
    static unsigned int count = 0;
    switch(ADC12IV)
    {
    case 10:
        ch0_results[count] = ADC12MEM0;
        ch1_results[count] = ADC12MEM1;
        ch2_results[count] = ADC12MEM2;
        count++;
        break;
    default:break;
    }
}


