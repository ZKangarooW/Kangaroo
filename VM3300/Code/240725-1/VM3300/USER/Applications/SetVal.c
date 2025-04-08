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
    if (SetOK_Flag && Key_Status <= 0)
    {
        if (Speed.Ctrl != Speed.Set)
        {
            Speed.Ctrl = Speed.Set;
            Param.Speed = Speed.Set;
            if (Speed.ADDMode != 0)
                Speed.ADDMode = 0;
        }
        Save_Param_En = 1; // 保存
        SetOK_Flag = 0;
    }
}
