//========================================
//<--Ԥ���崦����ֹ�ظ�����-->
#ifndef _RTC_H
#define _RTC_H

//========================================
//ͷ�ļ�



//========================================
//�궨��







//========================================
//�˿ڶ���



//========================================
//�����������
struct DATE
{
	uint16_t msec;
	uint8_t hour;
	uint8_t min;
	uint8_t sec;
	uint16_t 	year;
	uint8_t month;
	uint8_t day;
	uint8_t week;
	
	char cord[5];
	char string[24];				//�������鳤��ʱ��ע���޸Ķ�Ӧ����ճ���	
	
};
extern struct DATE NowTime;

union FlagRTCA  
{ 
      uint8_t flagBits; 
      struct       
      { 
						uint8_t			T1sec_Flag				:	1;					
						uint8_t			Bit1							:	1;	
						uint8_t 		Bit2							:	1;				
						uint8_t 		Bit3							:	1;
						uint8_t 		Bit4							:	1;				
						uint8_t 		Bit5							:	1;
						uint8_t 		Bit6							:	1;				
						uint8_t 		Bit7							:	1;		
 						
      } Bits; 
}; 
extern volatile union FlagRTCA flagRTC;

//========================================
//�����������
extern void RTCInit_Configuration(void);		//���RTC�ĳ�ʼ������
extern uint8_t RTC_SetTime(uint16_t year,uint8_t mon,uint8_t day,uint8_t hour,uint8_t min,uint8_t sec);		//����ʱ�ӳ���
extern uint8_t RTC_GetTime(void);																														//��ȡʱ�ӳ���





//========================================
//<--Ԥ�������-->
#endif



