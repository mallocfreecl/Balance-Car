#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "led.h"
#include "key.h"
#include "timer.h"


int PWM_MAX=7200,PWM_MIN=-7200;
int MOTOR1,MOTOR2;

 int main(void)
 {
	 delay_init();
	 led_init();
   key_init();
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�жϷ���Ϊ2
	 timer_init();

	 while(1)
	 {
	   LED1=!LED1;//LED0Ϩ��
		 delay_ms(200);
	 }

 }
//NVIC_InitTypeDef NVIC_InitStructure;
//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//���ֻ��main������ֻ����һ�η���
//  NVIC_InitStructure.NVIC_IRQChannel=EXTI2_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;	 
//	NVIC_Init(&NVIC_InitStructure);
