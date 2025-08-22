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
			if(Speed.Ctrl != Speed.Set)//判断控制速度和设定速度是不是不一样
			{
				Speed.Ctrl = Speed.Set;//把设定速度赋值给控制速度
				if(Speed.Unit == 0)
				{
					Param.P_Param[1] = Speed.Set;//转速
				}
				else
				{
					Param.P_Param[2] = Speed.Set;//离心率
				}
			}          
			if(Time.Ctrl != Time.Set)//实际时间不等于设定时间
			{
				Time.Ctrl = Time.Set;//把设定时间赋值给控制时间
				Param.P_Param[0] = Time.Set;//时间
			}  
			Save_Param_En = 1;//保存
			SetOK_Flag = 0;
		}
    }
}
