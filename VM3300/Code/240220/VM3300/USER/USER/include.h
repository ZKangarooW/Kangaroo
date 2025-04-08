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
#include "Drv_Remote.h"

/***************应用头文件***************/
#include "SysTick.h"
#include "Speed.h"
#include "Interrupt.h"

/***************底层头文件***************/
#include "Ctrl_Scheduler.h"

#endif
