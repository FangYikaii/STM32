//========================================
//<--Ԥ���崦����ֹ�ظ�����-->
#ifndef __USB_BSP__H__
#define __USB_BSP__H__

//========================================
//ͷ�ļ�
#include "usb_defines.h"


//========================================
//�궨��



//========================================
//�����������	

typedef enum 
{
  NoTimeout = 1,
  Timeout,  
}BSP_TimeoutStatus; 



//========================================
//�����������

void BSP_Init(void);

void USB_OTG_BSP_Init (void);
void USB_OTG_BSP_TimeInit (void);
void USB_OTG_BSP_uDelay (const uint32_t usec);
void USB_OTG_BSP_mDelay (const uint32_t msec);
void USB_OTG_BSP_EnableInterrupt (void);
void USB_OTG_BSP_ConfigVBUS(void);
void USB_OTG_BSP_DriveVBUS(uint8_t state);
void USB_OTG_BSP_TimerIRQ (void);
void BSP_TimeoutStatus BSP_secTimeout(void);
void BSP_secTimeoutStart(uint32_t);
void BSP_msecTimeoutStart(uint32_t);
void BSP_TimeoutStatus BSP_msecTimeout(void);

//========================================
//<--Ԥ�������-->
#endif 
