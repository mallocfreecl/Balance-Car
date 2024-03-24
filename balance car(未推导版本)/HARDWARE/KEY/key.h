#ifndef __KEY_H//记得#ifndef后有空格
#define __KEY_H

#include "sys.h"
#include "delay.h"
//宏定义端口读取的值
//#define KEY0 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)
#define KEY1 GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_15)
//#define KEY2 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)
//#define WKUP GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) 

//宏定义键值
//#define KEY0_PRES 1
#define KEY1_PRES 1
//#define KEY2_PRES 3
//#define WKUP_PRES 4
//#define UN_PRESS 0

//宏定义端口/位带操作
//#define KEY0_PRES PEout(4)
//#define KEY1_PRES PEout(3)
//#define KEY2_PRES PEout(2)
//#define WKUP_PRES PAout(0)

//函数声明
void key_init(void);
int KEY_Scan(u8 mode);
#endif
