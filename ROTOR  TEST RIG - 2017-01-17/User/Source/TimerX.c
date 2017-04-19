/*
����˵��:  	
            TimerX ��ʱ���� --- STM32F107VCT 
						Timer5 ����һ��Ķ�ʱ��ͬʱ��ΪUSARTx��ͨ�ų�ʱ����Ĵ���
						Timer2 ����USBͨ�ŵľ�ȷ��ʱ
ע�����						
						

������:     FangYikaii   
����ʱ��:   2017-01-16 
�޸�ʱ��:   2017-01-16
*/
//========================================
//��ʱ����7��������2watchdog timers���������Ź������ڿ��Ź���
//2������ʱ����TIM6��TIM7[��������ܣ��ۼ�ʱ������������Ԥ��ֵ�������жϻ򴥷�DMA][���ϼ�����
//4ͨ�ö�ʱ����TIM2��TIM3��TIM4��TIM5[������������Ƶ�ʡ�����������PWM����ȳ���][���ϣ����¼�����
//1�߼���ʱ����TIM1[����������������ӿڡ�ɲ������][�������¼���]

//ʱ������Systick=72MHz��APB1Ԥ��Ƶ���ķ�Ƶϵ������Ϊ2����PCK1�պ����ֵ36MHz
//Ԥ��Ƶ:TIMx_PSC=0����Ƶ  TIMx_PSC=1 2��Ƶ
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
��дʱ�䣺2017.01.16
�� д �ˣ�FangYIkaii
ע    �⣺1.TIM5ʹ��
					2.���ڡ�Ԥ��Ƶ������ʼ��
					3.������ʽ
					4.��ʼ����ʱ��
					5.�������ж�
					6.������ж�
					7.������ʹ��
				  ÿ�ν����жϵ�ʱ�䣺
					((1+TIM_Prescaler)/72M)*(1+TIM_Period)=(1+719)/72000000*(1+100-1)=0.001S
***********************************************************************/
void TIM5_Init(void)
{
		//���嶨ʱ���ṹ��
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;       	
	
		//TIM5ʹ��
		/* TIM5 clock enable */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	 /* ---------------------------------------------------------------
		TIMxCLK = 72 MHz, Prescaler = 720, T=100kHz // 0.01ms  * 100 = 1ms
	  T��72000000/720=1/100000
		���ڣ�T=1/100000*100=0.001  1MS
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
}

/***********************************************************************
�������ƣ�void TIM5_TimeCount(void)
��    �ܣ�TIM5ʱ�䴦�����
�����������
�����������
��дʱ�䣺2017.01.17
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/
void TIM5_TimeCount(void)
{
	//ms++
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
	
	//U�̶�д����
	RdData.collecttime_s=RdData.collecttime_s+0.001;
	
 	//IO�ڲ�������
 	PULSEGeneration(Timer5.msecond%2);
	
	//���ڽ��������ʱ
	if(flagCOM1.Bits.OverTime_Flag)//���������ʱ	
	{		
		//�����������<��������
		if(Rec_COM1.TimeOut<OVERFLOW_TIME)
		{
			Rec_COM1.TimeOut++;										//���������ʱ
		}
		//�����������>��������
		else
		{
			Rec_COM1.Count=0;											//���ڽ�������				
			Rec_COM1.TimeOut=0;										//���������ʱ
			flagCOM1.Bits.OverTime_Flag=FALSE;				//���������ʱ��־λ	
		}			
	}	
	
	//���������ʱ	
	if(flagCOM2.Bits.OverTime_Flag)//���������ʱ	
	{
		//�����������<��������
		if(Rec_COM2.TimeOut<OVERFLOW_TIME)
		{
			Rec_COM2.TimeOut++;										//���������ʱ
		}
		//�����������>��������
		else
		{
			Rec_COM2.Count=0;											//���ڽ�������				
			Rec_COM2.TimeOut=0;										//���������ʱ
			flagCOM2.Bits.OverTime_Flag=FALSE;				//���������ʱ��־λ				
		}			
	}
	
	//10ms�ж�һ��
	if(Timer5.msecond%10==0)
	{
		//USB
		//10ms�洢��־λ--True
		flagUDisk.Bits.SaveTime_10ms=TRUE;
		//IO Ctrl
		if(ControllerInfo.ScanTimeMode%2==1)		//GearScanT10ms = 1
		{
			//IO Ctrlɨ���־λ--ģʽ1��
			flagctrl.Bits.ScanTimeFlag=TRUE;			
		}
		//TIM5 10ms��־λ
		flagTIM5.Bits.T10msec_Flag=TRUE;
	}	
	//100ms�ж�һ��
	if(Timer5.msecond%100==0)									
	{
		//USB
		//100ms�洢��־λ--True
		flagUDisk.Bits.SaveTime_100ms=TRUE;		
		//IO Ctrl
		if(ControllerInfo.ScanTimeMode%2==0)		//GearScanT100ms = 2
		{
			//IO Ctrlɨ���־λ--ģʽ2��
			flagctrl.Bits.ScanTimeFlag=TRUE;			
		}
		//TIM5 100ms��־λ
		flagTIM5.Bits.T100msec_Flag=TRUE;
	}
	
	//���涨ʱ��ʱ--1s
	if(Timer5.msecond>=1000)
	{
		//********************************************************************************
		//���岶׽��ʱ����
		//TIM1-ͨ��1
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
		
		//TIM1-ͨ��2
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
		
		//TIM1-ͨ��3
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
		
		//TIM1-ͨ��4
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
		
		//TIM4-ͨ��1
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
		
		//TIM4-ͨ��2
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
		
		//TIM4-ͨ��3
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

		//TIM4-ͨ��4
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
			//1��-��־λ
			flagTIM5.Bits.T1sec_Flag=TRUE;		
			//���岶���־λ
			flagTIM5.Bits.Freq_1sec_Flag=TRUE;
			//USB�洢1���־λ
			flagUDisk.Bits.SaveTime_1s=TRUE;
			
			if(Timer5.second>=60)
			{
						Timer5.second=0;
						//1min��־λ
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
//��дʱ�䣺2017.01.17
//�� д �ˣ�FangYikaii
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
