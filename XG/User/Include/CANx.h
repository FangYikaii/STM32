//========================================
//<--Ԥ���崦����ֹ�ظ�����-->
#ifndef _CAN_H
#define _CAN_H

//========================================
//ͷ�ļ�





//========================================
//�궨��
#define 			CAN1_OwnStdId				0x0701				//����CAN1��ַ   ���趨��׼��ʶ��11λ��ֵ0-0x7ff,��չģʽ��Ϊ29λ��
#define 			CAN2_OwnStdId				0x0702				//����CAN2��ַ

#define 			CAN1_LinkStdId			0x0702				//CAN1��Ӧ���ӻ���ַ
#define 			CAN2_LinkStdId			0x0701				//CAN2��Ӧ���ӻ���ַ



//========================================
//�˿ڶ���

/*
							CAN1 �˿����
   CAN1TX -- PA12 , CAN1RX -- PA11 (Default);   CAN1TX -- PD1 , CAN1RX -- PD0 (Remap);					--�˰�ѡ�� CAN1TX -- PD1 , CAN1RX -- PD0 
*/

#define 			CAN1TX_GPIOX												GPIOD
#define 			CAN1RX_GPIOX												GPIOD

#define 			CAN1TX_RCC_APB2Periph_GPIOX					RCC_APB2Periph_GPIOD
#define 			CAN1RX_RCC_APB2Periph_GPIOX					RCC_APB2Periph_GPIOD

#define 			CAN1TX_GPIO_PIN											GPIO_Pin_1
#define 			CAN1RX_GPIO_PIN											GPIO_Pin_0

/*
							CAN2 �˿����
   CAN2TX -- PB13 , CAN2RX -- PB12 (Default);   CAN2TX -- PB6 , CAN2RX -- PB5 (Remap);					--�˰�ѡ�� CAN2TX -- PB6 , CAN2RX -- PB5
*/

#define 			CAN2TX_GPIOX												GPIOB
#define 			CAN2RX_GPIOX												GPIOB

#define 			CAN2TX_RCC_APB2Periph_GPIOX					RCC_APB2Periph_GPIOB
#define 			CAN2RX_RCC_APB2Periph_GPIOX					RCC_APB2Periph_GPIOB

#define 			CAN2TX_GPIO_PIN											GPIO_Pin_6
#define 			CAN2RX_GPIO_PIN											GPIO_Pin_5


//========================================
//�����������
extern CAN_InitTypeDef        CAN_InitStructure;
extern CAN_FilterInitTypeDef  CAN_FilterInitStructure;
extern CanTxMsg CAN1TxMessage;
extern CanRxMsg CAN1RxMessage;
extern CanTxMsg CAN2TxMessage;
extern CanRxMsg CAN2RxMessage;

//========================================
//�����������
extern void CAN_Configuration(void);				//���CAN������




//========================================
//<--Ԥ�������-->
#endif



