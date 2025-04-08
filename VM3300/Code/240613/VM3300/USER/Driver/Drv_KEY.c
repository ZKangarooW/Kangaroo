#include "Drv_KEY.h"

/**********全局变量**********/
float Key_Status;//在操作按键时

/**********局部变量声明*******/
float Key_Cnt1, Key_Cnt2,Key_Cnt3;       // 按下时间
uint8_t Key_Flag1, Key_Flag2,Key_Flag3;   // 按键按下标志
uint8_t LongPress1, LongPress2,LongPress3; // 按键长按标志

/**
 * @brief 检测按键状态-1s
 *
 * @param dT 任务周期
 */
void Check_Press(float dT)
{
    if(Key_Status)
        Key_Status -= dT;
}

/**
 * @brief 按键扫描
 *
 * @param dT 任务周期
 */
void Key_Scan(float dT)
{
    /******************************减键******************************/
    if (KEY1 == 0) // 按下按键
    {
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
				Speed.Set -= 100;
				if(Speed.Set < Speed_MIN)
					Speed.Set = Speed_MIN;
				SetOK_Flag = 1; 
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
                Beep_Time = 0.1f;
                LongPress1 = 1; // 长按标志置一
            }
        }
    }

    /******************************加键******************************/
    if (KEY2 == KEY_DOWN) // 按下按键
    {
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
                Speed.Set += 100;
				if(Speed.Set > Speed_MAX)
					Speed.Set = Speed_MAX;
				SetOK_Flag = 1; 
                Beep_Time = 0.1f; // 蜂鸣器响0.1S
            }
            Key_Flag2 = 0;  // 按键事件结束，等待下一次按下
            LongPress2 = 0; // 长按标志位清零
            Key_Cnt2 = 0;   // 按钮计数清零
        }
        if (Key_Cnt2 > 1.5f && Key_Cnt2 < 3.0f) // 按键时间大于1.5S小于3S表示长按
        {
            if (LongPress2 == 0) // 如果没有一直长按着
            {
                Beep_Time = 0.1f;
                LongPress2 = 1; // 长按标志置一
            }
        }
    }
	
	/******************************start键******************************/
    if (KEY3 == KEY_DOWN) // 按下按键
    {
        if (LongPress3 == 0) // 没有长按过
        {
            Key_Cnt3 += dT; // 按下时间++
            Key_Flag3 = 1;  // 按键按下标志置一
        }
    }

    if (Key_Flag3) // 按键被按下
    {
        if (KEY3 == KEY_UP) // ̧抬起按键
        {
            if (Key_Cnt3 > 0.05f && Key_Cnt3 < 1.5f) // 按键时间大于0.05S小于1.5S是单击
            {
                if(sys.Run_Status)
				{
					sys.Run_Status = 0;
				}
				else
				{
					sys.Run_Status = 1;
				}
                Beep_Time = 0.1f; // 蜂鸣器响0.1S
            }
            Key_Flag3 = 0;  // 按键事件结束，等待下一次按下
            LongPress3 = 0; // 长按标志位清零
            Key_Cnt3 = 0;   // 按钮计数清零
        }
        if (Key_Cnt3 > 1.5f && Key_Cnt3 < 3.0f) // 按键时间大于1.5S小于3S表示长按
        {
            if (LongPress3 == 0) // 如果没有一直长按着
            {
                Beep_Time = 0.1f;
                LongPress3 = 1; // 长按标志置一
            }
        }
    }
}
