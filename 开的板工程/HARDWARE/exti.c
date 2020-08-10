#include "key.h"
#include "exti.h"
#include "delay.h"
void exti_init(void)
{
	  EXTI_InitTypeDef EXTI_Initstructure;
	  NVIC_InitTypeDef NVIC_Initstructure;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource8);//wk_up
	
	  EXTI_Initstructure.EXTI_Line = EXTI_Line8;
	  EXTI_Initstructure.EXTI_LineCmd = ENABLE;
	  EXTI_Initstructure.EXTI_Mode = EXTI_Mode_Interrupt;
	  EXTI_Initstructure.EXTI_Trigger = EXTI_Trigger_Falling;
	  EXTI_Init(&EXTI_Initstructure);

	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource7);//key1
	
	  EXTI_Initstructure.EXTI_Line = EXTI_Line7;
	  EXTI_Initstructure.EXTI_LineCmd = ENABLE;
	  EXTI_Initstructure.EXTI_Mode = EXTI_Mode_Interrupt;
	  EXTI_Initstructure.EXTI_Trigger = EXTI_Trigger_Falling;
	  EXTI_Init(&EXTI_Initstructure);
	
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource6);//key2
	
	  EXTI_Initstructure.EXTI_Line = EXTI_Line6;
	  EXTI_Initstructure.EXTI_LineCmd = ENABLE;
	  EXTI_Initstructure.EXTI_Mode = EXTI_Mode_Interrupt;
	  EXTI_Initstructure.EXTI_Trigger = EXTI_Trigger_Falling;
	  EXTI_Init(&EXTI_Initstructure);
	
	  NVIC_Initstructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	  NVIC_Initstructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority = 0;
	  NVIC_Initstructure.NVIC_IRQChannelSubPriority = 1;
	  NVIC_Init(&NVIC_Initstructure);	
}


