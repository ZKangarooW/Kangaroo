#include "Drv_KEY.h"

#if (Key_Type == 0)

/**********全局变量声明******/
float Key_Status;//按键按下标志

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
 * 功    能：矩阵按键扫描
*****************************************************************
*/
void Key_Scan(float dT)
{
	/************************************MENU键**************************************/
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
				if(sys.Run_Status == 1)
				{
					Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
				}
				else
				{
					sys.SetMode_Option++;
					if(sys.SetMode_Option > 3)
						sys.SetMode_Option = 0;
					Beep_Time = 0.1;//蜂鸣器响0.1S
					Twinkle_Time = 6;//闪烁时间6S
				}
			}
			Key_Flag1 = 0;//按键事件结束，等待下一次按下
			LongPress1 = 0;//长按标志清零
			Key_Cnt1 = 0;//按钮计数清零
		}
		if(Key_Cnt1 > 1.5 && Key_Cnt1 < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress1 == 0)//如果没有一直一直长按着
			{
				Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
				LongPress1 = 1;//长按标志置一
			}
		}
	}
	/**************************************加键**************************************/
	if(KEY2== KEY_DOWN)//按下按键
	{
		Key_Cnt2 += dT;//按下时间++
		Key_Flag2 = 1;//按键按下标志置一
	}
	if(Key_Flag2 == 1)//按键被按下
	{
		if(KEY2 == KEY_UP)//抬起按键
		{   
			if(Key_Cnt2 < 1.4)//小于1.5S是单击
			{
				if(sys.SetMode_Option == 1)//设置温度
				{
					Temp.Set += 10;//温度加1度
					if(Temp.Set > Temp_MAX)//假如温度大于Temp_MAX度时
						Temp.Set = Temp_MAX;//温度等于Temp_MAX度
					Key_Status = 2;//设置时2S不闪烁
					Twinkle_Time = 6;//闪烁时间6S
				}
				else if(sys.SetMode_Option == 2)//设置速度
				{
					Speed.Set += 10;//转速加10转
					if(Speed.Set == 10)//从零转开始最低为50转，判断是10后
						Speed.Set = 50;//设定转速为50开始
					if(Speed.Set > Speed_MAX)//假如转速大于Speed_MAX
						Speed.Set = Speed_MAX;//转速等于Speed_MAX
					Key_Status = 2;//设置时2S不闪烁
					Twinkle_Time = 6;//闪烁时间6S
				}
				else if(sys.SetMode_Option == 3)//设置时间
				{
					Time.Set += 60;//时间加1分钟
					if(Time.Set > Time_MAX)//假如时间大于Time_MAX时
						Time.Set = Time_MAX;//时间等于Time_MAX
					Key_Status = 2;//设置时2S不闪烁
					Twinkle_Time = 6;//闪烁时间6S
				}
				else
				{
					Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
				}
			}
			Key_Flag2 = 0;//按键事件结束，等待下一次按下
			Key_Cnt2 = 0;//按钮计数清零	
		}			
		if(Key_Cnt2 > 1.9 && Key_Cnt2 < 2.1)//按键时间大于1.9S小于2.1S表示长按
		{
			if(sys.SetMode_Option == 1)//设置温度
			{
				Temp.Set += 100;//温度加10度
				if(Temp.Set > Temp_MAX)//假如温度大于Temp_MAX度时
					Temp.Set = Temp_MAX;//温度等于Temp_MAX度
				Key_Status = 2;//设置时2S不闪烁
				Twinkle_Time = 6;//闪烁时间6S
			}
			else if(sys.SetMode_Option == 2)//设置速度
			{
				Speed.Set += 100;//转速加100转
				if(Speed.Set > Speed_MAX)//假如转速大于Speed_MAX
					Speed.Set = Speed_MAX;//转速等于Speed_MAX
				Key_Status = 2;//设置时2S不闪烁
				Twinkle_Time = 6;//闪烁时间6S
			}
			else if(sys.SetMode_Option == 3)//设置时间
			{
				Time.Set += 600;//时间加10分钟
				if(Time.Set > Time_MAX)//假如时间大于Time_MAX时
					Time.Set = Time_MAX;//时间等于Time_MAX
				Key_Status = 2;//设置时2S不闪烁
				Twinkle_Time = 6;//闪烁时间6S
			}
			else
			{
				Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
			}
			Key_Flag2 = 0;//按键事件结束，等待下一次按下
			Key_Cnt2 = 1.4;//按钮计数从1.4s开始
		}
	}
	
	/**************************************减键**************************************/
	if(KEY3 == KEY_DOWN)//按下按键
	{
		Key_Cnt3 += dT;//按下时间++
		Key_Flag3 = 1;//按键按下标志置一
	}
	if(Key_Flag3 == 1)//按键被按下
	{
		if(KEY3 == KEY_UP)//抬起按键
		{   
			if(Key_Cnt3 < 1.4)/*单击*///小于1.5S是单击
			{
				if(sys.SetMode_Option == 1)//设置温度
				{
					Temp.Set -= 10;//温度减1度
					if(Temp.Set < 0)//假如温度小于0度时
						Temp.Set = 0;//温度等于0度
					Key_Status = 2;//设置时2S不闪烁
					Twinkle_Time = 6;//闪烁时间6S
				}
				else if(sys.SetMode_Option == 2)//设置速度
				{
					Speed.Set -= 10;//转速减10转
					if(Speed.Set < 50)//假如转速小于50时
						Speed.Set = 0;//转速等于0
					Key_Status = 2;//设置时2S不闪烁
					Twinkle_Time = 6;//闪烁时间6S
				}
				else if(sys.SetMode_Option == 3)//设置时间
				{
					Time.Set -= 60;//时间减1分钟
					if(Time.Set < 0)//假如时间小于0时
						Time.Set = 0;//时间等于0
					Key_Status = 2;//设置时2S不闪烁
					Twinkle_Time = 6;//闪烁时间6S
				}
				else
				{
					Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
				}
			}
			Key_Flag3 = 0;//按键事件结束，等待下一次按下
			Key_Cnt3 = 0;//按钮计数清零		
		}
		if(Key_Cnt3 > 1.9 && Key_Cnt3 < 2.1)//按键时间大于1.9S小于2.1S表示长按
		{
			if(sys.SetMode_Option == 1)//设置温度
			{
				Temp.Set -= 100;//温度减10度
				if(Temp.Set < 0)//假如温度小于0度时
					Temp.Set = 0;//温度等于0度
				Key_Status = 2;//设置时2S不闪烁
				Twinkle_Time = 6;//闪烁时间6S
			}
			else if(sys.SetMode_Option == 2)//设置速度
			{
				Speed.Set -= 100;//转速减100转
				if(Speed.Set < 50)//假如转速小于50时
					Speed.Set = 0;//转速等于0
				Key_Status = 2;//设置时2S不闪烁
				Twinkle_Time = 6;//闪烁时间6S
			}
			else if(sys.SetMode_Option == 3)//设置时间
			{
				Time.Set -= 600;//时间减10分钟
				if(Time.Set < 0)//假如时间小于0时
					Time.Set = 0;//时间等于0
				Key_Status = 2;//设置时2S不闪烁
				Twinkle_Time = 6;//闪烁时间6S
			}
			else
			{
				Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
			}
			Key_Flag3 = 0;//按键事件结束，等待下一次按下
			Key_Cnt3 = 1.4;//按钮计数从1.5s开始	
		}
	}
	
	/**************************************Start键**************************************/
	if(KEY4== KEY_DOWN)//按下按键
	{	
		if(LongPress4 == 0)//没有长按过
		{
			Key_Cnt4 += dT;//按下时间++
			Key_Flag4 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag4 == 1)//按键被按下
	{
		if(KEY4 == KEY_UP)//抬起按键
		{   
			if(Key_Cnt4 > 0.1 && Key_Cnt4 < 1.5)//小于1.5S是单击
			{
				if(sys.Run_Status != 1 && (Speed.Set || Temp.Set))//系统没启动的话
				{
					sys.Run_Status = 1;//启动系统
					Speed_Val.Integral = 43;//电器起步
					sys.SetMode_Option = 0;//设定模式设置为0
					Temp_Val.Integral = 0;//加热的积分清零
				}
				else//系统启动的话
				{
					Speed.ADDMode = 1;//进入减速模式
					Speed.Ctrl = 0;//将控制速度设置为0
				}
				Beep_Time = 0.1;//蜂鸣器响0.1S
				Twinkle_Time = 0;//闪烁时间6S
				sys.SetMode_Option = 0;
			}
			Key_Flag4 = 0;//按键事件结束，等待下一次按下
			LongPress4 = 0;//长按标志清零
			Key_Cnt4 = 0;//按钮计数清零		
		}
		if(Key_Cnt4 > 1.5 && Key_Cnt4 < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress4 == 0)//如果没有一直一直长按着
			{
				Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
				LongPress4 = 1;//长按标志置一
			}
		}
	}
}
#endif
