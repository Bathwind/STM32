#ifndef ___PID__H
#define ___PID__H

extern float Encoder;//当前高度，通过光电管得到高度
int Incremental_PI (float Encoder,int Target);
int myabs(int a);
void Xianfu_Pwm(void);
void Set_Pwm(int moto1);
int TIM2_IRQHandler(void);
#endif