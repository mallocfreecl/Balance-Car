#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK Mini STM32������
//ϵͳ�жϷ������û�		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/10
//�汾��V1.4
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
//********************************************************************************  
//THUMBָ�֧�ֻ������
//�������·���ʵ��ִ�л��ָ��WFI  
void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}
//�ر������ж�
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}
//���������ж�
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}
//����ջ����ַ
//addr:ջ����ַ
__asm void MSR_MSP(u32 addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}

//void NVIC_Config(void)
//{
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//���ֻ��main������ֻ����һ�η���
//	
//	//�ô���Ҳ��ֱ�ӷ���EXTI.c�ĳ�ʼ��������
//	NVIC_InitTypeDef NVIC_InitStructure;        
//  NVIC_InitStructure.NVIC_IRQChannel=EXTI9_5_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;	 //�ⲿ�ж����ȼ���Ϊ���
//	NVIC_Init(&NVIC_InitStructure);

//  //����1����usart.c�н�����NVIC����
//}
