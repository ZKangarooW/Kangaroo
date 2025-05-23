#include "Speed.h"

/**********全局变量声明******/
uint8_t CAPTURE_Status = 0;//捕获状态
uint8_t CAPTURE_First = 1;//捕获第一个高电平
uint16_t TIM1CH1_CAPTURE_STA = 0;//捕获周期数
uint32_t TIM1CH1_CAPTURE_VAL;//捕获计数值
uint32_t P_Status = 1;//捕获周期计数状态  1开启 0关闭
float frq;//周期频率值

/*
*****************************************************************
 * 函数原型：void Encoder_Init(void)
 * 功    能：编码器初始化
*****************************************************************
*/
void Encoder_Init(void)
{
	HAL_TIM_Base_Start_IT(&htim1);//开启定时器1
    HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_3);//开启time1通道3输入捕获
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
 * 函数原型：void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 * 功    能：定时器计数回调函数
*****************************************************************
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM1)
    {
        if(P_Status)//捕获周期计数状态:开启
        {    
            TIM1CH1_CAPTURE_STA++;//捕获周期数++
        }
    }
}

/*
*****************************************************************
 * 函数原型：void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
 * 功    能：输入捕获回调函数
*****************************************************************
*/
uint32_t Capture,rel;//输入捕获数和计算后的速度
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if(CAPTURE_Status == 0)
    {   
        if(CAPTURE_First)//捕获到第一个上升沿
        {
            CAPTURE_Status = 1;//捕获中
            CAPTURE_First = 0;//清除捕获第一个上升沿标志
            TIM1CH1_CAPTURE_VAL = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_3);//获取当前捕获计数值
            Capture = TIM1CH1_CAPTURE_STA;//定时器的周期值
            Capture *= 50;//一个周期50us（48000000/12/200 = 0.00005us）
            Capture += TIM1CH1_CAPTURE_VAL;//输入不获到的微秒数加上之前周期的时间
			frq = 1.0 / (((float)Capture) / 1000000.0);//频率计算，用1S/（周期/1000000.0) ;（周期/1000000.0)为转化单位为S
			rel = 60 * frq / 2;//rpm
			Rel_Speed = rel;
            P_Status = 0;//捕获周期计数状态:0关闭
			Speed_Cnt = 0;//检测速度
            __HAL_TIM_SET_COUNTER(&htim1, 0);//清楚输入捕获的值
            __HAL_TIM_DISABLE(&htim1);//关闭定时器一计数
        }
        else
        {
            TIM1CH1_CAPTURE_STA = 0;//清除周期计数
            TIM1CH1_CAPTURE_VAL = 0;//清楚捕获寄存器
            CAPTURE_First = 1;//已捕获第一个上升沿
            CAPTURE_Status = 0;//捕获结束
            P_Status = 1;//捕获周期计数
        }
    }
}

/*
*****************************************************************
 * 函数原型：void TIM1_Poll(void)
 * 功    能：TIM1轮训状态切换
*****************************************************************
*/
void TIM1_Poll(void)
{
    if(CAPTURE_Status)
	{	
		__HAL_TIM_ENABLE(&htim1);//开启计数定时器一计数
		CAPTURE_Status=0;//捕获状态为0
		TIM1CH1_CAPTURE_STA=0;//捕获的周期清零
	}
}
