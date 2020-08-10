#include "pid.h"
#include "tim.h"
#include "pwm.h"
#include "usart.h"
#include "vl53l0x_gen.h"
#include "led.h"

float errNow = 0;//当前误差
float errLast = 0;//上一次误差
uint16_t target = 150;//目标高度
float outPwm = 0;//输出pwm值
float height_P = 2.16;//pid的p系数
float height_I = 0.025;//pid的i系数

uint16_t myData[1] = {0};//存放采集到的高度

void TIM2_IRQHandler(void)
{
	if(TIM_GetFlagStatus(TIM2,TIM_FLAG_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		myV15310();//初始化激光测距模块并且开始测距
		control();//调用pid算出pwm的具体值
		sendData();//根据协议发给串口生成虚拟波形图
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


void usartSend(u8 byte){
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


void sendData(void){
	
	uint8_t cmdf[2] = { 0x03,0xfc };
	uint8_t cmdr[2] = { 0xfc,0x03 };
	
	usartPutBuff(cmdf,sizeof(cmdf));
	usartPutBuff((uint8_t *)myData,sizeof(myData));
	usartPutBuff(cmdr,sizeof(cmdr));
	
	
}

