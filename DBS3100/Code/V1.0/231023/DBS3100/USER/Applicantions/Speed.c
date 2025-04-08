#include "Speed.h"

/*
*****************************************************************
 * 函数原型：void Encoder_Init(void)
 * 功    能：编码器初始化
*****************************************************************
*/
void Encoder_Init(void)
{
	HAL_TIM_Base_Start_IT(&htim3);
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);//开启time1通道3输入捕获
}

/*
*****************************************************************
 * 函数原型：void Check_Speed(float dT)
 * 功    能：检测速度是否停止-0.05s
*****************************************************************
*/
void Check_Speed(float dT)
{
	Speed.Stop_Cnt += dT;//每50ms进入
    if(Speed.Stop_Cnt >= 1.0)//0.5s发现没出发输入捕获
	{
        Speed.Rel = 0;//将速度清零
		Speed.Stop_Cnt = 0;//计数清零
	}
}

/*
*****************************************************************
 * 函数原型：void TIM3CaptureChannel1Callback(void)
 * 功    能：Tim3通道1的输入捕获回调函数
*****************************************************************
*/
uint32_t L1_capture,L1_capture1,L1_capture2;
float rel1;
void TIM3CaptureChannel1Callback(void)
{
    L1_capture1=__HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_1);//获取Tim3通道1的输入捕获
    if(L1_capture1>L1_capture2)
        L1_capture=L1_capture1-L1_capture2;
    else
        L1_capture=L1_capture1+(0xFFFF-L1_capture2);
    if(L1_capture<100)
        return;
    rel1=10000.0f/(float)L1_capture;//计算速度
    L1_capture2=L1_capture1;
    Speed.Rel=rel1*60/2;//将速度赋值给L1的实际速度	
    Speed.Stop_Cnt = 0;
}	

/*
*****************************************************************
 * 函数原型： void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
 * 功    能： TIM_IC回调函数
*****************************************************************
*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM3) 
    {
        if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_1) 
        {
            TIM3CaptureChannel1Callback();
        } 
    }
}
