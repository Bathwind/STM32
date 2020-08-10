#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
 	 


#define KEY0  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)//读取按键0
#define KEY1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)//读取按键1
#define WK_UP   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)//读取按键2 
 

#define KEY0_PRES	1		//KEY0  
#define KEY1_PRES	2		//KEY1 
#define WKUP_PRES	3		//WK_UP  

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8 mode);  	//按键扫描函数					    
#endif
