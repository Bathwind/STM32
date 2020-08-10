#include "led.h"
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
	delay_init();	                               //��ʱ������ʼ��	  
	uart_init(115200);//���ڳ�ʼ��Ϊ115200 
	usmart_dev.init(72);     //��ʼ��USMART	                                           
	LED_Init();		  	                           //��ʼ����LED���ӵ�Ӳ���ӿ�
	LCD_Init();	                                   //LCD��ʼ��
	KEY_Init();			                           //������ʼ��		
	AT24CXX_Init();		                           //IIC��ʼ��                               //��������Ϊ��ɫ 
	 
		while(vl53l0x_init(&vl53l0x_dev))//vl53l0x��ʼ��
	 {
//		LED0=!LED0;//DS0��˸
	 }
	TIM1_PWM_Init(899,0); 
  tim2_init(4,7199);//��ʱ��2�жϳ�ʼ��
	while(1)
	{
//		TIM_SetCompare1(TIM1,280);
	}
}
