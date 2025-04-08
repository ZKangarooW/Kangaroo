#ifndef __INCLUDE_H__
#define __INCLUDE_H__

/***************系统头文件****************/
#include "System_Init.h"
#include "Structs.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "gpio.h"
#include "tim.h"
#include "adc.h"
#include <stdio.h>
#include <stdbool.h>

/***************硬件头文件****************/
#include "SEGGER_RTT.h"
#include "RTT.h"
#include "Drv_Beep.h"
#include "Drv_TM1640.h"
#include "Drv_HEAT.h"
#include "Drv_Flash.h"
#include "Drv_NTC.h"
#include "Drv_Key.h"

/***************应用头文件****************/
#include "SysTick.h"
#include "Param.h"
#include "Show.h"
#include "SetVal.h"
#include "PID.h"

/***************底层头文件****************/
#include "Ctrl_Scheduler.h"
#include "Ctrl_ControlTemp.h"
//#include "Ctrl_DownTime.h"

#endif
