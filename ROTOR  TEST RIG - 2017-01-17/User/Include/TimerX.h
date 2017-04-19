//========================================
//<--Ԥ���崦����ֹ�ظ�����-->
#ifndef _TimerX_H
#define _TimerX_H

//========================================
//ͷ�ļ�



//========================================
//�궨��




//========================================
//�˿ڶ���




//========================================
//�����������

//�ṹ��:TIMER�������
struct TIM5Result 
{
		uint32_t ms_Record;       //����
    uint16_t msecond;         //����
		uint16_t T1_5secmsCount;  //1.5��
	
    uint8_t second;          //��
    uint8_t minute;          //����
    uint8_t hour;            //ʱ��
};
extern struct TIM5Result Timer5;

//�����壺TIMER������־λ
union FlagTimer  
{ 
      uint8_t flagBits; 
      struct       
      { 
						uint8_t			T100msec_Flag 		:	1;			 //100ms         ��־λ
						uint8_t			T1sec_Flag  			:	1;       //1s            ��־λ
						uint8_t			T1min_Flag				:	1;			 //1min          ��־λ
						uint8_t 		T10msec_Flag			:	1;       //10ms          ��־λ
						uint8_t 		T1_5sec_Flag			:	1;			 //1.5s	         ��־λ
						uint8_t 		Freq_1sec_Flag		:	1;       //���岶׽����  ��־λ
						uint8_t 		Bit6	          	:	1;				
						uint8_t 		Bit7	           	:	1;		
 						
      } Bits; 
}; 
extern volatile union FlagTimer flagTIM5;

//========================================
//�����������
extern void TIM5_Init(void);   			//Timer5��ʱ����ʼ��
extern void TIM5_TimeCount(void);		//TIM5ʱ�䴦�����
extern void TIM5_IRQHandler(void); //TIM5�жϳ���



//========================================
//<--Ԥ�������-->
#endif



