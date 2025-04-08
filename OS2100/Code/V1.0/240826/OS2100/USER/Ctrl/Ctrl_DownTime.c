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
        if (Time.Rel > 0)
        {
            T += dT;
        }
        if (T >= 1.0f) // 1S
        {
            if (Time.Rel)
                Time.Rel--; // 控制时间--

            if (Time.Rel == 0)
            {
                sys.Run_Status = 0;//关闭运行
                Speed.ADDMode = 2;//进入减速模式下
                Twinkle_Time = 0;
                Key_Status = 0;
                Beep_Flash = 5;
                SetOK_Flag = 1;
                T = 0; // 周期清零
            }
            T = 0;
        }
    }
}
