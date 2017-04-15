//========================================
//����˵��:       STM32F107VCӲ������ģ�����
//�˿�ʹ��: 
//������:          Masterjay   
//����ʱ��:       2013-11-19 
//�޸�ʱ��:       2013-11-19 
//========================================
//========================================
//ͷ�ļ�
#include "main.h"

//========================================
//��������



//========================================
//��������

void NVIC_Configuration(void);      //�жϵȼ�����  


//========================================
//��ģ�麯��





/*******************************************************************************
* Function Name    : void NVIC_Configuration(void)
* Description          : Configures the used IRQ Channels and sets their priority.
* Input                   : None
* Output                : None
* Return                : None
*******************************************************************************/
/***********************************************************************
�������ƣ� void NVIC_Configuration(void)
��    �ܣ��жϵȼ�����
���������
���������
��дʱ�䣺2014.04.14
�� д �ˣ�
ע    �⣺
IO�ж϶�Ӧ���жϾ����ϵΪ��	GPIOX0 -- EXTI0_IRQHandler
															GPIOX1 -- EXTI1_IRQHandler					
															GPIOX2 -- EXTI1_IRQHandler	
															GPIOX3 -- EXTI1_IRQHandler					
															GPIOX4 -- EXTI1_IRQHandler	

															GPIOX5~GPIOX9 -- EXTI9_5_IRQHandler						
															GPIOX10~GPIOX15 -- EXTI15_10_IRQHandler	
***********************************************************************/
void NVIC_Configuration(void)
{ 
      NVIC_InitTypeDef NVIC_InitStructure;
      /* Set the Vector Table base address at 0x08000000 */
      NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0000);

// 			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);			//�������ȼ� 0   		��Ӧ���ȼ� 0-15	
// 			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);			//�������ȼ� 0-1    ��Ӧ���ȼ� 0-7	
// 			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			//�������ȼ� 0-3    ��Ӧ���ȼ� 0-3	
// 			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);			//�������ȼ� 0-7    ��Ӧ���ȼ� 0-1	
			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);			//�������ȼ� 0-15   ��Ӧ���ȼ� 0
	
      /* Enable the TIM5 gloabal Interrupt */
			NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	  
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);	
	
			NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;	  
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);

			NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;	  
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);	
	
			NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;	  
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);
	
			NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;	  
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);


			NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;							//�趨ͨ��
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 15;	//�������ȼ�����  0��1
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					//��Ӧ���ȼ�����
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
      NVIC_Init(&NVIC_InitStructure); 
		 
}
