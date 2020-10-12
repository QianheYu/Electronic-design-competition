#include<MSP430F5529.h>
#include<variate_init.h>
#define POINT 256
volatile unsigned int results_0[256];
volatile unsigned int results_1[256];
volatile unsigned int results_2[256];
volatile unsigned int Vpp_Table_Ac0[Vpp_num];
volatile unsigned int Vpp_Table_Ac1[Vpp_num];
float Vpp_ac0;
float Vpp_ac1;
float Vpp_direct;
unsigned int alternat = 0;
unsigned int direct = 0;
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
void Vpp_AC0_Operation(void)
{
    static unsigned char Vpp_cnt = 0;
    unsigned int j;
    unsigned int V_max = 0;
    unsigned int V_min = 0;
    V_max = results_0[0];
    V_min = results_0[0];
    for(j = 1;j <= 255;j++)
    {
        if(results_0[j] > V_max)
        {
            V_max = results_0[j];
        }
        if(results_0[j] < V_min)
        {
            V_min = results_0[j];
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
        Vpp_ac0 = (float) (total / Vpp_num * 3.3 / 4095);
        Vpp_cnt = 0;
    }
}

void Vpp_AC1_Operation(void)
{
    static unsigned char Vpp_cnt = 0;
    unsigned int k;
    unsigned int V_max = 0;
    unsigned int V_min = 0;
    V_max = results_1[0];
    V_min = results_1[0];
    for(k = 1;k <= 255;k++)
    {
        if(results_1[k] > V_max)
        {
            V_max = results_1[k];
        }
        if(results_1[k] < V_min)
        {
            V_min = results_1[k];
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
        Vpp_ac1 = (float) (total / Vpp_num * 3.3 / 4095);
        Vpp_cnt = 0;
    }
}

void Direct_Operation(void){

    static unsigned int i = 0;
    unsigned int j = 0;
    static unsigned long int sum[5];
    unsigned int average = 0;

    for(j = 0; j < 256; j++){
        sum[i] += results_2[j];
    }
    sum[i] = sum[i]/256;
    i++;
    if(i == 4){
        for(j = 1; j < i; j++){
            average += sum[j];
            sum[j] = 0;
        }
        i = 0;
        Vpp_direct = (float)(average/3*3.3/4096);
        average = 0;
    }

}


#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
//    __enable_interrupt();
    switch(ADC12IV)
    {


    case 10:
        results_0[alternat] = ADC12MEM0;
        results_1[alternat] = ADC12MEM1;
        results_2[alternat] = ADC12MEM2;
        alternat++;
        break;

    default:break;
    }
}
