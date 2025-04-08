#include "Drv_EC11A.h"

/**********结构体************/
_EC11A_ EC11A[1]; // 旋钮参数

/**
 * @brief EC11A初始化定时器
 *
 */
void EC11A_Init(void)
{
	EC11A[0].EXTI_Pin = EC1A_Pin;		  // EC11A旋钮中断引脚
	EC11A[0].EC11A_Pin = EC1B_Pin;		  // EC11A旋钮输入引脚
	EC11A[0].EC11A_GPIO = EC1B_GPIO_Port; // EC11A旋钮输入GPIO端口

	EC11A[0].Key_Pin = KEY1_Pin;		// EC11A按键输入引脚
	EC11A[0].Key_GPIO = KEY1_GPIO_Port; // EC11A按键输入GPIO端口

	EC11A[0].Tim = &EC11A_Tim_1;		   // 定时器选择
	EC11A[0].EC11A_Fast = EC11A_FastSpeed; // 判断旋转速度阈值
}

/**
 * @brief EC11A旋钮速度计算
 *
 * @param dT 任务周期
 */
void EC11A_Speed(float dT)
{
	EC11A[0].EC11A_Speed = EC11A[0].EC11A_Cnt * 60 / 20; // 一秒检测一次。转一圈20个反馈，一分钟的速度
	EC11A[0].EC11A_Cnt = 0;								 // 将检测到的计数清零
}

/**
 * @brief 检测按键按下状态-500ms
 *
 * @param dT 任务周期
 */
void Check_Press(float dT)
{
	if(sys.Run_Status == 0)
	{
		if(EC11A[0].EC11A_Knob)//旋钮被转动
			EC11A[0].EC11A_Knob-= 0.5; // 倒计时
	}
	else
	{
		if(EC11A[0].EC11A_Knob)
		{
			EC11A[0].EC11A_Knob-= 0.5;//1S倒计时
			if(EC11A[0].EC11A_Knob <= 0)
			{
				Ctrl_Speed = Set_Speed;
				Speed_ADDMode = 0;		
				Beep_Time = 0.1;//蜂鸣器响0.1S
			}
		}
	}
}

/**
 * @brief EC11A按键扫描
 *
 * @param dT 任务周期
 */
void EC11AKey_Scan(float dT)
{
	if (HAL_GPIO_ReadPin(EC11A[0].Key_GPIO, EC11A[0].Key_Pin) == EC11A_DOWN) // 按下按键
	{
		if (EC11A[0].LongPress == 0) // 没有长按过
		{
			EC11A[0].Key_Cnt += dT; // 按下时间++
			EC11A[0].Key_Flag = 1;	// 按键按下标志置一
		}
	}
	if (EC11A[0].Key_Flag == 1) // 按键被按下
	{
		if (HAL_GPIO_ReadPin(EC11A[0].Key_GPIO, EC11A[0].Key_Pin) == EC11A_UP) // 抬起按键
		{
			if (EC11A[0].Key_Cnt > 0.1f && EC11A[0].Key_Cnt < 1.5f) // 小于1.5S是单击
			{
				if(sys.Run_Status == 0)
                {
                    sys.SetMode_Option++;//设置模式++
                    if(sys.SetMode_Option == 3)
                    {
                        sys.SetMode_Option = 0;
                    }
                }
                else//启动下单击按键，直接停止
                {
                    sys.Motor_Stop = 1;//关闭运行
					Speed_ADDMode = 2;//进入减速模式下
                }
                Beep_Time = 0.1;//蜂鸣器响0.1S
                Twinkle_Time = 6000;//闪烁显示6S
			}
			EC11A[0].Key_Flag = 0;	// 按键事件结束，等待下一次按下
			EC11A[0].LongPress = 0; // 长按标志清零
			EC11A[0].Key_Cnt = 0;	// 按钮计数清零
		}
		if (EC11A[0].Key_Cnt > 1.5f && EC11A[0].Key_Cnt < 3.0f) // 按键时间大于1.5S小于3S表示长按
		{
			if (EC11A[0].LongPress == 0) // 如果没有一直一直长按着
			{
				if(sys.Run_Status == 0)
				{
					sys.Run_Status = 1;
					sys.SetMode_Option = 0;
					Speed_ADDMode = 0;
					Speed_Val.SumError=0x2422;//启动电机系数
					Twinkle_Time = 0;
					EC11A[0].EC11A_Knob = 0;
					Speed = 0;
				} 
				else
				{
					sys.Motor_Stop = 1;//检测电机
					Speed_ADDMode = 2;//进入减速模式下
				}   
				Beep_Time = 0.1;//蜂鸣器响0.1S
				EC11A[0].LongPress = 1; // 长按标志置一
			}
		}
	}
}

/**
 * @brief 外部中断
 *
 * @param GPIO_Pin
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	UNUSED(GPIO_Pin);

	if (GPIO_Pin == EC11A[0].EXTI_Pin) // A上升沿触发外部中断
	{
		HAL_TIM_Base_Start_IT(EC11A[0].Tim); // 开始定时器
		while (EC11A[0].TIM_Cnt <= 2)		 // 定时器一个周期1ms，计时2ms内看看A有没有电跳变
		{
			if (GPIO_Pin == EC11A[0].EXTI_Pin) // 在2ms内，检测到电平变化
			{
				HAL_TIM_Base_Stop_IT(EC11A[0].Tim);									// 停止定时器
				EC11A[0].TIM_Cnt = 0;												// 清除TIM计数
				EC11A[0].EC11A_Cnt++;												// 旋钮计数
				if (HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO, EC11A[0].EC11A_Pin) == 0) // 加
				{
					if(sys.Run_Status == 1 && sys.Motor_Stop == 0)
					{
						Speed = Rel_Speed/Tooth_Ratio; 
						if (EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast) // 如果慢慢旋转
						{
							Set_Speed += 10;
						}
						else
						{
							Set_Speed += 30;
						}
						if(Set_Speed >= MAX_Speed)
							Set_Speed = MAX_Speed;
						EC11A[0].EC11A_Knob = 2;//检测是不是在旋动旋钮
					}
					if(sys.SetMode_Option == 1)
					{
						if (EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast) // 如果慢慢旋转
						{
							Set_Speed += 10;
						}
						else
						{
							Set_Speed += 30;
						}
						if(Set_Speed >= MAX_Speed)
							Set_Speed = MAX_Speed;
						Ctrl_Speed = Set_Speed;
						EC11A[0].EC11A_Knob = 1;//检测是不是在旋动旋钮
					}
					if(sys.SetMode_Option == 2)
					{
						if (EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast) // 如果慢慢旋转
						{
							Set_Time += 60;
						}
						else
						{
							Set_Time += 300;
						}
						Time_State = 0;//不显示“----”
						if(Set_Time >= 86400)
							Set_Time = 86400;
						Time = Set_Time;
						Ctrl_Time = Set_Time;
						EC11A[0].EC11A_Knob = 1;//检测是不是在旋动旋钮
						
					}
					Twinkle_Time = 6000;//闪烁显示6S  
					break;
				}
				else if (HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO, EC11A[0].EC11A_Pin) == 1) // 减
				{
					if(sys.Run_Status == 1 && sys.Motor_Stop == 0)
					{
						Speed = Rel_Speed/Tooth_Ratio; 
						if (EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast) // 如果慢慢旋转
						{
							Set_Speed -= 10;
						}
						else
						{
							Set_Speed -= 30;
						}
						if(Set_Speed <= MIN_Speed)
							Set_Speed = MIN_Speed;
						EC11A[0].EC11A_Knob = 2;//检测是不是在旋动旋钮
					}
					if(sys.SetMode_Option == 1)
					{
						if (EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast) // 如果慢慢旋转
						{
							Set_Speed -= 10;
						}
						else
						{
							Set_Speed -= 30;
						}
						if(Set_Speed <= MIN_Speed)
							Set_Speed = MIN_Speed;
						Ctrl_Speed = Set_Speed;
						EC11A[0].EC11A_Knob = 1;//检测是不是在旋动旋钮
					}
					if(sys.SetMode_Option == 2)
					{
						if (EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast) // 如果慢慢旋转
						{
							Set_Time -= 60;
						}
						else
						{
							Set_Time -= 300;
						}
						if(Set_Time <= 0)
						{
							Time_State = 1;//显示“----”
							Set_Time = 0;
						}
						Time = Set_Time;
						EC11A[0].EC11A_Knob = 1;//检测是不是在旋动旋钮
						
					}
					Twinkle_Time = 6000;//闪烁显示6S 
					break;
				}
				break;
			}
		}
		HAL_TIM_Base_Stop_IT(EC11A[0].Tim); // 停止定时器
		EC11A[0].TIM_Cnt = 0;				// 清除TIM计数
	}
}

/**
 * @brief 定时器计数中断
 *
 * @param htim
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == EC11A_Tim_1.Instance)
	{
		EC11A[0].TIM_Cnt++;
	}
}
