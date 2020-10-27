#include "mpu6050.h"
#include "stm32f4xx.h"
#include "delay.h"
#include "sys.h"
#include "string.h"
#include "stdio.h"
#include "usart_mpu.h"
// mpu6050数据解算

float a[3],w[3],angle[3],T;
//extern unsigned char Re_buf[11],temp_buf[11],counter;
//extern unsigned char sign;
unsigned char Temp[11];

void mpu_read(void)
{
	if(sign)
  {  
		memcpy(Temp,Re_buf,11);
		sign=0;
		if(Re_buf[0]==0x55)       //检查帧头
		 {  
				switch(Re_buf[1])
				{
					 case 0x51: //标识这个包是加速度包
							a[0] = ((short)(Temp[3]<<8 | Temp[2]))/32768.0*16;      //X轴加速度
							a[1] = ((short)(Temp[5]<<8 | Temp[4]))/32768.0*16;      //Y轴加速度
							a[2] = ((short)(Temp[7]<<8 | Temp[6]))/32768.0*16;      //Z轴加速度
							T    = ((short)(Temp[9]<<8 | Temp[8]))/340.0+36.25;      //温度
							break;
					 case 0x52: //标识这个包是角速度包
							w[0] = ((short)(Temp[3]<<8| Temp[2]))/32768.0*2000;      //X轴角速度
							w[1] = ((short)(Temp[5]<<8| Temp[4]))/32768.0*2000;      //Y轴角速度
							w[2] = ((short)(Temp[7]<<8| Temp[6]))/32768.0*2000;      //Z轴角速度
							T    = ((short)(Temp[9]<<8| Temp[8]))/340.0+36.25;      //温度
							break;
					 case 0x53: //标识这个包是角度包
							angle[0] = ((short)(Temp[3]<<8| Temp[2]))/32768.0*180;   //X轴滚转角（x 轴）
							angle[1] = ((short)(Temp[5]<<8| Temp[4]))/32768.0*180;   //Y轴俯仰角（y 轴）
							angle[2] = ((short)(Temp[7]<<8| Temp[6]))/32768.0*180;   //Z轴偏航角（z 轴）
							T        = ((short)(Temp[9]<<8| Temp[8]))/340.0+36.25;   //温度

							//printf("X：%.2f   Y：%.2f   Z：%.2f\r\n",angle[0],angle[1],angle[2]);
							break;
					 default:  break;
				}
	//printf("ax=%.2f ay=%.2f az=%.2f\n wx=%.2f wy=%.2f wz=%.2f\n anglex=%.2f angley=%.2f anglez=%.2f\n",a[0],a[1],a[2],w[0],w[1],w[2],angle[0],angle[1],angle[2]);
//	printf("X：%.2f   Y：%.2f   Z：%.2f\r\n",angle[0],angle[1],angle[2]);
					printf("%.2f       %.2f      %.2f\r\n",angle[0],angle[1],angle[2]);
		 }
         
      }

}
