#include "key.h"

//PC15 按键
void key_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;                //该定义要提前	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//开启外设时钟
  
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;   
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;         //默认上拉高电平   //低电平表示按下
  //GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;   //检测输入,速度可有可无
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
 }

 //返回1表示按下，返回0表示没按下
 //mode: 0:不支持长按，长按只返回一次1，按键松开后再次检测   1:支持长按，长按就一直返回1
int KEY_Scan(u8 mode)
{  
	static u8 key_up=1;
	if(mode) key_up=1;//key_up为1表示按键抬起
	if(key_up==1 && KEY1==0)
	 {
		delay_ms(30);//消抖30ms
		key_up=0;
	  if(KEY1==0) return KEY1_PRES;  
	  }
	else if(KEY1==1) key_up=1;//按键抬起
  return 0;
}
