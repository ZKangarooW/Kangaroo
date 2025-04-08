#include "SetVal.h"

/**********全局变量声明******/
uint8_t SetOK_Flag;//检测是否按下按键
 
/*
*****************************************************************
 * 函数原型：void Check_Set(float dT)
 * 功    能：检测设置
*****************************************************************
*/
void Check_Set(float dT)
{
    if(Key_Status != 0)
    {
        SetOK_Flag = 1;//检测到波动旋钮，等待退出设置模式
    }
    if(SetOK_Flag == 1)
    {
		if(sys.SetMode_Option == 0 || sys.SetMode_Option == 1)//在设定好后
		{    
			if(Ctrl_Speed != Set_Speed)//判断控制速度和设定速度是不是不一样
			{
				Ctrl_Speed = Set_Speed;//把设定速度赋值给控制速度
				if(Speed_Mode == 0)
					Param.P_Param[PMode_Option][1] = Set_Speed;//转速
				else
					Param.P_Param[PMode_Option][3] = Set_Speed;//离心率
			}          
			if(Ctrl_Time != Set_Time)//实际时间不等于设定时间
			{
				Ctrl_Time = Set_Time;//把设定时间赋值给控制时间
				Param.P_Param[PMode_Option][0] = Set_Time;//时间
			}  
			Param.P_Param[PMode_Option][2] = Safe_Set_Temp;//安全温度
//			Save_Param_En = 1;//保存
			SetOK_Flag = 0;
		}
    }
}
