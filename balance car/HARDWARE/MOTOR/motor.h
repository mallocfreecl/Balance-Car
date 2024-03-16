#ifndef __MOTOR
#define __MOTOR
#include "sys.h"


//单片机给电机驱动模块的信号，控制两个电机正反转
#define Ain1 PBout(14)   //根据硬件接线改变
#define Ain2 PBout(15)

#define Bin1 PBout(13)
#define Bin2 PBout(12)

void Motor_Init(void);
void Limit(int* MOTORA,int* MOTORB);
int GFP_abs(int num);
void Load(int motor1,int motor2);

#endif
