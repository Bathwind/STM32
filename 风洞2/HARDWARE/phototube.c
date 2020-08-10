#include "phototube.h"
#include "pwm.h"
#include "oled.h"
#include "exti.h"
#include "fan.h"
#include "delay.h"
char pwm[10];
char pointlocation[10];
void phototube_init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);	 
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5| GPIO_Pin_12| GPIO_Pin_7|GPIO_Pin_6;			 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;			 
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
	 

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_10| GPIO_Pin_3 |GPIO_Pin_4 | GPIO_Pin_11|GPIO_Pin_6| GPIO_Pin_7 |GPIO_Pin_8 | GPIO_Pin_9|GPIO_Pin_13;				 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 		 
	 GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	 GPIO_Init(GPIOC, &GPIO_InitStructure);
	 GPIO_SetBits(GPIOC,GPIO_Pin_13);
   
}
void Location(void)
{
	  
	  sprintf(pointlocation,"%d",point);
	  OLED_P8x16Str(50,6,pointlocation);
	  if(tube1 == 0&&point == 1)
		{
			OLED_P8x16Str(0,3,"Apoint");
			oled_line(1);
		}
		if(tube5 == 0&&point == 5)
		{
			OLED_P8x16Str(0,3,"Bpoint");
			oled_line(3);
		}
		if(tube9 == 0&&point == 9)
		{
			OLED_P8x16Str(0,3,"Cpoint");
			oled_line(5);
		}
		if(tube13 == 0&&point == 13)
		{
			OLED_P8x16Str(0,3,"Dpoint");
			oled_line(8);
		}
}

