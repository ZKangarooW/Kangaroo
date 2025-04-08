#include "Drv_Key.h"

/**********全局变量声明******/
uint8_t Key_Status;//按键按下标志

/**********局部变量声明******/
float Key_Cnt1,Key_Cnt2,Key_Cnt3,Key_Cnt4;//按下时间
uint8_t Key_Flag1,Key_Flag2,Key_Flag3,Key_Flag4;//按键按下标志
uint8_t LongPress1,LongPress2,LongPress3,LongPress4;//按键长按标志

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
 * 函数原型：void Key_Scan(float dT)
 * 功    能：按键扫描
*****************************************************************
*/
void Key_Scan(float dT)
{
	/**************************************MENU键**************************************/
	if(Key1)//按下按键
	{
		if(LongPress1 == 0)//没有长按过
		{
			Key_Cnt1 += dT;//按下时间++
			Key_Flag1 = 1;//按键按下标志置一
		}
	}
	
	if(Key_Flag1)//按键被按下
	{
		if(!Key1)//抬起按键
		{   
			if(Key_Cnt1 > 0.05f && Key_Cnt1 < 1.5)//按键时间大于0.05S小于1.5S是单击
			{
				sys.SetMode_Option++;
				if(sys.SetMode_Option > 2)
					sys.SetMode_Option = 0;
				Beep_Time = 0.1;//蜂鸣器响0.1S
                Key_Status = 2.0f;//操作时常亮2S
                Twinkle_Time = 6.0f;//闪烁时间6S
			}
			Key_Flag1 = 0;//按键事件结束，等待下一次按下
			LongPress1 = 0;//长按标志清零
			Key_Cnt1 = 0;//按钮计数清零
		}
		if(Key_Cnt1 > 1.5 && Key_Cnt1 < 3.0)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress1 == 0)//如果没有一直一直长按着
			{
				LongPress1 = 1;//长按标志置一
			}
		}
	}
				
	/**************************************减键**************************************/
	if(!Key2)//按下按键
	{
		Key_Cnt2 += dT;//按下时间++
		Key_Flag2 = 1;//按键按下标志置一
	}
	if(Key_Flag2 == 1)//按键被按下
	{
		if(Key2)//抬起按键
		{   
			if(Key_Cnt2 > 0.05f && Key_Cnt2 < 1.5)//按键时间大于0.05S小于1.5S是单击
			{
				if(sys.SetMode_Option == 1)
                {
                    Temp.Set += 10;//温度加1℃
                    if(Temp.Set > Temp_MAX)//如果大于Temp_MAX℃
                        Temp.Set = Temp_MAX;//设定温度为Temp_MAX℃
                    Key_Status = 2.0f;//操作时常亮2S
                    Twinkle_Time = 6.0f;//闪烁时间6S
                }
                else if(sys.SetMode_Option == 2)
                {
                    if(Time.Set < 60)
                        Time.Set += 5;//时间加5秒钟
                    else
                        Time.Set += 60;//时间加1分钟
                    if(Time.Set > Time_MAX)//如果时间大于Time_Max
                        Time.Set = Time_MAX;//设定时间等于Time_Max
                    Key_Status = 2.0f;//操作时常亮2S
                    Twinkle_Time = 6.0f;//闪烁时间6S
                }
			}
			Key_Flag2 = 0;//按键事件结束，等待下一次按下
			Key_Cnt2 = 0;//按钮计数清零		
		}
		if(Key_Cnt2 > 1.9 && Key_Cnt2 < 2.1)//按键时间大于1.9S小于2.1S表示长按
		{
			if(sys.SetMode_Option == 1)
            {
                Temp.Set += 10;//温度加1℃
                if(Temp.Set > Temp_MAX)//如果大于Temp_MAX℃
                    Temp.Set = Temp_MAX;//设定温度为Temp_MAX℃
                Key_Status = 2.0f;//操作时常亮2S
                Twinkle_Time = 6.0f;//闪烁时间6S
            }
            else if(sys.SetMode_Option == 2)
            {
                if(Time.Set < 60)
                    Time.Set += 5;//时间加5秒钟
                else
                    Time.Set += 60;//时间加1分钟
                if(Time.Set > Time_MAX)//如果时间大于Time_Max
                    Time.Set = Time_MAX;//设定时间等于Time_Max
                Key_Status = 2.0f;//操作时常亮2S
                Twinkle_Time = 6.0f;//闪烁时间6S
            }
			Key_Flag2 = 0;//按键事件结束，等待下一次按下
			Key_Cnt2 = 1.88f;//按钮计数清零
		}
	}

	/**************************************减键**************************************/
	if(!Key3)//按下按键
	{
		Key_Cnt3 += dT;//按下时间++
		Key_Flag3 = 1;//按键按下标志置一
	}
	if(Key_Flag3 == 1)//按键被按下
	{
		if(Key3)//抬起按键
		{   
			if(Key_Cnt3 > 0.05f && Key_Cnt3 < 1.5)//按键时间大于0.05S小于1.5S是单击
			{
				if(sys.SetMode_Option == 1)
                {
                    Temp.Set -= 10;//温度减1℃
                    if(Temp.Set < Temp_MIN)//如果小于Temp_MIN℃
                        Temp.Set = Temp_MIN;//设定温度为Temp_MIN℃
                    Key_Status = 2.0f;//操作时常亮2S
                    Twinkle_Time = 6.0f;//闪烁时间6S
                }
                else if(sys.SetMode_Option == 2)
                {
                    if(Time.Set < 60)
                        Time.Set -= 5;//时间减5秒钟
                    else
                        Time.Set -= 60;//时间加1分钟
                    if(Time.Set < Time_MIN)//如果时间小于Time_MIN
                        Time.Set = Time_MIN;//设定时间等于Time_MIN
                    Key_Status = 2.0f;//操作时常亮2S
                    Twinkle_Time = 6.0f;//闪烁时间6S
                }
			}
			Key_Flag3 = 0;//按键事件结束，等待下一次按下
			Key_Cnt3 = 0;//按钮计数清零		
		}
		if(Key_Cnt3 > 1.9 && Key_Cnt3 < 2.1)//按键时间大于1.9S小于2.1S表示长按
		{
			if(sys.SetMode_Option == 1)
            {
                Temp.Set -= 10;//温度减1℃
                if(Temp.Set < Temp_MIN)//如果小于Temp_MIN℃
                    Temp.Set = Temp_MIN;//设定温度为Temp_MIN℃
                Key_Status = 2.0f;//操作时常亮2S
                Twinkle_Time = 6.0f;//闪烁时间6S
            }
            else if(sys.SetMode_Option == 2)
            {
                if(Time.Set < 60)
                    Time.Set -= 5;//时间减5秒钟
                else
                    Time.Set -= 60;//时间加1分钟
                if(Time.Set < Time_MIN)//如果时间小于Time_MIN
                    Time.Set = Time_MIN;//设定时间等于Time_MIN
                Key_Status = 2.0f;//操作时常亮2S
                Twinkle_Time = 6.0f;//闪烁时间6S
            }
			Key_Flag3 = 0;//按键事件结束，等待下一次按下
			Key_Cnt3 = 1.88f;//按钮计数清零
		}
	} 

	/**************************************Start键**************************************/
	if(!Key4)//按下按键
	{
		if(LongPress4 == 0)//没有长按过
		{
			Key_Cnt4 += dT;//按下时间++
			Key_Flag4 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag4)//按键被按下
	{
		if(Key4)//抬起按键
		{   
			if(Key_Cnt4 > 0.05f && Key_Cnt4 < 1.5)//按键时间大于0.05S小于1.5S是单击
			{
                if(sys.Run_Status == 2 || sys.Run_Status == 0)
                {
                    sys.Run_Status = 1;//系统启动
                    Temp_Val.Integral = 200;//开始就5分之一功率加热
                    LIMIT_Val = 300;//积分限幅300开始
                    SetOK_Flag = 1;//设置
                    sys.SetMode_Option = 0;
                    Beep_Time = 0.1;//蜂鸣器响0.1S
                    Key_Status = 0.0f;//操作时常亮0S
                    Twinkle_Time = 0.0f;//闪烁时间0S
                    Temp.ADDMode = 0;//速度显示模式清零
                }
                else
                {
                    sys.Run_Status = 2;//系统启动
                    Beep_Time = 0.1;//蜂鸣器响0.1S
                    Temp.ADDMode = 0;//速度显示模式清零
                }
			}
			Key_Flag4 = 0;//按键事件结束，等待下一次按下
			LongPress4 = 0;//长按标志清零
			Key_Cnt4 = 0;//按钮计数清零
		}
		if(Key_Cnt4 > 1.5 && Key_Cnt4 < 3.0)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress4 == 0)//如果没有一直一直长按着
			{
				LongPress4 = 1;//长按标志置一
			}
		}
	}
}

