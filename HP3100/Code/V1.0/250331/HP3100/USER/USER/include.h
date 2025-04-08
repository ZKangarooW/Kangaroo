#ifndef _INCLUDE_H_
#define _INCLUDE_H_

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

/***************硬件头文件****************/
#include "Drv_HT162x.h"
#include "Drv_Beep.h"
#include "Drv_EC11A.h"
#include "Drv_PT1000.h"
#include "Drv_Flash.h"
#include "Drv_HEAT.h"

/***************应用头文件****************/
#include "SysTick.h"
#include "Show.h"
#include "PID.h"
#include "Param.h"
#include "SetVal.h"

/***************底层头文件****************/
#include "Ctrl_Scheduler.h"
#include "Ctrl_ControlTemp.h"
#include "Ctrl_DownTime.h"

#endif
