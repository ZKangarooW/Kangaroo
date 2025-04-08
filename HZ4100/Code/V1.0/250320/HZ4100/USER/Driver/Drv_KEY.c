#include "Drv_KEY.h"

/**********局部变量声明*******/
float Key_Cnt1, Key_Cnt2;       // 按下时间
uint8_t Key_Flag1, Key_Flag2;   // 按键按下标志
uint8_t LongPress1, LongPress2; // 按键长按标志

/**********全局变量声明*******/
uint8_t Lock_Switch, Shake_Switch; // 锁定和抖动开关
float Lock_Alarm;//锁定报警
    
/**
 * @brief 按键扫描
 *
 * @param dT 任务周期
 */
void Key_Scan(float dT)
{
    /******************************锁定键******************************/
    if (KEY1 == KEY_DOWN) // 按下按键
    {
		 if (Shake_Alarm)
				return;
        if (LongPress1 == 0) // 没有长按过
        {
            Key_Cnt1 += dT; // 按下时间++
            Key_Flag1 = 1;  // 按键按下标志置一
        }
    }

    if (Key_Flag1) // 按键被按下
    {
        if (KEY1 == KEY_UP) // 抬起按键
        {
            if (Key_Cnt1 > 0.05f && Key_Cnt1 < 1.5f) // 按键时间大于0.05S小于1.5S是单击
            {
				if (Lock_Switch)
				{
					Lock_Switch = 0;
				}
				else
				{
					Lock_Switch = 1;
				}
				Beep_Time = 0.1f; // 蜂鸣器响0.1S
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
                LongPress1 = 1; // 长按标志置一
            }
        }
    }

    /******************************抖动键******************************/
    if (KEY2 == KEY_DOWN) // 按下按键
    {
		if (Shake_Alarm)
		return;
        if (LongPress2 == 0) // 没有长按过
        {
            Key_Cnt2 += dT; // 按下时间++
            Key_Flag2 = 1;  // 按键按下标志置一
        }
    }

    if (Key_Flag2) // 按键被按下
    {
        if (KEY2 == KEY_UP) // ̧抬起按键
        {
            if (Key_Cnt2 > 0.05f && Key_Cnt2 < 1.5f) // 按键时间大于0.05S小于1.5S是单击
            {
				if (Lock_Switch)
				{
					Beep_Flash = 2;
                    Lock_Alarm = 2;
				}
				else
				{
					if (Shake_Switch)
					{
						Shake_Switch = 0;
					}
					else
					{
						Shake_Switch = 1;
					}
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
}
