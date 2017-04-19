/*
����˵��:  	
            USB_OTG �û����� --- STM32F107VCT 
						
ע�����	1��ע��ܽŵĸ�������						
						
						
�˿�ʹ��:		��Doc�ļ�����˵��
������:     FangYikaii   
����ʱ��:   2014-04-21 
�޸�ʱ��:   2014-04-21
*/

//========================================
//ͷ�ļ�
#include "main.h"

#include "ff.h"
#include "usbh_msc_core.h"
#include "usbh_msc_scsi.h"
#include "usbh_msc_bot.h"

//========================================
//��������


uint8_t USBH_USR_ApplicationState = USH_USR_FS_INIT;
uint8_t temp[]                        = "          \n";
uint8_t buffer[1024]; 

UINT br;
FATFS fs;         /* Work area (file system object) for logical drive */
FIL fsrc;         /* file objects */
FRESULT res;


/*  Points to the DEVICE_PROP structure of current device */
/*  The purpose of this register is to speed up the execution */

USBH_Usr_cb_TypeDef USR_Callbacks =
{
  USBH_USR_Init,															//U��������ʼ
  USBH_USR_DeviceAttached,										//U��������ʾ
  USBH_USR_ResetDevice,												//U�̸�λ�������
  USBH_USR_DeviceDisconnected,								//U�̰γ���ʾ
  USBH_USR_OverCurrentDetected,								//
  USBH_USR_DeviceSpeedDetected,								//U���ٶȼ����ʾ
  USBH_USR_Device_DescAvailable,							//
  USBH_USR_DeviceAddressAssigned,							//
  USBH_USR_Configuration_DescAvailable,				//U���豸ID��ʾ
  USBH_USR_Manufacturer_String,								//
  USBH_USR_Product_String,										//
  USBH_USR_SerialNum_String,									//
  USBH_USR_EnumerationDone,										//
  USBH_USR_UserInput,													//
  USBH_USR_DeviceNotSupported,								//
  USBH_USR_UnrecoveredError										//U�̳�����ʾ

};

//========================================
//��ģ�麯��



/***********************************************************************
�������ƣ�void USBH_USR_Init(void)
��    �ܣ�U��������ʼ
�����������
�����������
��дʱ�䣺2014.04.27
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/
void USBH_USR_Init(void)
{
 	printf(">����u�̳�ʼ��\r\n");
}

/***********************************************************************
�������ƣ�void USBH_USR_DeviceAttached(void)
��    �ܣ�U��������ʾ
�����������
�����������
��дʱ�䣺2014.04.27
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/
void USBH_USR_DeviceAttached(void)
{
	USBInit_STATUS=0;				//U�̳�ʼ����־	
  printf("��⵽u�̣�");
  printf("\r\n");
}


/***********************************************************************
�������ƣ�void USBH_USR_UnrecoveredError (void)
��    �ܣ�U�̳�����ʾ
�����������
�����������
��дʱ�䣺2014.04.27
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/
void USBH_USR_UnrecoveredError (void)
{
 
  printf("���ɻָ�״̬����");
  printf("\r\n");
  
}


/***********************************************************************
�������ƣ�void USBH_USR_DeviceDisconnected (void)
��    �ܣ�U�̰γ���ʾ
�����������
�����������
��дʱ�䣺2014.04.27
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/
void USBH_USR_DeviceDisconnected (void)
{
 
 	printf("u���Ѱγ���\r\n");

}

/***********************************************************************
�������ƣ�void USBH_USR_ResetDevice(void)
��    �ܣ�U�̸�λ�������
�����������
�����������
��дʱ�䣺2014.04.27
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/
void USBH_USR_ResetDevice(void)
{
  /* callback for USB-Reset */
}


/***********************************************************************
�������ƣ�void USBH_USR_DeviceSpeedDetected(uint8_t DeviceSpeed)
��    �ܣ�U���ٶȼ����ʾ
�����������
�����������
��дʱ�䣺2014.04.27
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/

void USBH_USR_DeviceSpeedDetected(uint8_t DeviceSpeed)
{
  if(DeviceSpeed == HPRT0_PRTSPD_FULL_SPEED)
  {
		printf("usb�豸ȫ�١�");
		printf("\r\n");
  }
  else if(DeviceSpeed == HPRT0_PRTSPD_LOW_SPEED)
  {
		printf("usb�豸���١�");
		printf("\r\n");
  }
  else
  {
		printf("usb�豸����");
		printf("\r\n");
  }
}

/***********************************************************************
�������ƣ�void USBH_USR_Device_DescAvailable(void *DeviceDesc)
��    �ܣ�U���豸ID��ʾ
�����������
�����������
��дʱ�䣺2014.04.27
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/
void USBH_USR_Device_DescAvailable(void *DeviceDesc)
{
  uint8_t temp[50];    
  USBH_DevDesc_TypeDef *hs;
  hs = DeviceDesc;  
  
  
  sprintf((char *)temp , "VID          = %04Xh" , (uint32_t)(*hs).idVendor); 
  printf("VID          = %04Xh \r\n" , (uint32_t)(*hs).idVendor);  
  
  sprintf((char *)temp , "PID          = %04Xh" , (uint32_t)(*hs).idProduct); 
  printf("PID          = %04Xh \r\n" , (uint32_t)(*hs).idProduct);  

}

/***********************************************************************
�������ƣ�void USBH_USR_DeviceAddressAssigned(void)
��    �ܣ�
�����������
�����������
��дʱ�䣺2014.04.27
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/
void USBH_USR_DeviceAddressAssigned(void)
{
  
}


/***********************************************************************
�������ƣ�void USBH_USR_Configuration_DescAvailable(USBH_CfgDesc_TypeDef * cfgDesc,
                                          USBH_InterfaceDesc_TypeDef *itfDesc,
                                          USBH_EpDesc_TypeDef *epDesc)
��    �ܣ�
�����������
�����������
��дʱ�䣺2014.04.27
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/
void USBH_USR_Configuration_DescAvailable(USBH_CfgDesc_TypeDef * cfgDesc,
                                          USBH_InterfaceDesc_TypeDef *itfDesc,
                                          USBH_EpDesc_TypeDef *epDesc)
{
  USBH_InterfaceDesc_TypeDef *id;
  uint8_t temp[50];
  
  id = itfDesc;
  
  sprintf ((char *)temp, "�˵�� = %d" , (uint32_t)(*id).bNumEndpoints);
  printf("�˵�� = %d \r\n" , (uint32_t)(*id).bNumEndpoints);
  
  
  if((*id).bInterfaceClass  == 0x08)
  {
    
    printf("�����洢���豸");
		printf("\r\n");

  }
  else if((*id).bInterfaceClass  == 0x03)
  {
    
    printf("HID���豸");
		printf("\r\n");
  }    
}

/***********************************************************************
�������ƣ�void USBH_USR_Manufacturer_String(void *ManufacturerString)
��    �ܣ�
�����������
�����������
��дʱ�䣺2014.04.27
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/
void USBH_USR_Manufacturer_String(void *ManufacturerString)
{
  char temp[100];
  sprintf(temp, "���� : %s", (char *)ManufacturerString);
  printf("���� : %s \r\n", (char *)ManufacturerString);  
}

/***********************************************************************
�������ƣ�void USBH_USR_Product_String(void *ProductString)
��    �ܣ�
�����������
�����������
��дʱ�䣺2014.04.27
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/
void USBH_USR_Product_String(void *ProductString)
{
  char temp[100];
  sprintf((char *)temp, "Product : %s", (char *)ProductString);  
  printf("��Ʒ : %s \r\n", (char *)ProductString); 
}

/***********************************************************************
�������ƣ�USBH_USR_SerialNum_String(void *SerialNumString)
��    �ܣ�
�����������
�����������
��дʱ�䣺2014.04.27
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/
void USBH_USR_SerialNum_String(void *SerialNumString)
{
  uint8_t temp[100];
  sprintf((char *)temp, "���ں� : %s", (char *)SerialNumString);    
  printf("���ں� : %s \r\n", (char *)SerialNumString); 

} 



/***********************************************************************
�������ƣ�void USBH_USR_EnumerationDone(void)
��    �ܣ�
�����������
�����������
��дʱ�䣺2014.04.27
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/
void USBH_USR_EnumerationDone(void)
{
  
  /* Enumeration complete */
  printf("ö����ɡ�"); 
  printf("----------------------------------------"); 
  printf("\r\n");
  printf("\r\n");
  printf("\r\n");
} 


/***********************************************************************
�������ƣ�void USBH_USR_DeviceNotSupported(void)
��    �ܣ�
�����������
�����������
��дʱ�䣺2014.04.27
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/
void USBH_USR_DeviceNotSupported(void)
{
  
  if(MSC_Machine.maxLun > 0)
  {
		printf("> Contains more than one LUN! \r\n ");  

    /*Display the LUN in the connected device*/
    USBH_USR_HexToASCII((uint32_t)(MSC_Machine.maxLun));

		printf("LUN Available in the device:");
		printf("\r\n");  


    printf("-----------------------------------------");
		printf("\r\n");  


		printf( "%s" , temp );
		printf("\r\n");

    printf("-----------------------------------------");
		printf("\r\n");    
  }
  /* 2 seconds delay */
  USB_OTG_BSP_mDelay(2000);
  
}  


/***********************************************************************
�������ƣ�USBH_USR_Status USBH_USR_UserInput(void)
��    �ܣ�
�����������
�����������
��дʱ�䣺2014.04.27
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/
USBH_USR_Status USBH_USR_UserInput(void)
{
//   USBH_USR_Status usbh_usr_status;
  return USBH_USR_RESP_OK;
}  

/***********************************************************************
�������ƣ�void USBH_USR_OverCurrentDetected (void)
��    �ܣ�
�����������
�����������
��дʱ�䣺2014.04.27
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/
void USBH_USR_OverCurrentDetected (void)
{
  

  printf("u�̶�д\r\n");
  
  printf("ERR : OVERCURRENT DETECTED \r\n ");

  
    /* 2 seconds delay */
    USB_OTG_BSP_mDelay(2000);
}


/***********************************************************************
�������ƣ�int USBH_USR_MSC_Application(void)
��    �ܣ�U�̹���״̬������
�����������
�����������
��дʱ�䣺2014.04.27
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/
int USBH_USR_MSC_Application(void)
{
// 	uint i;
// 	ulong addr123=0;
	
  uint8_t read_txt_file_buff[512]; 
  char textFileBuffer[] = "��л��ʹ�ñ��ɼ��豸����\r\n";   
  FILINFO fno;
  DIR dir;
 /**********״̬��******************/
  switch(USBH_USR_ApplicationState)
  {
		case USH_USR_FS_INIT:  //�ļ���ʼ������ȡu�̴�С��
    
				/* Initialises the file system */
				f_mount(0,&fs);																//����U��
				// f_mount(0, NULL);													//ȡ������
		
				/*Display the size of the disk*/
				USBH_USR_HexToASCII((((USBH_MSC_Param.MSCapacity) * \
														 (USBH_MSC_Param.MSPageLength))/(1048576)));

				printf("��u�̵Ĵ�СΪ��MBytes����");	//"* Size of the disk in MBytes: "
				//printf("\r\n");

				printf("%s",temp);			//U�̴�С
				printf("\r\n");

				printf("-----------------------------------------");
				printf("\r\n");   
			 
				if(USBH_MSC_Param.MSWriteProtect == DISK_WRITE_PROTECTED) //���U��д����
				{
			
					printf("��u����д������");
					printf("\r\n");  
				
					printf("-----------------------------------------");
					printf("\r\n");  
				}
				USBH_USR_ApplicationState = USH_USR_FS_READLIST;
				break;
    
		case USH_USR_FS_READLIST:	//��ȡu�̵ĸ�Ŀ¼�ļ�����
    
					/*Reads the dir list*/
					res = f_opendir(&dir, "0:");
					if( res != FR_OK )
					{
						/*Could not open the selected directory*/
						return(-2);
					}
						

					printf("��u�̸�Ŀ¼�ļ��б����£�");
					printf("\r\n");  
					printf("\r\n");
					printf("\r\n");     
					
					/**************��u�̸�Ŀ¼�������Ʒ������ڣ�ע�ⲻ֧�ֳ��ļ���***************/
					while ((HCD_IsDeviceConnected(&USB_OTG_FS_dev)) && ( f_readdir(&dir, &fno) == FR_OK ) && fno.fname[0] != 0 )
					{       

						printf("%s",fno.fname);
						printf("\r\n");    
					}
					USBH_USR_ApplicationState = USH_USR_FS_WRITEFILE;
					break;
    
		case USH_USR_FS_WRITEFILE:		//��U�̴����ļ���д������
    
					/* Writes a text file, U������.TXT in the disk*/
				
					if(USBH_MSC_Param.MSWriteProtect == DISK_WRITE_PROTECTED)//���u��д����
					{		
							printf("��u����д������");
							printf("\r\n");

							printf("�޷�������˵��.TXT���ļ�");
							printf("\r\n");
						
							USBH_USR_ApplicationState = USH_USR_FS_READFILE;
							break;
					}				
					res = f_open( &fsrc , "0:/˵��.TXT" , FA_CREATE_NEW | FA_WRITE);	//������U������.TXT���ļ�	
//					res = f_open( &fsrc , "0:/˵��.TXT" , FA_OPEN_EXISTING | FA_WRITE);	//������U������.TXT���ļ�						
					
					if ( res == FR_OK )
					{ 
						/* Write buffer to file */
						res = f_write(&fsrc, textFileBuffer, strlen(textFileBuffer), &br); 	
						
//�������Ϊ���Գ���ƫ�Ƶ�ַӦ��ʹ���ݲ��ܿ���д�룬Ӧ����1024��Ϊһ���洢��
// 						addr123=0;
// 						for(i=0;i<10000;i++)
// 						{
// 							addr123=i*64;
// 							res=f_lseek(&fsrc, addr123);
// 							/* Write buffer to file */
// 							res = f_write(&fsrc, textFileBuffer, strlen(textFileBuffer), &br); 	
// 							printf("Now the I = %d; the addr=%d \r\n",i,addr123);
// 							
// 							res=f_sync(&fsrc);
// 						}						
						
						printf("***********************************************************");
						printf("\r\n");

						printf("˵��.TXT �����ɹ���");
						printf("\r\n");
					
						/*close file */
						f_close(&fsrc);      
					}
					else if ( res == FR_EXIST )	//�����U������.TXT���Ѿ�����
					{
						printf("-----------------------------------------");
						printf("\r\n");	  
						printf("˵��.TXT �ļ��Ѵ��ڡ�");
						printf("\r\n");
						
					}
					
					USBH_USR_ApplicationState = USH_USR_FS_READFILE;					
					break;
    
		case USH_USR_FS_READFILE:	  //��ȡ�ļ�
		 
					printf("-----------------------------------------");
					printf("\r\n");

					if(HCD_IsDeviceConnected(&USB_OTG_FS_dev))
					{
						f_mount(0, &fs);      
						res = f_opendir(&dir, "0:");
						if( res != FR_OK )
						{
							/*Could not open the selected directory*/
							return(-2);
						}
						
						if((HCD_IsDeviceConnected(&USB_OTG_FS_dev)) && ( f_readdir(&dir, &fno) == FR_OK ) && fno.fname[0] != 0 )
						{ 
							res = f_open(&fsrc, "0:/˵��.TXT", FA_OPEN_EXISTING | FA_READ);
							if( res == FR_OK )
							{
								printf("˵��.TXT  ��ȡ�ɹ���");
								printf("\r\n");
								res = f_read( &fsrc, read_txt_file_buff, sizeof(read_txt_file_buff) , &br );
								printf("˵��.TXT  �������ǣ�");
								printf("\r\n");
								printf("%s",read_txt_file_buff); //����ȡ�������ݷ�������  								
								/*close file */
								f_close(&fsrc);
							}
							else
							{
								printf("-----------------------------------------");
								printf("\r\n");	
								printf("û���ҵ� ˵��.TXT");
								printf("\r\n");	
							}						
						}
					}
					USBH_USR_ApplicationState = USH_USR_FS_NULL;
					break;
					
		case USH_USR_FS_NULL:	  //�ļ��򿪳ɹ���������ж�д����				
					
					
		default: 
					break;
  }
  return(0);
}



/***********************************************************************
�������ƣ�void USBH_USR_HexToASCII(uint32_t receivedValue)
��    �ܣ�16����ת����ASCII����
�����������
�����������
��дʱ�䣺2014.04.27
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/
void USBH_USR_HexToASCII(uint32_t receivedValue)
{
  uint8_t count;
  uint8_t localTemp[10] = "         "; 
  uint8_t *ptr;
  uint8_t counter = 0;
  
  for(count = 0; count < 8; count++ )
	{
    temp[count] = 0x20;		
	} 
  temp[8] = 0;
  for(count = 0; count < 8; count++ )
  {
    localTemp[count] = receivedValue % 10;    
    if(localTemp[count] < 0x0A)
		{
      localTemp[count] += 0x30;
		}
    else
		{
      localTemp[count] += 0x37; 
		}			
    
    if(receivedValue < 10)
    {     
      break;
    }    
    receivedValue = receivedValue / 10;   
  } 
  count = 0;
  
  /*check for end of data*/
  ptr = localTemp;
  while(*ptr != 0x20)
  {
    count++;
    ptr++;
  }
  
  counter = 0;
  ptr--;
  
  while(count)
  {
    temp[counter] = *ptr;
    ptr--;
    count--;
    counter++;
  }  
  
}

/***********************************************************************
�������ƣ�void USBH_USR_DeInit(void)
��    �ܣ�U�̳�ʼ��
�����������
�����������
��дʱ�䣺2014.04.27
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/
void USBH_USR_DeInit(void)
{
  USBH_USR_ApplicationState = USH_USR_FS_INIT;
}


























