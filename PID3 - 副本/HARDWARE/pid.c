#include "pid.h"
#include "tim.h"
#include "pwm.h"
#include "usart.h"
#include "vl53l0x_gen.h"
#include "led.h"

float errNow = 0;//��ǰ���
float errLast = 0;//��һ�����
uint16_t target = 150;//Ŀ��߶�
float outPwm = 0;//���pwmֵ
float height_P = 2.16;//pid��pϵ��
float height_I = 0.025;//pid��iϵ��

uint16_t myData[1] = {0};//��Ųɼ����ĸ߶�

void TIM2_IRQHandler(void)
{
	if(TIM_GetFlagStatus(TIM2,TIM_FLAG_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		myV15310();//��ʼ��������ģ�鲢�ҿ�ʼ���
		control();//����pid���pwm�ľ���ֵ
		sendData();//����Э�鷢�������������Ⲩ��ͼ
	}
}

float getHeight(void)
{
	return (float)Distance_data - 40;
}

void control(void)//ͨ������ʽPi���pwmֵ
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
	USART1->DR = byte; //Ҫ���͵��ַ������������ݼĴ���  
    while((USART1->SR&0X40)==0); //�ȴ��������  
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

