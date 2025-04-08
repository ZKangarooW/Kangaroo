#include "Drv_Key.h"

/**********全局变量声明*******/
float Key_Status;// 在操作按键的时间

/**********局部变量声明*******/
float Key_Cnt1, Key_Cnt2, Key_Cnt3, Key_Cnt4;// 按下时间
uint8_t Key_Flag1, Key_Flag2, Key_Flag3, Key_Flag4;// 按键按下标志
uint8_t LongPress1, LongPress2, LongPress3, LongPress4;// 按键长按标志
float UPPress_Time, DownPress_Time;// 长按的时间

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
    /******************************MENU键******************************/
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
                sys.SetMode_Option++;//设置模式++
                if(sys.SetMode_Option == 3)
                {
                    sys.SetMode_Option = 0;
                }
                if(sys.Run_Status)
                    Twinkle_Time = 2.0f;//闪烁显示2S
                else
                    Twinkle_Time = 6.0f;//闪烁显示6S
                Beep_Time = 0.1;//蜂鸣器响0.1S
            }
            Key_Flag1 = 0;  // 按键事件结束，等待下一次按下
            LongPress1 = 0; // 长按标志位清零
            Key_Cnt1 = 0;   // 按钮计数清零
        }
        if (Key_Cnt1 > 1.5f && Key_Cnt1 < 3.0f) // 按键时间大于1.5S小于3S表示长按
        {
            if (LongPress1 == 0) // 如果没有一直长按着
            {
				Beep_Flash = 2;
                LongPress1 = 1;   // 长按标志置一
            }
        }
    }

    /******************************加键******************************/
    if (Key2 == Key_Down) // 按下按键
    {
        UPPress_Time += dT; // 长按时间加加
        Key_Cnt2 += dT;     // 按下时间++
        Key_Flag2 = 1;      // 按键按下标志置一
    }
    if (Key_Flag2) // 按键被按下
    {
        if (Key2 == Key_Up) // ̧抬起按键
        {
            if (Key_Cnt2 < 1.5f) // 按键时间小于1.5S是单击
            {
				if(sys.SetMode_Option == 1)
                {
                    Speed.Set += 10;
                    if(Speed.Set >= Speed_MAX)
                        Speed.Set = Speed_MAX;
                }
                else if(sys.SetMode_Option == 2)
                {
                    Time.Set += 60;
                    if(Time.Set >= 86400)
                        Time.Set = 86400;
                }
                Key_Status = 2.0f;//检测是不是在调参数
                 if(sys.Run_Status)
                    Twinkle_Time = 2.0f;//闪烁显示2S
                else
                    Twinkle_Time = 6.0f;//闪烁显示6S
            }
            Key_Flag2 = 0; // 按键事件结束，等待下一次按下
            Key_Cnt2 = 0;  // 按钮计数清零
        }
        else if (Key_Cnt2 > 1.9f && Key_Cnt2 < 2.1f) // 按键时间大于1.9S小于2.1S表示长按
        {
            if(sys.SetMode_Option == 1)
            {
                if (UPPress_Time > 5.0f)
                {
                    Speed.Set += 30;
                }
                else
                {
                    Speed.Set += 10;
                }
                if(Speed.Set >= Speed_MAX)
                    Speed.Set = Speed_MAX;
            }
            else if(sys.SetMode_Option == 2)
            {
                if (UPPress_Time > 5.0f)
                {
                    Time.Set += 600;
                }
                else
                {
                    Time.Set += 60;
                }
                if(Time.Set >= Time_MAX)
                    Time.Set = Time_MAX;
            }
            Key_Status = 2.0f;
             if(sys.Run_Status)
                    Twinkle_Time = 2.0f;//闪烁显示2S
                else
                    Twinkle_Time = 6.0f;//闪烁显示6S
            if (UPPress_Time > 5.0f)
            {
                Key_Cnt2 = 1.82f; // 长按按键时间复位
            }
            else
            {
                Key_Cnt2 = 1.88f;
            }
            Key_Flag2 = 0; // 按键事件结束，等待下一次按下
        }
    }
    else
    {
        UPPress_Time = 0;
        Key_Cnt2 = 0; // 按键计数清零
    }

    /******************************减键******************************/
    if (Key3 == Key_Down) // 按下按键
    {
        DownPress_Time += dT;
        Key_Cnt3 += dT; // 按下时间++
        Key_Flag3 = 1;  // 按键按下标志置一
    }
    if (Key_Flag3 == 1) // 按键被按下
    {
        if (Key3 == Key_Up) // ̧抬起按键
        {
            if (Key_Cnt3 < 1.5f) // 按键时间小于1.5S是单击
            {
				if(sys.SetMode_Option == 1)
                {
                    Speed.Set -= 10;
                    if(Speed.Set <= Speed_MIN)
                        Speed.Set = Speed_MIN;
                }
                else if(sys.SetMode_Option == 2)
                {
                    Time.Set -= 60;
                    if(Time.Set <= 0)
                        Time.Set = 0;
                }
                Key_Status = 2.0f;//检测是不是在调参数
                 if(sys.Run_Status)
                    Twinkle_Time = 2.0f;//闪烁显示2S
                else
                    Twinkle_Time = 6.0f;//闪烁显示6S
            }
            Key_Flag3 = 0; // 按键事件结束，等待下一次按下
            Key_Cnt3 = 0;  // 按钮计数清零
        }
        else if (Key_Cnt3 > 1.9f && Key_Cnt3 < 2.1f) // 按键时间大于1.9S小于2.1S表示长按
        {
            if(sys.SetMode_Option == 1)
            {
                if (DownPress_Time > 5.0f)
                {
                    Speed.Set -= 100;
                }
                else
                {
                    Speed.Set -= 10;
                }
                if(Speed.Set <= Speed_MIN)
                    Speed.Set = Speed_MIN;
            }
            else if(sys.SetMode_Option == 2)
            {
                if (DownPress_Time > 5.0f)
                {
                    Time.Set -= 600;
                }
                else
                {
                    Time.Set -= 60;
                }
                if(Time.Set <= 0)
                    Time.Set = 0;
            }
            Key_Status = 2.0f;//检测是不是在调参数
             if(sys.Run_Status)
                    Twinkle_Time = 2.0f;//闪烁显示2S
                else
                    Twinkle_Time = 6.0f;//闪烁显示6S
            if (DownPress_Time > 5.0f)
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
        DownPress_Time = 0;
        Key_Cnt3 = 0; // 按键计数清零
    }

    /******************************Start键******************************/
    if (Key4 == Key_Down) // 按下按键
    {
        if (LongPress4 == 0) // 没有长按过
        {
            Key_Cnt4 += dT; // 按下时间++
            Key_Flag4 = 1;  // 按键按下标志置一
        }
    }
    if (Key_Flag4) // 按键被按下
    {
        if (Key4 == Key_Up) // 抬起按键
        {
            if (Key_Cnt4 > 0.05f && Key_Cnt4 < 1.5f) // 按键时间大于0.05S小于1.5S是单击
            {
				if(sys.Run_Status == 0)
                {
                    sys.Run_Status = 1;
					sys.SetMode_Option = 0;
					Speed.ADDMode = 0;
					Speed_Val.Integral = 40; // 13pwm启动
					Twinkle_Time = 0;
					Key_Status = 0;
                    SetOK_Flag = 1;
                    Beep_Time = 0.1;//蜂鸣器响0.1S
                }
                else//启动下单击按键，直接停止
                {
                    sys.Motor_Stop = 1;//关闭运行
					Speed.ADDMode = 2;//进入减速模式下
                    Twinkle_Time = 0;
					Key_Status = 0;
                    SetOK_Flag = 1;
                }
                Beep_Time = 0.1;//蜂鸣器响0.1S
            }
            Key_Flag4 = 0;  // 按键事件结束，等待下一次按下
            LongPress4 = 0; // 长按标志位清零
            Key_Cnt4 = 0;   // 按钮计数清零
        }
        if (Key_Cnt4 > 1.5f && Key_Cnt4 < 3.0f) // 按键时间大于1.5S小于3S表示长按
        {
            if (LongPress4 == 0)// 如果没有一直长按着
            {
				Beep_Flash = 2;
                LongPress4 = 1;// 长按标志置一
            }
        }
    }
}
