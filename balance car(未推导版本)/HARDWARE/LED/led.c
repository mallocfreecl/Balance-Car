#include "led.h"

//LED PC14
void led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;                 //该定义要提前	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);//开启外设时钟
	  
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
  GPIO_SetBits(GPIOC,GPIO_Pin_14);  //高电平熄灭，低电平亮
 
}
 
