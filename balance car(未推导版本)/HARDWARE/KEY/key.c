#include "key.h"


//PC15 ����
void key_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;                //�ö���Ҫ��ǰ	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//��������ʱ��
  
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;   
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;     //Ĭ�������ߵ�ƽ   //�͵�ƽ��ʾ����
  //GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; //�������,�ٶȿ��п���
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
 }
int KEY_Scan(u8 mode)
{  
	static u8 key_up=1;
	if(mode) key_up=1;//key_upΪ1��ʾ����̧��
	if(key_up==1 && KEY1==0)
	 {
		delay_ms(30);//����30ms
		key_up=0;
	    if(KEY1==0) return KEY1_PRES;
	  }
	else if(KEY1==1) key_up=1;//����̧��
    return 0;
}
