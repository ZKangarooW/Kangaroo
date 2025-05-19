#ifndef __CALIBRATION_H__
#define __CALIBRATION_H__

#include "include.h"

/**********宏定义************/
/**********结构体************/
typedef struct
{
    uint8_t Switch;//开关
    int16_t Deviation;//校准的温度偏差
    float Val;
} _Calibration_;
extern _Calibration_ Calibration;//校准参数

/**********全局变量声明*******/
/**********全局函数**********/

void Calibration_Temp(float dT);

#endif
