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
		if(sys.SetMode_Option == 0)//在设定好后
		{    
			if(Heat_Temp.Ctrl_Temp != Heat_Temp.Set_Temp)//判断控制温度和设定温度是不是不一样
			{
				Heat_Temp.Ctrl_Temp = Heat_Temp.Set_Temp;//把设定温度赋值给控制温度
				Param.Heat_Temp = Heat_Temp.Set_Temp;//赋值到保存参数
				HeatTemp_Val.SumError = 0;//Pid的积分和清零
				Heat_Temp.ADDMode = 0;//温度处理清零
			}    
			if(Cool_Temp.Ctrl_Temp != Cool_Temp.Set_Temp)//判断控制温度和设定温度是不是不一样
			{
				Cool_Temp.Ctrl_Temp = Cool_Temp.Set_Temp;//把设定温度赋值给控制温度
				Param.Cool_Temp = Cool_Temp.Set_Temp;//赋值到保存参数
				CoolTemp_Val.SumError = 0;//Pid的积分和清零
				Cool_Temp.ADDMode = 0;//温度处理清零
			}  			
			if(Time.Ctrl_Time != Time.Set_Time)//实际时间不等于设定时间
			{
				Time.Ctrl_Time = Time.Set_Time;//把设定时间赋值给控制时间
				Param.CountDown_Time = Time.Set_Time;//赋值到保存参数
			}  
			Save_Param_En = 1;//保存
			SetOK_Flag = 0;
		}
    }
}
