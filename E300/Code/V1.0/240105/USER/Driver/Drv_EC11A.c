#include "Drv_EC11A.h"

/**********结构体************/
_EC11A_ EC11A[2];//旋钮参数

/*
*****************************************************************
 * 函数原型：void EC11A_Init(void)
 * 功    能：EC11A初始化定时器
*****************************************************************
*/
void EC11A_Init(void)
{
	/**********EC11A_1**********/
	EC11A[0].EXTI_Pin = KEY1A_Pin;//EC11A旋钮中断引脚
	EC11A[0].EC11A_Pin = KEY1B_Pin;//EC11A旋钮输入引脚
	EC11A[0].EC11A_GPIO = KEY1B_GPIO_Port;//EC11A旋钮输入GPIO端口
	
	EC11A[0].Key_Pin = KEY1_Pin;//EC11A按键输入引脚
	EC11A[0].Key_GPIO = KEY1_GPIO_Port;//EC11A按键输入GPIO端口
	
	EC11A[0].Tim = &EC11A_Tim_1;//定时器选择
	EC11A[0].EC11A_Fast = EC11A_FastSpeed;//判断旋转速度阈值
	
	/**********EC11A_2**********/
	EC11A[1].EXTI_Pin = KEY2A_Pin;//EC11A旋钮中断引脚
	EC11A[1].EC11A_Pin = KEY2B_Pin;//EC11A旋钮输入引脚
	EC11A[1].EC11A_GPIO = KEY2B_GPIO_Port;//EC11A旋钮输入GPIO端口
	
	EC11A[1].Key_Pin = KEY2_Pin;//EC11A按键输入引脚
	EC11A[1].Key_GPIO = KEY2_GPIO_Port;//EC11A按键输入GPIO端口
	
	EC11A[1].Tim = &EC11A_Tim_2;//定时器选择
	EC11A[1].EC11A_Fast = EC11A_FastSpeed;//判断旋转速度阈值
}

/*
*****************************************************************
 * 函数原型：void Check_Knob(float dT)
 * 功    能：检测旋钮的状态-500ms
*****************************************************************
*/
void Check_Knob(float dT)
{
    if(EC11A[0].EC11A_Knob)//旋钮0旋转
        EC11A[0].EC11A_Knob -= dT;//倒计时
	
	if(EC11A[1].EC11A_Knob)//旋钮1旋转
        EC11A[1].EC11A_Knob -= dT;//倒计时
}

/*
*****************************************************************
 * 函数原型：void EC11A_Speed(float dT)
 * 功    能：EC11A旋钮速度计算
*****************************************************************
*/
void EC11A_Speed(float dT)
{
	/**********EC11A_1**********/
	EC11A[0].EC11A_Speed = EC11A[0].EC11A_Cnt*60/20;//一秒检测一次。转一圈20个反馈，一分钟的速度
	EC11A[0].EC11A_Cnt = 0;//将检测到的计数清零
	
	/**********EC11A_2**********/
	EC11A[1].EC11A_Speed = EC11A[1].EC11A_Cnt*60/20;//一秒检测一次。转一圈20个反馈，一分钟的速度
	EC11A[1].EC11A_Cnt = 0;//将检测到的计数清零
}

/*
*****************************************************************
 * 函数原型：void EC11AKey_Scan(float dT)
 * 功    能：EC11A按键扫描
*****************************************************************
*/
void EC11AKey_Scan(float dT)
{
	/**********EC11A_1**********///左旋钮
	if(HAL_GPIO_ReadPin(EC11A[0].Key_GPIO,EC11A[0].Key_Pin) == KEY_DOWN)//按下按键
	{
		if(EC11A[0].LongPress == 0)//没有长按过
		{
			EC11A[0].Key_Cnt += dT;//按下时间++
			EC11A[0].Key_Flag = 1;//按键按下标志置一
		}
	}
	if(EC11A[0].Key_Flag == 1)//按键被按下
	{
		if(HAL_GPIO_ReadPin(EC11A[0].Key_GPIO,EC11A[0].Key_Pin) == KEY_UP)//抬起按键
		{   
			if(EC11A[0].Key_Cnt > 0.1 && EC11A[0].Key_Cnt < 1.5)//小于1.5S是单击
			{
				if(!sys.Run_Status)
                {
                    sys.Run_Status = 1;//系统启动
                    Temp_Val.Integral = 200;//开始就5分之一功率加热
                    SpeedSet_Flag = TimeSet_Flag = 1;//速度设置，时间设置
                    Temp_Twinkle_Time = Time_Twinkle_Time =0;//闪烁时间清零
                    EC11A[0].EC11A_Knob = EC11A[1].EC11A_Knob = 0;//旋钮时间清零
                    Beep_Time = 0.1;//蜂鸣器响0.1S
                }
                else
                {
                    sys.Run_Status = 0;//系统关闭
                    Beep_Time = 0.1;//蜂鸣器响0.1S
                    Temp.ADDMode = 0;//加热显示模式清零
                }
			}
			EC11A[0].Key_Flag = 0;//按键事件结束，等待下一次按下
			EC11A[0].LongPress = 0;//长按标志清零
			EC11A[0].Key_Cnt = 0;//按钮计数清零
		}
		if(EC11A[0].Key_Cnt > 1.5 && EC11A[0].Key_Cnt < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(EC11A[0].LongPress == 0)//如果没有一直一直长按着
			{
				
				EC11A[0].LongPress = 1;//长按标志置一
			}
		}
	}
	
	/**********EC11A_2**********///右边旋钮
	if(HAL_GPIO_ReadPin(EC11A[1].Key_GPIO,EC11A[1].Key_Pin) == KEY_DOWN)//按下按键
	{
		if(EC11A[1].LongPress == 0)//没有长按过
		{
			EC11A[1].Key_Cnt += dT;//按下时间++
			EC11A[1].Key_Flag = 1;//按键按下标志置一
		}
	}
	if(EC11A[1].Key_Flag == 1)//按键被按下
	{
		if(HAL_GPIO_ReadPin(EC11A[1].Key_GPIO,EC11A[1].Key_Pin) == KEY_UP)//抬起按键
		{   
			if(EC11A[1].Key_Cnt > 0.1 && EC11A[1].Key_Cnt < 1.5)//小于1.5S是单击
			{
                if(!sys.Time_Status && sys.Run_Status && Beep_Flash == 0)
                {
                    sys.Time_Status = 1;//系统启动
                    Beep_Time = 0.1;//蜂鸣器响0.1S
                }
                else
                {
                    sys.Time_Status = 0;//系统关闭
                    Beep_Flash = 0;//蜂鸣器报警清零
                    TimeSet_Flag = 1;//时间设定
                    Beep_Time = 0.1;//蜂鸣器响0.1S
                }
			}
			EC11A[1].Key_Flag = 0;//按键事件结束，等待下一次按下
			EC11A[1].LongPress = 0;//长按标志清零
			EC11A[1].Key_Cnt = 0;//按钮计数清零
		}
		if(EC11A[1].Key_Cnt > 1.5 && EC11A[1].Key_Cnt < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(EC11A[1].LongPress == 0)//如果没有一直一直长按着
			{

				EC11A[1].LongPress = 1;//长按标志置一
			}
		}
	}
}

/*
*****************************************************************
 * 函数原型：void EC11A_EXTI_Interrupt(uint16_t GPIO_Pin)
 * 功    能：EC11A旋钮中断函数
 * 输    入：GPIO_Pin:出发的引脚
 * 参    数：uint16_t GPIO_Pin
*****************************************************************
*/
void EC11A_EXTI_Interrupt(uint16_t GPIO_Pin)
{
	/**********EC11A_1**********/
	if(GPIO_Pin == EC11A[0].EXTI_Pin)//A上升沿触发外部中断
	{
		HAL_TIM_Base_Start_IT(EC11A[0].Tim);//开始定时器
		while(EC11A[0].TIM_Cnt <= 20)//定时器一个周期1ms，计时2ms内看看A有没有电跳变
		{
			if(GPIO_Pin == EC11A[0].EXTI_Pin)//在2ms内，检测到电平变化
			{ 
				HAL_TIM_Base_Stop_IT(EC11A[0].Tim);//停止定时器
				EC11A[0].TIM_Cnt = 0;//清除TIM计数
				EC11A[0].EC11A_Cnt++;//旋钮计数
				EC11A[0].EC11A_Knob = 2.0f;//在旋转旋钮时
                if(Beep_Flash)
                {
                    Beep_Flash = 0;//蜂鸣器报警清零
                    TimeSet_Flag = 1;//时间设定
                }
				if(HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO,EC11A[0].EC11A_Pin) == 0)//加
				{
                    if(EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast)//如果慢慢旋转
                    {
                        Temp.Set++;
                    }
                    else
                    {
                        Temp.Set += 50;
                    }
					if(Temp.Set > Temp_MAX)
                        Temp.Set = Temp_MAX;
                    Temp_Twinkle_Time = 2.0f;//温度闪烁2S
					break;
				}
				else if(HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO,EC11A[0].EC11A_Pin) == 1)//减
				{
                    if(EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast)//如果慢慢旋转
                    {
                        Temp.Set--;
                    }
                    else
                    {
                        Temp.Set -= 50;
                    }
					if(Temp.Set < 0)
                        Temp.Set = 0;
                    Temp_Twinkle_Time = 2.0f;//温度闪烁2S
					break;
				}
				break;
			}
		}
		HAL_TIM_Base_Stop_IT(EC11A[0].Tim);//停止定时器
		EC11A[0].TIM_Cnt = 0;//清除TIM计数
	}
	
	/**********EC11A_2**********/
	if(GPIO_Pin == EC11A[1].EXTI_Pin)//A上升沿触发外部中断
	{
		HAL_TIM_Base_Start_IT(EC11A[1].Tim);//开始定时器
		while(EC11A[1].TIM_Cnt <= 2)//定时器一个周期1ms，计时2ms内看看A有没有电跳变
		{
			if(GPIO_Pin == EC11A[1].EXTI_Pin)//在2ms内，检测到电平变化
			{ 
				HAL_TIM_Base_Stop_IT(EC11A[1].Tim);//停止定时器
				EC11A[1].TIM_Cnt = 0;//清除TIM计数
				EC11A[1].EC11A_Cnt++;//旋钮计数
				EC11A[1].EC11A_Knob = 2.0f;//在旋转旋钮时
                if(Beep_Flash)
                {
                    Beep_Flash = 0;//蜂鸣器报警清零
                    TimeSet_Flag = 1;//时间设定
                }
				if(HAL_GPIO_ReadPin(EC11A[1].EC11A_GPIO,EC11A[1].EC11A_Pin) == 0)//加
				{
                    if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//如果慢慢旋转
                    {
                        Time.Set += 60;
                    }
                    else
                    {
                        Time.Set += 600;
                    }
                    if(Time.Set > Time_MAX)
                        Time.Set = Time_MAX;
                    Time_Twinkle_Time = 2.0f;//时间闪烁2S
					break;
				}
				else if(HAL_GPIO_ReadPin(EC11A[1].EC11A_GPIO,EC11A[1].EC11A_Pin) == 1)//减
				{
                    if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//如果慢慢旋转
                    {
                        Time.Set -= 60;
                    }
                    else
                    {
                        Time.Set -= 600;
                    }
                    if(Time.Set < 60)
                        Time.Set = 0;
                    Time_Twinkle_Time = 2.0f;//时间闪烁2S
					break;
				}
				break;
			}
		}
		HAL_TIM_Base_Stop_IT(EC11A[1].Tim);//停止定时器
		EC11A[1].TIM_Cnt = 0;//清除TIM计数
	}
}

/*
*****************************************************************
 * 函数原型：void EC11A_TIM_Interrupt(TIM_HandleTypeDef *htim)
 * 功    能：EC11A旋钮定时计数中断函数
 * 输    入：htim：定时器
 * 参    数：TIM_HandleTypeDef *htim
*****************************************************************
*/
void EC11A_TIM_Interrupt(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == EC11A_Tim_1.Instance) 
	{
		EC11A[0].TIM_Cnt++;
	}
	
	if(htim->Instance == EC11A_Tim_2.Instance) 
	{
		EC11A[1].TIM_Cnt++;
	}
}
