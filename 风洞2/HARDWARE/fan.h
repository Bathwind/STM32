#ifndef __FAN_H
#define __FAN_H	 
#include "sys.h"
#define fan2 PAout(7)	// PA8
#define fan1 PAout(8)	// PA8
#define led1 PCout(13)
void fan_open(void);
void fan_close(void);
#endif
