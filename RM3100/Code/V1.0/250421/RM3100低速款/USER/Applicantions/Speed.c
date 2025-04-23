#include "Speed.h"

/*
*****************************************************************
 * 函数原型：void Encoder_Init(void)
 * 功    能：编码器初始化 
*****************************************************************
*/
void Encoder_Init(void)
{   
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);//Motor输入捕获
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
uint32_t Capture, Capture1, Capture2;//捕获和计算的值
uint32_t rel;//实际计算后的速度
void TIM3CaptureChannel1Callback(void)
{
    Capture1 = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_1);//输入捕获到的数值
    if(Capture1 > Capture2)//当前的数值大于之前的数时
        Capture = Capture1 - Capture2;//算出捕获到的数
    else//加入当前数值小于之前的数值时，表示溢出了
        Capture = Capture1 + (0xFFFF - Capture2);//用当前数值加上65535-之前数值
    if(Capture < 100)//过滤
        return;
	rel = (60000000 / (Capture * 4))/60;//(60000000us/(捕获到的值*一圈9个脉冲))/56的减速比,RM3100
    Capture2 = Capture1;//当前的值赋值给之前的值，做记录
    Rel_Speed = rel;
    Speed_Cnt = 0;//速度计数清零，用于判断速度是否为0
}

/*
*****************************************************************
 * 函数原型：void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
 * 功    能：TIM_IC回调函数
*****************************************************************
*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM3)//进入TIM3的中断
    {
        if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_1)//进入TIM3通道一的中断
        {
            TIM3CaptureChannel1Callback();//进入计算速度的函数
        }     
    }
}
