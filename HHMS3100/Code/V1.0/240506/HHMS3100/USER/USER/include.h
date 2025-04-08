#ifndef __INCLUDE_H__
#define __INCLUDE_H__

/***************ϵͳͷ�ļ�***************/
#include "System_Init.h"
#include "Structs.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "gpio.h"

/***************FreeRTOSͷ�ļ�***********/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/***************Ӳ��ͷ�ļ�***************/
#include "Drv_Beep.h"
#include "Drv_HT162x.h"
#include "Drv_EC11A.h"

/***************Ӧ��ͷ�ļ�***************/
#include "Show.h"
#include "SysTick.h"

/***************�ײ�ͷ�ļ�***************/
#include "Ctrl_Scheduler.h"


#include "RTT.h"
#include "SEGGER_RTT.h"

#endif
