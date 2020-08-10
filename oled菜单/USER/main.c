#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"   
#include "usmart.h"
#include "vl53l0x.h"
#include "tim.h"
#include "OLED_I2C.h"
#include "pwm.h"
#include "pid.h"
#include "exti.h"
int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����2
	delay_init();//��ʱ������ʼ��	  
	uart_init(115200);//���ڳ�ʼ��Ϊ115200 
	usmart_dev.init(72);//��ʼ��USMART		
	I2C_Configuration();
	exti_init();//�ⲿ�жϳ�ʼ��	
	KEY_Init();//������ʼ��
	OLED_Init();//oled��ʼ��
//	while(vl53l0x_init(&vl53l0x_dev)){ }
//	TIM1_PWM_Init(899,0);//pwm��ʼ�� 
//  tim2_init(199,7199);//��ʱ��2�жϳ�ʼ��
	while(1)
	{
	
	}
}
 
