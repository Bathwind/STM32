#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "exti.h"
#include "tim.h"
#include "usart.h"
#include "pwm.h"
#include "key.h"
#include "oled.h"
#include <stdio.h>
#include "fan.h"
#include "phototube.h"
int main(void)
{	    
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	  delay_init(); //��ʱ��ʼ��
    KEY_Init();//��ʼ��������Ӧioģʽ	
   	TIM1_PWM_Init(899,0);//pwm��ʼ�� 
	  OLED_GPIO_Init();//��ʼ��oledI2C����
    OLED_Init();//oled��ʼ�� 
	  phototube_init();//����Io�ڳ�ʼ��
	  exti_init();//�ⲿ�жϳ�ʼ��
	  tim2_init(999,71);//��ʱ���жϳ�ʼ0.01s 
	  while(1)
	  {    
			Location();//ȷ��С��߶�
		}
    
}

