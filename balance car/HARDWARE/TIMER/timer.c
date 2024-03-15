#include "timer.h"
//��ʱ����ʼ������
//(ʱ����Ԫ�ṹ�嶨��/NVIC�ṹ�嶨��)
//1.RCC��ʱ��ʱ��ʹ��2.ѡ���ڲ�ʱ��/�ⲿʱ��3.ʱ����Ԫ��ʼ��
//(����жϱ�־λ)4.��ʱ���ж�ʹ��5.NVIC��ʼ��6.��ʱ��ʹ�ܿ���
//�жϷ����ӳ���


void timer_init(void)
 {
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//��������ʱ��
  
	TIM_InternalClockConfig(TIM2);//��ʱ��2ѡ���ڲ�ʱ��/ϵͳĬ�Ͼ��Ǹ����ÿ���ʡ��
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//�˲�����Ƶ��
  TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//���ϼ���
  TIM_TimeBaseInitStructure.TIM_Period=10000-1;//10kƵ���¼�10000�ζ�ʱ1s
  TIM_TimeBaseInitStructure.TIM_Prescaler=7200-1;
  TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;//�߼���ʱ�����ظ���������	 
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);//TIM�����жϣ���ֹ��ʱ����һ�γ�ʼ���ĸ�����
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);//������ʱ���ж�/�ڶ�������:TIM�����ж�Դ
	 
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//���ֻ��main������ֻ����һ�η���
  NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;	 
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2, ENABLE);
 }
 
 void TIM2_IRQHandler(void)
 {
    //if(TIM_GetFlagStatus(TIM2,TIM_FLAG_Update)==SET)//��ʱ�жϲ��øú���
 
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    LED0=!LED0;
		
 }
		
