#include "Drv_KEY.h"

/**********局部变量声明******/
float Key_Cnt1,Key_Cnt2,Key_Cnt3;//按下时间
uint8_t Key_Flag1,Key_Flag2,Key_Flag3;//按键按下标志
uint8_t LongPress1,LongPress2,LongPress3;//按键长按标志

/**
 * @brief 按键扫描
 * 
 * @param dT 执行周期
 */
void Key_Scan(float dT)
{
	/************************************P键**************************************/
	if(KEY1 == KEY_DOWN)//按下按键
	{
		if(LongPress1 == 0)//没有长按过
		{
			Key_Cnt1 += dT;//按下时间++
			Key_Flag1 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag1 == 1)//按键被按下
	{
		if(KEY1 == KEY_UP)//抬起按键
		{   
			if(Key_Cnt1 > 0.1 && Key_Cnt1 < 1.5)//小于1.5S是单击
			{
                if (PMode.Status == 1) // 如果打开P模式
                {
                    if(Pmode_Twinkle_Time)
                    {
                        PMode.Status = 0; // 关闭P模式
                        PMode.Mode = 0;   // 记忆模式下，因为单按只能进入P模式
                        PMode.Option = 0;
                        Param_Read();//读取参数
                        Pmode_Twinkle_Time = Speed_Twinkle_Time = Temp_Twinkle_Time = Time_Twinkle_Time = 0;
                    }
                    else
                    {
                        Speed_Twinkle_Time = Temp_Twinkle_Time = Time_Twinkle_Time = 0;
                        Pmode_Twinkle_Time = 2.0f;
                    }
                }
                else if (PMode.Status == 0)
                {
                    PMode.Status = 1; // 打开P模式
                    PMode.Mode = 0;   // 记忆模式下，因为单按只能进入P模式
                    PMode.Option = 1;
                    Param_Read();   // 读取参数
                    Speed_Twinkle_Time = Temp_Twinkle_Time = Time_Twinkle_Time = 0;
                    Pmode_Twinkle_Time = 2.0f;
                }
                Beep_Time = 0.1f; // 蜂鸣器响0.1S
			}
			Key_Flag1 = 0;//按键事件结束，等待下一次按下
			LongPress1 = 0;//长按标志清零
			Key_Cnt1 = 0;//按钮计数清零
		}
		if(Key_Cnt1 > 1.5 && Key_Cnt1 < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress1 == 0)//如果没有一直一直长按着
			{
				if (PMode.Mode) // 如果打开梯度
                {
                    PMode.Status = 1; // 打开P模式
                    PMode.Mode = 0;   // 记忆模式下，因为单按只能进入P模式
                    PMode.Option = 1;
                    PMode.P1 = 0;
                    PMode.P2 = 0;
                    Param_Read(); // 读取参数
                    Pmode_Twinkle_Time = 2.0f;
                }
                else
                {
                    PMode.Status = 2; // 打开P模式,选择梯度，用于后面的闪烁
                    PMode.Mode = 1;   // 记忆模式下，因为单按只能进入P模式
                    PMode.P1 = 1;
                    PMode.P2 = 9;
                    PMode.Option = PMode.P1;
                    Param_Read();   // 读取参数
                }
                Beep_Time = 0.1f; // 蜂鸣器响0.1S
				LongPress1 = 1;//长按标志置一
			}
		}
	}
    
	/**************************************锁定键**************************************/
	if(KEY2 == KEY_DOWN)//按下按键
	{	
		if(LongPress2 == 0)//没有长按过
		{
			Key_Cnt2 += dT;//按下时间++
			Key_Flag2 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag2 == 1)//按键被按下
	{
		if(KEY2 == KEY_UP)//抬起按键
		{   
			if(Key_Cnt2 > 0.1 && Key_Cnt2 < 1.5)//小于1.5S是单击
			{
				Beep_Time = 0.1;//蜂鸣器响0.1S
			}
			Key_Flag2 = 0;//按键事件结束，等待下一次按下
			LongPress2 = 0;//长按标志清零
			Key_Cnt2 = 0;//按钮计数清零		
		}
		if(Key_Cnt2 > 1.5 && Key_Cnt2 < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress2 == 0)//如果没有一直一直长按着
			{
				Beep_Flash = 2;//“滴滴”两下用于误触
				LongPress2 = 1;//长按标志置一
			}
		}
	}
	/**************************************定时键**************************************/
	if(KEY3 == KEY_DOWN)//按下按键
	{	
		if(LongPress3 == 0)//没有长按过
		{
			Key_Cnt3 += dT;//按下时间++
			Key_Flag3 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag3 == 1)//按键被按下
	{
		if(KEY3 == KEY_UP)//抬起按键
		{   
			if(Key_Cnt3 > 0.1 && Key_Cnt3 < 1.5)//小于1.5S是单击
			{
                if(sys.SetMode_Option != 3)
				{
					sys.SetMode_Option = 3;
					Time_Twinkle_Time = 6.0f;//闪烁时间6S
					Temp_Twinkle_Time = 0;
					Speed_Twinkle_Time = 0;
                    SpeedSet_Flag = 1;//进入速度设定
                    TempSet_Flag = 1;//进入速度设定
				}
				else
				{
					sys.SetMode_Option = 0;
					EC11A[1].EC11A_Knob = EC11A[0].EC11A_Knob = 0;
					Time_Twinkle_Time = 0;
					TimeSet_Flag = 1;//进入时间设定
				}
                Beep_Time = 0.1;//蜂鸣器响0.1S
			}
			Key_Flag3 = 0;//按键事件结束，等待下一次按下
			LongPress3 = 0;//长按标志清零
			Key_Cnt3 = 0;//按钮计数清零		
		}
		if(Key_Cnt3 > 1.5 && Key_Cnt3 < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress3 == 0)//如果没有一直一直长按着
			{
				Beep_Flash = 2;//“滴滴”两下用于误触
				LongPress3 = 1;//长按标志置一
			}
		}
	}
    
    if(HAL_GPIO_ReadPin(Key_POR_GPIO_Port,Key_POR_Pin) == KEY_DOWN)//按下按键
	{	
		sys.Display = 1;
	}
    else
    {
        sys.Display = 0;
    }
}
