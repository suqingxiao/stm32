/**
	***********************************
	* �ļ���:	rcc.c
	* ����:		stone
	* �汾:		V0.1
	* ����:		2018-3-29
	* ����:		����ʱ��Դ
	***********************************
	*/
#include "stm32f4xx_it.h"
#include "stm32f4xx_flash.h"
#include "rcc.h"
 
/* ����:	RCCʱ������
	 ����:	��
   ����ֵ:��
 */
void rcc_config(void)
{ 
	ErrorStatus HSEStartUpStatus;
 
	/* RCC�Ĵ�������ΪĬ������ */
	RCC_DeInit();
	
	/* ���ⲿ����ʱ�� */
	RCC_HSEConfig(RCC_HSE_ON);
	
	/* �ȴ��ⲿ����ʱ���ȶ� */
	HSEStartUpStatus = RCC_WaitForHSEStartUp();
	
	if(HSEStartUpStatus == SUCCESS) 
	{ 
		/* ����HCLK = SYSCLK ����AHBʱ��(HCLK) RCC_SYSCLK_Div1: AHB clock = SYSCLK72*/
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		/* ����PCLK2 = HCLK ���ø���APB2ʱ��72(PCLK2) UART1��SPI1��Timer1��ADC1I/O��AFIO���ڵȡ�*/
		/*�����������õ��� SYSCLK=168MHZ,HCLK=SYSCLK/1=168MHZ, PCLK1=HCLK/4=42MHZ, PCLK2=HCLK/2=82MHZ */
		RCC_PCLK2Config(RCC_HCLK_Div1);
		/* ����PCLK1 = HCLK / 2 ���õ���APB1ʱ��(PCLK1)36 ʱ���������ʱ��2-7ʹ��CAN��USB��I2C1��I2C2��USART2��USART3��UART4��UART5��SPI2*/
		RCC_PCLK1Config(RCC_HCLK_Div2);
		
		/* ����FLASH������ʱ */
		FLASH_SetLatency(FLASH_Latency_2);
		/* ʹ��Ԥȡַ���� */
		FLASH_PrefetchBufferCmd(ENABLE);;
		
		/* ����PLLʱ��ԴΪHSE��Ƶ9 72MHz */
		RCC_PLLConfig(RCC_PLLSource_HSE, 8, 288, 4, 8);//ԭ����144 2 4 ���޸ĵ���288 4 8
		/* ʹ��PLL */
		RCC_PLLCmd(ENABLE);
		/* �ȴ�PLL�ȶ� */
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		
		/* ����PLLΪϵͳʱ��Դ */
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		/* �ȴ�ϵͳʱ��Դ�л���PLL */
		while(RCC_GetSYSCLKSource() != 0x08);
 
		/* ����ϵͳ������ʱ��ԴΪFCLK */
		SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	}
}

