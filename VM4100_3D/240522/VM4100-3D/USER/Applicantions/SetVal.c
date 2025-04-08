#include "SetVal.h"

/**********全局变量声明******/
uint8_t SetOK_Flag;//检测是否波动旋钮和设置标志位

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
        if(SetMode_Option == 0)//在设定好后
        {     
            if(Ctrl_Speed != Set_Speed)//判断控制速度和设定速度是不是不一样
            {
                Ctrl_Speed = Set_Speed;//把设定速度赋值给控制速度
                if(Speed_ADDMode != 0)//假如工位只有在启动并且设置了速度的情况下不等于0，不在未处理模式下
					Speed_ADDMode = 0;//进入未处理，判断加速还是减速 
				Param.Speed = Set_Speed;//转速
				
            }          
            if(Rel_Time != Set_Time)//实际时间不等于设定时间
            {
                Rel_Time = Set_Time;//把设定时间赋值给控制时间
				if(Set_Time == 0)
					Time_State = 0;
				else
					Time_State = 1;
				Param.Time = Set_Time;//时间
            }  
            SetOK_Flag = 0;
			Save_Param_En = 1;
        } 
    }
}
