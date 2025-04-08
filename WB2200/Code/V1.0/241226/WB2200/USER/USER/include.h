#ifndef __INCLUDE_H__
#define __INCLUDE_H__

/***************ϵͳͷ�ļ�****************/
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

/***************Ӳ��ͷ�ļ�****************/
#include "SEGGER_RTT.h"
#include "RTT.h"
#include "Drv_Beep.h"
#include "Drv_TM1640.h"
#include "Drv_HEAT.h"
#include "Drv_Flash.h"
#include "Drv_NTC.h"
#include "Drv_Key.h"

/***************Ӧ��ͷ�ļ�****************/
#include "SysTick.h"
#include "Param.h"
#include "Show.h"
#include "SetVal.h"
#include "PID.h"

/***************�ײ�ͷ�ļ�****************/
#include "Ctrl_Scheduler.h"
#include "Ctrl_ControlTemp.h"
//#include "Ctrl_DownTime.h"

#endif
