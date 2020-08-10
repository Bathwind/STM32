#include "key.h"
#include "exti.h"
#include "delay.h"
void exti_init(void)
{
	  EXTI_InitTypeDef EXTI_Initstructure;
	  NVIC_InitTypeDef NVIC_Initstructure;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);//wk_up
	
	  EXTI_Initstructure.EXTI_Line = EXTI_Line0;
	  EXTI_Initstructure.EXTI_LineCmd = ENABLE;
	  EXTI_Initstructure.EXTI_Mode = EXTI_Mode_Interrupt;
	  EXTI_Initstructure.EXTI_Trigger = EXTI_Trigger_Falling;
	  EXTI_Init(&EXTI_Initstructure);

		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource3);//key2
	
	  EXTI_Initstructure.EXTI_Line = EXTI_Line3;
	  EXTI_Initstructure.EXTI_LineCmd = ENABLE;
	  EXTI_Initstructure.EXTI_Mode = EXTI_Mode_Interrupt;
	  EXTI_Initstructure.EXTI_Trigger = EXTI_Trigger_Falling;
	  EXTI_Init(&EXTI_Initstructure);
	
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);//key1
	
	  EXTI_Initstructure.EXTI_Line = EXTI_Line1;
	  EXTI_Initstructure.EXTI_LineCmd = ENABLE;
	  EXTI_Initstructure.EXTI_Mode = EXTI_Mode_Interrupt;
	  EXTI_Initstructure.EXTI_Trigger = EXTI_Trigger_Falling;
	  EXTI_Init(&EXTI_Initstructure);
	
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource2);//key0
	
	  EXTI_Initstructure.EXTI_Line = EXTI_Line2;
	  EXTI_Initstructure.EXTI_LineCmd = ENABLE;
	  EXTI_Initstructure.EXTI_Mode = EXTI_Mode_Interrupt;
	  EXTI_Initstructure.EXTI_Trigger = EXTI_Trigger_Falling;
	  EXTI_Init(&EXTI_Initstructure);
	
	  NVIC_Initstructure.NVIC_IRQChannel = EXTI0_IRQn;
	  NVIC_Initstructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority = 0;
	  NVIC_Initstructure.NVIC_IRQChannelSubPriority = 1;
	  NVIC_Init(&NVIC_Initstructure);	
		
		NVIC_Initstructure.NVIC_IRQChannel = EXTI1_IRQn;
	  NVIC_Initstructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority = 0;
	  NVIC_Initstructure.NVIC_IRQChannelSubPriority = 1;
	  NVIC_Init(&NVIC_Initstructure);	
		
		
		NVIC_Initstructure.NVIC_IRQChannel = EXTI2_IRQn;
	  NVIC_Initstructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority = 0;
	  NVIC_Initstructure.NVIC_IRQChannelSubPriority = 1;
	  NVIC_Init(&NVIC_Initstructure);	
		
		NVIC_Initstructure.NVIC_IRQChannel = EXTI3_IRQn;
	  NVIC_Initstructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority = 0;
	  NVIC_Initstructure.NVIC_IRQChannelSubPriority = 1;
	  NVIC_Init(&NVIC_Initstructure);	
}


