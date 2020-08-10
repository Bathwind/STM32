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
extern const u8 gImage_image1[];//图片数据(包含信息头),存储在image1.c里面.
int main(void)
{  
    HEADCOLOR *imginfo;
 	imginfo=(HEADCOLOR*)gImage_image1;	//得到文件信息 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组2
	delay_init();//延时函数初始化	  
	uart_init(115200);//串口初始化为115200
	exti_init();//外部中断初始化	
	LCD_Init();//lcd屏初始化
	tp_dev.init();//触摸屏初始化
//	TP_Adjust();  	 //屏幕校准 
    TP_Save_Adjdata();//保存校准参数
	srand(imginfo->h*imginfo->w);
	image_display(0,0,(u8*)gImage_image1);//在指定地址显示图片  
	LCD_ShowString(0,120,200,16,16,"THE BALL HEIGHT");
	LCD_ShowString(0,150,200,16,16,"Selected Ball Height:");
	LCD_ShowString(190,120,200,16,16,"mm");
	LCD_ShowString(0,80,200,16,16,"Current wind speed:");
	LCD_DrawRectangle(0,200,80,260);
    LCD_DrawRectangle(80,200,160,260);
    LCD_DrawRectangle(160,200,250,260);		
    while(vl53l0x_init(&vl53l0x_dev)){ }
	TIM1_PWM_Init(899,0);//pwm初始化 
    tim2_init(199,7199);//定时器2中断初始化
	Fan_Init();//拉高风扇io口电平
	while(1)
	{	 

  }
}
