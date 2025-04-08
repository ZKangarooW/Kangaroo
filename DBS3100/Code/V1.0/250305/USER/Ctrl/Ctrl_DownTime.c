#include "Ctrl_DownTime.h"

/**
 * @brief 时间倒计时检测
 *
 * @param dT 任务周期
 */
void Cheak_TimeDown(float dT)
{
    static float T;

    if (sys.Run_Status == 1) // 启动系统
    {
        if (Time.Rel > 0 && Temp.ADDMode == 4)
        {
            T += dT;
        }
        else if(Temp.Set == Temp.MIN && Speed.ADDMode == 3) // 等于-0.1度,并且速度到达了
         {
            T += dT;
        }
         
        if (T >= 1.0f) // 1S
        {
            if (Time.Rel)
                Time.Rel--; // 控制时间--

            if (Time.Rel == 0)
            {
                if (PMode.Status == 2) // 梯度模式下
                {
                    PMode.Option++;
                    if (PMode.Option <= PMode.P2)
                    {
                        Param_Read(); // 读取参数
                        sys.SetMode_Option = 0;
                        Speed.ADDMode = 0;
                        Temp.ADDMode = 0;
                        if (Temp.Set >= Temp.Rel)
                        {
                            Temp.Icon = 0; // 加热图标
                            Temp.Mode = 0; // 加热
                            WIND_OFF;
                        }
                        else
                        {
                            Temp.Icon = 1; // 制冷图标
                            Temp.Mode = 1; // 制冷
                            WIND_ON;
                        }
                    }
                    else
                    {
                        PMode.Option = PMode.P1;
                        Param_Read(); // 读取参数
                        sys.Run_Status = 2;
                        sys.SetMode_Option = 0;
                        Speed.ADDMode = 2;
                        Temp.ADDMode = 0;
                        SetOK_Flag = 1;
                        WIND_OFF;
                        PMode.Circle_Step = 0;
                        Beep_Flash = 5; // 响5下
                    }
                }
                else
                {
                    sys.Run_Status = 2;
                    sys.SetMode_Option = 0;
                    Speed.ADDMode = 2;
                    Temp.ADDMode = 0;
                    SetOK_Flag = 1;
                    WIND_OFF;
                    PMode.Circle_Step = 0;
                    Beep_Flash = 5; // 响5下
                }
                T = 0; // 周期清零
            }
            T = 0;
        }
    }
}
