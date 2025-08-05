#include "SetVal.h"

/**********全局变量声明******/
uint8_t SetOK_Flag;//检测是否波动旋钮和设置标志位

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
        SetOK_Flag = 1;//检测到设置标志后
    }
    if(SetOK_Flag == 1)
    {
        if(sys.SetMode_Option == 0)//在设定好后
        {    
			if(Temp.Ctrl_Temp != Temp.Set_Temp)//控制温度不等于设定温度的话
			{
				Temp.Ctrl_Temp = Temp.Set_Temp;//控制温度等于设定温度
				Param.P_Param[0] = Temp.Ctrl_Temp;//将控制温度保存到Flash
			}
			
			if(Speed.Ctrl_Speed != Speed.Set_Speed)//控制速度不等于设定速度的话
			{
				Speed.Ctrl_Speed = Speed.Set_Speed;//控制速度等于设定速度
				Param.P_Param[1] = Speed.Ctrl_Speed;//将控制速度保存到Flash
			}
			
            if(Time.Ctrl_Time != Time.Set_Time)//控制时间不等于设定时间的话
			{
				Time.Ctrl_Time = Time.Set_Time;//控制时间等于设定时间
				Param.P_Param[2] = Time.Ctrl_Time;//将控制时间保存到Flash
			}
			
            SetOK_Flag = 0;//设定好后清零标志位
			Save_Param_En = 1;//保存Flash标志位置一
        } 
    }
}
