#include "Drv_Key.h"

/**********全局变量声明*******/
float Key_Status; // 在操作按键的时间

/**********局部变量声明*******/
float Key_Cnt1, Key_Cnt2, Key_Cnt3, Key_Cnt4, Key_Cnt5;             // 按下时间
uint8_t Key_Flag1, Key_Flag2, Key_Flag3, Key_Flag4, Key_Flag5;      // 按键按下标志
uint8_t LongPress1, LongPress2, LongPress3, LongPress4, LongPress5; // 按键长按标志
float UPPress_Time, DownPress_Time;                                 // 长按的时间

/**
 * @brief 检测按键状态
 *
 * @param dT 任务周期
 */
void Check_Press(float dT)
{
    if (Key_Status)
        Key_Status -= dT;
}

/**
 * @brief 按键扫描
 *
 * @param dT 任务周期
 */
void Key_Scan(float dT)
{
    /******************************P键******************************/
    if (Key1 == Key_Down) // 按下按键
    {
        if (LongPress1 == 0) // 没有长按过
        {
            Key_Cnt1 += dT; // 按下时间++
            Key_Flag1 = 1;  // 按键按下标志置一
        }
    }
    if (Key_Flag1) // 按键被按下
    {
        if (Key1 == Key_Up) // 抬起按键
        {
            if (Key_Cnt1 > 0.05f && Key_Cnt1 < 1.5f) // 按键时间大于0.05S小于1.5S是单击
            {
				if (sys.Run_Status == 1)
				{
					Beep_Flash = 2;
				}
				else
				{
					if (PMode.Status == 1) // 如果打开P模式
					{
						PMode.Status = 0; // 关闭P模式
						PMode.Mode = 0;   // 记忆模式下，因为单按只能进入P模式
						PMode.Option = 0;
						Param_Read(); // 读取参数
						sys.SetMode_Option = 0;
						Twinkle_Time = 0;
					}
					else if (PMode.Status == 0)
					{
						PMode.Status = 1; // 打开P模式
						PMode.Mode = 0;   // 记忆模式下，因为单按只能进入P模式
						PMode.Option = 1;
						Param_Read();   // 读取参数
						SetOK_Flag = 1; // 设置参数
						sys.SetMode_Option = 1;
						Twinkle_Time = 6.0f;
					}
					Beep_Time = 0.1f; // 蜂鸣器响0.1S
				}
            }
            Key_Flag1 = 0;  // 按键事件结束，等待下一次按下
            LongPress1 = 0; // 长按标志位清零
            Key_Cnt1 = 0;   // 按钮计数清零
        }
        if (Key_Cnt1 > 1.5f && Key_Cnt1 < 3.0f) // 按键时间大于1.5S小于3S表示长按
        {
            if (LongPress1 == 0) // 如果没有一直长按着
            {
				if (sys.Run_Status == 1)
				{
					Beep_Flash = 2;
				}
				else
				{
                    if(Param.type == 0)
                    {
                        if (PMode.Mode) // 如果打开梯度
                        {
                            PMode.Status = 1; // 打开P模式
                            PMode.Mode = 0;   // 记忆模式下，因为单按只能进入P模式
                            PMode.Option = 1;
                            PMode.P1 = 0;
                            PMode.P2 = 0;
                            Param_Read(); // 读取参数
                            sys.SetMode_Option = 1;
                            Twinkle_Time = 6.0f;
                        }
                        else
                        {
                            PMode.Status = 2; // 打开P模式,选择梯度，用于后面的闪烁
                            PMode.Mode = 1;   // 记忆模式下，因为单按只能进入P模式
                            PMode.P1 = 1;
                            PMode.P2 = 1;
                            PMode.Option = PMode.P1;
                            Param_Read();   // 读取参数
                            SetOK_Flag = 1; // 设置参数
                            sys.SetMode_Option = 5;
                            Twinkle_Time = 6.0f;
                        }
                        Beep_Time = 0.1f; // 蜂鸣器响0.1S
                    }
                    else
                    {
                        Beep_Flash = 2;
                    }
				}
                LongPress1 = 1;   // 长按标志置一
            }
        }
    }

    /******************************MENU键******************************/
    if (Key2 == Key_Down) // 按下按键
    {
        if (LongPress2 == 0) // 没有长按过
        {
            Key_Cnt2 += dT; // 按下时间++
            Key_Flag2 = 1;  // 按键按下标志置一
        }
    }
    if (Key_Flag2) // 按键被按下
    {
        if (Key2 == Key_Up) // ̧抬起按键
        {
            if (Key_Cnt2 > 0.05f && Key_Cnt2 < 1.5f) // 按键时间大于0.05S小于1.5S是单击
            {
				if (sys.Run_Status == 1)
				{
					Beep_Flash = 2;
				}
				else
				{
					if (PMode.Status)
					{
						if (PMode.Mode) // 梯度模式
						{
							sys.SetMode_Option++;
							if (sys.SetMode_Option < 5)
							{
								sys.SetMode_Option = 5;
								PMode.Option = PMode.P1;
								Param_Read(); // 读取参数
							}
							if (sys.SetMode_Option == 6)
							{
								PMode.Option = PMode.P2;
								Param_Read(); // 读取参数
							}
							if (sys.SetMode_Option > 6)
							{
								PMode.Option = PMode.P1;
								Param_Read(); // 读取参数
								sys.SetMode_Option = 0;
							}
						}
						else
						{
							sys.SetMode_Option++;
							if (sys.SetMode_Option > 4)
								sys.SetMode_Option = 0;
						}
					}
					else // 不在P模式下
					{
						sys.SetMode_Option++;
						if (sys.SetMode_Option == 1)
							sys.SetMode_Option = 2;
						else if (sys.SetMode_Option > 4)
							sys.SetMode_Option = 0;
					}
					Twinkle_Time = 6.0f;
					Key_Status = 0;
					Beep_Time = 0.1f; // 蜂鸣器响0.1S
				}
            }
            Key_Flag2 = 0;  // 按键事件结束，等待下一次按下
            LongPress2 = 0; // 长按标志位清零
            Key_Cnt2 = 0;   // 按钮计数清零
        }
        if (Key_Cnt2 > 1.5f && Key_Cnt2 < 3.0f) // 按键时间大于1.5S小于3S表示长按
        {
            if (LongPress2 == 0) // 如果没有一直长按着
            {
				Beep_Flash = 2;
                LongPress2 = 1; // 长按标志置一
            }
        }
    }

    /******************************加键******************************/
    if (Key3 == Key_Down) // 按下按键
    {
        UPPress_Time += dT; // 长按时间加加
        Key_Cnt3 += dT;     // 按下时间++
        Key_Flag3 = 1;      // 按键按下标志置一
    }
    if (Key_Flag3) // 按键被按下
    {
        if (Key3 == Key_Up) // ̧抬起按键
        {
            if (Key_Cnt3 < 1.5f) // 按键时间小于1.5S是单击
            {
				if (sys.Run_Status == 1)
				{
					Beep_Flash = 2;
				}
				else
				{
					if (sys.SetMode_Option == 1)
					{
						PMode.Option++;
						if (PMode.Option > 9)
							PMode.Option = 1;
						Param_Read(); // 读取参数
					}
					else if (sys.SetMode_Option == 2)
					{
						Temp.Set++;
						if (Temp.Set > Temp_MAX)
							Temp.Set = Temp_MAX;
					}
					else if (sys.SetMode_Option == 3)
					{
						Speed.Set += 10;
                        if(Speed.Set == 10)
                            Speed.Set = 100;
						if (Speed.Set > Speed.MAX)
							Speed.Set = Speed.MAX;
					}
					else if (sys.SetMode_Option == 4)
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
						if (Time.Set > Time_MAX)
							Time.Set = Time_MAX;
					}
					else if (sys.SetMode_Option == 5)
					{
						PMode.P1++;
						if (PMode.P1 > 9)
							PMode.P1 = 1;
						PMode.Option = PMode.P1;
						Param_Read(); // 读取参数
					}
					else if (sys.SetMode_Option == 6)
					{
						PMode.P2++;
						if (PMode.P2 > 9)
							PMode.P2 = 1;
						PMode.Option = PMode.P2;
						Param_Read(); // 读取参数
					}
					else
					{
						Beep_Flash = 2;
					}
					Key_Status = 2.0f;
					Twinkle_Time = 6.0f;
				}
            }
            Key_Flag3 = 0; // 按键事件结束，等待下一次按下
            Key_Cnt3 = 0;  // 按钮计数清零
        }
        else if (Key_Cnt3 > 1.9f && Key_Cnt3 < 2.1f) // 按键时间大于1.9S小于2.1S表示长按
        {
            if (sys.SetMode_Option == 1)
            {
            }
            else if (sys.SetMode_Option == 2)
            {
                if (UPPress_Time > 5.0f)
                {
                    Temp.Set += 10;
                }
                else
                {
                    Temp.Set++;
                }
                if (Temp.Set > Temp_MAX)
                    Temp.Set = Temp_MAX;
            }
            else if (sys.SetMode_Option == 3)
            {
                if (UPPress_Time > 3.0f)
                {
                    Speed.Set += 20;
                    if(Speed.Set == 20)
                            Speed.Set = 100;
                }
                else
                {
                    Speed.Set += 10;
                    if(Speed.Set == 10)
                            Speed.Set = 100;
                }
                if (Speed.Set > Speed.MAX)
                    Speed.Set = Speed.MAX;
            }
            else if (sys.SetMode_Option == 4)
            {
                if (UPPress_Time > 5.0f)
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
                else
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
                if (Time.Set > Time_MAX)
                    Time.Set = Time_MAX;
            }
            Key_Status = 2.0f;
            Twinkle_Time = 6.0f;
            if (UPPress_Time > 5.0f)
            {
                Key_Cnt3 = 1.82f; // 长按按键时间复位
            }
            else
            {
                Key_Cnt3 = 1.88f;
            }
            Key_Flag3 = 0; // 按键事件结束，等待下一次按下
        }
    }
    else
    {
        UPPress_Time = 0;
        Key_Cnt3 = 0; // 按键计数清零
    }

    /******************************减键******************************/
    if (Key4 == Key_Down) // 按下按键
    {
        DownPress_Time += dT;
        Key_Cnt4 += dT; // 按下时间++
        Key_Flag4 = 1;  // 按键按下标志置一
    }
    if (Key_Flag4 == 1) // 按键被按下
    {
        if (Key4 == Key_Up) // ̧抬起按键
        {
            if (Key_Cnt4 < 1.5f) // 按键时间小于1.5S是单击
            {
				if (sys.Run_Status == 1)
				{
					Beep_Flash = 2;
				}
				else
				{
					if (sys.SetMode_Option == 1)
					{
						PMode.Option--;
						if (PMode.Option < 1)
							PMode.Option = 9;
						Param_Read(); // 读取参数
					}
					else if (sys.SetMode_Option == 2)
					{
						Temp.Set--;
						if(Param.type == 0)
                        {
                            if (Temp.Set < Temp_MIN)
                                Temp.Set = Temp_MIN;
                        }
                        else
                        {
                            if (Temp.Set < 0)
                                Temp.Set = 0;
                        }
					}
					else if (sys.SetMode_Option == 3)
					{
						Speed.Set -= 10;
						if (Speed.Set < Speed_MIN)
							Speed.Set = 0;
					}
					else if (sys.SetMode_Option == 4)
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
						if (Time.Set < Time_MIN)
							Time.Set = Time_MIN;
					}
					else if (sys.SetMode_Option == 5)
					{
						PMode.P1--;
						if (PMode.P1 < 1)
							PMode.P1 = 9;
						PMode.Option = PMode.P1;
						Param_Read(); // 读取参数
					}
					else if (sys.SetMode_Option == 6)
					{
						PMode.P2--;
						if (PMode.P2 < 1)
							PMode.P2 = 9;
						PMode.Option = PMode.P2;
						Param_Read(); // 读取参数
					}
					else
					{
						Beep_Flash = 2;
					}
					Key_Status = 2.0f;
					Twinkle_Time = 6.0f;
				}
            }
            Key_Flag4 = 0; // 按键事件结束，等待下一次按下
            Key_Cnt4 = 0;  // 按钮计数清零
        }
        else if (Key_Cnt4 > 1.9f && Key_Cnt4 < 2.1f) // 按键时间大于1.9S小于2.1S表示长按
        {
            if (sys.SetMode_Option == 1)
            {
            }
            else if (sys.SetMode_Option == 2)
            {
                if (DownPress_Time > 5.0f)
                {
                    Temp.Set -= 10;
                }
                else
                {
                    Temp.Set--;
                }
                if(Param.type == 0)
                {
                    if (Temp.Set < Temp_MIN)
                        Temp.Set = Temp_MIN;
                }
                else
                {
                    if (Temp.Set < 0)
                        Temp.Set = 0;
                }
            }
            else if (sys.SetMode_Option == 3)
            {
                if (DownPress_Time > 5.0f)
                {
                    Speed.Set -= 100;
                }
                else
                {
                    Speed.Set -= 10;
                }
                if (Speed.Set < Speed_MIN)
                    Speed.Set = 0;
            }
            else if (sys.SetMode_Option == 4)
            {
                if (DownPress_Time > 5.0f)
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
                else
                {
                    if (Time.Set < 3600)
                        Time.Set -= 5;
                    else
                    {
                        if (Time.Set % 60)
                            Time.Set = 3600;
                        else
                            Time.Set -= 60;
                    }
                }
                if (Time.Set < Time_MIN)
                    Time.Set = Time_MIN;
            }
            Key_Status = 2.0f;
            Twinkle_Time = 6.0f;
            if (DownPress_Time > 5.0f)
            {
                Key_Cnt4 = 1.82f; // 长按按键时间复位
            }
            else
            {
                Key_Cnt4 = 1.88f;
            }
            Key_Flag4 = 0; // 按键事件结束，等待下一次按下
        }
    }
    else
    {
        DownPress_Time = 0;
        Key_Cnt4 = 0; // 按键计数清零
    }

    /******************************Start键******************************/
    if (Key5 == Key_Down) // 按下按键
    {
        if (LongPress5 == 0) // 没有长按过
        {
            Key_Cnt5 += dT; // 按下时间++
            Key_Flag5 = 1;  // 按键按下标志置一
        }
    }
    if (Key_Flag5) // 按键被按下
    {
        if (Key5 == Key_Up) // 抬起按键
        {
            if (Key_Cnt5 > 0.05f && Key_Cnt5 < 1.5f) // 按键时间大于0.05S小于1.5S表示长按
            {
                if (!HALL1 || !HALL2)
                {
                    if (sys.Run_Status == 1)
                    {
                        sys.Run_Status = 2;
                        sys.SetMode_Option = 0;
                        Speed.ADDMode = 2;
                        SetOK_Flag = 1;
                        PMode.Circle_Step = 0;
                        WIND_OFF;
                    }
                    else
                    {
                        sys.Run_Status = 1;
                        Speed_Val.Integral = 14; // 13pwm启动
                        Speed.ADDMode = 0;
                        Temp.ADDMode = 0;
                        sys.SetMode_Option = 0;
                        SetOK_Flag = 1;
                        if(Param.type == 0)//加热制冷
                        {
                            if (Temp.Set >= Temp.Rel)
                            {
                                Temp.Icon = 0; // 加热图标
                                Temp.Mode = 0; // 加热
                                WIND_OFF;
                            }
                            else
                            {
                                Temp.Icon = 1; // 制冷图标
                                Temp.Mode = 1; // 制冷
                                WIND_ON;
                            }
                        }
                        else
                        {
                            Temp.Icon = 0; // 加热图标
                            Temp.Mode = 0; // 加热
                            WIND_OFF;
                        }
                        if (PMode.Mode == 1)
                        {
                            PMode.Option = PMode.P1;
                            Param_Read(); // 读取参数
                        }
                    }
                    Temp.Base_Err = 0;
                    Beep_Time = 0.1f;
                }
                else
                {
                    Temp.Base_Err = 1; // 模块没放，触发报警
                    Beep_Flash = 3;
                }
            }
            Key_Flag5 = 0;  // 按键事件结束，等待下一次按下
            LongPress5 = 0; // 长按标志位清零
            Key_Cnt5 = 0;   // 按钮计数清零
        }
        if (Key_Cnt5 > 1.5f && Key_Cnt5 < 3.0f) // 按键时间大于1.5S小于3S表示长按
        {
            if (LongPress5 == 0) // 如果没有一直长按着
            {
				Beep_Flash = 2;
                LongPress5 = 1; // 长按标志置一
            }
        }
    }
}
