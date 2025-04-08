#include "Drv_Motor.h"

/**
 * @brief 电机初始化
 *
 */
void Drv_Motor_Init(void)
{
    HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1); // 开启tim15通道2 20值起来
    Speed.CwIcn = 1;//顺时针图标
    HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_SET);
}
