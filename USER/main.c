#include "sys.h"
#include "delay.h"
#include "usart.h"
//#include "usart3.h"
#include "usart_mpu.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
//#include "mpu6050iic.h"
//#include "timer3.h"
//#include "inv_mpu.h"
//#include "inv_mpu_dmp_motion_driver.h" //如果是板载mpu6050无串口时需要dmp
//#include "rcc.h"
//#include "nvic.h"
#include "CANOpen_timeBase.h"
//#include "bsp_can.h"
#include "CANOpen_can.h"
#include "canfestival.h"
#include "usart_mpu.h"

struct SAcc
{
	short a[3];
	short T;
};
struct SGyro
{
	short w[3];
	short T;
};
struct SAngle
{
	short Angle[3];
	short T;
};

struct SAcc 		stcAcc;
struct SGyro 		stcGyro;
struct SAngle 	stcAngle;

struct SAcc 		stcAcc2;
struct SGyro 		stcGyro2;
struct SAngle 	stcAngle2;

extern CO_Data serverobject_Data;
extern INTEGER32 up_roll,up_pitch,up_yaw;//对应x y z
extern INTEGER32 down_roll,down_pitch,down_yaw;//对应x2 y2 z2
void Canopen_Init(void);
void CopeSerial2Data(unsigned char ucData);

int main(void)
{
  float angle_x=0,angle_y=0,angle_z=0;
	float angle_x2=0,angle_y2=0,angle_z2=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);        //初始化延时函数
	uart_init(115200);		  //初始化串口1波特率为115200
	usart_mpu_init(115200); //初始化串口2波特率为115200
//	usart3_init(115200);   //蓝牙测试使用的
	LED_Init();					  //初始化LED 
	KEY_Init(); 				  //按键初始化 
	Canopen_Init();       //CAN初始化
 	while(1)
	{
		delay_ms(100);
		delay_ms(10);//等待传输完成
		angle_x = (float)stcAngle.Angle[0]/32768*180;//IMU1
		angle_y = (float)stcAngle.Angle[1]/32768*180;
		angle_z = (float)stcAngle.Angle[2]/32768*180;
		angle_x2 = (float)stcAngle2.Angle[0]/32768*180;//IMU2
		angle_y2 = (float)stcAngle2.Angle[1]/32768*180;
		angle_z2 = (float)stcAngle2.Angle[2]/32768*180;
		up_roll = (int)(angle_x*(float)1000);//X轴滚转角（x 轴）扩大100倍6064
		up_pitch = (int)(angle_y*(float)1000);//Y轴俯仰角（y 轴）6069
		up_yaw = (int)(angle_z*(float)1000);// Z轴偏航角（z 轴）606c
		down_roll = (int)(angle_x2*(float)1000);//X2轴滚转角（x 轴）扩大100倍6062
		down_pitch = (int)(angle_y2*(float)1000);//Y2轴俯仰角（y 轴）606b
		down_yaw = (int)(angle_z2*(float)1000);// Z2轴偏航角（z 轴）607A

	} 	
}


void Canopen_Init()
{
	Canopen_Timebase_Config();//canopen时基配置
	Canopen_Can_Config();	    //can总线配置 波特率500kbps	CAN1 PB8--RX PB9--TX			
	setNodeId(&serverobject_Data, 0x01);         //设置nodeID
  setState(&serverobject_Data, Initialisation);//CANopen进入pre-op状态 	
}
//串口1用的
void CopeSerial2Data(unsigned char ucData)
{
	static unsigned char ucRxBuffer[250];
	static unsigned char ucRxCnt = 0;	
	
	ucRxBuffer[ucRxCnt++]=ucData;
	if (ucRxBuffer[0]!=0x55) //数据头不对，则重新开始寻找0x55数据头
	{
		ucRxCnt=0;
		return;
	}
	if (ucRxCnt<11) {return;}//数据不满11个，则返回
	else
	{
		switch(ucRxBuffer[1])
		{
			case 0x51:	memcpy(&stcAcc,&ucRxBuffer[2],8);break;
			case 0x52:	memcpy(&stcGyro,&ucRxBuffer[2],8);break;
			case 0x53:	memcpy(&stcAngle,&ucRxBuffer[2],8);break;
			default:  
				break;
		}
		ucRxCnt=0;
	}
}
//串口2用的
void CopeSerial2Data2(unsigned char ucData)
{
	static unsigned char ucRxBuffer[250];
	static unsigned char ucRxCnt = 0;	
	
	ucRxBuffer[ucRxCnt++]=ucData;
	if (ucRxBuffer[0]!=0x55) //数据头不对，则重新开始寻找0x55数据头
	{
		ucRxCnt=0;
		return;
	}
	if (ucRxCnt<11) {return;}//数据不满11个，则返回
	else
	{
		switch(ucRxBuffer[1])
		{
			case 0x51:	memcpy(&stcAcc2,&ucRxBuffer[2],8);break;
			case 0x52:	memcpy(&stcGyro2,&ucRxBuffer[2],8);break;
			case 0x53:	memcpy(&stcAngle2,&ucRxBuffer[2],8);break;
			default:  
				break;
		}
		ucRxCnt=0;
	}
}

