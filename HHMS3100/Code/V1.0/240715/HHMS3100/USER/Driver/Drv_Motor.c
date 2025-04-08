#include "Drv_Motor.h"

/**
 * @brief 电机初始化
 *
 */
void Drv_Motor_Init(void)
{
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1); // 开启tim5通道四 26值起来 63转
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2); // 开启tim5通道四 26值起来
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_3); // 开启tim5通道四 26值起来
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_4); // 开启tim5通道四 26值起来
    MO0_ON;
    MO1_ON;
    MO2_ON;
    MO3_ON;
}
