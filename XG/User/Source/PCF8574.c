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
������:     Masterjay   
����ʱ��:   2014-04-21 
�޸�ʱ��:   2014-04-21
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
��дʱ�䣺2014.4.14
�� д �ˣ�
ע    �⣺
***********************************************************************/
void Init_PCF8574(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(SCL_PCF8574_RCC_APB2Periph_GPIOX, ENABLE); 	//SCL_PCF8574 configure 					 
			
	GPIO_InitStructure.GPIO_Pin = SCL_PCF8574_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(SCL_PCF8574_GPIOX, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(SDA_PCF8574_RCC_APB2Periph_GPIOX, ENABLE); 	//SDA_PCF8574 configure 					 
			
	GPIO_InitStructure.GPIO_Pin = SDA_PCF8574_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(SDA_PCF8574_GPIOX, &GPIO_InitStructure);
	
	SCL_PCF8574(0);
	SDA_PCF8574(0);
	
	I2C_WriteData_PCF8574(0x70, 0x00);		//��ʼ��LED��ʾ����
		
	
}

/***********************************************************************
�������ƣ�void I2C_Start_PCF8574(void)
��    �ܣ�PCF8574��I2C��ʼ�ź�
���������
���������
��дʱ�䣺2014.4.14
�� д �ˣ�
ע    �⣺
***********************************************************************/
void I2C_Start_PCF8574(void)
{

	SDA_PCF8574(1);
	delay(DelayTime_PCF8574);	
	SCL_PCF8574(1);
	delay(DelayTime_PCF8574);
	SDA_PCF8574(0);	
	delay(DelayTime_PCF8574);	

	
}
/***********************************************************************
�������ƣ�void I2C_Stop_PCF8574(void)
��    �ܣ�PCF8574��I2Cֹͣ�ź�
���������
���������
��дʱ�䣺2014.4.14
�� д �ˣ�
ע    �⣺
***********************************************************************/
void I2C_Stop_PCF8574(void)
{
	
	SDA_PCF8574(0);
	delay(DelayTime_PCF8574);	
	SCL_PCF8574(1);
	delay(DelayTime_PCF8574);
	SDA_PCF8574(1);	
	delay(DelayTime_PCF8574);	

}

/***********************************************************************
�������ƣ�void I2C_NOAck_PCF8574(void)
��    �ܣ�PCF8574��I2C����Ӧ����Ϣ
���������
���������
��дʱ�䣺2014.4.14
�� д �ˣ�
ע    �⣺
***********************************************************************/
void I2C_NOAck_PCF8574(void)
{	
	SCL_PCF8574(0);	
	delay(DelayTime_PCF8574);			
	SDA_PCF8574(1);
	delay(DelayTime_PCF8574);				
	SCL_PCF8574(1);
	delay(DelayTime_PCF8574);
	SCL_PCF8574(0);	
	delay(DelayTime_PCF8574);		


}

/***********************************************************************
�������ƣ�void I2C_Ack_PCF8574(void)
��    �ܣ�PCF8574��I2C����Ӧ����Ϣ
���������
���������
��дʱ�䣺2014.4.14
�� д �ˣ�
ע    �⣺
***********************************************************************/
void I2C_Ack_PCF8574(void)
{
	uint8_t i;
	GPIO_InitTypeDef GPIO_InitStructure;	

	RCC_APB2PeriphClockCmd(SDA_PCF8574_RCC_APB2Periph_GPIOX, ENABLE);	 	//SDA_PCF8574 configure 					 	
	GPIO_InitStructure.GPIO_Pin = SDA_PCF8574_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(SDA_PCF8574_GPIOX, &GPIO_InitStructure);
	delay(DelayTime_PCF8574);	

	SCL_PCF8574(1);	
	delay(DelayTime_PCF8574);	
	while((SDA_Read_PCF8574==1) && (i<200))
	{
		i++;
	}
	delay(DelayTime_PCF8574);		
	SCL_PCF8574(0);	
	delay(DelayTime_PCF8574);	


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
��дʱ�䣺2014.4.14
�� д �ˣ�
ע    �⣺
***********************************************************************/
void I2C_Write1Byte_PCF8574(uint8_t data)
{
	uint8_t i;	
	SCL_PCF8574(0);	
	delay(DelayTime_PCF8574);		
	for(i=0x80;i>0;i>>=1)
	{
		if(i&data)
		{
			SDA_PCF8574(1);
		}
		else
		{
			SDA_PCF8574(0);	
		}
		delay(DelayTime_PCF8574);	
		SCL_PCF8574(1);
		delay(DelayTime_PCF8574);
		SCL_PCF8574(0);	
		delay(DelayTime_PCF8574);		
	}
	SDA_PCF8574(1);
	delay(DelayTime_PCF8574);
	
 	I2C_Ack_PCF8574();
}
/***********************************************************************
�������ƣ�uint8_t I2C_Rec1Byte_PCF8574(void)
��    �ܣ�PCF8574��I2C����һ���ֽڳ���
���������
���������
��дʱ�䣺2014.4.14
�� д �ˣ�
ע    �⣺
***********************************************************************/
uint8_t I2C_Rec1Byte_PCF8574(void)
{
	uint8_t i,data;
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
		data=data<<1;
		SCL_PCF8574(0);	
		delay(DelayTime_PCF8574);		
		SCL_PCF8574(1);
		delay(DelayTime_PCF8574);
		if(SDA_Read_PCF8574)
		{
			data=data | 0x01;
		}
		
	}
	SCL_PCF8574(0);	
	delay(DelayTime_PCF8574);	
	
	RCC_APB2PeriphClockCmd(SDA_PCF8574_RCC_APB2Periph_GPIOX, ENABLE); 	//SDA_PCF8574 configure 					 
			
	GPIO_InitStructure.GPIO_Pin = SDA_PCF8574_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(SDA_PCF8574_GPIOX, &GPIO_InitStructure);	
	delay(DelayTime_PCF8574);		

	I2C_NOAck_PCF8574();
	return data;
}

/***********************************************************************
�������ƣ�void I2C_WriteData_PCF8574(uint8_t addr, uint8_t data)
��    �ܣ�PCF8574��I2Cд���ݳ���
���������
���������
��дʱ�䣺2014.4.14
�� д �ˣ�
ע    �⣺
***********************************************************************/
void I2C_WriteData_PCF8574(uint8_t addr, uint8_t data)
{
	I2C_Start_PCF8574();
	I2C_Write1Byte_PCF8574(addr);
	I2C_Write1Byte_PCF8574(data);	
	I2C_Stop_PCF8574();	
}

/***********************************************************************
�������ƣ�uint8_t I2C_RecData_PCF8574(uint8_t addr)
��    �ܣ�PCF8574��I2C�����ݳ���
���������
���������
��дʱ�䣺2014.4.14
�� д �ˣ�
ע    �⣺
***********************************************************************/
uint8_t I2C_RecData_PCF8574(uint8_t addr)
{
	uint8_t temp;
	I2C_Start_PCF8574();
	I2C_Write1Byte_PCF8574(addr);
	temp=I2C_Rec1Byte_PCF8574();
	I2C_Stop_PCF8574();		
	return temp;
}

/***********************************************************************
�������ƣ�void KeyScan_PCF8574(uint8_t addr)
��    �ܣ�PCF8574�ļ���ɨ�����
���������
���������
��дʱ�䣺2014.4.14
�� д �ˣ�
ע    �⣺
***********************************************************************/
void KeyScan_PCF8574(void)
{
		uint8_t kvalue=0;
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
