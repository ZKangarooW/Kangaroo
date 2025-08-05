#ifndef __TIMEDOWN_H__
#define __TIMEDOWN_H__

#include "main.h"

/**********全局变量**********/
extern uint8_t time_disable;//关闭计时
extern uint8_t time_Last;//一直计时

/**********全局函数**********/
void Cheak_TimeDown(uint16_t dT);//时间倒计时检测

#endif
