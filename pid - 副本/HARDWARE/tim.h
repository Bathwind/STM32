#ifndef _tim_H
#define _tim_H
#include "sys.h"

void tim2_init(u16 arr,u16 psc);//定时器2初始化
u32 Get_tim2EchoTimer(void);//得到定时器2当前测量的时间
u32 Getball_time(void);//得到小球上升的时间
extern u32 Count;//小球进入定时器中断的次数
extern u32 risetime;//小球上升的时间

#endif


