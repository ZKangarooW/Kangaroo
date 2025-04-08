#ifndef __INCLUDE_H__
#define __INCLUDE_H__

/***************系统头文件***************/
#include "System_Init.h"
#include "Structs.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "gpio.h"
#include "tim.h"
#include <stdio.h>

/***************硬件头文件***************/
#include "Drv_Beep.h"
#include "Drv_HT162x.h"
#include "Drv_Key.h"
#include "Drv_Flash.h"
#include "Drv_Motor.h"

/***************应用头文件***************/
#include "Show.h"
#include "Speed.h"
#include "Param.h"
#include "SetVal.h"
#include "PID.h"

/***************底层头文件***************/
#include "Ctrl_Scheduler.h"
#include "Ctrl_Motor.h"
#include "Ctrl_DownTime.h"

#endif
