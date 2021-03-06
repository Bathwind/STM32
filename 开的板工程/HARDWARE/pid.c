#include "pid.h"
#include "tim.h"
#include "pwm.h"
#include "usart.h"
#include "vl53l0x_gen.h"
#include "key.h"
#include "exti.h"
#include "OLED_I2C.h"
int heigh = 0;
char hei[];//当前高度对应的点
float errNow = 0;//当前误差
float errLast = 0;//上一次误差
uint16_t target = 0;//目标高度
float outPwm = 0;//输出pwm值
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
//		sendData();//根据协议发给串口生成虚拟波形图
    OLED_ShowStr(2,3,dis,2);//显示小球实时高度   
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
	TIM_SetCompare1(TIM2,outPwm);
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
void EXTI9_5_IRQnIRQHandler(void)
{	
		if(EXTI_GetITStatus(EXTI_Line6)!=RESET)//判断某个线上的中断是否发生
		{
			EXTI_ClearITPendingBit(EXTI_Line6); //清除 LINE 上的中断标志位
			if(KEY0 == 0)
	{
		heigh-=1;
		sprintf(hei,"%d",heigh); 
		
		if(heigh == 1)//对应Apoint100mm
		{	
			OLED_CLS();
			OLED_ShowStr(2,5,hei,2);
			OLED_ShowCN(0,0,0);
	    OLED_ShowCN(16,0,1);
	    OLED_ShowCN(32,0,2);
	    OLED_ShowCN(48,0,3);
	    OLED_ShowStr(29,3,"mm",2);
			OLED_ShowStr(16,5,"Apoint",2);
			oled_line(1);
		}	
   	if(heigh == 2)//对应Bpoint150mm
		{	
			OLED_CLS();
			OLED_ShowStr(2,5,hei,2);
			OLED_ShowCN(0,0,0);
	    OLED_ShowCN(16,0,1);
	    OLED_ShowCN(32,0,2);
	    OLED_ShowCN(48,0,3);
	    OLED_ShowStr(29,3,"mm",2);
			OLED_ShowStr(16,5,"Bpoint",2);
			oled_line(3);
		}	
    if(heigh == 3)//对应Cpoint200mm
		{
			OLED_CLS();
			OLED_ShowStr(2,5,hei,2);
			OLED_ShowCN(0,0,0);
	    OLED_ShowCN(16,0,1);
	    OLED_ShowCN(32,0,2);
	    OLED_ShowCN(48,0,3);
	    OLED_ShowStr(29,3,"mm",2);
			OLED_ShowStr(16,5,"Cpoint",2);
			oled_line(4);
		}		
		 if(heigh == 4)//对应Dpoint250mm
		{
			OLED_CLS();
			OLED_ShowStr(2,5,hei,2);
			OLED_ShowCN(0,0,0);
	    OLED_ShowCN(16,0,1);
	    OLED_ShowCN(32,0,2);
	    OLED_ShowCN(48,0,3);
	    OLED_ShowStr(29,3,"mm",2);
			OLED_ShowStr(16,5,"Dpoint",2);
			oled_line(5);
		}
    if(heigh == 5)//对应Epoint300mm
		{	
			OLED_CLS();
			OLED_ShowStr(2,5,hei,2);
			OLED_ShowCN(0,0,0);
	    OLED_ShowCN(16,0,1);
	    OLED_ShowCN(32,0,2);
	    OLED_ShowCN(48,0,3);
	    OLED_ShowStr(29,3,"mm",2);
			OLED_ShowStr(16,5,"Epoint",2);
			oled_line(7);
		}
    if(heigh == 6)//对应Fpoint350mm
		{
			OLED_CLS();
			OLED_ShowStr(2,5,hei,2);
			OLED_ShowCN(0,0,0);
	    OLED_ShowCN(16,0,1);
	    OLED_ShowCN(32,0,2);
	    OLED_ShowCN(48,0,3);
	    OLED_ShowStr(29,3,"mm",2);
			OLED_ShowStr(16,5,"Fpoint",2);
			oled_line(8);
		}	
     if(heigh == 7)//对应Gpoint390mm
		{
			OLED_CLS();
			OLED_ShowStr(2,5,hei,2);
			OLED_ShowCN(0,0,0);
	    OLED_ShowCN(16,0,1);
	    OLED_ShowCN(32,0,2);
	    OLED_ShowCN(48,0,3);
	    OLED_ShowStr(29,3,"mm",2);
			OLED_ShowStr(16,5,"Gpoint",2);
			oled_line(9);
		}	
	
	}
		}
		if(EXTI_GetITStatus(EXTI_Line7)!=RESET)//判断某个线上的中断是否发生
		{
			EXTI_ClearITPendingBit(EXTI_Line7); //清除 LINE 上的中断标志位
			if(KEY1 == 0)
	  {
		heigh+=1;
		sprintf(hei,"%d",heigh); 
		OLED_ShowStr(2,5,hei,2);
	  OLED_ShowCN(0,0,0);
	  OLED_ShowCN(16,0,1);
	  OLED_ShowCN(32,0,2);
	  OLED_ShowCN(48,0,3);
	  OLED_ShowStr(29,3,"mm",2);
		 if(heigh == 1)//对应Apoint100mm
		 {
			OLED_ShowStr(16,5,"Apoint",2);
			oled_line(2);
		 }	
   	 if(heigh == 2)//对应Bpoint150mm
		 {
			OLED_ShowStr(16,5,"Bpoint",2);
			oled_line(3);
		 }	
     if(heigh == 3)//对应Cpoint200mm
		 {
			OLED_ShowStr(16,5,"Cpoint",2);
			oled_line(4);
		 }		
		  if(heigh == 4)//对应Dpoint250mm
		 {
			OLED_ShowStr(16,5,"Dpoint",2);
			oled_line(5);
		 }
     if(heigh == 5)//对应Epoint300mm
		 {
			OLED_ShowStr(16,5,"Epoint",2);
			oled_line(7);
		  }
     if(heigh == 6)//对应Fpoint350mm
		 { 
			OLED_ShowStr(16,5,"Fpoint",2);
			oled_line(9);
		 }	
      if(heigh == 7)//对应Gpoint370mm
		 {
			OLED_ShowStr(16,5,"Gpoint",2);
			oled_line(9);
		 }		
	 }
		}
		if(EXTI_GetITStatus(EXTI_Line8)!=RESET)//判断某个线上的中断是否发生
		{
			EXTI_ClearITPendingBit(EXTI_Line8); //清除 LINE 上的中断标志位
			if(WK_UP == 0)
			{
				control_location(heigh);
			}
		}
}
void EXTI1_IRQHandler(void)
{	
	EXTI_ClearITPendingBit(EXTI_Line1);  //清除EXTI1线路挂起位
  
}
void EXTI2_IRQHandler(void)
{	
	EXTI_ClearITPendingBit(EXTI_Line2);  //清除EXTI2线路挂起位
  
}
void control_location(int height)
{
   switch(height)
	 {
		  case 1:
		 {
		  target = 130;//目标高度//A点
		  height_P = 1.855;//pid的p系数
      height_I = 0.014;//pid的i系数
		 }
		 break;
		 case 2:
		 {
		  target = 150;//目标高度//B点
		  height_P = 1.552;//pid的p系数
      height_I = 0.019;//pid的i系数
		 }
		 break;
		 case 3:
		 {
			target = 200;//目标高度//C点
		  height_P = 0.996;//pid的p系数
      height_I = 0.011;//pid的i系数
		 }
		 break;
	   case 4:
		 {
			target = 250;//目标高度//D点
		  height_P = 0.889;//pid的p系数
      height_I = 0.0075;//pid的i系数
		 }
		 break;
		 case 5:
		 {
	    target = 300;//目标高度//E点
		  height_P = 1.0011;//pid的p系数
      height_I = 0.011;//pid的i系数
		 }
		 break;
		 case 6:
		 {
	    target = 350;//目标高度//F点
		  height_P = 0.899;//pid的p系数
      height_I = 0.0087;//pid的i系数
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
