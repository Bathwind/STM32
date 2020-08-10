#include "meau.h"
#include "lcd.h"

void show_maininterface(void)
{
	 POINT_COLOR=DARKBLUE ;//设置字体为蓝色
	 LCD_Clear(GREEN);
	 LCD_ShowString(30,150,200,16,16,"Welcom to use Wind tunnel system ");
	 LCD_ShowString(30,170,200,16,16,"WK_UP: Confirm the height");
	 LCD_ShowString(30,190,200,16,16,"KEY0: Increase height");    
	 LCD_ShowString(30,210,200,16,16,"KEY1: reduce in height");
}
