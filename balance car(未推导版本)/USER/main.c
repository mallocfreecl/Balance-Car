#include "sys.h"


//�ó���Ĭ�ϻ�е��ֵΪ0
float Pitch,Roll,Yaw;	   //�Ƕ�
short gyrox,gyroy,gyroz; //���ٶ�
short aacx,aacy,aacz;    //���ٶ�

int Enconder_Left,Enconder_Right;

int PWM_MAX=7200,PWM_MIN=-7200;
int MOTOR1,MOTOR2;

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//���ֻ��main������ֻ����һ�η���
	delay_init();
	uart_init(115200);
	 
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
		OLED_Float(0,0,Pitch,1);
		OLED_Float(50,50,velocity_out,1);
//		OLED_ShowNumber(30,0,Velocity_out,3,16);//OK
	 }

 }

