#include "led.h"
void led_init(void)
 {
  GPIO_InitTypeDef GPIO_InitStructure;//该定义要提前	 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);//开启外设时钟
  
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; 
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
  
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_SetBits(GPIOE,GPIO_Pin_5);
 }
 
