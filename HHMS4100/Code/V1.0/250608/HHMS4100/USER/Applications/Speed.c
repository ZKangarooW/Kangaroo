#include "Speed.h"

uint32_t capture[Motor_Num], capture1[Motor_Num], capture2[Motor_Num];
int16_t FilterSpeed[Motor_Num];//滤波的速度
float frq[Motor_Num];

/**
 * @brief 编码器初始化
 *
 */
void Encoder_Init(void)
{
    HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_Base_Start_IT(&htim2);
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);//开启time3通道1输入捕获
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_2);//开启time3通道2输入捕获
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_3);//开启time3通道3输入捕获
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_4);//开启time3通道4输入捕获
	HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_3);//开启time2通道3输入捕获
    HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_4);//开启time2通道4输入捕获
}

/*
*****************************************************************
 * 函数原型：int Filter_ADC(void)
 * 功    能：滑动平均值滤波
 * 输    出：滤波后的值
*****************************************************************
*/
#define S 10//采集10次
int SpeedValue_Buf[Motor_Num][S];//用于储存采集到的Speed值
int k[Motor_Num];//计数值
int Filter_Speed(uint8_t new_work,int16_t speed)
{
    char count;
    long sum = 0;

    SpeedValue_Buf[new_work][k[new_work]++] = speed;
	
    if(k[new_work] == S)//假如读了100组就从新开始
    {
        k[new_work] = 0;
    }
    for(count = 0; count < S; count++)
    {
        sum += SpeedValue_Buf[new_work][count];//100组相加
    }
    if(SpeedValue_Buf[new_work][S-1] == 0)//如果没有读到100组就用第一次读到的数
        return SpeedValue_Buf[new_work][0];
    else//读到100组后
        return (int)(sum / S);//输出平均值
}

/**
 * @brief 检测速度是否停止-0.05s
 *
 * @param dT 任务周期
 */
void Check_Speed(float dT)
{
    for(uint8_t i = 0;i<Motor_Num;i++)
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
    Work_Num[i].Speed.Rel = frq[i] * 60 / 2;
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
            capture1[0] = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_1);//获取Tim3通道1的输入捕获
            CaptureChanneCallback(0);
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
        {
            capture1[1] = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_2);//获取Tim3通道2的输入捕获
            CaptureChanneCallback(1);
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
        {
            capture1[3] = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_3);//获取Tim3通道3的输入捕获
            CaptureChanneCallback(3);
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)
        {
            capture1[5] = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_4);//获取Tim3通道4的输入捕获
            CaptureChanneCallback(5);
        }
    }
	if (htim->Instance == TIM2)
    {
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
        {
            capture1[4] = __HAL_TIM_GET_COMPARE(&htim2, TIM_CHANNEL_3);//获取Tim2通道3的输入捕获
            CaptureChanneCallback(4);
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)
        {
            capture1[2] = __HAL_TIM_GET_COMPARE(&htim2, TIM_CHANNEL_4);//获取Tim2通道4的输入捕获
            CaptureChanneCallback(2);
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
  
    while(1)
    {
        Check_Speed(0.05f);
        vTaskDelayUntil(&xLastWakeTime, 50);
    }
}
