#include "sys.h"
#include "delay.h"
#include "stm32f4xx.h"
#include "tad2141.h"
#include "spi.h"
#include "stdio.h"
//¶ÁÈ¡tad2141Êı¾İ(±àÂëÆ÷)

void Getangle(void)
{
	u16 rawdata = 0;
	u32 angle = 0;
	
	u16 status_h = 0;
	u16 status_l = 0;
	
	CS = 0;
	
	SPI1_ReadWriteByte(0x05);
	
	rawdata = SPI1_ReadWriteByte(0xff);
	rawdata = (rawdata<<8) + SPI1_ReadWriteByte(0xff);
	
	status_h = SPI1_ReadWriteByte(0xff);
	status_l = SPI1_ReadWriteByte(0xff);
	
	CS = 1;
	
	angle = 0xFFFF & ((rawdata * 360) >> 16);
	//return (u16) angle;
	
	printf("data = %d\n",rawdata);
	printf("angle = %d\n",angle);
	printf("statue = %d\n",status_h);
	printf("CRC = %d\n ",status_l);
}

