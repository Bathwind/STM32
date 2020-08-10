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
	  delay_init(); //延时初始化
    KEY_Init();//初始化按键对应io模式	
   	TIM1_PWM_Init(899,0);//pwm初始化 
	  OLED_GPIO_Init();//初始化oledI2C引脚
    OLED_Init();//oled初始化 
	  phototube_init();//光电管Io口初始化
	  exti_init();//外部中断初始化
	  tim2_init(999,71);//定时器中断初始0.01s 
	  while(1)
	  {    
			Location();//确定小球高度
		}
    
}

