һ����������
1.	ϵͳ��ʼ��
��1��	��ʼ��ϵͳʱ��
��2��	��ʼ��IO����ŷ�M1/M2/M3/M4;BR/RF/AS/XX��
��3��	��ʼ��MAX7219
��4��	��ʼ��TIM5��ʱ��
��5��	��ʼ�����岶׽��ת�٣�
��6��	��ʼ��CAN
2.	��������
��1��	IO���ã���λʱ��ɨ��ģʽ��10ms��
ControllerInfo.ScanTimeMode=GearScanT10ms;		//��λʱ��ɨ��ģʽ�ó�ʼֵ	
��2��	LEDָʾ����ʾ����Դָʾ����
LedValue=(LedValue & 0xFE) | 0x01;						//LEDָʾ��ֵ
I2C_WriteData_PCF8574(0x70, LedValue);				//LED��ʾ����--��Դָʾ����	
��3��	��ʾ���ã�ѹ����ʾ��ת����ʾ
XG.ChannelNo[0]=1;							//ѹ����ʾֵΪ1��ͨ��	1--6
XG.ChannelNo[1]=1;						//ת����ʾֵΪ2��ͨ��	2--4
XG.Function=XG.Function%100+XG.ChannelNo[0]*1000+XG.ChannelNo[1]*100;			//ͨ����ʾ
��4��	ת�ٱ����ã�1-4�����������ٱ�
��5��	����ģʽ���ã��ֶ�
ShiftModeStatus=HandShiftMode;					//Ĭ�ϣ��ֶ�����ģʽ
3.	ѭ��
��1��	IOɨ��(ɨ������flagctrl.Bits.ScanTimeFlag)
1.	IOɨ���־λ-false
2.	����ģʽ���ֶ�-�ֶ���λɨ��ʹ���
�Զ�-�Զ���λɨ��ʹ���
��2��	��ʾ����ɨ�裨ɨ������flagTIM5.Bits.Tisec_Flag��1s��
1.	��ʾ����ɨ���־λ-false
2.	װ�ػ�ϵͳ������ʾ
��3��	���岶��ɨ�裨ɨ������flagTIM5.Bits.Freq_1sec_Flag��1s��
1.	���岶��ɨ���־λ-false
2.	ͨ��1��2��3���岶�񣬱��棬����
3.	����ת�١������ת�ټ���
4.	ת����ʾ
��4��	���̲�����ɨ������
�����ֵ�Ѿ���ȡ��PCF8574.Bits.KeyScan_Flag==FALSE:
���Ϊ���Զ�/�ֶ����л�����:KeyValue_PCF8574==7
1.	��ֵ��ȡ��־λ��λ��PCF8574.Bits.KeyScan_Flag==TRUE;
2.	�����ǰģʽ--�ֶ�����ShiftMdeStatus==AutoShiftMode
           Ledָʾ��ֵ= (LedValue & 0x7F) | 0x80;
�Զ�����ShiftModeStatus==HandShiftMode
 	   Ledָʾ��ֵ=LedValue & 0x7F;		
3.	LED��ʾ����
����IO���ֿ������ɼ�
1����ȡ�ź�
��1��DIIN1:�ӻ���ѡ������ȡ24V�ź�M1��1������PE8
��2��DIIN2:�ӻ���ѡ������ȡ24V�ź�M2��2������PE7
��3��DIIN3:�ӻ���ѡ������ȡ24V�ź�M3��3������PE10
��4��DIIN4:�ӻ���ѡ������ȡ24V�ź�M4��4������PE9
��5��DIIN5:�ӻ���ѡ������ȡ24V�ź�AS���յ�����PE12
��6��DIIN6:�ӻ���ѡ������ȡ24V�ź�RF����������PE11
��7��DIIN7:���ƶ�����ȡ24V�ź�BR���ƶ�����PE14
��8��DIIN8��Ԥ����PE13
2������ź�
��1��DOOUT1�����Ƶ�ŷ�M1��1������PA0
��2��DOOUT2�����Ƶ�ŷ�M2��2������PA1
��3��DOOUT3�����Ƶ�ŷ�M3��3������PA2
��4��DOOUT4�����Ƶ�ŷ�M4��4������PA3
��5��DOOUT5��ģ���ƶ��ź�BR���ƶ���--PA6
��6��DOOUT1�����Ƶ�ŷ�BF����������PA7
��6��DOOUT1�����Ƶ�ŷ�AS���յ�����PB0
��6��DOOUT1��Ԥ����PB1
3����ȡ����
struct ControllerData				
{
	uint8_t ScanTimeMode;	//��λɨ��ʱ��ģʽ				
	uint8_t NowGear;			//��ǰ��λ��Ϣ	-- ��ȡ���
	uint8_t NowBrake;			//��ǰɲ��״̬	-- ��ȡ���
	uint8_t GoalGear;			//Ŀ�굲λ			-- ����ֵ
	uint8_t ProcessGear;		//���̵�λ      -- ����ֵ
	uint8_t SuggestGear;		//�Ƽ���λ      -- Ԥ��ֵ
	uint8_t	gearinfo;			//��λ					-- ������
	uint8_t brakeinfo;			//�ƶ��ź�			-- ������
	uint8_t gearCGcount;		//��λ�仯��������
	uint8_t brakeCGcount;		//��λ�仯��������	
};
4����־λ
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
5��IO��ʼ����void IOControl_Init(void)��
��1��GPIO��ʼ��
l	����:M1/M2/M3/M4/AS/RF/BR/XX��
�˿ڷ�ת�ٶȣ�GPIO_Speed_50MHz; 
�������룺GPIO_Mode_IN_FLOATING
l	���:M1/M2/M3/M4/BR/AS/RF/XX��
�˿ڷ�ת�ٶȣ�GPIO_Speed_50MHz; 
��ͨ���������GPIO_Mode_Out_PP
��2��GPIO��0
6���ֶ���λɨ��ʹ���
void GearScanVSDeal_HandShiftMode(void)
{		
	ReadGearLine_Status();					//��λ��Ϣ��ȡ
	GearToSolenoidValve(ControllerInfo.NowGear,ControllerInfo.NowBrake);  //���ͣ���ǰ��λ��Ϣ�͵�ǰɲ��״̬������ŷ����ƶ��ź�
}
7���Զ���λɨ��ʹ���
void GearScanVSDeal_AutoShiftMode(void)
{		
	ReadGearLine_Status();					//��λ��Ϣ��ȡ
	if(ControllerInfo.NowBrake==0)	        //�Ƿ�ɲ�� == ��
	{
		if(ControllerInfo.NowGear/0x10==0)		//ǰ����
		{	
			
		}
		else if(ControllerInfo.NowGear/0x10==1)			//���˵�
		{
			
		}			
	}
	else //�Ƿ�ɲ�� == ��
	{
		
	}	
	GearToSolenoidValve(ControllerInfo.NowGear,ControllerInfo.NowBrake);
	
}
8����λ��Ϣ��ȡ
����λ��Ӧ�ɼ�ֵ�б�
		ǰ���� V     �յ�N 			 ���˵�R        KD
P   0x14				 0x34				 0x24		 0xXX & 0x01=0x00
1   0x10				 0x30				 0x20		 0xXX & 0x01=0x00	
2   0x12				 0x32				 0x22		 0xXX & 0x01=0x00
3   0x16				 0x36				 0x26 	     0xXX & 0x01=0x00
4   0x1E				 0x3E				 0x2E 		  0xXX & 0x01=0x00
����MAX7219����(SPI)
1���˿�
l	�ܽ�1��DIN��PE1
������������˿ڣ�ʱ��������ʱ���ݱ������ڲ�16λ�Ĵ���
l	�ܽ�12��LOAD/CS��PE0
LOAD:��������
CS:��������
l	�ܽ�13��CLK��PE2
ʱ�����������
l	�ܽ�14-17,20-23��7�κ�С��������
#define 			REG_NO_OP 				    0x00    //����ղ����Ĵ��� 
#define 			DIG_1 						0x01    //���������1�Ĵ���   
#define 			DIG_2 						0x02    //���������2�Ĵ���         
#define 			DIG_3 						0x03    //���������3�Ĵ���        
#define 			DIG_4 						0x04    //���������4�Ĵ���        
#define 			DIG_5 						0x05    //���������5�Ĵ���      
#define 			DIG_6 						0x06    //���������6�Ĵ���       
#define 			DIG_7 						0x07    //���������7�Ĵ���        
#define 			DIG_8 						0x08  //���������8�Ĵ���         #define 			REG_DECODE 				0x09   	//������ƼĴ���   
#define 			REG_INTENSITY 		        0x0a   	//���ȿ��ƼĴ��� 
#define 			REG_SCAN_LIMIT 		        0x0b   	//ɨ����޼Ĵ��� 
#define 			REG_SHUTDOWN 			0x0c   	//�ض�ģʽ�Ĵ���
#define 			REG_DISPLAY_TEST 	        0x0f  	//���Կ��ƼĴ���
#define 			INTENSITY_MIN 		        0x00    //���������ʾ����      
#define 			INTENSITY_MAX 		        0x0f    //���������ʾ����
2��MAX7219��ʼ��
��1��  GPIO��ʼ��
l	�˿ڣ�CLK,LOAD/CS,DIN
�˿ڷ�ת�ٶȣ�GPIO_Speed_50MHz; 
��ͨ���������GPIO_Mode_Out_PP
��2��CLK��DIN��GPIO��0��LOAD/CS��GPIO��1
��3��1/2/3ƬMAX7219��ʼ��
l	����ģʽ
Write1stChip_MAX7219(REG_DISPLAY_TEST,0x00);      //ѡ����ģʽ��0xX0��			0x01 --testģʽ
l	��ʼ����
Write1stChip_MAX7219(REG_INTENSITY,0x02);        	//���ó�ʼ����
l	ȫ��ʾ
Write1stChip_MAX7219(REG_SCAN_LIMIT,0x07);        //����Ϊȫ��ʾ
l	����ģʽ
Write1stChip_MAX7219(REG_DECODE,0x00);       			//ѡ��B����ģʽ--0xFF,�ǽ���ģʽ--0x00
l	������������ģʽ
Write2ndChip_MAX7219(REG_SHUTDOWN,0x01);         	//������������ģʽ��0xX1��	0x00 --�ر���ʾ	
��5��	���1/2/3ƬMAX721
3��װ�ػ�������ʾ
void LoaderSystemDisplay(void)
{
		DisplayDigitalTube3_4Num_MAX7219 (XG.PressureShow/10,1,3);						//���۴�ǻѹ��__��1��2��4λ�������ʾ������ʾ��4λ
		DisplayDigitalTube3_4Num_MAX7219 (XG.Function,2,0);								//ͨ����Ϣ��ʾ������ֵ__��1��2��4λ�������ʾ������ʾ��4λ		
		DisplayDigitalTube1_4Num_MAX7219 (XG.PumpSpeed,1,0);							//����ת��__��1��2��4λ�������ʾ������ʾ��4λ
		DisplayDigitalTube1_4Num_MAX7219 (XG.SpeedShow,2,0);								//����ת��__��1��2��4λ�������ʾ������ʾ��4λ
		GearDisplay(ControllerInfo.SuggestGear,2);		
		GearDisplay(ControllerInfo.ProcessGear,1);			//��ǰ��λ��Ϣ��ʾ
		if(XG.Throttle>=100)
		{
			DisplayDigitalTube2_2Num_MAX7219 (99,3,0);									//���ſ���__��1��2��3��4��2λ�������ʾ������ʾ��4λ
		}
		else
		{
			DisplayDigitalTube2_2Num_MAX7219 (XG.Throttle,3,0);							//���ſ���__��1��2��3��4��2λ�������ʾ������ʾ��4λ			
		}
		//������Ϣ��ʾ__��1��2��3��4��2λ�������ʾ������ʾ��4λ
		ErrorDisplay(ErrorMessage);
}
��1��	���۴�ǻѹ����ʾ������������ܣ���һƬ��4λ��
��2��	ͨ����Ϣ��ʾ������������ܣ���2Ƭ��4λ��
��3��	����ת����ʾ����һ������ܣ���һƬ��4λ��---CAN��ȡ
��4��	����ת����ʾ����һ������ܣ���2Ƭ��4λ��---�������
��5��	���ſ�����ʾ
��6��	������Ϣ��ʾ
�ġ�PCF8574���ã�I2C��
���ڣ�дLED��ʾ��PCF8574д���ݵ�0x70��ַ����������ɨ�裨PCF8574��0x73��������
1���˿�
SCL��PE5
SDA��PE3
��PCF8574�ĵ�ַ��
��ַ(0x70) -- LED��ʾ���Ƶ�ַ
��ַ(0x73) -- ������ȡ���Ƶ�ַ
��ַ(0x7A) -- ��ŷ�����оƬ����źŶ�ȡ��ַ(δ��)
2��PCF8574��ʼ��
��1��GPIO��ʼ��
l	�˿ڣ�SCL��SDA
�˿ڷ�ת�ٶȣ�GPIO_Speed_50MHz; 
��ͨ���������GPIO_Mode_Out_PP
��2��SCL��SDA��GPIO��0
��3����ʼ��LED��ʾ���ƣ���PCF8574�ĵ�ַ0x70д����0x00
I2C_WriteData_PCF8574(0x70, 0x00);
{
	//PCF8574��I2C��ʼ�ź�
I2C_Start_PCF8574();
// PCF8574��I2Cдһ���ֽڳ��򣺵�ַ0x70
I2C_Write1Byte_PCF8574(addr);
// PCF8574��I2Cдһ���ֽڳ��򣺵�ַ0x00
I2C_Write1Byte_PCF8574(data);	
// PCF8574��I2Cֹͣ�ź�
I2C_Stop_PCF8574();	
}
3��PCF8574д����
void I2C_WriteData_PCF8574(uint8_t addr, uint8_t data)
{
	I2C_Start_PCF8574();
	I2C_Write1Byte_PCF8574(addr);
	I2C_Write1Byte_PCF8574(data);	
	I2C_Stop_PCF8574();	
}
//��    �ܣ�PCF8574��I2C��ʼ�ź�
void I2C_Start_PCF8574(void)
{

	SDA_PCF8574(1);
	delay(DelayTime_PCF8574);	
	SCL_PCF8574(1);
	delay(DelayTime_PCF8574);
	SDA_PCF8574(0);	
	delay(DelayTime_PCF8574);	
}
//��    �ܣ�PCF8574��I2Cֹͣ�ź�
void I2C_Stop_PCF8574(void)
{
	SDA_PCF8574(0);
	delay(DelayTime_PCF8574);	
	SCL_PCF8574(1);
	delay(DelayTime_PCF8574);
	SDA_PCF8574(1);	
	delay(DelayTime_PCF8574);	
}
//��    �ܣ�PCF8574��I2Cдһ���ֽڳ���
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
4��PCF8574������
uint8_t I2C_RecData_PCF8574(uint8_t addr)
{
	uint8_t temp;
	I2C_Start_PCF8574();
	I2C_Write1Byte_PCF8574(addr);
	temp=I2C_Rec1Byte_PCF8574();
	I2C_Stop_PCF8574();		
	return temp;
}
//����һ���ֽڵ�����
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
5������ɨ�����ͨ��д���ݵ�0x73��������ֵ
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
�塢��ʱ��
��ʱ����7��������2watchdog timers���������Ź������ڿ��Ź���
������ʱ����TIM6��TIM7[��������ܣ��ۼ�ʱ������������Ԥ��ֵ�������жϻ򴥷�DMA][���ϼ�����-- Timer5 ����һ��Ķ�ʱ��ͬʱ��ΪUSARTx��ͨ�ų�ʱ����Ĵ���
ͨ�ö�ʱ����TIM2��TIM3��TIM4��TIM5[������������Ƶ�ʡ�����������PWM����ȳ���][���ϣ����¼�����--- Timer2 ����USBͨ�ŵľ�ȷ��ʱ
�߼���ʱ����TIM1[����������������ӿڡ�ɲ������][�������¼���]

ʱ������Systick=72MHz��APB1Ԥ��Ƶ���ķ�Ƶϵ������Ϊ2����PCK1�պ����ֵ36MHz
Ԥ��Ƶ:TIMx_PSC=0����Ƶ  TIMx_PSC=1 2��Ƶ
1����־λ
union FlagTimer  
{ 
      uint8_t flagBits; 
      struct       
      { 
			uint8_t		T100msec_Flag 		:	1;				
			uint8_t		T1sec_Flag  			:	1;
			uint8_t		T1min_Flag			:	1;
			uint8_t 		T10msec_Flag			:	1;
			uint8_t 		T1_5sec_Flag			:	1;				
			uint8_t 		Freq_1sec_Flag		:	1;
			uint8_t 		Bit6					:	1;				
			uint8_t 		Bit7					:	1;						
      } Bits; 
};
struct TIM5Result 
{
	uint32_t ms_Record; 
    uint16_t msecond;
	uint16_t T1_5secmsCount;
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
};
2��TIME5��ʼ��
��1�����嶨ʱ���ṹ��
//��������Զ�װ�صļ���ֵ�����ڼ����Ǵ�0��ʼ�ģ�����10000�κ�Ϊ9999
TIM_TimeBaseStructure.TIM_Period = (100 - 1);
// �������Ԥ��Ƶϵ����������Ϊ0ʱ��ʾ����Ƶ����Ҫ��1
TIM_TimeBaseStructure.TIM_Prescaler = (7200-6480- 1);	
��2�������ж�
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	//�������ȼ� 0-15   ��Ӧ���ȼ� 0
NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;		//�趨ͨ��
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 15;	//�������ȼ�����  0��1
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//��Ӧ���ȼ�����
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure); 	
3��TIM5ʱ�䴦�����
Timer5.msecond++;
if(Timer5.msecond%10==0)									//10ms�ж�һ��
{
		flagUDisk.Bits.SaveTime_10ms=TRUE;	
		if(ControllerInfo.ScanTimeMode%2==1)		//GearScanT10ms = 1
		{
			flagctrl.Bits.ScanTimeFlag=TRUE;			
		}
		flagTIM5.Bits.T10msec_Flag=TRUE;
}
if(Timer5.msecond%100==0)									//100ms�ж�һ��
{
	if(ControllerInfo.ScanTimeMode%2==0)		//GearScanT100ms = 2
	{
		flagctrl.Bits.ScanTimeFlag=TRUE;			
	}		
		flagTIM5.Bits.T100msec_Flag=TRUE;
}
�������岶׽
1���˿�
���������PE2
ֻ���ˣ�TIM4.channel2  TIM4.channel3   TIM4.channel4
20·���壺
TIM1.channel1 -- PA8         TIM2.channel1 -- PA0
TIM1.channel2 -- PA9        	TIM2.channel2 -- PA1
TIM1.channel3 -- PA10        TIM2.channel3 -- PA2
TIM1.channel4 -- PA11        TIM2.channel4 -- PA3

TIM3.channel1 -- PA6         TIM4.channel1 -- PB6
TIM3.channel2 -- PA7        	TIM4.channel2 -- PB7
TIM3.channel3 -- PB0        	TIM4.channel3 -- PB8
TIM3.channel4 -- PB1         	TIM4.channel4 -- PB9

TIM5.channel1 -- PA0         	
TIM5.channel2 -- PA1        	
TIM5.channel3 -- PA2        	
TIM5.channel4 -- PA3    
2����������
struct FreqCapResult 
{
	uint8_t IsUsedFlag;				//��ʱ���Ƿ����ñ�־
	uint8_t NOINT_s;				//û��⵽����ȴ�ʱ��Ĭ��3S -- Fre_NOINTMAXTIME ����
	uint8_t count;
	uint16_t pulse1;				//��һ������ֵ
	uint16_t pulse2;				//�ڶ�������ֵ
	uint32_t pulse;				//�����ֵ
	float Freq;					//Ƶ��ֵ
};
3��FreqCap��ʼ��
��1��GPIO��ʼ��
l	���������PE2
�˿ڷ�ת�ٶȣ�GPIO_Speed_50MHz; 
��ͨ���������GPIO_Mode_Out_PP
l	TIM4.channel2  TIM4.channel3   TIM4.channel4
�˿ڷ�ת�ٶȣ�GPIO_Speed_50MHz; 
�������룺GPIO_Mode_IN_FLOATING
��2��TIM��ʱ����TIM1��TIM2��TIM3��TIM4
TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
TIM_ICInitStructure.TIM_ICFilter = 0x00;
TIM_ICInit(TIM4, &TIM_ICInitStructure);
TIM_ITConfig(TIM4, TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4|TIM_IT_Update, ENABLE);  		//�򿪶�ʱ���ж�
TIM_ClearITPendingBit(TIM4, TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4|TIM_IT_Update); 		
//����жϱ�־λ
TIM_Cmd(TIM4, ENABLE);							//������ʱ��
���ö�ʱ���Ƿ�����
��3��NVIC�ж�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);			//�������ȼ� 0-15   ��Ӧ���ȼ� 0
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =5;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
4���ж�void TIM4_IRQHandler(void)
ͨ��TIM4.channel2  TIM4.channel3   TIM4.channel4���������ز������
if(TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)
{
		TIM_ClearITPendingBit(TIM4, TIM_IT_CC1); //���־λ
		TIM4FreqCap[0].NOINT_s=0;	        
		TIM4FreqCap[0].pulse++;	              //������
}
�ߡ�CAN
1.�˿�
default��CAN1TX��PA12,CAN1RX��RA11
remap��CAN1TX��PD1,CAN1RX��PD0
default��CAN2TX��PB13,CAN2RX��RB12
remap��CAN2TX��PB6,CAN2RX��PB5
2.CAN��ʼ��
��1��GPIO��ʼ��
l	CAN1TX��CAN2TX
�ⲿʱ�ӣ�RCC_APB2PeriphClockCmd(CAN12TX_RCC_APB2Periph_GPIOX, ENABLE);
�������������GPIO_Mode_AF_PP
ʱ��Ƶ�ʣ�GPIO_Speed_50MHz;
l	CAN2RX, ,CAN2RX
�ⲿʱ�ӣ�RCC_APB2PeriphClockCmd(CAN12RX_RCC_APB2Periph_GPIOX, ENABLE);
�������룺GPIO_Mode_IPU;
ʱ��Ƶ�ʣ�GPIO_Speed_50MHz;
��2��CAN����
 /* Remap CAN1 and CAN2 GPIOs */
GPIO_PinRemapConfig(GPIO_Remap2_CAN1 , ENABLE);				//ע��IO�˿�ѡ�񣬴˴�ѡ��ӳ��ܽ�
  GPIO_PinRemapConfig(GPIO_Remap_CAN2, ENABLE); 		//ע��IO�˿�ѡ�񣬴˴�ѡ��ӳ��ܽ�
  /* CAN register init */
  CAN_DeInit(CAN1);
  CAN_DeInit(CAN2);
��3��CAN��ʼ��
CAN cell init
CAN filter init
��4���ж����ȼ�
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);			//�������ȼ� 0-15   ��Ӧ���ȼ� 0
NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);
NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
NVIC_Init(&NVIC_InitStructure);	
3��CAN�ж�

