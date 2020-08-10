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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//ÉèÖÃÖĞ¶ÏÓÅÏÈ¼¶·Ö×é2
	delay_init();//ÑÓÊ±º¯Êı³õÊ¼»¯	  
	uart_init(115200);//´®¿Ú³õÊ¼»¯Îª115200 
	usmart_dev.init(72);//³õÊ¼»¯USMART	¯ 
	LCD_Init();//LCD³õÊ¼»¯
	KEY_Init();//°´¼ü³õÊ¼»¯                             
	while(vl53l0x_init(&vl53l0x_dev)){ }
	TIM1_PWM_Init(899,0);//pwm³õÊ¼»¯ 
  tim2_init(4,7199);//¶¨Ê±Æ÷2ÖĞ¶Ï³õÊ¼»¯
	while(1)
	{
	}
}
