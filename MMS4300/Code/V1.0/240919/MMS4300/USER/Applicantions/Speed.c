#include "Speed.h"

uint32_t capture[15], capture1[15], capture2[15];
float frq[15];

/**
 * @brief 编码器初始化
 *
 */
void Encoder_Init(void)
{
    HAL_TIM_Base_Start_IT(&htim3);
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);//开启time3通道1输入捕获
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_2);//开启time3通道2输入捕获
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_3);//开启time3通道3输入捕获
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_4);//开启time3通道4输入捕获
    HAL_TIM_Base_Start_IT(&htim2);
    HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);//开启time2通道1输入捕获
    HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);//开启time2通道2输入捕获
    HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_3);//开启time2通道3输入捕获
    HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_4);//开启time2通道4输入捕获
    HAL_TIM_Base_Start_IT(&htim4);
    HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_1);//开启time4通道1输入捕获
    HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_2);//开启time4通道2输入捕获
    HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_3);//开启time4通道3输入捕获
    HAL_TIM_Base_Start_IT(&htim8);
    HAL_TIM_IC_Start_IT(&htim8, TIM_CHANNEL_1);//开启time8通道1输入捕获
    HAL_TIM_IC_Start_IT(&htim8, TIM_CHANNEL_2);//开启time8通道2输入捕获
    HAL_TIM_IC_Start_IT(&htim8, TIM_CHANNEL_3);//开启time8通道3输入捕获
    HAL_TIM_IC_Start_IT(&htim8, TIM_CHANNEL_4);//开启time8通道4输入捕获
}

/**
 * @brief 检测速度是否停止-0.05s
 *
 * @param dT 任务周期
 */
void Check_Speed(float dT)
{
    for(uint8_t i = 0;i<15;i++)
    {
        Work_Num[i].Speed.Stop_Cnt += dT;//每50ms进入
        if (Work_Num[i].Speed.Stop_Cnt >= 1.0) // 0.5s发现没出发输入捕获
        {
            Work_Num[i].Speed.Rel = 0;      // 将速度清零
            Work_Num[i].Speed.Stop_Cnt = 0; // 计数清零
        }
    }
}

/**
 * @brief Tim3通道4的输入捕获回调函数
 *
 */
void CaptureChanneCallback(uint8_t i)
{
    if (capture1[i] > capture2[i])
        capture[i] = capture1[i] - capture2[i];
    else
        capture[i] = capture1[i] + (0xFFFF - capture2[i]);
    frq[i] = 10000.0f / (float)capture[i];//计算频率
    capture2[i] = capture1[i];
    Work_Num[i].Speed.Rel = frq[i] * 60 / 5;
    Work_Num[i].Speed.Stop_Cnt = 0;
}

/**
 * @brief TIM_IC回调函数
 *
 * @param htim
 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM3)
    {
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
        {
            capture1[6] = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_1);//获取Tim3通道1的输入捕获
            CaptureChanneCallback(6);
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
        {
            capture1[7] = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_2);//获取Tim3通道2的输入捕获
            CaptureChanneCallback(7);
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
        {
            capture1[9] = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_3);//获取Tim3通道3的输入捕获
            CaptureChanneCallback(9);
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)
        {
            capture1[10] = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_4);//获取Tim3通道4的输入捕获
            CaptureChanneCallback(10);
        }
    }
    if (htim->Instance == TIM2)
    {
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
        {
            capture1[0] = __HAL_TIM_GET_COMPARE(&htim2, TIM_CHANNEL_1);//获取Tim3通道1的输入捕获
            CaptureChanneCallback(0);
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
        {
            capture1[1] = __HAL_TIM_GET_COMPARE(&htim2, TIM_CHANNEL_2);//获取Tim3通道2的输入捕获
            CaptureChanneCallback(1);
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
        {
            capture1[3] = __HAL_TIM_GET_COMPARE(&htim2, TIM_CHANNEL_3);//获取Tim3通道3的输入捕获
            CaptureChanneCallback(3);
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)
        {
            capture1[4] = __HAL_TIM_GET_COMPARE(&htim2, TIM_CHANNEL_4);//获取Tim3通道4的输入捕获
            CaptureChanneCallback(4);
        }
    }
    if (htim->Instance == TIM4)
    {
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
        {
            capture1[8] = __HAL_TIM_GET_COMPARE(&htim4, TIM_CHANNEL_1);//获取Tim3通道1的输入捕获
            CaptureChanneCallback(8);
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
        {
            capture1[11] = __HAL_TIM_GET_COMPARE(&htim4, TIM_CHANNEL_2);//获取Tim3通道2的输入捕获
            CaptureChanneCallback(11);
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
        {
            capture1[14] = __HAL_TIM_GET_COMPARE(&htim4, TIM_CHANNEL_3);//获取Tim3通道3的输入捕获
            CaptureChanneCallback(14);
        }
    }
    if (htim->Instance == TIM8)
    {
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
        {
            capture1[12] = __HAL_TIM_GET_COMPARE(&htim8, TIM_CHANNEL_1);//获取Tim3通道1的输入捕获
            CaptureChanneCallback(12);
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
        {
            capture1[13] = __HAL_TIM_GET_COMPARE(&htim8, TIM_CHANNEL_2);//获取Tim3通道2的输入捕获
            CaptureChanneCallback(13);
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
        {
            capture1[2] = __HAL_TIM_GET_COMPARE(&htim8, TIM_CHANNEL_3);//获取Tim3通道3的输入捕获
            CaptureChanneCallback(2);
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)
        {
            capture1[5] = __HAL_TIM_GET_COMPARE(&htim8, TIM_CHANNEL_4);//获取Tim3通道4的输入捕获
            CaptureChanneCallback(5);
        }
    }
}
