/*
 * pid.c
 *
 *  Created on: 2020年10月11日
 *      Author: ASUS
 */

#include "pid.h"
float Kp=1.1,Ki=0.01;

//-----闭环控制-----
float Speed_PI(int Encoder,int Target)
{
     static float Bias,Pwm,Last_bias,Bias_Integral;
     Bias=Target-Encoder;
     Bias_Integral +=Bias;
     Pwm+=Kp*(Bias-Last_bias)+Ki*Bias;   //增量式PI
//     Pwm=Kp*Bias+Bias_Integral*Ki;   //位置式PI
     Last_bias=Bias;                       //
     return Pwm;                         //
}


