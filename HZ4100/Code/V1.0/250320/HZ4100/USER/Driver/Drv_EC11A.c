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
	EC11A[0].EC11A_Cnt = 0;// 将检测到的计数清零
}

/**
 * @brief 检测按键按下状态-500ms
 *
 * @param dT 任务周期
 */
void Check_Press(float dT)
{
	if (EC11A[0].EC11A_Knob)	   // 旋钮0旋转
		EC11A[0].EC11A_Knob -= dT; // 倒计时
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
		if (Shake_Alarm)
			return;
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
				if (Lock_Switch)
				{
					Beep_Flash = 2;
                    Lock_Alarm = 2;
				}
				else
				{
					if (sys.Run_Status == 0)
					{
                        sys.SetMode_Option++; // 设置模式++
                        if(sys.SetMode_Option == 1 && Twinkle_Time > 0)
                            sys.SetMode_Option = 2;
                        if (sys.SetMode_Option > 3)
                        {
                            sys.SetMode_Option = 1;
                        }
                        Twinkle_Time = 2.0f;
					}
					else // 启动下单击按键，直接停止
					{
						sys.Run_Status = 0;
                        Speed.Status = 0;
                        Speed.CW = 1;
						sys.SetMode_Option = 0;
						Speed.ADDMode = 2;
						SetOK_Flag = 1;
					}
					EC11A[0].EC11A_Knob = 0;
					Beep_Time = 0.1f; // 蜂鸣器响0.1S
				}
			}
			EC11A[0].Key_Flag = 0;	// 按键事件结束，等待下一次按下
			EC11A[0].LongPress = 0; // 长按标志清零
			EC11A[0].Key_Cnt = 0;	// 按钮计数清零
		}
		if (EC11A[0].Key_Cnt > 1.5f && EC11A[0].Key_Cnt < 3.0f) // 按键时间大于1.5S小于3S表示长按
		{
			if (EC11A[0].LongPress == 0) // 如果没有一直一直长按着
			{
                if(!sys.Run_Status)
                {
                    if (Lock_Switch)
                    {
                        Beep_Flash = 2;
                        Lock_Alarm = 2;
                    }
                    else
                    {
                        sys.Run_Status = 1;
                        Speed.Status = 1;
                        Speed_Val.Integral = 20; // 28pwm启动
                        Speed.CW = 1;
                        Speed.ADDMode = 0;
                        sys.SetMode_Option = 0;
                        SetOK_Flag = 1;
                        EC11A[0].EC11A_Knob = 0; // 在旋转旋钮时
                        Twinkle_Time = 0;
                        Beep_Time = 0.1f; // 蜂鸣器响0.1S
                        EC11A[0].LongPress = 1; // 长按标志置一
                    }
                }
                else
                {
                    Beep_Flash = 2;
                }
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
		if (Shake_Alarm)
			return;
        
        if (GPIO_Pin == EC11A[0].EXTI_Pin) // 在2ms内，检测到电平变化
        {
            EC11A[0].EC11A_Cnt++;												// 旋钮计数
            EC11A[0].EC11A_Knob = 2;											// 在旋转旋钮时
            if (HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO, EC11A[0].EC11A_Pin) == 0) // 加
            {
                if (Lock_Switch)
                {
                        Beep_Flash = 2;
                    Lock_Alarm = 2;
                }
                else if (sys.SetMode_Option == 0)
                {
                    if (EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast) // 如果慢慢旋转
                    {
                        Speed.Set += 500;
                    }
                    else
                    {
                        Speed.Set += 1000;
                    }
                    if (Speed.Set > Speed_MAX)
                        Speed.Set = Speed_MAX;
                        Twinkle_Time = 2.0f; // 闪烁时间2S
                }
                else if (sys.SetMode_Option == 1)
                {
                    if (EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast) // 如果慢慢旋转
                    {
                        Speed.Set += 500;
                    }
                    else
                    {
                        Speed.Set += 1000;
                    }
                    if (Speed.Set > Speed_MAX)
                        Speed.Set = Speed_MAX;
                        Twinkle_Time = 2.0f; // 闪烁时间2S
                }
                else if (sys.SetMode_Option == 2)
                {
                    if (EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast) // 如果慢慢旋转
                    {
                        Temp.Set += 10;
                    }
                    else
                    {
                        Temp.Set += 40;
                    }
                    if (Temp.Set > Temp_MAX)
                        Temp.Set = Temp_MAX;
                    Twinkle_Time = 2.0f; // 闪烁时间6S
                }
                else if (sys.SetMode_Option == 3)
                {
                    if (EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast) // 如果慢慢旋转
                    {
                        if (Time.Set < 3600)
                            Time.Set += 5;
                        else
                        {
                            if (Time.Set % 60)
                                Time.Set = 3600;
                            else
                                Time.Set += 60;
                        }
                    }
                    else
                    {
                        if (Time.Set < 3600)
                            Time.Set += 60;
                        else
                        {
                            if (Time.Set % 60)
                                Time.Set = 3600;
                            else
                                Time.Set += 600;
                        }
                    }
                    if (Time.Set > Time_MAX)
                        Time.Set = Time_MAX;
                    Twinkle_Time = 2.0f; // 闪烁时间6S
                }
            }
            else if (HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO, EC11A[0].EC11A_Pin) == 1) // 减
            {
                if (Lock_Switch)
                {
                        Beep_Flash = 2;
                    Lock_Alarm = 2;
                }
                else if (sys.SetMode_Option == 0)
                {
                    if (EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast) // 如果慢慢旋转
                    {
                        Speed.Set -= 500;
                    }
                    else
                    {
                        Speed.Set -= 1000;
                    }
                    if (Speed.Set < Speed_MIN)
                        Speed.Set = Speed_MIN;
                    Twinkle_Time = 2.0f; // 闪烁时间2S
                }
                else if (sys.SetMode_Option == 1)
                {
                    if (EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast) // 如果慢慢旋转
                    {
                        Speed.Set -= 500;
                    }
                    else
                    {
                        Speed.Set -= 1000;
                    }
                    if (Speed.Set < Speed_MIN)
                        Speed.Set = Speed_MIN;
                    Twinkle_Time = 2.0f; // 闪烁时间2S
                }
                else if (sys.SetMode_Option == 2)
                {
                    if (EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast) // 如果慢慢旋转
                    {
                        Temp.Set -= 10;
                    }
                    else
                    {
                        Temp.Set -= 40;
                    }
                    if (Temp.Set < (Temp.Rel + 50)) // 设定安全温度大于实际安全温度+5度时
                        Temp.Set = Temp.Rel + 50;	// 设定安全温度等于实际安全温度+5度
                    Twinkle_Time = 2.0f;			// 闪烁时间2S
                }
                else if (sys.SetMode_Option == 3)
                {
                    if (EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast) // 如果慢慢旋转
                    {
                        if (Time.Set <= 3600)
                            Time.Set -= 5;
                        else
                        {
                            if (Time.Set % 60)
                                Time.Set = 3600;
                            else
                                Time.Set -= 60;
                        }
                    }
                    else
                    {
                        if (Time.Set <= 3600)
                            Time.Set -= 60;
                        else
                        {
                            if (Time.Set % 60)
                                Time.Set = 3600;
                            else
                                Time.Set -= 600;
                        }
                    }
                    if (Time.Set <= 0)
                        Time.Set = 0;
                    Twinkle_Time = 2.0f; // 闪烁时间2S
             }
		}
    }
	}
}
