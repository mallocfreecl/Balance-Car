#ifndef __ENCODER
#define __ENCODER
#include "sys.h"

void Encoder_TIM2_Init(void);
void Encoder_TIM3_Init(void);
int Get_Speed(int TIM);

#endif
