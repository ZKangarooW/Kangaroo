#include "SetVal.h"

/**********全局变量声明******/
uint8_t SpeedSet_Flag,TimeSet_Flag;//检测速度和时间设置标志位

/*
*****************************************************************
 * 函数原型： void Check_Set(void)
 * 功    能： 检测设置
*****************************************************************
*/
void Check_Set(void)
{
    if(Twinkle_Time1 == 0 && SpeedSet_Flag)
    {
		Ctrl_Speed = Set_Speed;
		Speed = Set_Speed;
		if(Speed_ADDMode != 0)//假如工位只有在启动并且设置了速度的情况下不等于0，不在未处理模式下
            Speed_ADDMode = 0;//进入未处理，判断加速还是减速  
		Param.Speed = Set_Speed;//转速
		Save_Param_En = 1;
        SpeedSet_Flag = 0;
    }
	if(Twinkle_Time2 == 0 && TimeSet_Flag)
    {
		Ctrl_Time = Set_Time;
		Time = Set_Time;
		Param.Time = Set_Time;//时间
		Save_Param_En = 1;
        TimeSet_Flag = 0;
    }
}
