#include "SetVal.h"

/**********全局变量声明******/
uint8_t SetOK_Flag,CtrlMode;//检测是否按下按键

/*
*****************************************************************
 * 函数原型： void Check_Set(void)
 * 功    能： 检测设置
*****************************************************************
*/
void Check_Set(void)
{
    if(Key_Status != 0)
    {
        SetOK_Flag = 1;//检测到波动旋钮，等待退出设置模式
    }
    if(SetOK_Flag == 1)
    {
		if(sys.SetMode_Option == 0)//在设定好后
		{    
			if(PMode_Status == 1)
			{
				Param.P_Param[PMode_Option][1] = Set_Time;
				Param.P_Param[PMode_Option][0] = Set_Temp;
				Param_Save();
			}
			if(Ctrl_Temp != Set_Temp)//判断控制速度和设定速度是不是不一样
			{
				Ctrl_Temp = Set_Temp;//把设定速度赋值给控制速度
				if(Temp_ADDMode != 0)//假如工位只有在启动并且设置了速度的情况下不等于0，不在未处理模式下
					Temp_ADDMode = 0;//进入未处理，判断加速还是减速
				Param.P_Param[PMode_Option][0] = Set_Temp;
				Param_Save();
			}          
			if(Ctrl_Time != Set_Time)//实际时间不等于设定时间
			{
				Ctrl_Time = Set_Time;//把设定时间赋值给控制时间
				Param.P_Param[PMode_Option][1] = Set_Time;
				Time = Set_Time;
				Param_Save();
			}  
			if(Set_Time > 0)
				Time_State = 0;
			else
				Time_State = 1;
			SetOK_Flag = 0;
		}
    }
}

void Check_CtrlTemp_Mode(void)
{
	if(CtrlMode == 1)
	{
		if(Ctrl_Temp > Rel_Temp)
		{
			sys.CtrlTemp_Mode = 1;
		}
		else
		{
			sys.CtrlTemp_Mode = 2;
		}
		CtrlMode = 0;
	}
}
