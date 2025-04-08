#include "Speed.h"

uint32_t capture, capture1, capture2;
int16_t FilterSpeed;
float rel1;

/**
 * @brief 编码器初始化
 *
 */
void Encoder_Init(void)
{
    HAL_TIM_Base_Start_IT(&htim17);
    HAL_TIM_IC_Start_IT(&htim17, TIM_CHANNEL_1); // 开启time17通道1输入捕获
}

/*
*****************************************************************
 * 函数原型：int Filter_ADC(void)
 * 功    能：滑动平均值滤波
 * 输    出：滤波后的值
*****************************************************************
*/
#define S 10//采集10次
int SpeedValue_Buf[S];//用于储存采集到的Speed值
int k;//计数值
int Filter_Speed(int16_t speed)
{
    char count;
    long sum = 0;

    SpeedValue_Buf[k++] = speed;
	
    if(k == S)//假如读了100组就从新开始
    {
        k = 0;
    }
    for(count = 0; count < S; count++)
    {
        sum += SpeedValue_Buf[count];//100组相加
    }
    if(SpeedValue_Buf[S-1] == 0)//如果没有读到100组就用第一次读到的数
        return SpeedValue_Buf[0];
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
    Speed.Stop_Cnt += dT;      // 每50ms进入
    if (Speed.Stop_Cnt >= 1.0) // 0.5s发现没出发输入捕获
    {
        FilterSpeed = 0;
        k = 0;
        memset(SpeedValue_Buf,0,sizeof (SpeedValue_Buf));
        Speed.Rel = 0;      // 将速度清零
        Speed.Stop_Cnt = 0; // 计数清零
    }
}

/**
 * @brief Tim17通道1的输入捕获回调函数
 *
 */
void TIM17CaptureChannel1Callback(void)
{
    capture1 = __HAL_TIM_GET_COMPARE(&htim17, TIM_CHANNEL_1); // 获取Tim14通道1的输入捕获
    if (capture1 > capture2)
        capture = capture1 - capture2;
    else
        capture = capture1 + (0xFFFF - capture2);
    rel1 = 10000.0f / (float)capture; // 计算速度
    capture2 = capture1;
    FilterSpeed = rel1 * 60 / 5; // 将速度赋值给L1的实际速度
    Speed.Rel = Filter_Speed(FilterSpeed);
    Speed.Stop_Cnt = 0;
}

/**
 * @brief TIM_IC回调函数
 *
 * @param htim
 */
void Speed_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM17)
    {
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
        {
            TIM17CaptureChannel1Callback();
        }
    }
}
