#include "control.h"

float Pitch,Roll,Yaw;	   //�Ƕ�
short gyrox,gyroy,gyroz; //���ٶ�
short aacx,aacy,aacz;    //���ٶ�

int Enconder_Left,Enconder_Right;



//�Ƕ�������ڻ�е��ֵ(Med_Angle)�ĽǶ�  
//Angle~A    A(r):��ǰ�Ƕ�    A(e):����Ƕ�  A(e) == Med_Angle == 0
//PD: ����΢�� ֱ��������Y��ĽǶȽ���PD����
//vertical_out = Kp*(A(r)-A(e))+Kd*( ( A(t)-A(e) ) - ( A(t-1)-A(e) ) )    //ƫ���΢�� ���ߵ�-A(e)��������
//vertical_out = Kp*(A(r)-A(e))+Kd*(A(t)-A(t-1))    (A(t)-A(t-1))��ԭ��: (A(t)-A(t-1))/t  tȡ1(��ʹȡ1��Kd������������)  

//��ڲ����������Ƕȣ���ʵ�Ƕ�(��ǰ�Ƕ�)����ʵ���ٶ�(��ǰ���ٶ�)

//��󴮼�PID�Ľ��: Kp1*��ʵ�Ƕ� + Kd*�Ƕ�ƫ���΢�� - Kp1*(Kp2*������ƫ��-Ki* ������ƫ���΢��) Kp1:ֱ������Kp  Kp2:�ٶȻ���Kp
int Vertical(float Med,float Angle,float gyro_Y)  //��ڲ��������Ż�һ��
{
	int PWM_out;
	PWM_out = Vertical_Kp * Angle + Vertical_Kd * gyro_Y; //���������float*float ��ʲô���� int = float���������������ת����
	return PWM_out;
}


//PI: �������� �ٶȻ����Ա�������ȡ���ٶȽ���PD����
//vertical_out = Kp*Ek+Ki*Ek_S     Ek:�ٶȵ�ƫ��  Ek_S:�ٶȵ�ƫ��Ļ���
int Velocity(int encoder_left,int encoder_right)  //��ڲ��������Ż�һ��
{
	//��PWM�����������ƫ���ͨ�˲��������ͨ�˲�����Ļ��֡��Ա��ε�ͨ�˲�������м�¼  ��ͨ�˲�ϵ�����ж���
	static int PWM_out, Encoder_Err, EnC_Err_Lowout, EnC_Err_Lowout_S, EnC_Err_Lowout_Last = 0;//EnC_Err_Lowout_Last�����ʼ��Ϊ0 ������ʼ�������ԣ���Ϊ�����ֵ�Ḳ��
	float a = 0.7;
	
	//1�����������ƫ��
	Encoder_Err = (encoder_left + encoder_right) - 0;//�����ٶ�Ϊ0  ��ȥ���
	
	//2�����ٶ�ƫ����е�ͨ�˲�         //??
	EnC_Err_Lowout = (1-a)*Encoder_Err + a * EnC_Err_Lowout_Last;
	EnC_Err_Lowout_Last = EnC_Err_Lowout;
	
	//3�����ٶ�ƫ���ͨ�˲����л���
	EnC_Err_Lowout_S += EnC_Err_Lowout;
	
	//4�����ٶ�ƫ���ͨ�˲����ֽ����޷�  Ϊʲô��10000����
	EnC_Err_Lowout_S = EnC_Err_Lowout_S >= 10000 ? EnC_Err_Lowout_S :(EnC_Err_Lowout_S <= -10000 ? (-10000) : EnC_Err_Lowout_S);
	
	//5���ٶȻ��������
	PWM_out = Velocity_Kp * EnC_Err_Lowout + Velocity_Ki * EnC_Err_Lowout_S;
	return PWM_out;
}


//ת��
int Turn(int gyro_Z) //��ڲ���ΪZ����ٶ�
{
	int PWM_out;
	PWM_out = (-0.5) * gyro_Z;
	return PWM_out;

}

void EXTI9_5_IRQHandler(void) //��⵽mpu6050���½����ź�
{
 if( EXTI_GetITStatus(EXTI_Line5) == SET) 
 {
	 if(PBout(5) == 0) //���μ�⣬��⵽���ŵ�ƽΪ��
	 {
	  EXTI_ClearITPendingBit(EXTI_Line5);//�жϱ�־λ����
	  //1���ɼ����������ݼ�MPU6050������
		Enconder_Left = - Get_Speed(2);
		Enconder_Right = Get_Speed(4);
		
		mpu_dmp_get_data(&Pitch,&Roll,&Yaw);	
		MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);
		MPU_Get_Accelerometer(&aacx,&aacy,&aacz);
		
		//2��������ѹ��ջ����ƣ����������
		vertical_out = Vertical(Med_Angle,Pitch,gyroy);
		velocity_out = Velocity(Enconder_Left,Enconder_Right);
		Turn_out = Turn(gyroz);
		PWM_out = vertical_out - Vertical_Kp * velocity_out;
		 
		//3��������������������
		MOTOR1 = PWM_out - Turn_out;
		MOTOR2 = PWM_out + Turn_out;
		Limit(&MOTOR1,&MOTOR2);
		Load(MOTOR1,MOTOR2);
	 }
 }
}
