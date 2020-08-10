#ifndef I2C__H
#define I2C__H
#include "sys.h"
#define SDA_IN()  {GPIOA->CRL&=0XF0FFFFFF;GPIOA->CRL|=8<<7;}
#define SDA_OUT() {GPIOA->CRL&=0XF0FFFFFF;GPIOA->CRL|=3<<7;}

//IO操作函数	 
#define IIC_SCL    PAout(7) //SCL
#define IIC_SDA    PAout(6) //SDA	 
#define READ_SDA   PAin(7)  //输入SDA 

void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

#endif