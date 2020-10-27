#ifndef __SPI_H
#define __SPI_H
#include "sys.h"

#define CS PAout(4)
void spi_init(void);
void SPI1_SetSpeed(u8 SpeedSet);
void CS_init(void);
u8 SPI1_ReadWriteByte(u8 TxData);
#endif
