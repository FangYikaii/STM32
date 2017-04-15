//========================================
//����˵��:       STM32F107VC�жϴ������
//�˿�ʹ��: 
//������:         FangYikaii   
//����ʱ��:       2017-01-17 
//�޸�ʱ��:       2017-01-17 
//========================================
//========================================
//ͷ�ļ�
#include "main.h"

//========================================
//��������


//========================================
//��������

void USART1_IRQHandler(void);    //UART_COM1�����жϴ������
void USART2_IRQHandler(void);    //UART_COM2�����жϴ������


//========================================
//��ģ�麯��

//*********************************************************
//�����жϴ������
/***********************************************************************
�������ƣ�void USART1_IRQHandler(void) 
��    �ܣ�UART_COM1�����жϴ������
���������
���������
***********************************************************************/
void USART1_IRQHandler(void)  
{
	//**********************************************************
	//�����жϴ������
	//��־λ��USART_IT_RXNE!=RESET
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) 
	{
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		USART_COM1_GetInputString();
	}
	//**********************************************************	
	//�����жϴ������
	//��־λ��USART_IT_TXE!=RESET
	if (USART_GetITStatus(USART1, USART_IT_TXE) != RESET) 
	{
    USART_ClearITPendingBit(USART1, USART_IT_TXE);           /* Clear the USART transmit interrupt                  */
	}	
	
	//**********************************************************	
	//����ͨ������������
	/* If overrun condition occurs, clear the ORE flag and recover communication */
	if (USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET)
	{
		(void)USART_ReceiveData(USART1);
	}
}


/***********************************************************************
�������ƣ�void USART2_IRQHandler(void) 
��    �ܣ�UART_COM2�����жϴ������
���������
���������
***********************************************************************/
void USART2_IRQHandler(void)  
{
	//**********************************************************
	//�����жϴ������
	//��־λ��USART_IT_RXNE!=RESET
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{	
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
		USART_COM2_GetInputString();											//���ڽ������ݴ���
	}
	
	//**********************************************************	
	//�����жϴ������
	//��־λ��USART_IT_TXE!=RESET
	if (USART_GetITStatus(USART2, USART_IT_TXE) != RESET) 
	{
    USART_ClearITPendingBit(USART2, USART_IT_TXE);           /* Clear the USART transmit interrupt                  */
	}	
	//**********************************************************	
	//����ͨ������������
		/* If overrun condition occurs, clear the ORE flag and recover communication */
if (USART_GetFlagStatus(USART2, USART_FLAG_ORE) != RESET)
{
		(void)USART_ReceiveData(USART2);
}
}
