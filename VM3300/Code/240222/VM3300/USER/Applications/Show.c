#include "Show.h"

/**
 * @brief 显示转速
 *
 * @param dis_speed 转速
 */
void Display_Speed(int16_t dis_speed)
{
    DisplayNumber_4BitDig(dis_speed);
}

/**
 * @brief 速度显示处理
 *
 * @param dT 任务周期
 */
void Deal_Speed(float dT)
{
    if (sys.Run_Status == 1)
    {
        if (Speed.ADDMode == 0) // 在电机控制中，速度未处理
        {
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
                if (Speed.Display < Speed.Rel)
                    Speed.Display += 1; // 显示当前速度
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
                if (Speed.Display > Speed.Rel)
                    Speed.Display -= 1; // 显示当前速度
            }
            else // 当前速度大于上一次速度
            {
                Speed.Display = Speed.Display; // 显示上一次速度，不让速度大于当前速度。呈现下降速度的现象
            }

            if (Speed.Display <= Speed.Ctrl) // 实际速度小于等于控制速度
            {
                Speed.ADDMode = 3; // 进入稳定模式
                return;
            }
        }
        else if (Speed.ADDMode == 3) // 速度稳定模式下
        {
            Speed.Display = Speed.Ctrl; // 显示控制速度
        }
    }
    else
    {
        if (Speed.Display && Speed.Display > Speed.Rel)
			Speed.Display -= 1; // 显示当前速度
    }
}

/**
 * @brief 显示屏幕内容
 *
 */
void Show_Display(float dT)
{
    if (sys.Run_Status == 1)
    {
        Speed.Display = Speed.Set; // 显示设定转速
    }
    else
    {
        Deal_Speed(dT);
    }
	
    Display_Speed(Speed.Display);

}
