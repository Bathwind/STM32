#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
 	 


#define WK_UP  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_13)//读取按键WK_UP
#define KEY0  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_14)//读取按键0
#define KEY1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)//读取按键1 

 

#define KEY0_PRES	1		//KEY0  
#define KEY1_PRES	2		//KEY1 
#define WKUP_PRES	3		//WK_UP   

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8 mode);  	//按键扫描函数					    
#endif
