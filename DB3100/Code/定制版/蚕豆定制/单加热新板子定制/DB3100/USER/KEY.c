#include "KEY.h"

/**********全局变量**********/
uint16_t run_mode = 0;//运行模式
uint16_t Key_Status;//在操作按键时

/**********局部变量**********/
float Key_Cnt1,Key_Cnt2,Key_Cnt3,Key_Cnt4,Key_Cnt5;//按下时间
uint8_t Key_Flag1,Key_Flag2,Key_Flag3,Key_Flag4,Key_Flag5;//按键按下标志
uint8_t LongPress1,LongPress2,LongPress3,LongPress4,LongPress5;//按键长按标志
float UPPress_Time, DownPress_Time;//长按的时间

/*
*****************************************************************
 * 函数原型： void Key_Handle(float dT)
 * 功    能： 按键功能
*****************************************************************
*/
void Key_Handle(float dT)
{
    /**************************************减键**************************************/
    if(!Key3)//按下按键
    {
        DownPress_Time += dT;
        Key_Cnt3 += dT; // 按下时间++
        Key_Flag3 = 1;  // 按键按下标志置一
    }
    if (Key_Flag3 == 1) // 按键被按下
    {
        if(Key3)//抬起按键
        {
            if (Key_Cnt3 < 1.5f) // 按键时间小于1.5S是单击
            {
				if(set_time >= 600)
                    set_time -= 600;//时间减10分钟
                rel_time = set_time;//把设定时间赋值给控制时间
                time_disable = 0;//开启倒计时
                Beep_Time = 0.1;//蜂鸣器响0.1S
                Key_Status = Run_Time;
            }
            Key_Flag3 = 0; // 按键事件结束，等待下一次按下
            Key_Cnt3 = 0;  // 按钮计数清零
        }
        else if (Key_Cnt3 > 1.9f && Key_Cnt3 < 2.1f) // 按键时间大于1.9S小于2.1S表示长按
        {
            if(set_time >= 600)
                set_time -= 600;//时间减10分钟
            rel_time = set_time;//把设定时间赋值给控制时间
            time_disable = 0;//开启倒计时
            Key_Status = Run_Time;
            Key_Cnt3 = 1.88f;
            Key_Flag3 = 0; // 按键事件结束，等待下一次按下
        }
    }
    else
    {
        DownPress_Time = 0;
        Key_Cnt3 = 0; // 按键计数清零
    }
   
    /******************************加键******************************/
    if(!Key2)//按下按键
    {
        UPPress_Time += dT; // 长按时间加加
        Key_Cnt2 += dT;     // 按下时间++
        Key_Flag2 = 1;      // 按键按下标志置一
    }
    if (Key_Flag2) // 按键被按下
    {
        if(Key2)//抬起按键
        {
            if (Key_Cnt2 < 1.5f) // 按键时间小于1.5S是单击
            {
                set_time += 600;//时间减10分钟
                if(set_time > 28800)//最高可定时8小时
                    set_time = 28800;
                rel_time = set_time;//把设定时间赋值给控制时间
                time_disable = 0;//开启倒计时
                Key_Status = Run_Time;
                Beep_Time = 0.1;//蜂鸣器响0.1S
            }
            Key_Flag2 = 0; // 按键事件结束，等待下一次按下
            Key_Cnt2 = 0;  // 按钮计数清零
        }
        else if (Key_Cnt2 > 1.9f && Key_Cnt2 < 2.1f) // 按键时间大于1.9S小于2.1S表示长按
        {
            set_time += 600;//时间减10分钟
                if(set_time > 28800)//最高可定时8小时
                    set_time = 28800;
            rel_time = set_time;//把设定时间赋值给控制时间
                time_disable = 0;//开启倒计时
            Key_Cnt2 = 1.88f;
            Key_Status = Run_Time;
            Key_Flag2 = 0; // 按键事件结束，等待下一次按下
        }
    }
    else
    {
        UPPress_Time = 0;
        Key_Cnt2 = 0; // 按键计数清零
    }
    
    /*****************************菜单键*************************************/ 
    if(!Key1)//按下按键
	{
		if(LongPress1 == 0)//没有长按过
		{ 
			Key_Cnt1 += dT;//按下时间++
			Key_Flag1 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag1)//按键被按下
	{
		if(Key1)//抬起按键
		{   
			if(Key_Cnt1 > 0.05f && Key_Cnt1 < 1.5)//按键时间大于0.05S小于1.5S是单击
			{
                set_temp=990;//开机设置设定温度65℃
                SetOK_Flag = 1;
                Run_Status = 1; //系统启动         
                ADD_Mode = 0;//加热状态清零
                Key_Status = Run_Time;
                Beep_Time = 0.1;//蜂鸣器响0.1S
			}
			Key_Flag1 = 0;//按键事件结束，等待下一次按下
			LongPress1 = 0;//长按标志清零
			Key_Cnt1 = 0;//按钮计数清零
		}
		if(Key_Cnt1 > 1.5 && Key_Cnt1 < 3.0)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress1 == 0)//如果没有一直一直长按着
			{
                Key_Status = Run_Time;
				Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
				LongPress1 = 1;//长按标志置一
			}
		}
	}

/*******************************P键*************************************/ 
    if(!Key5)//按下按键
	{
		if(LongPress5 == 0)//没有长按过
		{
			Key_Cnt5 += dT;//按下时间++
			Key_Flag5 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag5)//按键被按下
	{
		if(Key5)//抬起按键
		{   
			if(Key_Cnt5 > 0.05f && Key_Cnt5 < 1.5)//按键时间大于0.05S小于1.5S是单击
			{
                set_temp=650;//开机设置设定温度65℃
                SetOK_Flag = 1;
                Key_Status = Run_Time;
                Run_Status = 1; //系统启动         
                ADD_Mode = 0;//加热状态清零
                Beep_Time = 0.1;//蜂鸣器响0.1S
			}
			Key_Flag5 = 0;//按键事件结束，等待下一次按下
			LongPress5 = 0;//长按标志清零
			Key_Cnt5 = 0;//按钮计数清零
		}
		if(Key_Cnt5 > 1.5 && Key_Cnt5 < 3.0)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress5 == 0)//如果没有一直一直长按着
			{
                Key_Status = Run_Time;
				Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
				LongPress5 = 1;//长按标志置一
			}
		}
	}    

    
/******************************开始/停止********************************/  
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
                Key_Status = Run_Time;
                if(set_time)
                {
                    rel_time = set_time;//把设定时间赋值给控制时间
                    if(time_disable)
                    {
                        time_disable = 0;//关闭倒计时
                    }
                    else
                    {
                        time_disable = 1;//开启倒计时
                    }
                }
                else
                    time_disable = 0;//开启倒计时
                Beep_Time = 0.1;//蜂鸣器响0.1S
			}
			Key_Flag4 = 0;//按键事件结束，等待下一次按下
			LongPress4 = 0;//长按标志清零
			Key_Cnt4 = 0;//按钮计数清零
		}
		if(Key_Cnt4 > 1.5 && Key_Cnt4 < 3.0)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress4 == 0)//如果没有一直一直长按着
			{
                Key_Status = Run_Time;
                Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
				LongPress4 = 1;//长按标志置一
			}
		}
	}
}

/*
*****************************************************************
 * 函数原型：void Check_Key(void)
 * 功    能：检测按键状态-1s
*****************************************************************
*/
void Check_Key(void)
{
    if(Run_Status)
    {
        if(Key_Status)
            Key_Status--;
        if(Key_Status == 0)
        {
            set_time=0;//开机设置设定时间为0
            set_temp=0;//开机设置设定温度0℃
            Run_Status = 0;
            time_disable = 0;//关闭倒计时
            Key_Status = Run_Time;
            ADD_Mode = 0;
            Beep_Flash = 30;//无效按键时蜂鸣器“滴滴”
            SetOK_Flag = 1;
        }
    }
        
}
