#include "Speed.h"

/*
*****************************************************************
 * 函数原型：void Encoder_Init(void)
 * 功    能：编码器初始化 
*****************************************************************
*/
void Encoder_Init(void)
{   
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_3);//motor1 输入捕获
}

/*
*****************************************************************
 * 函数原型：void Check_Speed(float dT)
 * 功    能：检测速度是否停止-0.05s
*****************************************************************
*/
void Check_Speed(float dT)
{
	Speed_Cnt++;//每50ms进入
    if(Speed_Cnt >= 10)//0.5s发现没出发输入捕获
	{
        Rel_Speed = 0;//将速度清零
		Speed_Cnt = 0;//计数清零
	}
}

/*
*****************************************************************
 * 函数原型：void TIM3CaptureChannel3Callback(void)
 * 功    能：Tim3通道3的输入捕获回调函数
*****************************************************************
*/
uint32_t Capture, Capture1, Capture2;
uint32_t rel;
void TIM3CaptureChannel3Callback(void)
{
    Capture1 = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_3);
    if(Capture1 > Capture2)
        Capture = Capture1 - Capture2;
    else
        Capture = Capture1 + (0xFFFF - Capture2);
    if(Capture < 100)
        return;
    rel = 60000000 / (Capture * 6);
    Capture2 = Capture1;
    if((rel - Rel_Speed < 1000 && rel - Rel_Speed > 0)  || (Rel_Speed - rel < 1000 && Rel_Speed - rel > 0))
	{
		Rel_Speed = rel;
	}
    Speed_Cnt =0;
}

/*
*****************************************************************
 * 函数原型：void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
 * 功    能：TIM_IC回调函数
*****************************************************************
*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM3) 
    {
        if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_3) 
        {
            TIM3CaptureChannel3Callback();
        }     
    }
}
