#include "tim.h"
#include "exti.h"
#include "delay.h"
#include "oled.h"
#include "phototube.h"

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



