#include "tim.h"
#include "delay.h"
#include "oled.h"
void tim1_init(u16 arr,u16 psc)
{
	 TIM_TimeBaseInitTypeDef  TIM_TimeBaseInit_strutrue;
   NVIC_InitTypeDef NVIC_Initstructre;
	
	 RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
   
	 TIM_TimeBaseInit_strutrue.TIM_ClockDivision = 0;
	 TIM_TimeBaseInit_strutrue.TIM_CounterMode = TIM_CounterMode_Up;
	 TIM_TimeBaseInit_strutrue.TIM_Period = arr;
	 TIM_TimeBaseInit_strutrue.TIM_Prescaler = psc;
	 TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInit_strutrue);
   
	 NVIC_Initstructre.NVIC_IRQChannel = TIM1_IRQn;
	 NVIC_Initstructre.NVIC_IRQChannelCmd = ENABLE;
	 NVIC_Initstructre.NVIC_IRQChannelPreemptionPriority = 0;
	 NVIC_Initstructre.NVIC_IRQChannelSubPriority = 1;
	 NVIC_Init(&NVIC_Initstructre);
	
	 TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
		
	 TIM_Cmd(TIM1,ENABLE);
}



