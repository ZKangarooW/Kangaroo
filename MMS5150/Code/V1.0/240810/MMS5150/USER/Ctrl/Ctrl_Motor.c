#include "Ctrl_Motor.h"

/*
*****************************************************************
 * 函数原型： void Motor_Check(float dT)
 * 功    能： 电机停止检测
*****************************************************************
*/
void Motor_Check(float dT)
{
    static float T1,T2; 
    if(Rel_Speed.L1 == 0)//设定速度并且实际速度小于10
    {  
        T1 += dT;
        if(T1 >= 2)
        {
            Speed_Val_L1.SumError=0x12000;//启动电机系数
        }
    }
    else
    {
        T1 = 0;
    }
    if(Rel_Speed.L2 == 0)//设定速度并且实际速度小于10
    {  
        T2 += dT;
        if(T2 >= 2)
        {
            Speed_Val_L2.SumError=0x12000;//启动电机系数
        }
    }
    else
    {
        T2 = 0;
    }
    #if (Integration_TYPE == 0)
		static float T3,T4,T5,T6;
		if(Param.type == 0 || Param.type == 2)//四联
		{
			if(Rel_Speed.L5 == 0)//设定速度并且实际速度小于10
			{  
				T5 += dT;
				if(T5 >= 2)
				{
					Speed_Val_L5.SumError=0x12000;//启动电机系数
				}
			}
			else
			{
				T5 = 0;
			}
			if(Rel_Speed.L6 == 0)//设定速度并且实际速度小于10
			{  
				T6 += dT;
				if(T6 >= 2)
				{
					Speed_Val_L6.SumError=0x12000;//启动电机系数
				}
			}
			else
			{
				T6 = 0;
			}
		}
		else if(Param.type == 1 || Param.type == 3)//六联
		{
			if(Rel_Speed.L3 == 0)//设定速度并且实际速度小于10
			{  
				T3 += dT;
				if(T3 >= 2)
				{
					Speed_Val_L3.SumError=0x12000;//启动电机系数
				}
			}
			else
			{
				T3 = 0;
			}
			if(Rel_Speed.L4 == 0)//设定速度并且实际速度小于10
			{  
				T4 += dT;
				if(T4 >= 2)
				{
					Speed_Val_L4.SumError=0x12000;//启动电机系数
				}
			}
			else
			{
				T4 = 0;
			}
			if(Rel_Speed.L5 == 0)//设定速度并且实际速度小于10
			{  
				T5 += dT;
				if(T5 >= 2)
				{
					Speed_Val_L5.SumError=0x12000;//启动电机系数
				}
			}
			else
			{
				T5 = 0;
			}
			if(Rel_Speed.L6 == 0)//设定速度并且实际速度小于10
			{  
				T6 += dT;
				if(T6 >= 2)
				{
					Speed_Val_L6.SumError=0x12000;//启动电机系数
				}
			}
			else
			{
				T6 = 0;
			}
		}
    #elif (Integration_TYPE == 1) 
    static float T3,T4,T5,T6,T7,T8,T9;
    if(Rel_Speed.L3 == 0)//设定速度并且实际速度小于10
    {  
        T3 += dT;
        if(T3 >= 2)
        {
            Speed_Val_L3.SumError=0x12000;//启动电机系数
        }
    }
    else
    {
        T3 = 0;
    }
    if(Rel_Speed.L4 == 0)//设定速度并且实际速度小于10
    {  
        T4 += dT;
        if(T4 >= 2)
        {
            Speed_Val_L4.SumError=0x12000;//启动电机系数
        }
    }
    else
    {
        T4 = 0;
    }
    if(Rel_Speed.L5 == 0)//设定速度并且实际速度小于10
    {  
        T5 += dT;
        if(T5 >= 2)
        {
            Speed_Val_L5.SumError=0x12000;//启动电机系数
        }
    }
    else
    {
        T5 = 0;
    }
    if(Rel_Speed.L6 == 0)//设定速度并且实际速度小于10
    {  
        T6 += dT;
        if(T6 >= 2)
        {
            Speed_Val_L6.SumError=0x12000;//启动电机系数
        }
    }
    else
    {
        T6 = 0;
    }
    if(Rel_Speed.L7 == 0)//设定速度并且实际速度小于10
    {  
        T7 += dT;
        if(T7 >= 2)
        {
            Speed_Val_L7.SumError=0x12000;//启动电机系数
        }
    }
    else
    {
        T7 = 0;
    }
    if(Rel_Speed.L8 == 0)//设定速度并且实际速度小于10
    {  
        T8 += dT;
        if(T8 >= 2)
        {
            Speed_Val_L8.SumError=0x12000;//启动电机系数
        }
    }
    else
    {
        T8 = 0;
    }
	if(Rel_Speed.L9 == 0)//设定速度并且实际速度小于10
    {  
        T9 += dT;
        if(T9 >= 2)
        {
            Speed_Val_L9.SumError=0x12000;//启动电机系数
        }
    }
    else
    {
        T9 = 0;
    }
    #endif
}

/*
*****************************************************************
 * 函数原型： void Motor_Ctrl(void)
 * 功    能： 电机控制
*****************************************************************
*/
void Motor_Ctrl(void)
{   
    if(Run_Status == 1)//启动
    {
        Motor_Check(0.05);
		#if (Integration_TYPE == 0)//四六联
        /**********Speed_L1**********/
        if(Ctrl_Speed.L1 && ((DownTime_Over.L1 == 0)||(Ctrl_Time.L1)))//速度大于0和定时器没有结束
        {
            PID_Speed(Ctrl_Speed.L1,Rel_Speed.L1,&Speed_Arg,&Speed_Val_L1);//电机PID控制
			if(Param.type == 0 || Param.type == 2)//四联
			{
				PWM_L3 = Speed_Val_L1.Out;//pid输出
			}
			else if(Param.type == 1 || Param.type == 3)//六联
			{
				PWM_L1 = Speed_Val_L1.Out;//pid输出
			}
        }
        else
        {
			if(Param.type == 0 || Param.type == 2)//四联
			{
				PWM_L3 = 0;//pwm不输出
			}
			else if(Param.type == 1 || Param.type == 3)//六联
			{
				PWM_L1 = 0;//pwm不输出
			}
        }
        /**********Speed_L2**********/
        if(Ctrl_Speed.L2 && ((DownTime_Over.L2 == 0)||(Ctrl_Time.L2)))//速度大于0和定时器没有结束
        {
            PID_Speed(Ctrl_Speed.L2,Rel_Speed.L2,&Speed_Arg,&Speed_Val_L2);//电机PID控制
			if(Param.type == 0 || Param.type == 2)//四联
			{
				PWM_L4 = Speed_Val_L2.Out;//pid输出
			}
			else if(Param.type == 1 || Param.type == 3)//六联
			{
				PWM_L2 = Speed_Val_L2.Out;//pid输出
			}
        }
        else
        {
			if(Param.type == 0 || Param.type == 2)//四联
			{
				PWM_L4 = 0;//pwm不输出
			}
			else if(Param.type == 1 || Param.type == 3)//六联
			{
				PWM_L2 = 0;//pwm不输出
			}
        }
		if(Param.type == 0 || Param.type == 2)//四联
		{
			/**********Speed_L5**********/
			if(Ctrl_Speed.L5 && ((DownTime_Over.L5 == 0)||(Ctrl_Time.L5)))//速度大于0和定时器没有结束
			{
				PID_Speed(Ctrl_Speed.L5,Rel_Speed.L5,&Speed_Arg,&Speed_Val_L5);//电机PID控制
				PWM_L5 = Speed_Val_L5.Out;//pid输出
			}
			else
			{
				PWM_L5 = 0;//pwm不输出
			}
			/**********Speed_L6**********/
			if(Ctrl_Speed.L6 && ((DownTime_Over.L6 == 0)||(Ctrl_Time.L6)))//速度大于0和定时器没有结束
			{
				PID_Speed(Ctrl_Speed.L6,Rel_Speed.L6,&Speed_Arg,&Speed_Val_L6);//电机PID控制
				PWM_L6 = Speed_Val_L6.Out;//pid输出
			}
			else
			{
				PWM_L6 = 0;//pwm不输出
			}
		}
		else if(Param.type == 1 || Param.type == 3)//六联
		{
			/**********Speed_L3**********/
			if(Ctrl_Speed.L3 && ((DownTime_Over.L3 == 0)||(Ctrl_Time.L3)))//速度大于0和定时器没有结束
			{
				PID_Speed(Ctrl_Speed.L3,Rel_Speed.L3,&Speed_Arg,&Speed_Val_L3);//电机PID控制
				PWM_L3 = Speed_Val_L3.Out;//pid输出
			}
			else
			{
				PWM_L3 = 0;//pwm不输出
			}
			/**********Speed_L4**********/
			if(Ctrl_Speed.L4 && ((DownTime_Over.L4 == 0)||(Ctrl_Time.L4)))//速度大于0和定时器没有结束
			{
				PID_Speed(Ctrl_Speed.L4,Rel_Speed.L4,&Speed_Arg,&Speed_Val_L4);//电机PID控制
				PWM_L4 = Speed_Val_L4.Out;//pid输出
			}
			else
			{
				PWM_L4 = 0;//pwm不输出
			}
			/**********Speed_L5**********/
			if(Ctrl_Speed.L5 && ((DownTime_Over.L5 == 0)||(Ctrl_Time.L5)))//速度大于0和定时器没有结束
			{
				PID_Speed(Ctrl_Speed.L5,Rel_Speed.L5,&Speed_Arg,&Speed_Val_L5);//电机PID控制
				PWM_L5 = Speed_Val_L5.Out;//pid输出
			}
			else
			{
				PWM_L5 = 0;//pwm不输出
			}
			/**********Speed_L6**********/
			if(Ctrl_Speed.L6 && ((DownTime_Over.L6 == 0)||(Ctrl_Time.L6)))//速度大于0和定时器没有结束
			{
				PID_Speed(Ctrl_Speed.L6,Rel_Speed.L6,&Speed_Arg,&Speed_Val_L6);//电机PID控制
				PWM_L6 = Speed_Val_L6.Out;//pid输出
			}
			else
			{
				PWM_L6 = 0;//pwm不输出
			}
		}
        #elif (Integration_TYPE == 1)  
		/**********Speed_L1**********/
        if(Ctrl_Speed.L1 && ((DownTime_Over.L1 == 0)||(Ctrl_Time.L1)))//速度大于0和定时器没有结束
        {
            PID_Speed(Ctrl_Speed.L1,Rel_Speed.L1,&Speed_Arg,&Speed_Val_L1);//电机PID控制
            PWM_L1 = Speed_Val_L1.Out;//pid输出
        }
        else
        {
            PWM_L1 = 0;//pwm不输出
        }
        /**********Speed_L2**********/
        if(Ctrl_Speed.L2 && ((DownTime_Over.L2 == 0)||(Ctrl_Time.L2)))//速度大于0和定时器没有结束
        {
            PID_Speed(Ctrl_Speed.L2,Rel_Speed.L2,&Speed_Arg,&Speed_Val_L2);//电机PID控制
            PWM_L2 = Speed_Val_L2.Out;//pid输出
        }
        else
        {
            PWM_L2 = 0;//pwm不输出
        }
        /**********Speed_L3**********/
        if(Ctrl_Speed.L3 && ((DownTime_Over.L3 == 0)||(Ctrl_Time.L3)))//速度大于0和定时器没有结束
        {
            PID_Speed(Ctrl_Speed.L3,Rel_Speed.L3,&Speed_Arg,&Speed_Val_L3);//电机PID控制
            PWM_L3 = Speed_Val_L3.Out;//pid输出
        }
        else
        {
            PWM_L3 = 0;//pwm不输出
        }
        /**********Speed_L4**********/
        if(Ctrl_Speed.L4 && ((DownTime_Over.L4 == 0)||(Ctrl_Time.L4)))//速度大于0和定时器没有结束
        {
            PID_Speed(Ctrl_Speed.L4,Rel_Speed.L4,&Speed_Arg,&Speed_Val_L4);//电机PID控制
            PWM_L4 = Speed_Val_L4.Out;//pid输出
        }
        else
        {
            PWM_L4 = 0;//pwm不输出
        }
        /**********Speed_L5**********/
        if(Ctrl_Speed.L5 && ((DownTime_Over.L5 == 0)||(Ctrl_Time.L5)))//速度大于0和定时器没有结束
        {
            PID_Speed(Ctrl_Speed.L5,Rel_Speed.L5,&Speed_Arg,&Speed_Val_L5);//电机PID控制
            PWM_L5 = Speed_Val_L5.Out;//pid输出
        }
        else
        {
            PWM_L5 = 0;//pwm不输出
        }
        /**********Speed_L6**********/
        if(Ctrl_Speed.L6 && ((DownTime_Over.L6 == 0)||(Ctrl_Time.L6)))//速度大于0和定时器没有结束
        {
            PID_Speed(Ctrl_Speed.L6,Rel_Speed.L6,&Speed_Arg,&Speed_Val_L6);//电机PID控制
            PWM_L6 = Speed_Val_L6.Out;//pid输出
        }
        else
        {
            PWM_L6 = 0;//pwm不输出
        }
        /**********Speed_L7**********/
        if(Ctrl_Speed.L7 && ((DownTime_Over.L7 == 0)||(Ctrl_Time.L7)))//速度大于0和定时器没有结束
        {
            PID_Speed(Ctrl_Speed.L7,Rel_Speed.L7,&Speed_Arg,&Speed_Val_L7);//电机PID控制
            PWM_L7 = Speed_Val_L7.Out;//pid输出
        }
        else
        {
            PWM_L7 = 0;//pwm不输出
        }
        /**********Speed_L8**********/
        if(Ctrl_Speed.L8 && ((DownTime_Over.L8 == 0)||(Ctrl_Time.L8)))//速度大于0和定时器没有结束
        {
            PID_Speed(Ctrl_Speed.L8,Rel_Speed.L8,&Speed_Arg,&Speed_Val_L8);//电机PID控制
            PWM_L8 = Speed_Val_L8.Out;//pid输出
        }
        else
        {
            PWM_L8 = 0;//pwm不输出
        } 
		/**********Speed_L9**********/
        if(Ctrl_Speed.L9 && ((DownTime_Over.L9 == 0)||(Ctrl_Time.L9)))//速度大于0和定时器没有结束
        {
            PID_Speed(Ctrl_Speed.L9,Rel_Speed.L9,&Speed_Arg,&Speed_Val_L9);//电机PID控制
            PWM_L9 = Speed_Val_L9.Out;//pid输出
        }
        else
        {
            PWM_L9 = 0;//pwm不输出
        } 
        #endif
    }
    else
    {    
		#if (Integration_TYPE == 0)//四六联
			if(Param.type == 0 || Param.type == 2)//四联
			{
				PWM_L3 = 0;//pwm不输出
				PWM_L4 = 0;//pwm不输出
			}
			else if(Param.type == 1 || Param.type == 3)//六联
			{
				PWM_L1 = 0;//pwm不输出
				PWM_L2 = 0;//pwm不输出
			}		
			Speed_Val_L1.SumError=0;//启动电机系数
			Speed_Val_L2.SumError=0;//启动电机系数
			if(Param.type == 0 || Param.type == 2)//四联
			{
				PWM_L5 = 0;//pwm不输出
				PWM_L6 = 0;//pwm不输出
				Speed_Val_L7.SumError=0;//启动电机系数
				Speed_Val_L8.SumError=0;//启动电机系数
			}
			else if(Param.type == 1 || Param.type == 3)//六联
			{
				PWM_L3 = 0;//pwm不输出
				PWM_L4 = 0;//pwm不输出
				PWM_L5 = 0;//pwm不输出
				PWM_L6 = 0;//pwm不输出
				Speed_Val_L3.SumError=0;//启动电机系数
				Speed_Val_L4.SumError=0;//启动电机系数
				Speed_Val_L5.SumError=0;//启动电机系数
				Speed_Val_L6.SumError=0;//启动电机系数
			}
        #elif (Integration_TYPE == 1)
			PWM_L1 = 0;//pwm不输出
			PWM_L2 = 0;//pwm不输出
			PWM_L3 = 0;//pwm不输出
			PWM_L4 = 0;//pwm不输出
			PWM_L5 = 0;//pwm不输出
			PWM_L6 = 0;//pwm不输出
			PWM_L7 = 0;//pwm不输出
			PWM_L8 = 0;//pwm不输出
			PWM_L9 = 0;//pwm不输出
			Speed_Val_L1.SumError=0;//启动电机系数
			Speed_Val_L2.SumError=0;//启动电机系数
			Speed_Val_L3.SumError=0;//启动电机系数
			Speed_Val_L4.SumError=0;//启动电机系数
			Speed_Val_L5.SumError=0;//启动电机系数
			Speed_Val_L6.SumError=0;//启动电机系数
			Speed_Val_L7.SumError=0;//启动电机系数
			Speed_Val_L8.SumError=0;//启动电机系数
			Speed_Val_L9.SumError=0;//启动电机系数
        #endif
    }      
}

/*
*****************************************************************
 * 函数原型： void Motor_Init(void)
 * 功    能： 电机初始化 
*****************************************************************
*/
void Motor_Init(void)
{
    #if (Integration_TYPE == 0) 
		if(Param.type == 0 || Param.type == 2)//四联
		{
			HAL_GPIO_WritePin(MO1_GPIO_Port, MO1_Pin, GPIO_PIN_SET);//使能电机
			HAL_GPIO_WritePin(MO2_GPIO_Port, MO2_Pin, GPIO_PIN_SET);//使能电机  
			HAL_GPIO_WritePin(MO3_GPIO_Port, MO3_Pin, GPIO_PIN_SET);//使能电机
			HAL_GPIO_WritePin(MO4_GPIO_Port, MO4_Pin, GPIO_PIN_SET);//使能电机
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);//motor PWM输出
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);//motor PWM输出
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);//motor PWM输出
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);//motor PWM输出
		}
		else if(Param.type == 1 || Param.type == 3)//六联
		{
			HAL_GPIO_WritePin(MO1_GPIO_Port, MO1_Pin, GPIO_PIN_SET);//使能电机
			HAL_GPIO_WritePin(MO2_GPIO_Port, MO2_Pin, GPIO_PIN_SET);//使能电机  
			HAL_GPIO_WritePin(MO3_GPIO_Port, MO3_Pin, GPIO_PIN_SET);//使能电机
			HAL_GPIO_WritePin(MO4_GPIO_Port, MO4_Pin, GPIO_PIN_SET);//使能电机
			HAL_GPIO_WritePin(MO5_GPIO_Port, MO5_Pin, GPIO_PIN_SET);//使能电机
			HAL_GPIO_WritePin(MO6_GPIO_Port, MO6_Pin, GPIO_PIN_SET);//使能电机
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);//motor PWM输出
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);//motor PWM输出
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);//motor PWM输出
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);//motor PWM输出
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);//motor PWM输出
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);//motor PWM输出
		}
    #elif (Integration_TYPE == 1) 
	HAL_GPIO_WritePin(MO1_GPIO_Port, MO1_Pin, GPIO_PIN_SET);//使能电机
    HAL_GPIO_WritePin(MO2_GPIO_Port, MO2_Pin, GPIO_PIN_SET);//使能电机
    HAL_GPIO_WritePin(MO3_GPIO_Port, MO3_Pin, GPIO_PIN_SET);//使能电机
    HAL_GPIO_WritePin(MO4_GPIO_Port, MO4_Pin, GPIO_PIN_SET);//使能电机   
    HAL_GPIO_WritePin(MO5_GPIO_Port, MO5_Pin, GPIO_PIN_SET);//使能电机
    HAL_GPIO_WritePin(MO6_GPIO_Port, MO6_Pin, GPIO_PIN_SET);//使能电机
    HAL_GPIO_WritePin(MO7_GPIO_Port, MO7_Pin, GPIO_PIN_SET);//使能电机
    HAL_GPIO_WritePin(MO8_GPIO_Port, MO8_Pin, GPIO_PIN_SET);//使能电机 
	HAL_GPIO_WritePin(MO9_GPIO_Port, MO9_Pin, GPIO_PIN_SET);//使能电机
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);//motor PWM输出
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2);//motor PWM输出 
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_3);//motor PWM输出
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_4);//motor PWM输出
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);//motor PWM输出
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);//motor PWM输出
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);//motor PWM输出
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);//motor PWM输出
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);//motor PWM输出
    #endif
}
