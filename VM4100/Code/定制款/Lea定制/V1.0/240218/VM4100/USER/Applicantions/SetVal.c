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
    if(Key_Status != 0)//按下加减按键
    {
        SetOK_Flag = 1;//检测到波动旋钮，等待退出设置模式
    }
    if(SetOK_Flag == 1)//检测到按下加减按键后
    {
		if(sys.SetMode_Option)
		{
			if(Param.Mode != Speed_Mode)
			{
				Param.Mode = Speed_Mode;
				Set_Time = Param.Time[Speed_Mode][sys.Run_Step];//时间
				Set_Speed = Param.Speed[Speed_Mode][sys.Run_Step];//转速
			}
			Param.Speed[Speed_Mode][sys.Run_Step] = Set_Speed;
			Param.Time[Speed_Mode][sys.Run_Step] = Set_Time;
			if(sys.SetMode_Option > 4)
				sys.SetMode_Option = 0;
		}
		else
		{
			if(Param.Mode != Speed_Mode)
			{
				Param.Mode = Speed_Mode;
			}
		}
		if(sys.SetMode_Option<3)
		{
			sys.Run_Step = 0;
		}
		else
		{
			sys.Run_Step = 1;
		}	
		Set_Time = Param.Time[Speed_Mode][sys.Run_Step];//时间
		Set_Speed = Param.Speed[Speed_Mode][sys.Run_Step];//转速
        SetOK_Flag = 0;//表示已经设置好了，将设置标志位清零
		Save_Param_En = 1;//保存
    }
}
