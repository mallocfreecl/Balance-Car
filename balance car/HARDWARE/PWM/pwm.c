#include "pwm.h"


//使用TIM1高级定时器产生PWM波
//输出比较通道：CH1(PA8) CH4(PA11)  比较值暂时设为0

void PWM_TIM1_Init(u16 Per,u16 Psc)
{
	//定义GPIO,定时器，输出比较的结构体
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCStructure;
	
  //1、开启GPIO,定时器的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_TIM1, ENABLE);
	
	//2、初始化GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 |GPIO_Pin_11;    //PA8、PA11   TIM1的CH1和CH4
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;           //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//3、初始化时基单元    时基单元默认使用内部时钟
	//TIM_TimeBaseStructInit(&TIM_TimeBaseInitStructure);    //加不加都可以，因为所有参数都设置了
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInitStructure.TIM_Period = Per;
  TIM_TimeBaseInitStructure.TIM_Prescaler = Psc; 
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
	
	//4、初始化输出比较
	TIM_OCStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCStructure.TIM_Pulse = 0;
	TIM_OC1Init(TIM1, &TIM_OCStructure);
	TIM_OC4Init(TIM1, &TIM_OCStructure);
	
	//5、使能主输出
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	
	//定时器部分ARR和输出值CCR的影子寄存器使能:只有发生更新事件时对数值进行装载
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM1,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM1,ENABLE);
	
	//6、开启定时器
	TIM_Cmd(TIM1,ENABLE);

}

