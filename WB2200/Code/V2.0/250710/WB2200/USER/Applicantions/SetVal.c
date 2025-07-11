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
    if(Key_Status)
    {
        SetOK_Flag = 1;//检测到设置，等待退出设置模式
    }
    if(SetOK_Flag)
    {
		if(!sys.SetMode_Option)//在设定好后
		{    
			if(Temp.Ctrl != Temp.Set)
			{
				Temp.Ctrl = Temp.Set;
				Param.Temp = Temp.Set;
                if(Temp.ADDMode != 0)//速度显示模式不等于零时
                {
                    Temp.ADDMode = 0;//速度显示模式清零
                }
			}
			if(Time.Ctrl != Time.Set)
			{
                Time.Ctrl = Time.Set;
				Time.Rel = Time.Set;
				Param.Time = Time.Set;
			}
			Save_Param_En = 1;//保存
			SetOK_Flag = 0;
		}
    }
}
