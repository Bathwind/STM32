#include "pid.h"
#include "tim.h"
#include "pwm.h"
#include "exti.h"
#include "phototube.h"
#include "usart.h"
#include "fan.h"
int Target_height=15;  //Éè¶¨Ä¿±ê¸ß¶È
float Encoder;//µ±Ç°¸ß¶È£¬Í¨¹ý¹âµç¹ÜµÃµ½¸ß¶È
int Moto1;//Í¨¹ýµ÷½ÚµÃµ½µÄÕ¼¿Õ±È
int TIM2_IRQHandler(void)
{
	if(TIM_GetFlagStatus(TIM2,TIM_FLAG_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		Moto1=Incremental_PI(Encoder,Target_height);           //===¸ß¶ÈPI¿ØÖÆÆ÷
	  Xianfu_Pwm();                                            //===PWMÏÞ·ù
    Set_Pwm(Moto1);                                          //===¸³Öµ¸øPWM¼Ä´æÆ÷ 
	}
	return 0;
}
/**************************************************************************
º¯Êý¹¦ÄÜ£º¸³Öµ¸øPWM¼Ä´æÆ÷
Èë¿Ú²ÎÊý£ºPWM
·µ»Ø  Öµ£ºÎÞ
**************************************************************************/
void Set_Pwm(int moto1)
{
		TIM_SetCompare1(TIM1,moto1);
}

/**************************************************************************
º¯Êý¹¦ÄÜ£ºÏÞÖÆPWM¸³Öµ 
Èë¿Ú²ÎÊý£ºÎÞ
·µ»Ø  Öµ£ºÎÞ
**************************************************************************/
void Xianfu_Pwm(void)
{	
	  int Amplitude=7100;    //===PWMÂú·ùÊÇ7200 ÏÞÖÆÔÚ7100
    if(Moto1<-Amplitude) Moto1=-Amplitude;	
		if(Moto1>Amplitude)  Moto1=Amplitude;	
}

/**************************************************************************
º¯Êý¹¦ÄÜ£º¾ø¶ÔÖµº¯Êý
Èë¿Ú²ÎÊý£ºint
·µ»Ø  Öµ£ºunsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
/**************************************************************************
º¯Êý¹¦ÄÜ£ºÔöÁ¿PI¿ØÖÆÆ÷
Èë¿Ú²ÎÊý£ºµ±Ç°¸ß¶È£¬Ä¿±ê¸ß¶È
·µ»Ø  Öµ£ºµç»úPWM
¸ù¾ÝÔöÁ¿Ê½ÀëÉ¢PID¹«Ê½ 
pwm+=Kp[e£¨k£©-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)´ú±í±¾´ÎÆ«²î 
e(k-1)´ú±íÉÏÒ»´ÎµÄÆ«²î  ÒÔ´ËÀàÍÆ 
pwm´ú±íÔöÁ¿Êä³ö
ÔÚÎÒÃÇµÄËÙ¶È¿ØÖÆ±Õ»·ÏµÍ³ÀïÃæ£¬Ö»Ê¹ÓÃPI¿ØÖÆ
pwm+=Kp[e£¨k£©-e(k-1)]+Ki*e(k)
**************************************************************************/
int Incremental_PI (float Encoder,int Target)
{ 	
   float Kp=20,Ki=0;	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                //¼ÆËãÆ«²î
	 Pwm+=Kp*(Bias-Last_bias)+Ki*Bias;   //ÔöÁ¿Ê½PI¿ØÖÆÆ÷
	 Last_bias=Bias;	                   //±£´æÉÏÒ»´ÎÆ«²î 
	 return Pwm;                         //ÔöÁ¿Êä³ö
}
void EXTI0_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line0);  //Çå³ýEXTI0ÏßÂ·¹ÒÆðÎ
	if(tube1 == 0)
	{
	  Encoder = 0;
	
	}
}
void EXTI1_IRQHandler(void)
{
  delay_ms(10);    //Ïû¶¶			 
	EXTI_ClearITPendingBit(EXTI_Line1);  //Çå³ýLINE15ÏßÂ·¹ÒÆðÎ»
  if(tube2 == 0)
	{
	  Encoder = 2.5;
	
	}
}
void EXTI9_5_IRQHandler(void)
{			 
  if(EXTI_GetITStatus(EXTI_Line6)!=RESET)//ÅÐ¶ÏÄ³¸öÏßÉÏµÄÖÐ¶ÏÊÇ·ñ·¢Éú
  { 
     EXTI_ClearITPendingBit(EXTI_Line6); //Çå³ý LINE ÉÏµÄÖÐ¶Ï±êÖ¾Î»
     if(tube4 == 0)
		 {
		   Encoder = 7.5;
	
		 }
	}	
  if(EXTI_GetITStatus(EXTI_Line9)!=RESET)//ÅÐ¶ÏÄ³¸öÏßÉÏµÄÖÐ¶ÏÊÇ·ñ·¢Éú
  { 
     EXTI_ClearITPendingBit(EXTI_Line9); //Çå³ý LINE ÉÏµÄÖÐ¶Ï±êÖ¾Î»
		 if(tube12 == 0)
	  {
	    Encoder = 27.5;
		
	  }	
  }	
	if(EXTI_GetITStatus(EXTI_Line5)!=RESET)//ÅÐ¶ÏÄ³¸öÏßÉÏµÄÖÐ¶ÏÊÇ·ñ·¢Éú
  { 
     EXTI_ClearITPendingBit(EXTI_Line5); //Çå³ý LINE ÉÏµÄÖÐ¶Ï±êÖ¾Î»	
     if(tube3 == 0)
	  {
	   Encoder = 5;

	  }
  }
	if(EXTI_GetITStatus(EXTI_Line7)!=RESET)//ÅÐ¶ÏÄ³¸öÏßÉÏµÄÖÐ¶ÏÊÇ·ñ·¢Éú
  { 
     EXTI_ClearITPendingBit(EXTI_Line7); //Çå³ý LINE ÉÏµÄÖÐ¶Ï±êÖ¾Î»	
     if(tube5 == 0)
	  {
	   Encoder = 10;
	
	  }		
  }
	if(EXTI_GetITStatus(EXTI_Line8)!=RESET)//ÅÐ¶ÏÄ³¸öÏßÉÏµÄÖÐ¶ÏÊÇ·ñ·¢Éú
  { 
     EXTI_ClearITPendingBit(EXTI_Line8); //Çå³ý LINE ÉÏµÄÖÐ¶Ï±êÖ¾Î»	
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
  if(EXTI_GetITStatus(EXTI_Line3)!=RESET)//ÅÐ¶ÏÄ³¸öÏßÉÏµÄÖÐ¶ÏÊÇ·ñ·¢Éú
  { 
     EXTI_ClearITPendingBit(EXTI_Line3); //Çå³ý LINE ÉÏµÄÖÐ¶Ï±êÖ¾Î»	
			led1 = 0;
	    Encoder = 30;
	
	 	
  }	
}

void EXTI15_10_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line15)!=RESET)//ÅÐ¶ÏÄ³¸öÏßÉÏµÄÖÐ¶ÏÊÇ·ñ·¢Éú
  { 
     EXTI_ClearITPendingBit(EXTI_Line15); //Çå³ý LINE ÉÏµÄÖÐ¶Ï±êÖ¾Î»		
     if(tube9 == 0)
	  {
	   Encoder = 20;
		
	  }
  }
	if(EXTI_GetITStatus(EXTI_Line13)!=RESET)//ÅÐ¶ÏÄ³¸öÏßÉÏµÄÖÐ¶ÏÊÇ·ñ·¢Éú
  { 
     EXTI_ClearITPendingBit(EXTI_Line13); //Çå³ý LINE ÉÏµÄÖÐ¶Ï±êÖ¾Î»		
     if(tube9 == 0)
	  {
	   Encoder = 20.0;
	
	  }
  }
	if(EXTI_GetITStatus(EXTI_Line14)!=RESET)//ÅÐ¶ÏÄ³¸öÏßÉÏµÄÖÐ¶ÏÊÇ·ñ·¢Éú
  { 
     EXTI_ClearITPendingBit(EXTI_Line14); //Çå³ý LINE ÉÏµÄÖÐ¶Ï±êÖ¾Î»		
     if(tube10 == 0)
	  {
	    Encoder = 22.5;
	
	  }
  }
	if(EXTI_GetITStatus(EXTI_Line10)!=RESET)//ÅÐ¶ÏÄ³¸öÏßÉÏµÄÖÐ¶ÏÊÇ·ñ·¢Éú
  { 
     EXTI_ClearITPendingBit(EXTI_Line10); //Çå³ý LINE ÉÏµÄÖÐ¶Ï±êÖ¾Î»
     if(tube6 == 0)
	  {
	    Encoder = 12.5;
	
	  }
  }
	if(EXTI_GetITStatus(EXTI_Line11)!=RESET)//ÅÐ¶ÏÄ³¸öÏßÉÏµÄÖÐ¶ÏÊÇ·ñ·¢Éú
  { 
     EXTI_ClearITPendingBit(EXTI_Line11); //Çå³ý LINE ÉÏµÄÖÐ¶Ï±êÖ¾Î»
		 if(tube7 == 0)
	  {
	    Encoder = 15.0;
		
	  }
  }
	if(EXTI_GetITStatus(EXTI_Line12)!=RESET)//ÅÐ¶ÏÄ³¸öÏßÉÏµÄÖÐ¶ÏÊÇ·ñ·¢Éú
  { 
     EXTI_ClearITPendingBit(EXTI_Line12); //Çå³ý LINE ÉÏµÄÖÐ¶Ï±êÖ¾Î»		 
     if(tube8 == 0)
	  {
	    Encoder =17.5;
		
	  }
  }
}

