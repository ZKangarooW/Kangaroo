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
    if (SetOK_Flag && sys.SetMode_Option == 0)
    {
        if (Speed.Ctrl != Speed.Set)
        {
            Speed.Ctrl = Speed.Set;
            Param.Speed = Speed.Set;
            if (Speed.ADDMode != 0)
                Speed.ADDMode = 0;
        }
        if (Time.Set != Time.Ctrl)
        {
            Time.Rel = Time.Set;
            Time.Ctrl = Time.Set;
            Param.Time = Time.Set;
        }
        Save_Param_En = 1; // 保存
        SetOK_Flag = 0;
    }
}
