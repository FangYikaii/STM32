/*
����˵��:  	
            MAX7219���Ƶ��������ʾ���� --- STM32F107VCT 
						
ע�����						
						1��MAX7219��ʼ����ɺ���Ҫ����һ������ʱ�����������޷�������ʾ���������ò��ò���
          ˢ�³���ķ�������ֹ���ֲ���ʾ�����						
						2��ÿ�ζ�д����ö�MAX7219��һЩ�������ý����ظ���ʼ��������Ҳ����ֲ���ʾ�����
						3��ÿ��ˢ���������ʾ��ʱ����Ҫ��ˢ��1�飬����������ʾ���ȵ���
						
�˿�ʹ��:		��Doc�ļ����ڵ�·���˵��
������:     FangYIkaii   
����ʱ��:   2017-01-21 
�޸�ʱ��:   2017-01-21
*/
/*
SPI:Serial Peripheral Interface������Χ�豸�ӿ�--����������ƵDAоƬPCM1770��W25X16,2.4G����
1.��Ե�ͨ���У�SPI�ӿڲ���ҪѰַ��������Ϊȫ˫��ͨ�ţ��ڶ����������ϵͳ�У�ÿ����������Ҫ������ʹ���ź�
2.I2C������������õ���һ���ߣ�SPI��ֱ�ΪSDO��SDI�����ź��ߣ��ٶȿ��I2C,����������ǲ�ͬ�Ĺܽţ�ռ��CPU�Ĺܽ�Ҳ���I2C(ȫ˫��ͨ��)
3.4���ź��ߣ�����ʱ��SCLK,�����������SDO/MOSI,������������SDI/MISO,Ƭѡ�ź���CS
MISO:���豸�������룬���豸����������ţ������������ź��߶������ݣ��ӻ���������������������ӻ�-->����
MOSI:���豸������������豸�����������ţ����������ݴ�������������ӻ��������߶��룬����-->�ӻ�
SCK��ʱ���ź���
CS:Ƭѡ�ź��ߣ���SPI����豸��MCU������ʱ��ͨ��������ѡ���豸��MCUͨ��

*/

//========================================
//ͷ�ļ�
#include "main.h"

//========================================
//��������
//����壺                   0   			1    		2    	3    		4    	5    	6     	7    		8    9
//����壺                   F  		R/A  		H/N    	P   		-    	E   ����ʾ                  
const uint8_t code_table[17]= {0x7e,  0x30,  0x6d,  0x79,  0x33,  0x5b,  0x5f,  0x70,  0x7f,  0x7b,
                               0x47,  0x77,  0x37,  0x67,  0x01,  0X4F,  0x00,
														};


//========================================
//��������
void LoaderSystemDisplay(void);												//װ�ػ�ϵͳ������ʾ
void GearDisplay(uint8_t gear, uint8_t no);						//��λ��Ϣ��ʾ
void ErrorDisplay(uint8_t Error);											//������Ϣ��ʾ
														
														
														
void MAX7219_Configuration(void);											//���MAX7219������
void Init_MAX7219(void);															//MAX7219��ʼ������
void Send1Byte_MAX7219(uint8_t dat);										//��MAX7219����һ���ֽ����ݳ���
void Clear1stChip_MAX7219(void);											//���1ƬMAX7219����ʾ����
void Clear2ndChip_MAX7219(void);											//���2ƬMAX7219����ʾ����
void Clear3rdChip_MAX7219(void);											//���2ƬMAX7219����ʾ����
void Write1stChip_MAX7219(uint16_t addr,uint16_t data);				//MAX7219����1��оƬ��д���ݳ���
void Write2ndChip_MAX7219(uint16_t addr,uint16_t data);				//MAX7219����2��оƬ��д���ݳ���
void Write3rdChip_MAX7219(uint16_t addr,uint16_t data);				//MAX7219����3��оƬ��д���ݳ���
void DisplayChar_MAX7219 (uint8_t addr,uint8_t data,uint8_t chipno);		//MAX7219��ʾ���ݳ���
void DisplayDigitalTube1_4Num_MAX7219 (uint16_t data,uint8_t no,uint8_t point);				//��1��2��4λ�������ʾ������ʾ��4λ
void DisplayDigitalTube2_2Num_MAX7219 (uint8_t data,uint8_t no,uint8_t point);				//��1��2��3��4��2λ�������ʾ������ʾ��4λ
void DisplayDigitalTube3_4Num_MAX7219 (uint16_t data,uint8_t no,uint8_t point);	      //��1��2��4λ�������ʾ������ʾ��4λ
//========================================
//��ģ�麯��

/***********************************************************************
�������ƣ�void LoaderSystemDisplay(void)
��    �ܣ�װ�ػ�ϵͳ������ʾ
�����������
�����������
��дʱ�䣺2017-01-21
�� д �ˣ�FangYIkaii
ע    �⣺
***********************************************************************/
void LoaderSystemDisplay(void)
{
		DisplayDigitalTube3_4Num_MAX7219 (XG.PressureShow/10,1,3);							//���۴�ǻѹ��__��1��2��4λ�������ʾ������ʾ��4λ
		DisplayDigitalTube3_4Num_MAX7219 (XG.Function,2,0);											//ͨ����Ϣ��ʾ������ֵ__��1��2��4λ�������ʾ������ʾ��4λ			
		DisplayDigitalTube1_4Num_MAX7219 (XG.PumpSpeed,1,0);										//����ת��__��1��2��4λ�������ʾ������ʾ��4λ
		DisplayDigitalTube1_4Num_MAX7219 (XG.SpeedShow,2,0);										//����ת��__��1��2��4λ�������ʾ������ʾ��4λ
//		DisplayDigitalTube2_2Num_MAX7219 (ControllerInfo.SuggestGear,1,0);		//�Ƽ���λ__��1��2��3��4��2λ�������ʾ������ʾ��4λ
		GearDisplay(ControllerInfo.SuggestGear,2);		
	//			DisplayDigitalTube2_2Num_MAX7219 (Timer5.minute,2,0);							//��ǰ��λ__��1��2��3��4��2λ�������ʾ������ʾ��4λ
		GearDisplay(ControllerInfo.ProcessGear,1);															//��ǰ��λ��Ϣ��ʾ
		if(XG.Throttle>=100)
		{
			DisplayDigitalTube2_2Num_MAX7219(99,3,0);															//���ſ���__��1��2��3��4��2λ�������ʾ������ʾ��4λ
		}
		else
		{
			DisplayDigitalTube2_2Num_MAX7219 (XG.Throttle,3,0);											//���ſ���__��1��2��3��4��2λ�������ʾ������ʾ��4λ			
		}
//		DisplayDigitalTube2_2Num_MAX7219(ErrorMessage,4,0);											//������Ϣ��ʾ__��1��2��3��4��2λ�������ʾ������ʾ��4λ
		ErrorDisplay(ErrorMessage);
}	

/***********************************************************************
�������ƣ�void ErrorDisplay(uint8_t Error)
��    �ܣ�������Ϣ��ʾ
�������������ֵ
�����������
��дʱ�䣺2017-01-21
�� д �ˣ�FangYIkaii
ע    �⣺
***********************************************************************/
void ErrorDisplay(uint8_t Error)
{
	uint8_t code;

	Init_MAX7219();					//��Ҫ�ظ����ã�������ֲ���ʾ����
	code=code_table[Error%0x10];	
	Write2ndChip_MAX7219(DIG_7,code);					
	code=code_table[Error/0x10];							
	Write2ndChip_MAX7219(DIG_8,code);		
}


/***********************************************************************
�������ƣ�void GearDisplay(uint8_t gear, uint8_t no)
��    �ܣ���λ��Ϣ��ʾ
�����������λֵ
�����������
��дʱ�䣺2014.05.29
�� д �ˣ�masterjay
ע    �⣺
***********************************************************************/
void GearDisplay(uint8_t gear, uint8_t no)
{
	uint8_t code;
	Init_MAX7219();					//��Ҫ�ظ����ã�������ֲ���ʾ����
	if(no==1)		//��ǰ��λ��ʾ
	{
		if(flagctrl.Bits.KDchange)								//KD
		{
			code=code_table[14];		
			Write2ndChip_MAX7219(DIG_3,code);					
			code=code_table[14];						
			Write2ndChip_MAX7219(DIG_4,code);		
		}
		else
		{					
			if(gear/0x10==0)   //F
			{
				if(gear%0x10!=0)
				{
					code=code_table[10];		
					Write2ndChip_MAX7219(DIG_3,code);					
					code=code_table[gear%0x10];						
					Write2ndChip_MAX7219(DIG_4,code);		
				}	
				else
				{
					code=code_table[10];		
					Write2ndChip_MAX7219(DIG_3,code);					
					code=code_table[13];						
					Write2ndChip_MAX7219(DIG_4,code);					
				}
			}
			else if(gear/0x10==1)	//R
			{
				if(gear%0x10!=0)
				{
					code=code_table[11];		
					Write2ndChip_MAX7219(DIG_3,code);					
					code=code_table[gear%0x10];						
					Write2ndChip_MAX7219(DIG_4,code);		
				}
				else
				{
					code=code_table[11];		
					Write2ndChip_MAX7219(DIG_3,code);					
					code=code_table[13];						
					Write2ndChip_MAX7219(DIG_4,code);	
				}	
			}
			else if(gear/0x10==2)	//N
			{
				if(gear%0x10!=0)
				{
					code=code_table[12];		
					Write2ndChip_MAX7219(DIG_3,code);					
					code=code_table[gear%0x10];						
					Write2ndChip_MAX7219(DIG_4,code);		
				}
				else
				{
					code=code_table[12];		
					Write2ndChip_MAX7219(DIG_3,code);					
					code=code_table[13];		   				
					Write2ndChip_MAX7219(DIG_4,code);		
				}				
			}			
		}					
	}
	else if(no==2)	//�Ƽ���λ��ʾ	
	{
		if(flagctrl.Bits.KDchange)								//KD
		{
			code=code_table[14];		
			Write2ndChip_MAX7219(DIG_1,code);					
			code=code_table[14];						
			Write2ndChip_MAX7219(DIG_2,code);		

			
		}
		else
		{					
			if(gear/0x10==0)   //F
			{
				if(gear%0x10!=0)
				{
					code=code_table[10];		
					Write2ndChip_MAX7219(DIG_1,code);					
					code=code_table[gear%0x10];						
					Write2ndChip_MAX7219(DIG_2,code);		
				}	
				else
				{
					code=code_table[10];		
					Write2ndChip_MAX7219(DIG_1,code);					
					code=code_table[13];						
					Write2ndChip_MAX7219(DIG_2,code);					
				}
			}
			else if(gear/0x10==1)	//R
			{
				if(gear%0x10!=0)
				{
					code=code_table[11];		
					Write2ndChip_MAX7219(DIG_1,code);					
					code=code_table[gear%0x10];						
					Write2ndChip_MAX7219(DIG_2,code);		
				}
				else
				{
					code=code_table[11];		
					Write2ndChip_MAX7219(DIG_1,code);					
					code=code_table[13];						
					Write2ndChip_MAX7219(DIG_2,code);	
				}	
			}
			else if(gear/0x10==2)	//N
			{
				if(gear%0x10!=0)
				{
					code=code_table[12];		
					Write2ndChip_MAX7219(DIG_1,code);					
					code=code_table[gear%0x10];						
					Write2ndChip_MAX7219(DIG_2,code);		
				}
				else
				{
					code=code_table[12];		
					Write2ndChip_MAX7219(DIG_1,code);					
					code=code_table[13];		   				
					Write2ndChip_MAX7219(DIG_2,code);		
				}				
			}			
		}			
	}
	
	
	
}

/***********************************************************************
�������ƣ�void MAX7219_Configuration(void)
��    �ܣ����MAX7219������
���������
���������
��дʱ�䣺2017-01-21
�� д �ˣ�FangYIkaii
ע    �⣺
***********************************************************************/
void MAX7219_Configuration(void)
{
	//GPIO�ṹ���ʼ��
	GPIO_InitTypeDef GPIO_InitStructure;	
	//ʱ�ӣ�DIN;LOAD;CLK
	RCC_APB2PeriphClockCmd(DIN_MAX7219_RCC_APB2Periph_GPIOX, ENABLE);
	RCC_APB2PeriphClockCmd(LOAD_MAX7219_RCC_APB2Periph_GPIOX, ENABLE);	
	RCC_APB2PeriphClockCmd(CLK_MAX7219_RCC_APB2Periph_GPIOX, ENABLE);	
	
	//GPIO���壺�ܽţ��ٶ�--50MHz��ģʽ--PP--����������˿�
	//DIN
	GPIO_InitStructure.GPIO_Pin = DIN_MAX7219_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_Init(DIN_MAX7219_GPIOX, &GPIO_InitStructure);
	//LOAD
	GPIO_InitStructure.GPIO_Pin = LOAD_MAX7219_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_Init(LOAD_MAX7219_GPIOX, &GPIO_InitStructure);	
	//CLK
	GPIO_InitStructure.GPIO_Pin = CLK_MAX7219_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_Init(CLK_MAX7219_GPIOX, &GPIO_InitStructure);
	
	//DINд�͵�ƽ
	DIN_MAX7219(0);
	//LOADд�ߵ�ƽ
	LOAD_MAX7219(1);	
	//CLKд�͵�ƽ
	CLK_MAX7219(0); 
	//MAX7219��ʼ������
	Init_MAX7219();	
	Clear1stChip_MAX7219();														//���1ƬMAX7219����ʾ����	
	Clear2ndChip_MAX7219();														//���2ƬMAX7219����ʾ����
	Clear3rdChip_MAX7219();														//���3ƬMAX7219����ʾ����
}

/***********************************************************************
�������ƣ�void Init_MAX7219(void)
��    �ܣ�MAX7219��ʼ������
���������
���������
��дʱ�䣺2017-01-21
�� д �ˣ�FangYIkaii
ע    �⣺
					#define 			REG_DECODE 				0x09   	//������ƼĴ���   
					#define 			REG_INTENSITY 		0x0a   	//���ȿ��ƼĴ��� 
					#define 			REG_SCAN_LIMIT 		0x0b   	//ɨ����޼Ĵ��� 
					#define 			REG_SHUTDOWN 			0x0c   	//�ض�ģʽ�Ĵ���
					#define 			REG_DISPLAY_TEST 	0x0f  	//���Կ��ƼĴ���
***********************************************************************/
void Init_MAX7219(void)
{
	Write1stChip_MAX7219(REG_DISPLAY_TEST,0x00);      //ѡ����ģʽ��0xX0��			0x01 --testģʽ
	Write2ndChip_MAX7219(REG_DISPLAY_TEST,0x00);      //ѡ����ģʽ��0xX0��			0x01 --testģʽ
	Write3rdChip_MAX7219(REG_DISPLAY_TEST,0x00);      //ѡ����ģʽ��0xX0��			0x01 --testģʽ	
	Write1stChip_MAX7219(REG_INTENSITY,0x02);        	//���ó�ʼ����  
	Write2ndChip_MAX7219(REG_INTENSITY,0x02);        	//���ó�ʼ���� 
	Write3rdChip_MAX7219(REG_INTENSITY,0x02);        	//���ó�ʼ���� 	
	Write1stChip_MAX7219(REG_SCAN_LIMIT,0x07);        //����Ϊȫ��ʾ
	Write2ndChip_MAX7219(REG_SCAN_LIMIT,0x07);        //����Ϊȫ��ʾ
	Write3rdChip_MAX7219(REG_SCAN_LIMIT,0x07);        //����Ϊȫ��ʾ	
	Write1stChip_MAX7219(REG_DECODE,0x00);       			//ѡ��B����ģʽ--0xFF,�ǽ���ģʽ--0x00
	Write2ndChip_MAX7219(REG_DECODE,0x00);       			//ѡ��B����ģʽ--0xFF,�ǽ���ģʽ--0x00
	Write3rdChip_MAX7219(REG_DECODE,0x00);       			//ѡ��B����ģʽ--0xFF,�ǽ���ģʽ--0x00	
	Write1stChip_MAX7219(REG_SHUTDOWN,0x01);         	//������������ģʽ��0xX1��	0x00 --�ر���ʾ
	Write2ndChip_MAX7219(REG_SHUTDOWN,0x01);         	//������������ģʽ��0xX1��	0x00 --�ر���ʾ	
	Write3rdChip_MAX7219(REG_SHUTDOWN,0x01);         	//������������ģʽ��0xX1��	0x00 --�ر���ʾ			
}

/***********************************************************************
�������ƣ�void Send1Byte_MAX7219(uint8_t dat)
��    �ܣ���MAX7219����һ���ֽ����ݳ���
���������
���������
��дʱ�䣺2017-01-21
�� д �ˣ�FangYIkaii
ע    �⣺for i= 0��8
             1.CLK��0
             2.�ж�dat��DINд0��1
             3.CLK��1
             4.dat����һλ
***********************************************************************/
void Send1Byte_MAX7219(uint8_t dat)
{
   uint8_t i,temp;
   for (i=0;i<8;i++)
	 {   
			CLK_MAX7219(0);       				//CLK����
		 	delay(DelayTime_MAX7219);
			temp=dat&0x80; 								//ÿ��ȡ���ֽ�      
			if(temp==0x80)
			{
				DIN_MAX7219(1);
			}
			else
			{
				DIN_MAX7219(0);
			}
			delay(DelayTime_MAX7219);
			dat<<=1;										//��������1λ
			CLK_MAX7219(1);							//CLK�ø�
			delay(DelayTime_MAX7219);
	}
}

/***********************************************************************
�������ƣ�void Clear1stChip_MAX7219(void);
��    �ܣ����1ƬMAX7219����ʾ����
���������
���������
��дʱ�䣺2017-01-21
�� д �ˣ�FangYIkaii
ע    �⣺�Ĵ���1-8��digit0-digit7�����8λ��
***********************************************************************/
void Clear1stChip_MAX7219(void)
{ 
  uint8_t i; 
  for (i=1; i <=8; i++) 
	{
		Write1stChip_MAX7219(i, 0x00);
	}
} 

/***********************************************************************
�������ƣ�void Clear2ndChip_MAX7219(void);
��    �ܣ����2ƬMAX7219����ʾ����
���������
���������
��дʱ�䣺2017-01-21
�� д �ˣ�FangYIkaii
ע    �⣺�Ĵ���1-8��digit0-digit7�����8λ��
***********************************************************************/
void Clear2ndChip_MAX7219(void)
{
  uint8_t i; 
  for (i=1; i <=8; i++) 
	{
		Write2ndChip_MAX7219(i, 0x00);
	}
}

/***********************************************************************
�������ƣ�void Clear3rdChip_MAX7219(void);
��    �ܣ����2ƬMAX7219����ʾ����
���������
���������
��дʱ�䣺2017-01-21
�� д �ˣ�FangYIkaii
ע    �⣺�Ĵ���1-8��digit0-digit7�����8λ��
***********************************************************************/
void Clear3rdChip_MAX7219(void)
{
  uint8_t i; 
  for (i=1; i <=8; i++) 
	{
		Write3rdChip_MAX7219(i, 0x00);
	}
}

/***********************************************************************
�������ƣ�void Write1stChip_MAX7219(uint16_t addr,uint16_t data);
��    �ܣ�MAX7219����1��оƬ��д���ݳ���
���������
���������
��дʱ�䣺2017-01-21
�� д �ˣ�FangYIkaii
ע    �⣺LOAD�ߵ�ƽ
          1.д������оƬ(��) 2.д�ڶ���оƬ(��) 3.д��һ��оƬ(����,��ַ)
          LOAD�͵�ƽ
***********************************************************************/
void Write1stChip_MAX7219(uint16_t addr,uint16_t data)
{ 
	LOAD_MAX7219(0); 							//LOAD�õ�,ѡͨMAX7219оƬ
	
	delay(DelayTime_MAX7219);			//�Ե�����оƬ���пղ���	
	Send1Byte_MAX7219(REG_NO_OP);          
	Send1Byte_MAX7219(0x00);
// 	CLK_MAX7219(1);								//ʱ�������أ����͵�ַ
	
	delay(DelayTime_MAX7219);			//�Եڶ���оƬ���пղ���
	Send1Byte_MAX7219(REG_NO_OP);	
	Send1Byte_MAX7219(0x00);	
// 	CLK_MAX7219(1);								//ʱ�������أ����͵�ַ
	
	delay(DelayTime_MAX7219);
	Send1Byte_MAX7219(addr);			//�Ե�һ��оƬ����д����
	Send1Byte_MAX7219(data);
	
	LOAD_MAX7219(1);  						//LOAD�ø߽���MAX7219оƬ 
	delay(DelayTime_MAX7219);
}

/***********************************************************************
�������ƣ�void Write2ndChip_MAX7219(uint16_t addr,uint16_t data);
��    �ܣ�MAX7219����2��оƬ��д���ݳ���
���������
���������
��дʱ�䣺2017-01-21
�� д �ˣ�FangYIkaii
ע    �⣺ LOAD�ߵ�ƽ
           1.д������оƬ(��) 2.д�ڶ���оƬ(����,��ַ) 3.д��һ��оƬ(��)
           LOAD�͵�ƽ
***********************************************************************/
void Write2ndChip_MAX7219(uint16_t addr,uint16_t data)
{
	LOAD_MAX7219(0); 							//LOAD�õ�ѡͨMAX7219оƬ
	
	delay(DelayTime_MAX7219);      //�Ե�����оƬ���пղ���  
	Send1Byte_MAX7219(REG_NO_OP);        
	Send1Byte_MAX7219(0x00);
//	CLK_MAX7219(1);								//ʱ�������أ����͵�ַ		
	
	delay(DelayTime_MAX7219);
	Send1Byte_MAX7219(addr);     	//�Եڶ���оƬ����д����         
	Send1Byte_MAX7219(data);
//	CLK_MAX7219(1);								//ʱ�������أ����͵�ַ
	
	delay(DelayTime_MAX7219);
	Send1Byte_MAX7219(REG_NO_OP);	//�Ե�һ��оƬ���пղ���
	Send1Byte_MAX7219(0x00);
	
	LOAD_MAX7219(1);  						//LOAD�ø߽���MAX7219оƬ	
	delay(DelayTime_MAX7219);
}

/***********************************************************************
�������ƣ�void Write3rdChip_MAX7219(uint16_t addr,uint16_t data);
��    �ܣ�MAX7219����3��оƬ��д���ݳ���
���������
���������
��дʱ�䣺2017-01-21
�� д �ˣ�FangYIkaii
ע    �⣺LOAD�ߵ�ƽ
          1.д������оƬ(����,��ַ) 2.д�ڶ���оƬ(��) 3.д��һ��оƬ(��)
          LOAD�͵�ƽ
***********************************************************************/
void Write3rdChip_MAX7219(uint16_t addr,uint16_t data)
{
	LOAD_MAX7219(0); 							//LOAD�õ�ѡͨMAX7219оƬ
	
	delay(DelayTime_MAX7219); 	    //�Ե�����оƬ����д����        
	Send1Byte_MAX7219(addr);     
	Send1Byte_MAX7219(data);
//	CLK_MAX7219(1);								//ʱ�������أ����͵�ַ	
	
	delay(DelayTime_MAX7219);        //�Եڶ���оƬ���пղ���         
	Send1Byte_MAX7219(REG_NO_OP);
	Send1Byte_MAX7219(0x00);
//	CLK_MAX7219(1);								//ʱ�������أ����͵�ַ
	
	delay(DelayTime_MAX7219);
	Send1Byte_MAX7219(REG_NO_OP);	//�Ե�һ��оƬ���пղ���
	Send1Byte_MAX7219(0x00);
	
	LOAD_MAX7219(1);  						//LOAD�ø߽���MAX7219оƬ	
	delay(DelayTime_MAX7219);
}


/***********************************************************************
�������ƣ�void DisplayChar_MAX7219 (uint8_t addr,uint8_t data,uint8_t chipno) 
��    �ܣ�MAX7219��ʾ���ݳ���
���������
���������
��дʱ�䣺2017-01-21
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/
void DisplayChar_MAX7219(uint8_t addr,uint8_t data,uint8_t chipno) 
{
	if(chipno==1)
	{
		Write1stChip_MAX7219(addr,data);
	}
	else if(chipno==2)
	{
		Write2ndChip_MAX7219(addr,data);
	}		
	else if(chipno==3)
	{
		Write3rdChip_MAX7219(addr,data);
	}	
} 

/***********************************************************************
�������ƣ�void DisplayDigitalTube1_4Num_MAX7219 (uint16_t data,uint8_t no,uint8_t point) 
��    �ܣ���1��2��4λ�������ʾ������ʾ��4λ
�������������ֵ������ܱ�ţ�С����λ��
���������
��дʱ�䣺2017-01-21
�� д �ˣ�FangYikaii
ע    �⣺
***********************************************************************/
void DisplayDigitalTube1_4Num_MAX7219(uint16_t data,uint8_t no,uint8_t point) 
{
	uint8_t code;
	/*��Ҫ*/
	Init_MAX7219();					//��Ҫ�ظ����ã�������ֲ���ʾ����
	data=data%10000;				//��ʾ��4λ
	if(no==1)								//��1��4λ�����
	{
		//ǧλ
		code=data/1000;
		//���ж�Ӧ�ַ�
 		code=code_table[code];
		if(point==4)
		{
			code=code | 0x80;
		}			 
		//��һ����
		Write1stChip_MAX7219(DIG_1,code);		
		
		//��λ
		code=(data%1000)/100;
		//���ж�Ӧ���ַ�
 		code=code_table[code];		
		if(point==3)
		{
			code=code | 0x80;
		}
		//�ڶ�����
		Write1stChip_MAX7219(DIG_2,code);					

		//ʮλ
		code=(data%100)/10;
		//���ж�Ӧ�ַ�
 		code=code_table[code];			
		if(point==2)
		{
			code=code | 0x80;
		}			
		//��������
		Write1stChip_MAX7219(DIG_3,code);					

		//��λ
		code=data%10;
		//���ж�Ӧ�ַ�
 		code=code_table[code];			
		if(point==1)
		{
			code=code | 0x80;
		}				
		//���ĸ���
		Write1stChip_MAX7219(DIG_4,code);						
	}
	else if(no==2)					//��2��4λ�����
	{
		//ǧλ
		code=data/1000;
		//���ж�Ӧ����
 		code=code_table[code];
		if(point==4)
		{
			code=code | 0x80;
		}
    //�������
		Write1stChip_MAX7219(DIG_5,code);					

		//��λ
		code=(data%1000)/100;
		//���ж�Ӧ����
 		code=code_table[code];		
		if(point==3)
		{
			code=code | 0x80;
		}				
		//��������
		Write1stChip_MAX7219(DIG_6,code);					

		//ʮλ
		code=(data%100)/10;
		//���ж�Ӧ����
 		code=code_table[code];			
		if(point==2)
		{
			code=code | 0x80;
		}			
		//���߸���
		Write1stChip_MAX7219(DIG_7,code);					

		//��λ
		code=data%10;
		//���ж�Ӧ����
 		code=code_table[code];			
		if(point==1)
		{
			code=code | 0x80;
		}			
		//�ڰ˸���
		Write1stChip_MAX7219(DIG_8,code);					
	}
}

/***********************************************************************
�������ƣ�void DisplayDigitalTube2_2Num_MAX7219 (uint8_t data,uint8_t no,uint8_t point)
��    �ܣ���1��2��3��4��2λ�������ʾ������ʾ��2λ
�����������ֵ������ܱ�ţ�С����λ��
���������
��дʱ�䣺2017-01-21
�� д �ˣ�FangYIkaii
ע    �⣺
***********************************************************************/
void DisplayDigitalTube2_2Num_MAX7219(uint8_t data,uint8_t no,uint8_t point)
{
	uint8_t code;
	/*��Ҫ*/
	Init_MAX7219();					//��Ҫ�ظ����ã�������ֲ���ʾ����
	data=data%100;					//��ʾ��2λ
	if(no==1)								//��1��2λ�����
	{
		//ʮλ
		code=data/10;
 		code=code_table[code];	
		if(point==2)
		{
			code=code | 0x80;
		}			
		//��һ����
		Write2ndChip_MAX7219(DIG_1,code);				

		//��λ
		code=data%10;
 		code=code_table[code];			
		if(point==1)
		{
			code=code | 0x80;
		}			
		//�ڶ�����
		Write2ndChip_MAX7219(DIG_2,code);									
	}
	else if(no==2)					//��2��2λ�����
	{
		//ʮλ
		code=data/10;
 		code=code_table[code];	
		if(point==2)
		{
			code=code | 0x80;
		}			
		//��������
		Write2ndChip_MAX7219(DIG_3,code);					

		//��λ
		code=data%10;
 		code=code_table[code];			
		if(point==1)
		{
			code=code | 0x80;
		}			
		//���ĸ���
		Write2ndChip_MAX7219(DIG_4,code);					
	
				
	}	
	else if(no==3)					//��3��2λ�����
	{
		//ʮλ
		code=data/10;
 		code=code_table[code];	
		if(point==2)
		{
			code=code | 0x80;
		}			
		//�������
		Write2ndChip_MAX7219(DIG_5,code);					

		//��λ
		code=data%10;
 		code=code_table[code];			
		if(point==1)
		{
			code=code | 0x80;
		}			
		//��������
		Write2ndChip_MAX7219(DIG_6,code);						
	}		
	else if(no==4)					//��4��2λ�����
	{
		//ʮλ
		code=data/10;
 		code=code_table[code];	
		if(point==2)
		{
			code=code | 0x80;
		}			
		//���߸���
		Write2ndChip_MAX7219(DIG_7,code);					
	
		//��λ
		code=data%10;
 		code=code_table[code];			
		if(point==1)
		{
			code=code | 0x80;
		}			
		//��λ
		Write2ndChip_MAX7219(DIG_8,code);					
	}	
}


/***********************************************************************
�������ƣ�void DisplayDigitalTube3_4Num_MAX7219 (uint16_t data,uint8_t no,uint8_t point) 
��    �ܣ���1��2��4λ�������ʾ������ʾ��4λ
�������������ֵ������ܱ�ţ�С����λ��
���������
��дʱ�䣺2017-01-21
�� д �ˣ�FangYIkaii
ע    �⣺
***********************************************************************/
void DisplayDigitalTube3_4Num_MAX7219 (uint16_t data,uint8_t no,uint8_t point) 
{
	uint8_t code;
	/*��Ҫ*/
	Init_MAX7219();					//��Ҫ�ظ����ã�������ֲ���ʾ����
	data=data%10000;				//��ʾ��4λ
	if(no==1)								//��1��4λ�����
	{
		//ǧλ
		code=data/1000;
 		code=code_table[code];
		if(point==4)
		{
			code=code | 0x80;
		}			
		//��һ����
		Write3rdChip_MAX7219(DIG_1,code);

		//��λ
		code=(data%1000)/100;
 		code=code_table[code];		
		if(point==3)
		{
			code=code | 0x80;
		}			
		//�ڶ�����
		Write3rdChip_MAX7219(DIG_2,code);					

		//ʮλ
		code=(data%100)/10;
 		code=code_table[code];			
		if(point==2)
		{
			code=code | 0x80;
		}			
		//��������
		Write3rdChip_MAX7219(DIG_3,code);					

		//��λ
		code=data%10;
 		code=code_table[code];			
		if(point==1)
		{
			code=code | 0x80;
		}			
		//���ĸ���
		Write3rdChip_MAX7219(DIG_4,code);							
	}
	else if(no==2)					//��2��4λ�����
	{
		//ǧλ
		code=data/1000;
 		code=code_table[code];
		if(point==4)
		{
			code=code | 0x80;
		}			
		//�������
		Write3rdChip_MAX7219(DIG_5,code);					

		//��λ
		code=(data%1000)/100;
 		code=code_table[code];		
		if(point==3)
		{
			code=code | 0x80;
		}			
		//��������
		Write3rdChip_MAX7219(DIG_6,code);					

		//ʮλ
		code=(data%100)/10;
 		code=code_table[code];			
		if(point==2)
		{
			code=code | 0x80;
		}			
		//���߸���
		Write3rdChip_MAX7219(DIG_7,code);					

		//��λ
		code=data%10;
 		code=code_table[code];			
		if(point==1)
		{
			code=code | 0x80;
		}			
		//�ڰ˸���
		Write3rdChip_MAX7219(DIG_8,code);					
	}
}
