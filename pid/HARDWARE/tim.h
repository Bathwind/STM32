#ifndef _tim_H
#define _tim_H
#include "sys.h"

void tim2_init(u16 arr,u16 psc);//��ʱ��2��ʼ��
u32 Get_tim2EchoTimer(void);//�õ���ʱ��2��ǰ������ʱ��
u32 Getball_time(void);//�õ�С��������ʱ��
extern u32 Count;//С����붨ʱ���жϵĴ���
extern u32 risetime;//С��������ʱ��

#endif


