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
        OLED_ShowStr(55,3,dis,2);//显示小球实时高度   
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
void EXTI0_IRQHandler(void)
{	
	EXTI_ClearITPendingBit(EXTI_Line0);  //清除EXTI0线路挂起位
  if(KEY0 == 0)
	{
			control_location(heigh);
	}

}
void EXTI1_IRQHandler(void)
{	
	EXTI_ClearITPendingBit(EXTI_Line1);  //清除EXTI1线路挂起位
  if(KEY1 == 0)
	{
		if(heigh>7)
		{
  		heigh = -1;
      OLED_CLS();
   	  oled_line(1);	
	    OLED_ShowStr(0,3,"height",2);			
		  OLED_ShowStr(2,5,hei,2);
	    OLED_ShowCN(0,0,0);
	    OLED_ShowCN(16,0,1);
	    OLED_ShowCN(32,0,2);
	    OLED_ShowCN(48,0,3);
	    OLED_ShowStr(78,3,"mm",2);
		}
		heigh+=1;
		sprintf(hei,"%d",heigh);
		OLED_ShowStr(2,5,hei,2);
		OLED_ShowStr(0,3,"height",2);
	  OLED_ShowCN(0,0,0);
	  OLED_ShowCN(16,0,1);
	  OLED_ShowCN(32,0,2);
	  OLED_ShowCN(48,0,3);
	  OLED_ShowStr(78,3,"mm",2);
		if(heigh == 1)//对应Apoint100mm
		{
			OLED_ShowStr(16,5,"130mm",2);
			oled_line(1);
		}	
   	if(heigh == 2)//对应Bpoint160mm
		{
			OLED_ShowStr(16,5,"160mm",2);
	    oled_line(3);
		}	
    if(heigh == 3)//对应Cpoint200mm
		{
			OLED_ShowStr(16,5,"200mm",2);
	    oled_line(4);
		}		
		 if(heigh == 4)//对应Dpoint250mm
		{
			OLED_ShowStr(16,5,"250mm",2);
		  oled_line(5);
		}
    if(heigh == 5)//对应Epoint300mm
		{
			OLED_ShowStr(16,5,"300mm",2);
		  oled_line(7);
		}
    if(heigh == 6)//对应Fpoint350mm
		{
			OLED_ShowStr(16,5,"350mm",2);
      oled_line(8);
		}	
     if(heigh == 7)//对应Gpoint390mm
		{
			OLED_ShowStr(16,5,"390mm",2);
		  oled_line(9);
		}		
	}
}
void EXTI2_IRQHandler(void)
{	
	EXTI_ClearITPendingBit(EXTI_Line2);  //清除EXTI2线路挂起位
  if(KEY2 == 0)
	{
		if(heigh < 1 )
	  {		
		  heigh = 1;
      oled_line(1);
	  }		
		heigh-=1;
		sprintf(hei,"%d",heigh);
		OLED_ShowStr(2,5,hei,2);
		OLED_ShowStr(0,3,"height",2);
	  OLED_ShowCN(0,0,0);
	  OLED_ShowCN(16,0,1);
	  OLED_ShowCN(32,0,2);
	  OLED_ShowCN(48,0,3);
	  OLED_ShowStr(78,3,"mm",2);
		if(heigh == 1)//对应Apoint100mm
		{	
			OLED_CLS();
			OLED_ShowStr(0,3,"height",2);
			OLED_ShowStr(2,5,hei,2);
			OLED_ShowCN(0,0,0);
	    OLED_ShowCN(16,0,1);
	    OLED_ShowCN(32,0,2);
	    OLED_ShowCN(48,0,3);
	    OLED_ShowStr(78,3,"mm",2);
			OLED_ShowStr(16,5,"130mm",2);
      oled_line(1);
		}	
   	if(heigh == 2)//对应Bpoint160mm
		{	
			OLED_CLS();
			OLED_ShowStr(0,3,"height",2);
			OLED_ShowStr(2,5,hei,2);
			OLED_ShowCN(0,0,0);
	    OLED_ShowCN(16,0,1);
	    OLED_ShowCN(32,0,2);
	    OLED_ShowCN(48,0,3);
	    OLED_ShowStr(78,3,"mm",2);
			OLED_ShowStr(16,5,"160mm",2);
      oled_line(3);
		}	
    if(heigh == 3)//对应Cpoint200mm
		{
			OLED_CLS();
			OLED_ShowStr(0,3,"height",2);
			OLED_ShowStr(2,5,hei,2);
			OLED_ShowCN(0,0,0);
	    OLED_ShowCN(16,0,1);
	    OLED_ShowCN(32,0,2);
	    OLED_ShowCN(48,0,3);
	    OLED_ShowStr(78,3,"mm",2);
			OLED_ShowStr(16,5,"200mm",2);
			oled_line(4);
		}		
		 if(heigh == 4)//对应Dpoint250mm
		{
			OLED_CLS();
			OLED_ShowStr(0,3,"height",2);
			OLED_ShowStr(2,5,hei,2);
			OLED_ShowCN(0,0,0);
	    OLED_ShowCN(16,0,1);
	    OLED_ShowCN(32,0,2);
	    OLED_ShowCN(48,0,3);
	    OLED_ShowStr(78,3,"mm",2);
			OLED_ShowStr(16,5,"250mm",2);
		  oled_line(5);
		}
    if(heigh == 5)//对应Epoint300mm
		{	
			OLED_CLS();
			OLED_ShowStr(0,3,"height",2);
			OLED_ShowStr(2,5,hei,2);
			OLED_ShowCN(0,0,0);
	    OLED_ShowCN(16,0,1);
	    OLED_ShowCN(32,0,2);
	    OLED_ShowCN(48,0,3);
	    OLED_ShowStr(78,3,"mm",2);
			OLED_ShowStr(16,5,"300mm",2);
	    oled_line(7);
		}
    if(heigh == 6)//对应Fpoint350mm
		{
			OLED_CLS();
			OLED_ShowStr(0,3,"height",2);
			OLED_ShowStr(2,5,hei,2);
			OLED_ShowCN(0,0,0);
	    OLED_ShowCN(16,0,1);
	    OLED_ShowCN(32,0,2);
	    OLED_ShowCN(48,0,3);
	    OLED_ShowStr(78,3,"mm",2);
			OLED_ShowStr(16,5,"350mm",2);
		  oled_line(8);
		}	
     if(heigh == 7)//对应Gpoint390mm
		{
			OLED_CLS();
			OLED_ShowStr(0,3,"height",2);
			OLED_ShowStr(2,5,hei,2);
			OLED_ShowCN(0,0,0);
	    OLED_ShowCN(16,0,1);
	    OLED_ShowCN(32,0,2);
	    OLED_ShowCN(48,0,3);
	    OLED_ShowStr(78,3,"mm",2);
			OLED_ShowStr(16,5,"390mm",2);
		  oled_line(9);
		}	
	
	}
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
