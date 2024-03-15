#ifndef __PWM
#define __PWM
#include "sys.h"

#define Ain1 PBout(14)   //根据硬件接线改变
#define Ain2 PBout(15)

#define Bin1 PBout(13)
#define Bin2 PBout(12)

//函数声明

void PWM_TIM1_Init(u16 Per,u16 Psc);
void Limit(int* MOTORA,int* MOTORB);
int GFP_abs(int num);
void Load(int motor1,int motor2);


#endif
