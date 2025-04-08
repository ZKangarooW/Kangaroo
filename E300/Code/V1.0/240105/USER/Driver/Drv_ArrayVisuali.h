#ifndef __DRV_ARRAYVISUALI_H__
#define __DRV_ARRAYVISUALI_H__

#include "include.h"

/**********宏定义************/
#define Array_Size 128

/**********结构体************/
typedef struct
{
	int16_t A[Array_Size];
    int16_t Index;
}_Array_;
extern _Array_ Temp_Array;

/**********全局变量声明******/
/**********全局函数**********/
void Array_Check(float dT);//数组检测

#endif
