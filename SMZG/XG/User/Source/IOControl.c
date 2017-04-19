/*
����˵��:  	
            IO�������� --- STM32F107VCT 
						
ע�����	1��ע��ܽŵĸ�������						
						
						
�˿�ʹ��:		��Doc�ļ�����˵��
������:     FangYikaii   
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
void GearScanVSDeal_HandShiftMode(void);	//��λɨ��ʹ������
void GearScanVSDeal_AutoShiftMode(void);
void IOControl_Init(void);   							//IO��ʼ��
void ReadGearLine_Status(void);					//��ȡ���������ĵ�ƽ
void GearToSolenoidValve(uint8_t gear,uint8_t status_brake);			//��λ���ŷ�������ת��

//========================================
//��ģ�麯��


/***********************************************************************
�������ƣ�void StartUpGearDeal(void)
��    �ܣ�����ʱ�̵�λ�������
�����������
�����������
��дʱ�䣺2014.05.29
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/
void StartUpGearDeal(void)
{
	  if(flagctrl.Bits.ScanTimeFlag)		//10/100msɨ��һ��											
		{
			flagctrl.Bits.ScanTimeFlag=FALSE;	
			ReadGearLine_Status();						//��λ��Ϣ��ȡ		
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
�������ƣ�void GearScanVSDeal_HandShiftMode(void)
��    �ܣ��ֶ�����ʱ��λɨ��ʹ������
�����������
�����������
��дʱ�䣺2014.05.29
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/
void GearScanVSDeal_HandShiftMode(void)
{		
	ReadGearLine_Status();					//��λ��Ϣ��ȡ
	GearToSolenoidValve(ControllerInfo.NowGear,ControllerInfo.NowBrake);
	
}

/***********************************************************************
�������ƣ�void GearScanVSDeal_AutoShiftMode(void)
��    �ܣ��ֶ�����ʱ��λɨ��ʹ������
�����������
�����������
��дʱ�䣺2014.05.29
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/
void GearScanVSDeal_AutoShiftMode(void)
{		
	ReadGearLine_Status();					//��λ��Ϣ��ȡ
	if(ControllerInfo.NowBrake==0)	//�Ƿ�ɲ�� == ��
	{
		if(ControllerInfo.NowGear/0x10==0)										//ǰ����
		{	
			
		}
		else if(ControllerInfo.NowGear/0x10==1)										//���˵�
		{
			
		}			
	}
	else //�Ƿ�ɲ�� == ��
	{
		
	}	
	
	GearToSolenoidValve(ControllerInfo.NowGear,ControllerInfo.NowBrake);
	
}

/***********************************************************************
�������ƣ�void IOControl_Init(void)
��    �ܣ�IOControl��ʼ��
�����������
�����������
��дʱ�䣺2013.11.19
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/
void IOControl_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;      //����GPIO�ṹ��	

// //************************************
// //��λ�ɼ��ź�IO
 	
 	RCC_APB2PeriphClockCmd(DIIN1_M1_RCC_APB2Periph_GPIOX, ENABLE);								//M1
 	GPIO_InitStructure.GPIO_Pin = DIIN1_M1_PIN;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
 	GPIO_Init(DIIN1_M1_GPIOX, &GPIO_InitStructure);

 	RCC_APB2PeriphClockCmd(DIIN2_M2_RCC_APB2Periph_GPIOX, ENABLE);								//M2	
 	GPIO_InitStructure.GPIO_Pin = DIIN2_M2_PIN;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
 	GPIO_Init(DIIN2_M2_GPIOX, &GPIO_InitStructure);	
 	
 	RCC_APB2PeriphClockCmd(DIIN3_M3_RCC_APB2Periph_GPIOX, ENABLE);								//M3
 	GPIO_InitStructure.GPIO_Pin = DIIN3_M3_PIN;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
 	GPIO_Init(DIIN3_M3_GPIOX, &GPIO_InitStructure);
 	
 	RCC_APB2PeriphClockCmd(DIIN4_M4_RCC_APB2Periph_GPIOX, ENABLE);								//M4
 	GPIO_InitStructure.GPIO_Pin = DIIN4_M4_PIN;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
 	GPIO_Init(DIIN4_M4_GPIOX, &GPIO_InitStructure);
 	
 	RCC_APB2PeriphClockCmd(DIIN5_AS_RCC_APB2Periph_GPIOX, ENABLE);								 	//AS
 	GPIO_InitStructure.GPIO_Pin = DIIN5_AS_PIN;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
 	GPIO_Init(DIIN5_AS_GPIOX, &GPIO_InitStructure);

 	RCC_APB2PeriphClockCmd(DIIN6_RF_RCC_APB2Periph_GPIOX, ENABLE);								//RF
 	GPIO_InitStructure.GPIO_Pin = DIIN6_RF_PIN;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
 	GPIO_Init(DIIN6_RF_GPIOX, &GPIO_InitStructure);
	
 	RCC_APB2PeriphClockCmd(DIIN7_BR_RCC_APB2Periph_GPIOX, ENABLE);								//BR
 	GPIO_InitStructure.GPIO_Pin = DIIN7_BR_PIN;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
 	GPIO_Init(DIIN7_BR_GPIOX, &GPIO_InitStructure);	
	
 	RCC_APB2PeriphClockCmd(DIIN8_XX_RCC_APB2Periph_GPIOX, ENABLE);								//XX
 	GPIO_InitStructure.GPIO_Pin = DIIN8_XX_PIN;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
 	GPIO_Init(DIIN8_XX_GPIOX, &GPIO_InitStructure);		
	
//************************************
//��ŷ������ź�IO

	RCC_APB2PeriphClockCmd(DOOUT1_M1_RCC_APB2Periph_GPIOX, ENABLE);								 //��ŷ�--M1
	GPIO_InitStructure.GPIO_Pin = DOOUT1_M1_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(DOOUT1_M1_GPIOX, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(DOOUT2_M2_RCC_APB2Periph_GPIOX, ENABLE);								 //��ŷ�--M2
	GPIO_InitStructure.GPIO_Pin = DOOUT2_M2_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(DOOUT2_M2_GPIOX, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(DOOUT3_M3_RCC_APB2Periph_GPIOX, ENABLE);								 //��ŷ�--M3
	GPIO_InitStructure.GPIO_Pin = DOOUT3_M3_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(DOOUT3_M3_GPIOX, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(DOOUT4_M4_RCC_APB2Periph_GPIOX, ENABLE);								 //��ŷ�--M4
	GPIO_InitStructure.GPIO_Pin = DOOUT4_M4_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(DOOUT4_M4_GPIOX, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(DOOUT5_BR_RCC_APB2Periph_GPIOX, ENABLE);								 //BR
	GPIO_InitStructure.GPIO_Pin = DOOUT5_BR_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(DOOUT5_BR_GPIOX, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(DOOUT6_RF_RCC_APB2Periph_GPIOX, ENABLE);								 //RF
	GPIO_InitStructure.GPIO_Pin = DOOUT6_RF_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(DOOUT6_RF_GPIOX, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(DOOUT7_AS_RCC_APB2Periph_GPIOX, ENABLE);								 //AS
	GPIO_InitStructure.GPIO_Pin = DOOUT7_AS_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(DOOUT7_AS_GPIOX, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(DOOUT8_XX_RCC_APB2Periph_GPIOX, ENABLE);								 //XX
	GPIO_InitStructure.GPIO_Pin = DOOUT8_XX_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(DOOUT8_XX_GPIOX, &GPIO_InitStructure);	
	
	DOOUT1_M1(0);			
	DOOUT2_M2(0);			
	DOOUT3_M3(0);		
	DOOUT4_M4(0);	
	
	DOOUT5_BR(0);	
	DOOUT6_RF(0);  
	DOOUT7_AS(0);  	
	DOOUT8_XX(0);  	
	
}

/***********************************************************************
�������ƣ�uint8_t ReadGearLine_Status(void)
��    �ܣ���ȡ���������ĵ�ƽ
�����������
�����������λֵ
��дʱ�䣺2013.11.19
�� д �ˣ�FangYikaii
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

void ReadGearLine_Status(void)
{
	uint8_t gear=0;
	uint8_t result=0;
	//*******************************************	
 	if(DIIN1_M1_Read)//DIIN1 -- ��ŷ�M1
 	{
 		result+=1;	
//		DOOUT1_M1(1);
 	}	
	else
	{
//		DOOUT1_M1(0);		
	}
   result<<=1;
 	if(DIIN2_M2_Read)//DIIN2 -- ��ŷ�M2
 	{
 		result+=1;	
//		DOOUT2_M2(1);		
 	}	
	else
	{
//		DOOUT2_M2(0);			
	}
   result<<=1; 
	
 	if(DIIN3_M3_Read)//DIIN3 -- ��ŷ�M3
 	{
 		result+=1;	
//		DOOUT3_M3(1);			
 	}	
	else
	{
//		DOOUT3_M3(0);			
	}
   result<<=1;	
	
 	if(DIIN4_M4_Read)//DIIN4 -- ��ŷ�M4
 	{
 		result+=1;		
//		DOOUT4_M4(1);			
 	}	
	else
	{
//		DOOUT4_M4(0);			
	}
	//*******************************************
 	if(DIIN5_AS_Read)//DIIN5 -- AS  �յ��ź�
 	{	
//		DOOUT7_AS(1);			//AS  �յ��ź�
 	}
	else
	{
//		DOOUT7_AS(0);				
	}
	
 	if(DIIN6_RF_Read)//DIIN6 -- RF  �����ź�
 	{	
//		DOOUT6_RF(1);		//RF  �����ź�	
 	}
	else
	{
//		DOOUT6_RF(0);				
	}
	
 	if(DIIN7_BR_Read)//DIIN7 -- BR	�ƶ��ź�
 	{
		ControllerInfo.NowBrake=1;
//		DOOUT5_BR(1);		//BR	�ƶ��ź�	
 	}
	else
	{
		ControllerInfo.NowBrake=0;		
//		DOOUT5_BR(0);				
	}	
	
	//*******************************************	

	//XG.PumpSpeed=result;  ������ʾ������ʹ��
	switch(result)
	{
 			case 0x07 :						//1��  (0111)
 			{
 				gear=1;
 				break;				
 			}
 			case 0x0d :						//2��  (1101)
 			{
 				gear=2;
 				break;					
 			}	
 			case 0x03 :						//3��  (0011)
 			{
 				gear=3;
 				break;					
 			}	
 			case 0x09 :						//4�� (1001)
 			{
 				gear=4;
 				break;					
 			}
 			case 0x02 :						//5��  (0010)
 			{
 				gear=5;
 				break;					
 			}	
 			case 0x08 :						//6��  (1000)
 			{
 				gear=6;
 				break;					
 			}			
 			case 0x0F :						//��1��  (1111)
 			{
 				gear=1+0X10;
 				break;					
 			}
 			case 0x0B :						//��2��  (1011)
 			{
 				gear=2+0X10;
 				break;					
 			}	
 			case 0x0A :						//��3��  (1010)
 			{
 				gear=3+0X10;
 				break;					
 			}	
 			case 0x00 :						//�յ�   (0000)
 			{
 				gear=0+0X20;
 				break;					
 			}				
 			default :
			{
 				gear=0+0X20;				
 				break;						
			}	
	}	
	ControllerInfo.NowGear=gear;
	if(ControllerInfo.NowBrake==1)		//�ƶ��ź�
	{
		ControllerInfo.ProcessGear=0x20;				
	}
	else
	{
		ControllerInfo.ProcessGear=ControllerInfo.NowGear;		
	}
}
/***********************************************************************
�������ƣ�void GearToSolenoidValve(uint8_t gear,uint8_t status_brake)
��    �ܣ���λ���ŷ�������ת��
�����������λֵ
�����������
��дʱ�䣺2013.11.19
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/
void GearToSolenoidValve(uint8_t gear,uint8_t status_brake)
{
			if(gear/0x10==0)										//ǰ����
			{
				DOOUT7_AS(0);			//AS  �յ��ź�
				DOOUT6_RF(0);			//RF  �����ź�	
				switch(gear%0x10)
				{
					case 0x01:											//ǰ����--1��
					{
						if(status_brake==0)						//���ƶ��ź�
						{
							DOOUT1_M1(0);
							DOOUT2_M2(1);							
							DOOUT3_M3(1);
							DOOUT4_M4(1);							
						}
						else
						{
							DOOUT1_M1(0);
							DOOUT2_M2(1);							
							DOOUT3_M3(0);
							DOOUT4_M4(1);					
							
						}								
						break;						
					}
					case 0x02:											//ǰ����--2��
					{
						if(status_brake==0)						//���ƶ��ź�
						{
							DOOUT1_M1(1);
							DOOUT2_M2(1);							
							DOOUT3_M3(0);
							DOOUT4_M4(1);							
						}
						else
						{
							DOOUT1_M1(0);
							DOOUT2_M2(1);							
							DOOUT3_M3(0);
							DOOUT4_M4(1);					
							
						}							
						break;						
					}						
					case 0x03:											//ǰ����--3��
					{
						if(status_brake==0)						//���ƶ��ź�
						{
							DOOUT1_M1(0);
							DOOUT2_M2(0);							
							DOOUT3_M3(1);
							DOOUT4_M4(1);							
						}
						else
						{
							DOOUT1_M1(0);
							DOOUT2_M2(0);							
							DOOUT3_M3(0);
							DOOUT4_M4(1);					
							
						}			
					}
					case 0x04:											//ǰ����--4��
					{
						if(status_brake==0)						//���ƶ��ź�
						{
							DOOUT1_M1(1);
							DOOUT2_M2(0);							
							DOOUT3_M3(0);
							DOOUT4_M4(1);							
						}
						else
						{
							DOOUT1_M1(0);
							DOOUT2_M2(0);							
							DOOUT3_M3(0);
							DOOUT4_M4(1);					
							
						}					
						break;						
					}
					case 0x05:											//ǰ����--5��
					{
						if(status_brake==0)						//���ƶ��ź�
						{
							DOOUT1_M1(0);
							DOOUT2_M2(0);							
							DOOUT3_M3(1);
							DOOUT4_M4(0);							
						}
						else
						{
							DOOUT1_M1(0);
							DOOUT2_M2(0);							
							DOOUT3_M3(0);
							DOOUT4_M4(0);					
							
						}					
						break;						
					}					
					case 0x06:											//ǰ����--6��
					{
						if(status_brake==0)						//���ƶ��ź�
						{
							DOOUT1_M1(1);
							DOOUT2_M2(0);							
							DOOUT3_M3(0);
							DOOUT4_M4(0);							
						}
						else
						{
							DOOUT1_M1(0);
							DOOUT2_M2(0);							
							DOOUT3_M3(0);
							DOOUT4_M4(0);					
							
						}					
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
				DOOUT7_AS(0);			//AS  �յ��ź�
				DOOUT6_RF(1);			//RF  �����ź�	
				switch(gear%0x10)
				{					
					case 0x01:											//���˵�--1��
					{
						if(status_brake==0)						//���ƶ��ź�
						{
							DOOUT1_M1(1);
							DOOUT2_M2(1);							
							DOOUT3_M3(1);
							DOOUT4_M4(1);							
						}
						else
						{
							DOOUT1_M1(0);
							DOOUT2_M2(1);							
							DOOUT3_M3(0);
							DOOUT4_M4(1);					
							
						}						
						break;						
					}
					case 0x02:											//���˵�--2��
					{
						if(status_brake==0)						//���ƶ��ź�
						{
							DOOUT1_M1(1);
							DOOUT2_M2(0);							
							DOOUT3_M3(1);
							DOOUT4_M4(1);							
						}
						else
						{
							DOOUT1_M1(0);
							DOOUT2_M2(0);							
							DOOUT3_M3(0);
							DOOUT4_M4(1);							
						}						
						break;						
					}						
					case 0x03:											//���˵�--3��
					{
						if(status_brake==0)						//���ƶ��ź�
						{
							DOOUT1_M1(1);
							DOOUT2_M2(0);							
							DOOUT3_M3(1);
							DOOUT4_M4(0);							
						}
						else
						{
							DOOUT1_M1(0);
							DOOUT2_M2(0);							
							DOOUT3_M3(0);
							DOOUT4_M4(0);							
						}							
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
				DOOUT7_AS(1);			//AS  �յ��ź�
				DOOUT6_RF(0);			//RF  �����ź�	
				DOOUT1_M1(0);
				DOOUT2_M2(0);							
				DOOUT3_M3(0);
				DOOUT4_M4(0);		
			}			
	
}
