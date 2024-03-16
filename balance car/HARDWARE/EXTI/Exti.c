#include "exti.h"

//�����жϵ�6������
//һ��GPIO��NVIC�Ľṹ������Ҫ��ǰ,���򱨴�
//1.GPIO��AFIOʱ�ӣ�RCC��
//2.GPIO��ʼ��
//3.����AFIO�������ж�ͨ��(����AFIO�����ж�ͨ��)
//4.��ʼ���ж�(exti)
//5.��ʼ��NVIC(��غ�������misc.h���ҵ�)�����Ӻ������������������жϷ���
//6.�жϷ�����(�������ֿ��������ļ����ҵ�)


//ʹ���ⲿ�ж�5  GPIO:PB5  �½��ش���   NVIC�������뿪���ŵ���������
void MPU6050_Exti_Init(void)
{
	//����ṹ��
	GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;  
	
	//1������GPIO��AFIO��ʱ��  AFIO�������ж�ӳ������ӳ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
  
	//2��GPIO��ʼ��
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;        //PB5
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;    //�������룬��Ϊ�Ǽ���½���  �ٶȲ����ò���
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//3������AFIO�������ж�ͨ��(����AFIO�����ж�ͨ��)
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource5);//�ж�ͨ��5��PB5��ϵ����
  
	//4����ʼ���ж�(exti)
	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;//�жϴ���
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//�½��ش���
  EXTI_Init(&EXTI_InitStructure);
	
	//5������NVIC   
  NVIC_InitStructure.NVIC_IRQChannel=EXTI9_5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;	 //�ⲿ�ж����ȼ���Ϊ��ߣ����жϲ��ɱ����
	NVIC_Init(&NVIC_InitStructure);
}



		
