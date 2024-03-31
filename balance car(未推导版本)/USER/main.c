#include "sys.h"


//该程序默认机械中值为0
float Pitch,Roll,Yaw;	   //角度
short gyrox,gyroy,gyroz; //角速度
short aacx,aacy,aacz;    //加速度

int Enconder_Left,Enconder_Right;

int PWM_MAX=7200,PWM_MIN=-7200;
int MOTOR1,MOTOR2;

uint16_t temp;

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//最好只在main函数中只进行一次分组
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
		

//按键测试            测试正常
//使用按键控制LED
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
		
//LED、Delay代码测试	  测试正常	
//亮1.5s,灭1.5s
//		LED1 = 0;
//		delay_ms(1500);//delay函数没有问题，不要超过1864
//		LED1 = 1;
//		delay_ms(1500);


//OLED代码测试	        测试正常	
//OLED测试   
		  OLED_Float(0,0,Pitch,1);
			OLED_Float(2,0,Enconder_Left,1);
			OLED_Float(4,0,Enconder_Right,1);
//		OLED_Float(2,0,Get_battery_volt(),1);     //ADC测试正常
//		OLED_Float(4,0,MPU_Read_Byte(MPU_DEVICE_ID_REG),1);
//		OLED_Float(2,0,velocity_out,1);
//		OLED_ShowNumber(0,10,velocity_out,3,16);//注意是x,y
//		delay_ms(50);
	

//UART1串口测试         测试正常
//		uint16_t len,i;
//		if (USART_RX_STA & 0x8000) /* 接收到了数据? */ 
//		 { 
//		 len = USART_RX_STA & 0x3fff; /* 得到此次接收到的数据长度 */ 
//		 printf("\r\n 您发送的消息为:\r\n"); 
//		 
//		/*发送接收到的数据*/ 
//			for(i = 0; i <= len; i++)
//			{
//				USART_SendData(USART1,USART_RX_BUF[i]);
//				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
//			}
//		 printf("\r\n\r\n"); /* 插入换行 */ 
//		 USART_RX_STA = 0; 
//		 } 
	 }

 }

 
