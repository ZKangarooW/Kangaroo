#ifndef __DRV_PT1000_H__
#define __DRV_PT1000_H__

#include "include.h"

/**********宏定义************/
#define AD_LEN 8//DMA获取长度

/**********结构体************/
/**********全局变量声明******/
extern float PT_VALUE_1_TEMP[4];//外部探头阻值

/**********全局函数**********/
void ADCDMA_Init(void);
void PT1000_Task(void *p);

#endif
