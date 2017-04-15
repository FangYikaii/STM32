//========================================
//����˵����
//�˿�ʹ�ã�
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

volatile union FlagAF flagA;
struct XGData XG;									//װ�ػ�������Ϣ

uint8_t LedValue=0x00;						//LEDָʾ��ֵ
uint8_t ShiftModeStatus;					//����ģʽ
uint8_t ErrorMessage;							//������Ϣ

//========================================
//��������
extern void SystemInit(void);
void Init_System(void);    
  
void delay(uint16_t k);     //��ʱ����
//========================================
//������
int main(void) 
{
//	uint8_t mi;																																//��ʱ����
	//**********************************************************************
	//ϵͳ��ʼ��
	Init_System();
	
	//**********************************************************************
	//
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
	
//	//**********************************************************************
//	//��ʱ��������
//  XG.Startup_DelayTime=2;
//	while(XG.Startup_DelayTime)
//	{
//		;
//	}
	//**********************************************************************
	//ADCͨ��ֵУ׼	
	ADCRes.ADCMaxValue[0]=3;							//ͨ������õ�ѹֵ3V
	ADCRes.ADCMinValue[0]=0.6;						//ͨ������õ�ѹֵ0.6V	
	ADCRes.ADCMaxValue[1]=3;							//ͨ������õ�ѹֵ3V
	ADCRes.ADCMinValue[1]=0.6;						//ͨ������õ�ѹֵ0.6V
	ADCRes.ADCMaxValue[2]=3;							//ͨ������õ�ѹֵ3V
	ADCRes.ADCMinValue[2]=0.6;						//ͨ������õ�ѹֵ0.6V	
	ADCRes.ADCMaxValue[3]=3;							//ͨ������õ�ѹֵ3V
	ADCRes.ADCMinValue[3]=0.6;						//ͨ������õ�ѹֵ0.6V
	ADCRes.ADCMaxValue[4]=3;							//ͨ������õ�ѹֵ3V
	ADCRes.ADCMinValue[4]=0.6;						//ͨ������õ�ѹֵ0.6V	
	ADCRes.ADCMaxValue[5]=3;							//ͨ������õ�ѹֵ3V
	ADCRes.ADCMinValue[5]=0.6;						//ͨ������õ�ѹֵ0.6V

	//**********************************************************************
	//��ʼ����������λ�账��N���ܽ���ϵͳ	
	while(1)
	{
		StartUpGearDeal();																			//����ʱ�̵�λ�������	
		if(flagctrl.Bits.StartUpFromNx)													//��ʼ��ʱ�����źŴ�N��ʼ
		{			
			ControllerInfo.ProcessGear=ControllerInfo.NowGear;
			ControllerInfo.GoalGear=ControllerInfo.ProcessGear;		//Ŀ�굲λ
			ControllerInfo.gearinfo=ControllerInfo.NowGear;					
			break;																								//װ�ػ���ʽ����
		}		
	}
	
	//**********************************************************************
	//��Ҫ������ʼ��
	ShiftModeStatus=HandShiftMode;												//Ĭ�ϣ��ֶ�����ģʽ
	ControllerInfo.ProcessGear=Init_GearN1;								//���ó�ʼ��λֵ N1	
	ControllerInfo.GoalGear=Init_GearN1;									//���ó�ʼ��λֵ N1	
//	GearToSolenoidValve(Init_GearN1,Init_Brakeinfo);			//��ŷ�״̬��ʼ��	
	flagctrl.Bits.gearchange=TRUE;												//���µ�ŷ�ֵ
	//**********************************************************************
	//װ�ػ������������		
  while (1)
  {
		//**********************************************************************
		//��ͬ��������
		//**********************************************************************		
		//**********************
		//U�̴洢����
//		UserProcess_UDisk();					//U�̶�д�û�������
		
		//**********************
		//�������źŴ���		
	  if(flagctrl.Bits.ScanTimeFlag)		//10msɨ��һ��											
		{
			flagctrl.Bits.ScanTimeFlag=FALSE;	
			GearScanVSDeal();								//��λɨ��ʹ������	
			
		}
		//**********************
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
					if(flagA.Bits.Gear1Keep_Flag)						//1��������Чʱ
					{
						flagA.Bits.Gear1Keep_Flag=FALSE;			//��1������ֵ
						LedValue=LedValue & 0xDF;							//LEDָʾ��ֵ;
						
					}				
					if(flagA.Bits.Gear2Keep_Flag)						//2��������Чʱ
					{
						flagA.Bits.Gear2Keep_Flag=FALSE;			//��2������ֵ
						LedValue=LedValue & 0xBF;							//LEDָʾ��ֵ;
					}
					
				}	
				I2C_WriteData_PCF8574(0x70, LedValue);		//LED��ʾ����--��Դָʾ����				
			}
			//*********************
			if(KeyValue_PCF8574==6)												//2������
			{
				PCF8574.Bits.KeyScan_Flag=TRUE;							//��ǰ����ֵ�Ѷ�ȡ���ȴ���λ				
				if(ShiftModeStatus==AutoShiftMode)					//�Զ�ģʽ����Ч
				{
					if(!flagA.Bits.Gear2Keep_Flag)						//2������δ��Чʱ
					{
						flagA.Bits.Gear2Keep_Flag=TRUE;
						LedValue=(LedValue & 0xBF) | 0x40;			//LEDָʾ��ֵ;
						if(flagA.Bits.Gear1Keep_Flag)						//1��������Чʱ
						{
							flagA.Bits.Gear1Keep_Flag=FALSE;			//��1������ֵ
							LedValue=LedValue & 0xDF;							//LEDָʾ��ֵ;
							
						}								
						I2C_WriteData_PCF8574(0x70, LedValue);	//LED��ʾ����--��Դָʾ����						
					}		
					else
					{
						flagA.Bits.Gear2Keep_Flag=FALSE;
						LedValue=LedValue & 0xBF;								//LEDָʾ��ֵ;
						I2C_WriteData_PCF8574(0x70, LedValue);	//LED��ʾ����--��Դָʾ����				
					}
				}			
			}
			//*********************
			if(KeyValue_PCF8574==5)											//1������
			{
				PCF8574.Bits.KeyScan_Flag=TRUE;						//��ǰ����ֵ�Ѷ�ȡ���ȴ���λ
				if(ShiftModeStatus==AutoShiftMode)				//�Զ�ģʽ����Ч
				{	
					if(!flagA.Bits.Gear1Keep_Flag)						//2������δ��Чʱ
					{
						flagA.Bits.Gear1Keep_Flag=TRUE;
						LedValue=(LedValue & 0xDF) | 0x20;			//LEDָʾ��ֵ;
						if(flagA.Bits.Gear2Keep_Flag)						//2��������Чʱ
						{
							flagA.Bits.Gear2Keep_Flag=FALSE;			//��2������ֵ
							LedValue=LedValue & 0xBF;							//LEDָʾ��ֵ;
						}							
						I2C_WriteData_PCF8574(0x70, LedValue);	//LED��ʾ����--��Դָʾ����							
					}		
					else
					{
						flagA.Bits.Gear1Keep_Flag=FALSE;
						LedValue=LedValue & 0xDF;								//LEDָʾ��ֵ;
						I2C_WriteData_PCF8574(0x70, LedValue);	//LED��ʾ����--��Դָʾ����							
					}
				}					
			}			
			
			//*********************
			if(KeyValue_PCF8574==2)											//ת����ʾͨ��ѡ��
			{
				PCF8574.Bits.KeyScan_Flag=TRUE;						//��ǰ����ֵ�Ѷ�ȡ���ȴ���λ
				if(XG.ChannelNo[1]>=3)
				{
					XG.ChannelNo[1]=1;
				}
				else
				{
					XG.ChannelNo[1]++;
				}		
				XG.Function=XG.Function%100+XG.ChannelNo[0]*1000+XG.ChannelNo[1]*100;			//ͨ����ʾ	
			}				
			//*********************
			if(KeyValue_PCF8574==1)											//ѹ����ʾͨ��ѡ��
			{
				PCF8574.Bits.KeyScan_Flag=TRUE;						//��ǰ����ֵ�Ѷ�ȡ���ȴ���λ
				
				if(XG.ChannelNo[0]>=6)
				{
					XG.ChannelNo[0]=1;
				}
				else
				{
					XG.ChannelNo[0]++;
				}		
				XG.Function=XG.Function%100+XG.ChannelNo[0]*1000+XG.ChannelNo[1]*100;			//ͨ����ʾ					
			}			
		}
		//**********************
		//ADC�������
		if(flagADC.Bits.ADCOK)
		{			
			flagADC.Bits.ADCOK=FALSE;								
			ADC_ValueFilter();																												//ADC�˲�--��ʱԼ3ms	
			ADCRes.ADCSumValue[0]+=ADCRes.ADCResValue[0];
			ADCRes.ADCSumCount[0]++;
			ADCRes.ADCSumValue[1]+=ADCRes.ADCResValue[1];
			ADCRes.ADCSumCount[1]++;
			ADCRes.ADCSumValue[2]+=ADCRes.ADCResValue[2];
			ADCRes.ADCSumCount[2]++;
			ADCRes.ADCSumValue[3]+=ADCRes.ADCResValue[3];
			ADCRes.ADCSumCount[3]++;
			ADCRes.ADCSumValue[4]+=ADCRes.ADCResValue[4];
			ADCRes.ADCSumCount[4]++;			
			ADCRes.ADCSumValue[5]+=ADCRes.ADCResValue[5];
			ADCRes.ADCSumCount[5]++;
		}					
		//**********************
		//

		
		//**********************************************************************
		//����ģʽ������
		//**********************************************************************		
		if(ShiftModeStatus==AutoShiftMode)	//�Զ�����ģʽ
		{//�Զ�����
			if(flagctrl.Bits.KDchange)				//KD��ʹ��--1������		
			{
				ControllerInfo.GoalGear=(ControllerInfo.gearinfo/0x10)*0x10+1;
			}		
			else
			{
				ControllerInfo.GoalGear=ControllerInfo.gearinfo;							//Ŀ�굲λ				
			}
		
			//******************************************************************************
			//���̵�λ����		
		
			if(ControllerInfo.ProcessGear!=ControllerInfo.GoalGear)														//���̵�λ��Ŀ�굲λ��һ�µ�ʱ��ִ��
			{
				if(!flagTIM5.Bits.T1_5sec_Flag)																									//������ʱ�ж�
				{					
					if((ControllerInfo.ProcessGear/0x10)!=(ControllerInfo.GoalGear/0x10))					//����ͬ,��λֱ���л���Ŀ�귽��1��
					{
//						if(ControllerInfo.ProcessGear%0x10>1)																				//��λ����1������1��
//						{
//							ControllerInfo.ProcessGear=ControllerInfo.ProcessGear-1;
//						}
//						else																																				//��λ����1������ʼ����	
//						{
//							ControllerInfo.ProcessGear=(ControllerInfo.GoalGear/0x10)*0x10+1;				
//						}		
						ControllerInfo.ProcessGear=(ControllerInfo.GoalGear/0x10)*0x10+1;				
					}
					else																																					//������ͬ��ͨ����1����ʽ�л���ָ����λ
					{
						if((ControllerInfo.ProcessGear%0x10)<(ControllerInfo.GoalGear%0x10))
						{
							ControllerInfo.ProcessGear=ControllerInfo.ProcessGear+1;					
						}	
						else if((ControllerInfo.ProcessGear%0x10)>(ControllerInfo.GoalGear%0x10))
						{
							ControllerInfo.ProcessGear=ControllerInfo.ProcessGear-1;
						}
					}					
					flagctrl.Bits.gearchange=TRUE;
					flagTIM5.Bits.T1_5sec_Flag=TRUE;																							//���û�����ʱ����--1.5s			
				}
			}					
			
			
			//******************************************************************************
			//��λ����Ϣ�������			
			if(flagctrl.Bits.gearchange || flagctrl.Bits.brakechange)							//��ŷ�����
			{
				flagctrl.Bits.gearchange=FALSE;
				flagctrl.Bits.brakechange=FALSE;
				GearToSolenoidValve(ControllerInfo.ProcessGear,ControllerInfo.brakeinfo);			//��ŷ�״̬����			
			}	

			
		}//�Զ�����
		else																//�ֶ�����ģʽ
		{//�ֶ�����
			ControllerInfo.GoalGear=ControllerInfo.gearinfo;							//Ŀ�굲λ	
			ControllerInfo.ProcessGear=ControllerInfo.GoalGear;						//���̵�λ=Ŀ�굲λ			
			//******************************************************************************
			//��λ����Ϣ�������			
			if(flagctrl.Bits.gearchange || flagctrl.Bits.brakechange)							//��ŷ�����
			{
				flagctrl.Bits.gearchange=FALSE;
				flagctrl.Bits.brakechange=FALSE;
				GearToSolenoidValve(ControllerInfo.ProcessGear,ControllerInfo.brakeinfo);			//��ŷ�״̬����			
			}		
			ControllerInfo.SuggestGear=ControllerInfo.ProcessGear;

			
		}//�ֶ�����	
		
		//**********************************************************************
		//100ms ���³���		
		if(flagTIM5.Bits.T100msec_Flag)
		{
			flagTIM5.Bits.T100msec_Flag=FALSE;						
			//**************************************************************
			//	 
			ADCRes.ADCSumValue[0]=ADCRes.ADCSumValue[0]/ADCRes.ADCSumCount[0];			
			ADCRes.ADCSumValue[0]=(ADCRes.ADCSumValue[0]-ADCRes.ADCMinValue[0])*40/(ADCRes.ADCMaxValue[0]-ADCRes.ADCMinValue[0]);
			XG.BoomLargeCavityPressure=ADCRes.ADCSumValue[0]*1000;										//���۴�ǻѹ�� ��0 - 40MPa // 4 - 20mA // 150ŷķ���� //ADC1

			ADCRes.ADCSumValue[1]=ADCRes.ADCSumValue[1]/ADCRes.ADCSumCount[1];	
			ADCRes.ADCSumValue[1]=(ADCRes.ADCSumValue[1]-ADCRes.ADCMinValue[1])*40/(ADCRes.ADCMaxValue[1]-ADCRes.ADCMinValue[1]);
			XG.WorkingPumpPressure=ADCRes.ADCSumValue[1]*1000;										    //������ѹ�� ��0 - 40MPa // 4 - 20mA // 150ŷķ���� //ADC1

			ADCRes.ADCSumValue[2]=ADCRes.ADCSumValue[2]/ADCRes.ADCSumCount[2];	
			ADCRes.ADCSumValue[2]=(ADCRes.ADCSumValue[2]-ADCRes.ADCMinValue[2])*40/(ADCRes.ADCMaxValue[2]-ADCRes.ADCMinValue[2]);
			XG.SteeringPumpPressure=ADCRes.ADCSumValue[2]*1000;									    	//ת���ѹ�� ��0 - 40MPa // 4 - 20mA // 150ŷķ���� //ADC1

			ADCRes.ADCSumValue[3]=ADCRes.ADCSumValue[3]/ADCRes.ADCSumCount[3];				
			ADCRes.ADCSumValue[3]=(ADCRes.ADCSumValue[3]-ADCRes.ADCMinValue[3])*25/(ADCRes.ADCMaxValue[3]-ADCRes.ADCMinValue[3]);
			XG.RotatingBucketLargeCavityPressure=ADCRes.ADCSumValue[3]*1000;					//ת����ǻѹ��	 ��0 - 25MPa // 4 - 20mA // 150ŷķ���� //ADC1

			ADCRes.ADCSumValue[4]=ADCRes.ADCSumValue[4]/ADCRes.ADCSumCount[4];				
			ADCRes.ADCSumValue[4]=(ADCRes.ADCSumValue[4]-ADCRes.ADCMinValue[4])*40/(ADCRes.ADCMaxValue[4]-ADCRes.ADCMinValue[4]);
			XG.BoomSmallCavityPressure=ADCRes.ADCSumValue[4]*1000;										//����Сǻѹ�� ��0 - 40MPa // 4 - 20mA // 150ŷķ���� //ADC1		

			ADCRes.ADCSumValue[5]=ADCRes.ADCSumValue[5]/ADCRes.ADCSumCount[5];	
			ADCRes.ADCSumValue[5]=(ADCRes.ADCSumValue[5]-ADCRes.ADCMinValue[5])*25/(ADCRes.ADCMaxValue[5]-ADCRes.ADCMinValue[5]);
			XG.RotatingBucketSmallCavityPressure=ADCRes.ADCSumValue[5]*1000;					//ת��Сǻѹ��	 ��0 - 25MPa // 4 - 20mA // 150ŷķ���� //ADC1

			ADCRes.ADCSumValue[0]=0;
			ADCRes.ADCSumCount[0]=0;
			ADCRes.ADCSumValue[1]=0;
			ADCRes.ADCSumCount[1]=0;			
			ADCRes.ADCSumValue[2]=0;
			ADCRes.ADCSumCount[2]=0;			
			ADCRes.ADCSumValue[3]=0;
			ADCRes.ADCSumCount[3]=0;			
			ADCRes.ADCSumValue[4]=0;
			ADCRes.ADCSumCount[4]=0;
			ADCRes.ADCSumValue[5]=0;
			ADCRes.ADCSumCount[5]=0;
			
			
			XG.CANPressure[0]=XG.BoomLargeCavityPressure;															//���۴�ǻѹ�� ��0 - 40MPa
			XG.CANPressure[1]=XG.WorkingPumpPressure; 																//������ѹ��   ��0 - 40MPa
			XG.CANPressure[2]=XG.SteeringPumpPressure;																//ת���ѹ��   ��0 - 40MPa
			XG.CANPressure[3]=XG.RotatingBucketLargeCavityPressure;										//ת����ǻѹ�� ��0 - 25MPa
			XG.CANPressure[4]=XG.BoomSmallCavityPressure;															//����Сǻѹ�� ��0 - 40MPa
			XG.CANPressure[5]=XG.RotatingBucketSmallCavityPressure;										//ת��Сǻѹ�� ��0 - 25MPa	


			XG.PressureShow=XG.CANPressure[(XG.ChannelNo[0]-1)];

		}			
		//**********************************************************************
		//1 S���³���		
		if(flagTIM5.Bits.T1sec_Flag)
		{
			flagTIM5.Bits.T1sec_Flag=FALSE;	
		
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
			
			
			//**************************************************************
			//װ�ػ�ϵͳ������ʾ	
			LoaderSystemDisplay();
			//**************************************************************
			//


		}	
		//**********************************************************************		
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
		flagA.flagBits=0;
		IOControl_Init();   			//IO��ʼ��
		MAX7219_Configuration();	//���MAX7219������
	  Init_PCF8574();				    //PCF8574�ĳ�ʼ������
		Uart_Init();              //Uart���ڳ�ʼ��
		TIM5_Init();              //Timer5��ʱ����ʼ��
//		USB_UDisk_Init();					//U�̳�ʼ������
		ADC_Configuration();
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
