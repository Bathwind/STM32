#include "pid.h"
#include "tim.h"
#include "pwm.h"
#include "usart.h"
#include "vl53l0x_gen.h"
#include "key.h"
#include "exti.h"
#include "OLED_I2C.h"
#include "touch.h"
int heigh = 0;
char hei[];//当前高度对应的点
float errNow = 0;//当前误差
float errLast = 0;//上一次误差
uint16_t target = 0;//目标高度
float outPwm = 0;//输出pwm值
char windspeed1[];//保存当前算出的风力值
float height_P = 0;//pid的p系数
float height_I = 0;//pid的i系数
uint16_t myData[1] = {0};//存放采集到的高度
void TIM2_IRQHandler(void)
{
	if(TIM_GetFlagStatus(TIM2,TIM_FLAG_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		myV15310();//初始化激光测距模块并且开始测距
		control();//调用pid算出pwm的具体值
		Touch_judge();//触屏控制
        LCD_ShowString(160,120,200,16,16,dis);
        LED_init();		
	}
}

float getHeight(void)
{
	return (float)Distance_data - 40;
}

void control(void)//通过增量式Pi算出pwm值
{
	errNow = target - myData[0];
	outPwm=outPwm+(errNow-errLast)*height_P+height_I*errNow;
	if(outPwm>900)
	{
	  outPwm = 900;
	}
	TIM_SetCompare1(TIM1,outPwm);
	errLast = errNow;
}


void usartSend(u8 byte)
{
	USART1->DR = byte; //要发送的字符赋给串口数据寄存器  
  while((USART1->SR&0X40)==0); //等待发送完成  
}

void usartPutBuff(uint8_t *data,uint32_t size)
{
	uint8_t i = 0;
	for(;i<size;i++)
	{
		usartSend(*(data+i));
	}
}
void sendData(void)
{
	
	uint8_t cmdf[2] = { 0x03,0xfc };
	uint8_t cmdr[2] = { 0xfc,0x03 };
	
	usartPutBuff(cmdf,sizeof(cmdf));
	usartPutBuff((uint8_t *)myData,sizeof(myData));
	usartPutBuff(cmdr,sizeof(cmdr));
	
	
}
void control_location(int height)
{
   switch(height)
	 {
		  case 1:
		 {
		  target = 130;//目标高度//A点
		  height_P = 1.345;//pid的p系数
      height_I = 0.0125;//pid的i系数
		 }
		 break;
		 case 2:
		 {
		  target = 160;//目标高度//B点
		 	height_P = 1.878;//pid的p系数
      height_I = 0.00275;//pid的i系数
		 }
		 break;
		 case 3:
		 {
			target = 200;//目标高度//C点
		  height_P = 0.876;//pid的p系数
      height_I = 0.013;//pid的i系数
		 }
		 break;
	   case 4:
		 {
			target = 230;//目标高度//D点
	    height_P = 0.8155;//pid的p系数
      height_I = 0.0063;//pid的i系数
		 }
		 break;
		 case 5:
		 {
	    target = 300;//目标高度//E点
	    height_P = 0.873;//pid的p系数
      height_I = 0.0063;//pid的i系数
		 }
		 break;
		 case 6:
		 {
	    target = 350;//目标高度//F点
		  height_P = 0.899;//pid的p系数
      height_I = 0.0088;//pid的i系数
		 }
		 break;
		 case 7:
		 {
	    target = 390;//目标高度//G点
		  height_P = 0.899;//pid的p系数
      height_I = 0.0087;//pid的i系数
		 }
		 break;
	 }
}
void Touch_judge(void)
{
		tp_dev.scan(0);	
	  if(tp_dev.sta&TP_PRES_DOWN)//触摸屏被按下
		{
			delay_ms(100);
		if(tp_dev.x[0]<(80)&&tp_dev.x[0]>(0)&&tp_dev.y[0]<(260)&&tp_dev.y[0]>(200))//判断触摸在某范围时返回一个键值
		{	 
			 control_location(heigh);
		}
		if(tp_dev.x[0]<(160)&&tp_dev.x[0]>(90)&&tp_dev.y[0]<(260)&&tp_dev.y[0]>(200))//判断触摸在某范围时返回一个键值
		{	 
			 heigh++;
			 if(heigh == 1)
		   { 
				 LCD_ShowString(190,150,200,16,16,"130mm");
				 LCD_ShowString(185,80,200,16,16,"0.262m/s");
			 }
			 if(heigh == 2)
		   { 
				 LCD_ShowString(190,150,200,16,16,"160mm");
				 LCD_ShowString(185,80,200,16,16,"0.310m/s");
			 }
			 if(heigh == 3)
		   {
				 LCD_ShowString(190,150,200,16,16,"200mm");
				 LCD_ShowString(185,80,200,16,16,"0.350m/s");
			 }
			  if(heigh == 4)
		   {
				 LCD_ShowString(190,150,200,16,16,"230mm");
				 LCD_ShowString(185,80,200,16,16,"0.390m/s");
			 }
			   if(heigh == 5)
		   {
				 LCD_ShowString(190,150,200,16,16,"300mm");
				 LCD_ShowString(185,80,200,16,16,"0.395m/s");
			 }
			  if(heigh == 6)
		   {
				 LCD_ShowString(190,150,200,16,16,"350mm");
				 LCD_ShowString(185,80,200,16,16,"0.410m/s");
			 }
			  if(heigh == 7)
		   {
				 LCD_ShowString(190,150,200,16,16,"390mm");
				 LCD_ShowString(185,80,200,16,16,"0.425m/s");
			 }
		}
		if(tp_dev.x[0]<(250)&&tp_dev.x[0]>(170)&&tp_dev.y[0]<(260)&&tp_dev.y[0]>(200))//判断触摸在某范围时返回一个键值
		{	 
		   heigh--;
		 	 if(heigh == 1)
		   {
				 LCD_ShowString(190,150,200,16,16,"130mm");
				 LCD_ShowString(185,80,200,16,16,"0.262m/s");
			 }
			  if(heigh == 2)
		   { 
				 LCD_ShowString(190,150,200,16,16,"160mm");
				 LCD_ShowString(185,80,200,16,16,"0.310m/s");
			 }
			 if(heigh == 3)
		   {
				 LCD_ShowString(190,150,200,16,16,"200mm");
				  LCD_ShowString(185,80,200,16,16,"0.350m/s");
			 }
			 if(heigh == 4)
		   {
				 LCD_ShowString(190,150,200,16,16,"230mm");
				  LCD_ShowString(185,80,200,16,16,"0.390m/s");
			 }
			 if(heigh == 5)
		   {
				 LCD_ShowString(190,150,200,16,16,"300mm");
				 LCD_ShowString(185,80,200,16,16,"0.395m/s");
			 }
			  if(heigh == 6)
		   {
				 LCD_ShowString(190,150,200,16,16,"350mm");
				 LCD_ShowString(185,80,200,16,16,"0.410m/s");
			 }
			  if(heigh == 7)
		   {
				 LCD_ShowString(190,150,200,16,16,"390mm");
				 LCD_ShowString(185,80,200,16,16,"0.425m/s");
			 }
		}
	  }	
}
void show_windspeed(void)
{
	int windspeed;
	windspeed = (int)myData[0]*10;
	sprintf(windspeed1,"%d",windspeed);  
}
void EXTI15_10_IRQHandler(void)
{		 
 if(EXTI_GetITStatus(EXTI_Line15)!=RESET)//判断某个线上的中断是否发生key
 {
   EXTI_ClearITPendingBit(EXTI_Line15);
	 if(KEY1 == 0)
	 {
	  control_location(heigh);
	 }
 }
 if(EXTI_GetITStatus(EXTI_Line14)!=RESET)//判断某个线上的中断是否发生
 {
   EXTI_ClearITPendingBit(EXTI_Line14);
	  if(KEY0 == 0)
	 {
	  heigh--;
	  if(heigh == 1)
		   { 
				 LCD_ShowString(190,150,200,16,16,"130mm");
				 LCD_ShowString(185,80,200,16,16,"0.262m/s");
			 }
			 if(heigh == 2)
		   { 
				 LCD_ShowString(190,150,200,16,16,"160mm");
				 LCD_ShowString(185,80,200,16,16,"0.310m/s");
			 }
			 if(heigh == 3)
		   {
				 LCD_ShowString(190,150,200,16,16,"200mm");
				 LCD_ShowString(185,80,200,16,16,"0.350m/s");
			 }
			  if(heigh == 4)
		   {
				 LCD_ShowString(190,150,200,16,16,"230mm");
				 LCD_ShowString(185,80,200,16,16,"0.390m/s");
			 }
			   if(heigh == 5)
		   {
				 LCD_ShowString(190,150,200,16,16,"300mm");
				 LCD_ShowString(185,80,200,16,16,"0.395m/s");
			 }
			  if(heigh == 6)
		   {
				 LCD_ShowString(190,150,200,16,16,"350mm");
				 LCD_ShowString(185,80,200,16,16,"0.410m/s");
			 }
			  if(heigh == 7)
		   {
				 LCD_ShowString(190,150,200,16,16,"390mm");
				 LCD_ShowString(185,80,200,16,16,"0.425m/s");
			 }
	 }
 }
  if(EXTI_GetITStatus(EXTI_Line13)!=RESET)//判断某个线上的中断是否发生
 {
   EXTI_ClearITPendingBit(EXTI_Line13);
	  if(WK_UP == 0)
	 {
	   heigh++;
	   if(heigh == 1)
		   { 
				 LCD_ShowString(190,150,200,16,16,"130mm");
				 LCD_ShowString(185,80,200,16,16,"0.262m/s");
			 }
			 if(heigh == 2)
		   { 
				 LCD_ShowString(190,150,200,16,16,"160mm");
				 LCD_ShowString(185,80,200,16,16,"0.310m/s");
			 }
			 if(heigh == 3)
		   {
				 LCD_ShowString(190,150,200,16,16,"200mm");
				 LCD_ShowString(185,80,200,16,16,"0.350m/s");
			 }
			  if(heigh == 4)
		   {
				 LCD_ShowString(190,150,200,16,16,"230mm");
				 LCD_ShowString(185,80,200,16,16,"0.390m/s");
			 }
			   if(heigh == 5)
		   {
				 LCD_ShowString(190,150,200,16,16,"300mm");
				 LCD_ShowString(185,80,200,16,16,"0.395m/s");
			 }
			  if(heigh == 6)
		   {
				 LCD_ShowString(190,150,200,16,16,"350mm");
				 LCD_ShowString(185,80,200,16,16,"0.410m/s");
			 }
			  if(heigh == 7)
		   {
				 LCD_ShowString(190,150,200,16,16,"390mm");
				 LCD_ShowString(185,80,200,16,16,"0.425m/s");
			 }
	 }
 }
}
void LED_init(void)
{
	  if(myData[0] == 130)
		{
		  LED1 = 1;
			LED2 = 0;
			LED3 = 0; 
			LED4 = 0;
		}
		 if(myData[0] == 200)
		{
		  LED1 = 0;
			LED2 = 1;
			LED3 = 0; 
			LED4 = 0;
		}
		 if(myData[0] == 350)
		{
		  LED1 = 0;
			LED2 = 0;
			LED3 = 1; 
			LED4 = 0;
		}
		 if(myData[0] == 390)
		{
		  LED1 = 0;
			LED2 = 0;
			LED3 = 0; 
			LED4 = 1;
		}



}