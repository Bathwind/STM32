#include "exti.h"
#include "delay.h"
#include "pwm.h"
#include "key.h"
#include "fan.h"
#include "stm32f10x.h"
#include "phototube.h"
#include "tim.h"
#include "usart.h"
#include "oled.h"
u16 pwmlevel = 0;//风机占空比 
int ballflag = 0;//确定小球上升点的标志
int point;//用来确认上升到哪个点，n冲0开始依次是第一个光电管，第二个光电管。
void exti_init(void)
{
 
 	  EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟

	  KEY_Init();//初始化按键对应io模式

    //GPIOC.5 中断线以及中断初始化配置
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource9);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line9;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器 
	
    //GPIOA.15	  中断线以及中断初始化配置
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line15;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
    
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource6);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line6;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  
		
    //GPIOA.0	  中断线以及中断初始化配置
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);

   	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


 
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
 
 
   	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
 
}

 
void EXTI0_IRQHandler(void)
{
  delay_ms(10);    //消抖
	if(WK_UP==1)
	{	  
		pwmlevel+=20;
	  TIM_SetCompare1(TIM1,pwmlevel);
	}
	EXTI_ClearITPendingBit(EXTI_Line0);  //清除EXTI0线路挂起位
}
void EXTI9_5_IRQHandler(void)
{			 
  if(EXTI_GetITStatus(EXTI_Line6)!=RESET)//判断某个线上的中断是否发生
  { 
     EXTI_ClearITPendingBit(EXTI_Line6); //清除 LINE 上的中断标志位
     if(tube7 == 0&&point == 3)//用来控制风扇将转速降低到达第三个光电管
		{
			led1 = 0;
			TIM_SetCompare1(TIM1,254);
		}
		  if(tube7 == 0&&point == 1)//用来控制风扇将转速降低到达第一个光电管
		{
			led1 = 0;
			TIM_SetCompare1(TIM1,294);
		}
		 if(tube7 == 0&&point == 2)//用来控制风扇将转速降低到达第二个光电管
		{
			led1 = 0;
			TIM_SetCompare1(TIM1,265);
		}
		if(tube7 == 0&&point == 4)//用来控制风扇将转速降低到达第四个光电管
		{
			led1 = 0;
			TIM_SetCompare1(TIM1,245);
		}
		if(tube7 == 0&&point == 5)//用来控制风扇将转速降低到达第五个光电管
		{
			led1 = 0;
			TIM_SetCompare1(TIM1,240);
		}
		if(tube7 == 0&&point == 6)//用来控制风扇将转速降低到达第六个光电管
		{
			led1 = 0;
			TIM_SetCompare1(TIM1,238);
		}
  }	
	if(EXTI_GetITStatus(EXTI_Line9)!=RESET)//判断某个线上的中断是否发生
  { 
     EXTI_ClearITPendingBit(EXTI_Line9); //清除 LINE 上的中断标志位
		 delay_ms(10);//消抖		
     if(tube10 == 0&&p9-oint == 7)
		 {
			led1 = 0;
			TIM_SetCompare1(TIM1,230);
			 if(tube11 == 0)
			 {
				 led1 = 1;
			   TIM_SetCompare1(TIM1,230);
			 }
		 }
  }
	if(EXTI_GetITStatus(EXTI_Line5)!=RESET)//判断某个线上的中断是否发生
  { 
     EXTI_ClearITPendingBit(EXTI_Line5); //清除 LINE 上的中断标志位
		 delay_ms(10);//消抖		
     if(KEY0==0)
 	   {
		   Control_point(point);//控制小球到达的位置也就是第几个光电管
	   }
  }
}
void EXTI15_10_IRQHandler(void)
{
  delay_ms(10);    //消抖			 
  if(KEY1==0)	
	{
		point++;
	}
	 EXTI_ClearITPendingBit(EXTI_Line15);  //清除LINE15线路挂起位
}
void Control_point(int n)
{
		switch(n)
		{
			case 1:
				TIM_SetCompare1(TIM1,300);break;//到达第一个光电管	 
			case 2:
 				TIM_SetCompare1(TIM1,300);break;//到达第二个光电管	            
			case 3:
 				TIM_SetCompare1(TIM1,300);break;//到达第三个光电管	 
			case 4:
				TIM_SetCompare1(TIM1,300);break;//到达第四个光电管
			case 5:
 				TIM_SetCompare1(TIM1,300);break;//到达第五个光电管
			case 6:
 				TIM_SetCompare1(TIM1,284);break;//到达第六个光电管
			case 7:
 				TIM_SetCompare1(TIM1,284);break;//到达第七个光电管
    }
}