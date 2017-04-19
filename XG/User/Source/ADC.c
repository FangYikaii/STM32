/*
����˵��:  	
            ADC�ɼ�������� --- STM32F107VCT 
						
ע�����	�ڶ���ADC�Ĵ�����ַʱ��һ��Ҫʹ��__IO uint16_t���ݸ�ʽ����������
						������ע��ADCColValue[ADCCollectTime][ADCChannelNum]������Ľṹ��					
						

������:     Masterjay   
����ʱ��:   2014-06-11 
�޸�ʱ��:   2014-06-11
*/
//========================================
//ͷ�ļ�
#include "main.h"

//========================================
//��������
volatile union FlagADCA flagADC;
struct ADCResult ADCRes;

//========================================
//��������
void ADC_Configuration(void);										//���ADC������
void ADC_ValueFilter(void);											//ADC�ɼ�ֵ�˲�


//========================================
//��ģ�麯��







/***********************************************************************
�������ƣ�void ADC_Configuration(void)
��    �ܣ����ADC������
���������
���������
��дʱ�䣺2014.4.16
�� д �ˣ�
ע    �⣺
***********************************************************************/
void ADC_Configuration(void)
{

	ADC_InitTypeDef ADC_InitStructure;      //ADC��ʼ���ṹ������
	DMA_InitTypeDef DMA_InitStructure;      //DMA��ʼ���ṹ������
  GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
  /* Configure PC0-PC6 (ADC Channel10-15) as analog input -------------------------*/
  //PC0 ��Ϊģ��ͨ��10��������                         
  GPIO_InitStructure.GPIO_Pin = ADCNN11_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(ADCNN11_GPIOX, &GPIO_InitStructure);
  RCC_APB2PeriphClockCmd(ADCNN11_RCC_APB2Periph_GPIOX, ENABLE);	
	
  //PC1 ��Ϊģ��ͨ��11��������                         
  GPIO_InitStructure.GPIO_Pin = ADCNN12_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(ADCNN12_GPIOX, &GPIO_InitStructure);	
  RCC_APB2PeriphClockCmd(ADCNN12_RCC_APB2Periph_GPIOX, ENABLE);	
	
  //PC2 ��Ϊģ��ͨ��12��������                         
  GPIO_InitStructure.GPIO_Pin = ADCNN13_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(ADCNN13_GPIOX, &GPIO_InitStructure);	
  RCC_APB2PeriphClockCmd(ADCNN13_RCC_APB2Periph_GPIOX, ENABLE);
	
  //PC3 ��Ϊģ��ͨ��13��������                         
  GPIO_InitStructure.GPIO_Pin = ADCNN14_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(ADCNN14_GPIOX, &GPIO_InitStructure);	
  RCC_APB2PeriphClockCmd(ADCNN14_RCC_APB2Periph_GPIOX, ENABLE);
	
  //PC4 ��Ϊģ��ͨ��14��������                         
  GPIO_InitStructure.GPIO_Pin = ADCNN15_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(ADCNN15_GPIOX, &GPIO_InitStructure);	
  RCC_APB2PeriphClockCmd(ADCNN15_RCC_APB2Periph_GPIOX, ENABLE);
	
  //PC5 ��Ϊģ��ͨ��15��������                         
  GPIO_InitStructure.GPIO_Pin = ADCNN16_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(ADCNN16_GPIOX, &GPIO_InitStructure);	
  RCC_APB2PeriphClockCmd(ADCNN1_RCC_APB2Periph_GPIOX, ENABLE);
	
  /* Enable DMA1 clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); 
  /* DMA1 channel1 configuration ----------------------------------------------*/
  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;    								//DMA��Ӧ���������ַ
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCRes.ADCColValue;   			//�ڴ�洢����ַ
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;														//DMA��ת��ģʽΪSRCģʽ����������Ƶ��ڴ�
  DMA_InitStructure.DMA_BufferSize = ADCCollectTime*ADCChannelNum;		   				//DMA�����С��ADCCollectTime*ADCChannelNum��,��λΪDMA_MemoryDataSize
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;							//����һ�����ݺ��豸��ַ��ֹ����
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;												//�رս���һ�����ݺ�Ŀ���ڴ��ַ����
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  	//�����������ݿ��Ϊ16λ
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;  					//DMA�����ݳߴ磬HalfWord����Ϊ16λ
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;   														//ת��ģʽ��ѭ������ģʽ��
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;														//DMA���ȼ���
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;		  														//M2Mģʽ����
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);           												//DMA_Channel1 ͨ����ʼ��
	
 	DMA_ITConfig(DMA1_Channel1,DMA1_IT_TC1, ENABLE);																//DMA_Channel1 ͨ���ж�����--6ͨ����β�������ʱԼΪ3ms	 
 	DMA_ClearITPendingBit(DMA1_IT_TC1);

	/* Enable DMA1 channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);


	/* Set the Vector Table base address at 0x08000000 */
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0000);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);			//�������ȼ� 0-15   ��Ӧ���ȼ� 0

	/* Enable the TIM5 gloabal Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;	  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	

  /* Enable ADC1 and GPIOC clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  
  /* ADC1 configuration ------------------------------------------------------*/
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;  										//������ת��ģʽ
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;		  											//����ɨ��ģʽ
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;   										//��������ת��ģʽ
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;			//ADC�ⲿ���أ��ر�״̬
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;   								//���뷽ʽ,ADCΪ12λ�У��Ҷ��뷽ʽ
  ADC_InitStructure.ADC_NbrOfChannel = ADCChannelNum;	 										//����ͨ������ADCChannelNum��
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channel10 configuration ADCͨ���飬 ��10��ͨ�� ����˳��1��ת��ʱ�� */ 
  ADC_RegularChannelConfig(ADC1, ADCNN11_ChannelNO	, 1, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADC1, ADCNN12_ChannelNO	, 2, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADC1, ADCNN13_ChannelNO	, 3, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADC1, ADCNN14_ChannelNO	, 4, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADC1, ADCNN15_ChannelNO	, 5, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADC1, ADCNN16_ChannelNO	, 6, ADC_SampleTime_55Cycles5);	
	
  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);	  															//ADC���ʹ��
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);  																	//����ADC1
  /* Enable ADC1 reset calibaration register */   
  ADC_ResetCalibration(ADC1);	  														//����У׼
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));  							//�ȴ�����У׼���
  /* Start ADC1 calibaration */
  ADC_StartCalibration(ADC1);																//��ʼУ׼
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));	   								//�ȴ�У׼���
  /* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);										//����ת����ʼ��ADCͨ��DMA��ʽ���ϵĸ���RAM����

}

/***********************************************************************
�������ƣ�void ADC_ValueFilter(void)
��    �ܣ�ADC�ɼ�ֵ�˲�--��ʱԼ3ms
����������ɼ���
���������
��дʱ�䣺2014.4.16
�� д �ˣ�
ע    �⣺
***********************************************************************/
void ADC_ValueFilter(void)
{
	uint32_t sum;
	uint16_t t;
	uint16_t i,j,k;
	float fvalue;
	for(k=0;k<ADCChannelNum;k++)									//����С˳������
	{
		for(i=0;i<(ADCCollectTime-1);i++)
		{
			for(j=i+1;j<ADCCollectTime;j++)
			{
				if(ADCRes.ADCColValue[i][k]>ADCRes.ADCColValue[j][k])
				{
					t=ADCRes.ADCColValue[i][k];
					ADCRes.ADCColValue[i][k]=ADCRes.ADCColValue[j][k];
					ADCRes.ADCColValue[j][k]=t;
				}				
			}		
			
		}		
	}
	for(k=0;k<ADCChannelNum;k++)									//��ֵ�˲�
	{
		sum=0;
		for(i=5;i<(ADCCollectTime-5);i++)
		{
			sum+=ADCRes.ADCColValue[i][k];	
		}
		fvalue=(3.3*sum)/4096;			 								//2^12=4096��ADֵת��Ϊ��ѹֵ			
		fvalue=fvalue/(ADCCollectTime-10);	
		ADCRes.ADCResValue[k]=fvalue;
//		fvalue=fvalue*1000;
//		ADCRes.ADCResValue[k]=(uint16_t)fvalue;			
	}
}

 //========================================
//��������:void TIM5_IRQHandler(void)
//��������: TIM5�жϴ������
//��ڲ���:    
//���ڲ���:      
//========================================
/**
  * @brief  This function handles TIM5 global interrupt request.
  * @param  None
  * @retval None
  */
void DMA1_Channel1_IRQHandler(void)
{
	if(DMA1_IT_TC1)
	{
		flagADC.Bits.ADCOK=TRUE;
		DMA_ClearITPendingBit(DMA1_IT_TC1);		
	}

}
