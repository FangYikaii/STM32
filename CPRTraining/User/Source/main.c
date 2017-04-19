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

uint16_t FrqTimCout=0;						//���Ƶ�ʼ���

//========================================
//��������


uint8_t digitalcode[12]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0,0x40}; //��ģ
                    //0   1    2    3    4    5    6     7    8    9  �ո� -//�����ʻ�
uint8_t seg_table_p[]={0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6};//�����ʻ�
uint8_t seg_table_n[]={0x03,0x9F,0x25,0x0D,0x99,0x49,0x41,0x1F,0x01,0x09};//�����ʻ�

uint8_t presscount=0;				//��ѹ����

uint8_t uplaserstd=0x40;
uint8_t downlaserstd=0x40;	//ѡ����2������Ϊ���ذ�ѹ�������жϵ㣬������Ҫ����
uint8_t uplaserstatus=0;
uint8_t downlaserstatus=0;	//���µ�״ֵ̬

uint8_t uplaserflag=0;
uint8_t downlaserflag=0;		//���µ�״̬�仯��־


//	uint16_t mi;																																//��ʱ����
uint8_t data[4]; //������λ��ʾ�ַ������飬��ʾ��ѹ����
uint8_t cycles=0;	
	
uint8_t LaserModel_Input1;
uint8_t LaserModel_Input2;
	
//========================================
//��������
extern void SystemInit(void);
void Init_System(void);    


void LedRowOut(u32 Data);
void S74HC595Send(u8 data);
void S74HC595Load(void);


void delay(uint16_t k);     //��ʱ����
//========================================
//������
int main(void) 
{

	//**********************************************************************
	//ϵͳ��ʼ��
	Init_System();


	//**********************************************************************
	//
	while(1)
	{		
			if(Btn_Start_Read)		//��ʼ--��ť
			{
				presscount=0;				//��ѹ����
				uplaserflag=0;
				downlaserflag=0;		//���µ�״̬�仯��־
				flagA.Bits.Start_Flag=TRUE;			
				
				
				
			}		

			if(Btn_Stop_Read)		//ֹͣ--��ť
			{
				flagA.Bits.Start_Flag=FALSE;		


				
				
			}		
			
			
			if(flagA.Bits.Start_Flag)		//CPR ѵ����
			{
					LaserModel_Input1=I2C_RecData_PCF8574(0x71);
					LaserModel_Input2=I2C_RecData_PCF8574(0x73);						//ע��ܽŵĶ̽�ð�Ƿ�������ȷ	
					//�˴������ʼ״̬ʱ���ϲ�ָ���ļ���ģ�鱻�����յ����²�ָ���ļ���ģ��û���յ�
					if(LaserModel_Input1 && uplaserstd)											//��ѡ�ܽŸߵ�ƽ -- �ϱ�׼  ��������
					{
						if(uplaserstatus==0)			//״̬�ı�
						{
							uplaserstatus=1;							
						}						
						
					}
					else		//�޼�������
					{
						if(uplaserstatus==1)			//״̬�ı�
						{
							uplaserstatus=0;			
							uplaserflag=1;					//���������ƶ�	
						}							
						
					}
					if(LaserModel_Input2 && downlaserstd)											//��ѡ�ܽŸߵ�ƽ -- �±�׼  -- ��������
					{
						if(downlaserstatus==0)		//״̬�ı�
						{
							downlaserstatus=1;
							downlaserflag=1;				//���������ƶ����Ƶ�ָ��λ��
						}
					}		
					else
					{
						if(downlaserstatus==1)		//״̬�ı�
						{
							downlaserstatus=0;
						}
					}	
				
					if(uplaserflag && downlaserflag)		//���һ�ΰ�ѹ����
					{
						presscount++;				//��ѹ����
						uplaserflag=0;
						downlaserflag=0;
					}
									
			}



			
		
		if(flagTIM5.Bits.T1sec_Flag)					//1S�ж�
		{
			flagTIM5.Bits.T1sec_Flag=FALSE;
					
			
			
		}		
		
		if(flagTIM5.Bits.T100msec_Flag)			//100ms�ж�
		{			
			flagTIM5.Bits.T100msec_Flag=FALSE;
			hc595_display(presscount);							//��ѹ������ʾ -- ��ʾ�������ʵ�ʵ�����
			

		}

	}

	
}


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
		IOControl_Init();   			//��ʼ��ֹͣ��2����ť�ĳ�ʼ��
	  Init_PCF8574();				    //PCF8574�ĳ�ʼ������
		hc595_init();							//�������ʾ����ʼ��
		TIM5_Init();              //Timer5��ʱ����ʼ��
	
	
	
//		MAX7219_Configuration();	//���MAX7219������	
//		Uart_Init();              //Uart���ڳ�ʼ��	
//		USB_UDisk_Init();					//U�̳�ʼ������
//		ADC_Configuration();
//		FreqCap_Configuration(0xffff,(72-1));					//���PULSE������,��1Mhz��Ƶ�ʼ���	
//		CAN_Configuration();			//���CAN������	
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
