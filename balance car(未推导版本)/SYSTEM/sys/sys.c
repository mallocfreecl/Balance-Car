#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK Mini STM32开发板
//系统中断分组设置化		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/10
//版本：V1.4
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
//********************************************************************************  
//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI  
void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}
//关闭所有中断
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}
//开启所有中断
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}
//设置栈顶地址
//addr:栈顶地址
__asm void MSR_MSP(u32 addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}

//void NVIC_Config(void)
//{
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//最好只在main函数中只进行一次分组
//	
//	//该代码也可直接放在EXTI.c的初始化函数中
//	NVIC_InitTypeDef NVIC_InitStructure;        
//  NVIC_InitStructure.NVIC_IRQChannel=EXTI9_5_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;	 //外部中断优先级设为最高
//	NVIC_Init(&NVIC_InitStructure);

//  //串口1已在usart.c中进行了NVIC设置
//}
