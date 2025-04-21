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
		if(Select_Option < 2)//在设定好后
		{    
			if(Set_Mode_Enable == 1)
			{
				Param.P_Param[run_mode][1] = set_time;
				Param.P_Param[run_mode][0] = set_temp;
				Save_Param_En = 1;
			}
			if(ctrl_temp != set_temp)//判断控制速度和设定速度是不是不一样
			{
				ctrl_temp = set_temp;//把设定速度赋值给控制速度
				if(ADD_Mode != 0)//假如工位只有在启动并且设置了速度的情况下不等于0，不在未处理模式下
				ADD_Mode = 0;//进入未处理，判断加速还是减速
				Param.P_Param[run_mode][0] = set_temp;
				Save_Param_En = 1;
			}          
			if(rel_time != set_time)//实际时间不等于设定时间
			{
				rel_time = set_time;//把设定时间赋值给控制时间
				Param.P_Param[run_mode][1] = set_time;
				Save_Param_En = 1;
			} 
            if(Param.Mode_Val == 0)    
            {                
                if(set_time > 0)
                {
                    SetTime_State = 0;//设定时间退出显示“----”
                    time_Last = 0;
                }
                else
                {
                    SetTime_State = 1;//设定时间显示“----”
                    time_Last = 1;
                }
            }
			SetOK_Flag = 0;
		}
		
    }
}
