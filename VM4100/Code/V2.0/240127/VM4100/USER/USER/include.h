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
#include <stdio.h>

/***************硬件头文件****************/
#include "SEGGER_RTT.h"
#include "RTT.h"
#include "Drv_Beep.h"
#include "Drv_Key.h"
#include "Drv_HT1623.h"
#include "Drv_Motor.h"
#include "Drv_Flash.h"

/***************应用头文件****************/
#include "Show.h"
#include "Speed.h"
#include "PID.h"
#include "SetVal.h"
#include "Param.h"

/***************底层头文件****************/
#include "Ctrl_Scheduler.h"
#include "Ctrl_Motor.h"
#include "Ctrl_DownTime.h"

#endif
