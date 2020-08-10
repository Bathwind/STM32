#ifndef __PHOTOTUBE__H
#define __PHOTOTUBE__H
#include "sys.h"
/*八个光电管编号1到8,1为A位置，3为B位置，5为C位置，7为D位置*/
#define tube1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)
#define tube2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)
#define tube3 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)
#define tube4 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)
#define tube5 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)
#define tube6 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_13)
#define tube7 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)
#define tube8 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)
#define tube9 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)
#define tube10 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)
#define tube11 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)
#define tube12 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)
#define tube13 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)
#define tube14 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)
#define tube15 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)
#define tube16 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)

void phototube_init(void);//gpio初始化
void Location(void);//确定小球的位置

#endif
