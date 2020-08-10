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
u16 pwmlevel = 0;//���ռ�ձ� 
int ballflag = 0;//ȷ��С��������ı�־
int point;//����ȷ���������ĸ��㣬n��0��ʼ�����ǵ�һ�����ܣ��ڶ������ܡ�
void exti_init(void)
{
 
 	  EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//�ⲿ�жϣ���Ҫʹ��AFIOʱ��

	  KEY_Init();//��ʼ��������Ӧioģʽ

    //GPIOC.5 �ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource9);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line9;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ��� 
	
    //GPIOA.15	  �ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line15;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
    
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource6);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line6;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  
		
    //GPIOA.0	  �ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);

   	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


 
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
 
 
   	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
 
}

 
void EXTI0_IRQHandler(void)
{
  delay_ms(10);    //����
	if(WK_UP==1)
	{	  
		pwmlevel+=20;
	  TIM_SetCompare1(TIM1,pwmlevel);
	}
	EXTI_ClearITPendingBit(EXTI_Line0);  //���EXTI0��·����λ
}
void EXTI9_5_IRQHandler(void)
{			 
  if(EXTI_GetITStatus(EXTI_Line6)!=RESET)//�ж�ĳ�����ϵ��ж��Ƿ���
  { 
     EXTI_ClearITPendingBit(EXTI_Line6); //��� LINE �ϵ��жϱ�־λ
     if(tube7 == 0&&point == 3)//�������Ʒ��Ƚ�ת�ٽ��͵������������
		{
			led1 = 0;
			TIM_SetCompare1(TIM1,254);
		}
		  if(tube7 == 0&&point == 1)//�������Ʒ��Ƚ�ת�ٽ��͵����һ������
		{
			led1 = 0;
			TIM_SetCompare1(TIM1,294);
		}
		 if(tube7 == 0&&point == 2)//�������Ʒ��Ƚ�ת�ٽ��͵���ڶ�������
		{
			led1 = 0;
			TIM_SetCompare1(TIM1,265);
		}
		if(tube7 == 0&&point == 4)//�������Ʒ��Ƚ�ת�ٽ��͵�����ĸ�����
		{
			led1 = 0;
			TIM_SetCompare1(TIM1,245);
		}
		if(tube7 == 0&&point == 5)//�������Ʒ��Ƚ�ת�ٽ��͵�����������
		{
			led1 = 0;
			TIM_SetCompare1(TIM1,240);
		}
		if(tube7 == 0&&point == 6)//�������Ʒ��Ƚ�ת�ٽ��͵������������
		{
			led1 = 0;
			TIM_SetCompare1(TIM1,238);
		}
  }	
	if(EXTI_GetITStatus(EXTI_Line9)!=RESET)//�ж�ĳ�����ϵ��ж��Ƿ���
  { 
     EXTI_ClearITPendingBit(EXTI_Line9); //��� LINE �ϵ��жϱ�־λ
		 delay_ms(10);//����		
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
	if(EXTI_GetITStatus(EXTI_Line5)!=RESET)//�ж�ĳ�����ϵ��ж��Ƿ���
  { 
     EXTI_ClearITPendingBit(EXTI_Line5); //��� LINE �ϵ��жϱ�־λ
		 delay_ms(10);//����		
     if(KEY0==0)
 	   {
		   Control_point(point);//����С�򵽴��λ��Ҳ���ǵڼ�������
	   }
  }
}
void EXTI15_10_IRQHandler(void)
{
  delay_ms(10);    //����			 
  if(KEY1==0)	
	{
		point++;
	}
	 EXTI_ClearITPendingBit(EXTI_Line15);  //���LINE15��·����λ
}
void Control_point(int n)
{
		switch(n)
		{
			case 1:
				TIM_SetCompare1(TIM1,300);break;//�����һ������	 
			case 2:
 				TIM_SetCompare1(TIM1,300);break;//����ڶ�������	            
			case 3:
 				TIM_SetCompare1(TIM1,300);break;//�������������	 
			case 4:
				TIM_SetCompare1(TIM1,300);break;//������ĸ�����
			case 5:
 				TIM_SetCompare1(TIM1,300);break;//������������
			case 6:
 				TIM_SetCompare1(TIM1,284);break;//�������������
			case 7:
 				TIM_SetCompare1(TIM1,284);break;//������߸�����
    }
}