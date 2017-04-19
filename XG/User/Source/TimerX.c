/*
����˵��:  	
            TimerX ��ʱ���� --- STM32F107VCT 
						Timer5 ����һ��Ķ�ʱ��ͬʱ��ΪUSARTx��ͨ�ų�ʱ����Ĵ���
						Timer2 ����USBͨ�ŵľ�ȷ��ʱ
ע�����						
						

������:     Masterjay   
����ʱ��:   2014-04-21 
�޸�ʱ��:   2014-04-21
*/
//========================================
//ͷ�ļ�
#include "main.h"

//========================================
//��������
struct TIM5Result Timer5;
volatile union FlagTimer flagTIM5;

//========================================
//��������
void TIM5_Init(void);   		//Timer5��ʱ����ʼ��
void TIM5_TimeCount(void);	//TIM5ʱ�䴦�����




//========================================
//��ģ�麯��



/***********************************************************************
�������ƣ�void TIM5_Init(void)
��    �ܣ�Timer5��ʱ����ʼ��
���������
���������
��дʱ�䣺2013.11.19
�� д �ˣ�
ע    �⣺
***********************************************************************/
void TIM5_Init(void)
{
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;       //���嶨ʱ���ṹ��

		NVIC_InitTypeDef NVIC_InitStructure;



		/* TIM5 clock enable */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	 /* ---------------------------------------------------------------
		TIMxCLK = 72 MHz, Prescaler = 720, T=100kHz // 0.01ms  * 100 = 1ms
		--------------------------------------------------------------- */      
		/* Time base configuration */
		//��������Զ�װ�صļ���ֵ�����ڼ����Ǵ�0��ʼ�ģ�����10000�κ�Ϊ9999
		TIM_TimeBaseStructure.TIM_Period = (100 - 1);
		// �������Ԥ��Ƶϵ����������Ϊ0ʱ��ʾ����Ƶ����Ҫ��1
//      TIM_TimeBaseStructure.TIM_Prescaler = (7200 - 1);
		TIM_TimeBaseStructure.TIM_Prescaler = (7200-6480- 1);	
		// �߼�Ӧ�ñ��β��漰�������ڶ�ʱ��ʱ��(CK_INT)Ƶ���������˲���(ETR,TIx)
		// ʹ�õĲ���Ƶ��֮��ķ�Ƶ����
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //���˲��������йأ����Ƶ�޹�
		//���ϼ���
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		//��ʼ����ʱ��5
		TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
		/* Clear TIM5 update pending flag[���TIM5����жϱ�־] */
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
		/* TIM IT enable */ //������ж�
		TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
		/* TIM5 enable counter */
		TIM_Cmd(TIM5, ENABLE);  //������ʹ�ܣ���ʼ����
		
		
		

		/* Set the Vector Table base address at 0x08000000 */
		NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0000);

		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);			//�������ȼ� 0-15   ��Ӧ���ȼ� 0

		/* Enable the TIM5 gloabal Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;							//�趨ͨ��
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 15;	//�������ȼ�����  0��1
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					//��Ӧ���ȼ�����
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure); 			
}

/***********************************************************************
�������ƣ�void TIM5_TimeCount(void)
��    �ܣ�TIM5ʱ�䴦�����
�����������
�����������
��дʱ�䣺2014.04.11
�� д �ˣ�masterjay
ע    �⣺
***********************************************************************/
void TIM5_TimeCount(void)
{
	Timer5.msecond++;
	Timer5.ms_Record++;
	
	if(flagTIM5.Bits.T1_5sec_Flag)
	{
		Timer5.T1_5secmsCount++;
		if(Timer5.T1_5secmsCount>=1500)
		{
			Timer5.T1_5secmsCount=0;
			flagTIM5.Bits.T1_5sec_Flag=FALSE;		
		}	
	}
	
//	RdData.collecttime_s=RdData.collecttime_s+0.001;
	
// 	//IO�ڲ�������
// 	PULSEGeneration(Timer5.msecond%2);
	
	//���ڽ��������ʱ
	if(flagCOM1.Bits.OverTime_Flag)//���������ʱ	
	{
		
		if(Rec_COM1.TimeOut<OVERFLOW_TIME)
		{
			Rec_COM1.TimeOut++;										//���������ʱ
		}
		else
		{
			Rec_COM1.Count=0;											//���ڽ�������				
			Rec_COM1.TimeOut=0;										//���������ʱ
			flagCOM1.Bits.OverTime_Flag=FALSE;				//���������ʱ					
			
		}			
	}	
	if(flagCOM2.Bits.OverTime_Flag)//���������ʱ	
	{
		
		if(Rec_COM2.TimeOut<OVERFLOW_TIME)
		{
			Rec_COM2.TimeOut++;										//���������ʱ
		}
		else
		{
			Rec_COM2.Count=0;											//���ڽ�������				
			Rec_COM2.TimeOut=0;										//���������ʱ
			flagCOM2.Bits.OverTime_Flag=FALSE;				//���������ʱ					
			
		}			
	}
	
	if(Timer5.msecond%10==0)									//10ms�ж�һ��
	{
		flagUDisk.Bits.SaveTime_10ms=TRUE;	
		if(ControllerInfo.ScanTimeMode%2==1)		//GearScanT10ms = 1
		{
			flagctrl.Bits.ScanTimeFlag=TRUE;			
		}
		flagTIM5.Bits.T10msec_Flag=TRUE;
	}	
	if(Timer5.msecond%100==0)									//100ms�ж�һ��
	{
		if(ControllerInfo.ScanTimeMode%2==0)		//GearScanT100ms = 2
		{
			flagctrl.Bits.ScanTimeFlag=TRUE;			
		}		
		flagTIM5.Bits.T100msec_Flag=TRUE;

	}
	if(Timer5.msecond%100==0)									//100ms�ж�һ��
	{
		flagUDisk.Bits.SaveTime_100ms=TRUE;		
	}
	
	//���涨ʱ��ʱ
	if(Timer5.msecond>=1000)
	{
		//********************************************************************************
		//���岶׽��ʱ����
		if(TIM1FreqCap[0].IsUsedFlag==1)
		{
			if(TIM1FreqCap[0].NOINT_s<Fre_NOINTMAXTIME)
			{
				TIM1FreqCap[0].NOINT_s++;
			}
			else
			{
				TIM1FreqCap[0].Freq=0;
			}			
		}
		if(TIM1FreqCap[1].IsUsedFlag==1)
		{
			if(TIM1FreqCap[1].NOINT_s<Fre_NOINTMAXTIME)
			{
				TIM1FreqCap[1].NOINT_s++;
			}
			else
			{
				TIM1FreqCap[1].Freq=0;				
			}			
		}
		if(TIM1FreqCap[2].IsUsedFlag==1)
		{
			if(TIM1FreqCap[2].NOINT_s<Fre_NOINTMAXTIME)
			{
				TIM1FreqCap[2].NOINT_s++;
			}
			else
			{
				TIM1FreqCap[2].Freq=0;				
			}			
		}		
		if(TIM1FreqCap[3].IsUsedFlag==1)
		{
			if(TIM1FreqCap[3].NOINT_s<Fre_NOINTMAXTIME)
			{
				TIM1FreqCap[3].NOINT_s++;
			}
			else
			{
				TIM1FreqCap[3].Freq=0;				
			}			
		}		
		
		if(TIM4FreqCap[0].IsUsedFlag==1)
		{
			if(TIM4FreqCap[0].NOINT_s<Fre_NOINTMAXTIME)
			{
				TIM4FreqCap[0].NOINT_s++;
			}
			else
			{
				TIM4FreqCap[0].Freq=0;
			}			
		}
		if(TIM4FreqCap[1].IsUsedFlag==1)
		{
			if(TIM4FreqCap[1].NOINT_s<Fre_NOINTMAXTIME)
			{
				TIM4FreqCap[1].NOINT_s++;
			}
			else
			{
				TIM4FreqCap[1].Freq=0;				
			}			
		}
		if(TIM4FreqCap[2].IsUsedFlag==1)
		{
			if(TIM4FreqCap[2].NOINT_s<Fre_NOINTMAXTIME)
			{
				TIM4FreqCap[2].NOINT_s++;
			}
			else
			{
				TIM4FreqCap[2].Freq=0;				
			}			
		}		
		if(TIM4FreqCap[3].IsUsedFlag==1)
		{
			if(TIM4FreqCap[3].NOINT_s<Fre_NOINTMAXTIME)
			{
				TIM4FreqCap[3].NOINT_s++;
			}
			else
			{
				TIM4FreqCap[3].Freq=0;				
			}			
		}			
		
		//���岶׽��ʱ����			
		//********************************************************************************
	
			Timer5.msecond=0;			
			Timer5.second++;
		  if(XG.Startup_DelayTime>0)
			{
				XG.Startup_DelayTime=XG.Startup_DelayTime-1;
			}		
			flagTIM5.Bits.T1sec_Flag=TRUE;		
			flagTIM5.Bits.Freq_1sec_Flag=TRUE;
			flagUDisk.Bits.SaveTime_1s=TRUE;
			if(Timer5.second>=60)
			{
						Timer5.second=0;
						flagTIM5.Bits.T1min_Flag=TRUE;
						Timer5.minute++;
						if(Timer5.minute>=60)
						{
									Timer5.minute=0;
						}
			}
	}	
}


 //========================================
//��������:void TIM5_IRQHandler(void)
//��������: TIM5�жϴ������
//��ڲ���:    
//���ڲ���:      
//========================================
/**
  * @brief  This function handles TIM5 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM5_IRQHandler(void)
{
      if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
      {
            TIM_ClearITPendingBit(TIM5, TIM_IT_Update);     //���жϱ�־
            TIM5_TimeCount();																//TIM5ʱ�䴦�����      
      }
}
