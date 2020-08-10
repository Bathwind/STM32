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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组2
	delay_init();//延时函数初始化	  
	uart_init(115200);//串口初始化为115200 
	usmart_dev.init(72);//初始化USMART		
	I2C_Configuration();
	exti_init();//外部中断初始化	
	KEY_Init();//按键初始化
	OLED_Init();//oled初始化
//	while(vl53l0x_init(&vl53l0x_dev)){ }
//	TIM1_PWM_Init(899,0);//pwm初始化 
//  tim2_init(199,7199);//定时器2中断初始化
	while(1)
	{
	
	}
}
 
