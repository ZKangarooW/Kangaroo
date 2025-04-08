#ifndef __INCLUDE_H__
#define __INCLUDE_H__

/***************系统头文件***************/
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

/***************FreeRTOS头文件***********/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/***************硬件头文件***************/
#include "Drv_Beep.h"
#include "Drv_HT162x.h"
#include "Drv_EC11A.h"
#include "Drv_PT1000.h"
#include "Drv_Motor.h"
#include "Drv_Flash.h"

/***************应用头文件***************/
#include "Show.h"
#include "SysTick.h"
#include "Speed.h"
#include "Param.h"
#include "SetVal.h"

/***************底层头文件***************/
#include "Ctrl_Scheduler.h"
#include "Ctrl_Motor.h"


#include "SEGGER_SYSVIEW.h"
#include "SEGGER_RTT.h"
#include "RTT.h"


#endif
