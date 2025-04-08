#ifndef __DRV_NTC_H__
#define __DRV_NTC_H__

#include "include.h"

/**********宏定义************/
#define AD_LEN 1//DMA获取长度
#define ALPHA 0.1f  // 平滑因子，调整响应速度
#define R_REF 100000.0f  // 参考电阻 5.1kΩ
#define V_IN 3.3f  // 电源电压

/**********结构体************/
/**********全局变量声明******/

/**********全局函数**********/
void Read_Temp(float dT);//读取温度-10ms
void Temp_Init(void);//开机显示温度

#endif
