#ifndef __MOTOR
#define __MOTOR
#include "sys.h"


//��Ƭ�����������ģ����źţ����������������ת
#define Ain1 PBout(13)    //A����Ŀ�����
#define Ain2 PBout(12)

#define Bin1 PBout(14)    //B����Ŀ�����
#define Bin2 PBout(15)

void Motor_Init(void);
void Limit(int* MOTORA,int* MOTORB);
int GFP_abs(int num);
void Load(int motor1,int motor2);
void Turn_Off(float angle, float voltage);

#endif
