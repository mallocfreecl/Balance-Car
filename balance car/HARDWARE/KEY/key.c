#include "key.h"

void key_init(void)
 {
  GPIO_InitTypeDef GPIO_InitStructure;//�ö���Ҫ��ǰ	 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOA, ENABLE);//��������ʱ��
  
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//Ĭ�������ߵ�ƽ 
  //GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; //�������,�ٶȿ��п���
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;//Ĭ�������͵�ƽ
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
 }
int KEY_Scan(u8 mode)
{  static u8 key_up=1;
	 if(mode) key_up=1;//key_upΪ1��ʾ����̧��
   if(key_up==1&&(KEY0==0||KEY1==0||KEY2==0||WKUP==1))
	   {
			 delay_ms(50);//����
			 key_up=0;
			 if(KEY0==0) return KEY0_PRES;
	     else if(KEY1==0) return KEY1_PRES;
			 else if(KEY2==0) return KEY2_PRES;
			 else if(WKUP==1) return WKUP_PRES;
	 
	   }else if(KEY0==1&&KEY1==1&&KEY2==1&&WKUP==0) key_up=1;//����̧��

    return 0;
}
