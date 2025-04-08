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
	if(Key1 == Key_Down)//按下按键
	{
		if(Protect)
		{
			return;
		}
		if(LongPress1 == 0)//没有长按过
		{
			Key_Cnt1 += dT;//按下时间++
			Key_Flag1 = 1;//按键按下标志置一
		}
	}
	
	if(Key_Flag1)//按键被按下
	{
		if(Key1 == Key_Up)//抬起按键
		{   
			if(Key_Cnt1 > 0.05f && Key_Cnt1 < 1.5)//按键时间大于0.05S小于1.5S是单击
			{
                if(sys.Run_Status == 0 && Speed.Display_Rel != 0)
                {
                    Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
                }
                else
                {
                    #if(Type == 0)
                    sys.SetMode_Option++;
                    if(sys.SetMode_Option > 2)
                        sys.SetMode_Option = 0;
                    #elif(Type == 1)
                    sys.SetMode_Option++;
                    if(sys.SetMode_Option > 3)
                        sys.SetMode_Option = 0;
                    #endif
                    Twinkle_Time = 6.0f;//闪烁时间6S
                    Beep_Time = 0.1;//蜂鸣器响0.1S
                }
			}
			Key_Flag1 = 0;//按键事件结束，等待下一次按下
			LongPress1 = 0;//长按标志清零
			Key_Cnt1 = 0;//按钮计数清零
		}
		if(Key_Cnt1 > 1.5 && Key_Cnt1 < 3.0)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress1 == 0)//如果没有一直一直长按着
			{
                Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
				LongPress1 = 1;//长按标志置一
			}
		}
	}
				
	/**************************************加键**************************************/
	if(Key2 == Key_Down)//按下按键
	{
		if(Protect)
		{
			return;
		}
		Key_Cnt2 += dT;//按下时间++
		Key_Flag2 = 1;//按键按下标志置一
	}
	if(Key_Flag2 == 1)//按键被按下
	{
		if(Key2 == Key_Up)//抬起按键
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
					#if(Type == 0)
					Time.Set += 60;//时间加1分钟
					if(Time.Set > Time_MAX)//如果时间大于Time_Max
						Time.Set = Time_MAX;//设定时间等于Time_Max
					Key_Status = 2.0f;//操作时常亮2S
					Twinkle_Time = 6.0f;//闪烁时间6S
					#elif(Type == 1)
					if(!Speed.Set)
						Speed.Set += 100;//速度加100
					else
						Speed.Set += 50;//速度加50
					if(Speed.Set > Speed_MAX)//如果速度大于Speed_MAX
						Speed.Set = Speed_MAX;//设定速度等于Speed_MAX
					Key_Status = 2.0f;//操作时常亮2S
					Twinkle_Time = 6.0f;//闪烁时间6S
					#endif
				}
				else if(sys.SetMode_Option == 3)
				{
					Time.Set += 60;//时间加1分钟
					if(Time.Set > Time_MAX)//如果时间大于Time_Max
						Time.Set = Time_MAX;//设定时间等于Time_Max
					Key_Status = 2.0f;//操作时常亮2S
					Twinkle_Time = 6.0f;//闪烁时间6S
				}
                else
                {
                    Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
                }
			}
			Key_Flag2 = 0;//按键事件结束，等待下一次按下
			Key_Cnt2 = 0;//按钮计数清零		
		}
		if(Key_Cnt2 > 1.9 && Key_Cnt2 < 2.1)//按键时间大于1.9S小于2.1S表示长按
		{
			if(sys.SetMode_Option == 1)
			{
				Temp.Set += 100;//温度加10℃
				if(Temp.Set > Temp_MAX)//如果大于Temp_MAX℃
					Temp.Set = Temp_MAX;//设定温度为Temp_MAX℃
				Key_Status = 2.0f;//操作时常亮2S
				Twinkle_Time = 6.0f;//闪烁时间6S
			}
			else if(sys.SetMode_Option == 2)
			{
				#if(Type == 0)
				Time.Set += 1800;//时间加30分钟
				if(Time.Set > Time_MAX)//如果时间大于Time_Max
					Time.Set = Time_MAX;//设定时间等于Time_Max
				Key_Status = 2.0f;//操作时常亮2S
				Twinkle_Time = 6.0f;//闪烁时间6S
				#elif(Type == 1)
				Speed.Set += 100;//速度加100
				if(Speed.Set > Speed_MAX)//如果速度大于Speed_MAX
					Speed.Set = Speed_MAX;//设定速度等于Speed_MAX
				Key_Status = 2.0f;//操作时常亮2S
				Twinkle_Time = 6.0f;//闪烁时间6S
				#endif
			}
			else if(sys.SetMode_Option == 3)
			{
				Time.Set += 1800;//时间加30分钟
				if(Time.Set > Time_MAX)//如果时间大于Time_Max
					Time.Set = Time_MAX;//设定时间等于Time_Max
				Key_Status = 2.0f;//操作时常亮2S
				Twinkle_Time = 6.0f;//闪烁时间6S
			}
            else
            {
                Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
            }
			Key_Flag2 = 0;//按键事件结束，等待下一次按下
			Key_Cnt2 = 1.5;//按钮计数清零
		}
	}

	/**************************************减键**************************************/
	if(Key3 == Key_Down)//按下按键
	{
		if(Protect)
		{
			return;
		}
		Key_Cnt3 += dT;//按下时间++
		Key_Flag3 = 1;//按键按下标志置一
	}
	if(Key_Flag3 == 1)//按键被按下
	{
		if(Key3 == Key_Up)//抬起按键
		{   
			if(Key_Cnt3 > 0.05f && Key_Cnt3 < 1.5)//按键时间大于0.05S小于1.5S是单击
			{
				if(sys.SetMode_Option == 1)
				{
					if(Temp.Set)
						Temp.Set -= 10;//温度减1℃
					if(Temp.Set <= Temp_MIN)//如果小于等于Temp_MIN℃
						Temp.Set = Temp_MIN;//设定温度为Temp_MIN℃
					Key_Status = 2.0f;//操作时常亮2S
					Twinkle_Time = 6.0f;//闪烁时间6S
				}
				else if(sys.SetMode_Option == 2)
				{
					#if(Type == 0)
					if(Time.Set)
						Time.Set -= 60;//时间减1分钟
					if(Time.Set <= Time_MIN)//如果时间小于等于Time_MIN
						Time.Set = Time_MIN;//设定时间等于Time_MIN
					Key_Status = 2.0f;//操作时常亮2S
					Twinkle_Time = 6.0f;//闪烁时间6S
					#elif(Type == 1)
					if(Speed.Set)
						Speed.Set -= 50;//速度减50
					if(Speed.Set < Speed_MIN)//如果速度小于Speed_MIN
						Speed.Set = 0;//设定速度等于0
					Key_Status = 2.0f;//操作时常亮2S
					Twinkle_Time = 6.0f;//闪烁时间6S
					#endif
				}
				else if(sys.SetMode_Option == 3)
				{
					if(Time.Set)
						Time.Set -= 60;//时间减1分钟
					if(Time.Set <= Time_MIN)//如果时间小于等于Time_MIN
						Time.Set = Time_MIN;//设定时间等于Time_MIN
					Key_Status = 2.0f;//操作时常亮2S
					Twinkle_Time = 6.0f;//闪烁时间6S
				}
                else
                {
                    Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
                }
			}
			Key_Flag3 = 0;//按键事件结束，等待下一次按下
			Key_Cnt3 = 0;//按钮计数清零		
		}
		if(Key_Cnt3 > 1.9 && Key_Cnt3 < 2.1)//按键时间大于1.9S小于2.1S表示长按
		{
			if(sys.SetMode_Option == 1)
			{
				if(Temp.Set>100)//温度大于100
					Temp.Set -= 100;//温度减10℃
				else if(Temp.Set > 0 && Temp.Set<=100)
					Temp.Set -= 10;//温度减1℃
				if(Temp.Set <= Temp_MIN)//如果小于等于Temp_MIN℃
					Temp.Set = Temp_MIN;//设定温度为Temp_MIN℃
				Key_Status = 2.0f;//操作时常亮2S
				Twinkle_Time = 6.0f;//闪烁时间6S
			}
			else if(sys.SetMode_Option == 2)
			{
				#if(Type == 0)
				if(Time.Set>1800)
					Time.Set -= 1800;//时间减30分钟
				else if(Time.Set > 600 && Time.Set <= 1800)
					Time.Set -= 600;//时间减10分钟
				else if(Time.Set >= 60 && Time.Set <= 600)
					Time.Set -= 60;//时间减1分钟
				if(Time.Set <= Time_MIN)//如果时间小于等于Time_MIN
					Time.Set = Time_MIN;//设定时间等于Time_MIN
				Key_Status = 2.0f;//操作时常亮2S
				Twinkle_Time = 6.0f;//闪烁时间6S
				#elif(Type == 1)
				if(Speed.Set > 100)
					Speed.Set -= 100;//速度减100
				else if(Speed.Set > 50 && Speed.Set <= 100)
					Speed.Set -= 50;//速度减50
				if(Speed.Set < Speed_MIN)//如果速度小于Speed_MIN
					Speed.Set = 0;//设定速度等于0
				Key_Status = 2.0f;//操作时常亮2S
				Twinkle_Time = 6.0f;//闪烁时间6S
				#endif
			}
			else if(sys.SetMode_Option == 3)
			{
				if(Time.Set>1800)
					Time.Set -= 1800;//时间减30分钟
				else if(Time.Set > 600 && Time.Set <= 1800)
					Time.Set -= 600;//时间减10分钟
				else if(Time.Set >= 60 && Time.Set <= 600)
					Time.Set -= 60;//时间减1分钟
				if(Time.Set <= Time_MIN)//如果时间小于等于Time_MIN
					Time.Set = Time_MIN;//设定时间等于Time_MIN
				Key_Status = 2.0f;//操作时常亮2S
				Twinkle_Time = 6.0f;//闪烁时间6S
			}
            else
            {
                Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
            }
			Key_Flag3 = 0;//按键事件结束，等待下一次按下
			Key_Cnt3 = 1.5;//按钮计数清零
		}
	} 

	/**************************************Start键**************************************/
	if(Key4 == Key_Down)//按下按键
	{
		if(Protect)
		{
			return;
		}
		if(LongPress4 == 0)//没有长按过
		{
			Key_Cnt4 += dT;//按下时间++
			Key_Flag4 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag4)//按键被按下
	{
		if(Key4 == Key_Up)//抬起按键
		{   
			if(Key_Cnt4 > 0.05f && Key_Cnt4 < 1.5)//按键时间大于0.05S小于1.5S是单击
			{
				if(sys.Run_Status)
				{
					sys.Run_Status = 0;
					Speed.DisplayMode = 2;//降速显示
                    sys.SetMode_Option = 0;
                    SetOK_Flag = 1;
					Beep_Time = 0.1;//蜂鸣器响0.1S
				}
				else
				{
					if(Speed.Set || Temp.Set)//如果3个功能都不工作，不开启系统
					{
						sys.Run_Status = 1;
						Speed_Val.Integral = 25;
						Judge_TempMode();//温度显示模式检测
						Judge_SpeedMode();//速度显示模式检测
						sys.SetMode_Option = 0;
                        SetOK_Flag = 1;
						Beep_Time = 0.1;//蜂鸣器响0.1S
					}
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
                Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
				LongPress4 = 1;//长按标志置一
			}
		}
	}
}

