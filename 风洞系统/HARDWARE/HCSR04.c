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
//	    trig = 1;//����trig����
//			delay_us(15);//Ҫ���߳���20us;
//		  trig = 0;
//			while(!echo);//�ȴ��ߵ�ƽ�����иߵ�ƽ���е�ƽ�仯�����ⲿ�жϿ�����ʱ����
//			while(echo);//�ȴ�echo���͵�ƽ�������в����ͽ����ⲿ�жϹرն�ʱ���ж�
//}
//float HCSR04(void)
//{
//	 int i;
//	 HCSR04START();//���������ų�ʼ��
//	 lengthTemp = get_dis();//�õ�����������ľ���
//	 if(lengthTemp<300)//�������300�������ֵ��׼ȷ����0
//   return lengthTemp;
//	 else return 0;
//}
void send_oled(float distance2)
{
	 sprintf(pwm1,"%d",pwmlevel);//��ռ�ձ�ת��Ϊ�ַ�����oled
	 sprintf(ballflag1 ,"%d",ballflag);//��С��������ת��Ϊ�ַ�����oled
	 OLED_P16x16Ch(1,0,0);//С
   OLED_P16x16Ch(17,0,1);//��
	 OLED_P16x16Ch(34,0,2);//��
	 OLED_P16x16Ch(51,0,3);//��
   OLED_P16x16Ch(70,0,4);//λ
	 OLED_P16x16Ch(85,0,5);//��
	 OLED_P8x16Str(0,2,distanc);
	 OLED_P8x16Str(0,4,"pwm:");//pwm�ַ���
	 OLED_P8x16Str(28,4,pwm1);//��ǰpwm��ֵ
	 OLED_P8x16Str(0,6,ballflag1);//��ʾС���־λ
	 OLED_CLS();//oled��λ
}
