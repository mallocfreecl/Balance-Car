#include "sys.h"

float Med_Angle = 0; //��е��ֵ  ����ʵ������ı��е��ֵ
float Vertical_Kp,Vertical_Kd; //ֱ����Kp��Kd
float Velocity_Kp,Velocity_Ki; //�ٶȻ�Kp��Ki

int vertical_out,velocity_out,Turn_out,PWM_out; //ֱ����������ٶȻ������ת��


int PWM_MAX=7200,PWM_MIN=-7200;
int MOTOR1,MOTOR2;

 int main(void)
 {
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//���ֻ��main������ֻ����һ�η���
	 delay_init();
	 
	

	 while(1)
	 {
	   
	 }

 }

