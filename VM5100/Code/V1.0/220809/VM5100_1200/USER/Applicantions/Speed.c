#include "Speed.h"

/**********局部变量声明******/
uint32_t P_Status;//捕获周期计数状态  1开启 0关闭
uint16_t TIM1CH1_CAPTURE_STA=0;//捕获周期数	    				
uint32_t TIM1CH1_CAPTURE_VAL;//捕获计数值
uint8_t CAPTURE_First=0;//捕获第一个高电平
uint8_t CAPTURE_Status=0;//捕获状态
uint16_t Speed_Flag;//速度调0标志位

/*
*****************************************************************
 * 函数原型： void Encoder_Init(void)
 * 功    能： 编码器初始化 
*****************************************************************
*/
void Encoder_Init(void)
{   
    HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_3);//motor输入捕获
	HAL_TIM_Base_Start_IT(&htim1); 
}

/*
*****************************************************************
 * 函数原型： void Check_Speed(void)
 * 功    能： 检测速度是否停止
*****************************************************************
*/
void Check_Speed(void)
{
	if(Speed_Flag)
		Speed_Flag--;
	if(Speed_Flag==0)
		Rel_Speed=0;
}

/*
*****************************************************************
 * 函数原型： void Check_Status(void)
 * 功    能： 检测状态
*****************************************************************
*/
void Check_Status(void)
{
	if(CAPTURE_Status)
	{	
		__HAL_TIM_ENABLE(&htim1);
		CAPTURE_Status=0;
		TIM1CH1_CAPTURE_STA=0; 
	}
}

/*
*****************************************************************
 * 函数原型： void Check_Speed(void)
 * 功    能： 检测速度是否停止
*****************************************************************
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM1)
	{
		if(sys.Run_Status == 1)
		{
			if(P_Status)
			{
				TIM1CH1_CAPTURE_STA++;
			}
		}
	}	
}

/*
*****************************************************************
 * 函数原型： void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
 * 功    能： 输入捕获回调函数
*****************************************************************
*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(sys.Run_Status == 1)
	{
		if(CAPTURE_Status==0)
		{
			 Speed_Flag=2;
			if(CAPTURE_First)		 		
			{	  			
				CAPTURE_Status=1;//停止捕获计时
				CAPTURE_First=0;//清除捕获第一个上升沿标志
				TIM1CH1_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_3);//获取当前捕获计数值
				long long temp=0;
				temp=TIM1CH1_CAPTURE_STA;  
				temp*=100;//一个周期100us	 	    
				temp+=TIM1CH1_CAPTURE_VAL;//一个周期所需的us数   
				temp=60000000/temp;//rpm
				Rel_Speed=temp*10/25;
				P_Status=0;
				__HAL_TIM_SET_COUNTER(&htim1,0);
				__HAL_TIM_DISABLE(&htim1);      
			}
			else  								
			{
				TIM1CH1_CAPTURE_STA=0;//清除周期计数			
				TIM1CH1_CAPTURE_VAL=0;//清楚捕获寄存器
				CAPTURE_First=1;//已捕获第一个上升沿   
				CAPTURE_Status=0;//捕获计时
				P_Status=1;//捕获周期计数
			}		    
		}
	}
	else
	{
		TIM1CH1_CAPTURE_VAL = 0;
		TIM1CH1_CAPTURE_STA = 0;
	}
}
