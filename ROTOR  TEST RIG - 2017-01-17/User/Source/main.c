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
struct XGData XG;									//װ�ػ�������Ϣ
uint8_t ErrorMessage;							//������Ϣ

//========================================
//��������
extern void SystemInit(void);
void Init_System(void);    
  
void delay(uint16_t k);            //��ʱ����
void USARTSendSpeedData(void);     //���ڷ��͵�ǰ�ٶ�����
//========================================
//������
int main(void) 
{
	Init_System();  
	while (1)
  {	
		//**********************************************************************
		//1 S���³���		
		if(flagTIM5.Bits.T1sec_Flag)
		{			
			flagTIM5.Bits.T1sec_Flag=FALSE;	
		
			//1s��������
			if(flagTIM5.Bits.Freq_1sec_Flag)
			{
				flagTIM5.Bits.Freq_1sec_Flag=FALSE;
				
				//����2����ת��������Ŀ 3A �߰�λ �Ͱ�λ 0D 0A
				USARTSendSpeedData();
			}		

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
		IOControl_Init();   		       				 	          //IO��ʼ��
		MAX7219_Configuration();	      						  	  //���MAX7219������
	  Init_PCF8574();				           							 	  //PCF8574�ĳ�ʼ������
		Uart_Init();                                      //Uart���ڳ�ʼ��
		TIM5_Init();                                      //Timer5��ʱ����ʼ��
//		USB_UDisk_Init();			      		                //U�̳�ʼ������
		ADC_Configuration();                              //ģ��ת����ʼ��
		FreqCap_Configuration(0xffff,(72-1));				    	//���PULSE������,��1Mhz��Ƶ�ʼ���	
		CAN_Configuration();			                        //���CAN������	
		RTCInit_Configuration();	                        //���RTC�ĳ�ʼ������
		NVIC_Configuration();                             //������ȼ�����
		
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


//========================================
//��������:void USARTSendSpeedData(void)
//��������: ���ڷ��͵�ǰ�ٶ�����
//��ڲ���: ��
//���ڲ���: ��     
//========================================
void USARTSendSpeedData(void)
{
	uchar i;
	uchar Data[RX_MaxSize];
	uint32_t speed;
	
	speed=TIM4FreqCap[1].pulse;
	TIM4FreqCap[1].pulse=0;							
	
	Data[0]=0x3A;
	Data[1]=speed>>8;     //�߰�λ   
	Data[2]=0xFF&speed;   //�Ͱ�λ
	Data[3]=0x0D;
	Data[4]=0x0A;
	
	for(i=0;i<5;i++)
	{
		SerialPutChar(USART2,Data[i]);
	}
}
