#ifndef __exti_H
#define __exti_H
#include "sys.h"
void exti_init(void);//�ⲿ�жϳ�ʼ��
void Control_point(int n);//ͨ��С��λ����ȷ�ϵ�ǰpwm��ռ�ձȼ���Ƶ��
extern u16 pwmlevel;//���ռ�ձ� 
extern int point;//����λ��
#endif

