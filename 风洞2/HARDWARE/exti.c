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
int a;
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

	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource11);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line11;
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
    
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource3);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
		
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource9);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line9;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource7);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource6);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line6;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  
		
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource12);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line12;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	
		
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource3);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line6;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  
		
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource4);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
 
		NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
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
	EXTI_ClearITPendingBit(EXTI_Line0);  //���EXTI0��·����λ
}
void EXTI4_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line4);  //���EXTI0��·����λ
	if(tube14 == 0&&point == 13)
	{
		led1 = 0;
		TIM_SetCompare1(TIM1,246);
	}
}
void EXTI2_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line2);  //���EXTI0��·����λ
	
}
void EXTI3_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line3);  //���EXTI0��·����λ
}
void EXTI9_5_IRQHandler(void)
{			 
  if(EXTI_GetITStatus(EXTI_Line6)!=RESET)//�ж�ĳ�����ϵ��ж��Ƿ���
  { 
     EXTI_ClearITPendingBit(EXTI_Line6); //��� LINE �ϵ��жϱ�־λ
  }	
  if(EXTI_GetITStatus(EXTI_Line9)!=RESET)//�ж�ĳ�����ϵ��ж��Ƿ���
  { 
     EXTI_ClearITPendingBit(EXTI_Line9); //��� LINE �ϵ��жϱ�־λ
     if(tube12 == 0&&point == 9)
		 {
				led1 = 0;
			  TIM_SetCompare1(TIM1,245);
		 }
		  if(tube12 == 0&&point == 8)
		 {
				led1 = 0;
			  TIM_SetCompare1(TIM1,250);
		 }
		  if(tube12 == 0&&point == 10)
		 {
				led1 = 0;
			  TIM_SetCompare1(TIM1,245);
		 }
  }	
	if(EXTI_GetITStatus(EXTI_Line5)!=RESET)//�ж�ĳ�����ϵ��ж��Ƿ���
  { 
     EXTI_ClearITPendingBit(EXTI_Line5); //��� LINE �ϵ��жϱ�־λ
		 delay_ms(10);//����		
    
  }
	if(EXTI_GetITStatus(EXTI_Line7)!=RESET)//�ж�ĳ�����ϵ��ж��Ƿ���
  { 
     EXTI_ClearITPendingBit(EXTI_Line7); //��� LINE �ϵ��жϱ�־λ		 
  }
}
void EXTI15_10_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line15)!=RESET)//�ж�ĳ�����ϵ��ж��Ƿ���
  { 
     EXTI_ClearITPendingBit(EXTI_Line15); //��� LINE �ϵ��жϱ�־λ		
    
  }
	 if(EXTI_GetITStatus(EXTI_Line10)!=RESET)//�ж�ĳ�����ϵ��ж��Ƿ���
  { 
     EXTI_ClearITPendingBit(EXTI_Line10); //��� LINE �ϵ��жϱ�־λ

  }
	 if(EXTI_GetITStatus(EXTI_Line11)!=RESET)//�ж�ĳ�����ϵ��ж��Ƿ���
  { 
     EXTI_ClearITPendingBit(EXTI_Line11); //��� LINE �ϵ��жϱ�־λ
			 if(tube7 == 0&&point == 3)//�������Ʒ��Ƚ�ת�ٽ��͵������������
		   {
			  led1 = 0;
			  TIM_SetCompare1(TIM1,255);
		   }
		  if(tube7 == 0&&point == 1)//�������Ʒ��Ƚ�ת�ٽ��͵����һ������
		  {
			 led1 = 0;
			 TIM_SetCompare1(TIM1,294);
		  }
		  if(tube7 == 0&&point == 2)//�������Ʒ��Ƚ�ת�ٽ��͵���ڶ�������
		  {
			 led1 = 0;
			 TIM_SetCompare1(TIM1,264);
		  }
		  if(tube7 == 0&&point == 4)//�������Ʒ��Ƚ�ת�ٽ��͵�����ĸ�����
		 {
			 led1 = 0;
			 TIM_SetCompare1(TIM1,240);
		 }
		 if(tube7 == 0&&point == 5)//�������Ʒ��Ƚ�ת�ٽ��͵�����������
		 {
			led1 = 0;
			TIM_SetCompare1(TIM1,239);
		 }
		 if(tube7 == 0&&point == 6)//�������Ʒ��Ƚ�ת�ٽ��͵������������
		 {
			led1 = 0;
			TIM_SetCompare1(TIM1,230);
		 }
		 if(tube7 == 0&&point == 7)//�������Ʒ��Ƚ�ת�ٽ��͵����7������
		 {
			led1 = 0;
			TIM_SetCompare1(TIM1,225);
		 }
  }
		if(EXTI_GetITStatus(EXTI_Line12)!=RESET)//�ж�ĳ�����ϵ��ж��Ƿ���
  { 
     EXTI_ClearITPendingBit(EXTI_Line12); //��� LINE �ϵ��жϱ�־λ		 
     if(tube8 == 0 && point == 7)
		 {
				led1 = 1;
			  TIM_SetCompare1(TIM1,260);
		 }
		  if(tube8 == 0 && point == 6)
		 {
				led1 = 1;
			  TIM_SetCompare1(TIM1,260);
		 }
  }
}
void EXTI1_IRQHandler(void)
{
  delay_ms(10);    //����			 
	EXTI_ClearITPendingBit(EXTI_Line1);  //���LINE15��·����λ

}
void Control_point(int n)
{
		switch(n)
		{
			case 1:
				TIM_SetCompare1(TIM1,320);break;//�����һ������	 
			case 2:
 				TIM_SetCompare1(TIM1,300);break;//����ڶ�������	            
			case 3:
 				TIM_SetCompare1(TIM1,320);break;//�������������	 
			case 4:
				TIM_SetCompare1(TIM1,320);break;//������ĸ�����
			case 5:
 				TIM_SetCompare1(TIM1,290);break;//������������
			case 6:
 				TIM_SetCompare1(TIM1,266);break;//�������������
			case 7:
 				TIM_SetCompare1(TIM1,284);break;//������߸�����
			case 8:
				TIM_SetCompare1(TIM1,280);break;//����ڰ˸�����
			case 9:
 				TIM_SetCompare1(TIM1,280);break;//����ھŸ�����            
			case 10:
 				TIM_SetCompare1(TIM1,280);break;//�����ʮ������
			case 11:
				TIM_SetCompare1(TIM1,280);break;//�����ʮһ������
			case 12:
 				TIM_SetCompare1(TIM1,280);break;//�����ʮ��������
			case 13:
 				TIM_SetCompare1(TIM1,300);break;//�����ʮ��������
			case 14:
 				TIM_SetCompare1(TIM1,284);break;//�����ʮ�ĸ�����
    }
}