/**
	***********************************
	* �ļ���:	nvic.c
	* ����:		stone
	* �汾:		V0.1
	* ����:		2018-3-29
	* ����:		�����жϿ�����
	***********************************
	*/
#include "stm32f4xx_it.h"
#include "nvic.h"
 
/* ����:	�ж�Ƕ�׿���������
   ����:	��
   ����ֵ:��
 */
void nvic_config_init(void)
{
	/* ѡ���жϷ���2 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}
