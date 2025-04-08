#include "Speed.h"

/**********局部变量声明******/
uint32_t high,cycle;//高电平时间（us），和周期时间（us）
float frq;//周期频率值
__IO uint32_t TIM1_TIMEOUT_COUNT = 0;//定时器1定时溢出计数
uint32_t TIM1_CAPTURE_BUF[3] = {0, 0, 0};//分别存储上升沿计数、下降沿计数、下个上升沿计数
__IO uint8_t TIM1_CAPTURE_STA = 0;//状态标记

/*
*****************************************************************
 * 函数原型：void Encoder_Init(void)
 * 功    能：编码器初始化 
*****************************************************************
*/
void Encoder_Init(void)
{   
    HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);//motor1 输入捕获
}

/*
*****************************************************************
 * 函数原型：void Check_Speed(float dT)
 * 功    能：检测速度是否停止-0.05s
*****************************************************************
*/
void Check_Speed(float dT)
{
	Speed.Cnt++;//每50ms进入
    if(Speed.Cnt >= 10)//0.5s发现没出发输入捕获
	{
        Speed.Rel = 0;//将速度清零
		Speed.Cnt = 0;//计数清零
	}
}

/*
*****************************************************************
 * 函数原型：void TIM1_SetCapturePolarity(uint32_t TIM_ICPolarity)
 * 功    能：设置TIM1输入捕获极性
 * 输    入: TIM_INPUTCHANNELPOLARITY_RISING  ：上升沿捕获
 *           TIM_INPUTCHANNELPOLARITY_FALLING ：下降沿捕获
 *           TIM_INPUTCHANNELPOLARITY_BOTHEDGE：上升沿和下降沿都捕获
*****************************************************************
*/
void TIM1_SetCapturePolarity(uint32_t TIM_ICPolarity)
{
    htim1.Instance->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC1NP);
    htim1.Instance->CCER |= (TIM_ICPolarity & (TIM_CCER_CC1P | TIM_CCER_CC1NP));
}

/*
*****************************************************************
 * 函数原型：void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 * 功    能：定时器1时间溢出回调函数
*****************************************************************
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == htim1.Instance)
    {
        TIM1_TIMEOUT_COUNT++;//溢出次数计数
    }
}

/*
*****************************************************************
 * 函数原型：void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
 * 功    能：输入捕获回调函数
*****************************************************************
*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == htim1.Instance)
    {
        Speed.Cnt = 0;
        switch (TIM1_CAPTURE_STA)
        {
        case 1:
            {
                TIM1_CAPTURE_BUF[0] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1) + TIM1_TIMEOUT_COUNT * 50;//因为是在高电平段，所以25的计算方式为=（1/(48000000/分频数12)*计数值200）/上升沿的原因所以除以2
                TIM1_SetCapturePolarity(TIM_INPUTCHANNELPOLARITY_FALLING);//设置为下降沿触发
                TIM1_CAPTURE_STA++;//下一步骤
                break;
            }
        case 2:
            {
                TIM1_CAPTURE_BUF[1] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1) + TIM1_TIMEOUT_COUNT * 50;//因为是在低电平段，所以25的计算方式为=（1/(48000000/分频数12)*计数值200）/下降沿的原因所以除以2
                TIM1_SetCapturePolarity(TIM_INPUTCHANNELPOLARITY_RISING);//设置为上升沿触发
                TIM1_CAPTURE_STA++;//下一步骤
                break;
            }
        case 3:
            {
                TIM1_CAPTURE_BUF[2] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1) + TIM1_TIMEOUT_COUNT * 50;//因为是在高电平段，所以25的计算方式为=（1/(48000000/分频数12)*计数值200）/上升沿的原因所以除以2
                HAL_TIM_IC_Stop_IT(htim, TIM_CHANNEL_1);//停止捕获
                HAL_TIM_Base_Stop_IT(&htim1);//停止定时器更新中断
                TIM1_CAPTURE_STA++;//下一步骤
                break;
            }
        default:
            break;
        }
    }
}

/*
*****************************************************************
 * 函数原型：void TIM1_Poll(void)
 * 功    能：TIM1轮训状态切换
*****************************************************************
*/
uint32_t rel;
void TIM1_Poll(void)
{
    switch (TIM1_CAPTURE_STA)
    {
    case 0:
        {
            TIM1_TIMEOUT_COUNT = 0;//溢出清零
            __HAL_TIM_SET_COUNTER(&htim1, 0);//清除定时器2现有计数
            memset(TIM1_CAPTURE_BUF, 0, sizeof(TIM1_CAPTURE_BUF));//清除捕获计数
            TIM1_SetCapturePolarity(TIM_INPUTCHANNELPOLARITY_RISING);//设置为上升沿触发
            HAL_TIM_Base_Start_IT(&htim1);//启动定时器更新中断
            HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);//启动捕获中断
            TIM1_CAPTURE_STA++;//下一步骤
            break;
        }
    case 4:
        {
            high  = TIM1_CAPTURE_BUF[1] - TIM1_CAPTURE_BUF[0];//高电平持续时间
            cycle = TIM1_CAPTURE_BUF[2] - TIM1_CAPTURE_BUF[0];//周期  
            frq = 1.0 / (((float)cycle) / 1000000.0);//频率计算，用1S/（周期/1000000.0) ;（周期/1000000.0)为转化单位为S
            TIM1_CAPTURE_STA = 0;//重新测电平
			rel = 60 * frq / 2;//用一分钟/高电平时间/电机的一圈脉冲
            Speed.Rel = rel;
            break;
        }
    default:
        break;
    }
}
