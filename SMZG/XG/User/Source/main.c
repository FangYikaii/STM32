//========================================
//����˵���������ع�ƽ�ػ�
//�˿�ʹ�ã�6��24V�����5��24V����
//�����ߣ�
//����ʱ�䣺
//����޸�ʱ��
//========================================
//========================================
//ͷ�ļ�
#include "main.h"

#include "usbh_core.h"
#include "usbh_usr.h"
#include "usbh_msc_core.h"

//========================================
//��������

//volatile union FlagAF flagA;
struct XGData XG;									//װ�ػ�������Ϣ

uint8_t LedValue=0x00;						//LEDָʾ��ֵ
uint8_t ShiftModeStatus;					//����ģʽ
uint8_t ErrorMessage;							//������Ϣ

uint8_t testi=0;
//========================================
//��������
extern void SystemInit(void);
void Init_System(void);    
void delay(uint16_t k);     //��ʱ����


//========================================
//������
int main(void) 
{																	
	//**********************************************************************
	//ϵͳ��ʼ��
	Init_System();
	
	//**********************************************************************
	//��������	
	ControllerInfo.ScanTimeMode=GearScanT10ms;						//��λʱ��ɨ��ģʽ�ó�ʼֵ	
	LedValue=(LedValue & 0xFE) | 0x01;										//LEDָʾ��ֵ
	I2C_WriteData_PCF8574(0x70, LedValue);								//LED��ʾ����--��Դָʾ����	
	
	XG.ChannelNo[0]=1;																		//ѹ����ʾֵΪ1��ͨ��	1--6
	XG.ChannelNo[1]=1;																		//ת����ʾֵΪ2��ͨ��	2--4
	XG.Function=XG.Function%100+XG.ChannelNo[0]*1000+XG.ChannelNo[1]*100;			//ͨ����ʾ

	XG.GearRatio[0]=4.166;																//1��ת�ٱ�
	XG.GearRatio[1]=2.594;																//2��ת�ٱ�
	XG.GearRatio[2]=1.178;																//3��ת�ٱ�
	XG.GearRatio[3]=0.672;																//4��ת�ٱ�
	XG.DriveAxleRatio=22.75;															//�������ٱ�
	//**********************************************************************
	//��Ҫ������ʼ��
	ShiftModeStatus=HandShiftMode;												//Ĭ�ϣ��ֶ�����ģʽ

	
	while(1)
	{
		//**********************
		//�������źŴ���		
	  if(flagctrl.Bits.ScanTimeFlag)					//10msɨ��һ��											
		{
			flagctrl.Bits.ScanTimeFlag=FALSE;	
			
			if(ShiftModeStatus==HandShiftMode)		//�ֶ�����ģʽ
			{
				GearScanVSDeal_HandShiftMode();			//��λɨ��ʹ������					
			}
			else
			{
				GearScanVSDeal_AutoShiftMode();			//��λɨ��ʹ������	
				
			}
		}		
		
		//**********************
		//1 S���³���		
		if(flagTIM5.Bits.T1sec_Flag)
		{
			flagTIM5.Bits.T1sec_Flag=FALSE;		
			//**********************
			//װ�ػ�ϵͳ������ʾ	
			LoaderSystemDisplay();
		}	
		
		//**************************************************************
		//ת�ټ���
		//**********************************************************************
		//1s��������
		if(flagTIM5.Bits.Freq_1sec_Flag)
		{
			flagTIM5.Bits.Freq_1sec_Flag=FALSE;
			TIM4FreqCap[0].Freq=TIM4FreqCap[0].pulse;
			TIM4FreqCap[0].pulse=0;
			TIM4FreqCap[1].Freq=TIM4FreqCap[1].pulse;
			TIM4FreqCap[1].pulse=0;
			TIM4FreqCap[2].Freq=TIM4FreqCap[2].pulse;
			TIM4FreqCap[2].pulse=0;
			TIM4FreqCap[3].Freq=TIM4FreqCap[3].pulse;
			TIM4FreqCap[3].pulse=0;	
			
			XG.CANSpeed[0]=TIM4FreqCap[0].Freq;				
			XG.CANSpeed[1]=TIM4FreqCap[1].Freq*60/46;					//����ת��
			XG.CANSpeed[2]=TIM4FreqCap[2].Freq*60/3;					//�����ת�� 
			XG.CANSpeed[3]=TIM4FreqCap[3].Freq;
			
			XG.TurbineSpeed=XG.CANSpeed[1];										//����ת�� -- PLUSE2
			XG.RotationalSpeed=XG.CANSpeed[2];								//�����ת�� -- PLUSE3			
					
			XG.SpeedShow=XG.CANSpeed[XG.ChannelNo[1]];					
		}			
				
		//*******************************************************************************************
		//����ɨ�����
		KeyScan_PCF8574();
		if(!PCF8574.Bits.KeyScan_Flag)	//�жϼ�ֵ�Ƿ��Ѿ���ȡ
		{
			//*********************
			if(KeyValue_PCF8574==7)											//�Զ�/�ֶ�����
			{
				PCF8574.Bits.KeyScan_Flag=TRUE;						//��ǰ����ֵ�Ѷ�ȡ���ȴ���λ
				if(ShiftModeStatus==HandShiftMode)
				{
					ShiftModeStatus=AutoShiftMode;					//�Զ�ģʽ
					LedValue=(LedValue & 0x7F) | 0x80;			//LEDָʾ��ֵ;
				}
				else
				{
					ShiftModeStatus=HandShiftMode;					//�ֶ�ģʽ
					LedValue=LedValue & 0x7F;								//LEDָʾ��ֵ;
					
				}	
				I2C_WriteData_PCF8574(0x70, LedValue);		//LED��ʾ����--��Դָʾ����				
			}		
		}		
		
		
	}
}

//========================================
//��ģ�麯��



//========================================
//��������:void Init_System(void)
//��������: ϵͳ��ʼ��
//��ڲ���:    
//���ڲ���:      
//========================================
void Init_System(void)
{

		//************************
		//������ʼ��
		SystemInit();
//		flagA.flagBits=0;
		IOControl_Init();   			//IO��ʼ��
		MAX7219_Configuration();	//���MAX7219������
	  Init_PCF8574();				    //PCF8574�ĳ�ʼ������
//		Uart_Init();              //Uart���ڳ�ʼ��
		TIM5_Init();              //Timer5��ʱ����ʼ��
//		USB_UDisk_Init();					//U�̳�ʼ������
//		ADC_Configuration();
		FreqCap_Configuration(0xffff,(72-1));					//���PULSE������,��1Mhz��Ƶ�ʼ���	
		CAN_Configuration();			//���CAN������	
//		RTCInit_Configuration();	//���RTC�ĳ�ʼ������
	
}


//========================================
//��������:void delay(uint16_t k)
//��������: ��ʱ����
//��ڲ���:    
//���ڲ���:      
//========================================
void delay(uint16_t k)
{ 
      while(k--)
      { 
            ;   
      }
}
