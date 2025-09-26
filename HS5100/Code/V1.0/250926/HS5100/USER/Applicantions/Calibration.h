#ifndef __CALIBRATION_H__
#define __CALIBRATION_H__

#include "include.h"

/**********宏定义************/
/**********结构体************/
typedef struct
{
    uint8_t Switch;//开关
	float offset_temp; // 温度偏移量
    float gain; // 如果需要两点校准，可以加入增益系数
} _Calibration_;
extern _Calibration_ Calibration;//校准参数

/**********全局变量声明*******/
/**********全局函数**********/

void Calibration_Init(void);
void Calibration_Temp(float dT);
    
#endif
