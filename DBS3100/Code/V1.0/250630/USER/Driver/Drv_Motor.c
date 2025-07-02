#include "Drv_Motor.h"

/**
 * @brief 电机初始化
 *
 */
void Drv_Motor_Init(void)
{
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4); // 开启tim3通道四 14值起来
}
