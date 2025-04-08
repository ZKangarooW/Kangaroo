#ifndef __PARAM_H__
#define	__PARAM_H__

#include "include.h"

/**********宏定义************/
/**********结构体************/
struct _Save_Param_
{	
	uint8_t Flash_Check_Start;//检测是否已经初始化的开始位

    int P_Param[10][3];//10组数据，每组包括温度、速度、时间的参数

    uint8_t Flash_Check_End;//检测是否已经初始化的结束位
};
extern struct _Save_Param_ Param;

/**********全局变量声明*******/
extern uint8_t Save_Param_En;//保存标志位

/**********全局函数**********/

void Param_Read(void);
void Param_Save_Overtime(float dT);

#endif
