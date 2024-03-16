#include "exti.h"

//开启中断的6个步骤
//一般GPIO和NVIC的结构体声明要提前,否则报错
//1.GPIO和AFIO时钟（RCC）
//2.GPIO初始化
//3.配置AFIO，设置中断通道(利用AFIO设置中断通道)
//4.初始化中断(exti)
//5.初始化NVIC(相关函数可在misc.h中找到)可在子函数或主函数中设置中断分组
//6.中断服务函数(函数名字可在启动文件中找到)


//使用外部中断5  GPIO:PB5  下降沿触发   NVIC的设置与开启放到主函数里
void MPU6050_Exti_Init(void)
{
	//定义结构体
	GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;  
	
	//1、开启GPIO与AFIO的时钟  AFIO常用于中断映射与重映射
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
  
	//2、GPIO初始化
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;        //PB5
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;    //上拉输入，因为是检测下降沿  速度参数用不到
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//3、配置AFIO，设置中断通道(利用AFIO设置中断通道)
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource5);//中断通道5与PB5联系起来
  
	//4、初始化中断(exti)
	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;//中断触发
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//下降沿触发
  EXTI_Init(&EXTI_InitStructure);
	
	//5、配置NVIC   
  NVIC_InitStructure.NVIC_IRQChannel=EXTI9_5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;	 //外部中断优先级设为最高，该中断不可被打断
	NVIC_Init(&NVIC_InitStructure);
}



		
