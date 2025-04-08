#ifndef __SETVAL_H__
#define __SETVAL_H__

#include "include.h"

/**********全局变量声明******/
extern uint8_t SetOK_Flag;//检测是否波动旋钮和设置标志位

/**********全局函数**********/
void Set_Val(uint8_t flag,uint8_t Work_Option,uint8_t SetMode_Option);//设置数值
void Check_Set(void);//检测设置
void SetALL_int(int Val,_Work_Num_ *Work_Num);//
void SetALL_int8(uint8_t Val,_Work_Num_Flag *Work_Num);//将结构图中的参数赋值-uint8_t型
void SetALL_int32(uint32_t Val,_Work_Num_long *Work_Num);//将结构图中的参数赋值-uint32_t型
void SetALL_TimeOver(_Work_Num_long *Work_Num1,_Work_Num_long *Work_Num);//将两个结构体变量的参数对应赋值，用于结束时间复原
void SetALL_SpeedOver(_Work_Num_ *Work_Num1,_Work_Num_ *Work_Num);////将两个结构体变量的参数对应赋值，用于结束速度复原
void Speed_ALL(uint8_t work,_Work_Num_ *Work_Num,_Work_Num_ *Work_Num1);//同步功能，将所有工位的速度同步
void Time_ALL(uint8_t work,_Work_Num_long *Work_Num,_Work_Num_long *Work_Num1);//同步功能，将所有工位的时间同步
void Flag_ALL(uint8_t work,_Work_Num_Flag *Work_Num,_Work_Num_Flag *Work_Num1);//同步功能，将所有工位的flag同步
void Set_Speeds(_Work_Num_ *Work_Num,_Work_Num_ *Work_Num1,_Work_Num_ *Work_Num2,_Work_Num_ *Work_Num3,_Work_Num_ *Work_Num4,_Work_Num_ *Work_Num5);//判断设置速度数值是否改变
void Set_Times(_Work_Num_long *Work_Num,_Work_Num_long *Work_Num1,_Work_Num_long *Work_Num2,_Work_Num_long *Work_Num3,_Work_Num_long *Work_Num4,_Work_Num_long *Work_Num5);//判断设置时间数值是否改变
void Check_Time_State(_Work_Num_Flag *Work_Num,_Work_Num_long *Work_Num1);//判断时间状态

#endif
