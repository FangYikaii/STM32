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
struct TIM5Result 
{
		uint32_t ms_Record; 
    uint16_t msecond;
		uint16_t T1_5secmsCount;
	
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
};
extern struct TIM5Result Timer5;


union FlagTimer  
{ 
      uint8_t flagBits; 
      struct       
      { 
						uint8_t			T100msec_Flag 		:	1;				
						uint8_t			T1sec_Flag  			:	1;
						uint8_t			T1min_Flag				:	1;
						uint8_t 		T10msec_Flag			:	1;
						uint8_t 		T1_5sec_Flag			:	1;				
						uint8_t 		Freq_1sec_Flag		:	1;
						uint8_t 		T1msec_Flag	    	:	1;				
						uint8_t 		Bit7		:	1;		
 						
      } Bits; 
}; 
extern volatile union FlagTimer flagTIM5;

//========================================
//�����������
extern void TIM5_Init(void);   			//Timer5��ʱ����ʼ��
extern void TIM5_TimeCount(void);		//TIM5ʱ�䴦�����




//========================================
//<--Ԥ�������-->
#endif



