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

//************************************
//�ɼ��ź�IO
// 	
//	RCC_APB2PeriphClockCmd(DigIO_SCLK_RCC_APB2Periph_GPIOX, ENABLE);			//sclk				
//	GPIO_InitStructure.GPIO_Pin = DigIO_SCLK_PIN;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_Init(DigIO_SCLK_GPIOX, &GPIO_InitStructure);		
//	
//	RCC_APB2PeriphClockCmd(DigIO_RCLK_RCC_APB2Periph_GPIOX, ENABLE);			//rclk				
//	GPIO_InitStructure.GPIO_Pin = DigIO_RCLK_PIN;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_Init(DigIO_RCLK_GPIOX, &GPIO_InitStructure);		

//	RCC_APB2PeriphClockCmd(DigIO_DATA_RCC_APB2Periph_GPIOX, ENABLE);			//data				
//	GPIO_InitStructure.GPIO_Pin = DigIO_DATA_PIN;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			//GPIO_Mode_Out_PP GPIO_Mode_AF_PP --������� GPIO_Mode_AF_OD -- ��©���  
//	GPIO_Init(DigIO_DATA_GPIOX, &GPIO_InitStructure);		
//	
//	DigIO_DATA_OUT(0);		
//	DigIO_SCLK_OUT(0); 
//	DigIO_RCLK_OUT(0);	

	
	
//// 	RCC_APB2PeriphClockCmd(DigIO_IO1_RCC_APB2Periph_GPIOX, ENABLE);								
//// 	GPIO_InitStructure.GPIO_Pin = DigIO_IO1_PIN;
//// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
//// 	GPIO_Init(DigIO_IO1_GPIOX, &GPIO_InitStructure);

 	RCC_APB2PeriphClockCmd(Btn_Start_RCC_APB2Periph_GPIOX, ENABLE);							
 	GPIO_InitStructure.GPIO_Pin = Btn_Start_PIN;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
 	GPIO_Init(Btn_Start_GPIOX, &GPIO_InitStructure); 	
	
	
//////	RCC_APB2PeriphClockCmd(Btn_Start_RCC_APB2Periph_GPIOX, ENABLE);					
//////	GPIO_InitStructure.GPIO_Pin = Btn_Start_PIN;
//////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//////	GPIO_Init(Btn_Start_GPIOX, &GPIO_InitStructure);	
////	
////	
////	
 	RCC_APB2PeriphClockCmd(Btn_Stop_RCC_APB2Periph_GPIOX, ENABLE);								
 	GPIO_InitStructure.GPIO_Pin = Btn_Stop_PIN;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
 	GPIO_Init(Btn_Stop_GPIOX, &GPIO_InitStructure);
	
//// 	
//// 	RCC_APB2PeriphClockCmd(DigIO_IO4_RCC_APB2Periph_GPIOX, ENABLE);								
//// 	GPIO_InitStructure.GPIO_Pin = DigIO_IO4_PIN;
//// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
//// 	GPIO_Init(DigIO_IO4_GPIOX, &GPIO_InitStructure);
//// 	
//////************************************
//////��ŷ������ź�IO

////	RCC_APB2PeriphClockCmd(SolenoidValve_M1_RCC_APB2Periph_GPIOX, ENABLE);								 //��ŷ�--M1
////	GPIO_InitStructure.GPIO_Pin = SolenoidValve_M1_PIN;
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
////	GPIO_Init(SolenoidValve_M1_GPIOX, &GPIO_InitStructure);
////	
////	RCC_APB2PeriphClockCmd(SolenoidValve_M2_RCC_APB2Periph_GPIOX, ENABLE);								 //��ŷ�--M2
////	GPIO_InitStructure.GPIO_Pin = SolenoidValve_M2_PIN;
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
////	GPIO_Init(SolenoidValve_M2_GPIOX, &GPIO_InitStructure);
////	
////	RCC_APB2PeriphClockCmd(SolenoidValve_M3_RCC_APB2Periph_GPIOX, ENABLE);								 //��ŷ�--M3
////	GPIO_InitStructure.GPIO_Pin = SolenoidValve_M3_PIN;
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
////	GPIO_Init(SolenoidValve_M3_GPIOX, &GPIO_InitStructure);	

////	RCC_APB2PeriphClockCmd(SolenoidValve_M4_RCC_APB2Periph_GPIOX, ENABLE);								 //��ŷ�--M4
////	GPIO_InitStructure.GPIO_Pin = SolenoidValve_M4_PIN;
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
////	GPIO_Init(SolenoidValve_M4_GPIOX, &GPIO_InitStructure);	

////	RCC_APB2PeriphClockCmd(SolenoidValve_M5_RCC_APB2Periph_GPIOX, ENABLE);								 //��ŷ�--M5
////	GPIO_InitStructure.GPIO_Pin = SolenoidValve_M5_PIN;
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
////	GPIO_Init(SolenoidValve_M5_GPIOX, &GPIO_InitStructure);	


////	RCC_APB2PeriphClockCmd(SolenoidValve_M6_RCC_APB2Periph_GPIOX, ENABLE);								 //��ŷ�--M6
////	GPIO_InitStructure.GPIO_Pin = SolenoidValve_M6_PIN;
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
////	GPIO_Init(SolenoidValve_M6_GPIOX, &GPIO_InitStructure);
////	
////	RCC_APB2PeriphClockCmd(SolenoidValve_M7_RCC_APB2Periph_GPIOX, ENABLE);								 //��ŷ�--M7
////	GPIO_InitStructure.GPIO_Pin = SolenoidValve_M7_PIN;
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
////	GPIO_Init(SolenoidValve_M7_GPIOX, &GPIO_InitStructure);
////	
////	RCC_APB2PeriphClockCmd(SolenoidValve_M8_RCC_APB2Periph_GPIOX, ENABLE);								 //��ŷ�--M8
////	GPIO_InitStructure.GPIO_Pin = SolenoidValve_M8_PIN;
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
////	GPIO_Init(SolenoidValve_M8_GPIOX, &GPIO_InitStructure);	

////	RCC_APB2PeriphClockCmd(SolenoidValve_M9_RCC_APB2Periph_GPIOX, ENABLE);								 //��ŷ�--M9
////	GPIO_InitStructure.GPIO_Pin = SolenoidValve_M9_PIN;
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
////	GPIO_Init(SolenoidValve_M9_GPIOX, &GPIO_InitStructure);	

////	RCC_APB2PeriphClockCmd(SolenoidValve_M10_RCC_APB2Periph_GPIOX, ENABLE);								 //��ŷ�--M10
////	GPIO_InitStructure.GPIO_Pin = SolenoidValve_M10_PIN;
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
////	GPIO_Init(SolenoidValve_M10_GPIOX, &GPIO_InitStructure);	
////	

////	RCC_APB2PeriphClockCmd(SolenoidValve_M11_RCC_APB2Periph_GPIOX, ENABLE);								 //��ŷ�--M11
////	GPIO_InitStructure.GPIO_Pin = SolenoidValve_M11_PIN;
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
////	GPIO_Init(SolenoidValve_M11_GPIOX, &GPIO_InitStructure);
////	
////	RCC_APB2PeriphClockCmd(SolenoidValve_M12_RCC_APB2Periph_GPIOX, ENABLE);								 //��ŷ�--M12
////	GPIO_InitStructure.GPIO_Pin = SolenoidValve_M12_PIN;
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
////	GPIO_Init(SolenoidValve_M12_GPIOX, &GPIO_InitStructure);
////	
////	RCC_APB2PeriphClockCmd(SolenoidValve_M13_RCC_APB2Periph_GPIOX, ENABLE);								 //��ŷ�--M13
////	GPIO_InitStructure.GPIO_Pin = SolenoidValve_M13_PIN;
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
////	GPIO_Init(SolenoidValve_M13_GPIOX, &GPIO_InitStructure);	

////	RCC_APB2PeriphClockCmd(SolenoidValve_M14_RCC_APB2Periph_GPIOX, ENABLE);								 //��ŷ�--M14
////	GPIO_InitStructure.GPIO_Pin = SolenoidValve_M14_PIN;
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
////	GPIO_Init(SolenoidValve_M14_GPIOX, &GPIO_InitStructure);	

////	RCC_APB2PeriphClockCmd(SolenoidValve_M15_RCC_APB2Periph_GPIOX, ENABLE);								 //��ŷ�--M15
////	GPIO_InitStructure.GPIO_Pin = SolenoidValve_M15_PIN;
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
////	GPIO_Init(SolenoidValve_M15_GPIOX, &GPIO_InitStructure);	

////	RCC_APB2PeriphClockCmd(SolenoidValve_M16_RCC_APB2Periph_GPIOX, ENABLE);								 //��ŷ�--M16
////	GPIO_InitStructure.GPIO_Pin = SolenoidValve_M16_PIN;
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
////	GPIO_Init(SolenoidValve_M16_GPIOX, &GPIO_InitStructure);
////	
////	RCC_APB2PeriphClockCmd(SolenoidValve_M17_RCC_APB2Periph_GPIOX, ENABLE);								 //��ŷ�--M17
////	GPIO_InitStructure.GPIO_Pin = SolenoidValve_M17_PIN;
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
////	GPIO_Init(SolenoidValve_M17_GPIOX, &GPIO_InitStructure);
////	
////	RCC_APB2PeriphClockCmd(SolenoidValve_M18_RCC_APB2Periph_GPIOX, ENABLE);								 //��ŷ�--M18
////	GPIO_InitStructure.GPIO_Pin = SolenoidValve_M18_PIN;
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
////	GPIO_Init(SolenoidValve_M18_GPIOX, &GPIO_InitStructure);	

////	RCC_APB2PeriphClockCmd(SolenoidValve_M19_RCC_APB2Periph_GPIOX, ENABLE);								 //��ŷ�--M19
////	GPIO_InitStructure.GPIO_Pin = SolenoidValve_M19_PIN;
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
////	GPIO_Init(SolenoidValve_M19_GPIOX, &GPIO_InitStructure);	

////	RCC_APB2PeriphClockCmd(SolenoidValve_M20_RCC_APB2Periph_GPIOX, ENABLE);								 //��ŷ�--M20
////	GPIO_InitStructure.GPIO_Pin = SolenoidValve_M20_PIN;
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
////	GPIO_Init(SolenoidValve_M20_GPIOX, &GPIO_InitStructure);	
////	
////	SolenoidValve_M1(0);
////	SolenoidValve_M2(0);
////	SolenoidValve_M3(0);
////	SolenoidValve_M4(0);
////	SolenoidValve_M5(0);
////	SolenoidValve_M6(0);
////	SolenoidValve_M7(0);
////	SolenoidValve_M8(0);
////	SolenoidValve_M9(0);
////	SolenoidValve_M10(0);	
////	SolenoidValve_M11(0);
////	SolenoidValve_M12(0);
////	SolenoidValve_M13(0);
////	SolenoidValve_M14(0);
////	SolenoidValve_M15(0);
////	SolenoidValve_M16(0);
////	SolenoidValve_M17(0);
////	SolenoidValve_M18(0);
////	SolenoidValve_M19(0);
////	SolenoidValve_M20(0);		
////	
	
}

