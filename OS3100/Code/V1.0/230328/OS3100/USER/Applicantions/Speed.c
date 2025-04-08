#include "Speed.h"

/*
*****************************************************************
 * 函数原型： void Encoder_Init(void)
 * 功    能： 编码器初始化 
*****************************************************************
*/
void Encoder_Init(void)
{   
	HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_2);//motor输入捕获
}

/*
*****************************************************************
 * 函数原型： void Check_Speed(void)
 * 功    能： 检测速度是否停止
*****************************************************************
*/
void Check_Speed(void)
{
   Speed_Cnt++;//每50ms进入
    if(Speed_Cnt>=10)//0.5s发现没出发输入捕获
        Rel_Speed = 0;//将速度清零
}

/*
*****************************************************************
 * 函数原型： void TIM1CaptureChannel2Callback(void)
 * 功    能： Tim1通道2的输入捕获回调函数
*****************************************************************
*/
uint32_t capture, capture1, capture2;
uint32_t rel;
void TIM1CaptureChannel2Callback()
{
	if(sys.Run_Status == 1)
	{
		capture1 = __HAL_TIM_GET_COMPARE(&htim1, TIM_CHANNEL_2);
		if(capture1 > capture2)
			capture = capture1 - capture2;
		else
			capture = capture1 + (0xFFFF - capture2);
		if(capture < 100)
			return;
		rel = 60000000 / capture / 5;
		if((rel - Rel_Speed < 500 && rel - Rel_Speed > 0)  || (Rel_Speed - rel < 500 && Rel_Speed - rel > 0))
			Rel_Speed = rel;
		capture2 = capture1;
		Speed_Cnt = 0;
	}
	else
	{
		capture1 = 0;
		capture2 = 0;
		rel = 0;
	}
}


/*
*****************************************************************
 * 函数原型： void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
 * 功    能： TIM_IC回调函数
*****************************************************************
*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM1)
    {
        if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
        {
            TIM1CaptureChannel2Callback();
        }
    }

}
