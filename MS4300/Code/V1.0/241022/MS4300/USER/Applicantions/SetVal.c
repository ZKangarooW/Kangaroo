#include "SetVal.h"

/**********全局变量声明******/
uint8_t SpeedSet_Flag,TimeSet_Flag;//速度设置，时间设置

/*
*****************************************************************
 * 函数原型：void Check_Set(float dT)
 * 功    能：检测设置
*****************************************************************
*/
void Check_Set(float dT)
{
	if(SpeedSet_Flag)//速度设置
    {
        if(Speed.Ctrl != Speed.Set)//控制速度和设定速度不同时
		{
			Speed.Ctrl = Speed.Set;
			Param.P_Param[PMode.Option][0] = Speed.Set;
			if(Speed.ADDMode != 0)//速度显示模式不等于零时
				Speed.ADDMode = 0;//速度显示模式清零
			Save_Param_En = 1;//保存
		}
		SpeedSet_Flag = 0;//设置标志位清零
    }
	
	if(TimeSet_Flag)//时间设置
    {
        if(Time.Rel != Time.Set)//实际时间和设定时间不同时
		{
			Time.Rel = Time.Set;
			Param.P_Param[PMode.Option][1] = Time.Set;
			Save_Param_En = 1;//保存
		}
		TimeSet_Flag = 0;//设置标志位清零
    }
}
