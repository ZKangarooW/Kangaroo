#include "Speed.h"

/**
 * @brief 编码器初始化
 *
 */
void Encoder_Init(void)
{
    HAL_TIM_Base_Start_IT(&htim1);
    HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_2); // 开启time1通道2输入捕获
}

/**
 * @brief 检测速度是否停止-0.05s
 *
 * @param dT 任务周期
 */
void Check_Speed(float dT)
{
    Speed.Stop_Cnt += dT;      // 每50ms进入
    if (Speed.Stop_Cnt >= 1.0) // 0.5s发现没出发输入捕获
    {
        Speed.Rel = 0;      // 将速度清零
        Speed.Stop_Cnt = 0; // 计数清零
    }
}

uint32_t capture, capture1, capture2;
float rel1;
/**
 * @brief Tim1通道2的输入捕获回调函数
 *
 */
void TIM1CaptureChannel2Callback(void)
{
    capture1 = __HAL_TIM_GET_COMPARE(&htim1, TIM_CHANNEL_2); // 获取Tim14通道1的输入捕获
    if (capture1 > capture2)
        capture = capture1 - capture2;
    else
        capture = capture1 + (0xFFFF - capture2);
    rel1 = 10000.0f / (float)capture; // 计算速度
    capture2 = capture1;
    Speed.Rel = rel1 * 60 / 5; // 将速度赋值给L1的实际速度
    Speed.Stop_Cnt = 0;
}

/**
 * @brief TIM_IC回调函数
 *
 * @param htim
 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM1)
    {
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
        {
            TIM1CaptureChannel2Callback();
        }
    }
}
