#include "SetVal.h"

/**********全局变量声明******/
uint8_t SetOK_Flag; // 检测是否按下按键

/**
 * @brief 检测设置
 *
 * @param dT 任务周期
 */
void Check_Set(float dT)
{
    if (Key_Status)
    {
        SetOK_Flag = 1; // 检测到设置，等待退出设置模式
    }
    if (SetOK_Flag)
    {

        if (Temp.Ctrl != Temp.Set)
        {
            Temp.Ctrl = Temp.Set;
            Param.P_Param[PMode.Option][0] = Temp.Set;
        }
        if (Speed.Ctrl != Speed.Set)
        {
            Speed.Ctrl = Speed.Set;
            Param.P_Param[PMode.Option][1] = Speed.Set;
            if (Speed.ADDMode != 0)
                Speed.ADDMode = 0;
        }
        if (Time.Rel != Time.Set)
        {
            Time.Rel = Time.Set;
            Param.P_Param[PMode.Option][2] = Time.Set;
        }
        Save_Param_En = 1; // 保存
        SetOK_Flag = 0;
    }
}
