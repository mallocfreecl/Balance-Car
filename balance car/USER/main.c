#include "sys.h"

float Med_Angle = 0; //机械中值  根据实际情况改变机械中值
float Vertical_Kp,Vertical_Kd; //直立环Kp、Kd
float Velocity_Kp,Velocity_Ki; //速度环Kp、Ki

int vertical_out,velocity_out,Turn_out,PWM_out; //直立环输出、速度环输出、转向环


int PWM_MAX=7200,PWM_MIN=-7200;
int MOTOR1,MOTOR2;

 int main(void)
 {
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//最好只在main函数中只进行一次分组
	 delay_init();
	 
	

	 while(1)
	 {
	   
	 }

 }

