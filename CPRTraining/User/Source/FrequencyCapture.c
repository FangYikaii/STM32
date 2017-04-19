//========================================
//����˵��:       STM32F107VC Ƶ�ʲɼ�����
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
struct FreqCapResult TIM1FreqCap[4];
struct FreqCapResult TIM4FreqCap[4];
uint8_t FreqCapChannelNO=1;														//����ͨ��ѡ��
uint16_t Freq_Output;																	//���Ƶ��ֵ


//========================================
//��������

void FreqCap_Configuration(u16 arr,u16 psc);					//���PULSE������




//========================================
//��ģ�麯��







/***********************************************************************
�������ƣ�void FreqCap_Configuration(u16 arr,u16 psc)
��    �ܣ����PULSE������
���������
���������
��дʱ�䣺2014.4.16
�� д �ˣ�
ע    �⣺
***********************************************************************/
void FreqCap_Configuration(u16 arr,u16 psc)
{	 
  
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure; 
	//�������IO����
	
	RCC_APB2PeriphClockCmd(PULSEGeneration_RCC_APB2Periph_GPIOX, ENABLE); 	//IO�˿�ʱ�ӿ���			 
			
	GPIO_InitStructure.GPIO_Pin = PULSEGeneration_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(PULSEGeneration_GPIOX, &GPIO_InitStructure);		
		
// 	//TIM1��׽ͨ��
// 	RCC_APB2PeriphClockCmd(FreqCap1TIM1_RCC_APB2Periph_GPIOX,ENABLE);	
// 	GPIO_InitStructure.GPIO_Pin = FreqCap1TIM1_GPIO_PIN;     
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(FreqCap1TIM1_GPIOX, &GPIO_InitStructure);	
// 	
// 	RCC_APB2PeriphClockCmd(FreqCap2TIM1_RCC_APB2Periph_GPIOX,ENABLE);	
// 	GPIO_InitStructure.GPIO_Pin = FreqCap2TIM1_GPIO_PIN;     
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(FreqCap2TIM1_GPIOX, &GPIO_InitStructure);	
// 	
// 	RCC_APB2PeriphClockCmd(FreqCap3TIM1_RCC_APB2Periph_GPIOX,ENABLE);	
// 	GPIO_InitStructure.GPIO_Pin = FreqCap3TIM1_GPIO_PIN;     
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(FreqCap3TIM1_GPIOX, &GPIO_InitStructure);	
// 	
// 	RCC_APB2PeriphClockCmd(FreqCap4TIM1_RCC_APB2Periph_GPIOX,ENABLE);	
// 	GPIO_InitStructure.GPIO_Pin = FreqCap4TIM1_GPIO_PIN;     
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(FreqCap4TIM1_GPIOX, &GPIO_InitStructure);	
	
	
	//TIM4��׽ͨ��	
	
// 	RCC_APB2PeriphClockCmd(FreqCap1TIM4_RCC_APB2Periph_GPIOX,ENABLE);	
// 	GPIO_InitStructure.GPIO_Pin = FreqCap1TIM4_GPIO_PIN;     
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(FreqCap2TIM4_GPIOX, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(FreqCap2TIM4_RCC_APB2Periph_GPIOX,ENABLE);	
	GPIO_InitStructure.GPIO_Pin = FreqCap2TIM4_GPIO_PIN;     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(FreqCap2TIM4_GPIOX, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(FreqCap3TIM4_RCC_APB2Periph_GPIOX,ENABLE);	
	GPIO_InitStructure.GPIO_Pin = FreqCap3TIM4_GPIO_PIN;     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(FreqCap3TIM4_GPIOX, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(FreqCap4TIM4_RCC_APB2Periph_GPIOX,ENABLE);	
	GPIO_InitStructure.GPIO_Pin = FreqCap4TIM4_GPIO_PIN;     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(FreqCap4TIM4_GPIOX, &GPIO_InitStructure);	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);						//TIMxʱ�ӿ���
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);							//TIMxʱ�ӿ���

 /* ---------------------------------------------------------------
	TIMxCLK = 72 MHz, Prescaler = 72, T=1MHz // 0.001ms  �����ź� 2ms  ��2�������ؿɼǵ�2000����
	--------------------------------------------------------------- */      
	/* Time base configuration */
	
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF; 										////�Զ�װ�صļ���ֵ�����ڼ����Ǵ�0��ʼ�ģ�����0xFFFF�����
	TIM_TimeBaseStructure.TIM_Prescaler =72-1; 										//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 									//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 							//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
//  	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 

// 	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;      					//ͨ��ѡ��1ͨ��             
// 	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;     //��׽�����أ��½��أ�TIM_ICPolarity_Falling  
// 	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //�ܽ���Ĵ�����Ӧ��ϵ -- ֱ�Ӷ�Ӧ 
// 	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; 					//��Ƶ�� ÿ1�β�׽�Ͳ����ж�  TIM_ICPSC_DIV2/3/4 -- ÿ2/3/4�β�׽�����ж�
// 	TIM_ICInitStructure.TIM_ICFilter = 0x00;												//�˲������ã������������������϶������ȶ�  --  0x00 -- 0x0F	
// 	TIM_ICInit(TIM4, &TIM_ICInitStructure);
//  	TIM_ICInit(TIM1, &TIM_ICInitStructure);	
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;                   
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;       
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;   
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; 
	TIM_ICInitStructure.TIM_ICFilter = 0x00;
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
//  	TIM_ICInit(TIM1, &TIM_ICInitStructure);	
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;                   
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;       
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;   
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; 
	TIM_ICInitStructure.TIM_ICFilter = 0x00;
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
//  	TIM_ICInit(TIM1, &TIM_ICInitStructure);	
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;                   
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;       
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;   
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; 
	TIM_ICInitStructure.TIM_ICFilter = 0x00;
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
//  	TIM_ICInit(TIM1, &TIM_ICInitStructure);	

// 	TIM_SelectInputTrigger(TIM1,TIM_TS_TI1FP1);																								//ѡ�񴥷�ʱ��Դ
// 	TIM_SelectSlaveMode(TIM1,TIM_SlaveMode_Reset);																						//ѡ�񴥷���ʽ
// 	TIM_SelectMasterSlaveMode(TIM1,TIM_MasterSlaveMode_Enable);																//������ʱ����������


	TIM_ITConfig(TIM4, TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4|TIM_IT_Update, ENABLE);  		//�򿪶�ʱ���ж�
	TIM_ClearITPendingBit(TIM4, TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4|TIM_IT_Update); 		//����жϱ�־λ

// 	TIM_ITConfig(TIM4, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4|TIM_IT_Update, ENABLE);  		//�򿪶�ʱ���ж�
// 	TIM_ClearITPendingBit(TIM4, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4|TIM_IT_Update); 		//����жϱ�־λ

//  	TIM_ITConfig(TIM1,TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4|TIM_IT_Update, ENABLE);
//  	TIM_ClearITPendingBit(TIM1, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4|TIM_IT_Update);


	TIM_Cmd(TIM4, ENABLE);							//������ʱ��
	TIM4FreqCap[0].IsUsedFlag=0;				//1 -- ��������  0 -- ����������
	TIM4FreqCap[1].IsUsedFlag=0;
	TIM4FreqCap[2].IsUsedFlag=0;
	TIM4FreqCap[3].IsUsedFlag=0;	
	
	
	TIM4FreqCap[1].pulse=((Fre_Min_Wave+Fre_Max_Wave)/2)*40;
	Freq_Output=TIM4FreqCap[1].pulse/40;														//���Ƶ��ֵ
	
	
//  	TIM_Cmd(TIM1, ENABLE);							//������ʱ��   
//	TIM1FreqCap[0].IsUsedFlag=1;
//	TIM1FreqCap[1].IsUsedFlag=1;
//	TIM1FreqCap[2].IsUsedFlag=1;
//	TIM1FreqCap[3].IsUsedFlag=1;	  

	/* Set the Vector Table base address at 0x08000000 */
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0000);

// 			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);			//�������ȼ� 0   		��Ӧ���ȼ� 0-15	
// 			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);			//�������ȼ� 0-1    ��Ӧ���ȼ� 0-7	
// 			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			//�������ȼ� 0-3    ��Ӧ���ȼ� 0-3	
// 			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);			//�������ȼ� 0-7    ��Ӧ���ȼ� 0-1	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);			//�������ȼ� 0-15   ��Ӧ���ȼ� 0



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


/***********************************************************************
�������ƣ�void TIM1_CC_IRQHandler(void)
��    �ܣ�TIM1�жϴ�����
���������
���������
��дʱ�䣺2014.04.14
�� д �ˣ�
ע    ��  
***********************************************************************/
void TIM1_CC_IRQHandler(void)
{ 

//********************************************	
//ͨ��1���������ز����жϳ���
	if(TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);		
		TIM1FreqCap[0].NOINT_s=0;	
		TIM1FreqCap[0].pulse++;	
	}		
	
//********************************************	
//ͨ��2���������ز����жϳ���
	if(TIM_GetITStatus(TIM1, TIM_IT_CC2) != RESET)
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC2);		
		TIM1FreqCap[1].NOINT_s=0;	
		TIM1FreqCap[1].pulse++;	
	}	
	
//********************************************	
//ͨ��3���������ز����жϳ���
	if(TIM_GetITStatus(TIM1, TIM_IT_CC3) != RESET)
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC3);		
		TIM1FreqCap[2].NOINT_s=0;	
		TIM1FreqCap[2].pulse++;	
	}		
	
//********************************************	
//ͨ��2���������ز����жϳ���
	if(TIM_GetITStatus(TIM1, TIM_IT_CC4) != RESET)
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC4);		
		TIM1FreqCap[3].NOINT_s=0;	
		TIM1FreqCap[3].pulse++;	
	}		
	
//********************************************		
//��ʱ������жϴ������
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);	
	}		
	
	
}

/***********************************************************************
�������ƣ�void TIM4_IRQHandler(void)
��    �ܣ�TIM4�жϴ�����
���������
���������
��дʱ�䣺2014.04.14
�� д �ˣ�
ע    ��  
***********************************************************************/
void TIM4_IRQHandler(void)
{ 

//********************************************	
//ͨ��1���������ز����жϳ���
	if(TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_CC1);		
		TIM4FreqCap[0].NOINT_s=0;	
		TIM4FreqCap[0].pulse++;	
	}		
	
//********************************************	
//ͨ��2���������ز����жϳ���
	if(TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET)
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_CC2);		
		TIM4FreqCap[1].NOINT_s=0;	

		if(DigIO_IO1_Read)
		{
			if(TIM4FreqCap[1].pulse<Fre_Max_Wave*40)
			{
				TIM4FreqCap[1].pulse++;	
			}	
		}
		else
		{
	
			if(TIM4FreqCap[1].pulse>Fre_Min_Wave*40)
			{
				TIM4FreqCap[1].pulse--;	
			}			
		}			
		
	}	

//********************************************	
//ͨ��3���������ز����жϳ���
	if(TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET)
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_CC3);		
		TIM4FreqCap[2].NOINT_s=0;	
		TIM4FreqCap[2].pulse++;	
	}		
	
//********************************************	
//ͨ��2���������ز����жϳ���
	if(TIM_GetITStatus(TIM4, TIM_IT_CC4) != RESET)
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_CC4);		
		TIM4FreqCap[3].NOINT_s=0;	
		TIM4FreqCap[3].pulse++;	
	}		
	
//********************************************		
//��ʱ������жϴ������
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);	
	}		

}
