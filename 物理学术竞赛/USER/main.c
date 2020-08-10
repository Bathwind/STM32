#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"   
#include "usmart.h"
#include "vl53l0x.h"
#include "tim.h"
#include "pwm.h"
#include "meau.h"
#include "pid.h"
#include "exti.h"
#include "touch.h"
#include "image2lcd.h"
extern const u8 gImage_image1[];//ͼƬ����(������Ϣͷ),�洢��image1.c����.
int main(void)
{  
    HEADCOLOR *imginfo;
 	imginfo=(HEADCOLOR*)gImage_image1;	//�õ��ļ���Ϣ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����2
	delay_init();//��ʱ������ʼ��	  
	uart_init(115200);//���ڳ�ʼ��Ϊ115200
	exti_init();//�ⲿ�жϳ�ʼ��	
	LCD_Init();//lcd����ʼ��
	tp_dev.init();//��������ʼ��
//	TP_Adjust();  	 //��ĻУ׼ 
    TP_Save_Adjdata();//����У׼����
	srand(imginfo->h*imginfo->w);
	image_display(0,0,(u8*)gImage_image1);//��ָ����ַ��ʾͼƬ  
	LCD_ShowString(0,120,200,16,16,"THE BALL HEIGHT");
	LCD_ShowString(0,150,200,16,16,"Selected Ball Height:");
	LCD_ShowString(190,120,200,16,16,"mm");
	LCD_ShowString(0,80,200,16,16,"Current wind speed:");
	LCD_DrawRectangle(0,200,80,260);
    LCD_DrawRectangle(80,200,160,260);
    LCD_DrawRectangle(160,200,250,260);		
    while(vl53l0x_init(&vl53l0x_dev)){ }
	TIM1_PWM_Init(899,0);//pwm��ʼ�� 
    tim2_init(199,7199);//��ʱ��2�жϳ�ʼ��
	Fan_Init();//���߷���io�ڵ�ƽ
	while(1)
	{	 

  }
}
