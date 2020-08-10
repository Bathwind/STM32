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
   	u8 t=0;	  
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
   	TIM1_PWM_Init(899,0);//pwm��ʼ��    
  	KEY_Init();//��ʼ��������Ӧioģʽ	
	  phototube_init();//����Io�ڳ�ʼ��
	  OLED_GPIO_Init();//��ʼ��oledI2C����
    OLED_Init();//oled��ʼ�� 
	  delay_init(); //��ʱ��ʼ��  	
 		
	  exti_init();//�ⲿ�жϳ�ʼ��  
	  while(1)
	 {    
   	  Location();//ȷ��С��߶�
		t=KEY_Scan(0);		//�õ���ֵ
		switch(t)
	 {				 
		 case KEY0_PRES:
				point--;
				break;
		 case KEY1_PRES:
			 point++;
			 break;
		 case KEY2_PRES:				
			 Control_point(point);
			 break;
		 default:
			 delay_ms(10);	
	}
	} 
}

