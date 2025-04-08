#ifndef __INCLUDE_H__
#define __INCLUDE_H__

/***************系统头文件****************/
#include "System_Init.h"
#include "Structs.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "gpio.h"
#include <stdio.h>
#include "adc.h"
#include "dma.h"
#include "tim.h"

/***************硬件头文件****************/
#include "Drv_GN1640.h"
#include "Drv_Beep.h"
#include "Drv_Key.h"
#include "Drv_Flash.h"
#include "Drv_NTC.h"

/***************应用头文件****************/
#include "SysTick.h"
#include "Show.h"
#include "Param.h"
#include "SetVal.h"
#include "PID.h"

/***************底层头文件****************/
#include "Ctrl_Scheduler.h"
#include "Ctrl_DownTime.h"
#include "Ctrl_ControlTemp.h"

#endif
