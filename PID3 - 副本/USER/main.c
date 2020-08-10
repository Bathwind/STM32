#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"  
#include "24cxx.h" 
#include "myiic.h"
#include "usmart.h"
#include "vl53l0x.h"
#include "tim.h"
#include "oled.h"
#include "pwm.h"
int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����2
	delay_init();//��ʱ������ʼ��	  
	uart_init(115200);//���ڳ�ʼ��Ϊ115200 
	usmart_dev.init(72);//��ʼ��USMART	� 
	LCD_Init();//LCD��ʼ��
	KEY_Init();//������ʼ��                             
	while(vl53l0x_init(&vl53l0x_dev)){ }
	TIM1_PWM_Init(899,0);//pwm��ʼ�� 
  tim2_init(4,7199);//��ʱ��2�жϳ�ʼ��
	while(1)
	{
	}
}
