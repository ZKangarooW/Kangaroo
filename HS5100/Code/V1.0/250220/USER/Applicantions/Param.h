#ifndef __PARAM_H__
#define	__PARAM_H__

#include "include.h"

/**********宏定义************/
/**********结构体************/
struct _Save_Param_
{	
	uint8_t Flash_Check_Start;//检查是否已经初始化的开始位
    
    int P_Param[10][3];

    uint8_t Unit;//温度单位
    uint8_t TempUp_Speed;//上升速度
    uint8_t SpeedUp_Speed;//上升速度
    int16_t Safe_Temp;//安全温度
    uint8_t DownTime_Type;//倒计时类型
    
	uint8_t Flash_Check_End;//检查是否已经初始化的结束位
};
extern struct _Save_Param_ Param;

/**********全局变量声明******/
extern uint8_t Save_Param_En;

/**********全局函数**********/
void Param_Read(void);//读取硬件中的参数，判断是否更新
void Param_Save_Overtime(float dT);//保存标志位置1，0.5s后保存

#endif
