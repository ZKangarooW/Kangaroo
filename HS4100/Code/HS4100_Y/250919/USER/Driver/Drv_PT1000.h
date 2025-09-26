#ifndef __DRV_PT1000_H__
#define __DRV_PT1000_H__

#include "include.h"

/**********宏定义************/
#define AD_LEN      3//DMA获取长度

#define VREFINT_CAL (*(uint16_t *)(0x1FFFF7BA))//工厂校准值
#define VREFINT_CAL_VOLTAGE 1.2f //内部电压

#define FILTER_WINDOW_SIZE 100  // 滤波窗口大小，可根据需要调整
#define MAX_FILTER_CHANNELS 8  // 最大支持通道数

#define OP_Value	6.8//放大系数
#define Vref		1.2//参考电压
#define R_3K        3.0f//分压电阻3k
#define R_910R      0.91f//分压电阻910Ω

typedef struct {
    uint16_t buffer[FILTER_WINDOW_SIZE];
    uint16_t write_index;
    uint8_t buffer_full;
    uint32_t running_sum;
} ADC_Filter_t;

/**********全局变量**********/
extern float PT_VALUE_1_TEMP;//外部探头阻值
extern float PT_VALUE_2_TEMP;//台面探头阻值

/**********全局函数**********/
void ADCDMA_Init(void);//ADC和DMA的初始化
void Read_Temp(float dT);//读取温度-10ms
float CelsiusToFahrenheit(uint8_t type,int16_t celsius);//摄氏度转华氏度

#endif
