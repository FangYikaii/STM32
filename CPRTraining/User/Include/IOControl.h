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

//***********************
//�˿��Ѹ���  ���ٽ� 2016.06.27
//***********************



 #define     	Btn_Start_PIN											GPIO_Pin_13									//��ʼ
 #define     	Btn_Start_GPIOX										GPIOD	
 #define     	Btn_Start_RCC_APB2Periph_GPIOX	  RCC_APB2Periph_GPIOD
 #define 			Btn_Start_Read										GPIO_ReadInputDataBit(Btn_Start_GPIOX, Btn_Start_PIN)
 
 #define 			Btn_Start_OUT(x)   							 ((x) ? (GPIO_SetBits(Btn_Start_GPIOX, Btn_Start_PIN)) : (GPIO_ResetBits(Btn_Start_GPIOX, Btn_Start_PIN)))
 
 
 

 #define     	Btn_Stop_PIN											GPIO_Pin_14									//��ͣ
 #define     	Btn_Stop_GPIOX										GPIOD	
 #define     	Btn_Stop_RCC_APB2Periph_GPIOX	  	RCC_APB2Periph_GPIOD
 #define 			Btn_Stop_Read											GPIO_ReadInputDataBit(Btn_Stop_GPIOX, Btn_Stop_PIN)





 #define     	DigIO_SCLK_PIN											GPIO_Pin_11									//DigIO_SCLK
 #define     	DigIO_SCLK_GPIOX										GPIOE	
 #define     	DigIO_SCLK_RCC_APB2Periph_GPIOX	  RCC_APB2Periph_GPIOE
 #define 			DigIO_SCLK_Read										GPIO_ReadInputDataBit(DigIO_SCLK_GPIOX, DigIO_SCLK_PIN)
 
 #define 			DigIO_SCLK_OUT(x)   							 ((x) ? (GPIO_SetBits(DigIO_SCLK_GPIOX, DigIO_SCLK_PIN)) : (GPIO_ResetBits(DigIO_SCLK_GPIOX, DigIO_SCLK_PIN)))
 
 #define     	DigIO_RCLK_PIN											GPIO_Pin_13									//DigIO_RCLK
 #define     	DigIO_RCLK_GPIOX										GPIOE	
 #define     	DigIO_RCLK_RCC_APB2Periph_GPIOX	  	RCC_APB2Periph_GPIOE
 #define 			DigIO_RCLK_Read											GPIO_ReadInputDataBit(DigIO_RCLK_GPIOX, DigIO_RCLK_PIN)
 
 #define 			DigIO_RCLK_OUT(x)   							 ((x) ? (GPIO_SetBits(DigIO_RCLK_GPIOX, DigIO_RCLK_PIN)) : (GPIO_ResetBits(DigIO_RCLK_GPIOX, DigIO_RCLK_PIN)))
 
 #define     	DigIO_DATA_PIN											GPIO_Pin_15									//DigIO_DATA
 #define     	DigIO_DATA_GPIOX										GPIOE	
 #define     	DigIO_DATA_RCC_APB2Periph_GPIOX	  	RCC_APB2Periph_GPIOE
 #define 			DigIO_DATA_Read											GPIO_ReadInputDataBit(DigIO_DATA_GPIOX, DigIO_DATA_PIN)
 
 #define 			DigIO_DATA_OUT(x)   							 ((x) ? (GPIO_SetBits(DigIO_DATA_GPIOX, DigIO_DATA_PIN)) : (GPIO_ResetBits(DigIO_DATA_GPIOX, DigIO_DATA_PIN)))
 





//************************************
//�ɼ��ź�IO

 #define     	DigIO_IO1_PIN											GPIO_Pin_8									//����
 #define     	DigIO_IO1_GPIOX										GPIOE	
 #define     	DigIO_IO1_RCC_APB2Periph_GPIOX		RCC_APB2Periph_GPIOE
 #define 			DigIO_IO1_Read										GPIO_ReadInputDataBit(DigIO_IO1_GPIOX, DigIO_IO1_PIN)




 
 
 
 #define     	DigIO_IO4_PIN											GPIO_Pin_11									//DigIO_IO4
 #define     	DigIO_IO4_GPIOX										GPIOE	
 #define     	DigIO_IO4_RCC_APB2Periph_GPIOX	  RCC_APB2Periph_GPIOE
 #define 			DigIO_IO4_Read										GPIO_ReadInputDataBit(DigIO_IO4_GPIOX, DigIO_IO4_PIN)
 
 
//******************************************************
//******************************************************

//   �ر�ע�⣬���ڵ�·���뷽���������Ե�ƽҪ�෴����

//******************************************************
//******************************************************

//************************************
//��ŷ������ź�IO

#define     	SolenoidValve_M1_PIN											GPIO_Pin_10									//��ŷ�--M1 
#define     	SolenoidValve_M1_GPIOX										GPIOA	
#define     	SolenoidValve_M1_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOA
#define 			SolenoidValve_M1(x)   										((x) ? (GPIO_SetBits(SolenoidValve_M1_GPIOX, SolenoidValve_M1_PIN)) : (GPIO_ResetBits(SolenoidValve_M1_GPIOX, SolenoidValve_M1_PIN)))

#define     	SolenoidValve_M2_PIN											GPIO_Pin_9									//��ŷ�--M2 
#define     	SolenoidValve_M2_GPIOX										GPIOA	
#define     	SolenoidValve_M2_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOA
#define 			SolenoidValve_M2(x)   										((x) ? (GPIO_SetBits(SolenoidValve_M2_GPIOX, SolenoidValve_M2_PIN)) : (GPIO_ResetBits(SolenoidValve_M2_GPIOX, SolenoidValve_M2_PIN)))

#define     	SolenoidValve_M3_PIN											GPIO_Pin_8									//��ŷ�--M3 
#define     	SolenoidValve_M3_GPIOX										GPIOA	
#define     	SolenoidValve_M3_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOA
#define 			SolenoidValve_M3(x)   										((x) ? (GPIO_SetBits(SolenoidValve_M3_GPIOX, SolenoidValve_M3_PIN)) : (GPIO_ResetBits(SolenoidValve_M3_GPIOX, SolenoidValve_M3_PIN)))

#define     	SolenoidValve_M4_PIN											GPIO_Pin_9									//��ŷ�--M4 
#define     	SolenoidValve_M4_GPIOX										GPIOC
#define     	SolenoidValve_M4_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOC
#define 			SolenoidValve_M4(x)   										((x) ? (GPIO_SetBits(SolenoidValve_M4_GPIOX, SolenoidValve_M4_PIN)) : (GPIO_ResetBits(SolenoidValve_M4_GPIOX, SolenoidValve_M4_PIN)))

#define     	SolenoidValve_M5_PIN											GPIO_Pin_8									//��ŷ�--M5 
#define     	SolenoidValve_M5_GPIOX										GPIOC	
#define     	SolenoidValve_M5_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOC
#define 			SolenoidValve_M5(x)   										((x) ? (GPIO_SetBits(SolenoidValve_M5_GPIOX, SolenoidValve_M5_PIN)) : (GPIO_ResetBits(SolenoidValve_M5_GPIOX, SolenoidValve_M5_PIN)))

#define     	SolenoidValve_M6_PIN											GPIO_Pin_7									//��ŷ�--M6 
#define     	SolenoidValve_M6_GPIOX										GPIOC	
#define     	SolenoidValve_M6_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOC
#define 			SolenoidValve_M6(x)   										((x) ? (GPIO_SetBits(SolenoidValve_M6_GPIOX, SolenoidValve_M6_PIN)) : (GPIO_ResetBits(SolenoidValve_M6_GPIOX, SolenoidValve_M6_PIN)))

#define     	SolenoidValve_M7_PIN											GPIO_Pin_6									//��ŷ�--M7 
#define     	SolenoidValve_M7_GPIOX										GPIOC	
#define     	SolenoidValve_M7_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOC
#define 			SolenoidValve_M7(x)   										((x) ? (GPIO_SetBits(SolenoidValve_M7_GPIOX, SolenoidValve_M7_PIN)) : (GPIO_ResetBits(SolenoidValve_M7_GPIOX, SolenoidValve_M7_PIN)))

#define     	SolenoidValve_M8_PIN											GPIO_Pin_15									//��ŷ�--M8 
#define     	SolenoidValve_M8_GPIOX										GPIOD	
#define     	SolenoidValve_M8_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOD
#define 			SolenoidValve_M8(x)   										((x) ? (GPIO_SetBits(SolenoidValve_M8_GPIOX, SolenoidValve_M8_PIN)) : (GPIO_ResetBits(SolenoidValve_M8_GPIOX, SolenoidValve_M8_PIN)))

#define     	SolenoidValve_M9_PIN											GPIO_Pin_14									//��ŷ�--M9
#define     	SolenoidValve_M9_GPIOX										GPIOD	
#define     	SolenoidValve_M9_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOD
#define 			SolenoidValve_M9(x)   										((x) ? (GPIO_SetBits(SolenoidValve_M9_GPIOX, SolenoidValve_M9_PIN)) : (GPIO_ResetBits(SolenoidValve_M9_GPIOX, SolenoidValve_M9_PIN)))

#define     	SolenoidValve_M10_PIN											GPIO_Pin_13									//��ŷ�--M10 
#define     	SolenoidValve_M10_GPIOX										GPIOD	
#define     	SolenoidValve_M10_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOD
#define 			SolenoidValve_M10(x)   										((x) ? (GPIO_SetBits(SolenoidValve_M10_GPIOX, SolenoidValve_M10_PIN)) : (GPIO_ResetBits(SolenoidValve_M10_GPIOX, SolenoidValve_M10_PIN)))

#define     	SolenoidValve_M11_PIN											GPIO_Pin_12									//��ŷ�--M11 
#define     	SolenoidValve_M11_GPIOX										GPIOD
#define     	SolenoidValve_M11_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOD
#define 			SolenoidValve_M11(x)   										((x) ? (GPIO_SetBits(SolenoidValve_M11_GPIOX, SolenoidValve_M11_PIN)) : (GPIO_ResetBits(SolenoidValve_M11_GPIOX, SolenoidValve_M11_PIN)))

#define     	SolenoidValve_M12_PIN											GPIO_Pin_11									//��ŷ�--M12 
#define     	SolenoidValve_M12_GPIOX										GPIOD
#define     	SolenoidValve_M12_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOD
#define 			SolenoidValve_M12(x)   										((x) ? (GPIO_SetBits(SolenoidValve_M12_GPIOX, SolenoidValve_M12_PIN)) : (GPIO_ResetBits(SolenoidValve_M12_GPIOX, SolenoidValve_M12_PIN)))

#define     	SolenoidValve_M13_PIN											GPIO_Pin_10									//��ŷ�--M13 
#define     	SolenoidValve_M13_GPIOX										GPIOD
#define     	SolenoidValve_M13_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOD
#define 			SolenoidValve_M13(x)   										((x) ? (GPIO_SetBits(SolenoidValve_M13_GPIOX, SolenoidValve_M13_PIN)) : (GPIO_ResetBits(SolenoidValve_M13_GPIOX, SolenoidValve_M13_PIN)))

#define     	SolenoidValve_M14_PIN											GPIO_Pin_9									//��ŷ�--M14 
#define     	SolenoidValve_M14_GPIOX										GPIOD	
#define     	SolenoidValve_M14_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOD
#define 			SolenoidValve_M14(x)   										((x) ? (GPIO_SetBits(SolenoidValve_M14_GPIOX, SolenoidValve_M14_PIN)) : (GPIO_ResetBits(SolenoidValve_M14_GPIOX, SolenoidValve_M14_PIN)))

#define     	SolenoidValve_M15_PIN											GPIO_Pin_8									//��ŷ�--M15 
#define     	SolenoidValve_M15_GPIOX										GPIOD	
#define     	SolenoidValve_M15_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOD
#define 			SolenoidValve_M15(x)   										((x) ? (GPIO_SetBits(SolenoidValve_M15_GPIOX, SolenoidValve_M15_PIN)) : (GPIO_ResetBits(SolenoidValve_M15_GPIOX, SolenoidValve_M15_PIN)))

#define     	SolenoidValve_M16_PIN											GPIO_Pin_15									//��ŷ�--M16 
#define     	SolenoidValve_M16_GPIOX										GPIOB	
#define     	SolenoidValve_M16_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOB
#define 			SolenoidValve_M16(x)   										((x) ? (GPIO_SetBits(SolenoidValve_M16_GPIOX, SolenoidValve_M16_PIN)) : (GPIO_ResetBits(SolenoidValve_M16_GPIOX, SolenoidValve_M16_PIN)))

#define     	SolenoidValve_M17_PIN											GPIO_Pin_14									//��ŷ�--M17 
#define     	SolenoidValve_M17_GPIOX										GPIOB
#define     	SolenoidValve_M17_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOB
#define 			SolenoidValve_M17(x)   										((x) ? (GPIO_SetBits(SolenoidValve_M17_GPIOX, SolenoidValve_M17_PIN)) : (GPIO_ResetBits(SolenoidValve_M17_GPIOX, SolenoidValve_M17_PIN)))

#define     	SolenoidValve_M18_PIN											GPIO_Pin_13									//��ŷ�--M18 
#define     	SolenoidValve_M18_GPIOX										GPIOB
#define     	SolenoidValve_M18_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOB
#define 			SolenoidValve_M18(x)   										((x) ? (GPIO_SetBits(SolenoidValve_M18_GPIOX, SolenoidValve_M18_PIN)) : (GPIO_ResetBits(SolenoidValve_M18_GPIOX, SolenoidValve_M18_PIN)))

#define     	SolenoidValve_M19_PIN											GPIO_Pin_12									//��ŷ�--M19 
#define     	SolenoidValve_M19_GPIOX										GPIOB	
#define     	SolenoidValve_M19_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOB
#define 			SolenoidValve_M19(x)   										((x) ? (GPIO_SetBits(SolenoidValve_M19_GPIOX, SolenoidValve_M19_PIN)) : (GPIO_ResetBits(SolenoidValve_M19_GPIOX, SolenoidValve_M19_PIN)))

#define     	SolenoidValve_M20_PIN											GPIO_Pin_11									//��ŷ�--M20
#define     	SolenoidValve_M20_GPIOX										GPIOB
#define     	SolenoidValve_M20_RCC_APB2Periph_GPIOX	    RCC_APB2Periph_GPIOB
#define 			SolenoidValve_M20(x)   										((x) ? (GPIO_SetBits(SolenoidValve_M20_GPIOX, SolenoidValve_M20_PIN)) : (GPIO_ResetBits(SolenoidValve_M20_GPIOX, SolenoidValve_M20_PIN)))




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



