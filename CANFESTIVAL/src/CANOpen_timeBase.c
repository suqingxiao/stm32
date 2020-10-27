/**
	***********************************
	* �ļ���:	CANOpen_timeBase.c
	* ����:		stone
	* �汾:		V0.1
	* ����:		2018-3-29
	* ����:		CANOPEN�ײ㶨ʱ���ӿ��ļ�
	***********************************
	*/
#include "stm32f4xx_it.h"
#include "canfestival.h"
#include "CANOpen_timeBase.h"
 
/* ����:	��ʱ������
	 ����:	��
	 ����ֵ:��
 */
static void timer_config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	/* ����TIM2��ʱ�� */
	//RCC_APB1���û���õ���APB (APB1)��Χʱ�� 42Mhz 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	 
	/* ����ʱ��2�Ĵ�����Ϊ��ʼֵ */
	TIM_DeInit(TIM2);
	
	/* ���ö�ʱ��2���ڲ�ʱ�� */
	TIM_InternalClockConfig(TIM2);
	
	/* Ԥ��Ƶֵ */
//	TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;//72MHZ
		TIM_TimeBaseStructure.TIM_Prescaler = 84 - 1;//84MHZ
	/* ʱ�ӷָ� */
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	/* ���ϼ��� */
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	/* �Զ�����ֵ */
	TIM_TimeBaseStructure.TIM_Period = 50000 - 1;
	/* ��ʼ����ʱ��2 */
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	/* �������жϱ�־ */ 
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	
	/* ��ֹARRԤװ�ػ����� */
	TIM_ARRPreloadConfig(TIM2, DISABLE);
	
	/* ����TIM2���ж� */
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	/* ������ʱ��2 */
	TIM_Cmd(TIM2, ENABLE);
}
 
/* ����:	TIM�ж�����
	 ����:	��
	 ����ֵ:��
 */
static void TIM_nvic_config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* ѡ��TIM2���ж�ͨ�� */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	/* ��ռʽ�ж����ȼ�����Ϊ2 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	/* ��Ӧʽ�ж����ȼ�����Ϊ2 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	/* ʹ���ж� */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	/* �жϳ�ʼ�� */
	NVIC_Init(&NVIC_InitStructure);	
}
 
/* ����:	canopenʱ������
	 ����:	��
	 ����ֵ:��
 */
void Canopen_Timebase_Config(void)
{
	/* ��ʱ������ */
	timer_config();
	
	/* �ж����� */
	TIM_nvic_config();
}
 
/* ���ܣ�	���ö�ʱ������ʱ��
	 ����: 	��ʱ������ʱ��
	 ����ֵ:�� 
 */
void setTimer(TIMEVAL value)
{
	TIM2->ARR = TIM2->CNT + value;
}
 
/* ���ܣ�	��ȡ�ϴδ��������ڵ�����ʱ��
	 ����: 	��
	 ����ֵ:��ȡ������ֵ
 */
TIMEVAL getElapsedTime(void)
{
	return TIM2->CNT;
}
 
/* ��ʱ��2�ж����� */
void TIM2_IRQHandler(void)
{
	/* ��ʱ��2�����־λ */
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		/* ��ʱ��2��������־λ */
		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);
 
		TimeDispatch();
	}
}

