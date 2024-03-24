#ifndef __LED_H//记得#ifndef后有空格
#define __LED_H

#include "sys.h"
//宏定义端口/位带操作
//#define LED0 PBout(5)
#define LED1 PCout(14)
//函数声明
void led_init(void);
#endif
