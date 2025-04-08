#ifndef __INCLUDE_H__
#define __INCLUDE_H__

/***************系统头文件***************/
#include "System_Init.h"
#include "Structs.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include <stdio.h>
#include "SC_Init.h"
#include "SC_it.h"
#include "..\Drivers\SCDriver_list.h"
#include "HeadFiles\SysFunVarDefine.h"

/***************硬件头文件***************/
#include "Drv_Beep.h"
#include "Drv_Touch.h"
#include "Drv_WS2812.h"
#include "Drv_Motor.h"
#include "Drv_Infrared.h"

/***************应用头文件***************/
#include "Show.h"
#include "Speed.h"
#include "PID.h"
#include "SysTick.h"

/***************底层头文件***************/
#include "Ctrl_Scheduler.h"
#include "Ctrl_Motor.h"

#endif
