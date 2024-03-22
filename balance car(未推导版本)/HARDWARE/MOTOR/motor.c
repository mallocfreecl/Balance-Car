#include "motor.h"


//对电机驱动模块控制正反转信号进行初始化
void Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 |GPIO_Pin_13 |GPIO_Pin_14 |GPIO_Pin_15;  //PB12、PB13、PB14、PB15
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;           //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

}

//限幅函数
void Limit(int* MOTORA,int* MOTORB)
{
	if(*MOTORA >= PWM_MAX) *MOTORA =PWM_MAX;
	if(*MOTORA <= PWM_MIN) *MOTORA =PWM_MIN;
	
	if(*MOTORB >= PWM_MAX) *MOTORB =PWM_MAX;
	if(*MOTORB <= PWM_MIN) *MOTORB =PWM_MIN;
}

//绝对值函数
int GFP_abs(int num)
{
	return num>=0 ? num :(-num);
}


//赋值函数
//入口参数：PID运算完最终的PWM值
void Load(int motor1,int motor2)
{
	if(motor1 >= 0) {Ain1 = 1; Ain2 = 0;}//正转
	else            {Ain1 = 0; Ain2 = 1;}//反转
	TIM_SetCompare1(TIM1,GFP_abs(motor1));
	
	if(motor2 >= 0) {Bin1 = 1; Bin2 = 0;}
	else            {Bin1 = 0; Bin2 = 1;}
	TIM_SetCompare4(TIM1,GFP_abs(motor2));

}

