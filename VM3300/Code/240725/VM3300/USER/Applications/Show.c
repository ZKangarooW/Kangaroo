#include "Show.h"

/**
 * @brief 速度显示处理
 *
 * @param dT 任务周期
 */
void Deal_Speed(float dT)
{
    if ((sys.Run_Status ||(Infrared[0].Someone || Infrared[1].Someone)) || Speed.Rel > 10)
    {
        if (Speed.ADDMode == 0) // 在电机控制中，速度未处理
        {
			Speed.Display = Speed.Rel;
            if (Speed.Ctrl >= Speed.Display) // 控制速度大于实际速度
            {
                Speed.ADDMode = 1; // 进入加速模式下
            }
            else if (Speed.Ctrl < Speed.Display) // 控制速度小于实际速度
            {
                Speed.ADDMode = 2; // 进入减速模式下
            }
        }
        if (Speed.ADDMode == 1) // 在进入加速模式下
        {
            if (Speed.Rel > Speed.Display) // 当前速度大于显示速度
            {
                    Speed.Display = Speed.Rel; // 显示当前速度
            }
            else // 当前速度小于上一次速度
            {
                Speed.Display = Speed.Display; // 显示上一次速度，不让速度小于当前速度。呈现攀升速度的现象
            }
            if (Speed.Display >= Speed.Ctrl) // 实际速度大于等于控制速度
            {
                Speed.ADDMode = 3; // 进入稳定模式
                return;
            }
        }
        if (Speed.ADDMode == 2) // 速度下降模式下
        {
            if (Speed.Rel < Speed.Display) // 当前速度小于上一次速度
            {
                    Speed.Display = Speed.Rel; // 显示当前速度
            }
            else // 当前速度大于上一次速度
            {
                Speed.Display = Speed.Display; // 显示上一次速度，不让速度大于当前速度。呈现下降速度的现象
            }
            if(sys.Motor_Stop == 0)
            {
                if (Speed.Display <= Speed.Ctrl) // 实际速度小于等于控制速度
                {
                    Speed.ADDMode = 3; // 进入稳定模式
                    return;
                }
            }
        }
        else if (Speed.ADDMode == 3) // 速度稳定模式下
        {
            Speed.Display = Speed.Ctrl; // 显示控制速度
        }
    }
	else
	{
		Speed.Display = Speed.Set; // 显示设定转速
		Speed.ADDMode = 0;
	}
}

/**
 * @brief 显示屏幕内容
 *
 */
void Show_Display(float dT)
{
    if(sys.Run_Status ||(Infrared[0].Someone || Infrared[1].Someone))//启动后
    {
        if(Key_Status)
        {
            Speed.Display = Speed.Set; // 显示设定转速
        }
        else
        {
            Deal_Speed(dT);
        }
    }
    else//不启动
    {
        Speed.ADDMode = 0;
        Speed.Display = Speed.Set; // 显示设定转速
    }
    DisplayNumber_4BitDig(Speed.Display);
}
