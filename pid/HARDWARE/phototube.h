#ifndef __PHOTOTUBE__H
#define __PHOTOTUBE__H
#include "sys.h"
/*�˸����ܱ��1��8,1ΪAλ�ã�3ΪBλ�ã�5ΪCλ�ã�7ΪDλ��*/
#define tube1 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)//A��0cm
#define tube2 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)
#define tube3 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)
#define tube4 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)
#define tube5 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)//B��10cm
#define tube6 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)
#define tube7 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)
#define tube8 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)
#define tube9 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)//C��20cm
#define tube10 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)
#define tube11 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)
#define tube12 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)
#define tube13 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)//D��30cm
#define tube14 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)
#define tube15 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)
#define tube16 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)


void phototube_init(void);//gpio��ʼ��
void Location(void);//ȷ��С���λ��

#endif
