#ifndef __DRV_PT1000_H__
#define __DRV_PT1000_H__

#include "include.h"

/**********宏定义************/
#define N           100//互动滤波采集100次
#define ALPHA       0.1f//平滑因子，调整响应速度

#define Vref		1.2f//内部参考电压
#define OP_Value	6.8f//放大系数
#define R_3K        3.0f//分压电阻3k
#define R_910R      0.91f//分压电阻910Ω

#define AD_LEN      12//DMA获取长度

/**********结构体************/
/**********全局变量声明******/
extern float PT_VALUE_1_TEMP[Motor_Num];//外部探头阻值
extern float PT_VALUE_2_TEMP[Motor_Num];//外部探头阻值

/**********全局函数**********/

void ADCDMA_Init(void);//ADC和DMA的初始化
void PT1000_Task(void *p);

#endif
