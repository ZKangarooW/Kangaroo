#ifndef __PID_H__
#define __PID_H__

#include "include.h"

/**********宏定义************/
#define LIMIT(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))
#define safe_div(numerator, denominator, safe_value) ((denominator == 0) ? (safe_value) : ((numerator) / (denominator)))

/**********结构体************/
typedef struct
{
    float Kp; // 比例系数
    float Ki; // 积分系数
    float Kd; // 微分系数
} _PID_Arg_;
extern _PID_Arg_ Speed_Arg;

typedef struct
{
    float Proportion;   // 比例
    float Integral;     // 积分
    float Differential; // 微分

    float Error;          // 误差
    float Error_Last;     // 上一次误差
    float Error_Previous; // 上上次误差

    float Fb_Differential; // 微分先行
    float Proportion_Last; // 上一次比例
    float Freedback_Old;   // 上一个反馈值

    float Out; // 输出
} _PID_Val_;
extern _PID_Val_ Speed_Val;

/**********全局变量声明*******/
/**********全局函数**********/

void AltPID_Calculation(float dT, float Expect, float Freedback, _PID_Arg_ *PID_Arg, _PID_Val_ *PID_Val, float Error_Lim, float Integral_Lim);
void IncPID_Calculation(float dT, float Expect, float Freedback, _PID_Arg_ *PID_Arg, _PID_Val_ *PID_Val, float Integral_Lim); 

#endif
