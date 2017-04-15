//========================================
//<--Ԥ���崦����ֹ�ظ�����-->
#ifndef _FrequencyCapture_H
#define _FrequencyCapture_H

//========================================
//ͷ�ļ�





//========================================
//�궨��

#define 						Fre_NOINTMAXTIME								3								//��׽�жϲ����������ʱ�� Ĭ��10s



//========================================
//�˿ڶ���
/*
TIM1.channel1 -- PA8         	TIM2.channel1 -- PA0
TIM1.channel2 -- PA9        	TIM2.channel2 -- PA1
TIM1.channel3 -- PA10        	TIM2.channel3 -- PA2
TIM1.channel4 -- PA11         TIM2.channel4 -- PA3


TIM3.channel1 -- PA6         	TIM4.channel1 -- PB6
TIM3.channel2 -- PA7        	TIM4.channel2 -- PB7
TIM3.channel3 -- PB0        	TIM4.channel3 -- PB8
TIM3.channel4 -- PB1         	TIM4.channel4 -- PB9

TIM5.channel1 -- PA0         	
TIM5.channel2 -- PA1        	
TIM5.channel3 -- PA2        	
TIM5.channel4 -- PA3         

*/

#define 			FreqCap1TIM1_GPIOX												GPIOA
#define 			FreqCap2TIM1_GPIOX												GPIOA
#define 			FreqCap3TIM1_GPIOX												GPIOA
#define 			FreqCap4TIM1_GPIOX												GPIOA

#define 			FreqCap1TIM2_GPIOX												GPIOA
#define 			FreqCap2TIM2_GPIOX												GPIOA
#define 			FreqCap3TIM2_GPIOX												GPIOA
#define 			FreqCap4TIM2_GPIOX												GPIOA

#define 			FreqCap1TIM3_GPIOX												GPIOA
#define 			FreqCap2TIM3_GPIOX												GPIOA
#define 			FreqCap3TIM3_GPIOX												GPIOB
#define 			FreqCap4TIM3_GPIOX												GPIOB

#define 			FreqCap1TIM4_GPIOX												GPIOB
#define 			FreqCap2TIM4_GPIOX												GPIOB
#define 			FreqCap3TIM4_GPIOX												GPIOB
#define 			FreqCap4TIM4_GPIOX												GPIOB

#define 			FreqCap1TIM5_GPIOX												GPIOA
#define 			FreqCap2TIM5_GPIOX												GPIOA
#define 			FreqCap3TIM5_GPIOX												GPIOA
#define 			FreqCap4TIM5_GPIOX												GPIOA


#define 			FreqCap1TIM1_RCC_APB2Periph_GPIOX					RCC_APB2Periph_GPIOA
#define 			FreqCap2TIM1_RCC_APB2Periph_GPIOX					RCC_APB2Periph_GPIOA
#define 			FreqCap3TIM1_RCC_APB2Periph_GPIOX					RCC_APB2Periph_GPIOA
#define 			FreqCap4TIM1_RCC_APB2Periph_GPIOX					RCC_APB2Periph_GPIOA

#define 			FreqCap1TIM2_RCC_APB2Periph_GPIOX					RCC_APB2Periph_GPIOA
#define 			FreqCap2TIM2_RCC_APB2Periph_GPIOX					RCC_APB2Periph_GPIOA
#define 			FreqCap3TIM2_RCC_APB2Periph_GPIOX					RCC_APB2Periph_GPIOA
#define 			FreqCap4TIM2_RCC_APB2Periph_GPIOX					RCC_APB2Periph_GPIOA

#define 			FreqCap1TIM3_RCC_APB2Periph_GPIOX					RCC_APB2Periph_GPIOA
#define 			FreqCap2TIM3_RCC_APB2Periph_GPIOX					RCC_APB2Periph_GPIOA
#define 			FreqCap3TIM3_RCC_APB2Periph_GPIOX					RCC_APB2Periph_GPIOB
#define 			FreqCap4TIM3_RCC_APB2Periph_GPIOX					RCC_APB2Periph_GPIOB

#define 			FreqCap1TIM4_RCC_APB2Periph_GPIOX					RCC_APB2Periph_GPIOB
#define 			FreqCap2TIM4_RCC_APB2Periph_GPIOX					RCC_APB2Periph_GPIOB
#define 			FreqCap3TIM4_RCC_APB2Periph_GPIOX					RCC_APB2Periph_GPIOB
#define 			FreqCap4TIM4_RCC_APB2Periph_GPIOX					RCC_APB2Periph_GPIOB

#define 			FreqCap1TIM5_RCC_APB2Periph_GPIOX					RCC_APB2Periph_GPIOA
#define 			FreqCap2TIM5_RCC_APB2Periph_GPIOX					RCC_APB2Periph_GPIOA
#define 			FreqCap3TIM5_RCC_APB2Periph_GPIOX					RCC_APB2Periph_GPIOA
#define 			FreqCap4TIM5_RCC_APB2Periph_GPIOX					RCC_APB2Periph_GPIOA

#define 			FreqCap1TIM1_GPIO_PIN											GPIO_Pin_8
#define 			FreqCap2TIM1_GPIO_PIN											GPIO_Pin_9
#define 			FreqCap3TIM1_GPIO_PIN											GPIO_Pin_10
#define 			FreqCap4TIM1_GPIO_PIN											GPIO_Pin_11

#define 			FreqCap1TIM2_GPIO_PIN											GPIO_Pin_0
#define 			FreqCap2TIM2_GPIO_PIN											GPIO_Pin_1
#define 			FreqCap3TIM2_GPIO_PIN											GPIO_Pin_2
#define 			FreqCap4TIM2_GPIO_PIN											GPIO_Pin_3

#define 			FreqCap1TIM3_GPIO_PIN											GPIO_Pin_6
#define 			FreqCap2TIM3_GPIO_PIN											GPIO_Pin_7
#define 			FreqCap3TIM3_GPIO_PIN											GPIO_Pin_0
#define 			FreqCap4TIM3_GPIO_PIN											GPIO_Pin_1

#define 			FreqCap1TIM4_GPIO_PIN											GPIO_Pin_6
#define 			FreqCap2TIM4_GPIO_PIN											GPIO_Pin_7
#define 			FreqCap3TIM4_GPIO_PIN											GPIO_Pin_8
#define 			FreqCap4TIM4_GPIO_PIN											GPIO_Pin_9

#define 			FreqCap1TIM5_GPIO_PIN											GPIO_Pin_0
#define 			FreqCap2TIM5_GPIO_PIN											GPIO_Pin_1
#define 			FreqCap3TIM5_GPIO_PIN											GPIO_Pin_2
#define 			FreqCap4TIM5_GPIO_PIN											GPIO_Pin_3



#define 			PULSEGeneration_GPIOX											GPIOE
#define 			PULSEGeneration_RCC_APB2Periph_GPIOX			RCC_APB2Periph_GPIOE
#define 			PULSEGeneration_GPIO_PIN									GPIO_Pin_2

#define 			PULSEGeneration(x)		((x) ? (GPIO_SetBits(PULSEGeneration_GPIOX, PULSEGeneration_GPIO_PIN)) : (GPIO_ResetBits(PULSEGeneration_GPIOX, PULSEGeneration_GPIO_PIN)))


//========================================
//�����������

struct FreqCapResult 
{
	uint8_t IsUsedFlag;				//��ʱ���Ƿ����ñ�־
	uint8_t NOINT_s;					//û��⵽����ȴ�ʱ��Ĭ��3S -- Fre_NOINTMAXTIME ����
	uint8_t count;
	uint16_t pulse1;					//��һ������ֵ
	uint16_t pulse2;					//�ڶ�������ֵ
	uint32_t pulse;						//�����ֵ
	float Freq;								//Ƶ��ֵ
};
extern struct FreqCapResult TIM1FreqCap[4];
extern struct FreqCapResult TIM4FreqCap[4];

extern uint8_t FreqCapChannelNO;


//========================================
//�����������

extern void FreqCap_Configuration(u16 arr,u16 psc);					//���PULSE������




//========================================
//<--Ԥ�������-->
#endif



