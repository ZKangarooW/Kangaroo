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
#if (Integration_TYPE ==0)//四六联
	#include "Drv_HT1623.h"
#elif(Integration_TYPE == 1)//设置成九联时
	#include "Drv_HT1623_9.h"
#endif

#include "Drv_EC11A.h"
#include "Drv_Beep.h"
#include "Drv_NTC.h"
#include "Drv_Flash.h"

/***************应用头文件****************/
#if (Integration_TYPE==0)//四六联
	#include "Show.h"
#elif(Integration_TYPE == 1)//设置成九联时
	#include "Show_9.h"
#endif

#include "SetVal.h"
#include "Speed.h"
#include "PID.h"
#include "Param.h"

/***************底层头文件****************/
#include "Ctrl_Scheduler.h"
#include "Ctrl_DownTime.h"
#include "Ctrl_Motor.h"
#include "Ctrl_ControlTemp.h"

#endif
