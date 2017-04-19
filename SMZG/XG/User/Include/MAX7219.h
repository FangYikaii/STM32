//========================================
//<--Ԥ���崦����ֹ�ظ�����-->
#ifndef _MAX7219_H
#define _MAX7219_H

//========================================
//ͷ�ļ�
#define 			NOPOINT			0
#define 			ENPOINT			1

#define 			SEGLED1			1			
#define 			SEGLED2			2	
#define 			SEGLED3			3	
#define 			SEGLED4			4	

//========================================
//�궨��

#define 			REG_NO_OP 				0x00 		//����ղ����Ĵ��� 
#define 			DIG_1 						0x01    //���������1�Ĵ���   
#define 			DIG_2 						0x02    //���������2�Ĵ���         
#define 			DIG_3 						0x03    //���������3�Ĵ���        
#define 			DIG_4 						0x04    //���������4�Ĵ���        
#define 			DIG_5 						0x05    //���������5�Ĵ���      
#define 			DIG_6 						0x06    //���������6�Ĵ���       
#define 			DIG_7 						0x07    //���������7�Ĵ���        
#define 			DIG_8 						0x08    //���������8�Ĵ���         
#define 			REG_DECODE 				0x09   	//������ƼĴ���   
#define 			REG_INTENSITY 		0x0a   	//���ȿ��ƼĴ��� 
#define 			REG_SCAN_LIMIT 		0x0b   	//ɨ����޼Ĵ��� 
#define 			REG_SHUTDOWN 			0x0c   	//�ض�ģʽ�Ĵ���
#define 			REG_DISPLAY_TEST 	0x0f  	//���Կ��ƼĴ���
#define 			INTENSITY_MIN 		0x00    //���������ʾ����      
#define 			INTENSITY_MAX 		0x0f    //���������ʾ����       

#define 			CHIP_1						0x01		//1��оƬ
#define 			CHIP_2						0x02		//2��оƬ


#define 			DelayTime_MAX7219	1

//========================================
//�˿ڶ���

#define 			DIN_MAX7219_GPIOX													GPIOE
#define 			LOAD_MAX7219_GPIOX												GPIOE
#define 			CLK_MAX7219_GPIOX													GPIOE

#define 			DIN_MAX7219_RCC_APB2Periph_GPIOX					RCC_APB2Periph_GPIOE
#define 			LOAD_MAX7219_RCC_APB2Periph_GPIOX					RCC_APB2Periph_GPIOE
#define 			CLK_MAX7219_RCC_APB2Periph_GPIOX					RCC_APB2Periph_GPIOE

#define 			DIN_MAX7219_GPIO_PIN											GPIO_Pin_1
#define 			LOAD_MAX7219_GPIO_PIN											GPIO_Pin_0
#define 			CLK_MAX7219_GPIO_PIN											GPIO_Pin_2


#define 			DIN_MAX7219(x)   				((x) ? (GPIO_SetBits(DIN_MAX7219_GPIOX, DIN_MAX7219_GPIO_PIN)) : (GPIO_ResetBits(DIN_MAX7219_GPIOX, DIN_MAX7219_GPIO_PIN)))
#define 			LOAD_MAX7219(x)    			((x) ? (GPIO_SetBits(LOAD_MAX7219_GPIOX, LOAD_MAX7219_GPIO_PIN)) : (GPIO_ResetBits(LOAD_MAX7219_GPIOX, LOAD_MAX7219_GPIO_PIN)))
#define 			CLK_MAX7219(x)   				((x) ? (GPIO_SetBits(CLK_MAX7219_GPIOX, CLK_MAX7219_GPIO_PIN)) : (GPIO_ResetBits(CLK_MAX7219_GPIOX, CLK_MAX7219_GPIO_PIN)))

				
//========================================
//�����������




//========================================
//�����������
extern void MAX7219_Configuration(void);																							    //���MAX7219������
extern void DisplayDigitalTube1_4Num_MAX7219 (uint16_t data,uint8_t no,uint8_t point);	  //��1��2��4λ�������ʾ������ʾ��4λ
extern void DisplayDigitalTube2_2Num_MAX7219 (uint8_t data,uint8_t no,uint8_t point);	    //��1��2��3��4��2λ�������ʾ������ʾ��4λ
extern void DisplayDigitalTube3_4Num_MAX7219 (uint16_t data,uint8_t no,uint8_t point);	  //��1��2��4λ�������ʾ������ʾ��4λ

extern void GearDisplay(uint8_t gear, uint8_t no);																		    //��λ��Ϣ��ʾ
extern void LoaderSystemDisplay(void);																										//װ�ػ�ϵͳ������ʾ
extern void ErrorDisplay(uint8_t Error);																									//������Ϣ��ʾ
//========================================
//<--Ԥ�������-->
#endif



