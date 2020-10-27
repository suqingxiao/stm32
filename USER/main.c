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
//#include "inv_mpu_dmp_motion_driver.h" //����ǰ���mpu6050�޴���ʱ��Ҫdmp
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
extern INTEGER32 up_roll,up_pitch,up_yaw;//��Ӧx y z
extern INTEGER32 down_roll,down_pitch,down_yaw;//��Ӧx2 y2 z2
void Canopen_Init(void);
void CopeSerial2Data(unsigned char ucData);

int main(void)
{
  float angle_x=0,angle_y=0,angle_z=0;
	float angle_x2=0,angle_y2=0,angle_z2=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);        //��ʼ����ʱ����
	uart_init(115200);		  //��ʼ������1������Ϊ115200
	usart_mpu_init(115200); //��ʼ������2������Ϊ115200
//	usart3_init(115200);   //��������ʹ�õ�
	LED_Init();					  //��ʼ��LED 
	KEY_Init(); 				  //������ʼ�� 
	Canopen_Init();       //CAN��ʼ��
 	while(1)
	{
		delay_ms(100);
		delay_ms(10);//�ȴ��������
		angle_x = (float)stcAngle.Angle[0]/32768*180;//IMU1
		angle_y = (float)stcAngle.Angle[1]/32768*180;
		angle_z = (float)stcAngle.Angle[2]/32768*180;
		angle_x2 = (float)stcAngle2.Angle[0]/32768*180;//IMU2
		angle_y2 = (float)stcAngle2.Angle[1]/32768*180;
		angle_z2 = (float)stcAngle2.Angle[2]/32768*180;
		up_roll = (int)(angle_x*(float)1000);//X���ת�ǣ�x �ᣩ����100��6064
		up_pitch = (int)(angle_y*(float)1000);//Y�ḩ���ǣ�y �ᣩ6069
		up_yaw = (int)(angle_z*(float)1000);// Z��ƫ���ǣ�z �ᣩ606c
		down_roll = (int)(angle_x2*(float)1000);//X2���ת�ǣ�x �ᣩ����100��6062
		down_pitch = (int)(angle_y2*(float)1000);//Y2�ḩ���ǣ�y �ᣩ606b
		down_yaw = (int)(angle_z2*(float)1000);// Z2��ƫ���ǣ�z �ᣩ607A

	} 	
}


void Canopen_Init()
{
	Canopen_Timebase_Config();//canopenʱ������
	Canopen_Can_Config();	    //can�������� ������500kbps	CAN1 PB8--RX PB9--TX			
	setNodeId(&serverobject_Data, 0x01);         //����nodeID
  setState(&serverobject_Data, Initialisation);//CANopen����pre-op״̬ 	
}
//����1�õ�
void CopeSerial2Data(unsigned char ucData)
{
	static unsigned char ucRxBuffer[250];
	static unsigned char ucRxCnt = 0;	
	
	ucRxBuffer[ucRxCnt++]=ucData;
	if (ucRxBuffer[0]!=0x55) //����ͷ���ԣ������¿�ʼѰ��0x55����ͷ
	{
		ucRxCnt=0;
		return;
	}
	if (ucRxCnt<11) {return;}//���ݲ���11�����򷵻�
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
//����2�õ�
void CopeSerial2Data2(unsigned char ucData)
{
	static unsigned char ucRxBuffer[250];
	static unsigned char ucRxCnt = 0;	
	
	ucRxBuffer[ucRxCnt++]=ucData;
	if (ucRxBuffer[0]!=0x55) //����ͷ���ԣ������¿�ʼѰ��0x55����ͷ
	{
		ucRxCnt=0;
		return;
	}
	if (ucRxCnt<11) {return;}//���ݲ���11�����򷵻�
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

