//========================================
//����˵��:       STM32F107VC Ƶ�ʲɼ�����
//�˿�ʹ��: 
//������:        	FangYikaii  
//����ʱ��:       2017-01-16 
//�޸�ʱ��:       2013-01-16 
//========================================
//========================================

//ͷ�ļ�
#include "main.h"

//========================================
//��������
struct FreqCapResult TIM1FreqCap[4];                  //Ƶ�ʲɼ���� TIM1 FreqCap
struct FreqCapResult TIM4FreqCap[4];                  //Ƶ�ʲɼ���� TIM4 FreqCap
uint8_t FreqCapChannelNO=1;														//����ͨ��ѡ��



//========================================
//��������
void FreqCap_Configuration(u16 arr,u16 psc);					//���PULSE������
void TIM1_CC_IRQHandler(void);                        //TIM1�жϴ�����
void TIM4_IRQHandler(void);                           //TIM2�жϴ�����



//========================================
//��ģ�麯��
/***********************************************************************
�������ƣ�void FreqCap_Configuration(u16 arr,u16 psc)
��    �ܣ����PULSE������
���������
���������
��дʱ�䣺2017.01.17
�� д �ˣ�FangYIkaii
ע    �⣺
***********************************************************************/
void FreqCap_Configuration(u16 arr,u16 psc)
{	 
	//���嶨ʱ���ṹ��
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	//�������벶��ṹ�� <INPUT CAPTURE�� TIM_Channel ͨ�� TIM_ICPolarity �������½����� TIM_ICSelection TIM_ICPrescaler  TIM_ICFilter>
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	//����GPIO�ṹ��  GPIO_Speed GPIO_Mode GPIO_Pin
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//�������IO����
	/*PlusGeneration Enable*/
	RCC_APB2PeriphClockCmd(PULSEGeneration_RCC_APB2Periph_GPIOX, ENABLE); 	//IO�˿�ʱ�ӿ���			 
			
	GPIO_InitStructure.GPIO_Pin = PULSEGeneration_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(PULSEGeneration_GPIOX, &GPIO_InitStructure);		
		
// 	//TIM1��׽ͨ��
		
//	//1.����ʱ��
//	//2.GPIO����(1.GPIO_PIN��2.GPIO_Mode��3.GPIO_Speed)
//	//3.GPIO��ʼ��
		
//	//TIM1 FC1
// 	RCC_APB2PeriphClockCmd(FreqCap1TIM1_RCC_APB2Periph_GPIOX,ENABLE);	
// 	GPIO_InitStructure.GPIO_Pin = FreqCap1TIM1_GPIO_PIN;     
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(FreqCap1TIM1_GPIOX, &GPIO_InitStructure);	
//
//	//TIM1 FC2
// 	RCC_APB2PeriphClockCmd(FreqCap2TIM1_RCC_APB2Periph_GPIOX,ENABLE);	
// 	GPIO_InitStructure.GPIO_Pin = FreqCap2TIM1_GPIO_PIN;     
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(FreqCap2TIM1_GPIOX, &GPIO_InitStructure);	
// 	
//	//TIM1 FC3
// 	RCC_APB2PeriphClockCmd(FreqCap3TIM1_RCC_APB2Periph_GPIOX,ENABLE);	
// 	GPIO_InitStructure.GPIO_Pin = FreqCap3TIM1_GPIO_PIN;     
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(FreqCap3TIM1_GPIOX, &GPIO_InitStructure);	
//
//	//TIM1 FC4
// 	RCC_APB2PeriphClockCmd(FreqCap4TIM1_RCC_APB2Periph_GPIOX,ENABLE);	
// 	GPIO_InitStructure.GPIO_Pin = FreqCap4TIM1_GPIO_PIN;     
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(FreqCap4TIM1_GPIOX, &GPIO_InitStructure);	
	
	
	//TIM4��׽ͨ��	
	
	//1.����ʱ��
	//2.GPIO����(1.GPIO_PIN��2.GPIO_Mode��3.GPIO_Speed)
	//3.GPIO��ʼ��

//	//TIM4 FC1
// 	RCC_APB2PeriphClockCmd(FreqCap1TIM4_RCC_APB2Periph_GPIOX,ENABLE);	
// 	GPIO_InitStructure.GPIO_Pin = FreqCap1TIM4_GPIO_PIN;     
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(FreqCap2TIM4_GPIOX, &GPIO_InitStructure);	
	
	//TIM4 FC2
	RCC_APB2PeriphClockCmd(FreqCap2TIM4_RCC_APB2Periph_GPIOX,ENABLE);	
	GPIO_InitStructure.GPIO_Pin = FreqCap2TIM4_GPIO_PIN;     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(FreqCap2TIM4_GPIOX, &GPIO_InitStructure);	
	
	//TIM4 FC3
	RCC_APB2PeriphClockCmd(FreqCap3TIM4_RCC_APB2Periph_GPIOX,ENABLE);	
	GPIO_InitStructure.GPIO_Pin = FreqCap3TIM4_GPIO_PIN;     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(FreqCap3TIM4_GPIOX, &GPIO_InitStructure);	
	
	//TIM4 FC4
	RCC_APB2PeriphClockCmd(FreqCap4TIM4_RCC_APB2Periph_GPIOX,ENABLE);	
	GPIO_InitStructure.GPIO_Pin = FreqCap4TIM4_GPIO_PIN;     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(FreqCap4TIM4_GPIOX, &GPIO_InitStructure);	
			
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);						//TIMxʱ�ӿ���
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);							//TIMxʱ�ӿ���

 /* ---------------------------------------------------------------
	TIMxCLK = 72 MHz, Prescaler = 72, T=1MHz // 0.001ms  �����ź� 2ms  ��2�������ؿɼǵ�2000����
	--------------------------------------------------------------- */      
	/* Time base configuration */
	//TIM4
  //((1+TIM_Prescaler)/72M)*(1+TIM_Period)=(1+71)/72000000*(1+65535)=0.065536 s
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


	TIM_Cmd(TIM4, ENABLE);							//������ʱ��TIM4
	TIM4FreqCap[0].IsUsedFlag=0;
	TIM4FreqCap[1].IsUsedFlag=1;
	TIM4FreqCap[2].IsUsedFlag=1;
	TIM4FreqCap[3].IsUsedFlag=1;	
//  	TIM_Cmd(TIM1, ENABLE);							//������ʱ��TIM1   
//	TIM1FreqCap[0].IsUsedFlag=1;
//	TIM1FreqCap[1].IsUsedFlag=1;
//	TIM1FreqCap[2].IsUsedFlag=1;
//	TIM1FreqCap[3].IsUsedFlag=1;	     
}


/***********************************************************************
�������ƣ�void TIM1_CC_IRQHandler(void)
��    �ܣ�TIM1�жϴ�����
���������
���������
��дʱ�䣺2017.01.18
�� д �ˣ�FangYIkaii
ע    ��  
***********************************************************************/
void TIM1_CC_IRQHandler(void)
{ 
	//��ͨ��1���������¼�
	if(TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)
	{
		TIM1FreqCap[0].NOINT_s=0;																					//��δ������׽�жϼ�ʱ��			
		//�����β����ֵ����������õ���ȷ������ֵ			
		if(TIM1FreqCap[0].count==0)
		{
				 //TIM1FreqCap[0]�ĵ�һ������ֵ	
				 TIM1FreqCap[0].pulse1=TIM_GetCapture1(TIM1);									//��ȡTIM1 CCR1��ֵ
				 TIM1FreqCap[0].count=1;
		}
		else
		{
			//TIM1FreqCap[0]�ĵڶ�������ֵ
			TIM1FreqCap[0].pulse2=TIM_GetCapture1(TIM1);
			TIM1FreqCap[0].count=0;
			if(TIM1FreqCap[0].pulse2>TIM1FreqCap[0].pulse1)
			{
				//pluse2>pluse1
				//TIM1FreqCap[0]�������ֵ=pluse2-pluse1
				TIM1FreqCap[0].pulse=TIM1FreqCap[0].pulse2-TIM1FreqCap[0].pulse1;			//����2���жϼ�ļ�ʱ��������ֵ
			}
			else
			{
				//pluse2<pluse1
				//TIM1FreqCap[0]�������ֵ=65535+(pluse2-pluse1)
				TIM1FreqCap[0].pulse=0xffff-TIM1FreqCap[0].pulse1;
				TIM1FreqCap[0].pulse+=TIM1FreqCap[0].pulse2;											//����2���жϼ�ļ�ʱ��������ֵ					
			}
			TIM1FreqCap[0].Freq=1000000.0/TIM1FreqCap[0].pulse;									//�������Ƶ��
		}
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);					//���жϱ�־	
	}
	
	//��ͨ��2���������¼�
	if(TIM_GetITStatus(TIM1, TIM_IT_CC2) != RESET)
	{
		TIM1FreqCap[1].NOINT_s=0;																					//��δ������׽�жϼ�ʱ��				
		//�����β����ֵ����������õ���ȷ������ֵ			
		if(TIM1FreqCap[1].count==0)
		{
				 //TIM1FreqCap[1]�ĵ�һ������ֵ	
				 TIM1FreqCap[1].pulse1=TIM_GetCapture2(TIM1);//��ȡTIM1 CCR2��ֵ
				 TIM1FreqCap[1].count=1;
		}
		else
		{
			//TIM1FreqCap[1]�ĵڶ�������ֵ
			TIM1FreqCap[1].pulse2=TIM_GetCapture2(TIM1);
			TIM1FreqCap[1].count=0;
			if(TIM1FreqCap[1].pulse2>TIM1FreqCap[1].pulse1)
			{
				//pluse2>pluse1
				//TIM1FreqCap[1]�������ֵ=pluse2-pluse1
				TIM1FreqCap[1].pulse=TIM1FreqCap[1].pulse2-TIM1FreqCap[1].pulse1;			//����2���жϼ�ļ�ʱ��������ֵ
			}
			else
			{
				//pluse2<pluse1
				//TIM1FreqCap[1]�������ֵ=65535+(pluse2-pluse1)
				TIM1FreqCap[1].pulse=0xffff-TIM1FreqCap[1].pulse1;
				TIM1FreqCap[1].pulse+=TIM1FreqCap[1].pulse2;											//����2���жϼ�ļ�ʱ��������ֵ					
			}
			TIM1FreqCap[1].Freq=1000000.0/TIM1FreqCap[1].pulse;									//�������Ƶ��
		}			
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC2);					//���жϱ�־	
	}
	
	//��ͨ��3���������¼�
	if(TIM_GetITStatus(TIM1, TIM_IT_CC3) != RESET)
	{
		TIM1FreqCap[2].NOINT_s=0;																					//��δ������׽�жϼ�ʱ��				
		//�����β����ֵ����������õ���ȷ������ֵ			
		if(TIM1FreqCap[2].count==0)
		{
				 //TIM1FreqCap[2]�ĵ�һ������ֵ	
				 TIM1FreqCap[2].pulse1=TIM_GetCapture3(TIM1);//��ȡTIM1 CCR3��ֵ
				 TIM1FreqCap[2].count=1;
		}
		else
		{
			//TIM1FreqCap[2]�ĵڶ�������ֵ
			TIM1FreqCap[2].pulse2=TIM_GetCapture3(TIM1);
			TIM1FreqCap[2].count=0;
			if(TIM1FreqCap[2].pulse2>TIM1FreqCap[2].pulse1)
			{
				//pluse2>pluse1
				//TIM1FreqCap[2]�������ֵ=pluse2-pluse1
				TIM1FreqCap[2].pulse=TIM1FreqCap[2].pulse2-TIM1FreqCap[2].pulse1;			//����2���жϼ�ļ�ʱ��������ֵ
			}
			else
			{
				//pluse2<pluse1
				//TIM1FreqCap[2]�������ֵ=65535+(pluse2-pluse1)
				TIM1FreqCap[2].pulse=0xffff-TIM1FreqCap[2].pulse1;
				TIM1FreqCap[2].pulse+=TIM1FreqCap[2].pulse2;											//����2���жϼ�ļ�ʱ��������ֵ					
			}
			TIM1FreqCap[2].Freq=1000000.0/TIM1FreqCap[2].pulse;									//�������Ƶ��
		}			
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC3);					//���жϱ�־	
	}
	
	//��ͨ��4���������¼�
	if(TIM_GetITStatus(TIM1, TIM_IT_CC4) != RESET)
	{
		TIM1FreqCap[3].NOINT_s=0;																					//��δ������׽�жϼ�ʱ��			
		//�����β����ֵ����������õ���ȷ������ֵ			
		if(TIM1FreqCap[3].count==0)
		{
				 //TIM1FreqCap[3]�ĵ�һ������ֵ
				 TIM1FreqCap[3].pulse1=TIM_GetCapture4(TIM1);//��ȡTIM1 CCR4��ֵ
				 TIM1FreqCap[3].count=1;
		}
		else
		{
			//TIM1FreqCap[3]�ĵڶ�������ֵ
			TIM1FreqCap[3].pulse2=TIM_GetCapture4(TIM1);
			TIM1FreqCap[3].count=0;
			if(TIM1FreqCap[3].pulse2>TIM1FreqCap[3].pulse1)
			{
				//pluse2>pluse1
				//TIM1FreqCap[3]�������ֵ=pluse2-pluse1
				TIM1FreqCap[3].pulse=TIM1FreqCap[3].pulse2-TIM1FreqCap[3].pulse1;			//����2���жϼ�ļ�ʱ��������ֵ
			}
			else
			{
				//pluse2<pluse1
				//TIM1FreqCap[3]�������ֵ=65535+(pluse2-pluse1)
				TIM1FreqCap[3].pulse=0xffff-TIM1FreqCap[3].pulse1;
				TIM1FreqCap[3].pulse+=TIM1FreqCap[3].pulse2;											//����2���жϼ�ļ�ʱ��������ֵ					
			}
			TIM1FreqCap[3].Freq=1000000.0/TIM1FreqCap[3].pulse;									//�������Ƶ��
		}	
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC4);					//���жϱ�־		
	}
	
	//��ʱ������жϴ������
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);					//���жϱ�־
	}
}

/***********************************************************************
�������ƣ�void TIM4_IRQHandler(void)
��    �ܣ�TIM4�жϴ�����
���������
���������
��дʱ�䣺2017.01.18
�� д �ˣ�FangYIkaii
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
		TIM4FreqCap[1].pulse++;	
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
//ͨ��4���������ز����жϳ���
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
