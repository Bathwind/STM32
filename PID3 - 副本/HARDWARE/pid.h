#ifndef ___PID__H
#define ___PID__H
#include "sys.h"

float getHeight(void);
void control(void);
void usartSend(u8 byte);
void usartPutBuff(uint8_t *data,uint32_t size);
void sendData(void);
extern uint16_t myData[1];

#endif
