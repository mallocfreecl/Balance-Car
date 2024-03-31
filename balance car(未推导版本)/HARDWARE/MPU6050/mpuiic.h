#ifndef __MPUIIC_H
#define __MPUIIC_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK MiniSTM32F103开发板
//MPU6050 IIC驱动 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/4/18
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
	   		   
//IO方向设置           //注意：使用该IIC文件，不仅要改.h文件的配置，还要在.c文件中修改为GPIO的相应引脚

//GPIO的CR寄存器，用于配置GPIO的模式与输出速度，4个位决定一个GPIO.x的模式
//CRL(32位)决定GPIO.0-GPIO.7这8个端口的模式  CRH(32位)决定GPIO.8-GPIO.15这8个端口的模式
//1.现将4位清零  2.设置对应的模式  


#define MPU_SDA_IN()   {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(uint32_t)8<<28;} //(uint32_t)加不加都行
#define MPU_SDA_OUT()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(uint32_t)3<<28;}

//#define MPU_SDA_IN()   {GPIOB->CRL&=0XFFFF0FFF;GPIOB->CRL|=8<<12;}
//#define MPU_SDA_OUT()  {GPIOB->CRL&=0XFFFF0FFF;GPIOB->CRL|=3<<12;}


//#define SDA_IN()  {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=8<<4;}
//#define SDA_OUT() {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=3<<4;}

//IO操作函数	 
#define MPU_IIC_SCL     PBout(6) 
#define MPU_IIC_SDA     PBout(7) 
#define MPU_READ_SDA   	PBin(7) 

//#define MPU_IIC_SCL     PBout(4) 
//#define MPU_IIC_SDA     PBout(3) 
//#define MPU_READ_SDA   	PBin(3) 

//#define IIC_SCL    PBout(8) //SCL
//#define IIC_SDA    PBout(9) //SDA	 
//#define READ_SDA   PBin(9)  //输入SDA 



//IIC所有操作函数
void MPU_IIC_Delay(void);				//MPU IIC延时函数
void MPU_IIC_Init(void);                //初始化IIC的IO口				 
void MPU_IIC_Start(void);				//发送IIC开始信号
void MPU_IIC_Stop(void);	  			//发送IIC停止信号
void MPU_IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 MPU_IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 MPU_IIC_Wait_Ack(void); 				//IIC等待ACK信号
void MPU_IIC_Ack(void);					//IIC发送ACK信号
void MPU_IIC_NAck(void);				//IIC不发送ACK信号

void IMPU_IC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 MPU_IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
















