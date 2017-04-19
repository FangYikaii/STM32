//========================================
//<--Ԥ���崦����ֹ�ظ�����-->
#ifndef _USB_UDisk_H
#define _USB_UDisk_H

//========================================
//ͷ�ļ�

#include "usbh_usr.h"
#include "usb_bsp.h" 



//========================================
//�궨��
#define 			ERROR						0									//���󷵻���Ϣֵ
#define				NORMAL					1									//����������Ϣ

#define				CONTENTSIZE			64								//TXT�ĵ�˵�����ݳ���
#define				RecordTMSIZE		21								//����TXT�ĵ�ʱ�䳤��
#define				DATAINFOSIZE		15								//TXT������Ϣ����
#define				DATASTARADDR		100								//���ݼ�¼����ʼ��ַ
#define				ROWSIZE					128								//����ÿ�г���           1024/N

#define				MS_Eable				1
#define				MS_UnEable			0
//========================================
//�˿ڶ���




//========================================
//�����������
// struct DATE
// {
// 	uint8_t hour;
// 	uint8_t min;
// 	uint8_t sec;
// 	uint16_t 	year;
// 	uint8_t month;
// 	uint8_t day;
// 	uint8_t week;
// 	uint16_t  msec;
// 	
// 	char cord[5];
// 	char string[24];				//�������鳤��ʱ��ע���޸Ķ�Ӧ����ճ���	
// 	
// };
// extern struct DATE NowTime;

struct TXT
{
	char Name[50];					//TXT�ĵ�����
	char Content[64];				//TXT�ĵ���¼����˵��
	uint16_t RowLength;					//ÿ�г���
	uint32_t RecordCount;			//��¼���ݸ���
	uint32_t RecordAddr;				//��¼���ݵ�ַ
	
};
extern struct TXT TXTInfo[];

struct RecordDATA				
{
	char 	TimeString[23];									//��¼ʱ����Ϣ-- 14-05-09 17:15:00 1000(��-��-�� ʱ:��:�� ����)	
	uint8_t	GearInfo;											//��λ��Ϣ--2���ַ�
	float AnalogChannelData[8];						//ģ��ͨ���ɼ�ֵ--��ѹֵ(���ſ��ȡ�ת���͸�ѹ����̧��ѹ����)
	uint16_t	DigitalChannelData[4];			//ģ��ͨ���ɼ�ֵ--����ֵ(����ת�١�����ת�١����ٵ�)
	float collecttime_s;									//����ʱ��--s.
	uint16_t recordcount;
	
};
extern struct RecordDATA RdData;
extern FIL fsrc_FIL[];       					  /* file objects */
extern uint8_t USBInit_STATUS;						//U�̳�ʼ����־

union FlagUSB  
{ 
      uint8_t flagBits; 
      struct       
      { 
						uint8_t			SaveTime_1s				:	1;					
						uint8_t			SaveTime_100ms		:	1;	
						uint8_t			SaveTime_10ms			:	1;			
						uint8_t 		Bit3							:	1;
						uint8_t 		Bit4							:	1;				
						uint8_t 		Bit5							:	1;
						uint8_t 		Bit6							:	1;				
						uint8_t 		Bit7							:	1;		
 						
      } Bits; 
}; 
extern volatile union FlagUSB flagUDisk;




//========================================
//�����������
extern void USB_UDisk_Init(void);																//U�̳�ʼ������
extern void UserProcess_UDisk(void);														//U�̶�д�û�������
extern uint8_t OpenTXT_UDisk(char *str,FIL *fsrcN);								//U�̴�TXT�ļ�����
extern uint8_t CloseTXT_UDisk(FIL *fsrcN);												//U�̹ر�TXT�ļ�����
extern uint8_t CreatTXT_UDisk(char *str,FIL *fsrcN);							//U�̴���TXT�ļ�����
extern uint8_t DelTXT_UDisk(char *str,FIL *fsrcN);								//U��ɾ���ļ�����
extern uint8_t WriteRdDataToTxt_UDisk(char *str, FIL *fsrcN);			//U��д��ɼ����ݵ�TXT�ĵ���



//========================================
//<--Ԥ�������-->
#endif



