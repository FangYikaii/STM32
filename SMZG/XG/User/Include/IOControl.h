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
//���ֿ������ɼ�-DIIN

 #define     	DIIN1_M1_PIN											GPIO_Pin_8									//DIIN1 -- �ӻ���ѡ������ȡ���24V�ź�M1
 #define     	DIIN1_M1_GPIOX										GPIOE	
 #define     	DIIN1_M1_RCC_APB2Periph_GPIOX		  RCC_APB2Periph_GPIOE
 #define 			DIIN1_M1_Read											GPIO_ReadInputDataBit(DIIN1_M1_GPIOX, DIIN1_M1_PIN)

 #define     	DIIN2_M2_PIN											GPIO_Pin_7									//DIIN2 -- �ӻ���ѡ������ȡ���24V�ź�M2
 #define     	DIIN2_M2_GPIOX										GPIOE	
 #define     	DIIN2_M2_RCC_APB2Periph_GPIOX	  	RCC_APB2Periph_GPIOE
 #define 			DIIN2_M2_Read											GPIO_ReadInputDataBit(DIIN2_M2_GPIOX, DIIN2_M2_PIN)

 #define     	DIIN3_M3_PIN											GPIO_Pin_10									//DIIN3 -- �ӻ���ѡ������ȡ���24V�ź�M3
 #define     	DIIN3_M3_GPIOX										GPIOE	
 #define     	DIIN3_M3_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOE
 #define 			DIIN3_M3_Read											GPIO_ReadInputDataBit(DIIN3_M3_GPIOX, DIIN3_M3_PIN)

 #define     	DIIN4_M4_PIN											GPIO_Pin_9									//DIIN4 -- �ӻ���ѡ������ȡ���24V�ź�M4
 #define     	DIIN4_M4_GPIOX										GPIOE	
 #define     	DIIN4_M4_RCC_APB2Periph_GPIOX	  	RCC_APB2Periph_GPIOE
 #define 			DIIN4_M4_Read											GPIO_ReadInputDataBit(DIIN4_M4_GPIOX, DIIN4_M4_PIN)

 #define     	DIIN5_AS_PIN						  				GPIO_Pin_12								//DIIN5 -- �ӻ���ѡ������ȡ���24V�ź�AS
 #define     	DIIN5_AS_GPIOX										GPIOE	
 #define     	DIIN5_AS_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOE
 #define 			DIIN5_AS_Read											GPIO_ReadInputDataBit(DIIN5_AS_GPIOX, DIIN5_AS_PIN)

 #define     	DIIN6_RF_PIN											GPIO_Pin_11									//DIIN6 -- �ӻ���ѡ������ȡ���24V�ź�RF
 #define     	DIIN6_RF_GPIOX										GPIOE	
 #define     	DIIN6_RF_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOE
 #define 			DIIN6_RF_Read											GPIO_ReadInputDataBit(DIIN6_RF_GPIOX, DIIN6_RF_PIN)

 #define     	DIIN7_BR_PIN											GPIO_Pin_14								//DIIN7 -- ���ƶ����϶�ȡ�ƶ�����24V�ź�BR
 #define     	DIIN7_BR_GPIOX										GPIOE	
 #define     	DIIN7_BR_RCC_APB2Periph_GPIOX		  RCC_APB2Periph_GPIOE
 #define 			DIIN7_BR_Read											GPIO_ReadInputDataBit(DIIN7_BR_GPIOX, DIIN7_BR_PIN)

 #define     	DIIN8_XX_PIN											GPIO_Pin_13								//DIIN8 -- Ԥ��
 #define     	DIIN8_XX_GPIOX										GPIOE	
 #define     	DIIN8_XX_RCC_APB2Periph_GPIOX		  RCC_APB2Periph_GPIOE
 #define 			DIIN8_XX_Read											GPIO_ReadInputDataBit(DIIN7_BR_GPIOX, DIIN7_BR_PIN)

//************************************
//��ŷ��������-DOOUT

#define     	DOOUT1_M1_PIN													GPIO_Pin_0									//DOOUT1 -- ��ŷ�--M1
#define     	DOOUT1_M1_GPIOX												GPIOA	
#define     	DOOUT1_M1_RCC_APB2Periph_GPIOX	    	RCC_APB2Periph_GPIOA
#define 			DOOUT1_M1(x)   												((x) ? (GPIO_ResetBits(DOOUT1_M1_GPIOX, DOOUT1_M1_PIN)) : (GPIO_SetBits(DOOUT1_M1_GPIOX, DOOUT1_M1_PIN)))

#define     	DOOUT2_M2_PIN													GPIO_Pin_1									//DOOUT2 -- ��ŷ�--M2
#define     	DOOUT2_M2_GPIOX												GPIOA	
#define     	DOOUT2_M2_RCC_APB2Periph_GPIOX	    	RCC_APB2Periph_GPIOA
#define 			DOOUT2_M2(x)   												((x) ? (GPIO_ResetBits(DOOUT2_M2_GPIOX, DOOUT2_M2_PIN)) : (GPIO_SetBits(DOOUT2_M2_GPIOX, DOOUT2_M2_PIN)))

#define     	DOOUT3_M3_PIN													GPIO_Pin_2									//DOOUT3 -- ��ŷ�--M3
#define     	DOOUT3_M3_GPIOX												GPIOA	
#define     	DOOUT3_M3_RCC_APB2Periph_GPIOX	    	RCC_APB2Periph_GPIOA
#define 			DOOUT3_M3(x)   												((x) ? (GPIO_ResetBits(DOOUT3_M3_GPIOX, DOOUT3_M3_PIN)) : (GPIO_SetBits(DOOUT3_M3_GPIOX, DOOUT3_M3_PIN)))

#define     	DOOUT4_M4_PIN													GPIO_Pin_3									//DOOUT4 -- ��ŷ�--M4
#define     	DOOUT4_M4_GPIOX												GPIOA	
#define     	DOOUT4_M4_RCC_APB2Periph_GPIOX	    	RCC_APB2Periph_GPIOA
#define 			DOOUT4_M4(x)   												((x) ? (GPIO_ResetBits(DOOUT4_M4_GPIOX, DOOUT4_M4_PIN)) : (GPIO_SetBits(DOOUT4_M4_GPIOX, DOOUT4_M4_PIN)))

#define     	DOOUT5_BR_PIN													GPIO_Pin_6									//DOOUT5 -- ģ���ƶ��ź�BR
#define     	DOOUT5_BR_GPIOX												GPIOA	
#define     	DOOUT5_BR_RCC_APB2Periph_GPIOX	    	RCC_APB2Periph_GPIOA
#define 			DOOUT5_BR(x)   												((x) ? (GPIO_ResetBits(DOOUT5_BR_GPIOX, DOOUT5_BR_PIN)) : (GPIO_SetBits(DOOUT5_BR_GPIOX, DOOUT5_BR_PIN)))

#define     	DOOUT6_RF_PIN													GPIO_Pin_7									//DOOUT6 -- ���Ƶ���BF
#define     	DOOUT6_RF_GPIOX												GPIOA	
#define     	DOOUT6_RF_RCC_APB2Periph_GPIOX	    	RCC_APB2Periph_GPIOA
#define 			DOOUT6_RF(x)   												((x) ? (GPIO_ResetBits(DOOUT6_RF_GPIOX, DOOUT6_RF_PIN)) : (GPIO_SetBits(DOOUT6_RF_GPIOX, DOOUT6_RF_PIN)))

#define     	DOOUT7_AS_PIN													GPIO_Pin_0									//DOOUT7 -- ���������ź�AS
#define     	DOOUT7_AS_GPIOX												GPIOB	
#define     	DOOUT7_AS_RCC_APB2Periph_GPIOX	  		RCC_APB2Periph_GPIOB
#define 			DOOUT7_AS(x)   												((x) ? (GPIO_ResetBits(DOOUT7_AS_GPIOX, DOOUT7_AS_PIN)) : (GPIO_SetBits(DOOUT7_AS_GPIOX, DOOUT7_AS_PIN)))

#define     	DOOUT8_XX_PIN													GPIO_Pin_1									//DOOUT8 -- Ԥ��
#define     	DOOUT8_XX_GPIOX												GPIOB	
#define     	DOOUT8_XX_RCC_APB2Periph_GPIOX	    	RCC_APB2Periph_GPIOB
#define 			DOOUT8_XX(x)   												((x) ? (GPIO_ResetBits(DOOUT8_XX_GPIOX, DOOUT8_XX_PIN)) : (GPIO_SetBits(DOOUT8_XX_GPIOX, DOOUT8_XX_PIN)))


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
extern void GearScanVSDeal_HandShiftMode(void);								//��λɨ��ʹ������
extern void GearScanVSDeal_AutoShiftMode(void);

extern void IOControl_Init(void);   																//IO��ʼ��  
extern void ReadGearLine_Status(void);															//��ȡ���������ĵ�ƽ
extern void GearToSolenoidValve(uint8_t gear,uint8_t ststus_brake);			//��λ���ŷ�������ת��




//========================================
//<--Ԥ�������-->
#endif



