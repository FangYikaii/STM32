/*
����˵��:  	
            IO�������� --- STM32F107VCT 
						
ע�����	1��ע��ܽŵĸ�������						
						
						
�˿�ʹ��:		��Doc�ļ�����˵��
������:     Masterjay   
����ʱ��:   2014-04-21 
�޸�ʱ��:   2014-04-21
*/

//========================================
//ͷ�ļ�
#include "main.h"

//========================================
//��������
struct ControllerData	ControllerInfo;
volatile union FlagController flagctrl;

//========================================
//��������
void StartUpGearDeal(void);								//����ʱ�̵�λ�������
void GearScanVSDeal(void);								//��λɨ��ʹ������

void IOControl_Init(void);   							//IO��ʼ��
uint8_t ReadGearLine_Status(void);					//��ȡ���������ĵ�ƽ
void GearToSolenoidValve(uint8_t gear,uint8_t status_brake);			//��λ���ŷ�������ת��

//========================================
//��ģ�麯��


/***********************************************************************
�������ƣ�void StartUpGearDeal(void)
��    �ܣ�����ʱ�̵�λ�������
�����������
�����������
��дʱ�䣺2014.05.29
�� д �ˣ�masterjay
ע    �⣺
***********************************************************************/
void StartUpGearDeal(void)
{
	  if(flagctrl.Bits.ScanTimeFlag)		//10/100msɨ��һ��											
		{
			flagctrl.Bits.ScanTimeFlag=FALSE;	
			ControllerInfo.NowGear=ReadGearLine_Status();						//��λ��Ϣ��ȡ		
			ControllerInfo.ProcessGear=ControllerInfo.NowGear;			//���̵�λ��ʾ��δ�������������л������Ŵ���N1��
			if(!flagctrl.Bits.StartUpFromNx)												//��ʼ��ʱ�����źŴ�N��ʼ�ж�
			{
				if(ControllerInfo.NowGear/0x10==2)										//����ǰ����N�ź�
				{
						flagctrl.Bits.StartUpFromNx=TRUE;									//����װ�ػ�����	
						ErrorMessage=0xEE;																//������ʾ��Ϣ-- -- -- �޴���										
//					if(ControllerInfo.NowGear%0x10<2)										//N+1��N+P
//					{
//						flagctrl.Bits.StartUpFromNx=TRUE;									//����װ�ػ�����	
//						ErrorMessage=0xEE;																//������ʾ��Ϣ-- -- -- �޴���
//					}
//					else
//					{
//						ErrorMessage=0xFF;																//������ʾ��Ϣ--EE	
//					}
				}
				else
				{
					ErrorMessage=0xFF;																	//������ʾ��Ϣ--EE					
				}
			}
		}
		if(flagTIM5.Bits.T1sec_Flag)															//��ʾ������Ϣ EE-- ��λδ��N+1��N+P����
		{
			flagTIM5.Bits.T1sec_Flag=FALSE;	
			ErrorDisplay(ErrorMessage);		
		}			
}

/***********************************************************************
�������ƣ�void GearScanVSDeal(void)
��    �ܣ���λɨ��ʹ������
�����������
�����������
��дʱ�䣺2014.05.29
�� д �ˣ�masterjay
ע    �⣺
***********************************************************************/
void GearScanVSDeal(void)
{		
	//******************************************************************************
	//��λ�Ȼ�����Ϣ��ȡ����
	ControllerInfo.NowGear=ReadGearLine_Status();					//��λ��Ϣ��ȡ
	ControllerInfo.NowBrake=BrakeControl_Read;						//ɲ���ƶ���Ϣ��ȡ
	if(ControllerInfo.NowGear==0x30)											//KD��
	{
		if(!flagctrl.Bits.KDScan_Flag)											//KD��֮ǰδ����
		{
			flagctrl.Bits.KDScan_Flag=TRUE;										//KD�����£��ȴ���λ
			if(!flagctrl.Bits.KDchange)												//KD��δ��Чǰ
			{
				flagctrl.Bits.KDchange=TRUE;										
				flagctrl.Bits.gearchange=TRUE;	
				ControllerInfo.gearCGcount=0;
				RdData.GearInfo=ControllerInfo.NowGear;					//���ڵ�λ��ʾ				
			}	
			else																							//��ǰ�Ѵ���KD��״̬
			{
				flagctrl.Bits.KDchange=FALSE;										
				flagctrl.Bits.gearchange=TRUE;	
				ControllerInfo.gearCGcount=0;
				RdData.GearInfo=ControllerInfo.NowGear;
				ControllerInfo.gearinfo=ControllerInfo.NowGear;	//��¼��λ��Ϣ-- ע����ȫ��Ĳ��
			}					
		}
		
	}	
	else
	{
		flagctrl.Bits.KDScan_Flag=FALSE;												//KD����λ����
		if(ControllerInfo.NowGear!=ControllerInfo.gearinfo)			//��λ�仯����
		{		
			ControllerInfo.gearCGcount++;													//��ǰ��λɨ�����������3ʱ��ʾ��λ�仯�ȶ�
			flagctrl.Bits.KDchange=FALSE;
			if(ControllerInfo.gearCGcount>=3)
			{
				flagctrl.Bits.gearchange=TRUE;	
				ControllerInfo.gearCGcount=0;
				ControllerInfo.gearinfo=ControllerInfo.NowGear;
				RdData.GearInfo=ControllerInfo.NowGear;	
			}
		}			
	}
	if(ControllerInfo.NowBrake!=ControllerInfo.brakeinfo)			//�ƶ��źű仯����
	{
		ControllerInfo.brakeCGcount++;
		if(ControllerInfo.brakeCGcount>=3)
		{
			flagctrl.Bits.brakechange=TRUE;
			ControllerInfo.brakeCGcount=0;
			ControllerInfo.brakeinfo=ControllerInfo.NowBrake;
		}
	}	
}

/***********************************************************************
�������ƣ�void IOControl_Init(void)
��    �ܣ�IOControl��ʼ��
�����������
�����������
��дʱ�䣺2013.11.19
�� д �ˣ�masterjay
ע    �⣺
***********************************************************************/
void IOControl_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;      //����GPIO�ṹ��	

// //************************************
// //��λ�ɼ��ź�IO
 	
 	RCC_APB2PeriphClockCmd(GearLine_Brown_RCC_APB2Periph_GPIOX, ENABLE);								//����--3 ��ɫ
 	GPIO_InitStructure.GPIO_Pin = GearLine_Brown_PIN;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
 	GPIO_Init(GearLine_Brown_GPIOX, &GPIO_InitStructure);

 	RCC_APB2PeriphClockCmd(GearLine_Purple_RCC_APB2Periph_GPIOX, ENABLE);								//����--4 ��ɫ	
 	GPIO_InitStructure.GPIO_Pin = GearLine_Purple_PIN;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
 	GPIO_Init(GearLine_Purple_GPIOX, &GPIO_InitStructure);	
 	
 	RCC_APB2PeriphClockCmd(GearLine_White_RCC_APB2Periph_GPIOX, ENABLE);								//����--5 ��ɫ
 	GPIO_InitStructure.GPIO_Pin = GearLine_White_PIN;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
 	GPIO_Init(GearLine_White_GPIOX, &GPIO_InitStructure);
 	
 	RCC_APB2PeriphClockCmd(GearLine_Yellow_RCC_APB2Periph_GPIOX, ENABLE);								//����--6 ��ɫ
 	GPIO_InitStructure.GPIO_Pin = GearLine_Yellow_PIN;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
 	GPIO_Init(GearLine_Yellow_GPIOX, &GPIO_InitStructure);
 	
 	RCC_APB2PeriphClockCmd(GearLine_Blue_RCC_APB2Periph_GPIOX, ENABLE);								 	//����--7 ��ɫ
 	GPIO_InitStructure.GPIO_Pin = GearLine_Blue_PIN;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
 	GPIO_Init(GearLine_Blue_GPIOX, &GPIO_InitStructure);

 	RCC_APB2PeriphClockCmd(GearLine_Green_RCC_APB2Periph_GPIOX, ENABLE);								//����--8 ��ɫ
 	GPIO_InitStructure.GPIO_Pin = GearLine_Green_PIN;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
 	GPIO_Init(GearLine_Green_GPIOX, &GPIO_InitStructure);
	
//************************************
//��ŷ������ź�IO

	RCC_APB2PeriphClockCmd(SolenoidValve_M1_RCC_APB2Periph_GPIOX, ENABLE);								 //��ŷ�--M1 ��ɫ
	GPIO_InitStructure.GPIO_Pin = SolenoidValve_M1_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(SolenoidValve_M1_GPIOX, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(SolenoidValve_M2_RCC_APB2Periph_GPIOX, ENABLE);								 //��ŷ�--M2 ��ɫ
	GPIO_InitStructure.GPIO_Pin = SolenoidValve_M2_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(SolenoidValve_M2_GPIOX, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(SolenoidValve_M3_RCC_APB2Periph_GPIOX, ENABLE);								 //��ŷ�--M3 ��ɫ
	GPIO_InitStructure.GPIO_Pin = SolenoidValve_M3_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(SolenoidValve_M3_GPIOX, &GPIO_InitStructure);	

	RCC_APB2PeriphClockCmd(SolenoidValve_M4_RCC_APB2Periph_GPIOX, ENABLE);								 //��ŷ�--M4 ��ɫ
	GPIO_InitStructure.GPIO_Pin = SolenoidValve_M4_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(SolenoidValve_M4_GPIOX, &GPIO_InitStructure);	

	RCC_APB2PeriphClockCmd(SolenoidValve_M5_RCC_APB2Periph_GPIOX, ENABLE);								 //��ŷ�--M5 ��ɫ
	GPIO_InitStructure.GPIO_Pin = SolenoidValve_M5_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(SolenoidValve_M5_GPIOX, &GPIO_InitStructure);	

	SolenoidValve_M1(0);
	SolenoidValve_M2(0);
	SolenoidValve_M3(0);
	SolenoidValve_M4(0);
	SolenoidValve_M5(0);
	
// //************************************
// //�ƶ����Ʋɼ���ϢIO	

 	RCC_APB2PeriphClockCmd(BrakeControl_RCC_APB2Periph_GPIOX, ENABLE);								 //�ƶ�����--��ɫ
 	GPIO_InitStructure.GPIO_Pin = BrakeControl_PIN;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
 	GPIO_Init(BrakeControl_GPIOX, &GPIO_InitStructure);		
	


//************************************
//�յ����������뵹����ʾ�ƿ�����ϢIO

	RCC_APB2PeriphClockCmd(AsternAlarmLED_RCC_APB2Periph_GPIOX, ENABLE);								 //������ʾ��--��ɫ
	GPIO_InitStructure.GPIO_Pin = AsternAlarmLED_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(AsternAlarmLED_GPIOX, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(NeutralStartInterlock_RCC_APB2Periph_GPIOX, ENABLE);								 //�յ���������--��ɫ
	GPIO_InitStructure.GPIO_Pin = NeutralStartInterlock_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(NeutralStartInterlock_GPIOX, &GPIO_InitStructure);	

	AsternAlarmLED(0);
	NeutralStartInterlock(0);	

//************************************
//Ԥ��IO

	RCC_APB2PeriphClockCmd(ReservedIO_RCC_APB2Periph_GPIOX, ENABLE);								 //Ԥ��IO--�ɿ��Ƶ�ŷ�
	GPIO_InitStructure.GPIO_Pin = ReservedIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 			
	GPIO_Init(ReservedIO_GPIOX, &GPIO_InitStructure);		
	
	ReservedIO(0);
	
	
	
}

/***********************************************************************
�������ƣ�uint8_t ReadGearLine_Status(void)
��    �ܣ���ȡ���������ĵ�ƽ
�����������
�����������λֵ
��дʱ�䣺2013.11.19
�� д �ˣ�masterjay
ע    �⣺
***********************************************************************/
/***********************************************************************
����λ��Ӧ�ɼ�ֵ�б�
		ǰ���� V     �յ�N 			 ���˵�R     KD
P   0x14				 0x34				 0x24				 0xXX & 0x01=0x00
1   0x10				 0x30				 0x20				 0xXX & 0x01=0x00		
2   0x12				 0x32				 0x22				 0xXX & 0x01=0x00
3   0x16				 0x36				 0x26 			 0xXX & 0x01=0x00
4   0x1E				 0x3E				 0x2E 			 0xXX & 0x01=0x00

***********************************************************************/

uint8_t ReadGearLine_Status(void)
{
	uint8_t gear=0;
	uint8_t result=0;
 	if(GearLine_Purple_Read)//����--4 ��ɫ
 	{
 		result+=1;		
 	}	
   result<<=1;
 	if(GearLine_Brown_Read)	//����--3 ��ɫ
 	{
 		result+=1;
 	}
   result<<=1;
 	if(GearLine_Green_Read)//����--8 ��ɫ	
 	{
 		result+=1;		
 	}	
   result<<=1;
 	if(GearLine_Blue_Read)//����--7 ��ɫ	
 	{
 		result+=1;		
 	}	
   result<<=1;	
 	if(GearLine_Yellow_Read)//����--6 ��ɫ	
 	{
 		result+=1;		
 	}	
   result<<=1;
 	
 	if(GearLine_White_Read)//����--5 ��ɫ
 	{
 		result+=1;		
 	}
 	if(result%2==1)			 				//KD
 	{
 		gear=0x30;
 	}
 	else
 	{
 		switch(result%0x10)
 		{
 			case 0x04 :					 //P��
 			{
 				gear=0;
 				break;				
 			}			
 			case 0x00 :						//1��
 			{
 				gear=1;
 				break;				
 			}
 			case 0x02 :						//2��
 			{
 				gear=2;
 				break;					
 			}	
 			case 0x06 :						//3��
 			{
 				gear=3;
 				break;					
 			}	
 			case 0x0E :						//4��
 			{
 				gear=4;
 				break;					
 			}
 			default :
 				break;		
 		}
 		switch(result/0x10)
 		{
 			case 0x03 :					  //�յ� -- 0x2x
 			{
 				gear=gear+0x20;
 				break;				
 			}	
 			case 0x02 :					  //���˵�	-- 0x1x
 			{
 				gear=gear+0x10;
 				break;				
 			}	
 			case 0x01 :					  //ǰ����	-- 0x0x
 			{
 				gear=gear+0x00;
 				break;				
 			}	
 			default :
 			break;	
 		}	
 	}
  return (gear);
}
/***********************************************************************
�������ƣ�void GearToSolenoidValve(uint8_t gear,uint8_t status_brake)
��    �ܣ���λ���ŷ�������ת��
�����������λֵ
�����������
��дʱ�䣺2013.11.19
�� д �ˣ�masterjay
ע    �⣺
***********************************************************************/
void GearToSolenoidValve(uint8_t gear,uint8_t status_brake)
{
		if(flagctrl.Bits.KDchange)				//KD��ʹ��--1������			
		{
			if(gear/0x10==0)								//ǰ����
			{	
				AsternAlarmLED(0); 						//������ʾ��
				NeutralStartInterlock(0); 		//�յ���������					
				if(status_brake==0)						//���ƶ��ź�
				{
					SolenoidValve_M5(0);			
					SolenoidValve_M4(1);
					SolenoidValve_M3(1);				//�����ƶ����	
					SolenoidValve_M2(1);					
					SolenoidValve_M1(0);
				}
				else
				{
					SolenoidValve_M5(0);			
					SolenoidValve_M4(1);
					SolenoidValve_M3(0);				//�����ƶ����		
					SolenoidValve_M2(1);					
					SolenoidValve_M1(0);					
					
				}		
			}
			else if(gear/0x10==1)						//���˵�
			{
				AsternAlarmLED(1); 						//������ʾ��
				NeutralStartInterlock(0); 		//�յ���������				
				if(status_brake==0)						//���ƶ��ź�
				{
					SolenoidValve_M5(0);			
					SolenoidValve_M4(1);
					SolenoidValve_M3(1);				//�����ƶ����	
					SolenoidValve_M2(1);					
					SolenoidValve_M1(1);				//�����ƶ����	
				}
				else
				{
					SolenoidValve_M5(0);			
					SolenoidValve_M4(1);
					SolenoidValve_M3(0);				//�����ƶ����		
					SolenoidValve_M2(1);					
					SolenoidValve_M1(0);				//�����ƶ����						
					
				}									
			}	
			else if(gear/0x10==2)						//�յ�
			{
				AsternAlarmLED(0); 						//������ʾ��
				NeutralStartInterlock(1); 		//�յ���������				

				SolenoidValve_M5(0);			
				SolenoidValve_M4(1);
				SolenoidValve_M3(0);
				SolenoidValve_M2(1);					
				SolenoidValve_M1(0);										
			}	
			
		}
		else																	//KD��δʹ�����	
		{
			if(gear/0x10==0)										//ǰ����
			{
				AsternAlarmLED(0); 								//������ʾ��
				NeutralStartInterlock(0); 				//�յ���������
				switch(gear%0x10)
				{
					case 0x00:											//ǰ����--P��
					{
						
						SolenoidValve_M5(0);					//ͣ��		
						SolenoidValve_M4(0);
						SolenoidValve_M3(0);				
						SolenoidValve_M2(0);					
						SolenoidValve_M1(0);						
						
						
//						if(status_brake==0)						//���ƶ��ź� == 1��
//						{
//							SolenoidValve_M5(0);			
//							SolenoidValve_M4(1);
//							SolenoidValve_M3(1);				//�����ƶ����	
//							SolenoidValve_M2(1);					
//							SolenoidValve_M1(0);
//						}
//						else
//						{
//							SolenoidValve_M5(0);			
//							SolenoidValve_M4(1);
//							SolenoidValve_M3(0);				//�����ƶ����		
//							SolenoidValve_M2(1);					
//							SolenoidValve_M1(0);					
//							
//						}						
						break;						
					}
					case 0x01:											//ǰ����--1��
					{
						if(status_brake==0)						//���ƶ��ź�
						{
							SolenoidValve_M5(0);			
							SolenoidValve_M4(1);
							SolenoidValve_M3(1);				//�����ƶ����	
							SolenoidValve_M2(1);					
							SolenoidValve_M1(0);
						}
						else
						{
							SolenoidValve_M5(0);			
							SolenoidValve_M4(1);
							SolenoidValve_M3(0);				//�����ƶ����		
							SolenoidValve_M2(1);					
							SolenoidValve_M1(0);					
							
						}								
						break;						
					}
					case 0x02:											//ǰ����--2��
					{
						if(status_brake==0)						//���ƶ��ź�
						{
							SolenoidValve_M5(0);			
							SolenoidValve_M4(1);
							SolenoidValve_M3(1);				//�����ƶ����	
							SolenoidValve_M2(0);					
							SolenoidValve_M1(0);
						}
						else
						{
							SolenoidValve_M5(0);			
							SolenoidValve_M4(1);
							SolenoidValve_M3(0);				//�����ƶ����		
							SolenoidValve_M2(0);					
							SolenoidValve_M1(0);					
						}							
						break;						
					}						
					case 0x03:											//ǰ����--3��
					{
						SolenoidValve_M5(0);							
						SolenoidValve_M4(0);						
						SolenoidValve_M3(1);
						SolenoidValve_M2(0);
						SolenoidValve_M1(0);						
						break;						
					}
					case 0x04:											//ǰ����--4��
					{
						SolenoidValve_M5(0);								
						SolenoidValve_M4(0);		
						SolenoidValve_M3(0);
						SolenoidValve_M2(0);						
						SolenoidValve_M1(1);				
						break;						
					}
					default:						
					{						
						break;						
					}						
				}					
			}
			else if(gear/0x10==1)								//���˵�
			{
				AsternAlarmLED(1); 								//������ʾ��
				NeutralStartInterlock(0); 				//�յ���������
				switch(gear%0x10)
				{
					case 0x00:											//���˵�--P��	
					{
						
						SolenoidValve_M5(0);					//  == ͣ��
						SolenoidValve_M4(0);
						SolenoidValve_M3(0);				
						SolenoidValve_M2(0);					
						SolenoidValve_M1(0);									
//						if(status_brake==0)						//���ƶ��ź�  == 1��
//						{
//							SolenoidValve_M5(0);			
//							SolenoidValve_M4(1);
//							SolenoidValve_M3(1);				//�����ƶ����	
//							SolenoidValve_M2(1);					
//							SolenoidValve_M1(1);				//�����ƶ����	
//						}
//						else
//						{
//							SolenoidValve_M5(0);			
//							SolenoidValve_M4(1);
//							SolenoidValve_M3(0);				//�����ƶ����		
//							SolenoidValve_M2(1);					
//							SolenoidValve_M1(0);				//�����ƶ����						
//							
//						}						
						break;	
					}						
					case 0x01:											//���˵�--1��
					{
						if(status_brake==0)						//���ƶ��ź�
						{
							SolenoidValve_M5(0);			
							SolenoidValve_M4(1);
							SolenoidValve_M3(1);				//�����ƶ����	
							SolenoidValve_M2(1);					
							SolenoidValve_M1(1);				//�����ƶ����	
						}
						else
						{
							SolenoidValve_M5(0);			
							SolenoidValve_M4(1);
							SolenoidValve_M3(0);				//�����ƶ����		
							SolenoidValve_M2(1);					
							SolenoidValve_M1(0);				//�����ƶ����						
							
						}							
						break;						
					}
					case 0x02:											//���˵�--2��
					{
						if(status_brake==0)						//���ƶ��ź�
						{
							SolenoidValve_M5(0);			
							SolenoidValve_M4(1);
							SolenoidValve_M3(1);				//�����ƶ����	
							SolenoidValve_M2(0);					
							SolenoidValve_M1(1);				//�����ƶ����	
						}
						else
						{
							SolenoidValve_M5(0);			
							SolenoidValve_M4(1);
							SolenoidValve_M3(0);				//�����ƶ����		
							SolenoidValve_M2(0);					
							SolenoidValve_M1(0);				//�����ƶ����						
							
						}							
						break;						
					}						
					case 0x03:											//���˵�--3��
					{
						SolenoidValve_M5(0);	
						SolenoidValve_M4(0);		
						SolenoidValve_M3(1);
						SolenoidValve_M2(0);						
						SolenoidValve_M1(1);							
						break;						
					}
					case 0x04:											//���˵�--4��
					{
						SolenoidValve_M5(0);	
						SolenoidValve_M4(0);		
						SolenoidValve_M3(1);
						SolenoidValve_M2(0);						
						SolenoidValve_M1(1);							
						break;						
					}					
					default:											//
					{						
						break;						
					}						
				}					
				
			}
			else if(gear/0x10==2)						//�յ�
			{
				AsternAlarmLED(0); 						//������ʾ��
				NeutralStartInterlock(1); 		//�յ���������				
				switch(gear%0x10)
				{
					case 0x00:									//�յ�--P��
					{
						
						SolenoidValve_M5(0);			// == ͣ��				
						SolenoidValve_M4(0);						
						SolenoidValve_M3(0);				
						SolenoidValve_M2(0);						
						SolenoidValve_M1(0);							
						
//						SolenoidValve_M5(0);			// == 1��							
//						SolenoidValve_M4(1);						
//						SolenoidValve_M3(0);				
//						SolenoidValve_M2(1);						
//						SolenoidValve_M1(0);				
						break;						
					}					
					
					case 0x01:									//�յ�--1��
					{
						SolenoidValve_M5(0);
						SolenoidValve_M4(1);
						SolenoidValve_M3(0);		
						SolenoidValve_M2(1);						
						SolenoidValve_M1(0);					
						break;						
					}
					case 0x02:									//�յ�--2��
					{
						SolenoidValve_M5(0);							
						SolenoidValve_M4(1);						
						SolenoidValve_M3(0);						
						SolenoidValve_M2(0);						
						SolenoidValve_M1(0);					
						break;						
					}						
					case 0x03:									//�յ�--3��
					{
						SolenoidValve_M1(0);
						SolenoidValve_M2(0);
						SolenoidValve_M3(0);
						SolenoidValve_M4(0);
						SolenoidValve_M5(0);							
						break;						
					}
					case 0x04:									//�յ�--4��
					{
						SolenoidValve_M1(0);
						SolenoidValve_M2(0);
						SolenoidValve_M3(0);
						SolenoidValve_M4(0);
						SolenoidValve_M5(0);							
						break;						
					}
					default:										//
					{						
						break;						
					}						
				}			
			}			
		}	
}




