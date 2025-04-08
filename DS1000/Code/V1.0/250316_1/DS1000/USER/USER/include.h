#ifndef _INCLUDE_H_
#define _INCLUDE_H_

/***************系统头文件****************/
#include "System_Init.h"
#include "Structs.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include <stdio.h>
#include <intrins.h>

/***************硬件头文件****************/
#include "Drv_Beep.h"
#include "Drv_LedDisplay.h"
#include "Drv_HEAT.h"
#include "uart0.h"
#include "Drv_KEY.h"

/***************应用头文件****************/
#include "SysTick.h"
#include "Show.h"

/***************底层头文件****************/
#include "Ctrl_Scheduler.h"
#include "Ctrl_DownTime.h"


#include "CheckTouchKey_80F73xx.h"
#include "CheckTouchKey_Set.h"
#include "REL_Protocol.h"

#endif
