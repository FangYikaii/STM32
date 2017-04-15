/*
����˵��:  	
            USARTx ����ͨ�ų��� --- STM32F107VCT 
						
ע�����	1��ע��ܽŵĸ�������						
						
						
�˿�ʹ��:		��Doc�ļ�����˵��
������:     FangYIkaii   
����ʱ��:   2017-01-19
�޸�ʱ��:   2017-01-19
*/
/*
RS232�������ӿ��ߣ��������ݡ��������ݡ��źŵ�-----�����ƽ�źţ��ź�1Ϊ-3V��-15V,�ź�0Ϊ3V��15V,�����𻵽ӿڵ�·оƬ������Ҫת����ƽ��·��TTL��·�����������Ų
2:RxD,Input 3:TxD,Output 5:GND

RS485���������źţ��ź�1�Ե�ѹ��+2-+6V��ʾ���ź�0�����ߵ�ѹ��-2V--6V��ʾ����TTL��ƽ���ݣ�������TTL��·�����ӣ�
485+ 485-

������룺RS232��15��25m����߲�����19200bps   RS485��120��3000�ף���ߴ�������10Mbps
*/
/*
USARTx_TX ȫ˫��ģʽ          ���츴�����
          ��˫��ͬ��ģʽ      ���츴�����
USARTx_RX ȫ˫��ģʽ          ������������������
          ��˫��ͬ��ģʽ      δ�ã�����Ϊͨ��I/O
GPIO_MODE_AIN ģ������  GPIO_MODE_FLOATING ��������   GPIO_MODE_IPD ��������  GPIO_MODE_IPU ��������
GPIO_MODE_Out_OD ��©���  GPIO_MODE_Out_PP �������  GPIO_MODE_AF_OD ���ÿ�©���  GPIO_MODE_AF_PP �����������
*/
//========================================
//ͷ�ļ�
#include "main.h"

//========================================
//��������
//����ṹ�� UART���
struct UartResult Rec_COM1;
struct UartResult Rec_COM2;
//���������� UART��־λ
volatile union FlagUart flagCOM1;
volatile union FlagUart flagCOM2;
//���������� UART���ձ�־λ
volatile union FlagUartRec flagUartRecCOM1;
volatile union FlagUartRec flagUartRecCOM2;

USART_InitTypeDef USART_InitStructure;
//COM_USART[COMn] ��������
USART_TypeDef* COM_USART[COMn] = {UART_COM1, UART_COM2, UART_COM3, UART_COM4, UART_COM5}; 
//COM_TX_PORT[COMn] ���ڷ��Ͷ˿�
GPIO_TypeDef* COM_TX_PORT[COMn] = {UART_COM1_TX_GPIO_PORT, UART_COM2_TX_GPIO_PORT, UART_COM3_TX_GPIO_PORT, UART_COM4_TX_GPIO_PORT, UART_COM5_TX_GPIO_PORT}; 
//COM_RX_PORT[COMn] ���ڽ��ն˿�
GPIO_TypeDef* COM_RX_PORT[COMn] = {UART_COM1_RX_GPIO_PORT, UART_COM2_RX_GPIO_PORT, UART_COM3_RX_GPIO_PORT, UART_COM4_RX_GPIO_PORT, UART_COM5_RX_GPIO_PORT}; 
//COM_USART_CLK[COMn] ����ʱ��
const uint32_t COM_USART_CLK[COMn] = {UART_COM1_CLK, UART_COM2_CLK, UART_COM3_CLK, UART_COM4_CLK, UART_COM5_CLK};
//COM_TX_PORT_CLK[COMn] ���ڷ���ʱ��
const uint32_t COM_TX_PORT_CLK[COMn] = {UART_COM1_TX_GPIO_CLK, UART_COM2_TX_GPIO_CLK, UART_COM3_TX_GPIO_CLK, UART_COM4_TX_GPIO_CLK, UART_COM5_TX_GPIO_CLK};
//COM_RX_PORT_CLK[COMn] ���ڽ���ʱ��
const uint32_t COM_RX_PORT_CLK[COMn] = {UART_COM1_RX_GPIO_CLK, UART_COM2_RX_GPIO_CLK, UART_COM3_RX_GPIO_CLK, UART_COM4_RX_GPIO_CLK, UART_COM5_RX_GPIO_CLK};
//COM_TX_PIN[COMn] ���ڷ��͹ܽ�
const uint16_t COM_TX_PIN[COMn] = {UART_COM1_TX_PIN, UART_COM2_TX_PIN, UART_COM3_TX_PIN, UART_COM4_TX_PIN, UART_COM5_TX_PIN};
//COM_RX_PIN[COMn] ���ڽ��չܽ�
const uint16_t COM_RX_PIN[COMn] = {UART_COM1_RX_PIN, UART_COM2_RX_PIN, UART_COM3_RX_PIN, UART_COM4_RX_PIN, UART_COM5_RX_PIN};

//========================================
//��������
void Uart_Init(void);   //���ڳ�ʼ��
void STM_UART_COMInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct);	//���ڳ�ʼ���ó���
void SerialPutChar(USART_TypeDef* USARTx, uint8_t Data);	//���ڳ�ʼ���ó���

void USART_COM1_GetInputString(void);			//���ڽ������ݴ���
void USART_COM2_GetInputString(void);			//���ڽ������ݴ���
void RS485_COM1_PutChar(USART_TypeDef* USARTx, uint8_t Data);	//RS485_COM2���͵��ֽ�����

uchar LRC_Check(uchar *data,uchar length);	//LRC�������

//========================================
//��ģ�麯��



/***********************************************************************
�������ƣ�void Uart_Init(void)
��    �ܣ�Uart���ڳ�ʼ��
�����������
�����������
��дʱ�䣺2017-01-19
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/
void Uart_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;      //����GPIO�ṹ��	

	//RS485 COM1
	RCC_APB2PeriphClockCmd(RS485_COM1_RCC_APB2Periph_EnGPIOX, ENABLE); 					 
	GPIO_InitStructure.GPIO_Pin = RS485_COM1_EnPIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;            //�������
	GPIO_Init(RS485_COM1_EnGPIOX, &GPIO_InitStructure);
	RS485_COM1_RxEnable(1);																			//RS485_COM1���ڽ���״̬

//���ڼ�������
	Rec_COM1.Count=0;	
	Rec_COM2.Count=0;	
	
//���ڲ�������	
	USART_InitStructure.USART_BaudRate = 9600;                          //������ 9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;         //����λ 8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;              //ֹͣλ 1λ
	USART_InitStructure.USART_Parity = USART_Parity_No;                 //��żУ��λ ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;     //ģʽ��Rx||Tx

	STM_UART_COMInit(COM1, &USART_InitStructure);				//���ڳ�ʼ���ó���--IO���õ�
	USART_ITConfig(UART_COM1, USART_IT_RXNE, ENABLE);		//���ڽ����ж�ʹ��
//USART_ITConfig(UART_COM1, USART_IT_TXE, ENABLE);		//���ڷ����ж�ʹ��
	USART_ITConfig(UART_COM1, USART_IT_TXE, DISABLE);		//���ڷ����ж�ʹ�ܲ��ܿ�������û�취����
	USART_ClearITPendingBit(UART_COM1, USART_IT_TC);		//����ж�TCλ
		
	STM_UART_COMInit(COM2, &USART_InitStructure);				//���ڳ�ʼ���ó���--IO���õ�
	USART_ITConfig(UART_COM2, USART_IT_RXNE, ENABLE);		//���ڽ����ж�ʹ��
//USART_ITConfig(UART_COM2, USART_IT_TXE, ENABLE);		//���ڷ����ж�ʹ��
	USART_ITConfig(UART_COM2, USART_IT_TXE, DISABLE);		//���ڷ����жϲ��ܿ�������û�취����
	USART_ClearITPendingBit(UART_COM2, USART_IT_TC);		//����ж�TCλ
	
}


/***********************************************************************
�������ƣ�void STM_UART_COMInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct)
��    �ܣ����ڳ�ʼ���ó���--IO���õ�
������������ںţ����ڲ����ṹ��
�����������
��дʱ�䣺2014.04.11
�� д �ˣ�masterjay
ע    �⣺
***********************************************************************/
void STM_UART_COMInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct)
{
      GPIO_InitTypeDef GPIO_InitStructure;
      /* Enable GPIO clock */
      RCC_APB2PeriphClockCmd(COM_TX_PORT_CLK[COM] | COM_RX_PORT_CLK[COM] | RCC_APB2Periph_AFIO, ENABLE);
      if (COM == COM1)
      {
// 						/* Enable the USART1 Pins Software Remapping */
//             GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);									//�ر�ע�⣬�Ƿ�ʹ��ӳ��ܽ�
						
				/* Enable the USART1 Pins */
				RCC_APB2PeriphClockCmd(COM_USART_CLK[COM], ENABLE);
				
      }
      else if(COM==COM2)
      {
				/* Enable the USART2 Pins Software Remapping */
				GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);									//�ر�ע�⣬�Ƿ�ʹ��ӳ��ܽ�
				
				/* Enable the USART2 Pins */
				RCC_APB1PeriphClockCmd(COM_USART_CLK[COM], ENABLE);				
      }
      else if(COM==COM3)
      {
				/* Enable the USART2 Pins Software Remapping */
// 				GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);					//�ر�ע�⣬�Ƿ�ʹ��ӳ��ܽ�
// 				GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);							//�ر�ע�⣬�Ƿ�ʹ��ӳ��ܽ�

				/* Enable the USART3 Pins */
				RCC_APB1PeriphClockCmd(COM_USART_CLK[COM], ENABLE);				
      }			
      else
      {
				/* Enable the USART4/5 Pins */
				RCC_APB1PeriphClockCmd(COM_USART_CLK[COM], ENABLE);				
      }			
		
			//USART Tx ���Ͷ�����
      /* Configure USART Tx as alternate function push-pull */
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                     //USART Tx:���Ͷ˵����--�������PUSH PULL
      GPIO_InitStructure.GPIO_Pin = COM_TX_PIN[COM];                      //USART Tx:���Ͷ˵ĹܽŶ���--
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                   //USART Tx:���Ͷ˵��ٶ�--50MHz
      GPIO_Init(COM_TX_PORT[COM], &GPIO_InitStructure);                   //USART Tx:���Ͷ˵Ķ˿�����

			//USART Tx ���Ͷ�����			
      /* Configure USART Rx as input floating */
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;               //USART Rx:���ն˵�����--��������FLOATING
      GPIO_InitStructure.GPIO_Pin = COM_RX_PIN[COM];                      //USART Rx:���ն˵ĹܽŶ���--
      GPIO_Init(COM_RX_PORT[COM], &GPIO_InitStructure);                   //USART Rx:���ն˵Ķ˿�����--
			
			//USART ����
      /* USART configuration */
      USART_Init(COM_USART[COM], USART_InitStruct);
    
			//USART ʹ��
      /* Enable USART */
      USART_Cmd(COM_USART[COM], ENABLE);
}



/***********************************************************************
�������ƣ�void SerialPutChar(USART_TypeDef* USARTx, uint8_t Data)
��    �ܣ����ڷ��͵��ֽ����� char  0x00
������������ںţ���ֵ
�����������
��дʱ�䣺2017-01-19
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/
void SerialPutChar(USART_TypeDef* USARTx, uint8_t Data)
{
    USART_SendData(USARTx, Data);
		//ֱ����λ����
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)
//  while(!(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == SET)) 
    {
        ;
    }
}

/***********************************************************************
�������ƣ�void RS485_COM1_PutChar(USART_TypeDef* USARTx, uint8_t Data)
��    �ܣ�RS485_COM1���͵��ֽ�����  char 0x00
������������ںţ���ֵ
�����������
��дʱ�䣺2017-01-19
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/
void RS485_COM1_PutChar(USART_TypeDef* USARTx, uint8_t Data)
{
		RS485_COM1_RxEnable(0);																	//RS485_COM1����״̬	
		delay(10);
    USART_SendData(USARTx, Data);
	  //ֱ����λ����
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)
//  while(!(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == SET)) 
    {
        ;
    }
		RS485_COM1_RxEnable(1);																	//RS485_COM1���ڽ���״̬		
}


/***********************************************************************
�������ƣ�void USART_COM1_GetInputString(void)
��    �ܣ����ڽ������ݴ���
�����������
�����������
��дʱ�䣺2017-01-19
�� д �ˣ�FangYikaii
ע    �⣺���ͣ�0x3A 0x01 0x���� ...����... 0x0D 0x0A   [3A��ʼλ��01ѡ����ģʽ������λ���ȣ�0D 0A ����λ][���ݳ���Ϊ����λ����ĳ���]
					��ȡ��0x3A 0x02 0x���� ...����... 0x0D 0x0A   [3A��ʼλ��02ѡ���ȡģʽ������λ���ȣ�0D 0A ����λ][���ݳ���Ϊ����λ����ĳ���] 
***********************************************************************/
void USART_COM1_GetInputString(void)
{
	uchar data;	
	data=USART_ReceiveData(USART1);	
	
	//��һλΪ0
	if(Rec_COM1.Count==0)
	{		
		//��ʼλ0x3A
		if(data==0x3A)	
		{
			Rec_COM1.Data[Rec_COM1.Count]=data;	
			Rec_COM1.Count++;	
		}				
	}	 
	//�ڶ�λ
	else if(Rec_COM1.Count==1)
	{
		Rec_COM1.Data[Rec_COM1.Count]=data;
		//�ڶ�λ��0x01 ����ģʽ
		if(Rec_COM1.Data[Rec_COM1.Count]==0x01)
		{
			flagUartRecCOM1.Bits.SetFlag=TRUE;
			Rec_COM1.Count++;
		}
		//�ڶ�λ��0x02 ��ȡģʽ
		else if(Rec_COM1.Data[Rec_COM1.Count]==0x02)
		{
			flagUartRecCOM1.Bits.ReadFlag=TRUE;
			Rec_COM1.Count++;
		}
		else
		{
			Rec_COM1.Count=0;
		}
	}
	//����--��ȡ�����ݳ���
	else if(Rec_COM1.Count==2)
	{
		Rec_COM1.Data[Rec_COM1.Count]=data;
		Rec_COM1.length=Rec_COM1.Data[Rec_COM1.Count];
		Rec_COM1.Count++;
	}
	else  
	{
		//����ģʽ
		if(flagUartRecCOM1.Bits.SetFlag==TRUE)
		{			
			Rec_COM1.Data[Rec_COM1.Count]=data;
			Rec_COM1.Count++;					
			//���ݸ�ʽ  Count>���ݳ���+����5����ʽ�����ַ� && �����0x0A && ���ڶ�����0x0D
			if((Rec_COM1.Count>=Rec_COM1.length+5)&&Rec_COM1.Data[Rec_COM1.length+4]==0x0A && Rec_COM1.Data[Rec_COM1.length+3]==0x0D)
			{	
					flagUartRecCOM1.Bits.SetFlag=FALSE;
					Rec_COM1.Count=0;
					flagUartRecCOM1.Bits.UART_Rec_Flag = TRUE;
			}
			else			
			{
				if(Rec_COM1.Count>=RX_MaxSize)
				{
					//���ͱ�־λ��λ
					flagUartRecCOM1.Bits.SetFlag=FALSE;
					//Count��0
					Rec_COM1.Count=0;
				}					
			}
		}
		//��ȡģʽ
		if(flagUartRecCOM1.Bits.ReadFlag==TRUE)
		{
				Rec_COM1.Data[Rec_COM1.Count]=data;
				Rec_COM1.Count++;											
				if((Rec_COM1.Count>=Rec_COM1.length+5)&&Rec_COM1.Data[Rec_COM1.length+4]==0x0A && Rec_COM1.Data[Rec_COM1.length+3]==0x0D)
				{	
						//��ȡ��־λ��λ
						flagUartRecCOM1.Bits.ReadFlag=FALSE;
						//Count��0
						Rec_COM1.Count=0;
						//д����1���ձ�־λ
						flagUartRecCOM1.Bits.UART_Rec_Flag = TRUE;					
				}
				else
				{
					if(Rec_COM1.Count>=RX_MaxSize)
					{
						//��ȡ��־λ��λ
						flagUartRecCOM1.Bits.ReadFlag=FALSE;
						//Count��0
						Rec_COM1.Count=0;
					}					
				}					
		}
	}				
}

/***********************************************************************
�������ƣ�void USART_COM2_GetInputString(void)
��    �ܣ����ڽ������ݴ���
�����������
�����������
��дʱ�䣺2017-01-19
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/
void USART_COM2_GetInputString(void)
{
	uchar check_data;
	uchar check_orgi;
	uchar data;	
	data=USART_ReceiveData(USART2);	
	if(Rec_COM2.Count==0)
	{		
		if(data==0x3A)	
		{
			Rec_COM2.TimeOut=0;										//���������ʱ
//			flagA.Bits.COM2_TimeFlag=TRUE;				//���������ʱ
			Rec_COM2.Data[Rec_COM2.Count]=data;	
			Rec_COM2.Count++;	
		}				
	}	 
	else if(Rec_COM2.Count<60)
	{
		Rec_COM2.Data[Rec_COM2.Count]=data;
		Rec_COM2.Count++;											//���ݸ�ʽ  3A   ...  0D 0A
		if(Rec_COM2.Data[0]==0x3a)
		{
			if(Rec_COM2.Count>=4)
			{
				if(Rec_COM2.Data[Rec_COM2.Count-1]==0x0A && Rec_COM2.Data[Rec_COM2.Count-2]==0x0D)
				{
					check_data=LRC_Check(Rec_COM2.Data,(Rec_COM2.Count-5));					//LRC����
					if(Rec_COM2.Data[Rec_COM2.Count-4]<0x3A)
					{
						check_orgi=Rec_COM2.Data[Rec_COM2.Count-4]%0x30;				
					}
					else
					{
						check_orgi=Rec_COM2.Data[Rec_COM2.Count-4]%0x41;
						check_orgi=check_orgi+10;	
					}
					check_orgi=check_orgi*0x10;						
					if(Rec_COM2.Data[Rec_COM2.Count-3]<0x3A)
					{
						check_orgi+=Rec_COM2.Data[Rec_COM2.Count-3]%0x30;				
					}
					else
					{
						check_orgi+=Rec_COM2.Data[Rec_COM2.Count-3]%0x41;
						check_orgi=check_orgi+10;	
					}
					if(check_data==check_orgi)
					{
						flagUartRecCOM2.Bits.UART_Rec_Flag=TRUE;
					}				
					Rec_COM2.Count=0;					
					Rec_COM2.TimeOut=0;										     	//���������ʱ
					flagCOM2.Bits.OverTime_Flag=FALSE;					//���������ʱ							
										
				}
			}
		}				
	}	
	else
	{
		Rec_COM2.Count=0;					
	}	  							
}


/***********************************************************************
�������ƣ�uchar LRC_Check(uchar *data,uchar length)
��    �ܣ�LRC�������
�����������
�����������
��дʱ�䣺2014.04.11
�� д �ˣ�masterjay
ע    �⣺
***********************************************************************/
uchar LRC_Check(uchar *data,uchar length)
{
	uchar i;
	uint k;
	uchar result;
	uchar lrcdata[RX_MaxSize];
	for(i=1;i<length+1;i++)
	{
		if(data[i]>0x40)
			lrcdata[i-1]=data[i]-0x41+10;
		else
			lrcdata[i-1]=data[i]-0x30;	
	}		
	k=0;	
	for(i=0;i<length/2;i++)
	{		
		k+=(lrcdata[2*i]*16+lrcdata[2*i+1]); 	
	}
	k=k%256;
	k=256-k;
	result=k%256;
	return result;
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
      while (1)
      {
            ;
      }
}
#endif

