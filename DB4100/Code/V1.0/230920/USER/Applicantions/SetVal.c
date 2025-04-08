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
        if(Temp.Ctrl != Temp.Set)
        {
            Temp.Ctrl = Temp.Set;
            Param.P_Param[PMode.Option][0] = Temp.Set;
        }
        if(Time.Rel != Time.Set)
        {
            Time.Rel = Time.Set;
            Param.P_Param[PMode.Option][1] = Time.Set;
        }
        Save_Param_En = 1;//保存
        SetOK_Flag = 0;
    }
}
