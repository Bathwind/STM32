#ifndef ___PID__H
#define ___PID__H

extern float Encoder;//��ǰ�߶ȣ�ͨ�����ܵõ��߶�
int Incremental_PI (float Encoder,int Target);
int myabs(int a);
void Xianfu_Pwm(void);
void Set_Pwm(int moto1);
int TIM2_IRQHandler(void);
#endif