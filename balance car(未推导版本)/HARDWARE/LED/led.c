#include "led.h"

//LED PC14
void led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;                 //�ö���Ҫ��ǰ	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);//��������ʱ��
	  
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
  GPIO_SetBits(GPIOC,GPIO_Pin_14);  //�ߵ�ƽϨ�𣬵͵�ƽ��
 
}
 
