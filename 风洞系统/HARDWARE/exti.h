#ifndef __exti_H
#define __exti_H
#include "sys.h"
void exti_init(void);//外部中断初始化
void Control_point(int n);//通过小球位置来确认当前pwm的占空比及其频率
extern u16 pwmlevel;//电机占空比 
extern int point;//光电管位置
#endif

