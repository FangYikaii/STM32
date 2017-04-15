//========================================
//����˵��:       STM32F107VC�жϵȼ�����
//�˿�ʹ��: 
//������:          FangYikaii   
//����ʱ��:       2017-01-17 
//�޸�ʱ��:       2013-01-17 
//========================================
//========================================
//���ȳ̶ȣ�������NVIC_IRQChannelPreemptionPriority--����ӦNVIC_IRQChannelSubPriority
//�ж�����  ��ռ���ȼ�  ��Ӧ���ȼ�
//A          0          0
//B          1          0
//C          1          1
//����ִ��C,C�ɱ���ռ���ȼ����ߵ�A��ϣ�B��C����ռ���ȼ�һ����C���ܱ�B��ϣ
//��B��Cͬʱ���B����Ӧ

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
��дʱ�䣺2017.01.16
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
  
	//USART1_IRQn
	/* Enable the USART1_IRQn gloabal Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	              //�趨ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //�������ȼ����� 0 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	            //��Ӧ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
	
	//USART2_IRQn
	/* Enable the USART2_IRQn gloabal Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;	              //�趨ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;       //�������ȼ����� 0 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	            //�������ȼ����� 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//TIM5-��ͨ��ʱ
	//���ȳ̶ȵ͡�����=15��
	/* Enable the TIM5 gloabal Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;							//�趨ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 15;	//�������ȼ�����  0��1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					//��Ӧ���ȼ�����
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure); 
	
	//TIM4-Ƶ�ʲ���
	/* Enable the TIM5 gloabal Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =5;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);


// 	NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
// 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =6;
// 	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;
// 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
// 	NVIC_Init(&NVIC_InitStructure);   
}
