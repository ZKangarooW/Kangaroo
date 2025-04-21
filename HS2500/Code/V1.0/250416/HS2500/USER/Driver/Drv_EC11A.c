#include "Drv_EC11A.h"

/**********结构体************/
_EC11A_ EC11A[2];//旋钮变量

/**
 * @brief EC11A初始化定时器
 * 
 */
void EC11A_Init(void)
{
	/**********EC11A_1**********/
	EC11A[0].EXTI_Pin = EC1A_Pin;//EC11A旋钮中断引脚
	EC11A[0].EC11A_Pin = EC1B_Pin;//EC11A旋钮方向引脚
	EC11A[0].EC11A_GPIO = EC1B_GPIO_Port;//EC11A旋钮方向GPIO端口
	
	EC11A[0].Key_Pin = KEY1_Pin;//EC11A按键输入引脚
	EC11A[0].Key_GPIO = KEY1_GPIO_Port;//EC11A按键GPIO端口
	
	EC11A[0].EC11A_Fast = EC11A_FastSpeed;//中断旋转速度阈值

	/**********EC11A_2**********/
	EC11A[1].EXTI_Pin = EC2A_Pin;//EC11A旋钮中断引脚
	EC11A[1].EC11A_Pin = EC2B_Pin;//EC11A旋钮方向引脚
	EC11A[1].EC11A_GPIO = EC2B_GPIO_Port;//EC11A旋钮方向GPIO端口
	
	EC11A[1].Key_Pin = KEY2_Pin;//EC11A按键输入引脚
	EC11A[1].Key_GPIO = KEY2_GPIO_Port;//EC11A按键GPIO端口
	
	EC11A[1].EC11A_Fast = EC11A_FastSpeed;//中断旋转速度阈值
}

/**
 * @brief EC11A旋钮速度计算
 * 
 * @param dT 执行周期
 */
void EC11A_Speed(float dT)
{
	/**********EC11A_1**********/
	EC11A[0].EC11A_Speed = EC11A[0].EC11A_Cnt*60/20;//一秒一次。转一圈20个脉冲，一分钟的速度
	EC11A[0].EC11A_Cnt = 0;//清检测到的脉冲计数
	
	/**********EC11A_2**********/
	EC11A[1].EC11A_Speed = EC11A[1].EC11A_Cnt*60/20;//一秒一次。转一圈20个脉冲，一分钟的速度
	EC11A[1].EC11A_Cnt = 0;//清检测到的脉冲计数
}

/**
 * @brief 检测按键状态-500ms
 * 
 * @param dT 执行周期
 */
void Check_Press(float dT)
{
    if(EC11A[0].EC11A_Knob) //旋钮0旋转
    {
        EC11A[0].EC11A_Knob -= dT; //递减时间
    }
    
    if(EC11A[1].EC11A_Knob) //旋钮1旋转
    {
        EC11A[1].EC11A_Knob -= dT; //递减时间
    }
}

/**
 * @brief EC11A按键扫描
 * 
 * @param dT 执行周期
 */
void EC11AKey_Scan(float dT)
{
	/**********EC11A_1**********/
	if(HAL_GPIO_ReadPin(EC11A[0].Key_GPIO,EC11A[0].Key_Pin) == GPIO_PIN_RESET)//按下按键
	{
        // if(sys.Display)
        // {
        //     return;
        // }
		if(EC11A[0].LongPress == 0)//没有长按
		{
			EC11A[0].Key_Cnt += dT;//按键时间++
			EC11A[0].Key_Flag = 1;//按键按下标志置1
		}
	}
	if(EC11A[0].Key_Flag == 1)//按键已按下
	{
		if(HAL_GPIO_ReadPin(EC11A[0].Key_GPIO,EC11A[0].Key_Pin) == GPIO_PIN_SET)//抬起按键
		{   
			if(EC11A[0].Key_Cnt > 0.1 && EC11A[0].Key_Cnt < 1.5)//小于1.5S是单击
			{
                if(sys.Lock)
				{
					Beep_Flash = 2;//蜂鸣器短促响两声
                    sys.Lock_Alarm = 2.0f;//触发锁定报警，图标闪烁报警
				}
				else
				{
                    if (sys.Setting == 1) // 处于设置模式时
                    {
                        sys.Setting_Option++;
                        if(sys.Setting_Option > 4)
                            sys.Setting_Option = 0;
                    }
                    else//运行模式
                    {
                        if(sys.Run_Status != 1 && (Speed.Set || Temp.Set))//系统没有运行时
                        {
                            sys.Run_Status = 1;//启动系统
                            Speed.ADDMode = 0;//清除速度显示标志
                            if(Speed.Up_Speed == 1)//低速
                            {
                                Speed_Val.Integral = 30;//积分值
                            }
                            else if(Speed.Up_Speed == 2)//中速
                            {
                                Speed_Val.Integral = 40;//积分值
                            }
                            else//高速
                            {
                                Speed_Val.Integral = 30;//积分值
                            }
                        }
                        else//系统运行时
                        {
                            Speed.ADDMode = 2;//设置模式
                            sys.Motor_Stop = 1;//电机停止
                        }
                    }
                    Beep_Time = 0.1;//蜂鸣时间0.1S
                }
			}
			EC11A[0].Key_Flag = 0;//清除按键事件，等待下一次按键
			EC11A[0].LongPress = 0;//长按标志清零
			EC11A[0].Key_Cnt = 0;//按键计数器清零
		}
		if(EC11A[0].Key_Cnt > 3.0f && EC11A[0].Key_Cnt < 4.0f)//按键时间大于3S小于4S显示长按
		{
			if(EC11A[0].LongPress == 0)//如果还没有一直按住
			{
                if(sys.Lock)
				{
					Beep_Flash = 2;//蜂鸣器短促响两声
                    sys.Lock_Alarm = 2.0f;//触发锁定报警，图标闪烁报警
				}
				else
				{
                    if (sys.Setting == 1) // 处于设置模式时
                    {
                        sys.Setting = 0;//退出设置界面
                        sys.Setting_Option = 0;
                        Param.Unit = Temp.Unit;//温度单位
                        Param.TempUp_Speed = Temp.Up_Speed;//升温速度
                        Param.SpeedUp_Speed = Speed.Up_Speed;//加速速度
                        Param.Safe_Temp = Temp.Safe_Temp;//安全温度
                        Param.DownTime_Type = sys.DownTime_Type;//停机时间类型写入Flash
                        Save_Param_En = 1;//保存
                    }
                    else if (sys.Setting == 0)
                    {
                        sys.Setting = 1;//进入设置界面
                        sys.Setting_Option = 0;
                    }
                    Beep_Time = 0.1f; // 蜂鸣时间0.1S
                }
				EC11A[0].LongPress = 1;//长按标志置1
			}
		}
	}
	
	/**********EC11A_2**********/
	if(HAL_GPIO_ReadPin(EC11A[1].Key_GPIO,EC11A[1].Key_Pin) == GPIO_PIN_RESET)//按下按键
	{
        // if(sys.Display)
        // {
        //     return;
        // }
		if(EC11A[1].LongPress == 0)//没有长按
		{
			EC11A[1].Key_Cnt += dT;//按键时间++
			EC11A[1].Key_Flag = 1;//按键按下标志置1
		}
	}
	if(EC11A[1].Key_Flag == 1)//按键已按下
	{
		if(HAL_GPIO_ReadPin(EC11A[1].Key_GPIO,EC11A[1].Key_Pin) == GPIO_PIN_SET)//抬起按键
		{   
			if(EC11A[1].Key_Cnt > 0.1 && EC11A[1].Key_Cnt < 1.5)//小于1.5S是单击
			{
                if(sys.Lock)
				{
					Beep_Flash = 2;//蜂鸣器短促响两声
                    sys.Lock_Alarm = 2.0f;//触发锁定报警，图标闪烁报警
				}
				else
				{
                    if(sys.Run_Status != 1 && (Speed.Set || Temp.Set))//系统没有运行时
                    {
                        sys.Run_Status = 1;//启动系统
                        Speed.ADDMode = 0;//清除速度显示标志
                        if(Speed.Up_Speed == 1)//低速
                        {
                            Speed_Val.Integral = 30;//积分值
                        }
                        else if(Speed.Up_Speed == 2)//中速
                        {
                            Speed_Val.Integral = 40;//积分值
                        }
                        else//高速
                        {
                            Speed_Val.Integral = 30;//积分值
                        }
                    }
                    else//系统运行时
                    {
                        Speed.ADDMode = 2;//设置模式
                        sys.Motor_Stop = 1;//电机停止
                    }
                    SpeedSet_Flag = TempSet_Flag = TimeSet_Flag=1;//设置标志
                    Speed_Twinkle_Time = Temp_Twinkle_Time = Time_Twinkle_Time = 0;//关闭闪烁
                    Beep_Time = 0.1;//蜂鸣时间0.1S
                    sys.SetMode_Option = 0;
                }
			}
			EC11A[1].Key_Flag = 0;//清除按键事件，等待下一次按键
			EC11A[1].LongPress = 0;//长按标志清零
			EC11A[1].Key_Cnt = 0;//按键计数器清零
		}
		if(EC11A[1].Key_Cnt > 1.5 && EC11A[1].Key_Cnt < 3)//按键时间大于1.5S小于3S显示长按
		{
			if(EC11A[1].LongPress == 0)//如果还没有一直按住
			{
                if(sys.Lock)
				{
					Beep_Flash = 2;//蜂鸣器短促响两声
                    sys.Lock_Alarm = 2.0f;//触发锁定报警，图标闪烁报警
				}
				else
				{
                    if(!Speed.Cw)//改变转向时
                    {
                        Speed.ADDMode = 2;//设置模式
                        sys.Motor_Stop = 1;//电机停止
                        Speed.Cw = 1;//改变转向
                        Speed.CwShow = 1;//转向图标改变，重新开始
                        SpeedSet_Flag = TempSet_Flag = TimeSet_Flag=1;//设置标志
                    }
                    Beep_Time = 0.1;//蜂鸣时间0.1S
                }
				EC11A[1].LongPress = 1;//长按标志置1
			}
		}
	}
}
