#include "stm32f10x.h"
#include "delay.h"
#include "exti.h"
#include "tim.h"
#include "pwm.h"
#include "oled.h"
#include "fan.h"
#include "phototube.h"
#include "pid.h"
#include "usart.h"
int main(void)
{	  
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	  delay_init(); //��ʱ��ʼ��
    uart_init(9600); 	
    TIM1_PWM_Init(7199,0);//pwm��ʼ��
    tim2_init(99,7199);//ÿ10ms����һ���ж� 	  
	  exti_init();//�ⲿ�жϳ�ʼ��  
	  phototube_init();//����Io�ڳ�ʼ��	

	  while(1)
	  {    
			 Oscilloscope(Encoder);
		}
    
}

