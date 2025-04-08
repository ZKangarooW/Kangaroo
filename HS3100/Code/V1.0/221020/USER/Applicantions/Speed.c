#include "Speed.h"

/**********局部变量声明******/
uint32_t P_Status;//捕获周期计数状态  1开启 0关闭
uint16_t TIM1CH3_CAPTURE_STA=0;//捕获溢出的周期数	    				
uint32_t TIM1CH3_CAPTURE_VAL;//捕获未溢出的计数值
uint8_t CAPTURE_First=0;//捕获第一个高电平
uint8_t CAPTURE_Status=0;//捕获状态
uint16_t Speed_Flag;//速度调0标志位

/*
*****************************************************************
 * 函数原型：void Encoder_Init(void)
 * 功    能：编码器初始化 
*****************************************************************
*/
void Encoder_Init(void)
{   
    HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_3);//motor输入捕获
	HAL_TIM_Base_Start_IT(&htim1);//开启定时器1的中断
}

/*
*****************************************************************
 * 函数原型：void Check_Speed(float dT)
 * 功    能：检测速度是否停止
*****************************************************************
*/
void Check_Speed(float dT)
{
	if(Speed_Flag)
		Speed_Flag -= dT;
	if(Speed_Flag==0)
		Speed.Rel_Speed = 0;
}

/*
*****************************************************************
 * 函数原型：void Check_Status(void)
 * 功    能：检测捕获状态
*****************************************************************
*/
void Check_Status(void)
{
	if(CAPTURE_Status)//捕获结束
	{	
		__HAL_TIM_ENABLE(&htim1);//重新开始捕获
		CAPTURE_Status=0;//开始捕获
		TIM1CH3_CAPTURE_STA=0;//溢出时间清零
	}
}

/*
*****************************************************************
 * 函数原型：void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 * 功    能：定时器中断
*****************************************************************
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM1)
	{
		if(P_Status)//捕获周期计数
		{
			TIM1CH3_CAPTURE_STA++;//溢出加1
		}
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
	if(CAPTURE_Status==0)
	{
		 Speed_Flag=2;//每次进入都赋值2，如果2S后不进入表示速度为0
		if(CAPTURE_First)		 		
		{	  			
			CAPTURE_Status=1;//停止捕获计时
			CAPTURE_First=0;//清除捕获第一个上升沿标志
			TIM1CH3_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_3);//获取当前捕获计数值
			long long temp=0;
			temp=TIM1CH3_CAPTURE_STA;//溢出的次数（用于计算进入多少个周期）
			temp*=50;//一个周期溢出的时间（us）计算=定时器周期（1/（48000000/6）*400）=0.00005S=50us
			temp+=TIM1CH3_CAPTURE_VAL;//一个周期所需的us数（用溢出的时间加上没有溢出的时间）得出一个周期用了多少us
			temp=60000000/temp/2;//一分钟有60000000us，一分钟内有多少个脉冲（周期）。2是一圈有几个脉冲得出一分钟转了多少圈
			Speed.Rel_Speed = temp;
			P_Status=0;//捕获周期计数关闭
			__HAL_TIM_SET_COUNTER(&htim1,0);//定时器寄存器清零
			__HAL_TIM_DISABLE(&htim1);//不进入定时器中断（不溢出计数）   
		}
		else  								
		{
			TIM1CH3_CAPTURE_STA=0;//清除周期计数			
			TIM1CH3_CAPTURE_VAL=0;//清除捕获寄存器
			CAPTURE_First=1;//已捕获第一个上升沿   
			CAPTURE_Status=0;//捕获计时
			P_Status=1;//捕获周期计数开始
		}		    
	}			
}
