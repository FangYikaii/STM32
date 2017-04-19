//========================================
//<--Ԥ���崦����ֹ�ظ�����-->
#ifndef _main_H
#define _main_H

//========================================
//ͷ�ļ�

//���ļ�

#include <stdio.h>
#include <stdlib.h>
#include <string.h>	
#include "stm32f10x.h"


//�û������ļ�

#include "TimerX.h"
#include "USARTx.h"
#include "USB_UDisk.h"
#include "IOControl.h"
#include "CANx.h"
#include "MAX7219.h"
#include "RTC.h"
#include "PCF8574.h"
#include "ADC.h"
#include "FrequencyCapture.h"

//========================================
//�궨��
#define 			TRUE 							1
#define 			FALSE							0

#define 			HandShiftMode			1
#define				AutoShiftMode			2

#define				GearScanT10ms			1
#define				GearScanT100ms		2

#define				Init_GearN1				0x21
#define				Init_Brakeinfo		0x00

//========================================
//�˿ڶ���




//========================================
//�����������
union FlagAF  
{ 
      uint8_t flagBits; 
      struct       
      { 
            uint8_t		Gear1Keep_Flag							:	1;			
						uint8_t		Gear2Keep_Flag							:	1;
						uint8_t		Bit2							:	1;				
						uint8_t		Bit3							:	1;	
						uint8_t		Bit4							:	1;		 			
						uint8_t		Bit5							:	1;	
						uint8_t		Bit6							:	1;				
						uint8_t		Bit7							:	1;
				
      } Bits; 
}; 
extern volatile union FlagAF flagA;



//========================================
//�����������
extern uint8_t ShiftModeStatus;						//����ģʽ
extern uint8_t ErrorMessage;							//������Ϣ

struct XGData 
{
	uint8_t  Startup_DelayTime;							//������ʱ��ʱ--s
	uint16_t BoomLargeCavityPressure;									//���۴�ǻѹ��
	uint16_t WorkingPumpPressure;											//������ѹ��
	uint16_t SteeringPumpPressure;										//ת���ѹ��
	uint16_t RotatingBucketLargeCavityPressure;				//ת����ǻѹ��
	uint16_t BoomSmallCavityPressure;									//����Сǻѹ��	
	uint16_t RotatingBucketSmallCavityPressure;				//ת��Сǻѹ��	
	uint16_t CANPressure[6];
	uint16_t CANSpeed[4];
	uint16_t PressureShow;
	uint16_t SpeedShow;

	
  uint8_t Throttle;												//���ſ���
	float SpeedRatio;												//ת�ٱ�
	uint16_t PumpSpeed;											//����ת��
	uint16_t TurbineSpeed;									//����ת��
	uint16_t RotationalSpeed;								//�����ת��
	
	uint8_t ChannelNo[2];										//ͨ��ѡ��: 0-- ѹ����ʾͨ��  1-- ת����ʾͨ��    ...
	uint16_t Function;											//������ʾ
	float GearRatio[4];											//��λ�ٱ�
  float DriveAxleRatio;										//�����Ŵ�����
};

extern struct XGData XG;


//========================================
//�����������





extern void delay(uint16_t k);     //��ʱ����

//========================================
//<--Ԥ�������-->
#endif
