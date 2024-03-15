#include "timer.h"
//定时器初始化过程
//(时基单元结构体定义/NVIC结构体定义)
//1.RCC定时器时钟使能2.选择内部时钟/外部时钟3.时基单元初始化
//(清除中断标志位)4.定时器中断使能5.NVIC初始化6.定时器使能开启
//中断服务子程序


void timer_init(void)
 {
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//开启外设时钟
  
	TIM_InternalClockConfig(TIM2);//定时器2选择内部时钟/系统默认就是该设置可以省略
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//滤波采样频率
  TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//向上计数
  TIM_TimeBaseInitStructure.TIM_Period=10000-1;//10k频率下计10000次定时1s
  TIM_TimeBaseInitStructure.TIM_Prescaler=7200-1;
  TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;//高级定时器的重复计数功能	 
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);//TIM更新中断，防止定时器第一次初始化的副作用
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);//开启定时器中断/第二个参数:TIM更新中断源
	 
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//最好只在main函数中只进行一次分组
  NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;	 
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2, ENABLE);
 }
 
 void TIM2_IRQHandler(void)
 {
    //if(TIM_GetFlagStatus(TIM2,TIM_FLAG_Update)==SET)//延时判断才用该函数
 
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    LED0=!LED0;
		
 }
		
