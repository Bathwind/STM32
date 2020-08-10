#include "HCSR04.h"
#include "delay.h"
#include "tim.h"
#include "oled.h"
#include "pwm.h"
#include "exti.h"
#include <stdio.h>
float lengthTemp = 0;
char pwm1[10];
char ballflag1[10];
void HCSR04GPIO_init(void)
{
		 GPIO_InitTypeDef  GPIO_InitStructure;
 	
		 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD, ENABLE);	 
	
		 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				 
		 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
		 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
		 GPIO_Init(GPIOA, &GPIO_InitStructure);

		 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 
		 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
		 GPIO_Init(GPIOA, &GPIO_InitStructure);
     GPIO_ResetBits(GPIOA,GPIO_Pin_4);
 	
	   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 
	   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	   GPIO_Init(GPIOD, &GPIO_InitStructure);
     GPIO_SetBits(GPIOD,GPIO_Pin_2);	
}
//void HCSR04START(void)
//{
//	    trig = 1;//拉高trig引脚
//			delay_us(15);//要拉高超过20us;
//		  trig = 0;
//			while(!echo);//等待高电平；如有高电平则有电平变化进入外部中断开启定时器；
//			while(echo);//等待echo傅低电平产生如有产生就进入外部中断关闭定时器中断
//}
//float HCSR04(void)
//{
//	 int i;
//	 HCSR04START();//超声波引脚初始化
//	 lengthTemp = get_dis();//得到超声波测出的距离
//	 if(lengthTemp<300)//如果超过300则测量的值不准确，清0
//   return lengthTemp;
//	 else return 0;
//}
void send_oled(float distance2)
{
	 sprintf(pwm1,"%d",pwmlevel);//将占空比转换为字符串给oled
	 sprintf(ballflag1 ,"%d",ballflag);//将小球上升点转化为字符串给oled
	 OLED_P16x16Ch(1,0,0);//小
   OLED_P16x16Ch(17,0,1);//球
	 OLED_P16x16Ch(34,0,2);//高
	 OLED_P16x16Ch(51,0,3);//度
   OLED_P16x16Ch(70,0,4);//位
	 OLED_P16x16Ch(85,0,5);//置
	 OLED_P8x16Str(0,2,distanc);
	 OLED_P8x16Str(0,4,"pwm:");//pwm字符串
	 OLED_P8x16Str(28,4,pwm1);//当前pwm数值
	 OLED_P8x16Str(0,6,ballflag1);//显示小球标志位
	 OLED_CLS();//oled复位
}
