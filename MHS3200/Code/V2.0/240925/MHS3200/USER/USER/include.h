#ifndef _INCLUDE_H_
#define _INCLUDE_H_

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

/***************Ӳ��ͷ�ļ�****************/
#if (Integration_TYPE ==0)//������
	#include "Drv_HT1623.h"
#elif(Integration_TYPE == 1)//���óɾ���ʱ
	#include "Drv_HT1623_9.h"
#endif

#include "Drv_EC11A.h"
#include "Drv_Beep.h"
#include "Drv_NTC.h"
#include "Drv_Flash.h"

/***************Ӧ��ͷ�ļ�****************/
#if (Integration_TYPE==0)//������
	#include "Show.h"
#elif(Integration_TYPE == 1)//���óɾ���ʱ
	#include "Show_9.h"
#endif

#include "SetVal.h"
#include "Speed.h"
#include "PID.h"
#include "Param.h"

/***************�ײ�ͷ�ļ�****************/
#include "Ctrl_Scheduler.h"
#include "Ctrl_DownTime.h"
#include "Ctrl_Motor.h"
#include "Ctrl_ControlTemp.h"

#endif
