#include "led.h"
void Fan_Init(void)
{
 
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOC, ENABLE);	 //使能PA,PD端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
 GPIO_Init(GPIOA, &GPIO_InitStructure);					
 GPIO_SetBits(GPIOA,GPIO_Pin_11);					

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);	 	
	GPIO_SetBits(GPIOD,GPIO_Pin_2); 						
	


  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	    	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);	 	
	GPIO_ResetBits(GPIOA,GPIO_Pin_9); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	    	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);	 	
	GPIO_ResetBits(GPIOA,GPIO_Pin_10);
//	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	    	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);	 	
	GPIO_ResetBits(GPIOA,GPIO_Pin_6);
//	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	    	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);	 	
	GPIO_ResetBits(GPIOA,GPIO_Pin_7); 
}
 
