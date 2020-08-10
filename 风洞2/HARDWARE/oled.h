#ifndef _OLED_H
#define _OLED_H
#include "sys.h"

#define OLED_IIC_SCL PBout(12) //串行时钟
#define OLED_IIC_SDA PBout(15) //串行数据
#define OLED_WRITE_SDA   PBin(15) 		//输入SDA 

#define high 1
#define low 0

#define	Brightness	0xCF 
#define X_WIDTH 	128
#define Y_WIDTH 	64
void OLED_GPIO_Init(void);
void IIC_Start(void);// -- 开启I2C总线
void IIC_Stop(void);// -- 关闭I2C总线
void Write_IIC_Byte(unsigned char IIC_Byte);// -- 通过I2C总线写一个byte的数据
void OLED_WrDat(unsigned char dat);// -- 向OLED屏写数据
void OLED_WrCmd(unsigned char cmd);// -- 向OLED屏写命令
void OLED_Set_Pos(unsigned char x, unsigned char y);// -- 设置显示坐标
void OLED_Fill(unsigned char bmp_dat);// -- 全屏显示(显示BMP图片时才会用到此功能)
void OLED_CLS(void);// -- 复位/清屏
void OLED_Init(void);// -- OLED屏初始化程序，此函数应在操作屏幕之前最先调用
void OLED_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[]);// -- 6x8点整，用于显示ASCII码的最小阵列，不太清晰
void OLED_P8x16Str(unsigned char x,unsigned char y,unsigned char ch[]);// -- 8x16点整，用于显示ASCII码，非常清晰
void OLED_P16x16Ch(unsigned char x,unsigned char y,unsigned int N);// -- 16x16点整，用于显示汉字的最小阵列，可设置各种字体、加粗、倾斜、下划线等
void Draw_BMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);// -- 将128x64像素的BMP位图在取字软件中算出字表，然后复制到codetab中，此函数调用即可
void OLED_showNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void oled_showChar(u8 x,u8 y,u8 chr,u8 f_w,u8 f_h,u8 mode);
void oled_line(unsigned char i);
u32 oled_pow(u8 m,u8 n);






#endif
