#include "key.h"

void key_init(void)
 {
  GPIO_InitTypeDef GPIO_InitStructure;//该定义要提前	 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOA, ENABLE);//开启外设时钟
  
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//默认上拉高电平 
  //GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; //检测输入,速度可有可无
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;//默认下拉低电平
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
 }
int KEY_Scan(u8 mode)
{  static u8 key_up=1;
	 if(mode) key_up=1;//key_up为1表示按键抬起
   if(key_up==1&&(KEY0==0||KEY1==0||KEY2==0||WKUP==1))
	   {
			 delay_ms(50);//消抖
			 key_up=0;
			 if(KEY0==0) return KEY0_PRES;
	     else if(KEY1==0) return KEY1_PRES;
			 else if(KEY2==0) return KEY2_PRES;
			 else if(WKUP==1) return WKUP_PRES;
	 
	   }else if(KEY0==1&&KEY1==1&&KEY2==1&&WKUP==0) key_up=1;//按键抬起

    return 0;
}
