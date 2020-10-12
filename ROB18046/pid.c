/*
 * pid.c
 *
 *  Created on: 2020��10��11��
 *      Author: ASUS
 */

#include "pid.h"
float Kp=1.1,Ki=0.01;

//-----�ջ�����-----
float Speed_PI(int Encoder,int Target)
{
     static float Bias,Pwm,Last_bias,Bias_Integral;
     Bias=Target-Encoder;
     Bias_Integral +=Bias;
     Pwm+=Kp*(Bias-Last_bias)+Ki*Bias;   //����ʽPI
//     Pwm=Kp*Bias+Bias_Integral*Ki;   //λ��ʽPI
     Last_bias=Bias;                       //
     return Pwm;                         //
}


