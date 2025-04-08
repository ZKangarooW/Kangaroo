#include "Drv_Motor.h"

/**
 * @brief 电机初始化
 *
 */
void Drv_Motor_Init(void)
{
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2); // 开启tim3通道二 2值起来
    HAL_GPIO_WritePin(MO_GPIO_Port, MO_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_SET);
}
