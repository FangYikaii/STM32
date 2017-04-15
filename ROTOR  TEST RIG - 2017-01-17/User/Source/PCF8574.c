/*
����˵��:  	
            PCF8574 IO��չ��·��Ƴ��� --- STM32F107VCT 
						
						��ַ(0x70) -- LED��ʾ���Ƶ�ַ
						��ַ(0x72) -- ������ȡ���Ƶ�ַ
						��ַ(0x7A) -- ��ŷ�����оƬ����źŶ�ȡ��ַ(δ��)
						
						
ע�����						
						1��PCF8574 ��SCL��SDA��INT �ȶ˿���Ҫ��10K���������������д�����						
						2��PCF8574 �ж����÷���EXTI.C�ڣ�ע��IO��Ҳ��Ҫ��ʼ����
						3��PCF8574 �ж�ɨ�辭���������⣬����ʹ��ѭ��ɨ�裬�����������

�˿�ʹ��:		��Doc�ļ�����˵��
������:     FangYIkaii 
����ʱ��:   2017-01-20 
�޸�ʱ��:   2017-01-20
*/
/*
##I2C-EEPROM�Ķ�д����ʵ�飺�볣����EEPROMоƬAT2402Ϊ�� �������ROM##
I2C(Inter-Integrated Circuit)���ɵ�·���ߣ���������SDA��ʱ��SCL���ɵĴ������ߣ����Է��ͺͽ������ݣ��ٶȿ��Դﵽ400Kbs
1.ÿ�����ӵ����ߵ��豸����ͨ��Ψһ���豸��ַ��������
2.����8λ˫�����ݴ��䣬λ�����±�׼ģʽ���Դﵽ100kbs/s,����ģʽ400kbs/s,����ģʽ3.4Mb/s
3.���߳����7.6m��Ƭ���˲����������ӿ����������
4.������7λ��ַ�����128���豸��������ϵͳ��һ�������Ͽ���ͬʱ�ж���������ڣ�ͨ����ͻ������ʱ��ֹ���ݲ����ƻ�

����״̬��
��ʼ�źţ�SCL�ߵ�ƽ�ڼ䣬SDA�ɸߵ�ƽ��͵�ƽ���䣬��ʼ��������
�����źţ�SCL�ߵ�ƽ�ڼ䣬SDA�ɵ͵�ƽ��ߵ�ƽ���䣬������������
Ӧ���źţ��������ݵ�IC����8bit���ݺ��������ݵ�IC�����ض��ĵ͵�ƽ���壬��ʾ�յ����ݣ���δ�յ�Ӧ���źţ��ж��ܿص�Ԫ����

STM32F107��I2C�ӿ��������£�
1.оƬ����2��I2C���߽ӿڣ�I2C1��I2C2
2.�ܹ����������ģʽ���ģʽ��֧�ֱ�׼ģʽ100kbs/s�Ϳ���ģʽ400kbs/s,��֧��7λѰַ
3.����Ӳ��crc����У���������շ��Ϳ���ͨ��DMA

SCL:ʱ��ΪI2CЭ���е�ʱ���źţ���I2C�ӿڸ���ʱ�ӿ��ƼĴ���CCR���ƣ����ƵĲ�����ҪΪʱ��Ƶ��
SDA:ͨ��һϵ�����ݿ��Ƽܹ����ڽ�Ҫ���͵����ݵĻ����ϣ�����Э����Ӹ�����ʼ�źš�Ӧ���źš���ַ�źţ�ʵ����I2CЭ�鷢�ͳ�ȥ
*/
/*
<----PCF8574 ��ַ ����   ---->
            ��ַ    ����
��ʼ��     0x70      0x00
������     0x73
   

<----PCF8574 ���̼�ֵ ����  ---->
S1  -- 0xFE --  S9
S2  -- 0xFD --  S10
S3  -- 0xFB --  S11	
S4  -- 0xF7 --  S12

S5  -- 0xEF --  S13
S6  -- 0xDF --  S14
S7  -- 0xBF --  S15	
S8  -- 0x7F --  S16
*/

//******************************************
//ͷ�ļ�
#include "main.h"

//******************************************
//��������
uint8_t KeyValue_PCF8574;								//PCF8574����ɨ��ֵ
volatile union FlagPCF8574 PCF8574;

//******************************************
//��������
void Init_PCF8574(void);																	//PCF8574�ĳ�ʼ������

void I2C_Start_PCF8574(void);															//PCF8574��I2C��ʼ�ź�
void I2C_Stop_PCF8574(void);															//PCF8574��I2Cֹͣ�ź�
void I2C_NOAck_PCF8574(void);															//PCF8574��I2C����Ӧ����Ϣ
void I2C_Ack_PCF8574(void);																//PCF8574��I2C����Ӧ����Ϣ
void I2C_Write1Byte_PCF8574(uint8_t data);									//PCF8574��I2Cдһ���ֽڳ���
uint8_t I2C_Rec1Byte_PCF8574(void);													//PCF8574��I2C����һ���ֽڳ���

void I2C_WriteData_PCF8574(uint8_t addr, uint8_t data);				//PCF8574��I2Cд���ݳ���
uint8_t I2C_RecData_PCF8574(uint8_t addr);										//PCF8574��I2C�����ݳ���
void KeyScan_PCF8574(void);																//PCF8574�ļ���ɨ�����

//******************************************
//��ģ�麯��


/***********************************************************************
�������ƣ�void Init_PCF8574(void)
��    �ܣ�PCF8574�ĳ�ʼ������
���������
���������
��дʱ�䣺2017.01.20
�� д �ˣ�FangYIkaii
ע    �⣺
***********************************************************************/
void Init_PCF8574(void)
{
	//GPIO�ṹ���ʼ��
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//GPIO����-SCL
	//ʹ��ʱ�ӣ��ܽţ��˿ڣ��ٶ�[50MHz]��ģʽ[PP�������]
	RCC_APB2PeriphClockCmd(SCL_PCF8574_RCC_APB2Periph_GPIOX, ENABLE); 	//SCL_PCF8574 configure 					 			
	GPIO_InitStructure.GPIO_Pin = SCL_PCF8574_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(SCL_PCF8574_GPIOX, &GPIO_InitStructure);	
	
	//GPIO����-SDA
	//ʹ��ʱ�ӣ��ܽţ��˿ڣ��ٶ�[50MHz]��ģʽ[PP�������]
	RCC_APB2PeriphClockCmd(SDA_PCF8574_RCC_APB2Periph_GPIOX, ENABLE); 	//SDA_PCF8574 configure 					 			
	GPIO_InitStructure.GPIO_Pin = SDA_PCF8574_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(SDA_PCF8574_GPIOX, &GPIO_InitStructure);
	
	//SCL��SDAд�͵�ƽ
	SCL_PCF8574(0);
	SDA_PCF8574(0);
	
	I2C_WriteData_PCF8574(0x70, 0x00);		//��ʼ��LED��ʾ����
	
}

/***********************************************************************
�������ƣ�void I2C_Start_PCF8574(void)
��    �ܣ�PCF8574��I2C��ʼ�ź�
���������
���������
��дʱ�䣺2017-01-21
�� д �ˣ�FangYIkaii
ע    �⣺SCL�ߵ�ƽ�ڼ䣬SDA�ɸߵ�ƽ��͵�ƽ���䣬��ʼ��������
***********************************************************************/
void I2C_Start_PCF8574(void)
{
	//SDAд�ߵ�ƽ
	SDA_PCF8574(1);
	delay(DelayTime_PCF8574);	
	//SCLд�ߵ�ƽ
	SCL_PCF8574(1);
	delay(DelayTime_PCF8574);
	//SDAд�͵�ƽ(�ߵ�ƽ-�͵�ƽ-����)
	SDA_PCF8574(0);	
	delay(DelayTime_PCF8574);	
}

/***********************************************************************
�������ƣ�void I2C_Stop_PCF8574(void)
��    �ܣ�PCF8574��I2Cֹͣ�ź�
���������
���������
��дʱ�䣺2017-01-21
�� д �ˣ�FangYIkaii
ע    �⣺SCL�ߵ�ƽ�ڼ䣬SDA�ɵ͵�ƽ��ߵ�ƽ���䣬������������
***********************************************************************/
void I2C_Stop_PCF8574(void)
{
	//SDAд�͵�ƽ
	SDA_PCF8574(0);
	delay(DelayTime_PCF8574);	
	//SCLд�ߵ�ƽ
	SCL_PCF8574(1);
	delay(DelayTime_PCF8574);
	//SDAд�ߵ�ƽ(�͵�ƽ-�ߵ�ƽ-����)
	SDA_PCF8574(1);	
	delay(DelayTime_PCF8574);	
}

/***********************************************************************
�������ƣ�void I2C_NOAck_PCF8574(void)
��    �ܣ�PCF8574��I2C����Ӧ����Ϣ
���������
���������
��дʱ�䣺2017-01-21
�� д �ˣ�FangYIkaii
ע    �⣺�������ݵ�IC����8bit���ݺ��������ݵ�IC�����ض��ĵ͵�ƽ���壬��ʾ�յ����ݣ���δ�յ�Ӧ���źţ��ж��ܿص�Ԫ����
          ���ͣ�SCL:��--[����]--��-��  SDA:��
***********************************************************************/
void I2C_NOAck_PCF8574(void)
{	
	//SCLд�͵�ƽ
	SCL_PCF8574(0);	
	delay(DelayTime_PCF8574);			
	//SDAд�ߵ�ƽ
	SDA_PCF8574(1);
	delay(DelayTime_PCF8574);				
	//SCLд�ߵ�ƽ
	SCL_PCF8574(1);
	delay(DelayTime_PCF8574);
	//SCLд�͵�ƽ
	SCL_PCF8574(0);	
	delay(DelayTime_PCF8574);		
}

/***********************************************************************
�������ƣ�void I2C_Ack_PCF8574(void)
��    �ܣ�PCF8574��I2C����Ӧ����Ϣ
���������
���������
��дʱ�䣺2017-01-21
�� д �ˣ�FangYIkaii
ע    �⣺���գ�SCL:��--��  ��SDA�ߵ�ƽ
***********************************************************************/
void I2C_Ack_PCF8574(void)
{
	uint8_t i;
	
	//SDA GPIO����--��������--FLOATING
	GPIO_InitTypeDef GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(SDA_PCF8574_RCC_APB2Periph_GPIOX, ENABLE);	 	//SDA_PCF8574 configure 					 	
	GPIO_InitStructure.GPIO_Pin = SDA_PCF8574_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(SDA_PCF8574_GPIOX, &GPIO_InitStructure);
	delay(DelayTime_PCF8574);	

	//SCLд�ߵ�ƽ
	SCL_PCF8574(1);	
	delay(DelayTime_PCF8574);	
	//��SDA����ĸߵ�ƽ
	while((SDA_Read_PCF8574==1) && (i<200))
	{
		i++;
	}
	delay(DelayTime_PCF8574);		
	//SCLд�͵�ƽ
	SCL_PCF8574(0);	
	delay(DelayTime_PCF8574);	

	//SDA GPIO����--�������--PP
	RCC_APB2PeriphClockCmd(SDA_PCF8574_RCC_APB2Periph_GPIOX, ENABLE); 	//SDA_PCF8574 configure 					 		
	GPIO_InitStructure.GPIO_Pin = SDA_PCF8574_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(SDA_PCF8574_GPIOX, &GPIO_InitStructure);	
	delay(DelayTime_PCF8574);				
}

/***********************************************************************
�������ƣ�void I2C_Write1Byte_PCF8574(uint8_t data)
��    �ܣ�PCF8574��I2Cдһ���ֽڳ���
���������
���������
��дʱ�䣺2017-01-21
�� д �ˣ�
ע    �⣺���ͣ�SCL����--[����]-��-��
***********************************************************************/
void I2C_Write1Byte_PCF8574(uint8_t data)
{
	uint8_t i;	
	//SCLд�͵�ƽ
	SCL_PCF8574(0);	
	delay(DelayTime_PCF8574);		
	for(i=0x80;i>0;i>>=1)  //i=10000000>>01000000>>0010000.....>>00000001
	{
		//�����i������Ϊ1
		if(i&data)
		{
			//SDAд�ߵ�ƽ
			SDA_PCF8574(1);
		}
		else
		{
			//����SDAд�͵�ƽ
			SDA_PCF8574(0);	
		}
		delay(DelayTime_PCF8574);	
		//SCLд�ߵ�ƽ
		SCL_PCF8574(1);
		delay(DelayTime_PCF8574);
		//SCLд�͵�ƽ
		SCL_PCF8574(0);	
		delay(DelayTime_PCF8574);		
	}
	//SDAд�ߵ�ƽ
	SDA_PCF8574(1);
	delay(DelayTime_PCF8574);
	
	//PCF8574��I2C����Ӧ����Ϣ
 	I2C_Ack_PCF8574();
}

/***********************************************************************
�������ƣ�uint8_t I2C_Rec1Byte_PCF8574(void)
��    �ܣ�PCF8574��I2C����һ���ֽڳ���
���������
���������
��дʱ�䣺2017-01-21
�� д �ˣ�
ע    �⣺
***********************************************************************/
uint8_t I2C_Rec1Byte_PCF8574(void)
{
	uint8_t i,data;
	
	//SDA GPIO����--��������--FLOATING
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(SDA_PCF8574_RCC_APB2Periph_GPIOX, ENABLE);	 	//SDA_PCF8574 configure 					 	
	GPIO_InitStructure.GPIO_Pin = SDA_PCF8574_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(SDA_PCF8574_GPIOX, &GPIO_InitStructure);	
	delay(DelayTime_PCF8574);	
	
	data=0x00;	
	for(i=0;i<8;i++)
	{
		//����һλ
		data=data<<1;
		//SCLд�͵�ƽ
		SCL_PCF8574(0);	  
		delay(DelayTime_PCF8574);		
		//SCLд�ߵ�ƽ
		SCL_PCF8574(1);
		delay(DelayTime_PCF8574);
		//���SDA�����ƽΪ��
		if(SDA_Read_PCF8574)
		{
			//��λ��1
			data=data | 0x01;
		}		
	}
	SCL_PCF8574(0);	
	delay(DelayTime_PCF8574);	
	
	//SDA GPIO����--�������--PP
	RCC_APB2PeriphClockCmd(SDA_PCF8574_RCC_APB2Periph_GPIOX, ENABLE); 	//SDA_PCF8574 configure 					 		
	GPIO_InitStructure.GPIO_Pin = SDA_PCF8574_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(SDA_PCF8574_GPIOX, &GPIO_InitStructure);	
	delay(DelayTime_PCF8574);		

	//PCF8574��I2C����Ӧ����Ϣ
	I2C_NOAck_PCF8574();
	return data;
}

/***********************************************************************
�������ƣ�void I2C_WriteData_PCF8574(uint8_t addr, uint8_t data)
��    �ܣ�PCF8574��I2Cд���ݳ���
���������
���������
��дʱ�䣺2017-01-20
�� д �ˣ�FangYikaii
ע    �⣺1.I2C��ʼ
          2.дҪд���ݵĵ�ַ
          3.дҪд���ݵ�����
					4.I2Cֹͣ
***********************************************************************/
void I2C_WriteData_PCF8574(uint8_t addr, uint8_t data)
{
	//PCF8574��I2C��ʼ�ź�
	I2C_Start_PCF8574();
	//PCF8574��I2Cдһ���ֽ�:��ַ
	I2C_Write1Byte_PCF8574(addr);
	//PCF8574��I2Cдһ���ֽ�:����
	I2C_Write1Byte_PCF8574(data);	
	//PCF8574��I2Cֹͣ�ź�
	I2C_Stop_PCF8574();	
}

/***********************************************************************
�������ƣ�uint8_t I2C_RecData_PCF8574(uint8_t addr)
��    �ܣ�PCF8574��I2C�����ݳ���
���������
���������
��дʱ�䣺2017-01-20
�� д �ˣ�FangYIkaii
ע    �⣺1.I2C��ʼ
          2.дҪ�����ݵĵ�ַ
          3.��������+��ֵ
					4.I2Cֹͣ
***********************************************************************/
uint8_t I2C_RecData_PCF8574(uint8_t addr)
{
	uint8_t temp;
	//PCF8574��I2C��ʼ�ź�
	I2C_Start_PCF8574();
	//PCF8574��I2Cдһ���ֽ�:��ַ
	I2C_Write1Byte_PCF8574(addr);
	//PCF8574��I2C����һ���ֽڳ���
	temp=I2C_Rec1Byte_PCF8574();
	//PCF8574��I2Cֹͣ�ź�
	I2C_Stop_PCF8574();		
	return temp;
}

/***********************************************************************
�������ƣ�void KeyScan_PCF8574(uint8_t addr)
��    �ܣ�PCF8574�ļ���ɨ�����
���������
���������
��дʱ�䣺2017-01-20
�� д �ˣ�FangYIkaii
ע    �⣺
					<----PCF8574 ���̼�ֵ ����  ---->
					S1  -- 0xFE --  S9     11111110
					S2  -- 0xFD --  S10    11111101
					S3  -- 0xFB --  S11	   11111011
					S4  -- 0xF7 --  S12    11110111

					S5  -- 0xEF --  S13    11101111
					S6  -- 0xDF --  S14    11011111
					S7  -- 0xBF --  S15	   10111111
					S8  -- 0x7F --  S16    01111111
***********************************************************************/
void KeyScan_PCF8574(void)
{
		uint8_t kvalue=0;
	  //��ֵ
		kvalue=I2C_RecData_PCF8574(0x73);	
		if(kvalue==0xFE)
		{
			KeyValue_PCF8574=1;						//PCF8574����ɨ��ֵ
		}		
		else if(kvalue==0xFD)
		{
			KeyValue_PCF8574=2;						//PCF8574����ɨ��ֵ
		}		
		else if(kvalue==0xFB)
		{
			KeyValue_PCF8574=3;						//PCF8574����ɨ��ֵ
		}			
		else if(kvalue==0xF7)
		{
			KeyValue_PCF8574=4;						//PCF8574����ɨ��ֵ
		}
		else if(kvalue==0xEF)
		{
			KeyValue_PCF8574=5;						//PCF8574����ɨ��ֵ
		}		
		else if(kvalue==0xDF)
		{
			KeyValue_PCF8574=6;						//PCF8574����ɨ��ֵ
		}		
		else if(kvalue==0xBF)
		{
			KeyValue_PCF8574=7;						//PCF8574����ɨ��ֵ
		}			
		else if(kvalue==0x7F)
		{
			KeyValue_PCF8574=8;						//PCF8574����ɨ��ֵ
		}	
		else
		{
			PCF8574.Bits.KeyScan_Flag=FALSE;	//���̰����Ѹ�λ
			KeyValue_PCF8574=0;								//PCF8574����ɨ��ֵ
		}
}
