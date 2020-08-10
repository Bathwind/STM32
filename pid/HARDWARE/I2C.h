#ifndef I2C__H
#define I2C__H
#include "sys.h"
#define SDA_IN()  {GPIOA->CRL&=0XF0FFFFFF;GPIOA->CRL|=8<<7;}
#define SDA_OUT() {GPIOA->CRL&=0XF0FFFFFF;GPIOA->CRL|=3<<7;}

//IO��������	 
#define IIC_SCL    PAout(7) //SCL
#define IIC_SDA    PAout(6) //SDA	 
#define READ_SDA   PAin(7)  //����SDA 

void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

#endif