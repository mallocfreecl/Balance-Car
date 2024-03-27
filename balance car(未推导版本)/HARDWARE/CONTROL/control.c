#include "control.h"

//该程序默认机械中值为0
float Med_Angle = 0; //机械中值  根据实际情况改变机械中值
float Target_Speed = 0; //二次开发，期望速度


float Vertical_Kp,Vertical_Kd; //直立环Kp、Kd
float Velocity_Kp,Velocity_Ki; //速度环Kp、Ki
float Turn_Kp;

int vertical_out,velocity_out,Turn_out,PWM_out; //直立环输出、速度环输出、转向环

//角度是相对于机械中值(Med_Angle)的角度  
//Angle~A    A(r):当前角度    A(e):理想角度  A(e) == Med_Angle == 0
//PD: 比例微分 直立环：对Y轴的角度进行PD控制
//vertical_out = Kp*(A(r)-A(e))+Kd*( ( A(t)-A(e) ) - ( A(t-1)-A(e) ) )    //偏差的微分 两边的-A(e)可以消掉
//vertical_out = Kp*(A(r)-A(e))+Kd*(A(t)-A(t-1))    (A(t)-A(t-1))的原因: (A(t)-A(t-1))/t  t取1(即使取1，Kd可以主动控制)  

//入口参数：期望角度，真实角度(当前角度)，真实角速度(当前角速度)

//最后串级PID的结果: Kp1*真实角度 + Kd*角度偏差的微分 - Kp1*(Kp2*编码器偏差-Ki* 编码器偏差的积分) Kp1:直立环的Kp  Kp2:速度环的Kp
int Vertical(float Med, float Angle, float gyro_Y)  //入口参数可以优化一下
{
	int PWM_out;
	PWM_out = Vertical_Kp * (Angle - Med) + Vertical_Kd * gyro_Y; //这里的float*float 是float类型,强转为int时会舍弃小数
	return PWM_out;
}


//PI: 比例积分 速度环：对编码器读取的速度进行PD控制
//vertical_out = Kp*Ek+Ki*Ek_S     Ek:速度的偏差  Ek_S:速度的偏差的积分
int Velocity(int target_speed,int encoder_left,int encoder_right)  //入口参数可以优化一下
{
	//对PWM输出、编码器偏差、低通滤波输出、低通滤波输出的积分、对本次低通滤波输出进行记录  低通滤波系数进行定义
	static int PWM_out, Encoder_Err, EnC_Err_Lowout, EnC_Err_Lowout_S, EnC_Err_Lowout_Last;//局部静态变量未初始化时值为0，与全局变量相同
	float a = 0.7;
	
	//1、计算编码器偏差
	Encoder_Err = (encoder_left + encoder_right) - target_speed;//期望速度为0  舍去误差
	
	//2、对速度偏差进行低通滤波         //??
	EnC_Err_Lowout = (1-a) * Encoder_Err + a * EnC_Err_Lowout_Last;
	EnC_Err_Lowout_Last = EnC_Err_Lowout;
	
	//3、对速度偏差低通滤波进行积分
	EnC_Err_Lowout_S += EnC_Err_Lowout;
	
	//4、对速度偏差低通滤波积分进行限幅  为什么是10000？？
	EnC_Err_Lowout_S = EnC_Err_Lowout_S >= 10000 ? 10000 :(EnC_Err_Lowout_S <= -10000 ? (-10000) : EnC_Err_Lowout_S);
	
	//5、速度环控制输出
	PWM_out = Velocity_Kp * EnC_Err_Lowout + Velocity_Ki * EnC_Err_Lowout_S;
	
//	if(Pitch<-40||Pitch>40) 	EnC_Err_Lowout_S=0;     						//===电机关闭后清除积分
	return PWM_out;
}


//转向环
int Turn(int gyro_Z) //入口参数为Z轴角速度
{
	int PWM_out;
	PWM_out = (-Turn_Kp) * gyro_Z;
	return PWM_out;

}

void EXTI9_5_IRQHandler(void) //检测到mpu6050的下降沿信号
{
 if( EXTI_GetITStatus(EXTI_Line5) == SET) 
 {
	 if(PBout(5) == 0) //二次检测，检测到引脚电平为低
	 {
	  EXTI_ClearITPendingBit(EXTI_Line5);//中断标志位清零
	  //1、采集编码器数据及MPU6050的数据
		Enconder_Left = - Get_Speed(2);  //接的是A编码器接口
		Enconder_Right = Get_Speed(3);   //接的是B编码器接口
		
		mpu_dmp_get_data(&Pitch,&Roll,&Yaw);	
		MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);
		MPU_Get_Accelerometer(&aacx,&aacy,&aacz);
		
		//2、将数据压入闭环控制，计算控制量
		
		velocity_out = Velocity(Target_Speed,Enconder_Left,Enconder_Right); //速度环  外环
		vertical_out = Vertical(velocity_out+Med_Angle,Pitch,gyroy);        //直立环  内环
		Turn_out = Turn(gyroz);
		PWM_out = vertical_out;
		 
		//3、将控制量输出到电机上
		MOTOR1 = PWM_out - Turn_out;
		MOTOR2 = PWM_out + Turn_out;
		Limit(&MOTOR1,&MOTOR2);
		Load(MOTOR1,MOTOR2);
	 }
 }
}
