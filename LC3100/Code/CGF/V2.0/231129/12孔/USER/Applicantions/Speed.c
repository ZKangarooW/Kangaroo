#include "Speed.h"

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
	Speed.Stop_Cnt++;//每50ms进入
    if(Speed.Stop_Cnt >= 10)//0.5s发现没出发输入捕获
	{
        Speed.Rel = 0;//将速度清零
		Speed.Stop_Cnt = 0;//计数清零
	}
}

/*
*****************************************************************
 * 函数原型：void TIM1CaptureChannel1Callback(void)
 * 功    能：Tim1通道1的输入捕获回调函数
*****************************************************************
*/
uint32_t Capture, Capture1, Capture2;
uint32_t rel;
void TIM1CaptureChannel1Callback(void)
{
    Capture1 = __HAL_TIM_GET_COMPARE(&htim1, TIM_CHANNEL_1);//读取编码器的值
    if(Capture1 > Capture2)//假如读到的值大于上一次的值
        Capture = Capture1 - Capture2;//得出当前的值
    else
        Capture = Capture1 + (0xFFFF - Capture2);//如果小于上次的值，0xFFFF-上一次的值
    if(Capture < 100)//过滤小于100的
        return;
    rel = 60000000 / (Capture * 12);//用1S/编码器的值*一圈的脉冲
    Capture2 = Capture1;//将读到的值赋值给上一次的值
	Speed.Rel = rel;
    Speed.Stop_Cnt = 0;//将检测速度的时间清零
}

/*
*****************************************************************
 * 函数原型：void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
 * 功    能：TIM_IC回调函数
*****************************************************************
*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM1) 
    {
        if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_1) 
        {
            TIM1CaptureChannel1Callback();
        }     
    }
}
