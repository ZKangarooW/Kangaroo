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
#include "dma.h"
#include <stdio.h>

/***************硬件头文件****************/
#include "Drv_Beep.h"
#include "Drv_HT162x.h"
#include "Drv_KEY.h"
#include "Drv_NTC.h"
#include "Drv_Flash.h"

/***************应用头文件****************/
#include "Show.h"

/***************底层头文件****************/
#include "Ctrl_Scheduler.h"

#endif
