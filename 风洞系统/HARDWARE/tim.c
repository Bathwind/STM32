#include "tim.h"
#include "exti.h"
#include "delay.h"
u32 Count = 0;//���붨ʱ��2���жϵĴ���
u32 t = 0;//��������������Ҫ��ʱ��
u32 risetime = 0;//С����������Ҫ��ʱ��
void tim2_init(u16 arr,u16 psc)
{
	 TIM_TimeBaseInitTypeDef  TIM_TimeBaseInit_strutrue;
   NVIC_InitTypeDef NVIC_Initstructre;
	
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
   
	 TIM_TimeBaseInit_strutrue.TIM_ClockDivision = 0;
	 TIM_TimeBaseInit_strutrue.TIM_CounterMode = TIM_CounterMode_Up;
	 TIM_TimeBaseInit_strutrue.TIM_Period = arr;
	 TIM_TimeBaseInit_strutrue.TIM_Prescaler = psc;
	 TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInit_strutrue);
   
	 NVIC_Initstructre.NVIC_IRQChannel = TIM2_IRQn;
	 NVIC_Initstructre.NVIC_IRQChannelCmd = ENABLE;
	 NVIC_Initstructre.NVIC_IRQChannelPreemptionPriority = 0;
	 NVIC_Initstructre.NVIC_IRQChannelSubPriority = 1;
	 NVIC_Init(&NVIC_Initstructre);
	
	 TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
}
void TIM2_IRQHandler(void)
{
	if(TIM_GetFlagStatus(TIM2,TIM_FLAG_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		Count++;
	}
	
}
u32 Get_tim2EchoTimer(void)
{
		u32 t2 = 0;
	  t2 = Count;                  //��Sת����US
	  t2 += TIM_GetCounter(TIM2);          
	  TIM2->CNT = 0;                       //��TIM2�����Ĵ����ļ���ֵ����
    return t2;
}
u32 Getball_time(void)//�õ�С�����������ʱ��
{
		risetime = Get_tim2EchoTimer();
    return risetime;
}

