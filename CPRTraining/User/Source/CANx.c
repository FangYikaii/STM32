/*
����˵��:  	
            CANx ͨ�Ŵ������ --- STM32F107VCT 
						
ע�����						
						1��ע�� CANx ��IO�˿�ѡ��Ĭ�ϻ���ӳ��ܽ�
						
						
						
						
						
�˿�ʹ��:		��Doc�ļ�����˵��
������:     Masterjay   
����ʱ��:   2014-04-21 
�޸�ʱ��:   2014-04-21
*/
//========================================
//ͷ�ļ�
#include "main.h"

//========================================
//��������
CAN_InitTypeDef        CAN_InitStructure;
CAN_FilterInitTypeDef  CAN_FilterInitStructure;
CanTxMsg CAN1TxMessage;
CanRxMsg CAN1RxMessage;
CanTxMsg CAN2TxMessage;
CanRxMsg CAN2RxMessage;

//========================================
//��������
void CAN_Configuration(void);				//���CAN������


//========================================
//��ģ�麯��

/***********************************************************************
�������ƣ�void CAN_Configuration(void)
��    �ܣ����CAN������
���������
���������
��дʱ�䣺2014.4.13
�� д �ˣ�
ע    �⣺key1->PE2,
					key2->PE3,
					key3->PE4,
					key4->PE5,
***********************************************************************/
void CAN_Configuration(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
  /* GPIOB, GPIOD and AFIO clocks enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB2PeriphClockCmd(CAN1TX_RCC_APB2Periph_GPIOX, ENABLE);
  RCC_APB2PeriphClockCmd(CAN1RX_RCC_APB2Periph_GPIOX, ENABLE);
  RCC_APB2PeriphClockCmd(CAN2TX_RCC_APB2Periph_GPIOX, ENABLE);
  RCC_APB2PeriphClockCmd(CAN2RX_RCC_APB2Periph_GPIOX, ENABLE);	
	
  /* CAN1 and CAN2 Periph clocks enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1 | RCC_APB1Periph_CAN2, ENABLE); 
  
  /* Configure CAN1 RX pin */
  GPIO_InitStructure.GPIO_Pin = CAN1RX_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(CAN1RX_GPIOX, &GPIO_InitStructure);
   
  /* Configure CAN2 RX pin */
  GPIO_InitStructure.GPIO_Pin = CAN2RX_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	
  GPIO_Init(CAN2RX_GPIOX, &GPIO_InitStructure);

  /* Configure CAN1 TX pin */
  GPIO_InitStructure.GPIO_Pin = CAN1TX_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(CAN1TX_GPIOX, &GPIO_InitStructure);

  /* Configure CAN2 TX pin */
  GPIO_InitStructure.GPIO_Pin = CAN2TX_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
  GPIO_Init(CAN2TX_GPIOX, &GPIO_InitStructure);


  /* Remap CAN1 and CAN2 GPIOs */
  GPIO_PinRemapConfig(GPIO_Remap2_CAN1 , ENABLE);					//ע��IO�˿�ѡ�񣬴˴�ѡ��ӳ��ܽ�
  GPIO_PinRemapConfig(GPIO_Remap_CAN2, ENABLE);						//ע��IO�˿�ѡ�񣬴˴�ѡ��ӳ��ܽ�


  /* CAN register init */
  CAN_DeInit(CAN1);
  CAN_DeInit(CAN2);
  CAN_StructInit(&CAN_InitStructure);

  /* CAN1 cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE;									//ʱ�䴥��ͨѶģʽ�ر�
  CAN_InitStructure.CAN_ABOM = DISABLE;									//��������������״̬�ָ�
  CAN_InitStructure.CAN_AWUM = DISABLE;									//������������뿪����ģʽ
  CAN_InitStructure.CAN_NART = DISABLE;									//ʹ���ش�
  CAN_InitStructure.CAN_RFLM = DISABLE;									//һ��FIFO������һ������ı��Ľ�����
  CAN_InitStructure.CAN_TXFP = DISABLE;									//���÷���FIFO���ȼ����ɱ�ʶ���������ȼ�
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;					//��CANΪ����ģʽ
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
  CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;							//���ò�����=(72MHZ/2)/16/(1+3+5)=0.25MHZ=250KHz
  CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;
  CAN_InitStructure.CAN_Prescaler = 16;									//������Ԥ��Ƶ��
  CAN_Init(CAN1, &CAN_InitStructure);
  CAN_Init(CAN2, &CAN_InitStructure);

  /* CAN1 filter init */
  CAN_FilterInitStructure.CAN_FilterNumber = 0;												//�Թ�����0��������
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;			//����ģʽ
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;		//32λ
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;									//����ƥ���λ
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;							//�Ա�ʶ�����бȽ�
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;								//��������ճ�����ܵ�0
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);
  
  /* CAN2 filter init */
  CAN_FilterInitStructure.CAN_FilterNumber = 14;
  CAN_FilterInit(&CAN_FilterInitStructure);
  
  /* IT Configuration for CAN1 */  
  CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
  /* IT Configuration for CAN2 */  
  CAN_ITConfig(CAN2, CAN_IT_FMP0, ENABLE);
	
	
		/* Set the Vector Table base address at 0x08000000 */
		NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0000);

		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);			//�������ȼ� 0-15   ��Ӧ���ȼ� 0

		NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
		NVIC_Init(&NVIC_InitStructure);	

}


/***********************************************************************
�������ƣ�void CAN1_RX0_IRQHandler(void)
��    �ܣ�CAN1�����жϴ������
���������
���������
��дʱ�䣺2014.04.14
�� д �ˣ�
ע    ��  
***********************************************************************/
void CAN1_RX0_IRQHandler(void)
{
  CAN_Receive(CAN1, CAN_FIFO0, &CAN1RxMessage);

//*******************************************************************
//EEC1 ���ӷ�����������1	--  50HZ
	if(CAN1RxMessage.ExtId == 0x0CF00400)														
	{
		XG.PumpSpeed=(CAN1RxMessage.Data[4]<<8)+CAN1RxMessage.Data[3];	//���ͷ�����ת�� 0-8031.88 RPM
		XG.PumpSpeed=XG.PumpSpeed*0.125;																//���ͷ�����ת��ӦΪʵ�ʶ�ȡֵ*0.125(CAN����ν��ɨ������)		
	}
//*******************************************************************
//EEC2 	���ӷ�����������2		--  20HZ
	if(CAN1RxMessage.ExtId == 0x0CF00300)														
	{
		XG.Throttle=CAN1RxMessage.Data[1];															//����λ�� 0-100
		XG.Throttle=XG.Throttle*0.4;																		//����λ��ӦΪʵ�ʶ�ȡֵ*0.4(CAN����ν��ɨ������)					
	}	
//*******************************************************************
//EEC3 	���ӷ�����������3  --  5HZ
//	if(CAN1RxMessage.ExtId == 0x18FEDF00)														
//	{
//				
//	}		

//*******************************************************************
//FlConsum	ȼ��������
//	if(CAN1RxMessage.ExtId == 0x18FEE900)														
//	{
//		TotalFuelConsumption=(CAN1RxMessage.Data[7]<<24)+(CAN1RxMessage.Data[6]<<16)+(CAN1RxMessage.Data[5]<<8)+CAN1RxMessage.Data[4];										//��ȼ��������
//				
//	}	

//*******************************************************************
//FLDPRES ȼ��ѹ��  --  2HZ
//	if(CAN1RxMessage.ExtId == 0x18FEE200)														
//	{		
//			
//	}	

//*******************************************************************
//FlEco ȼ�;����� -- 10HZ
//	if(CAN1RxMessage.ExtId == 0x18FEF200)														
//	{
//		FuelRate=(CAN1RxMessage.Data[1]<<8)+CAN1RxMessage.Data[0];										//Сʱȼ�������� L/H
//		InstantaneousFuelEconomy=(CAN1RxMessage.Data[3]<<8)+CAN1RxMessage.Data[2];		//˲̬ȼ�;����� km/L
//		
//	}	

//*******************************************************************
//CAN1�ڶ�ȡֵ����ͨ��CAN2��ת��	
	
		CAN2TxMessage.StdId = 0x0000;									//�趨��׼��ʶ��11λ��ֵ0-0x7ff -- 0x00~���������Ƶ�Ԫ
		CAN2TxMessage.ExtId = CAN1RxMessage.ExtId;		//�趨��չ��׼��ʶ��29λ��ֵ0-0x1fffffff
		CAN2TxMessage.RTR = CAN_RTR_DATA;							//����֡  CAN_RTR_REMOTE // CAN_RTR_DATA
		CAN2TxMessage.IDE = CAN_ID_EXT;								//��׼֡��ʽ[ExtID��Ч]CAN_ID_EXT //CAN_ID_STD
		CAN2TxMessage.DLC = 8;												//֡���ȣ���λ�ֽڣ������ͼ�������	
		CAN2TxMessage.Data[0]=CAN1RxMessage.Data[0];
		CAN2TxMessage.Data[1]=CAN1RxMessage.Data[1];
		CAN2TxMessage.Data[2]=CAN1RxMessage.Data[2];
		CAN2TxMessage.Data[3]=CAN1RxMessage.Data[3];
		CAN2TxMessage.Data[4]=CAN1RxMessage.Data[4];
		CAN2TxMessage.Data[5]=CAN1RxMessage.Data[5];
		CAN2TxMessage.Data[6]=CAN1RxMessage.Data[6];
		CAN2TxMessage.Data[7]=CAN1RxMessage.Data[7];
		CAN_Transmit(CAN2, &CAN2TxMessage);		

//*******************************************************************
//���ӷ���ֵ

//*******************************************************************
//���ӷ���1 -- ETC2  0x18F00503	10Hz
		if(CAN1RxMessage.ExtId == 0x18FEF200)			//FlEco ȼ�;����� -- 10HZ													
		{
			//���̵�λ
			if(flagctrl.Bits.KDchange)												//KD��ʹ��--1������			
			{
				if(ControllerInfo.ProcessGear/0x10==0)					//ǰ����
				{
					CAN2TxMessage.Data[0]=125+0x01+10;				
				}
				else if(ControllerInfo.ProcessGear/0x10==1)			//���˵�
				{
					CAN2TxMessage.Data[0]=125-0x01-10;			
				}
				else if(ControllerInfo.ProcessGear/0x10==2)			//�յ�
				{
					CAN2TxMessage.Data[0]=125;
				}			
			}
			else
			{	
				if(ControllerInfo.ProcessGear/0x10==0)															//ǰ����
				{
					CAN2TxMessage.Data[0]=125+ControllerInfo.ProcessGear+10;				
				}
				else if(ControllerInfo.ProcessGear/0x10==1)													//���˵�
				{
					CAN2TxMessage.Data[0]=125+0x10-ControllerInfo.ProcessGear-10;			
				}
				else if(ControllerInfo.ProcessGear/0x10==2)													//�յ�
				{
					CAN2TxMessage.Data[0]=125+ControllerInfo.ProcessGear-0x20;
				}			
			}
			//Ŀ�굲λ
			if(ControllerInfo.GoalGear/0x10==0)																		//ǰ����
			{
				CAN2TxMessage.Data[3]=125+ControllerInfo.GoalGear+10;				
			}
			else if(ControllerInfo.GoalGear/0x10==1)															//���˵�
			{
				CAN2TxMessage.Data[3]=125+0x10-ControllerInfo.GoalGear-10;			
			}
			else if(ControllerInfo.GoalGear/0x10==2)															//�յ�
			{
				CAN2TxMessage.Data[3]=125+ControllerInfo.GoalGear-0x20;
			}				
		
			CAN2TxMessage.StdId = 0x0000;									//�趨��׼��ʶ��11λ��ֵ0-0x7ff -- 0x00~���������Ƶ�Ԫ
			CAN2TxMessage.ExtId = 0x18F00503;						  //�趨��չ��׼��ʶ��29λ��ֵ0-0x1fffffff  ��ETC2��
			CAN2TxMessage.RTR = CAN_RTR_DATA;							//����֡  CAN_RTR_REMOTE // CAN_RTR_DATA
			CAN2TxMessage.IDE = CAN_ID_EXT;								//��׼֡��ʽ[ExtID��Ч]CAN_ID_EXT //CAN_ID_STD
			CAN2TxMessage.DLC = 8;												//֡���ȣ���λ�ֽڣ������ͼ�������	
			
//			CAN2TxMessage.Data[0]=0x00;									//ѡ��λ -- ���̵�λ								
			CAN2TxMessage.Data[1]=0x00;										//
			CAN2TxMessage.Data[2]=0x00;										//
//			CAN2TxMessage.Data[3]=0x00;									//ѡ��λ -- Ŀ�굲λ				
			CAN2TxMessage.Data[4]=ErrorMessage;						//������Ϣ
			CAN2TxMessage.Data[5]=0x00;										//
			CAN2TxMessage.Data[6]=0x00;										//
			CAN2TxMessage.Data[7]=0x00;										//
			
			CAN_Transmit(CAN2, &CAN2TxMessage);							
		
		}
		
//*******************************************************************
//���ӷ���2 -- EEC4  0x0CF00500	50Hz
//���ӷ���3 -- EEC5  0x0CF00600	50Hz				
		if(CAN1RxMessage.ExtId == 0x0CF00400)		//EEC1 ���ӷ�����������1	--  50HZ												
		{
			CAN2TxMessage.StdId = 0x0000;									//�趨��׼��ʶ��11λ��ֵ0-0x7ff -- 0x00~���������Ƶ�Ԫ
			CAN2TxMessage.ExtId = 0x0CF00500;						  //�趨��չ��׼��ʶ��29λ��ֵ0-0x1fffffff  ��EEC4��
			CAN2TxMessage.RTR = CAN_RTR_DATA;							//����֡  CAN_RTR_REMOTE // CAN_RTR_DATA
			CAN2TxMessage.IDE = CAN_ID_EXT;								//��׼֡��ʽ[ExtID��Ч]CAN_ID_EXT //CAN_ID_STD
			CAN2TxMessage.DLC = 8;												//֡���ȣ���λ�ֽڣ������ͼ�������	
			
			CAN2TxMessage.Data[0]=XG.CANPressure[0]%0x100;				//							
			CAN2TxMessage.Data[1]=XG.CANPressure[0]/0x100;				//ѹ��������ֵ1
			CAN2TxMessage.Data[2]=XG.CANPressure[1]%0x100;				//
			CAN2TxMessage.Data[3]=XG.CANPressure[1]/0x100;				//ѹ��������ֵ2
			CAN2TxMessage.Data[4]=XG.CANPressure[2]%0x100;				//
			CAN2TxMessage.Data[5]=XG.CANPressure[2]/0x100;				//ѹ��������ֵ3
			CAN2TxMessage.Data[6]=XG.CANPressure[3]%0x100;				//
			CAN2TxMessage.Data[7]=XG.CANPressure[3]/0x100;				//ѹ��������ֵ4
			
			CAN_Transmit(CAN2, &CAN2TxMessage);				
	
			CAN2TxMessage.StdId = 0x0000;									//�趨��׼��ʶ��11λ��ֵ0-0x7ff -- 0x00~���������Ƶ�Ԫ
			CAN2TxMessage.ExtId = 0x0CF00600;						  //�趨��չ��׼��ʶ��29λ��ֵ0-0x1fffffff  ��EEC5��
			CAN2TxMessage.RTR = CAN_RTR_DATA;							//����֡  CAN_RTR_REMOTE // CAN_RTR_DATA
			CAN2TxMessage.IDE = CAN_ID_EXT;								//��׼֡��ʽ[ExtID��Ч]CAN_ID_EXT //CAN_ID_STD
			CAN2TxMessage.DLC = 8;												//֡���ȣ���λ�ֽڣ������ͼ�������	
			
			CAN2TxMessage.Data[0]=XG.CANPressure[4]%0x100;			//							
			CAN2TxMessage.Data[1]=XG.CANPressure[4]/0x100;			//ѹ��������ֵ5
			CAN2TxMessage.Data[2]=XG.CANPressure[5]%0x100;			//
			CAN2TxMessage.Data[3]=XG.CANPressure[5]/0x100;			//ѹ��������ֵ6
			CAN2TxMessage.Data[4]=0x00;										//
			CAN2TxMessage.Data[5]=0x00;										//
			CAN2TxMessage.Data[6]=0x00;										//
			CAN2TxMessage.Data[7]=0x00;										//
			
			CAN_Transmit(CAN2, &CAN2TxMessage);			
		}
//*******************************************************************		
//���ӷ���4 -- EEC6  0x0CF00700	50Hz			
	if(CAN1RxMessage.ExtId == 0x0CF00300)		//EEC2 	���ӷ�����������2		--  20HZ		
	{
			CAN2TxMessage.StdId = 0x0000;									//�趨��׼��ʶ��11λ��ֵ0-0x7ff -- 0x00~���������Ƶ�Ԫ
			CAN2TxMessage.ExtId = 0x0CF00700;						  //�趨��չ��׼��ʶ��29λ��ֵ0-0x1fffffff  ��EEC6��
			CAN2TxMessage.RTR = CAN_RTR_DATA;							//����֡  CAN_RTR_REMOTE // CAN_RTR_DATA
			CAN2TxMessage.IDE = CAN_ID_EXT;								//��׼֡��ʽ[ExtID��Ч]CAN_ID_EXT //CAN_ID_STD
			CAN2TxMessage.DLC = 8;												//֡���ȣ���λ�ֽڣ������ͼ�������	
			
			CAN2TxMessage.Data[0]=XG.CANSpeed[0]%0x100;					//							
			CAN2TxMessage.Data[1]=XG.CANSpeed[0]/0x100;					//ת��ֵ1
			CAN2TxMessage.Data[2]=XG.CANSpeed[1]%0x100;					//
			CAN2TxMessage.Data[3]=XG.CANSpeed[1]/0x100;					//ת��ֵ2
			CAN2TxMessage.Data[4]=XG.CANSpeed[2]%0x100;					//
			CAN2TxMessage.Data[5]=XG.CANSpeed[2]/0x100;					//ת��ֵ3
			CAN2TxMessage.Data[6]=XG.CANSpeed[3]%0x100;					//
			CAN2TxMessage.Data[7]=XG.CANSpeed[3]/0x100;					//ת��ֵ4
			
			CAN_Transmit(CAN2, &CAN2TxMessage);			
	}
		
}

/***********************************************************************
�������ƣ�void CAN2_RX0_IRQHandler(void)
��    �ܣ�CAN2�����жϴ������
���������
���������
��дʱ�䣺2014.04.14
�� д �ˣ�
ע    ��  
***********************************************************************/
void CAN2_RX0_IRQHandler(void)
{
  CAN_Receive(CAN2, CAN_FIFO0, &CAN2RxMessage);

}
