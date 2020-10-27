/**
	***********************************
	* �ļ���:	CANOpen_can.c
	* ����:		stone
	* �汾:		V0.1
	* ����:		2018-3-29
	* ����:		CANOPENЭ��ײ����߽ӿ�
	***********************************
	*/
#include "stm32f4xx_it.h"
#include "stm32f4xx.h"
#include "CANOpen_can.h"
#include "canfestival.h"
#include "bsp_can.h"
#include "usart.h"
/* CANOPEN�ֵ� */
extern CO_Data serverobject_Data;
/*
 * ��������gpio_config
 * ����  ��CAN��GPIO ����
 * ����  ����
 * ���  : ��
 * ����  ���ڲ�����
 */
static void gpio_config(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;   	

		/* ʹ��GPIOʱ��*/
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��PORTBʱ�� 	

		//��ʼ��GPIO--CAN1
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_8;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHz
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
		GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��PB8,PB9
		//���Ÿ���ӳ������
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_CAN2); //GPIOB8����ΪCAN1
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_CAN2); //GPIOB9����ΪCAN1
}


/*
 * ��������nvic_config
 * ����  ��CAN��NVIC ����,��1���ȼ��飬1��2���ȼ�
 * ����  ����
 * ���  : ��
 * ����  ���ڲ�����
 */
static void nvic_config(void)
{
   	NVIC_InitTypeDef NVIC_InitStructure;
		/* Configure one bit for preemption priority */
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	 	/*�ж�����*/
		NVIC_InitStructure.NVIC_IRQChannel = CAN_RX_IRQ;	   //CAN RX�ж�
//	  NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX_IRQ;	   //CAN RX�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;			   
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
 
/* ����:	CAN���߹���������
	 ����:	��
	 ����ֵ:��
 */
static void can_filter_config(void)
{
	CAN_FilterInitTypeDef CAN_FilterInitStructure;
 
	/* ���ù�����0�飬���óɱ�׼��ʶ���ҵ�7λ��Ϊ0ʱ���� */
	CAN_FilterInitStructure.CAN_FilterNumber = 0;													/* ���ù�������0 *///CAN1
//	CAN_FilterInitStructure.CAN_FilterNumber = 14;													/* ���ù�������14 *///14��can2�õ�
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;				/* ����ģʽ */
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;			/* 32λģʽ */
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;								/* ��CANOpen�б�׼��ʶ���ĵ�7λ��ʾ�ڵ�ID */
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0004;									/* ��CANOpen��ֻ�ñ�׼��ʶ��������֡/Զ��֡���� */
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;										/* ���ڵ�IDΪ0 */
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;											/* ��׼֡ */
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;	/* ������������FIFO0 */
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;								/* ʹ�ܹ����� */
	CAN_FilterInit(&CAN_FilterInitStructure);
}
 
/* ����:	can��������
	 ����:	��
	 ����ֵ:��
 */
void Canopen_Can_Config(void)
{
	CAN_InitTypeDef CAN_InitStructure;
 
	/* ����IO */
	gpio_config();
 
	/* �ж�Ƕ�׿��������� */
	nvic_config();
 
	/* ����CAN����ʱ�� */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
 
	/* CAN1Ĭ�ϲ��� */
	CAN_DeInit(CAN1);
//  CAN_DeInit(CAN2);
	/* ���ṹ������Ĭ�ϲ��� */
	CAN_StructInit(&CAN_InitStructure);

	//CAN��Ԫ����
	CAN_InitStructure.CAN_TTCM=DISABLE;	//��ʱ�䴥��ͨ��ģʽ   
	CAN_InitStructure.CAN_ABOM=ENABLE;	//DISABLE����Զ����߹���	 ENABLE �ر��Զ����߹���
	CAN_InitStructure.CAN_AWUM=ENABLE;// DISABLE˯��ģʽͨ���������(���CAN->MCR��SLEEPλ) ENABLE �ر��Զ�����
	CAN_InitStructure.CAN_NART=DISABLE;	//ENABLE ��ֹ�����Զ����� DISABLE �Զ��ش�
	CAN_InitStructure.CAN_RFLM=DISABLE;	//���Ĳ�����,�µĸ��Ǿɵ� ��ֹFIFO���ʱ����ԭ���� 
	CAN_InitStructure.CAN_TXFP=DISABLE;	//���ȼ��ɱ��ı�ʶ������ 
	CAN_InitStructure.CAN_Mode= CAN_Mode_Normal;	 //ģʽ���� 
	
//	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;	//����ͬ����Ծ���(Tsjw)Ϊtsjw+1��ʱ�䵥λ CAN_SJW_1tq~CAN_SJW_4tq
//	CAN_InitStructure.CAN_BS1=CAN_BS1_4tq; //Tbs1��ΧCAN_BS1_1tq ~CAN_BS1_16tq
//	CAN_InitStructure.CAN_BS2=CAN_BS2_3tq;//Tbs2��ΧCAN_BS2_1tq ~	CAN_BS2_8tq
//	CAN_InitStructure.CAN_Prescaler=9;  //��Ƶϵ��(Fdiv)Ϊbrp+1	���ò�����:36MHz/9/(4+3+1)=500kbps 42MHz/7/(7+4+1)=500kbps
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;	//����ͬ����Ծ���(Tsjw)Ϊtsjw+1��ʱ�䵥λ CAN_SJW_1tq~CAN_SJW_4tq
	CAN_InitStructure.CAN_BS1=CAN_BS1_7tq; //Tbs1��ΧCAN_BS1_1tq ~CAN_BS1_16tq
	CAN_InitStructure.CAN_BS2=CAN_BS2_4tq;//Tbs2��ΧCAN_BS2_1tq ~	CAN_BS2_8tq
	CAN_InitStructure.CAN_Prescaler=7;  //��Ƶϵ��(Fdiv)Ϊbrp+1	���ò�����:36MHz/9/(4+3+1)=500kbps 42MHz/7/(7+4+1)=500kbps
	CAN_Init(CAN1, &CAN_InitStructure);   // ��ʼ��CAN1  
//	CAN_Init(CAN2, &CAN_InitStructure);   // ��ʼ��CAN2
  
	/* CAN���߹��������� */
	can_filter_config();
	
	/* ���չ����ж� */
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
//	CAN_ITConfig(CAN2, CAN_IT_FMP0, ENABLE);
}
 
/* can���߽����жϻص����� *///CAN1
//void USB_LP_CAN1_RX0_IRQHandler(void)
void CAN1_RX0_IRQHandler(void)
{
	CanRxMsg message;
	Message Rx_Message;
	
	/* ������Ϣ */
	CAN_Receive(CAN1, CAN_FIFO0, &message);
	
	/* ��װcanopen���ݰ� */
	Rx_Message.cob_id = message.StdId;											/* ������ͽڵ�ID */
	Rx_Message.rtr = (message.RTR == CAN_RTR_DATA) ? 0 : 1;	/* ��ʶ������ */
	Rx_Message.len = message.DLC;														/* ���ݰ����� */
	memcpy(Rx_Message.data, message.Data, message.DLC);			/* ���� */
	/* canopen���ݰ����䴦���� */
	canDispatch(&serverobject_Data, &Rx_Message);
	
//	printf("1"); 	//��ʾ�յ�
}


/* can���߽����жϻص����� *///CAN2
//void CAN2_RX0_IRQHandler(void)
//{
//	CanRxMsg message;
//	Message Rx_Message;
//	
//	/* ������Ϣ */
//	CAN_Receive(CAN2, CAN_FIFO0, &message);
//	
//	/* ��װcanopen���ݰ� */
//	Rx_Message.cob_id = message.StdId;											/* ������ͽڵ�ID */
//	Rx_Message.rtr = (message.RTR == CAN_RTR_DATA) ? 0 : 1;	/* ��ʶ������ */
//	Rx_Message.len = message.DLC;														/* ���ݰ����� */
//	memcpy(Rx_Message.data, message.Data, message.DLC);			/* ���� */

//	/* canopen���ݰ����䴦���� */
//	canDispatch(&serverobject_Data, &Rx_Message);
//	
////	printf("1"); 	//��ʾ�յ�
//}
/* ����:	CAN�������ݺ���
	 ����:	notused can���߶˿�
					message canopen���ݰ�
	����ֵ:	0 �ɹ�
					1 ʧ��
 */
//CAN_PORT notused,
//CAN2
//uint8_t canSend(CAN_PORT notused, Message *message)
//{
//	uint32_t i = 0xFFFFFF;
//	CanTxMsg TxMessage;
//	uint8_t TransmitMailbox = 0;
// 
//	/* ��װCAN���ݰ� */
//	TxMessage.DLC = message->len;																	/* ���ݳ��� */
//	memcpy(TxMessage.Data, message->data, message->len);					/* ���� */
//	TxMessage.IDE = CAN_ID_STD;																		/* ��׼ID#CAN_Id_Standard((uint32_t)0x00000000)*/
//	TxMessage.StdId = message->cob_id;														/* ��ʶ�� */
//	TxMessage.RTR = (message->rtr == CAN_RTR_DATA) ? 0 : 2;				/* ����֡ */
//	TransmitMailbox = CAN_Transmit(CAN2, &TxMessage);
//	/* �ȴ����ͳɹ� */
//	while((CAN_TransmitStatus(CAN2, TransmitMailbox) != CANTXOK) && --i);
//	/* �ɹ�0 ��ʱ1 */
//	return (i != 0) ? 0 : 1; 
//}

//CAN1
uint8_t canSend(CAN_PORT notused, Message *message)
{
	uint32_t i = 0xFFFFFF;
	CanTxMsg TxMessage;
	uint8_t TransmitMailbox = 0;
 
	/* ��װCAN���ݰ� */
	TxMessage.DLC = message->len;																	/* ���ݳ��� */
	memcpy(TxMessage.Data, message->data, message->len);					/* ���� */
	TxMessage.IDE = CAN_ID_STD;																		/* ��׼ID#CAN_Id_Standard((uint32_t)0x00000000)*/
	TxMessage.StdId = message->cob_id;														/* ��ʶ�� */
	TxMessage.RTR = (message->rtr == CAN_RTR_DATA) ? 0 : 2;				/* ����֡ */
	/* �������ݰ� */
	TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	/* �ȴ����ͳɹ� */
	while((CAN_TransmitStatus(CAN1, TransmitMailbox) != CANTXOK) && --i);
	/* �ɹ�0 ��ʱ1 */
	return (i != 0) ? 0 : 1; 
}



//uint8_t canChangeBaudRate(CAN_PORT notused, char* baud)
//{
//	
//}
//can����һ������(�̶���ʽ:IDΪ0X12,��׼֡,����֡)	
//len:���ݳ���(���Ϊ8)				     
//msg:����ָ��,���Ϊ8���ֽ�.
//����ֵ:0,�ɹ�;
////		 ����,ʧ��;
//u8 CAN2_Send_Msg(u8* msg,u8 len)
//{	
//  u8 mbox;
//  u16 i=0;
//  CanTxMsg TxMessage;
//  TxMessage.StdId=0x12;	 // ��׼��ʶ��Ϊ0
//  TxMessage.ExtId=0x12;	 // ������չ��ʾ����29λ��
//  TxMessage.IDE=0;		  // ʹ����չ��ʶ��
//  TxMessage.RTR=0;		  // ��Ϣ����Ϊ����֡��һ֡8λ
//  TxMessage.DLC=len;							 // ������֡��Ϣ
//  for(i=0;i<len;i++)
//  TxMessage.Data[i]=msg[i];				 // ��һ֡��Ϣ          
//  mbox= CAN_Transmit(CAN2, &TxMessage);   
//  i=0;
//  while((CAN_TransmitStatus(CAN2, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//�ȴ����ͽ���
//	printf("\r\nsend_usart:\r\n");
//  if(i>=0XFFF)return 1;
//  return 0;		

//}

