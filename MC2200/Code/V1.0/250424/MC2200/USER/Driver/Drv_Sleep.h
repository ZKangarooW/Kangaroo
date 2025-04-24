#ifndef __DRV_SLEEP_H__
#define __DRV_SLEEP_H__

#include "include.h"

/**********宏定义************/
/**********全局变量**********/
/**********全局函数**********/
void Drv_Sleep_Init(void);//Sleep驱动初始化
void Check_Sleep(float dT);//检测时间，进入休眠模式
    
#endif
