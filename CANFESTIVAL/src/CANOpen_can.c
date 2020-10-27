/**
	***********************************
	* 文件名:	CANOpen_can.c
	* 作者:		stone
	* 版本:		V0.1
	* 日期:		2018-3-29
	* 描述:		CANOPEN协议底层总线接口
	***********************************
	*/
#include "stm32f4xx_it.h"
#include "stm32f4xx.h"
#include "CANOpen_can.h"
#include "canfestival.h"
#include "bsp_can.h"
#include "usart.h"
/* CANOPEN字典 */
extern CO_Data serverobject_Data;
/*
 * 函数名：gpio_config
 * 描述  ：CAN的GPIO 配置
 * 输入  ：无
 * 输出  : 无
 * 调用  ：内部调用
 */
static void gpio_config(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;   	

		/* 使能GPIO时钟*/
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能PORTB时钟 	

		//初始化GPIO--CAN1
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_8;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHz
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
		GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化PB8,PB9
		//引脚复用映射配置
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_CAN2); //GPIOB8复用为CAN1
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_CAN2); //GPIOB9复用为CAN1
}


/*
 * 函数名：nvic_config
 * 描述  ：CAN的NVIC 配置,第1优先级组，1，2优先级
 * 输入  ：无
 * 输出  : 无
 * 调用  ：内部调用
 */
static void nvic_config(void)
{
   	NVIC_InitTypeDef NVIC_InitStructure;
		/* Configure one bit for preemption priority */
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	 	/*中断设置*/
		NVIC_InitStructure.NVIC_IRQChannel = CAN_RX_IRQ;	   //CAN RX中断
//	  NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX_IRQ;	   //CAN RX中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;			   
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
 
/* 功能:	CAN总线过滤器配置
	 参数:	无
	 返回值:无
 */
static void can_filter_config(void)
{
	CAN_FilterInitTypeDef CAN_FilterInitStructure;
 
	/* 配置过滤器0组，配置成标准标识符且低7位都为0时接受 */
	CAN_FilterInitStructure.CAN_FilterNumber = 0;													/* 设置过滤器组0 *///CAN1
//	CAN_FilterInitStructure.CAN_FilterNumber = 14;													/* 设置过滤器组14 *///14是can2用的
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;				/* 屏蔽模式 */
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;			/* 32位模式 */
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;								/* 在CANOpen中标准标识符的低7位表示节点ID */
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0004;									/* 在CANOpen中只用标准标识符，数据帧/远程帧都有 */
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;										/* 主节点ID为0 */
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;											/* 标准帧 */
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;	/* 过滤器关联到FIFO0 */
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;								/* 使能过滤器 */
	CAN_FilterInit(&CAN_FilterInitStructure);
}
 
/* 功能:	can总线配置
	 参数:	无
	 返回值:无
 */
void Canopen_Can_Config(void)
{
	CAN_InitTypeDef CAN_InitStructure;
 
	/* 配置IO */
	gpio_config();
 
	/* 中断嵌套控制器配置 */
	nvic_config();
 
	/* 配置CAN总线时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
 
	/* CAN1默认参数 */
	CAN_DeInit(CAN1);
//  CAN_DeInit(CAN2);
	/* 将结构体填入默认参数 */
	CAN_StructInit(&CAN_InitStructure);

	//CAN单元设置
	CAN_InitStructure.CAN_TTCM=DISABLE;	//非时间触发通信模式   
	CAN_InitStructure.CAN_ABOM=ENABLE;	//DISABLE软件自动离线管理	 ENABLE 关闭自动离线管理
	CAN_InitStructure.CAN_AWUM=ENABLE;// DISABLE睡眠模式通过软件唤醒(清除CAN->MCR的SLEEP位) ENABLE 关闭自动唤醒
	CAN_InitStructure.CAN_NART=DISABLE;	//ENABLE 禁止报文自动传送 DISABLE 自动重传
	CAN_InitStructure.CAN_RFLM=DISABLE;	//报文不锁定,新的覆盖旧的 禁止FIFO溢出时覆盖原报文 
	CAN_InitStructure.CAN_TXFP=DISABLE;	//优先级由报文标识符决定 
	CAN_InitStructure.CAN_Mode= CAN_Mode_Normal;	 //模式设置 
	
//	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;	//重新同步跳跃宽度(Tsjw)为tsjw+1个时间单位 CAN_SJW_1tq~CAN_SJW_4tq
//	CAN_InitStructure.CAN_BS1=CAN_BS1_4tq; //Tbs1范围CAN_BS1_1tq ~CAN_BS1_16tq
//	CAN_InitStructure.CAN_BS2=CAN_BS2_3tq;//Tbs2范围CAN_BS2_1tq ~	CAN_BS2_8tq
//	CAN_InitStructure.CAN_Prescaler=9;  //分频系数(Fdiv)为brp+1	设置波特率:36MHz/9/(4+3+1)=500kbps 42MHz/7/(7+4+1)=500kbps
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;	//重新同步跳跃宽度(Tsjw)为tsjw+1个时间单位 CAN_SJW_1tq~CAN_SJW_4tq
	CAN_InitStructure.CAN_BS1=CAN_BS1_7tq; //Tbs1范围CAN_BS1_1tq ~CAN_BS1_16tq
	CAN_InitStructure.CAN_BS2=CAN_BS2_4tq;//Tbs2范围CAN_BS2_1tq ~	CAN_BS2_8tq
	CAN_InitStructure.CAN_Prescaler=7;  //分频系数(Fdiv)为brp+1	设置波特率:36MHz/9/(4+3+1)=500kbps 42MHz/7/(7+4+1)=500kbps
	CAN_Init(CAN1, &CAN_InitStructure);   // 初始化CAN1  
//	CAN_Init(CAN2, &CAN_InitStructure);   // 初始化CAN2
  
	/* CAN总线过滤器配置 */
	can_filter_config();
	
	/* 接收挂起中断 */
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
//	CAN_ITConfig(CAN2, CAN_IT_FMP0, ENABLE);
}
 
/* can总线接收中断回调函数 *///CAN1
//void USB_LP_CAN1_RX0_IRQHandler(void)
void CAN1_RX0_IRQHandler(void)
{
	CanRxMsg message;
	Message Rx_Message;
	
	/* 接收消息 */
	CAN_Receive(CAN1, CAN_FIFO0, &message);
	
	/* 组装canopen数据包 */
	Rx_Message.cob_id = message.StdId;											/* 功能码和节点ID */
	Rx_Message.rtr = (message.RTR == CAN_RTR_DATA) ? 0 : 1;	/* 标识符类型 */
	Rx_Message.len = message.DLC;														/* 数据包长度 */
	memcpy(Rx_Message.data, message.Data, message.DLC);			/* 数据 */
	/* canopen数据包分配处理函数 */
	canDispatch(&serverobject_Data, &Rx_Message);
	
//	printf("1"); 	//提示收到
}


/* can总线接收中断回调函数 *///CAN2
//void CAN2_RX0_IRQHandler(void)
//{
//	CanRxMsg message;
//	Message Rx_Message;
//	
//	/* 接收消息 */
//	CAN_Receive(CAN2, CAN_FIFO0, &message);
//	
//	/* 组装canopen数据包 */
//	Rx_Message.cob_id = message.StdId;											/* 功能码和节点ID */
//	Rx_Message.rtr = (message.RTR == CAN_RTR_DATA) ? 0 : 1;	/* 标识符类型 */
//	Rx_Message.len = message.DLC;														/* 数据包长度 */
//	memcpy(Rx_Message.data, message.Data, message.DLC);			/* 数据 */

//	/* canopen数据包分配处理函数 */
//	canDispatch(&serverobject_Data, &Rx_Message);
//	
////	printf("1"); 	//提示收到
//}
/* 功能:	CAN发送数据函数
	 参数:	notused can总线端口
					message canopen数据包
	返回值:	0 成功
					1 失败
 */
//CAN_PORT notused,
//CAN2
//uint8_t canSend(CAN_PORT notused, Message *message)
//{
//	uint32_t i = 0xFFFFFF;
//	CanTxMsg TxMessage;
//	uint8_t TransmitMailbox = 0;
// 
//	/* 组装CAN数据包 */
//	TxMessage.DLC = message->len;																	/* 数据长度 */
//	memcpy(TxMessage.Data, message->data, message->len);					/* 数据 */
//	TxMessage.IDE = CAN_ID_STD;																		/* 标准ID#CAN_Id_Standard((uint32_t)0x00000000)*/
//	TxMessage.StdId = message->cob_id;														/* 标识符 */
//	TxMessage.RTR = (message->rtr == CAN_RTR_DATA) ? 0 : 2;				/* 数据帧 */
//	TransmitMailbox = CAN_Transmit(CAN2, &TxMessage);
//	/* 等待发送成功 */
//	while((CAN_TransmitStatus(CAN2, TransmitMailbox) != CANTXOK) && --i);
//	/* 成功0 超时1 */
//	return (i != 0) ? 0 : 1; 
//}

//CAN1
uint8_t canSend(CAN_PORT notused, Message *message)
{
	uint32_t i = 0xFFFFFF;
	CanTxMsg TxMessage;
	uint8_t TransmitMailbox = 0;
 
	/* 组装CAN数据包 */
	TxMessage.DLC = message->len;																	/* 数据长度 */
	memcpy(TxMessage.Data, message->data, message->len);					/* 数据 */
	TxMessage.IDE = CAN_ID_STD;																		/* 标准ID#CAN_Id_Standard((uint32_t)0x00000000)*/
	TxMessage.StdId = message->cob_id;														/* 标识符 */
	TxMessage.RTR = (message->rtr == CAN_RTR_DATA) ? 0 : 2;				/* 数据帧 */
	/* 发送数据包 */
	TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	/* 等待发送成功 */
	while((CAN_TransmitStatus(CAN1, TransmitMailbox) != CANTXOK) && --i);
	/* 成功0 超时1 */
	return (i != 0) ? 0 : 1; 
}



//uint8_t canChangeBaudRate(CAN_PORT notused, char* baud)
//{
//	
//}
//can发送一组数据(固定格式:ID为0X12,标准帧,数据帧)	
//len:数据长度(最大为8)				     
//msg:数据指针,最大为8个字节.
//返回值:0,成功;
////		 其他,失败;
//u8 CAN2_Send_Msg(u8* msg,u8 len)
//{	
//  u8 mbox;
//  u16 i=0;
//  CanTxMsg TxMessage;
//  TxMessage.StdId=0x12;	 // 标准标识符为0
//  TxMessage.ExtId=0x12;	 // 设置扩展标示符（29位）
//  TxMessage.IDE=0;		  // 使用扩展标识符
//  TxMessage.RTR=0;		  // 消息类型为数据帧，一帧8位
//  TxMessage.DLC=len;							 // 发送两帧信息
//  for(i=0;i<len;i++)
//  TxMessage.Data[i]=msg[i];				 // 第一帧信息          
//  mbox= CAN_Transmit(CAN2, &TxMessage);   
//  i=0;
//  while((CAN_TransmitStatus(CAN2, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//等待发送结束
//	printf("\r\nsend_usart:\r\n");
//  if(i>=0XFFF)return 1;
//  return 0;		

//}

