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
	  delay_init(); //延时初始化
    uart_init(9600); 	
    TIM1_PWM_Init(7199,0);//pwm初始化
    tim2_init(99,7199);//每10ms进入一次中断 	  
	  exti_init();//外部中断初始化  
	  phototube_init();//光电管Io口初始化	

	  while(1)
	  {    
			 Oscilloscope(Encoder);
		}
    
}

