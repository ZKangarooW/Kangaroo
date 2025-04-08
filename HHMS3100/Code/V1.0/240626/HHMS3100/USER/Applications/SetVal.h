#ifndef __SETVAL_H__
#define __SETVAL_H__

#include "include.h"

/**********全局变量声明******/
extern uint8_t SetOK_Flag;//检测是否波动旋钮和设置标志位

/**********全局函数**********/

void Setting_Task(void *p);

#endif
