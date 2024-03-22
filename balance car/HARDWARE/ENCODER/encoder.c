#include "encoder.h"


//编码器1 使用TIM2 CH1(PA0) CH2(PA1)两个通道
void Encoder_TIM2_Init(void)
{
	//GPIO,定时器,输入捕获结构体定义    
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICStructure;
	
	//1、开启GPIO,定时器时钟    //GPIOA TIM2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	//2、GPIO初始化
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 |GPIO_Pin_1;    //PA0、PA1   TIM2的CH1和CH2
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;    //浮空输入  速度参数用不到
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//3、时基单元初始化
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStructure);
	TIM_TimeBaseInitStructure.TIM_Period=65536-1;//使用最大计数，方便u16转为s16时转化为负数
	TIM_TimeBaseInitStructure.TIM_Prescaler=1-1; 
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	//4、输入捕获初始化
	TIM_ICStructInit(&TIM_ICStructure);
	TIM_ICStructure.TIM_Channel=TIM_Channel_1;   //通道参数也可以不写，STM32编码器会直接占用整个TIMx定时器通道，
	TIM_ICStructure.TIM_ICFilter=10;             //编码器引脚也是固定的TIMx_Ch1和TIM_Ch2，通道已被硬件固化，不需要配置。
	TIM_ICInit(TIM2, &TIM_ICStructure);
	TIM_ICStructure.TIM_Channel=TIM_Channel_2;
	TIM_ICStructure.TIM_ICFilter=10;             //滤波参数
	TIM_ICInit(TIM2, &TIM_ICStructure);
	
	//5、编码器初始化
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12 ,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	//定时器计数器清零
	TIM_SetCounter(TIM2, 0);
	
	//6、开启定时器
	TIM_Cmd(TIM2,ENABLE);

}


//编码器2 使用TIM4 CH1(PB6) CH2(PB7)两个通道
void Encoder_TIM4_Init(void)
{
	//GPIO,定时器,输入捕获结构体定义    
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICStructure;
	
	//1、开启GPIO,定时器时钟    //GPIOB TIM4
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	//2、GPIO初始化
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6 |GPIO_Pin_7;    //PB6、PB7   TIM4的CH1和CH2
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;    //浮空输入  速度参数用不到
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//3、时基单元初始化
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStructure);
  TIM_TimeBaseInitStructure.TIM_Period=65536-1;//10k频率下计10000次定时1s
  TIM_TimeBaseInitStructure.TIM_Prescaler=1-1; 
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
	
	//4、输入捕获初始化
	TIM_ICStructInit(&TIM_ICStructure);
	TIM_ICStructure.TIM_Channel=TIM_Channel_1;
	TIM_ICStructure.TIM_ICFilter=10;
	TIM_ICInit(TIM4, &TIM_ICStructure);
	TIM_ICStructure.TIM_Channel=TIM_Channel_2;
	TIM_ICStructure.TIM_ICFilter=10;
	TIM_ICInit(TIM4, &TIM_ICStructure);
	
	//5、编码器初始化
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12 ,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	//定时器计数器清零
	TIM_SetCounter(TIM4, 0);
	
	//6、开启定时器
	TIM_Cmd(TIM4,ENABLE);
}

int Get_Speed(int TIM)
{
  //在keil5中 int是32位的有符号整数   short是16位的有符号整数
	int count = 0;
	switch(TIM)
	{
		case 2: count = (short)TIM_GetCounter(TIM2); TIM_SetCounter(TIM2, 0); break;  //short最后会转制转换为int型
		case 4: count = (short)TIM_GetCounter(TIM4); TIM_SetCounter(TIM4, 0); break;
		default: count = 0;
	}
	return count;
	
	//也可以这样简单的写
//	switch(TIM)
//	{
//		case 2: return (short)TIM_GetCounter(TIM2); TIM_SetCounter(TIM2, 0); break;  //short最后会转制转换为int型
//		case 4: return (short)TIM_GetCounter(TIM4); TIM_SetCounter(TIM4, 0); break;
//		default: return 0;
//	}
}
	








