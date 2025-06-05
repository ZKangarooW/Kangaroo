#ifndef __DRV_KEY_H__
#define __DRV_KEY_H__

#include "include.h"

/**********宏定义************/
#define KEY1 P21

/**********全局变量声明******/

/**********全局函数**********/
void Drv_Key_Init(void);//Key驱动初始化
void Key_Scan(float dT);//矩阵按键扫描

#endif

