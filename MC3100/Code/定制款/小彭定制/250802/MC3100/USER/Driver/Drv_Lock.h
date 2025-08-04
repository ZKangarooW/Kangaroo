#ifndef __DRV_LOCK_H__
#define	__DRV_LOCK_H__

#include "include.h"

/**********宏定义************/
/**********结构体************/
/**********全局变量声明******/
extern uint8_t Lock_Status;//盖子的状态

/**********局部变量声明******/
/**********全局函数**********/
void Ctrl_Lock(float dT);//关开盖检测

#endif
