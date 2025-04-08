#include "Speed.h"

/**
 * @brief 编码器初始化
 *
 */
void Encoder_Init(void)
{
    HAL_TIM_Base_Start_IT(&htim3);
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);//开启time3通道1输入捕获
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_2);//开启time3通道1输入捕获
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_3);//开启time3通道1输入捕获
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_4);//开启time3通道1输入捕获
}

/**
 * @brief 检测速度是否停止-0.05s
 *
 * @param dT 任务周期
 */
void Check_Speed(float dT)
{
    Work_Num[0].Speed.Stop_Cnt += dT;//每50ms进入
    if (Work_Num[0].Speed.Stop_Cnt >= 1.0) // 0.5s发现没出发输入捕获
    {
        Work_Num[0].Speed.Rel = 0;      // 将速度清零
        Work_Num[0].Speed.Stop_Cnt = 0; // 计数清零
    }
}

uint32_t capture[4], capture1[4], capture2[4];
float frq[4];
/**
 * @brief Tim3通道3的输入捕获回调函数
 *
 */
void TIM3CaptureChannel3Callback(void)
{
    capture1[0] = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_3);//获取Tim3通道3的输入捕获
    if (capture1[0] > capture2[0])
        capture[0] = capture1[0] - capture2[0];
    else
        capture[0] = capture1[0] + (0xFFFF - capture2[0]);
    frq[0] = 10000.0f / (float)(capture[0]);//计算频率
    capture2[0] = capture1[0];
    Work_Num[0].Speed.Rel = frq[0] * 60 / 2;//将速度赋值给L1的实际速度
    Work_Num[0].Speed.Stop_Cnt = 0;
}

/**
 * @brief Tim3通道1的输入捕获回调函数
 *
 */
void TIM3CaptureChannel1Callback(void)
{
    capture1[1] = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_1);//获取Tim3通道1的输入捕获
    if (capture1[1] > capture2[1])
        capture[1] = capture1[1] - capture2[1];
    else
        capture[1] = capture1[1] + (0xFFFF - capture2[1]);
    frq[1] = 10000.0f / (float)capture[0];//计算频率
    capture2[1] = capture1[1];
    Work_Num[1].Speed.Rel = frq[1] * 60 / 2;//将速度赋值给L1的实际速度
    Work_Num[1].Speed.Stop_Cnt = 0;
}

/**
 * @brief Tim3通道2的输入捕获回调函数
 *
 */
void TIM3CaptureChanne12Callback(void)
{
    capture1[3] = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_2);//获取Tim3通道2的输入捕获
    if (capture1[3] > capture2[3])
        capture[3] = capture1[3] - capture2[3];
    else
        capture[3] = capture1[3] + (0xFFFF - capture2[3]);
    frq[3] = 10000.0f / (float)capture[3];//计算频率
    capture2[3] = capture1[3];
    Work_Num[3].Speed.Rel = frq[3] * 60 / 2;//将速度赋值给L1的实际速度
    Work_Num[3].Speed.Stop_Cnt = 0;
}

/**
 * @brief Tim3通道4的输入捕获回调函数
 *
 */
void TIM3CaptureChanne14Callback(void)
{
    capture1[2] = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_4);//获取Tim3通道4的输入捕获
    if (capture1[2] > capture2[2])
        capture[2] = capture1[2] - capture2[2];
    else
        capture[2] = capture1[2] + (0xFFFF - capture2[2]);
    frq[2] = 10000.0f / (float)capture[2];//计算频率
    capture2[2] = capture1[2];
    Work_Num[2].Speed.Rel = frq[2] * 60 / 2;//将速度赋值给L1的实际速度
    Work_Num[2].Speed.Stop_Cnt = 0;
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
            TIM3CaptureChannel1Callback();
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
        {
            TIM3CaptureChanne12Callback();
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
        {
            TIM3CaptureChannel3Callback();
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)
        {
            TIM3CaptureChanne14Callback();
        }
    }
}

/**
 * @brief 测速任务
 * 
 */
void Speed_Task(void *p)
{
    TickType_t xLastWakeTime;//刚开始唤醒的时间
    xLastWakeTime = xTaskGetTickCount ();

    /**********编码器初始化***********/
    Encoder_Init();
  
    while(1)
    {
        Check_Speed(0.05f);
        vTaskDelayUntil(&xLastWakeTime, 50);
    }
}
