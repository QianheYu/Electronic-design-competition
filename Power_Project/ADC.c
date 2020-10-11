#include<MSP430F5529.h>
#include<variate_init.h>
#include<PI_PWM.h>

volatile unsigned int results[256];
volatile unsigned int results0[256];
volatile unsigned int results1[256];
volatile unsigned int Vpp_DC0[Vpp_num];
volatile unsigned int Vpp_DC1[Vpp_num];
volatile unsigned int Vpp_AC[Vpp_num];
float Vpp_dc0;
float Vpp_dc1;
float Vpp_ac;


void ADC_init(void)
{
    P6SEL |= BIT0 + BIT1;
    ADC12CTL0 = ADC12SHT0_8 + ADC12ON + ADC12MSC;
    ADC12CTL1 = ADC12SHP + ADC12CONSEQ_3 + ADC12SSEL_3;
    ADC12MCTL0 = ADC12INCH_0;
    ADC12MCTL1 = ADC12INCH_1 + ADC12EOS;
    ADC12IE = 0x02;

    ADC12CTL0 |= ADC12ENC;
}

void Vpp_DC0_Operation(void)
{
    static unsigned char Vpp_cnt0 = 0;
    unsigned int t;
    unsigned long int Results_All0 = 0;
    for(t = 0;t <= 255;t++)
    {
        Results_All0 = Results_All0 + results0[t];
    }
    Vpp_DC0[Vpp_cnt0] = Results_All0 / 256;
    Vpp_cnt0++;
    if(Vpp_cnt0 == Vpp_num)
    {
        unsigned int total = 0;
        unsigned int j;
        for(j = 0;j < Vpp_num;j++)
        {
            total = total + Vpp_DC0[j];
        }
        Vpp_dc0 = (float) (total / Vpp_num * 3.3 / 4095);
        Vpp_cnt0 = 0;
//        Dc_Pwm();
    }
}

void Vpp_DC1_Operation(void)
{
    static unsigned char Vpp_cnt1 = 0;
    unsigned int tt;
    unsigned long int Results_All1 = 0;
    for(tt = 0;tt <= 255;tt++)
    {
        Results_All1 = Results_All1 + results1[tt];
    }
    Vpp_DC1[Vpp_cnt1] = Results_All1 / 256;
    Vpp_cnt1++;
    if(Vpp_cnt1 == Vpp_num)
    {
        unsigned int total = 0;
        unsigned int jj;
        for(jj = 0;jj < Vpp_num;jj++)
        {
            total = total + Vpp_DC1[jj];
        }
        Vpp_dc1 = (float) (total / Vpp_num * 3.3 / 4095);
        Vpp_cnt1 = 0;
//        Dc_Pwm();
    }
}

void Vpp_AC_Operation(void)
{
    static unsigned char Vpp_cnt = 0;
    unsigned int t;
    unsigned int V_max = 0;
    unsigned int V_min = 0;
    V_max = results[0];
    V_min = results[0];
    for(t = 1;t <= 255;t++)
    {
        if(results[t] > V_max)
        {
            V_max = results[t];
        }
        if(results[t] < V_min)
        {
            V_min = results[t];
        }
    }
    Vpp_AC[Vpp_cnt] = V_max - V_min;
    Vpp_cnt++;
    if(Vpp_cnt == Vpp_num)
    {
        unsigned int total = 0;
        unsigned int j;
        for(j = 0;j < Vpp_num;j++)
        {
            total = total + Vpp_AC[j];
        }
        Vpp_ac = (float) (total / Vpp_num * 3.3 / 4095);
        Vpp_cnt = 0;
        Ac_Pwm();
    }
}
