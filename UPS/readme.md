# 代码说明

## 主函数
主函数主要处理时钟和定时器、ADC的初始化以及ADC采集数据的处理。


## Clock模块
在该部分代码中使用smosc

## 定时器模块
该模块用于生成SPWM和PWM波。其中使用TimerB生成两个相反的SPWM波，使用TimerB生成PWM波。其中SPWM的会根据PID算法自动调节占空比。



## PID模块

PID的代码实现采用增量式


