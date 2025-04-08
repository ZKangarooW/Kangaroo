#include "Drv_HEAT.h"

/**
 * @brief 初始化加热制冷
 *
 */
void HEAT_Init(void)
{
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
}


/**
 * @brief 控温模式任务
 * 
 * @param dT 任务周期
 * @param pwm 功率
 */
void HEAT_Duty(float dT, int16_t pwm)
{
    static float T;
    static uint8_t Mode; // 储存上一次的模式
    uint16_t Val;

    Val = ABS(pwm);

    if (pwm >= 0)
    {
        Temp.Mode = 0; // 加热
    }
    else
    {
        Temp.Mode = 1; // 制冷
    }

    if (Temp.Mode != Mode)
    {
        T += dT;
        if (T <= 1.0f)
        {
            COLD = 0;
            HEAT = 0;
        }
        else
        {
            T = 0;
            Mode = Temp.Mode;
        }
    }
    else
    {
        if (Temp.Mode)
        {
            COLD = Val;
            HEAT = 0;
        }
        else
        {
            COLD = 0;
            HEAT = Val;
        }
    }
}