#ifndef HCSR04_H
#define HCSR04_H
#include "sys.h"
#define trig PAout(3)
#define echo PAin(4)
void HCSR04GPIO_init(void);
void HCSR04START(void);
void DIS_Send(float dis);
float HCSR04(void);
uvoid send_oled(float distance2);
#endif

