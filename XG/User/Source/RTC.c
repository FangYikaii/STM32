/*
����˵��:  	
            RTC ��������ʾ���� --- STM32F107VCT 
						
ע�����						
						1����Ƭ��·�ľ�����������δ�ҵ��������ڡ�
						
�˿�ʹ��:		��Doc�ļ����ڵ�·���˵��
������:     Masterjay   
����ʱ��:   2014-04-21 
�޸�ʱ��:   2014-04-21
*/

//========================================
//ͷ�ļ�
#include "main.h"

//========================================
//��������
struct DATE NowTime;
const uint8_t mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};		//ƽ���·�������
const uint8_t table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; 							//������ϵ����

volatile union FlagRTCA flagRTC;
//========================================
//��������
void RTC_Configuration(void);				//���RTC������
void RTCInit_Configuration(void);		//���RTC�ĳ�ʼ������
uint8_t RTC_SetTime(uint16_t year,uint8_t mon,uint8_t day,uint8_t hour,uint8_t min,uint8_t sec);		//����ʱ�ӳ���
uint8_t RTC_GetTime(void);																														//��ȡʱ�ӳ���
uint8_t RTC_GetWeek(uint16_t year,uint8_t month,uint8_t day);																	//��ȡ���ڼ�����,ֻ����1901--2099


//========================================
//��ģ�麯��


/***********************************************************************
�������ƣ�void RTC_Configuration(void)
��    �ܣ����RTC������
���������
���������
��дʱ�䣺2014.4.14
�� д �ˣ�
ע    �⣺
***********************************************************************/
void RTC_Configuration(void)
{
  /* Enable PWR and BKP clocks */
  /* PWRʱ�ӣ���Դ���ƣ���BKPʱ�ӣ�RTC�󱸼Ĵ�����ʹ�� */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

  /* Allow access to BKP Domain */
  /*ʹ��RTC�ͺ󱸼Ĵ������� */
  PWR_BackupAccessCmd(ENABLE);

  /* Reset Backup Domain */
  /* ������BKP��ȫ���Ĵ�������Ϊȱʡֵ */
  BKP_DeInit();

  /* Enable LSE */
  /* ʹ��LSE���ⲿ32.768KHz���پ���*/
  RCC_LSEConfig(RCC_LSE_ON);
  
  /* Wait till LSE is ready */
  /* �ȴ��ⲿ�������ȶ���� */
  while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {
		;
	}

  /* Select LSE as RTC Clock Source */
  /*ʹ���ⲿ32.768KHz������ΪRTCʱ�� */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

  /* Enable RTC Clock */
  /* ʹ�� RTC ��ʱ�ӹ��� */
  RCC_RTCCLKCmd(ENABLE);

  /* Wait for RTC registers synchronization */
  /*�ȴ�RTC�Ĵ���ͬ�� */
  RTC_WaitForSynchro();

  /* Wait until last write operation on RTC registers has finished */
  /* �ȴ���һ�ζ�RTC�Ĵ�����д������� */
  RTC_WaitForLastTask();

  /* Enable the RTC Second */
  /* ʹ��RTC�����ж� */
  RTC_ITConfig(RTC_IT_SEC, ENABLE);

  /* Wait until last write operation on RTC registers has finished */
  /* �ȴ���һ�ζ�RTC�Ĵ�����д������� */
  RTC_WaitForLastTask();
  
  /* Set RTC prescaler: set RTC period to 1sec */
  /* 32.768KHz����Ԥ��Ƶֵ��32767,����Ծ���Ҫ��ܸ߿����޸Ĵ˷�Ƶֵ��У׼���� */
  RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */

  /* Wait until last write operation on RTC registers has finished */
  /* �ȴ���һ�ζ�RTC�Ĵ�����д������� */
  RTC_WaitForLastTask();
}

/***********************************************************************
�������ƣ�void RTCInit_Configuration(void)
��    �ܣ����RTC�ĳ�ʼ������
���������
���������
��дʱ�䣺2014.4.15
�� д �ˣ�
ע    �⣺
***********************************************************************/
void RTCInit_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
  /* ����if...else.... if�ж�ϵͳʱ���Ƿ��Ѿ����ã��ж�RTC�󱸼Ĵ���1��ֵ
     �Ƿ�Ϊ����д���0XA5A5��������ǣ���˵��RTC�ǵ�һ���ϵ磬��Ҫ����RTC��
     ��ʾ�û�ͨ�����ڸ���ϵͳʱ�䣬��ʵ��ʱ��ת��ΪRTC����ֵд��RTC�Ĵ���,
     ���޸ĺ󱸼Ĵ���1��ֵΪ0XA5A5��
     else��ʾ�Ѿ�������ϵͳʱ�䣬��ӡ�ϴ�ϵͳ��λ��ԭ�򣬲�ʹ��RTC���ж�
  */
  if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)		
  {
		RTC_Configuration();													//RTC Configuration		
		RTC_SetTime(2014,04,15,21,46,0);							//����ʱ�ӳ���
    BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);			//�޸ĺ󱸼Ĵ���1��ֵΪ0XA5A5
  }
  else
  {
    /* Check if the Power On Reset flag is set */
    if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)				//Power On Reset occurred
    {
      ;
    }
    /* Check if the Pin Reset flag is set */
    else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)		//External Reset occurred
    {
      ;
    }
    RTC_WaitForSynchro();

    /* Enable the RTC Second */
    RTC_ITConfig(RTC_IT_SEC, ENABLE);
    
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
  }

  /* Enable PWR and BKP clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
      
  /* Allow access to BKP Domain */
  PWR_BackupAccessCmd(ENABLE);

  /* Disable the Tamper Pin */
  BKP_TamperPinCmd(DISABLE); /* To output RTCCLK/64 on Tamper pin, the tamper
                                 functionality must be disabled */

  /* Enable RTC Clock Output on Tamper Pin */
  BKP_RTCOutputConfig(BKP_RTCOutputSource_CalibClock);

  /* Clear reset flags */
  RCC_ClearFlag();	
	
	RTC_ClearITPendingBit(RTC_IT_SEC);

	/* Wait until last write operation on RTC registers has finished */
	/* �ȴ���һ�ζ�RTC�Ĵ�����д������� */
	RTC_WaitForLastTask();	


	/* Set the Vector Table base address at 0x08000000 */
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0000);

// 			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);			//�������ȼ� 0   		��Ӧ���ȼ� 0-15	
// 			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);			//�������ȼ� 0-1    ��Ӧ���ȼ� 0-7	
// 			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			//�������ȼ� 0-3    ��Ӧ���ȼ� 0-3	
// 			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);			//�������ȼ� 0-7    ��Ӧ���ȼ� 0-1	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);			//�������ȼ� 0-15   ��Ӧ���ȼ� 0

	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 14;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
	
}

/***********************************************************************
�������ƣ�uint8_t Is_Leap_Year(uint16_t year)
��    �ܣ��ж��Ƿ�Ϊ�������
������������
���������1--������  0--������
��дʱ�䣺2014.4.15
�� д �ˣ�
ע    �⣺
�·�				1 	2 	3 	4 	5 	6 	7 	8 	9 	10 	11 	12

�������� 		31 	29 	31 	30 	31 	30 	31 	31 	30 	31 	30 	31

���������� 	31 	28 	31 	30 	31 	30 	31 	31 	30 	31 	30 	31

***********************************************************************/
uint8_t Is_Leap_Year(uint16_t year)
{
	if(year%4==0) 				//�ܷ�4����
	{
		if(year%100==0)			//�ܷ�100����
		{
			if(year%400==0)		//�ܷ�400����
			{
				return 1;				//������				
			}
			else 
			{
				return 0;				
			}
		}
		else 
		{
			return 1;					//������			
		}
	}
	else 
	{
		return 0;		
	}

}
/***********************************************************************
�������ƣ�uint8_t RTC_SetTime(uint16_t year,uint8_t mon,uint8_t day,uint8_t hour,uint8_t min,uint8_t sec)
��    �ܣ�����ʱ�ӳ���
������������
���������1--������  0--������
��дʱ�䣺2014.4.15
�� д �ˣ�
ע    �⣺
�·�				1 	2 	3 	4 	5 	6 	7 	8 	9 	10 	11 	12

�������� 		31 	29 	31 	30 	31 	30 	31 	31 	30 	31 	30 	31

���������� 	31 	28 	31 	30 	31 	30 	31 	31 	30 	31 	30 	31

***********************************************************************/
uint8_t RTC_SetTime(uint16_t year,uint8_t mon,uint8_t day,uint8_t hour,uint8_t min,uint8_t sec)
{
	uint16_t t;
	uint32_t seccount=0;
	if(year<2000||year>2099)		//year��ΧΪ1970-2099,����������Ч��ΧΪ2000-2099
	{
		return 1;		
	}
	for(t=1970;t<year;t++)			//��������ݵ��������
	{
		if(Is_Leap_Year(t))				//�ж��Ƿ�Ϊ����
		{
			seccount+=31622400;			//��������
		}
		else 
		{
			seccount+=31536000;			//����������		
		}
	}
	mon-=1;
	for(t=0;t<mon;t++)					//��ǰ���·ݵ��������
	{
		seccount+=(uint32_t)mon_table[t]*86400;	//�·��������
		if(Is_Leap_Year(year)&&t==1)					//����2�·ݶ�1������
		{
			seccount+=86400;			
		}
	}
	seccount+=(uint32_t)(day-1)*86400;			//ǰ�������������
	seccount+=(uint32_t)hour*3600;					//ǰ��Сʱ�������
	seccount+=(uint32_t)min*60; 						//ǰ������������
	seccount+=sec;											//ǰ�������������

	//����ʱ��
/* 
	RCC->APB1ENR|=1<<28;								//ʹ�ܵ�Դʱ��
	RCC->APB1ENR|=1<<27;								//ʹ�ܱ���ʱ��
	PWR->CR|=1<<8; 											//ȡ��������д����
*/	
	PWR_BackupAccessCmd(ENABLE);
	/* Wait until last write operation on RTC registers has finished */
  /* �ȴ���һ�ζ�RTC�Ĵ�����д������� */
  RTC_WaitForLastTask();
  
  /* Change the current time */
  /* ��ʱ��ת��ΪRTC����ֵд��RTC�Ĵ��� */
  RTC_SetCounter(seccount);
  
  /* Wait until last write operation on RTC registers has finished */
  /* �ȴ���һ�ζ�RTC�Ĵ�����д������� */
  RTC_WaitForLastTask();	
	
	
	
	return 0;
}

/***********************************************************************
�������ƣ�uint8_t RTC_GetTime(void)
��    �ܣ���ȡʱ�ӳ���
�����������
���������0--��ȡ�ɹ�������ֵ--��ȡʧ��
��дʱ�䣺2014.4.15
�� д �ˣ�
ע    �⣺
�·�				1 	2 	3 	4 	5 	6 	7 	8 	9 	10 	11 	12

�������� 		31 	29 	31 	30 	31 	30 	31 	31 	30 	31 	30 	31

���������� 	31 	28 	31 	30 	31 	30 	31 	31 	30 	31 	30 	31

***********************************************************************/
uint8_t RTC_GetTime(void)
{
	static uint16_t daycnt=0;
	uint32_t timecount=0;
	uint32_t temp=0;
	uint16_t temp1=0;
	timecount=RTC_GetCounter();						//��ȡ����
	temp=timecount/86400; 								//�õ�����
	if(daycnt!=temp)											//��������1
	{
		daycnt=temp;
		temp1=1970; 												//��1970�꿪ʼ
		while(temp>=365)										//��������365
		{
			if(Is_Leap_Year(temp1))						//�ж��Ƿ�Ϊ����
			{
				if(temp>=366)										//��������366
				{
					temp-=366;													
				}
				else
				{
					temp1++;
					break;
				}
			}
			else
			{
				temp-=365; 											//ƽ�꣬��ȥ1������			
			}
			temp1++;
		}
		NowTime.year=temp1;									//�õ����
		temp1=0;
		while(temp>=28)											//����1����
		{
			if(Is_Leap_Year(NowTime.year)&&temp1==1)	//�жϵ����ǲ��������Ҹպ�Ϊ2�·�
			{
				if(temp>=29)
				{
					temp-=29;	
				}
				else 
				{
					break;
				}
			}
			else
			{
				if(temp>=mon_table[temp1])
				{
					temp-=mon_table[temp1];
				}
				else
				{
					break;
				}
			}
			temp1++;
		}
		NowTime.month=temp1+1;					//�õ��·�
		NowTime.day=temp+1; 						//�õ�����
	}
	temp=timecount%86400; 						//�õ�1�������
	NowTime.hour=temp/3600; 					//�õ�Сʱ
	NowTime.min=(temp%3600)/60; 			//�õ�����
	NowTime.sec=(temp%3600)%60; 			//�õ�����
	NowTime.week=RTC_GetWeek(NowTime.year,NowTime.month,NowTime.day);		//�õ���
	return 0;

}
/***********************************************************************
�������ƣ�uint8_t RTC_GetWeek(uint16_t year,uint8_t month,uint8_t day)
��    �ܣ���ȡ���ڼ�����,ֻ����1901--2099
����������꣬�£���
���������0--��ȡ�ɹ�������ֵ--��ȡʧ��
��дʱ�䣺2014.4.15
�� д �ˣ�
ע    �⣺
�·�				1 	2 	3 	4 	5 	6 	7 	8 	9 	10 	11 	12

�������� 		31 	29 	31 	30 	31 	30 	31 	31 	30 	31 	30 	31

���������� 	31 	28 	31 	30 	31 	30 	31 	31 	30 	31 	30 	31

***********************************************************************/
uint8_t RTC_GetWeek(uint16_t year,uint8_t month,uint8_t day)
{
	uint16_t temp2;
	uint8_t yearH,yearL;
	yearH=year/100; 
	yearL=year%100;
	if (yearH>19)						//���Ϊ21���ͣ���ݼ�100
	{
		yearL+=100;		
	}
	temp2=yearL+yearL/4;		//����������ֻ��1900��֮��
	temp2=temp2%7;
	temp2=temp2+day+table_week[month-1];
	if (yearL%4==0&&month<3)
	{
		temp2--;
	}
	return(temp2%7);
}


/***********************************************************************
�������ƣ�void RTC_IRQHandler(void)
��    �ܣ�RTC�жϴ������
���������
���������
��дʱ�䣺2014.04.14
�� д �ˣ�
ע    ��  
***********************************************************************/
void RTC_IRQHandler(void)
{
  /*  �ж�RTC�Ƿ��������жϣ�Ҳ�п�����������������ж�) */
  if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
  {
    /* Clear the RTC Second interrupt */
    /* ������жϱ�־ */
    RTC_ClearITPendingBit(RTC_IT_SEC);

    /* Wait until last write operation on RTC registers has finished */
    /* �ȴ���һ�ζ�RTC�Ĵ�����д������� */
    RTC_WaitForLastTask();
    flagRTC.Bits.T1sec_Flag=TRUE;				//RTC���ж���λ
		
  }
}
