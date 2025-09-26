#include "Drv_Motor.h"

/**
 * @brief 电机初始化
 *
 */
void Drv_Motor_Init(void)
{
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2); // 开启tim1通道二 28值起来
}
