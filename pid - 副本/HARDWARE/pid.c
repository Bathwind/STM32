#include "pid.h"
#include "tim.h"
#include "pwm.h"
#include "exti.h"
#include "phototube.h"
#include "usart.h"
#include "fan.h"
int Target_height=15;  //�趨Ŀ��߶�
float Encoder;//��ǰ�߶ȣ�ͨ�����ܵõ��߶�
int Moto1;//ͨ�����ڵõ���ռ�ձ�
int TIM2_IRQHandler(void)
{
	if(TIM_GetFlagStatus(TIM2,TIM_FLAG_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		Moto1=Incremental_PI(Encoder,Target_height);           //===�߶�PI������
	  Xianfu_Pwm();                                            //===PWM�޷�
    Set_Pwm(Moto1);                                          //===��ֵ��PWM�Ĵ��� 
	}
	return 0;
}
/**************************************************************************
�������ܣ���ֵ��PWM�Ĵ���
��ڲ�����PWM
����  ֵ����
**************************************************************************/
void Set_Pwm(int moto1)
{
		TIM_SetCompare1(TIM1,moto1);
}

/**************************************************************************
�������ܣ�����PWM��ֵ 
��ڲ�������
����  ֵ����
**************************************************************************/
void Xianfu_Pwm(void)
{	
	  int Amplitude=7100;    //===PWM������7200 ������7100
    if(Moto1<-Amplitude) Moto1=-Amplitude;	
		if(Moto1>Amplitude)  Moto1=Amplitude;	
}

/**************************************************************************
�������ܣ�����ֵ����
��ڲ�����int
����  ֵ��unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
/**************************************************************************
�������ܣ�����PI������
��ڲ�������ǰ�߶ȣ�Ŀ��߶�
����  ֵ�����PWM
��������ʽ��ɢPID��ʽ 
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)������ƫ�� 
e(k-1)������һ�ε�ƫ��  �Դ����� 
pwm�����������
�����ǵ��ٶȿ��Ʊջ�ϵͳ���棬ֻʹ��PI����
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)
**************************************************************************/
int Incremental_PI (float Encoder,int Target)
{ 	
   float Kp=20,Ki=0;	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                //����ƫ��
	 Pwm+=Kp*(Bias-Last_bias)+Ki*Bias;   //����ʽPI������
	 Last_bias=Bias;	                   //������һ��ƫ�� 
	 return Pwm;                         //�������
}
void EXTI0_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line0);  //���EXTI0��·�����
	if(tube1 == 0)
	{
	  Encoder = 0;
	
	}
}
void EXTI1_IRQHandler(void)
{
  delay_ms(10);    //����			 
	EXTI_ClearITPendingBit(EXTI_Line1);  //���LINE15��·����λ
  if(tube2 == 0)
	{
	  Encoder = 2.5;
	
	}
}
void EXTI9_5_IRQHandler(void)
{			 
  if(EXTI_GetITStatus(EXTI_Line6)!=RESET)//�ж�ĳ�����ϵ��ж��Ƿ���
  { 
     EXTI_ClearITPendingBit(EXTI_Line6); //��� LINE �ϵ��жϱ�־λ
     if(tube4 == 0)
		 {
		   Encoder = 7.5;
	
		 }
	}	
  if(EXTI_GetITStatus(EXTI_Line9)!=RESET)//�ж�ĳ�����ϵ��ж��Ƿ���
  { 
     EXTI_ClearITPendingBit(EXTI_Line9); //��� LINE �ϵ��жϱ�־λ
		 if(tube12 == 0)
	  {
	    Encoder = 27.5;
		
	  }	
  }	
	if(EXTI_GetITStatus(EXTI_Line5)!=RESET)//�ж�ĳ�����ϵ��ж��Ƿ���
  { 
     EXTI_ClearITPendingBit(EXTI_Line5); //��� LINE �ϵ��жϱ�־λ	
     if(tube3 == 0)
	  {
	   Encoder = 5;

	  }
  }
	if(EXTI_GetITStatus(EXTI_Line7)!=RESET)//�ж�ĳ�����ϵ��ж��Ƿ���
  { 
     EXTI_ClearITPendingBit(EXTI_Line7); //��� LINE �ϵ��жϱ�־λ	
     if(tube5 == 0)
	  {
	   Encoder = 10;
	
	  }		
  }
	if(EXTI_GetITStatus(EXTI_Line8)!=RESET)//�ж�ĳ�����ϵ��ж��Ƿ���
  { 
     EXTI_ClearITPendingBit(EXTI_Line8); //��� LINE �ϵ��жϱ�־λ	
     if(tube11 == 0)
	  {
			led1 = 0;
	   Encoder = 25 ;

	  }		
  }
}
void EXTI4_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line4);  
   if(tube14 == 0)
	 {
	   Encoder = 32.5;
		  
	 }	
}
void EXTI3_IRQHandler(void)
{  
  if(EXTI_GetITStatus(EXTI_Line3)!=RESET)//�ж�ĳ�����ϵ��ж��Ƿ���
  { 
     EXTI_ClearITPendingBit(EXTI_Line3); //��� LINE �ϵ��жϱ�־λ	
			led1 = 0;
	    Encoder = 30;
	
	 	
  }	
}

void EXTI15_10_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line15)!=RESET)//�ж�ĳ�����ϵ��ж��Ƿ���
  { 
     EXTI_ClearITPendingBit(EXTI_Line15); //��� LINE �ϵ��жϱ�־λ		
     if(tube9 == 0)
	  {
	   Encoder = 20;
		
	  }
  }
	if(EXTI_GetITStatus(EXTI_Line13)!=RESET)//�ж�ĳ�����ϵ��ж��Ƿ���
  { 
     EXTI_ClearITPendingBit(EXTI_Line13); //��� LINE �ϵ��жϱ�־λ		
     if(tube9 == 0)
	  {
	   Encoder = 20.0;
	
	  }
  }
	if(EXTI_GetITStatus(EXTI_Line14)!=RESET)//�ж�ĳ�����ϵ��ж��Ƿ���
  { 
     EXTI_ClearITPendingBit(EXTI_Line14); //��� LINE �ϵ��жϱ�־λ		
     if(tube10 == 0)
	  {
	    Encoder = 22.5;
	
	  }
  }
	if(EXTI_GetITStatus(EXTI_Line10)!=RESET)//�ж�ĳ�����ϵ��ж��Ƿ���
  { 
     EXTI_ClearITPendingBit(EXTI_Line10); //��� LINE �ϵ��жϱ�־λ
     if(tube6 == 0)
	  {
	    Encoder = 12.5;
	
	  }
  }
	if(EXTI_GetITStatus(EXTI_Line11)!=RESET)//�ж�ĳ�����ϵ��ж��Ƿ���
  { 
     EXTI_ClearITPendingBit(EXTI_Line11); //��� LINE �ϵ��жϱ�־λ
		 if(tube7 == 0)
	  {
	    Encoder = 15.0;
		
	  }
  }
	if(EXTI_GetITStatus(EXTI_Line12)!=RESET)//�ж�ĳ�����ϵ��ж��Ƿ���
  { 
     EXTI_ClearITPendingBit(EXTI_Line12); //��� LINE �ϵ��жϱ�־λ		 
     if(tube8 == 0)
	  {
	    Encoder =17.5;
		
	  }
  }
}

