#include "pid.h"
#include "tim.h"
#include "pwm.h"
#include "exti.h"
#include "phototube.h"
#include "usart.h"
#include "fan.h"
int Target_height=15;  //设定目标高度
float Encoder;//当前高度，通过光电管得到高度
int Moto1;//通过调节得到的占空比
int TIM2_IRQHandler(void)
{
	if(TIM_GetFlagStatus(TIM2,TIM_FLAG_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		Moto1=Incremental_PI(Encoder,Target_height);           //===高度PI控制器
	  Xianfu_Pwm();                                            //===PWM限幅
    Set_Pwm(Moto1);                                          //===赋值给PWM寄存器 
	}
	return 0;
}
/**************************************************************************
函数功能：赋值给PWM寄存器
入口参数：PWM
返回  值：无
**************************************************************************/
void Set_Pwm(int moto1)
{
		TIM_SetCompare1(TIM1,moto1);
}

/**************************************************************************
函数功能：限制PWM赋值 
入口参数：无
返回  值：无
**************************************************************************/
void Xianfu_Pwm(void)
{	
	  int Amplitude=7100;    //===PWM满幅是7200 限制在7100
    if(Moto1<-Amplitude) Moto1=-Amplitude;	
		if(Moto1>Amplitude)  Moto1=Amplitude;	
}

/**************************************************************************
函数功能：绝对值函数
入口参数：int
返回  值：unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
/**************************************************************************
函数功能：增量PI控制器
入口参数：当前高度，目标高度
返回  值：电机PWM
根据增量式离散PID公式 
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  以此类推 
pwm代表增量输出
在我们的速度控制闭环系统里面，只使用PI控制
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)
**************************************************************************/
int Incremental_PI (float Encoder,int Target)
{ 	
   float Kp=20,Ki=0;	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                //计算偏差
	 Pwm+=Kp*(Bias-Last_bias)+Ki*Bias;   //增量式PI控制器
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}
void EXTI0_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line0);  //清除EXTI0线路挂起�
	if(tube1 == 0)
	{
	  Encoder = 0;
	
	}
}
void EXTI1_IRQHandler(void)
{
  delay_ms(10);    //消抖			 
	EXTI_ClearITPendingBit(EXTI_Line1);  //清除LINE15线路挂起位
  if(tube2 == 0)
	{
	  Encoder = 2.5;
	
	}
}
void EXTI9_5_IRQHandler(void)
{			 
  if(EXTI_GetITStatus(EXTI_Line6)!=RESET)//判断某个线上的中断是否发生
  { 
     EXTI_ClearITPendingBit(EXTI_Line6); //清除 LINE 上的中断标志位
     if(tube4 == 0)
		 {
		   Encoder = 7.5;
	
		 }
	}	
  if(EXTI_GetITStatus(EXTI_Line9)!=RESET)//判断某个线上的中断是否发生
  { 
     EXTI_ClearITPendingBit(EXTI_Line9); //清除 LINE 上的中断标志位
		 if(tube12 == 0)
	  {
	    Encoder = 27.5;
		
	  }	
  }	
	if(EXTI_GetITStatus(EXTI_Line5)!=RESET)//判断某个线上的中断是否发生
  { 
     EXTI_ClearITPendingBit(EXTI_Line5); //清除 LINE 上的中断标志位	
     if(tube3 == 0)
	  {
	   Encoder = 5;

	  }
  }
	if(EXTI_GetITStatus(EXTI_Line7)!=RESET)//判断某个线上的中断是否发生
  { 
     EXTI_ClearITPendingBit(EXTI_Line7); //清除 LINE 上的中断标志位	
     if(tube5 == 0)
	  {
	   Encoder = 10;
	
	  }		
  }
	if(EXTI_GetITStatus(EXTI_Line8)!=RESET)//判断某个线上的中断是否发生
  { 
     EXTI_ClearITPendingBit(EXTI_Line8); //清除 LINE 上的中断标志位	
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
  if(EXTI_GetITStatus(EXTI_Line3)!=RESET)//判断某个线上的中断是否发生
  { 
     EXTI_ClearITPendingBit(EXTI_Line3); //清除 LINE 上的中断标志位	
			led1 = 0;
	    Encoder = 30;
	
	 	
  }	
}

void EXTI15_10_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line15)!=RESET)//判断某个线上的中断是否发生
  { 
     EXTI_ClearITPendingBit(EXTI_Line15); //清除 LINE 上的中断标志位		
     if(tube9 == 0)
	  {
	   Encoder = 20;
		
	  }
  }
	if(EXTI_GetITStatus(EXTI_Line13)!=RESET)//判断某个线上的中断是否发生
  { 
     EXTI_ClearITPendingBit(EXTI_Line13); //清除 LINE 上的中断标志位		
     if(tube9 == 0)
	  {
	   Encoder = 20.0;
	
	  }
  }
	if(EXTI_GetITStatus(EXTI_Line14)!=RESET)//判断某个线上的中断是否发生
  { 
     EXTI_ClearITPendingBit(EXTI_Line14); //清除 LINE 上的中断标志位		
     if(tube10 == 0)
	  {
	    Encoder = 22.5;
	
	  }
  }
	if(EXTI_GetITStatus(EXTI_Line10)!=RESET)//判断某个线上的中断是否发生
  { 
     EXTI_ClearITPendingBit(EXTI_Line10); //清除 LINE 上的中断标志位
     if(tube6 == 0)
	  {
	    Encoder = 12.5;
	
	  }
  }
	if(EXTI_GetITStatus(EXTI_Line11)!=RESET)//判断某个线上的中断是否发生
  { 
     EXTI_ClearITPendingBit(EXTI_Line11); //清除 LINE 上的中断标志位
		 if(tube7 == 0)
	  {
	    Encoder = 15.0;
		
	  }
  }
	if(EXTI_GetITStatus(EXTI_Line12)!=RESET)//判断某个线上的中断是否发生
  { 
     EXTI_ClearITPendingBit(EXTI_Line12); //清除 LINE 上的中断标志位		 
     if(tube8 == 0)
	  {
	    Encoder =17.5;
		
	  }
  }
}

