#ifndef ___PID__H
#define ___PID__H
#include "sys.h"

float getHeight(void);
void control(void);
void usartSend(u8 byte);
void usartPutBuff(uint8_t *data,uint32_t size);
void sendData(void);
void control_location(int height);
void free_location(uint16_t a);//�����л��߶�
void Touch_judge(void);
void show_windspeed(void);
void LED_init(void);
extern uint16_t myData[1];


#endif
