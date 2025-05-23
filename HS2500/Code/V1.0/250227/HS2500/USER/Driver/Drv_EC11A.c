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
	EC11A[0].EXTI_Pin = EC1A_Pin;//EC11A旋钮中断引脚
	EC11A[0].EC11A_Pin = EC1B_Pin;//EC11A旋钮输入引脚
	EC11A[0].EC11A_GPIO = EC1B_GPIO_Port;//EC11A旋钮输入GPIO端口
	
	EC11A[0].Key_Pin = KEY1_Pin;//EC11A按键输入引脚
	EC11A[0].Key_GPIO = KEY1_GPIO_Port;//EC11A按键输入GPIO端口
	
	EC11A[0].EC11A_Fast = EC11A_FastSpeed;//判断旋转速度阈值
	
	/**********EC11A_2**********/
	EC11A[1].EXTI_Pin = EC2A_Pin;//EC11A旋钮中断引脚
	EC11A[1].EC11A_Pin = EC2B_Pin;//EC11A旋钮输入引脚
	EC11A[1].EC11A_GPIO = EC2B_GPIO_Port;//EC11A旋钮输入GPIO端口
	
	EC11A[1].Key_Pin = KEY2_Pin;//EC11A按键输入引脚
	EC11A[1].Key_GPIO = KEY2_GPIO_Port;//EC11A按键输入GPIO端口
	
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
    if(EC11A[0].EC11A_Knob)//旋钮0旋转
        EC11A[0].EC11A_Knob -= dT;//倒计时
	
	if(EC11A[1].EC11A_Knob)//旋钮1旋转
        EC11A[1].EC11A_Knob -= dT;//倒计时
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
        if(sys.Display || sys.DownTime_Mode)
        {
            return;
        }
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
				if(sys.Lock)
				{
					Beep_Flash = 2;//“滴滴”两下用于误触
                    sys.Lock_Alarm = 2.0f;//锁定误触，图标闪烁两下
				}
				else
				{
                    if(sys.Run_Status != 1 && (Speed.Set || Temp.Set))//系统没启动的话
                    {
                        sys.Run_Status = 1;//启动系统
                        Speed.ADDMode = 0;//进入判断速度显示处理
                        Speed_Val.Integral = 24;//电器起步
                    }
                    else//系统启动的话
                    {
                        Speed.ADDMode = 2;//进入减速模式
                        sys.Motor_Stop = 1;//电机停止
                    }
                    Beep_Time = 0.1;//蜂鸣器响0.1S
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
				if(sys.Lock)
				{
					Beep_Flash = 2;//“滴滴”两下用于误触
                    sys.Lock_Alarm = 2.0f;//锁定误触，图标闪烁两下
				}
                else
                {
                    Beep_Flash = 2;//“滴滴”两下用于误触
                }
				EC11A[0].LongPress = 1;//长按标志置一
			}
		}
	}
	
	/**********EC11A_2**********/
	if(HAL_GPIO_ReadPin(EC11A[1].Key_GPIO,EC11A[1].Key_Pin) == KEY_DOWN)//按下按键
	{
        if(sys.Display)
        {
            return;
        }
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
				if(sys.Lock)
				{
					Beep_Flash = 2;//“滴滴”两下用于误触
                    sys.Lock_Alarm = 2.0f;//锁定误触，图标闪烁两下
				}
				else
				{
                    if(sys.DownTime_Mode)
                    {
                        sys.DownTime_Mode = 0;//退出设定模式
                        Beep_Time = 0.1;//蜂鸣器响0.1S
                    }
                    else
                    {
                        if(sys.Run_Status != 1 && (Speed.Set || Temp.Set))//系统没启动的话
                        {
                            sys.Run_Status = 1;//启动系统
                            Speed.ADDMode = 0;//进入判断速度显示处理
                            Speed_Val.Integral = 24;//电器起步
                        }
                        else//系统启动的话
                        {
                            Speed.ADDMode = 2;//进入减速模式
                            sys.Motor_Stop = 1;//电机停止
                        }
                        SpeedSet_Flag = TempSet_Flag = TimeSet_Flag=1;//进入设置
                        Speed_Twinkle_Time = Temp_Twinkle_Time = Time_Twinkle_Time = 0;//关闭闪烁
                        Beep_Time = 0.1;//蜂鸣器响0.1S
                        sys.SetMode_Option = 0;
                    }
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
				if(sys.Lock)
				{
					Beep_Flash = 2;//“滴滴”两下用于误触
                    sys.Lock_Alarm = 2.0f;//锁定误触，图标闪烁两下
				}
				else
				{
                    if(!Speed.Cw)//改变转向的话
                    {
                        Speed.ADDMode = 2;//进去减速显示
                        sys.Motor_Stop = 1;//电机停止
                        Speed.Cw = 1;//进入改变转向
                        Speed.CwShow = 1;//转向图标改变，动画开始
                        SpeedSet_Flag = TempSet_Flag = TimeSet_Flag=1;//进入设置
                    }
                    Beep_Time = 0.1;//蜂鸣器响0.1S
                }
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
        if(sys.Display)
        {
            return;
        }
        if(sys.Lock)
        {
            Beep_Flash = 2;//“滴滴”两下用于误触
            sys.Lock_Alarm = 2.0f;//锁定误触，图标闪烁两下
            return;
        }
        if(GPIO_Pin == EC11A[0].EXTI_Pin)//在2ms内，检测到电平变化
        { 
            EC11A[0].EC11A_Cnt++;//旋钮计数
            EC11A[0].EC11A_Knob = 2.0f;//在旋转旋钮时
            if(sys.SetMode_Option != 3)
                sys.SetMode_Option = 1;//设置温度
            if(HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO,EC11A[0].EC11A_Pin) == 1)//加
            {
                if (Pmode_Twinkle_Time) // 如果在设置P值时
                {
                    PMode.Option ++;
                    if(PMode.Option > 9)
                        PMode.Option = 1;
                    Param_Read(); // 读取参数
                    Pmode_Twinkle_Time = 2.0f;
                }
                else if(sys.DownTime_Mode)
                {
                    sys.DownTime_Type = C2;
                    Param.DownTime_Type = sys.DownTime_Type;//将计时类型赋值倒Flash中
                    Save_Param_En = 1;
                }
                else
                {
                    if(sys.SetMode_Option == 1)
                    {
                        if(EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast)//如果慢慢旋转
                        {
                            if(Temp.Set < 1000)
                            {
                                Temp.Set += 5;
                            }
                            else
                            {
                                if (Temp.Set % 10)
                                    Temp.Set = Temp.Set - (Temp.Set % 10);
                                Temp.Set += 10;
                            }
                        }
                        else
                        {
                            Temp.Set += 20;
                            if (Temp.Set % 10 && Temp.Set > 1000)
                                Temp.Set = Temp.Set - (Temp.Set % 10);
                        }
                        if(Temp.Set > Temp.Safe_Temp - 500)
                            Temp.Set = Temp.Safe_Temp - 500;
                        Temp_Twinkle_Time = 2;//闪烁时间2S
                    }
                    else if(sys.SetMode_Option == 3)
                    {
                        if(EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast)//如果慢慢旋转
						{
							Time.Set += 60;
						}
						else
						{
							Time.Set += 300;
						}
						if(Time.Set > Time_MAX)
							Time.Set = Time_MAX;
                        Time_Twinkle_Time = 2;//闪烁时间2S
                    }
                }
            }
            else if(HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO,EC11A[0].EC11A_Pin) == 0)//减
            {
                if (Pmode_Twinkle_Time) // 如果在设置P值时
                {
                    PMode.Option --;
                    if(PMode.Option < 1)
                        PMode.Option = 9;
                    Param_Read(); // 读取参数
                    Pmode_Twinkle_Time = 2.0f;
                }
                else if(sys.DownTime_Mode)
                {
                    sys.DownTime_Type = C1;
                    Param.DownTime_Type = sys.DownTime_Type;//将计时类型赋值倒Flash中
                    Save_Param_En = 1;
                }
                else
                {
                    if(sys.SetMode_Option == 1)
					{
						if(EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast)//如果慢慢旋转
                        {
                            if(Temp.Set < 1000)
                            {
                                Temp.Set -= 5;
                            }
                            else
                            {
                                if (Temp.Set % 10)
                                    Temp.Set = Temp.Set - (Temp.Set % 10);
                                Temp.Set -= 10;
                            }
                        }
						else
                        {
                            Temp.Set -= 20;
                            if (Temp.Set % 10 && Temp.Set > 1000)
                                Temp.Set = Temp.Set - (Temp.Set % 10);
                        }
						if(Temp.Set <= 0)
							Temp.Set = 0;
						Temp_Twinkle_Time = 2;//闪烁时间2S
					}
                    else if(sys.SetMode_Option == 3)
                    {
                        if(EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast)//如果慢慢旋转
						{
							Time.Set -= 60;
						}
						else
						{
							Time.Set -= 300;
						}
						if(Time.Set < 0)
							Time.Set = 0;
						Time_Twinkle_Time = 2;//闪烁时间2S
                    }
                }
            }
        }
	}
	
	/**********EC11A_2**********/
	if(GPIO_Pin == EC11A[1].EXTI_Pin)//A上升沿触发外部中断
	{
        if(sys.Display ||sys.DownTime_Mode)
        {
            return;
        }
        if(sys.Lock)
        {
            Beep_Flash = 2;//“滴滴”两下用于误触
            sys.Lock_Alarm = 2.0f;//锁定误触，图标闪烁两下
            return;
        }
        if(GPIO_Pin == EC11A[1].EXTI_Pin)//在2ms内，检测到电平变化
        { 
            EC11A[1].EC11A_Cnt++;//旋钮计数
            EC11A[1].EC11A_Knob = 2.0f;//在旋转旋钮时
            if(sys.SetMode_Option != 3)
                sys.SetMode_Option = 2;//设置速度
            if(HAL_GPIO_ReadPin(EC11A[1].EC11A_GPIO,EC11A[1].EC11A_Pin) == 0)//加
            {
                if (Pmode_Twinkle_Time) // 如果在设置P值时
                {
                    PMode.Option ++;
                    if(PMode.Option > 9)
                        PMode.Option = 1;
                    Param_Read(); // 读取参数
                }
                else
                {
                    if(sys.SetMode_Option == 2)
                    {
                        if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//如果慢慢旋转
                        {
                            Speed.Set += 10;
                            if(Speed.Set == 10)//从零转开始最低为50转，判断是10后
                                Speed.Set = 100;//设定转速为100开始
                        }
                        else
                        {
                            Speed.Set += 30;
                            if(Speed.Set == 30)//从零转开始最低为50转，判断是10后
                                Speed.Set = 100;//设定转速为100开始
                        }
                        if(Speed.Set > Speed_MAX)
                            Speed.Set = Speed_MAX;
                        Speed_Twinkle_Time = 2;//闪烁时间2S
                    }
                    else if(sys.SetMode_Option == 3)
                    {
                        if(EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast)//如果慢慢旋转
						{
							Time.Set += 60;
						}
						else
						{
							Time.Set += 300;
						}
						if(Time.Set > Time_MAX)
							Time.Set = Time_MAX;
                        Time_Twinkle_Time = 2;//闪烁时间2S
                    }
                }
            }
            else if(HAL_GPIO_ReadPin(EC11A[1].EC11A_GPIO,EC11A[1].EC11A_Pin) == 1)//减
            {
                if (Pmode_Twinkle_Time) // 如果在设置P值时
                {
                    PMode.Option --;
                    if(PMode.Option < 1)
                        PMode.Option = 9;
                    Param_Read(); // 读取参数
                }
                else
                {
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
                        if(Speed.Set < Speed_MIN)
                            Speed.Set = 0;
                        Speed_Twinkle_Time = 2;//闪烁时间6S
                    }
                    else if(sys.SetMode_Option == 3)
                    {
                        if(EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast)//如果慢慢旋转
						{
							Time.Set -= 60;
						}
						else
						{
							Time.Set -= 300;
						}
						if(Time.Set < 0)
							Time.Set = 0;
						Time_Twinkle_Time = 2;//闪烁时间2S
                    }
                }
            }
        }
	}
}
