/*
����˵��:  	
            U�̶�д���� --- STM32F107VCT 
						
ע�����	1������U�̼���TIM2���жϼ���������ó���ߣ��������ְβ�U���޷���ʾ				
						2���ַ�����д��ʱ�򣬽�����ʶ��Ϊ'\o'/ NULL�����κ��ַ���д��Ͷ�ȡ��ʱ���������ַ�
						�ͻ��Զ��������ʶ�ȡ�ַ���ʱע�ⳤ�ȡ�
						3���ַ����е�strlen()������ַ�����Ҳ����'\o'������sizeof()ֻ���ں��������ľֲ�
						��Χ�ڲ��ܰ���������ĳ��ȶ���������Ƕ�׵�������'\o'ʱҲ��Ϊ�ַ����ȼ��������
						4��ע��ƫ�Ƶ�ַ��λ�ã��κεĶ�д��������ñ��˵�ַ��f_lseek(&fsrc, XX);
						5��ע���ļ��Ĵ���رգ��ر��ǵ��������ļ��Ķ�дʱ������Ƕ����Ŀǰ�Ķ�д״̬�£��������ļ�û��
						6��ע��U�̶�дʱһ����Ҫ������д������Ӧ�÷���д�������1024�������д����
						7��ʹ��Printf���ܣ����ڹ�����������Ҫ��ѡ USE MICROLIB
�˿�ʹ��:		��Doc�ļ�����˵��
������:     FangYIkaii
����ʱ��:   2017-01-21 
�޸�ʱ��:   2014-01-21
*/
//**********************************************************************************************************
/*
������ɾ���ļ�����˵����
FA_READ									ָ�������ʶ���
FA_WRITE								ָ��д���ʶ���
FA_OPEN_EXISTING				���ļ�������ļ������ڣ����ʧ��
FA_OPEN_ALWAYS					����ļ����ڣ���򿪣����򴴽�һ��TXT�ļ�
FA_CREATE_NEW						����һ��TXT�ļ�������ļ��Ѵ��ڣ��򴴽�ʧ��
FA_CREATE_ALWAYS				����һ��TXT�ļ�������ļ��Ѵ��ڣ����������ضϲ�����

�ļ���д����ֵ˵����
	FR_OK=0							 			(0) Succeeded 
	FR_DISK_ERR,			 				(1) A hard error occured in the low level disk I/O layer 
	FR_INT_ERR,				 				(2) Assertion failed 
	FR_NOT_READY,			 				(3) The physical drive cannot work 
	FR_NO_FILE,				 				(4) Could not find the file 
	FR_NO_PATH,				 				(5) Could not find the path 
	FR_INVALID_NAME,		 			(6) The path name format is invalid 
	FR_DENIED,				 				(7) Acces denied due to prohibited access or directory full 
	FR_EXIST,				 					(8) Acces denied due to prohibited access 
	FR_INVALID_OBJECT,		 		(9) The file/directory object is invalid 
	FR_WRITE_PROTECTED,		 		(10) The physical drive is write protected 
	FR_INVALID_DRIVE,		 			(11) The logical drive number is invalid 
	FR_NOT_ENABLED,			 			(12) The volume has no work area 
	FR_NO_FILESYSTEM,		 			(13) There is no valid FAT volume on the physical drive
	FR_MKFS_ABORTED,		 			(14) The f_mkfs() aborted due to any parameter error 
	FR_TIMEOUT,				 				(15) Could not get a grant to access the volume within defined period 
	FR_LOCKED,								(16) The operation is rejected according to the file shareing policy 
	FR_NOT_ENOUGH_CORE,		 		(17) LFN working buffer could not be allocated 
	FR_TOO_MANY_OPEN_FILES	 	(18) Number of open files > _FS_SHARE 


*/
//**********************************************************************************************************

//========================================
//ͷ�ļ�
#include "main.h"

//========================================
//��������
FIL fsrc_FIL[5];    //File Object Structure
struct TXT TXTInfo[5];  

// struct DATE NowTime;
struct RecordDATA RdData;
uint8_t USBInit_STATUS=0;						//U�̳�ʼ����־
volatile union FlagUSB flagUDisk;

//========================================
//��������
void USB_UDisk_Init(void);																							//U�̳�ʼ������
void UserProcess_UDisk(void);																						//U�̶�д�û�������

uint8_t OpenTXT_UDisk(char *str,FIL *fsrcN);															//U�̴�TXT�ļ�����
uint8_t CloseTXT_UDisk(FIL *fsrcN);																				//U�̹ر�TXT�ļ�����
uint8_t CreatTXT_UDisk(char *str,FIL *fsrcN);															//U�̴���TXT�ļ�����
uint8_t DelTXT_UDisk(char *str,FIL *fsrcN);																//U��ɾ���ļ�����

uint8_t WriteRdDataToTxt_UDisk(char *str, FIL *fsrcN);										//U��д��ɼ����ݵ�TXT�ĵ���

uint8_t ReadDataRecordNum_UDisk(char *str);																//U�̶�ȡTXT�ĵ������ݼ�¼����
uint8_t WriteDataRecordNum_UDisk(char *str);															//U��д��TXT�ĵ������ݼ�¼����															

void ClearStr(char *str,uint16_t len);							//�ַ�����ճ���
void DateToStr(uint8_t ms_en);										//ʱ��ת�����ַ���
void DateToFileName(void);											//ʱ��ת�����ļ���
char *itoa(int num, char *str, int radix);			//����תΪ�ַ���

void die(FRESULT res);													//�ļ�����ִ�н������

//========================================
//��ģ�麯��



/***********************************************************************
�������ƣ�void USB_UDisk_Init(void)
��    �ܣ�U�̳�ʼ������
�����������
�����������
��дʱ�䣺2014.04.29
�� д �ˣ�masterjay
ע    �⣺
***********************************************************************/
void USB_UDisk_Init(void)
{
		USBH_Init(&USB_OTG_FS_dev, &MSC_cb , &USR_Callbacks);
}

/***********************************************************************
�������ƣ�void UserProcess_UDisk(void)
��    �ܣ�U�̶�д�û�������
�����������
�����������
��дʱ�䣺2014.04.29
�� д �ˣ�masterjay
ע    �⣺
***********************************************************************/
void UserProcess_UDisk(void)
{
	char i;
	char printstr[100];
	char nstr[20];
	USBH_Process();																		//USB_OTG�ڲ�ʵʱ������
	if(USBH_USR_ApplicationState == USH_USR_FS_NULL)	//U��������ʼ����ϣ��û���������
	{
		if(USBInit_STATUS==0)			//U�̳�ʼ����ɺ��ִ��һ�β���
		{
			USBInit_STATUS=1;				//U�̳�ʼ����־
			res = f_open(&fsrc_FIL[0], "2015.txt", FA_CREATE_ALWAYS | FA_WRITE);						//����TXT�ļ�	
			die(res);
			if ( res != FR_OK)
			{ 
				printf("\r\n�ļ��򿪻򴴽�ʧ��");
			}	
		}	
		else if(USBInit_STATUS==1)
		{
				if(flagUDisk.Bits.SaveTime_100ms)
				{
					flagUDisk.Bits.SaveTime_100ms=FALSE;						//ע������	
					ClearStr(printstr,sizeof(printstr));	
					
					ClearStr(nstr,sizeof(nstr));
					sprintf(nstr,"%9.3f",RdData.collecttime_s);					
					strcat(printstr,nstr);
					strcat(printstr," ");	
					
					ClearStr(nstr,sizeof(nstr));
					sprintf(nstr,"%9.3f",RdData.collecttime_s);					
					strcat(printstr,nstr);
					strcat(printstr," ");	

					ClearStr(nstr,sizeof(nstr));
					sprintf(nstr,"%9.3f",RdData.collecttime_s);					
					strcat(printstr,nstr);
					strcat(printstr," ");						
					
					for(i=0;i<6;i++)
					{
						ClearStr(nstr,sizeof(nstr));
						sprintf(nstr,"%9.3f",ADCRes.ADCResValue[i]);					
						strcat(printstr,nstr);
						strcat(printstr," ");			
					}				
					strcat(printstr,"  \r\n");	
					i=strlen(printstr);
					res = f_write(&fsrc_FIL[0], printstr, strlen(printstr) , &br);  //д��������Ϣ
					die(res);
					if ( res != FR_OK)
					{
						printf("���ݴ洢ʧ�ܣ�\r\n");
					}
					else
					{
						printf("���ݴ洢�ɹ���\r\n");
					}
					RdData.recordcount++;
// 					f_sync(&fsrc_FIL[0]);
					printf("RdData.recordcount= %d \r\n",RdData.recordcount);
					if(RdData.recordcount>=1000)
					{
						RdData.recordcount=0;
						f_close(&fsrc_FIL[0]);
						printf("�洢������");
						USBInit_STATUS=3;	
					}
						
				}	
			
		}
		

		
	}
	
	
	
	
	
	// 	if(USBH_USR_ApplicationState == USH_USR_FS_NULL)	//U��������ʼ����ϣ��û���������
// 	{
// 		if(USBInit_STATUS==0)			//U�̳�ʼ����ɺ��ִ��һ�β���
// 		{
// 			USBInit_STATUS=1;				//U�̳�ʼ����־

// 			NowTime.year=2014;
// 			NowTime.month=15;
// 			NowTime.day=14;
// 			NowTime.hour=23;
// 			NowTime.min=40;
// 			NowTime.sec=15;
// 			NowTime.msec=1000;	
// 			RdData.AnalogChannelData[0]=12121.02;
// 			RdData.AnalogChannelData[1]=12122.02;		
// 			RdData.AnalogChannelData[2]=12123.02;
// 			RdData.AnalogChannelData[3]=12124.02;
// 			RdData.AnalogChannelData[4]=12125.02;
// 			RdData.AnalogChannelData[5]=12126.02;			
// 			RdData.AnalogChannelData[6]=12127.02;
// 			RdData.AnalogChannelData[7]=12128.02;
// 			RdData.DigitalChannelData[0]=100000;
// 			RdData.DigitalChannelData[1]=200000;			
// 			RdData.DigitalChannelData[2]=300000;
// 			RdData.DigitalChannelData[3]=142353;
// 			RdData.GearInfo=2;	
// 			DateToFileName();																					//ʱ��ת��Ϊ�ļ���
// 			ClearStr(TXTInfo[0].Name,sizeof(TXTInfo[0].Name));
// 			strcat(TXTInfo[0].Name,NowTime.string);										//�ļ����ƣ�ʱ����
// 			CreatTXT_UDisk(TXTInfo[0].Name,&fsrc_FIL[0]);		
// 			OpenTXT_UDisk(TXTInfo[0].Name,&fsrc_FIL[0]);	
// 		}	
// 		else
// 		{
// 			if(flagUDisk.Bits.SaveTime_100ms)
// 			{
// 				flagUDisk.Bits.SaveTime_100ms=FALSE;						//ע������	
// 			
// 				printf("%d\r\n",Timer5.msecond);
// 				WriteRdDataToTxt_UDisk(TXTInfo[0].Name,&fsrc_FIL[0]);						
// 				printf("RecordAddr=%d\r\n",TXTInfo[0].RecordAddr);
// 				printf("RecordCount=%d\r\n",TXTInfo[0].RecordCount);			
// 				printf("%d\r\n",Timer5.msecond);
// 			}			
// 		}						
// 		

// 	}
// 	else		//U�̳�ʼ��ʧ�ܣ����Ѿ��Ͽ�����
// 	{
// 		;
// 	}


}

/***********************************************************************
�������ƣ�uint8_t OpenTXT_UDisk(char *str,FIL *fsrcN)
��    �ܣ�U�̴�TXT�ļ�����
����������ļ�����
���������1  �ɹ�    0  ����
��дʱ�䣺2014.05.15
�� д �ˣ�masterjay
ע    �⣺�ļ���Ҫʹ���������֣������޷������ɹ������ʹ�ã�������ض�
***********************************************************************/
uint8_t OpenTXT_UDisk(char *str,FIL *fsrcN)
{
	uint8_t status=NORMAL;
	char printstr[100];
	char FileName[30];
	if(USBH_MSC_Param.MSWriteProtect == DISK_WRITE_PROTECTED)						//���u��д����
	{		
			ClearStr(printstr,sizeof(printstr));
			printf("��u����д������");
			printf("\r\n");
			strcat(printstr,"�޷�������");
			strcat(printstr,str);
			strcat(printstr,"���ļ�");
			strcat(printstr,"\r\n");		
			printf(printstr);		
			status=ERROR;																									//����������
	}	
	else
	{
		ClearStr(FileName,sizeof(FileName));
		strcat(FileName,"0:/");
		strcat(FileName,str);	
		strcat(FileName,".TXT");		
		res = f_open(fsrcN , FileName , FA_OPEN_EXISTING | FA_READ | FA_WRITE);
		die(res);
		if(res!=FR_OK)
		{
			status=ERROR;
		}
	}
	return status;
}

/***********************************************************************
�������ƣ�uint8_t CloseTXT_UDisk(FIL *fsrcN)
��    �ܣ�U�̹ر�TXT�ļ�����
����������ļ�����
���������1  �ɹ�    0  ����
��дʱ�䣺2014.05.15
�� д �ˣ�masterjay
ע    �⣺�ļ���Ҫʹ���������֣������޷������ɹ������ʹ�ã�������ض�
***********************************************************************/
uint8_t CloseTXT_UDisk(FIL *fsrcN)
{
	uint8_t status=NORMAL;	
	res = f_close(fsrcN);	
	die(res);
	if(res!=FR_OK)
	{
		status=ERROR;
	}
	return status;
}

/***********************************************************************
�������ƣ�uint8_t CreatTXT_UDisk(char *str,FIL *fsrcN)
��    �ܣ�U�̴���TXT�ļ�����
����������ļ����� �ļ�����
���������1  �ɹ�    0  ����
��дʱ�䣺2014.05.15
�� д �ˣ�masterjay
ע    �⣺�ļ���Ҫʹ���������֣������޷������ɹ������ʹ�ã�������ض�
***********************************************************************/
uint8_t CreatTXT_UDisk(char *str,FIL *fsrcN)
{
	uint8_t status=NORMAL;
	char printstr[100];	
	char FileName[30];
	if(USBH_MSC_Param.MSWriteProtect == DISK_WRITE_PROTECTED)						//���u��д����
	{		
			ClearStr(printstr,sizeof(printstr));
			printf("��u����д������");
			printf("\r\n");
			strcat(printstr,"�޷�������");
			strcat(printstr,str);
			strcat(printstr,"���ļ�");
			strcat(printstr,"\r\n");		
			printf(printstr);		
			status=ERROR;																									//����������
	}	
	else
	{
		ClearStr(FileName,sizeof(FileName));
		strcat(FileName,"0:/");
		strcat(FileName,str);	
		strcat(FileName,".TXT");			
		res = f_open(fsrcN , FileName , FA_CREATE_ALWAYS);						//����TXT�ļ�	
		die(res);
		if ( res != FR_OK)
		{ 
			status=ERROR;
		}	
		f_close(fsrcN);	
	}
	return status;
}

/***********************************************************************
�������ƣ�uint8_t DelTXT_UDisk(char *str,FIL *fsrcN)
��    �ܣ�U��ɾ���ļ�����
����������ļ�����
���������1  �ɹ�       0  ����
��дʱ�䣺2014.05.15
�� д �ˣ�masterjay
ע    �⣺�ļ���Ҫʹ���������֣������޷������ɹ������ʹ�ã�������ض�
***********************************************************************/
uint8_t DelTXT_UDisk(char *str,FIL *fsrcN)
{
	uint8_t status=NORMAL;
	char printstr[100];
	char FileName[30];
	if(USBH_MSC_Param.MSWriteProtect == DISK_WRITE_PROTECTED)//���u��д����
	{		
			ClearStr(printstr,sizeof(printstr));
			printf("��u����д������");
			printf("\r\n");
			strcat(printstr,"�޷�ɾ����");
			strcat(printstr,str);
			strcat(printstr,"���ļ�");
			printf("\r\n");		
			status=ERROR;															//ɾ��������
	}	
	else
	{	
		ClearStr(FileName,sizeof(FileName));			
		strcat(FileName,"0:/");
		strcat(FileName,str);	
		strcat(FileName,".TXT");
		res = f_unlink(FileName);										//ɾ��TXT�ļ�	
		die(res);
		if ( res != FR_OK )
		{ 
			status=ERROR;															//ɾ��������
		}
		f_close(fsrcN); 		
	}
	return status;
}


/***********************************************************************
�������ƣ�uint8_t WriteRdDataToTxt_UDisk(char *str, FIL *fsrcN)
��    �ܣ�U��д��ɼ����ݵ�TXT�ĵ���
����������ļ���,�ֱ�
���������1  �ɹ�    0  ����
��дʱ�䣺2014.05.15
�� д �ˣ�masterjay
ע    �⣺
***********************************************************************/
uint8_t WriteRdDataToTxt_UDisk(char *str, FIL *fsrcN)
{	
	uint8_t status=NORMAL;
	uint8_t i;	
	char printstr[200];
	char nstr[50];
//**********************************************************************
//��ʽ��д����Ϣ	-- 128���ַ�
	DateToStr(MS_Eable);											//������ת�����ַ���
	ClearStr(printstr,sizeof(printstr));		
	strcat(printstr,RdData.TimeString);				//��¼ʱ����Ϣ-- 05-09 17:15:00:1000(��-��-�� ʱ:��:��:����)	
	strcat(printstr," ");		
	
	sprintf(nstr,"%2d",RdData.GearInfo);			//��λ��Ϣ--2���ַ�(��λֵ: -2 -1 1 2 3)
	strcat(printstr,nstr);
	strcat(printstr," ");		
	
	for(i=0;i<8;i++)
	{
		if(i<6)
		{		
			sprintf(nstr,"%8.2f",ADCRes.ADCResValue[i]);
		}
		else
		{
			sprintf(nstr,"%8.2f",RdData.AnalogChannelData[i]);		//ģ��ͨ���ɼ�ֵ--��ѹֵ(���ſ��ȡ�ת���͸�ѹ����̧��ѹ����)			
		}
		
	
		strcat(printstr,nstr);
		strcat(printstr," ");			
	}
	
	for(i=0;i<4;i++)
	{
		sprintf(nstr,"%6d",RdData.DigitalChannelData[i]);			//ģ��ͨ���ɼ�ֵ--����ֵ(����ת�١�����ת�١����ٵ�)	
		strcat(printstr,nstr);
		strcat(printstr," ");						
	}	
	strcat(printstr,"\r\n");

// 	sprintf(nstr,"%10d",Timer5.ms_Record);
// 	strcat(printstr,nstr);
// 	strcat(printstr," ");		
// 	for(i=0;i<6;i++)
// 	{
// 		sprintf(nstr,"%8.3f",ADCRes.ADCResValue[i]);		//ģ��ͨ���ɼ�ֵ--��ѹֵ(���ſ��ȡ�ת���͸�ѹ����̧��ѹ����)	
// 		strcat(printstr,nstr);
// 		strcat(printstr," ");			
// 	}	
// 	strcat(printstr,"\r\n");
	
//**********************************************************************
//��ʼд������
//	OpenTXT_UDisk(str,fsrcN);	

// 	TXTInfo[0].RecordAddr=(TXTInfo[0].RecordCount*ROWSIZE);  //д����֮ʱ��ע����1024��Ϊ�����Σ����ܿ�����д����
// 	res = f_lseek(fsrcN,TXTInfo[0].RecordAddr);
// 	die(res);	
	
// 	res = f_lseek(fsrcN,f_size(fsrcN));
// 	die(res);	
	res = f_write(fsrcN, printstr, strlen(printstr) , &br);  //д��������Ϣ
	die(res);
	if ( res == FR_OK)
	{
		TXTInfo[0].RecordCount++;			
	}
	else
	{
		status=ERROR;
	}
	f_sync(fsrcN);																					//�رն�д�������ر��ļ����γ��ٲ�����ܼ�����д
//	f_close(fsrcN);																						//�رն�д�ҹر��ļ����γ����ٲ���ɼ�����д
	return status;
}

/***********************************************************************
�������ƣ�uint8_t ReadDataRecordNum_UDisk(char *str)
��    �ܣ�U�̶�ȡTXT�ĵ������ݼ�¼����
����������ļ�����
���������1   ��ȡ�ɹ�  0   ��ȡʧ��
��дʱ�䣺2014.05.08
�� д �ˣ�masterjay
ע    �⣺
***********************************************************************/
uint8_t ReadDataRecordNum_UDisk(char *str)
{	
	uint32_t recordnum;
	uint8_t status=NORMAL;
	uint8_t i;	
	char FileName[20];
	char printstr[100];	

	ClearStr(FileName,sizeof(FileName));
	strcat(FileName,"0:/");
	strcat(FileName,str);	
	strcat(FileName,".TXT");		
	res = f_open( &fsrc , FileName , FA_OPEN_EXISTING | FA_READ);
	die(res);
	if ( res == FR_OK)
	{ 
		ClearStr(printstr,sizeof(printstr));
		f_lseek(&fsrc, (CONTENTSIZE+RecordTMSIZE));
		res = f_read( &fsrc, printstr, DATAINFOSIZE, &br );	
		die(res);
		recordnum=0x00;
		for(i=0;i<4;i++)				//���������еĳ���
		{

			if(printstr[i]>=0x30)
			{
				recordnum*=16;				
				if(printstr[i]<=0x39)
				{
					recordnum+=(printstr[i]%16);
				}
				else if(printstr[i]>=0x41)
				{
					recordnum+=(printstr[i]%16+9);				
				}				
			}			
		}
		TXTInfo[0].RowLength=recordnum;			//ÿ���ܳ���
		
		recordnum=0;		
		for(i=0;i<8;i++)			//���㵱ǰ�洢�ĸ���
		{

			if(printstr[i+5]>=0x30)
			{
				recordnum*=16;				
				if(printstr[i+5]<=0x39)
				{
					recordnum+=(printstr[i+5]%16);
				}
				else if(printstr[i+5]>=0x41)
				{
					recordnum+=(printstr[i+5]%16+9);				
				}				
			}			
		}
		TXTInfo[0].RecordCount=recordnum;			//�����ܸ���
//		printf(printstr);		
	}	
	else
	{
		status=ERROR;
	}
	f_close(&fsrc);	
	return status;
}

/***********************************************************************
�������ƣ�uint8_t WriteDataRecordNum_UDisk(char *str)
��    �ܣ�U��д��TXT�ĵ������ݼ�¼����
����������ļ�����
���������1   д��ɹ�  0   д��ʧ��
��дʱ�䣺2014.05.08
�� д �ˣ�masterjay
ע    �⣺
***********************************************************************/
uint8_t WriteDataRecordNum_UDisk(char *str)
{	
	uint8_t status=NORMAL;
	char printstr[100];	
	char nstr[20];
	char FileName[20];
	
	ClearStr(FileName,sizeof(FileName));							//��ȡ�ļ����ַ���
	strcat(FileName,"0:/");
	strcat(FileName,str);	
	strcat(FileName,".TXT");		
	res = f_open( &fsrc , FileName , FA_OPEN_EXISTING | FA_WRITE);
	die(res);
	if ( res == FR_OK)
	{ 
			ClearStr(printstr,sizeof(printstr));
			TXTInfo[0].RowLength=ROWSIZE;											//���ݼ�¼��ÿ�г���
			sprintf(nstr,"%4x",TXTInfo[0].RowLength); 
			strcat(printstr,nstr);
			strcat(printstr," ");														
			sprintf(nstr,"%8x",TXTInfo[0].RecordCount); 				//���ݼ�¼��������
			strcat(printstr,nstr);
			strcat(printstr,"\r\n");
			f_lseek(&fsrc,(CONTENTSIZE+RecordTMSIZE));		 	//ƫ��85���ֽ�			
			res = f_write(&fsrc, printstr, strlen(printstr), &br); 							//******д��������Ϣ--15���ַ�
			die(res);
	}	
	else
	{
		status=ERROR;
	}
	f_close(&fsrc);	
	return status;
}



/***********************************************************************
�������ƣ�uint8_t ReadTxtToData_UDisk(char *str)
��    �ܣ�U�̶�ȡTXT�ĵ�������
����������ļ�����
���������1   ��ȡ����    0   ��ȡ�ɹ�
��дʱ�䣺2014.04.29
�� д �ˣ�masterjay
ע    �⣺
***********************************************************************/
uint8_t ReadTxtToData_UDisk(char *str)
{	
	uint8_t Error=FALSE;
	char printstr[100];
	char aa[100];

	strcat(printstr,"0:/");
	strcat(printstr,str);
	strcat(printstr,".TXT");	
	printf("�ļ��洢λ�ã�");		

	res = f_open( &fsrc , printstr , FA_OPEN_EXISTING | FA_READ);	//��ȡTXT�ļ�	
	ClearStr(printstr,100);
	strcat(printstr,str);		
	strcat(printstr,".TXT");			
	if ( res == FR_OK )
	{ 
//**********************************************************************************************
//���ݶ�ȡ�������

	res = f_open(&fsrc, "0:/2014.TXT", FA_OPEN_EXISTING | FA_READ);
	if( res == FR_OK )		
	{
		
		res = f_read( &fsrc, aa, 25 , &br );							
		f_lseek(&fsrc, 25);
		res = f_read( &fsrc, aa, 25 , &br );
		
		f_close(&fsrc);
	}								
							
							
	
		

//**********************************************************************************************		
		strcat(printstr," ��ȡ�ɹ���");				
		printf(printstr);
		printf("\r\n");     
	}
	else		//TXT�ļ���ȡʧ��
	{  
		strcat(printstr," �����ڣ�");				
		printf(printstr);
		printf("\r\n");	
		Error=TRUE;					
	}	
	/*close file */
	f_close(&fsrc); 				

	return Error;
}


/***********************************************************************
�������ƣ�uint8_t CreatFile_UDisk(char *str)
��    �ܣ�U�̴����ļ��г���
����������ļ�����
���������1   ��������    0   �����ɹ�
��дʱ�䣺2014.04.29
�� д �ˣ�masterjay
ע    �⣺�ļ���Ҫʹ���������֣������޷������ɹ������ʹ�ã�������ض�
					���������⣬����ʹ��
***********************************************************************/
uint8_t CreatFile_UDisk(char *str)
{
	uint8_t Error=FALSE;
	char printstr[100];
	ClearStr(printstr,100);
	if(USBH_MSC_Param.MSWriteProtect == DISK_WRITE_PROTECTED)//���u��д����
	{		
			printf("��u����д������");
			printf("\r\n");
			strcat(printstr,"�޷�������");
			strcat(printstr,str);
			strcat(printstr,"���ļ�");
			printf("\r\n");		
			Error=TRUE;																//����������
	}	
	else
	{
		strcat(printstr,"0:/");
		strcat(printstr,str);	
		printf("�����ļ���");		
		printf(printstr);
		printf("\r\n");			
		res = f_mkdir(str);
		ClearStr(printstr,100);
		strcat(printstr,str);
		die(res);			
// 		if ( res == FR_OK )
// 		{ 
// 			strcat(printstr," �����ɹ���");				
// 			printf(printstr);
// 			printf("\r\n");     
// 		}
// 		else if ( res == FR_EXIST )									//�ļ��Ѿ�����
// 		{  
// 			strcat(printstr," �ļ��Ѵ��ڡ�");				
// 			printf(printstr);
// 			printf("\r\n");		
// 		}	
// 		else
// 		{
// 			printf("����δ֪���󣡣�");
// 			printf("\r\n");				
// 		}		
	}
	return Error;	
}

/***********************************************************************
�������ƣ�void ClearStr(char *str,uint16_t len)
��    �ܣ��ַ�����ճ���
�����������
�����������
��дʱ�䣺2014.04.29
�� д �ˣ�masterjay
ע    �⣺
***********************************************************************/
void ClearStr(char *str,uint16_t len)
{
	uint8_t i;
	for(i=0;i<len;i++)
	{
		str[i]='\0';
	}
}


/***********************************************************************
�������ƣ�void DateToFileName(void)
��    �ܣ�ʱ��ת�����ļ���  �8���ַ�
�����������
�����������
��дʱ�䣺2014.05.15
�� д �ˣ�masterjay
ע    �⣺
***********************************************************************/
void DateToFileName(void)
{
	ClearStr(NowTime.string,sizeof(NowTime.string));
	
// 	sprintf(NowTime.cord,"%4d",NowTime.year); 
// 	strcat(NowTime.string,NowTime.cord);
// 	sprintf(NowTime.cord,"%2d",NowTime.month); 
// 	strcat(NowTime.string,NowTime.cord);
// 	sprintf(NowTime.cord,"%2d",NowTime.day); 
// 	strcat(NowTime.string,NowTime.cord);	
	sprintf(NowTime.cord,"%2d",NowTime.hour); 	
	strcat(NowTime.string,NowTime.cord);	
	sprintf(NowTime.cord,"%2d",NowTime.min); 
	strcat(NowTime.string,NowTime.cord);
	sprintf(NowTime.cord,"%2d",NowTime.sec); 
	strcat(NowTime.string,NowTime.cord);	

}

/***********************************************************************
�������ƣ�void DateToStr(uint8_t ms_en)
��    �ܣ�ʱ��ת�����ַ���
���������ms�Ƿ�ʹ��
�����������
��дʱ�䣺2014.05.04
�� д �ˣ�masterjay
ע    �⣺
***********************************************************************/
void DateToStr(uint8_t ms_en)
{
	uint8_t i;
	ClearStr(NowTime.string,sizeof(NowTime.string));
	
	sprintf(NowTime.cord,"%4d",NowTime.year); 
	strcat(NowTime.string,NowTime.cord);

	strcat(NowTime.string,"-");		

	sprintf(NowTime.cord,"%2d",NowTime.month); 
	strcat(NowTime.string,NowTime.cord);

	strcat(NowTime.string,"-");		

	sprintf(NowTime.cord,"%2d",NowTime.day); 
	strcat(NowTime.string,NowTime.cord);	

	strcat(NowTime.string," ");			

	sprintf(NowTime.cord,"%2d",NowTime.hour); 	
	strcat(NowTime.string,NowTime.cord);	

	strcat(NowTime.string,":");	

	sprintf(NowTime.cord,"%2d",NowTime.min); 
	strcat(NowTime.string,NowTime.cord);	
	
	strcat(NowTime.string,":");		
	
	sprintf(NowTime.cord,"%2d",NowTime.sec); 
	strcat(NowTime.string,NowTime.cord);	

	if(ms_en)
	{
		strcat(NowTime.string,":");				
		sprintf(NowTime.cord,"%4d",NowTime.msec); 
		strcat(NowTime.string,NowTime.cord);	
		for(i=0;i<23;i++)															//��¼ʱ��
		{
			RdData.TimeString[i]=NowTime.string[i+2];		
		}		
	}
}

/***********************************************************************
�������ƣ�char *itoa(int num, char *str, int radix)
��    �ܣ����͵��ַ���ת������
�����������ת���������ַ��洢�Ĵ�������ֵ��ʽ
����������ַ��洢�Ĵ�����ַ
��дʱ�䣺2014.04.29
�� д �ˣ�masterjay
ע    �⣺
***********************************************************************/
char *itoa(int num, char *str, int radix)
{
	const char table[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *ptr = str;
	char *start;
	uint8_t negative = FALSE;
	if(num == 0)						//num=0 
	{ 
		*ptr++='0';
		*ptr='\0'; 						// don`t forget the end of the string is '\0'!!!!!!!!!
		return str;
	}
	if(num<0)								//if num is negative ,the add '-'and change num to positive 
	{ 
		 *ptr++='-';
		 num*=-1;
		 negative = TRUE;
	}
	while(num)
	{
		*ptr++ = table[num%radix];
		num/=radix;
	}
	*ptr = '\0';							
	
	// in the below, we have to converse the string
	start = (negative ? str+1 : str); //now start points the head of the string
	ptr--; //now prt points the end of the string

	while(start<ptr)
	{
		char temp = *start; 
		*start = *ptr;
		*ptr = temp;
		start++;
		ptr--;
	} 
	return str;	
}
/***********************************************************************
�������ƣ�void die(FRESULT res)
��    �ܣ��ļ�����ִ�н������
�����������ת���������ַ��洢�Ĵ�������ֵ��ʽ
����������ַ��洢�Ĵ�����ַ
��дʱ�䣺2014.04.29
�� д �ˣ�masterjay
ע    �⣺
***********************************************************************/
void die(FRESULT res)
{
    switch(res)
		{
				case FR_OK:        //The function succeeded. 
				{
	//					printf("\r\nThe function succeeded!\r\n");
							break;
				}
				case FR_NOT_READY://The disk drive cannot work due to no medium in the drive or any other reason
				{
						printf("\r\nThe disk drive cannot work due to no medium in the drive or any other reason!\r\n");
								break;
				}
				case FR_NO_FILE://Could not find the file.
				{
						printf("\r\nCould not find the file!\r\n");
								break;
				}
				case FR_NO_PATH://Could not find the path
				{
						printf("\r\nCould not find the path!\r\n");
								break;
				}
				case FR_INVALID_NAME://The path name is invalid
				{
						printf("\r\nThe path name is invalid!\r\n");
								break;
				}
				case FR_INVALID_DRIVE://The drive number is invalid
				{
						printf("\r\nThe drive number is invalid!\r\n");
								break;
				}
				case FR_DENIED://The directory cannot be created due to directory table or disk is full. 
				{
						printf("\r\nThe directory cannot be created due to directory table or disk is full!\r\n");
								break;
				}
				case FR_EXIST://A file or directory that has same name is already existing
				{
						printf("\r\nA file or directory that has same name is already existing!\r\n");
								break;
				}
//                case FR_RW_ERROR://The function failed due to a disk error or an internal error
/*
				case FR_RW_ERROR://The function failed due to a disk error or an internal error
				{
						printp("\r\nThe function failed due to a disk error or an internal error!\r\n");
								break;
				}
*/
				case FR_WRITE_PROTECTED://The medium is write protected
				{
						printf("\r\nThe medium is write protected!\r\n");
								break;
				}
				case FR_NOT_ENABLED://The logical drive has no work area
				{
						printf("\r\nThe logical drive has no work area!\r\n");
								break;
				}
				case FR_NO_FILESYSTEM://There is no valid FAT partition on the disk
				{
						printf("\r\nThere is no valid FAT partition on the disk!\r\n");
								break;
				}
				case FR_INVALID_OBJECT://The file object is invalid
				{
						printf("\r\nThe file object is invalid!\r\n");
								break;
				}

				//The function aborted before start in format due to a reason as follows. 
				//The disk size is too small. 
				//Invalid parameter was given to any parameter. 
				//Not allowable cluster size for this drive. This can occure when number of clusters becomes around 0xFF7 and 0xFFF7. 
				case FR_MKFS_ABORTED://
				{
						printf("\r\nThe function aborted before start in format!\r\n");
								break;
				}
				
				default:
				{
						printf("\r\nerror!\r\n");
								break;
				}        
		}
		return;
}
