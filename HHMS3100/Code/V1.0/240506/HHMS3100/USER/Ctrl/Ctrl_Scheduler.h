#ifndef __CTRL_SCHEDULER_H__
#define __CTRL_SCHEDULER_H__

#include "include.h"

/**********宏定义************/
/**********结构体************/
extern TaskHandle_t Buzzer_Task_Handler;//函数句柄

/**********全局变量声明******/
/**********全局函数**********/
void Start_Task(void *p);

#endif
