#include<MSP430F5529.h>
#include<variate_init.h>
#include<ADC.h>
#include<SPWM.h>

#define SetValue 1.6
#define SetValue_S 0.98

extern float Vpp_ac0;
extern float Vpp_dc;
extern unsigned int s;

float K = 0;
float Kp = 0.008;
float Ki = 0.03;
float ErrorP = 0;
float ErrorI = 0;

float K_S = 0;
float Kp_S = 0.001;
float Ki_S = 0.003;
float ErrorP_S = 0;
float ErrorI_S = 0;

void PID_SPWM(void)
{
    ErrorP_S = SetValue_S - Vpp_ac0;
    ErrorI_S = ErrorP_S + ErrorI_S;
    K_S = Kp_S * ErrorP_S + Ki_S * ErrorI_S;
}

void Ac_Spwm(void)
{
    PID_SPWM();
    if(K_S < 0)
    {
        K_S = 0;
    }
    else if(K_S > 0.3)
    {
        K_S = 0.3;
    }
    Sin_Table();
}

void PID_PWM(void)
{
    ErrorP = SetValue - Vpp_dc;
    ErrorI = ErrorP + ErrorI;
    K = Kp * ErrorP + Ki * ErrorI;
}

void Dc_Pwm(void)
{
    PID_PWM();
    if(K < 0)
    {
        K = 0;
    }
    else if(K > 0.49)
    {
        K = 0.49;
    }
    TA0CCR1 = Period_A * (0.01 + K);
}

void Dc_Pwm_Open(void)
{
    if(s == 0)
    {
        if(Vpp_dc > 1.2)
        {
            TA0CCR1 = Period_A * 0.05;
        }
        else if(Vpp_dc > 1.1)
        {
            TA0CCR1 = Period_A * 0.2;
        }
        else
        {
            TA0CCR1 = Period_A * 0.36;
        }
    }
    else
    {
        TA0CCR1 = Period_A * 0.5;
    }

}

void Exsist_Test(void)
{
    static unsigned int et = 0;
    static float TOTAL = 0;
    TOTAL += Vpp_ac1;
    et++;
    if(et == 10)
    {
        if(TOTAL > 2)
        {
            P1OUT &= ~BIT0;
            s = 0;
        }
        else
        {
            P1OUT |= BIT0;
            s = 1;
        }
        TOTAL = 0;
        et = 0;
    }

}
