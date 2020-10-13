# 代码说明

## 文件组织说明

本程序需输出PWM、SPWM波形，并使用ADC进行采样处理。

目录树按照外设的分类进行文件组织各外设所使用的宏定义均定义在其对应的头文件中，所有代码公用宏定义及包含文件定义在system_config.h文件中。

+ Project
  + system_config.h
  + main.c
  + clock.h
  + clock.c
  + gpio.h
  + gpio.c
  + timer.h
  + timer.c
  + adc.h
  + adc.c



## 主函数

主函数主要处理时钟和GPIO、定时器、ADC的初始化以及ADC采集数据的处理、触发ADC采样和输出状态切换。




## Clock模块
在该部分代码中使用XT2作为整个时钟系统的时钟源，通过FLL锁相环进行倍频使smock输出16MHz左右的时钟频率作为单片机运行的主频。



## GPIO模块

该模块用于对使用到的IO口进行初始化设置，如对Timer和ADC所用IO口进行初始化。
P3.5-6用于输出SPWM波，P1.2用于输出PWM波，P6.0-2用于ADC采样信号的输入， P1.0用继电器的控制。


## 定时器模块
该模块用于实现生成SPWM和PWM波的功能。其中使用TimerB生成两个相反的SPWM波，使用TimerA生成PWM波。其中SPWM的会根据PID算法调节占空比。

其中包括三部分代码TimerA０的初始化、TimerB０的初始化以及TimerB０的中断服务程序。TimerB０的中断时间将通过sin_table中的元素决定。
TimerA0和TimerB0均使用增模式，通过Tx0CCR0控制输出波形的周期，Tx0CCR1模式7控制占空比，另用TA0CCR2模式3生成反向的SPWM波。



## ADC模块

该模块包括以下功能，ADC的初始化，ADC采集数据的处理以及ADC中断服务程序用于读取采样数据，以实现闭环控制的输入。

ADC采样使用多通道连续采样模式，共使用3个通道进行采样其中0、1通道用于采集交流信号，2通道用于采集直流信号。
两个交流信号分别用于输出的SPWM做闭环控制和输入电源的检测，直流信号用于控制升压。



## PID模块

PID的代码实现采用增量式算法对处理后的采集数据进行运算，自动调整输出的SPWM、PWM波形。


