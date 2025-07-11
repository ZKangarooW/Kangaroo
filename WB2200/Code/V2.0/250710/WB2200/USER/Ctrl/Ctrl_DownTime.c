#include "Ctrl_DownTime.h"

/**
 * @brief 时间倒计时检测
 *
 * @param dT 任务周期
 */
void Cheak_TimeDown(float dT)
{
    static float T;
    if(sys.Run_Status == 1)//启动系统
    {
        if(sys.DownTime_Type == 0 && Temp.ADDMode != 4)//C1
        {
            return;
        }
		if(Time.Rel > 0)
		{
			T += dT;
		}
        if(T >= 1.0f)//1S
        {			
            if(Time.Rel)
                Time.Rel--;//控制时间--
            if(Time.Rel == 0)
            {
                sys.Run_Status = 0;
//                SetOK_Flag = 1;//设置因为进去设置判断不出有改变。所以自己加了
                Time.Rel = Time.Set;
                Temp_ShowFlag = 0;//这个需要清零一次，不然不会闪烁
                Beep_Flash = 5;//响5下
            }
            T = 0;//周期清零
        }
    }
}
