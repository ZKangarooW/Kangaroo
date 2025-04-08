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
        if (Time.Rel > 0 && sys.Motor_Stop==0)
        {
            T += dT;
        }
        if (T >= 1.0f) // 1S
        {
            if (Time.Rel)
                Time.Rel--; // 控制时间--

            if (Time.Rel == 0)
            {
                Time.Rel = Time.Set;
                sys.Motor_Stop = 1;//检测电机
                Speed.ADDMode = 2;//进入减速模式下
                Beep_Flash = 5; // 响5下
            }
            T = 0;
        }
    }
}
