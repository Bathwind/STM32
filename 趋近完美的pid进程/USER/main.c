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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组2
	delay_init();	                               //延时函数初始化	  
	uart_init(115200);//串口初始化为115200 
	usmart_dev.init(72);     //初始化USMART	                                           
	LED_Init();		  	                           //初始化与LED连接的硬件接口
	LCD_Init();	                                   //LCD初始化
	KEY_Init();			                           //按键初始化		
	AT24CXX_Init();		                           //IIC初始化                               //设置字体为红色 
	 
		while(vl53l0x_init(&vl53l0x_dev))//vl53l0x初始化
	 {
//		LED0=!LED0;//DS0闪烁
	 }
	TIM1_PWM_Init(899,0); 
  tim2_init(4,7199);//定时器2中断初始化
	while(1)
	{
//		TIM_SetCompare1(TIM1,280);
	}
}
