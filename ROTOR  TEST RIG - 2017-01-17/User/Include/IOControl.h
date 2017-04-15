//========================================
//<--Ԥ���崦����ֹ�ظ�����-->
#ifndef _IOControl_H
#define _IOControl_H

//========================================
//ͷ�ļ�


//========================================
//�궨��



//========================================
//�˿ڶ���

//************************************
//��λ�ɼ��ź�IO(6·)
//PE7 PE8 PE9 PE10 PE11 PE12
//�ܽš��˿ڡ�����ʱ�ӡ���GPIO�����ƽ--GPIO_ReadInputDataBit

 #define     	GearLine_Brown_PIN											GPIO_Pin_8									//����--3 ��ɫ
 #define     	GearLine_Brown_GPIOX										GPIOE	
 #define     	GearLine_Brown_RCC_APB2Periph_GPIOX		  RCC_APB2Periph_GPIOE
 #define 			GearLine_Brown_Read											!GPIO_ReadInputDataBit(GearLine_Brown_GPIOX, GearLine_Brown_PIN)

 #define     	GearLine_Purple_PIN											GPIO_Pin_7									//����--4 ��ɫ
 #define     	GearLine_Purple_GPIOX										GPIOE	
 #define     	GearLine_Purple_RCC_APB2Periph_GPIOX	  RCC_APB2Periph_GPIOE
 #define 			GearLine_Purple_Read										!GPIO_ReadInputDataBit(GearLine_Purple_GPIOX, GearLine_Purple_PIN)

 #define     	GearLine_White_PIN											GPIO_Pin_10									//����--5 ��ɫ
 #define     	GearLine_White_GPIOX										GPIOE	
 #define     	GearLine_White_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOE
 #define 			GearLine_White_Read											!GPIO_ReadInputDataBit(GearLine_White_GPIOX, GearLine_White_PIN)

 #define     	GearLine_Yellow_PIN											GPIO_Pin_9									//����--6 ��ɫ
 #define     	GearLine_Yellow_GPIOX										GPIOE	
 #define     	GearLine_Yellow_RCC_APB2Periph_GPIOX	  RCC_APB2Periph_GPIOE
 #define 			GearLine_Yellow_Read										!GPIO_ReadInputDataBit(GearLine_Yellow_GPIOX, GearLine_Yellow_PIN)

 #define     	GearLine_Blue_PIN						  					GPIO_Pin_12									//����--7 ��ɫ
 #define     	GearLine_Blue_GPIOX										  GPIOE	
 #define     	GearLine_Blue_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOE
 #define 			GearLine_Blue_Read											!GPIO_ReadInputDataBit(GearLine_Blue_GPIOX, GearLine_Blue_PIN)

 #define     	GearLine_Green_PIN											GPIO_Pin_11									//����--8 ��ɫ
 #define     	GearLine_Green_GPIOX										GPIOE	
 #define     	GearLine_Green_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOE
 #define 			GearLine_Green_Read											!GPIO_ReadInputDataBit(GearLine_Green_GPIOX, GearLine_Green_PIN)


//******************************************************
//******************************************************

//   �ر�ע�⣬���ڵ�·���뷽���������Ե�ƽҪ�෴����

//******************************************************
//******************************************************

//************************************
//��ŷ������ź�IO(5·)
//PA0 PA1 PA2 PA3 PA6
//�ܽš��˿ڡ�����ʱ�ӡ�[���Ƶ�ƽ--GPIO_ResetBits--GPIO_SetBits]

#define     	SolenoidValve_M1_PIN											GPIO_Pin_0									//��ŷ�--M1 ��ɫ
#define     	SolenoidValve_M1_GPIOX										GPIOA	
#define     	SolenoidValve_M1_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOA
#define 			SolenoidValve_M1(x)   											((x) ? (GPIO_ResetBits(SolenoidValve_M1_GPIOX, SolenoidValve_M1_PIN)) : (GPIO_ResetBits(SolenoidValve_M1_GPIOX, SolenoidValve_M1_PIN)))

#define     	SolenoidValve_M2_PIN											GPIO_Pin_1									//��ŷ�--M2 ��ɫ
#define     	SolenoidValve_M2_GPIOX										GPIOA	
#define     	SolenoidValve_M2_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOA
#define 			SolenoidValve_M2(x)   											((x) ? (GPIO_ResetBits(SolenoidValve_M2_GPIOX, SolenoidValve_M2_PIN)) : (GPIO_SetBits(SolenoidValve_M2_GPIOX, SolenoidValve_M2_PIN)))

#define     	SolenoidValve_M3_PIN											GPIO_Pin_2									//��ŷ�--M3 ��ɫ
#define     	SolenoidValve_M3_GPIOX										GPIOA	
#define     	SolenoidValve_M3_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOA
#define 			SolenoidValve_M3(x)   											((x) ? (GPIO_ResetBits(SolenoidValve_M3_GPIOX, SolenoidValve_M3_PIN)) : (GPIO_SetBits(SolenoidValve_M3_GPIOX, SolenoidValve_M3_PIN)))

#define     	SolenoidValve_M4_PIN											GPIO_Pin_3									//��ŷ�--M4 ��ɫ
#define     	SolenoidValve_M4_GPIOX										GPIOA	
#define     	SolenoidValve_M4_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOA
#define 			SolenoidValve_M4(x)   											((x) ? (GPIO_ResetBits(SolenoidValve_M4_GPIOX, SolenoidValve_M4_PIN)) : (GPIO_SetBits(SolenoidValve_M4_GPIOX, SolenoidValve_M4_PIN)))

#define     	SolenoidValve_M5_PIN											GPIO_Pin_6									//��ŷ�--M5 ��ɫ
#define     	SolenoidValve_M5_GPIOX										GPIOA	
#define     	SolenoidValve_M5_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOA
#define 			SolenoidValve_M5(x)   											((x) ? (GPIO_ResetBits(SolenoidValve_M5_GPIOX, SolenoidValve_M5_PIN)) : (GPIO_SetBits(SolenoidValve_M5_GPIOX, SolenoidValve_M5_PIN)))


// //************************************
// //�ƶ����Ʋɼ���ϢIO(1·PE14)
//�ܽš��˿ڡ�����ʱ�ӡ�����ƽ--GPIO_ReadInputDataBit

 #define     	BrakeControl_PIN													GPIO_Pin_14									//�ƶ�����--��ɫ
 #define     	BrakeControl_GPIOX												GPIOE	
 #define     	BrakeControl_RCC_APB2Periph_GPIOX		  		RCC_APB2Periph_GPIOE
 #define 			BrakeControl_Read													GPIO_ReadInputDataBit(BrakeControl_GPIOX, BrakeControl_PIN)



//************************************
//�յ����������뵹����ʾ�ƿ�����ϢIO(2·)
//PA7 PB0
//�ܽš��˿ڡ�����ʱ�ӡ�[���Ƶ�ƽ--GPIO_ResetBits--GPIO_SetBits]

#define     	AsternAlarmLED_PIN												GPIO_Pin_7									//������ʾ��--��ɫ--j2
#define     	AsternAlarmLED_GPIOX											GPIOA	
#define     	AsternAlarmLED_RCC_APB2Periph_GPIOX	    	RCC_APB2Periph_GPIOA
#define 			AsternAlarmLED(x)   											((x) ? (GPIO_ResetBits(AsternAlarmLED_GPIOX, AsternAlarmLED_PIN)) : (GPIO_SetBits(AsternAlarmLED_GPIOX, AsternAlarmLED_PIN)))

#define     	NeutralStartInterlock_PIN											GPIO_Pin_0							//�յ���������--��ɫ--J1
#define     	NeutralStartInterlock_GPIOX										GPIOB	
#define     	NeutralStartInterlock_RCC_APB2Periph_GPIOX	  RCC_APB2Periph_GPIOB
#define 			NeutralStartInterlock(x)   										((x) ? (GPIO_ResetBits(NeutralStartInterlock_GPIOX, NeutralStartInterlock_PIN)) : (GPIO_SetBits(NeutralStartInterlock_GPIOX, NeutralStartInterlock_PIN)))

//************************************
//Ԥ��IO
#define     	ReservedIO_PIN														GPIO_Pin_1									//
#define     	ReservedIO_GPIOX													GPIOB	
#define     	ReservedIO_RCC_APB2Periph_GPIOX	    			RCC_APB2Periph_GPIOB
#define 			ReservedIO(x)   													((x) ? (GPIO_ResetBits(ReservedIO_GPIOX, ReservedIO_PIN)) : (GPIO_SetBits(ReservedIO_GPIOX, ReservedIO_PIN)))


//========================================
//�����������
struct ControllerData				
{
	uint8_t ScanTimeMode;											//��λɨ��ʱ��ģʽ				
	uint8_t NowGear;													//��ǰ��λ��Ϣ	-- ��ȡ���
	uint8_t NowBrake;													//��ǰɲ��״̬	-- ��ȡ���
	uint8_t GoalGear;													//Ŀ�굲λ			-- ����ֵ
	uint8_t ProcessGear;											//���̵�λ      -- ����ֵ
	uint8_t SuggestGear;											//�Ƽ���λ      -- Ԥ��ֵ
	uint8_t	gearinfo;													//��λ					-- ������
	uint8_t brakeinfo;												//�ƶ��ź�			-- ������
	uint8_t gearCGcount;											//��λ�仯��������
	uint8_t brakeCGcount;											//��λ�仯��������
	
};
extern struct ControllerData	ControllerInfo;

union FlagController  
{ 
      uint8_t flagBits; 
      struct       
      { 
            uint8_t 		gearchange		:	1;
						uint8_t 		brakechange		:	1;				
						uint8_t 		KDchange    	:	1;
						uint8_t 		StartUpFromNx	:	1;
						uint8_t 		ScanTimeFlag	:	1;     			
						uint8_t 		KDScan_Flag  	:	1;
						uint8_t 		Bit6		:	1;				
						uint8_t 		Bit7		:	1;		
 						
      } Bits; 
}; 
extern volatile union FlagController flagctrl;


//========================================
//�����������

extern void StartUpGearDeal(void);							//����ʱ�̵�λ�������
extern void GearScanVSDeal(void);								//��λɨ��ʹ������
extern void IOControl_Init(void);   																//IO��ʼ��  
extern uint8_t ReadGearLine_Status(void);															//��ȡ���������ĵ�ƽ
extern void GearToSolenoidValve(uint8_t gear,uint8_t ststus_brake);			//��λ���ŷ�������ת��

//========================================
//<--Ԥ�������-->
#endif
