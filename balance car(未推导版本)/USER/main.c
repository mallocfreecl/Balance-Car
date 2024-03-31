#include "sys.h"


//�ó���Ĭ�ϻ�е��ֵΪ0
float Pitch,Roll,Yaw;	   //�Ƕ�
short gyrox,gyroy,gyroz; //���ٶ�
short aacx,aacy,aacz;    //���ٶ�

int Enconder_Left,Enconder_Right;

int PWM_MAX=7200,PWM_MIN=-7200;
int MOTOR1,MOTOR2;

uint16_t temp;

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//���ֻ��main������ֻ����һ�η���
	delay_init();
	uart_init(115200);
	 
	led_init();
	key_init();
	AD_Init();
	
	OLED_Init();
	OLED_Clear();
	
	MPU_Init();
	mpu_dmp_init();
	MPU6050_Exti_Init();
	 
	Encoder_TIM2_Init();
	Encoder_TIM3_Init();
	Motor_Init();
	PWM_TIM1_Init(0,7199);
	
	while(1)
	{
		

//��������            ��������
//ʹ�ð�������LED
//		if(KEY_Scan(0) == 1)
//		{	
//			if(temp) 
//			{
//				LED1 = 0; 
//			}
//			else
//			{
//				LED1 = 1;
//			}
//			temp = !temp;
//		
//		}
		
//LED��Delay�������	  ��������	
//��1.5s,��1.5s
//		LED1 = 0;
//		delay_ms(1500);//delay����û�����⣬��Ҫ����1864
//		LED1 = 1;
//		delay_ms(1500);


//OLED�������	        ��������	
//OLED����   
		  OLED_Float(0,0,Pitch,1);
			OLED_Float(2,0,Enconder_Left,1);
			OLED_Float(4,0,Enconder_Right,1);
//		OLED_Float(2,0,Get_battery_volt(),1);     //ADC��������
//		OLED_Float(4,0,MPU_Read_Byte(MPU_DEVICE_ID_REG),1);
//		OLED_Float(2,0,velocity_out,1);
//		OLED_ShowNumber(0,10,velocity_out,3,16);//ע����x,y
//		delay_ms(50);
	

//UART1���ڲ���         ��������
//		uint16_t len,i;
//		if (USART_RX_STA & 0x8000) /* ���յ�������? */ 
//		 { 
//		 len = USART_RX_STA & 0x3fff; /* �õ��˴ν��յ������ݳ��� */ 
//		 printf("\r\n �����͵���ϢΪ:\r\n"); 
//		 
//		/*���ͽ��յ�������*/ 
//			for(i = 0; i <= len; i++)
//			{
//				USART_SendData(USART1,USART_RX_BUF[i]);
//				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
//			}
//		 printf("\r\n\r\n"); /* ���뻻�� */ 
//		 USART_RX_STA = 0; 
//		 } 
	 }

 }

 
