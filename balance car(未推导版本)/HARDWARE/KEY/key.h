#ifndef __KEY_H//�ǵ�#ifndef���пո�
#define __KEY_H

#include "sys.h"
#include "delay.h"
//�궨��˿ڶ�ȡ��ֵ
//#define KEY0 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)
#define KEY1 GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_15)
//#define KEY2 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)
//#define WKUP GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) 

//�궨���ֵ
//#define KEY0_PRES 1
#define KEY1_PRES 1
//#define KEY2_PRES 3
//#define WKUP_PRES 4
//#define UN_PRESS 0

//�궨��˿�/λ������
//#define KEY0_PRES PEout(4)
//#define KEY1_PRES PEout(3)
//#define KEY2_PRES PEout(2)
//#define WKUP_PRES PAout(0)

//��������
void key_init(void);
int KEY_Scan(u8 mode);
#endif
