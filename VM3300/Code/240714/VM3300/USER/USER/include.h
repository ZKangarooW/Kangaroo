#ifndef __INCLUDE_H__
#define __INCLUDE_H__

/***************系统头文件***************/
#include "System_Init.h"
#include "Structs.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "gpio.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include <stdio.h>

/***************硬件头文件***************/
#include "Drv_Beep.h"
#include "Drv_WS2812.h"
#include "Drv_Motor.h"
#include "Drv_Infrared.h"
#include "Drv_Flash.h"
#include "Drv_KEY.h"
#include "Drv_TM1650.h"
#include "Drv_Uart.h"

/***************应用头文件***************/
#include "SysTick.h"
#include "Speed.h"
#include "Interrupt.h"
#include "Param.h"
#include "PID.h"
#include "SetVal.h"
#include "Show.h"

/***************底层头文件***************/
#include "Ctrl_Scheduler.h"
#include "Ctrl_Motor.h"
#include "Ctrl_Protocol.h"

#endif
