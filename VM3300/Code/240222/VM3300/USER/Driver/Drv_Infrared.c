#include "Drv_Infrared.h"

/**********结构体************/
_Infrared_ Infrared[2];

/*
*****************************************************************
 * 函数原型：void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 * 功    能：定时器计数中断
*****************************************************************
*/
void Infrared_TIM_Interrupt(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == htim6.Instance) 
	{
		if(Infrared[0].step == 0)
		{
			Infrared_Send1 = 79;
			Infrared_Send2 = 79;
			Infrared[0].time++;
			if(Infrared[0].time >= 900)
			{
				Infrared[0].step = 1;
				Infrared[0].time = 0;
			}
		}
		if(Infrared[0].step == 1)
		{
			Infrared_Send1 = 0;
			Infrared_Send2 = 0;
			Infrared[0].time++;
			if(Infrared[0].time >= 225)
			{
				Infrared[0].step = 2;
				Infrared[0].time = 0;
			}
		}
		if(Infrared[0].step == 2)
		{
			Infrared_Send1 = 79;
			Infrared_Send2 = 79;
			Infrared[0].time++;
			if(Infrared[0].time >= 56)
			{
				Infrared[0].step = 3;
				Infrared[0].time = 0;
			}
		}
		if(Infrared[0].step == 3)
		{
			Infrared_Send1 = 0;
			Infrared_Send2 = 0;
			Infrared[0].time++;
			if(Infrared[0].time >= 9819)
			{
				Infrared[0].step = 0;
				Infrared[0].time = 0;
			}
		}
	}
}

/**
 * @brief 检测速度是否停止-0.05s
 *
 * @param dT 任务周期
 */
void Check_Infrared(float dT)
{
    Infrared[0].Someone_Time += dT;//每100ms进入
	Infrared[1].Someone_Time += dT;//每100ms进入
    if (Infrared[0].Someone_Time >= 0.5f)// 0.5s发现没出发输入捕获
    {
        Infrared[0].Someone = 0;// 将有人清零
        Infrared[0].Someone_Time = 0;//计数清零
    }
	if (Infrared[1].Someone_Time >= 0.5f)// 0.5s发现没出发输入捕获
    {
        Infrared[1].Someone = 0;// 将有人清零
        Infrared[1].Someone_Time = 0;//计数清零
    }
}

void Infrared_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM15)
	{
		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
		{
			if(IR1_IN)//capture了上升沿
			{
				TIM_RESET_CAPTUREPOLARITY(&htim15, TIM_CHANNEL_2);//清除捕获上升沿
				TIM_SET_CAPTUREPOLARITY(&htim15, TIM_CHANNEL_2, TIM_ICPOLARITY_FALLING);//开始捕获下降沿
				__HAL_TIM_SET_COUNTER(&htim15, 0);//清空定时器值
				Infrared[0].IRSta |= 0x10;//[4]置1，即标志上升沿已捕获
			}
			else  //捕获下降沿
			{
				Infrared[0].Dval = HAL_TIM_ReadCapturedValue(&htim15, TIM_CHANNEL_2);//下降沿计数
				TIM_RESET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_2);//清除捕获下降沿
				TIM_SET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_2,TIM_ICPOLARITY_RISING);//开始捕获上升沿
				if(Infrared[0].IRSta & 0x10)  //如果完成了一次高电平捕获，接下来看是否有引导码
				{
					if(Infrared[0].Dval>2100 && Infrared[0].Dval<2400)//2.25ms高电平，引导码
					{
						Infrared[0].Someone = 1;
						Infrared[0].Someone_Time = 0;
						Infrared[0].IRSta &= 0xF0;  
					}
				}	
				Infrared[0].IRSta &=~(1<<4);//清空[4]，即高电平计数结束
			}
		}
		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
		{
			if(IR2_IN)//capture了上升沿
			{
				TIM_RESET_CAPTUREPOLARITY(&htim15, TIM_CHANNEL_1);//清除捕获上升沿
				TIM_SET_CAPTUREPOLARITY(&htim15, TIM_CHANNEL_1, TIM_ICPOLARITY_FALLING);//开始捕获下降沿
				__HAL_TIM_SET_COUNTER(&htim15, 0);//清空定时器值
				Infrared[1].IRSta |= 0x10;//[4]置1，即标志上升沿已捕获
			}
			else  //捕获下降沿
			{
				Infrared[1].Dval = HAL_TIM_ReadCapturedValue(&htim15, TIM_CHANNEL_1);//下降沿计数
				TIM_RESET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_1);//清除捕获下降沿
				TIM_SET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);//开始捕获上升沿
				if(Infrared[1].IRSta & 0x10)//如果完成了一次高电平捕获，接下来看是否有引导码
				{
					if(Infrared[1].Dval>2100 && Infrared[1].Dval<2600)//2.25ms高电平，引导码
					{
						Infrared[1].Someone = 1;
						Infrared[1].Someone_Time = 0;
						Infrared[1].IRSta &= 0xF0;  
					}
				}	
				Infrared[1].IRSta &=~(1<<4); //清空[4]，即高电平计数结束
			}
		}
	}
}

void Drv_Infrared_Init(void)
{
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);//开启tim3通道一
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);//开启tim3通道二
	
	HAL_TIM_IC_Start_IT(&htim15, TIM_CHANNEL_1);   //开启tim15通道1的捕获（中断方式）
	HAL_TIM_IC_Start_IT(&htim15, TIM_CHANNEL_2);   //开启tim15通道2的捕获（中断方式）
	__HAL_TIM_ENABLE_IT(&htim15, TIM_IT_UPDATE);   //更新使能中断
	
	HAL_TIM_Base_Start_IT(&htim6);//开始定时器
}
