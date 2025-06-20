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
        if(sys.SetMode_Option == 0)//在设定好后
        {     
            if(Ctrl_Speed != Set_Speed)//判断控制速度和设定速度是不是不一样
            {
                Ctrl_Speed = Set_Speed;//把设定速度赋值给控制速度
                if(Speed_ADDMode != 0)//假如工位只有在启动并且设置了速度的情况下不等于0，不在未处理模式下
					Speed_ADDMode = 0;//进入未处理，判断加速还是减速 
				Param.Speed = Set_Speed;//转速
            }    
			if(Ctrl_Time != Set_Time)//在没有启动的情况下可以设置时间
			{				
				if(Ctrl_Time != Set_Time)//实际时间不等于设定时间
				{
					Ctrl_Time = Set_Time;//把设定时间赋值给控制时间
                    Rel_Time = Ctrl_Time;
					Param.Time = Set_Time;//时间
				}
			}
            if(sys.Run_Status)
            {
                if(Speed_ADDMode != 0)//假如工位只有在启动并且设置了速度的情况下不等于0，不在未处理模式下
					Speed_ADDMode = 0;//进入未处理，判断加速还是减速 
                Display_Speed = Rel_Speed;
            }
            SetOK_Flag = 0;//表示已经设置好了，将设置标志位清零
			Save_Param_En = 1;//保存
        } 
    }
}
