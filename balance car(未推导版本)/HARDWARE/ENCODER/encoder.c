#include "encoder.h"


//������1 ʹ��TIM2 CH1(PA0) CH2(PA1)����ͨ��   //Ӳ���ϲ����B������ٶ�
void Encoder_TIM2_Init(void)
{
	//GPIO,��ʱ��,���벶��ṹ�嶨��    
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICStructure;
	
	//1������GPIO,��ʱ��ʱ��    //GPIOA TIM2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	//2��GPIO��ʼ��
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 |GPIO_Pin_1;    //PA0��PA1   TIM2��CH1��CH2
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;    //��������  �ٶȲ����ò���
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//3��ʱ����Ԫ��ʼ��
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStructure);
	TIM_TimeBaseInitStructure.TIM_Period=65536-1;//ʹ��������������u16תΪs16ʱת��Ϊ����
	TIM_TimeBaseInitStructure.TIM_Prescaler=1-1; 
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	//4�����벶���ʼ��
	TIM_ICStructInit(&TIM_ICStructure);
	TIM_ICStructure.TIM_Channel=TIM_Channel_1;   //ͨ������Ҳ���Բ�д��STM32��������ֱ��ռ������TIMx��ʱ��ͨ����
	TIM_ICStructure.TIM_ICFilter=10;             //����������Ҳ�ǹ̶���TIMx_Ch1��TIM_Ch2��ͨ���ѱ�Ӳ���̻�������Ҫ���á�
	TIM_ICInit(TIM2, &TIM_ICStructure);
	TIM_ICStructure.TIM_Channel=TIM_Channel_2;
	TIM_ICStructure.TIM_ICFilter=10;             //�˲�����
	TIM_ICInit(TIM2, &TIM_ICStructure);
	
	//5����������ʼ��
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12 ,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	//��ʱ������������
	TIM_SetCounter(TIM2, 0);
	
	//6��������ʱ��
	TIM_Cmd(TIM2,ENABLE);

}


//������2 ʹ��TIM3 CH1(PA6) CH2(PA7)����ͨ��          //Ӳ���ϲ����A������ٶ�
void Encoder_TIM3_Init(void)             
{
	//GPIO,��ʱ��,���벶��ṹ�嶨��    
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICStructure;
	
	//1������GPIO,��ʱ��ʱ��    //GPIOA TIM3
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	//2��GPIO��ʼ��
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6 |GPIO_Pin_7;    //PA6��PA7   TIM3��CH1��CH2
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;    //��������  �ٶȲ����ò���
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//3��ʱ����Ԫ��ʼ��
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStructure);
	TIM_TimeBaseInitStructure.TIM_Period=65536-1;      //10kƵ���¼�10000�ζ�ʱ1s
	TIM_TimeBaseInitStructure.TIM_Prescaler=1-1; 
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	//4�����벶���ʼ��
	TIM_ICStructInit(&TIM_ICStructure);
	TIM_ICStructure.TIM_Channel=TIM_Channel_1;
	TIM_ICStructure.TIM_ICFilter=10;
	TIM_ICInit(TIM3, &TIM_ICStructure);
	TIM_ICStructure.TIM_Channel=TIM_Channel_2;
	TIM_ICStructure.TIM_ICFilter=10;
	TIM_ICInit(TIM3, &TIM_ICStructure);
	
	//5����������ʼ��
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12 ,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	//��ʱ������������
	TIM_SetCounter(TIM3, 0);
	
	//6��������ʱ��
	TIM_Cmd(TIM3,ENABLE);
}

int Get_Speed(int TIM)
{
  //��keil5�� int��32λ���з�������   short��16λ���з�������
	int count = 0;
	switch(TIM)
	{
		case 2: count = (short)TIM_GetCounter(TIM2); TIM_SetCounter(TIM2, 0); break;  //short����ת��ת��Ϊint��
		case 3: count = (short)TIM_GetCounter(TIM3); TIM_SetCounter(TIM3, 0); break;
		default: count = 0;
	}
	return count;
	
	//Ҳ���������򵥵�д
//	switch(TIM)
//	{
//		case 2: return (short)TIM_GetCounter(TIM2); TIM_SetCounter(TIM2, 0); break;  //short����ת��ת��Ϊint��
//		case 3: return (short)TIM_GetCounter(TIM3); TIM_SetCounter(TIM3, 0); break;
//		default: return 0;
//	}
}
	








