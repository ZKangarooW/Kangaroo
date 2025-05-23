#include "Drv_EC11A.h"
#if (Key_Type == 1)
/**********结构体************/
_EC11A_ EC11A[2];//旋钮参数

/**********全局变量声明******/
float Key_Status;//按键按下标志

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
 * 函数原型：void Check_Press(float dT)
 * 功    能：检测按键按下状态-500ms
*****************************************************************
*/
void Check_Press(float dT)
{
    if(Key_Status)//按键按下
        Key_Status -= dT;//倒计时
}

/*
*****************************************************************
 * 函数原型：void EC11AKey_Scan(float dT)
 * 功    能：EC11A按键扫描
*****************************************************************
*/
void EC11AKey_Scan(float dT)
{
	/**********EC11A_1**********/
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
				if(sys.Run_Status != 1 && (Speed.Set || Temp.Set))//系统没启动的话
				{
					sys.Run_Status = 1;//启动系统
					Speed_Val.Integral = 43;//电器起步
					sys.SetMode_Option = 0;//设定模式设置为0
					Temp_Val.Integral = 0;//加热的积分清零
					Temp.Old = Temp.Rel;
				}
				else//系统启动的话
				{
					Speed.ADDMode = 1;//进入减速模式
					Speed.Ctrl = 0;//将控制速度设置为0
				}
				Beep_Time = 0.1;//蜂鸣器响0.1S
				Twinkle_Time = 0;//闪烁时间6S
				sys.SetMode_Option = 0;
			}
			EC11A[0].Key_Flag = 0;//按键事件结束，等待下一次按下
			EC11A[0].LongPress = 0;//长按标志清零
			EC11A[0].Key_Cnt = 0;//按钮计数清零
		}
		if(EC11A[0].Key_Cnt > 1.5 && EC11A[0].Key_Cnt < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(EC11A[0].LongPress == 0)//如果没有一直一直长按着
			{
				Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
				EC11A[0].LongPress = 1;//长按标志置一
			}
		}
	}
	
	/**********EC11A_2**********/
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
				if(sys.Run_Status != 1 && (Speed.Set || Temp.Set))//系统没启动的话
				{
					sys.Run_Status = 1;//启动系统
					Speed_Val.Integral = 43;//电器起步
					sys.SetMode_Option = 0;//设定模式设置为0
					Temp_Val.Integral = 0;//加热的积分清零
					Temp.Old = Temp.Rel;
				}
				else//系统启动的话
				{
					Speed.ADDMode = 1;//进入减速模式
					Speed.Ctrl = 0;//将控制速度设置为0
				}
				Beep_Time = 0.1;//蜂鸣器响0.1S
				Twinkle_Time = 0;//闪烁时间6S
				sys.SetMode_Option = 0;
			}
			EC11A[1].Key_Flag = 0;//按键事件结束，等待下一次按下
			EC11A[1].LongPress = 0;//长按标志清零
			EC11A[1].Key_Cnt = 0;//按钮计数清零
		}
		if(EC11A[1].Key_Cnt > 1.5 && EC11A[1].Key_Cnt < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(EC11A[1].LongPress == 0)//如果没有一直一直长按着
			{
				Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
				EC11A[1].LongPress = 1;//长按标志置一
			}
		}
	}
}

/*
*****************************************************************
 * 函数原型：void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
 * 功    能：外部中断
*****************************************************************
*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	UNUSED(GPIO_Pin);
	
	/**********EC11A_1**********/
	if(GPIO_Pin == EC11A[0].EXTI_Pin)//A上升沿触发外部中断
	{
		HAL_TIM_Base_Start_IT(EC11A[0].Tim);//开始定时器
		while(EC11A[0].TIM_Cnt <= 2)//定时器一个周期1ms，计时2ms内看看A有没有电跳变
		{
			if(GPIO_Pin == EC11A[0].EXTI_Pin)//在2ms内，检测到电平变化
			{ 
				HAL_TIM_Base_Stop_IT(EC11A[0].Tim);//停止定时器
				EC11A[0].TIM_Cnt = 0;//清除TIM计数
				EC11A[0].EC11A_Cnt++;//旋钮计数
				EC11A[0].EC11A_Knob = 2;//在旋转旋钮时
                if(sys.Run_Status == 1)
					return;
                sys.SetMode_Option = 1;//设置温度
				if(HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO,EC11A[0].EC11A_Pin) == 0)//加
				{
					if(sys.SetMode_Option == 1)
					{
						if(EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast)//如果慢慢旋转
							Temp.Set += 10;
						else
							Temp.Set += 30;
						if(Temp.Set > Temp_MAX)
							Temp.Set = Temp_MAX;
						Key_Status = 1;//设置时2S不闪烁
						Twinkle_Time = 2;//闪烁时间6S
					}
					break;
				}
				else if(HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO,EC11A[0].EC11A_Pin) == 1)//减
				{
					if(sys.SetMode_Option == 1)
					{
						if(EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast)//如果慢慢旋转
							Temp.Set -= 10;
						else
							Temp.Set -= 30;
						if(Temp.Set <= 0)
							Temp.Set = 0;
						Key_Status = 1;//设置时2S不闪烁
						Twinkle_Time = 2;//闪烁时间2S
					}
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
				EC11A[1].EC11A_Knob = 2;//在旋转旋钮时
				if(sys.Run_Status == 1)
					return;
				sys.SetMode_Option = 2;//设置速度
				if(HAL_GPIO_ReadPin(EC11A[1].EC11A_GPIO,EC11A[1].EC11A_Pin) == 0)//加
				{
					/*加*/
					if(sys.SetMode_Option == 2)
					{
						if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//如果慢慢旋转
						{
							Speed.Set += 10;
							if(Speed.Set == 10)//从零转开始最低为50转，判断是10后
								Speed.Set = 200;//设定转速为200开始
						}
						else
						{
							Speed.Set += 30;
							if(Speed.Set == 30)//从零转开始最低为50转，判断是10后
								Speed.Set = 200;//设定转速为200开始
						}
						if(Speed.Set > Speed_MAX)
							Speed.Set = Speed_MAX;
						Key_Status = 1;//设置时2S不闪烁
						Twinkle_Time = 2;//闪烁时间6S
					}
					break;
				}
				else if(HAL_GPIO_ReadPin(EC11A[1].EC11A_GPIO,EC11A[1].EC11A_Pin) == 1)//减
				{
					/*减*/
					if(sys.SetMode_Option == 2)
					{
						if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//如果慢慢旋转
						{
							Speed.Set -= 10;
						}
						else
						{
							Speed.Set -= 30;
						}
						if(Speed.Set < 200)
							Speed.Set = 0;
						Key_Status = 1;//设置时2S不闪烁
						Twinkle_Time = 2;//闪烁时间6S
					}
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
 * 函数原型：void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 * 功    能：定时器计数中断
*****************************************************************
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
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
#endif
