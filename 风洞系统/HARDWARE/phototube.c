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
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD, ENABLE);	 
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_12| GPIO_Pin_13|GPIO_Pin_5|GPIO_Pin_3|GPIO_Pin_4;				 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;			 
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
	 
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8| GPIO_Pin_9;				 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 		 
	 GPIO_Init(GPIOC, &GPIO_InitStructure);

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_10| GPIO_Pin_3 |GPIO_Pin_4 | GPIO_Pin_11;				 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 		 
	 GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	 GPIO_Init(GPIOD, &GPIO_InitStructure);
	 GPIO_SetBits(GPIOD,GPIO_Pin_2);	 
}
void Location(void)
{
    OLED_P16x16Ch(0,0,0);
		OLED_P16x16Ch(16,0,1);
		OLED_P16x16Ch(32,0,2);
	  OLED_P16x16Ch(48,0,3);
	  sprintf(pwm,"%d",pwmlevel);
	  sprintf(pointlocation,"%d",point);
	  OLED_P8x16Str(0,4,"pwmlevel");
	  OLED_P8x16Str(55,4,pwm);
	  OLED_P8x16Str(0,6,"point:");
	  OLED_P8x16Str(50,6,pointlocation);
		if(tube1 == 0)
		{
			OLED_P8x16Str(0,2,"0cm");
			delay_ms(5000);
			OLED_CLS();
		}
		if(tube2 == 0)
		{
			OLED_P8x16Str(0,2,"2.5cm");
			delay_ms(5000);
			OLED_CLS();
		}
		if(tube3 == 0)
		{
			OLED_P8x16Str(0,2,"5cm");
			delay_ms(5000);
			OLED_CLS();
		}
		if(tube4 == 0)
		{
			OLED_P8x16Str(0,2,"7.5cm");
			delay_ms(5000);
			OLED_CLS();
		}
		if(tube5 == 0)
		{
			OLED_P8x16Str(0,2,"10cm");
			delay_ms(5000);
			OLED_CLS();
		}
		if(tube6 == 0)
		{
			OLED_P8x16Str(0,2,"12.5cm");
			delay_ms(5000);
			OLED_CLS();
		}
		if(tube7 == 0)
		{
			OLED_P8x16Str(0,2,"15cm");
			delay_ms(5000);
			OLED_CLS();
		}
		if(tube8 == 0)
		{
			OLED_P8x16Str(0,2,"17.5cm");
			delay_ms(5000);
			OLED_CLS();
		}
		if(tube9 == 0)
		{
			OLED_P8x16Str(0,2,"20cm");
			delay_ms(5000);
			OLED_CLS();
		}
		if(tube10 == 0)
		{
			OLED_P8x16Str(0,2,"22.5cm");
			delay_ms(5000);
			OLED_CLS();
		}
		if(tube11 == 0)
		{
			OLED_P8x16Str(0,2,"25cm");
			delay_ms(5000);
			OLED_CLS();
		}
		if(tube12 == 0)
		{
			OLED_P8x16Str(0,2,"27.5cm");
			delay_ms(5000);
			OLED_CLS();
		}
		if(tube13 == 0)
		{
			OLED_P8x16Str(0,2,"30cm");
			delay_ms(5000);
			OLED_CLS();
		}
		if(tube14 == 0)
		{
			OLED_P8x16Str(0,2,"32.5cm");
			delay_ms(5000);
			OLED_CLS(); 
		}
		if(tube15 == 0)
		{
			OLED_P8x16Str(0,2,"35cm");
			delay_ms(5000);
			OLED_CLS();
		}
		if(tube16 == 0)
		{
			OLED_P8x16Str(0,2,"37.5cm");
			delay_ms(5000);
			OLED_CLS();
		}
}

