//========================================
//<--Ԥ���崦����ֹ�ظ�����-->
#ifndef _PCF8574_H
#define _PCF8574_H

//========================================
//ͷ�ļ�



//========================================
//�궨��
#define 			DelayTime_PCF8574			10



//========================================
//�˿ڶ���

//***********************
//�˿��Ѹ��£�ע����ϵĵ�ַ���룬��000-111���ã�����2���壬1����Ϊ000������һ����Ϊ001.��������������  ���ٽ� 2016.06.27
//***********************

#define 			SCL_PCF8574_GPIOX													GPIOD
#define 			SDA_PCF8574_GPIOX												  GPIOD

#define 			SCL_PCF8574_RCC_APB2Periph_GPIOX					RCC_APB2Periph_GPIOD
#define 			SDA_PCF8574_RCC_APB2Periph_GPIOX					RCC_APB2Periph_GPIOD

#define 			SCL_PCF8574_GPIO_PIN											GPIO_Pin_12
#define 			SDA_PCF8574_GPIO_PIN											GPIO_Pin_11


#define 			SCL_PCF8574(x)   													((x) ? (GPIO_SetBits(SCL_PCF8574_GPIOX, SCL_PCF8574_GPIO_PIN)) : (GPIO_ResetBits(SCL_PCF8574_GPIOX, SCL_PCF8574_GPIO_PIN)))
#define 			SDA_PCF8574(x)    												((x) ? (GPIO_SetBits(SDA_PCF8574_GPIOX, SDA_PCF8574_GPIO_PIN)) : (GPIO_ResetBits(SDA_PCF8574_GPIOX, SDA_PCF8574_GPIO_PIN)))

#define 			SCL_Read_PCF8574												GPIO_ReadInputDataBit(SCL_PCF8574_GPIOX, SCL_PCF8574_GPIO_PIN)
#define 			SDA_Read_PCF8574												GPIO_ReadInputDataBit(SDA_PCF8574_GPIOX, SDA_PCF8574_GPIO_PIN)


//========================================
//�����������
extern uint8_t KeyValue_PCF8574;						//PCF8574����ɨ��ֵ

union FlagPCF8574  
{ 
      uint8_t flagBits; 
      struct       
      { 
            uint8_t		KeyScan_Flag			:	1;				//ɨ��ɨ���־
						uint8_t		Bit1							:	1;
						uint8_t		Bit2							:	1;				
						uint8_t		Bit3							:	1;	
						uint8_t		Bit4							:	1;		 			
						uint8_t		Bit5							:	1;	
						uint8_t		Bit6							:	1;				
						uint8_t		Bit7							:	1;
				
      } Bits; 
}; 
extern volatile union FlagPCF8574 PCF8574;

//========================================
//�����������
extern void Init_PCF8574(void);																	//PCF8574�ĳ�ʼ������
extern void I2C_WriteData_PCF8574(uint8_t addr, uint8_t data);			//PCF8574��I2Cд���ݳ���
extern uint8_t I2C_RecData_PCF8574(uint8_t addr);										//PCF8574��I2C�����ݳ���

extern void KeyScan_PCF8574(void);															//PCF8574�ļ���ɨ�����



//========================================
//<--Ԥ�������-->
#endif



