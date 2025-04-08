#include "Drv_Motor.h"

/**
 * @brief 电机初始化
 *
 */
void Drv_Motor_Init(void)
{
    HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_1); // 开启tim15通道一 10值起来
}
