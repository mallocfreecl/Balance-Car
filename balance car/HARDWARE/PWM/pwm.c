#include "pwm.h"


//ʹ��TIM1�߼���ʱ������PWM��
//����Ƚ�ͨ����CH1(PA8) CH4(PA11)  �Ƚ�ֵ��ʱ��Ϊ0

void PWM_TIM1_Init(u16 Per,u16 Psc)
{
	//����GPIO,��ʱ��������ȽϵĽṹ��
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCStructure;
	
  //1������GPIO,��ʱ����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_TIM1, ENABLE);
	
	//2����ʼ��GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 |GPIO_Pin_11;    //PA8��PA11   TIM1��CH1��CH4
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;           //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//3����ʼ��ʱ����Ԫ    ʱ����ԪĬ��ʹ���ڲ�ʱ��
	//TIM_TimeBaseStructInit(&TIM_TimeBaseInitStructure);    //�Ӳ��Ӷ����ԣ���Ϊ���в�����������
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInitStructure.TIM_Period = Per;
  TIM_TimeBaseInitStructure.TIM_Prescaler = Psc; 
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
	
	//4����ʼ������Ƚ�
	TIM_OCStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCStructure.TIM_Pulse = 0;
	TIM_OC1Init(TIM1, &TIM_OCStructure);
	TIM_OC4Init(TIM1, &TIM_OCStructure);
	
	//5��ʹ�������
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	
	//��ʱ������ARR�����ֵCCR��Ӱ�ӼĴ���ʹ��:ֻ�з��������¼�ʱ����ֵ����װ��
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM1,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM1,ENABLE);
	
	//6��������ʱ��
	TIM_Cmd(TIM1,ENABLE);

}

