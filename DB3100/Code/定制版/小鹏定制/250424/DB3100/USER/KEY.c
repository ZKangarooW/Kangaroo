#include "KEY.h"

/**********全局变量**********/
uint16_t run_mode = 0;//运行模式
uint8_t Key_Status;//在操作按键时

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
                if(Param.Mode_Val)//在B模式下，并且启动定时
                {
                    Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
                }
                else
                {
                    if(Run_Status > 0) //运行中不能设置
                    {
                        Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
                    }
                    else
                    {
                        if(Select_Option == 2)//在设置温度选项
                        {
                            set_temp--;//温度--；
                            if(set_temp < 0)//如果设定温度小于0时（单加热只能自动降温）
                            {
                                set_temp = 0;//将设定温度保持在0
                            }
                            Twinkle_On = 6000;//闪烁倒计时，如果停止按键设置，6S后停止闪烁
                            Key_Status = 2;//按键操作时不闪烁，2s后闪烁
                        }
                        else if(Select_Option == 3)//在设置时间选项
                        {
                            if(time_status == 0)//在秒单位模式下
                            {
                                if(set_time)
                                    set_time -= 5;//时间减5s
                                if(set_time < 5)//小于5s的设定值时
                                {
                                    set_time = 0;
                                    time_Last = 1;//跳出倒计时
                                    SetTime_State = 1;//设定时间显示“----”
                                }  				
                            }
                            else//在分为单位的模式下
                                set_time -= 60;//时间减1分钟
                            Twinkle_On = 6000;//闪烁倒计时，如果停止按键设置，6S后停止闪烁
                            Key_Status = 2;//按键操作时不闪烁，2s后闪烁
                        }
                        else if(Select_Option == 1)//在设置模式选项
                        {
                            run_mode--;//P记忆位置--
                            if(run_mode < 1)//小于1时返回到第九个位置
                            {
                                run_mode = 1;
                            }
                            Flash_Read((uint8_t *)(&Param),sizeof(Param));
                            set_time=Param.P_Param[run_mode][1];//开机设置设定时间为20min
                            set_temp=Param.P_Param[run_mode][0];//开机设置设定温度37℃
                            if(set_time > 0 )
                            {
                                SetTime_State = 0;//设定时间退出显示“----”
                                time_Last = 0;
                            }
                            else
                            {
                                SetTime_State = 1;//设定时间显示“----”
                                time_Last = 1;
                            }
                            SetOK_Flag = 1;
                            Twinkle_On = 6000;//闪烁倒计时，如果停止按键设置，6S后停止闪烁
                            Key_Status = 2;//按键操作时不闪烁，2s后闪烁
                        }
                        else
                        {
                            Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
                        }
                    }
                }
            }
            Key_Flag3 = 0; // 按键事件结束，等待下一次按下
            Key_Cnt3 = 0;  // 按钮计数清零
        }
        else if (Key_Cnt3 > 1.9f && Key_Cnt3 < 2.1f) // 按键时间大于1.9S小于2.1S表示长按
        {
            if(Param.Mode_Val)//在B模式下，并且启动定时
            {
                Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
            }
            else
            {
                if(Run_Status > 0) //运行中不能设置
                {
                    Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
                }
                else
                {
                    if(Select_Option == 2)//在设置温度选项
                    {
                        if (DownPress_Time > 5.0f)
                        {
                            set_temp -= 10;
                        }
                        else
                        {
                            set_temp--;
                        }
                        if(set_temp < 0)//如果设定温度小于0时（单加热只能自动降温）
                        {
                            set_temp = 0;//将设定温度保持在0
                        }
                        Twinkle_On = 6000;//闪烁倒计时，如果停止按键设置，6S后停止闪烁
                        Key_Status = 2;//按键操作时不闪烁，2s后闪烁
                        if (DownPress_Time > 5.0f)
                        {
                            Key_Cnt3 = 1.82f; // 长按按键时间复位
                        }
                        else
                        {
                            Key_Cnt3 = 1.88f;
                        }
                    }
                    else if(Select_Option == 3)//在设置时间选项
                    {
                        if (DownPress_Time > 5.0f)
                        {
                            if(time_status == 0)//在秒单位模式下
                            {
                                if(set_time)
                                    set_time -= 60;//时间减5s
                                if(set_time < 5)//小于5s的设定值时
                                {
                                    set_time = 0;
                                    time_Last = 1;//跳出倒计时
                                    SetTime_State = 1;//设定时间显示“----”
                                }   
                            }
                            else
                            {
                                if(set_time <  7200)
                                {
                                    if (set_time % 60)
                                        set_time = 3600;
                                    else
                                        set_time -= 600;
                                }
                                else
                                    set_time -= 600;
                            }
                        }
                        else
                        {
                            if(time_status == 0)//在秒单位模式下
                            {
                                if(set_time)
                                    set_time -= 5;//时间减5s
                                if(set_time < 5)//小于5s的设定值时
                                {
                                    set_time = 0;
                                    time_Last = 1;//跳出倒计时
                                    SetTime_State = 1;//设定时间显示“----”
                                }   
                            }
                            else
                            {
                                if(set_time<  7200)
                                {
                                    if (set_time % 60)
                                        set_time = 3600;
                                    else
                                        set_time -= 60;
                                }
                                else
                                {
                                    set_time -= 60;
                                }
                            }
                        }
                        Twinkle_On = 6000;//闪烁倒计时，如果停止按键设置，6S后停止闪烁
                        Key_Status = 2;//按键操作时不闪烁，2s后闪烁
                        if (DownPress_Time > 5.0f)
                        {
                            Key_Cnt3 = 1.82f; // 长按按键时间复位
                        }
                        else
                        {
                            Key_Cnt3 = 1.88f;
                        }
                    }
                    else if(Select_Option == 1)//在设置模式选项
                    {
                        run_mode--;//P记忆位置--
                        if(run_mode < 1)//小于1时返回到第九个位置
                        {
                            run_mode = 1;
                        }
                        Flash_Read((uint8_t *)(&Param),sizeof(Param));
                        set_time=Param.P_Param[run_mode][1];//开机设置设定时间为20min
                        set_temp=Param.P_Param[run_mode][0];//开机设置设定温度37℃
                        if(set_time > 0 )
                        {
                            SetTime_State = 0;//设定时间退出显示“----”
                            time_Last = 0;
                        }
                        else
                        {
                            SetTime_State = 1;//设定时间显示“----”
                            time_Last = 1;
                        }
                        SetOK_Flag = 1;
                        Twinkle_On = 6000;//闪烁倒计时，如果停止按键设置，6S后停止闪烁
                        Key_Status = 2;//按键操作时不闪烁，2s后闪烁
                        Key_Cnt3 = 1.5f;
                    }
                    else
                    {
                        Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
                    }
                }
            }
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
                if(Param.Mode_Val)//在B模式下，并且启动定时
                {
                    Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
                }
                else
                {
                    if(Run_Status > 0) //运行中不能设置
                    {
                        Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
                    }
                    else
                    {
                        if(Select_Option == 2)//在设置温度选项
                        {
                            set_temp++;//温度++；
                            if(set_temp > 1000)//最高设定温度在100℃
                                set_temp = 1000;
                            Twinkle_On = 6000;//闪烁倒计时，如果停止按键设置，6S后停止闪烁
                            Key_Status = 2;//按键操作时不闪烁，2s后闪烁
                        }
                        else if(Select_Option == 3)//在设置时间选项
                        {
                            if(time_status == 0)//在秒单位模式下
                            {
                                set_time += 5;//时间加5s
                                time_Last = 0;//加入倒计时
                                SetTime_State = 0;//设定时间退出显示“----”
                            }
                            else//在分单位模式下
                                set_time += 60;//时间加60s
                            if(set_time > 86399)//最高可定时23.59小时
                                set_time = 86399;
                            Twinkle_On = 6000;//闪烁倒计时，如果停止按键设置，6S后停止闪烁
                            Key_Status = 2;//按键操作时不闪烁，2s后闪烁
                        }
                        else if(Select_Option == 1)//在设置模式选项
                        {
                            run_mode++;//P记忆位置++
                            if(run_mode > 9)//大于9时返回到第一个位置
                            {
                                run_mode = 9;
                            }
                            Flash_Read((uint8_t *)(&Param),sizeof(Param));
                            set_time=Param.P_Param[run_mode][1];//开机设置设定时间为20min
                            set_temp=Param.P_Param[run_mode][0];//开机设置设定温度37℃
                            if(set_time > 0 )
                            {
                                SetTime_State = 0;//设定时间退出显示“----”
                                time_Last = 0;
                            }
                            else
                            {
                                SetTime_State = 1;//设定时间显示“----”
                                time_Last = 1;
                            }
                            SetOK_Flag = 1;
                            Twinkle_On = 6000;//闪烁倒计时，如果停止按键设置，6S后停止闪烁
                            Key_Status = 2;//按键操作时不闪烁，2s后闪烁
                        }
                        else
                        {
                            Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
                        }
                    }
                }
            }
            Key_Flag2 = 0; // 按键事件结束，等待下一次按下
            Key_Cnt2 = 0;  // 按钮计数清零
        }
        else if (Key_Cnt2 > 1.9f && Key_Cnt2 < 2.1f) // 按键时间大于1.9S小于2.1S表示长按
        {
            if(Param.Mode_Val)//在B模式下，并且启动定时
            {
                Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
            }
            else
            {
                if(Run_Status > 0) //运行中不能设置
                {
                    Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
                }
                else
                {
                    if(Select_Option == 2)//在设置温度选项
                    {
                        if (UPPress_Time > 5.0f)
                        {
                            set_temp += 10;
                        }
                        else
                        {
                            set_temp++;//温度++；
                        }
                        if(set_temp > 1000)//最高设定温度在100℃
                            set_temp = 1000;
                        Twinkle_On = 6000;//闪烁倒计时，如果停止按键设置，6S后停止闪烁
                        Key_Status = 2;//按键操作时不闪烁，2s后闪烁
                        if (UPPress_Time > 5.0f)
                        {
                            Key_Cnt2 = 1.82f; // 长按按键时间复位
                        }
                        else
                        {
                            Key_Cnt2 = 1.88f;
                        }
                    }
                    else if(Select_Option == 3)//在设置时间选项
                    {
                        if (UPPress_Time > 5.0f)
                        {
                            if(time_status == 0)//在秒单位模式下
                            {
                                set_time += 60;//时间加60s
                                time_Last = 0;//加入倒计时
                                SetTime_State = 0;//设定时间退出显示“----”
                            }
                            else
                            {
                                if(set_time<  7200)
                                {
                                    if (set_time % 60)
                                        set_time = 3600;
                                    else
                                        set_time += 600;
                                }
                                else
                                {
                                    set_time += 600;
                                }
                            }
                        }
                        else
                        {
                            if(time_status == 0)//在秒单位模式下
                            {
                                set_time += 5;//时间加5s
                                time_Last = 0;//加入倒计时
                                SetTime_State = 0;//设定时间退出显示“----”
                            }
                            else
                            {
                                if(set_time<  7200)
                                {
                                    if (set_time % 60)
                                        set_time = 3600;
                                    else
                                        set_time += 60;
                                }
                                else
                                    set_time += 60;
                            }
                        }
                        if(set_time > 86399)//最高可定时23.59小时
                            set_time = 86399;
                        Twinkle_On = 6000;//闪烁倒计时，如果停止按键设置，6S后停止闪烁
                        Key_Status = 2;//按键操作时不闪烁，2s后闪烁
                        if (UPPress_Time > 5.0f)
                        {
                            Key_Cnt2 = 1.82f; // 长按按键时间复位
                        }
                        else
                        {
                            Key_Cnt2 = 1.88f;
                        }
                    }
                    else if(Select_Option == 1)//在设置模式选项
                    {
                        run_mode++;//P记忆位置++
                        if(run_mode > 9)//大于9时返回到第一个位置
                        {
                            run_mode = 9;
                        }
                        Flash_Read((uint8_t *)(&Param),sizeof(Param));
                        set_time=Param.P_Param[run_mode][1];//开机设置设定时间为20min
                        set_temp=Param.P_Param[run_mode][0];//开机设置设定温度37℃
                        if(set_time > 0 )
                        {
                            SetTime_State = 0;//设定时间退出显示“----”
                            time_Last = 0;
                        }
                        else
                        {
                            SetTime_State = 1;//设定时间显示“----”
                            time_Last = 1;
                        }
                        SetOK_Flag = 1;
                        Twinkle_On = 6000;//闪烁倒计时，如果停止按键设置，6S后停止闪烁
                        Key_Status = 2;//按键操作时不闪烁，2s后闪烁
                        Key_Cnt2 = 1.5f;
                    }
                    else
                    {
                        Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
                    }
                }
            }
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
                if(Param.Mode_Val)//在B模式下，并且启动定时
                {
                    Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
                }
                else
                {
                    if(Run_Status > 0) //运行中不能设置
                    {
                        Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
                    }
                    else
                    {
                        Select_Option++;//设置选项切换
                        if(Set_Mode_Enable == 0)
                        {
                            if(Select_Option == 1)//不进入p模式按一下直接进入温度设定
                            {
                                Select_Option = 2;
                            }
                            if(Select_Option > 3)//在温度和时间来换选择
                            {
                                Select_Option = 0;//不进行设置    			
                            }
                            Twinkle_On = 6000;//闪烁倒计时，如果停止按键设置，6S后停止闪烁
                            Beep_Time = 0.1;//蜂鸣器响0.1S
                        }
                        else
                        {
                            if(Select_Option > 3)//在温度和时间和P模式来换选择
                            {
                                Select_Option = 0;//不进行设置    	
                            }
                            Twinkle_On = 6000;//闪烁倒计时，如果停止按键设置，6S后停止闪烁
                            Beep_Time = 0.1;//蜂鸣器响0.1S
                        }
                    }
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
                if(Param.Mode_Val && Run_Status && time_Last == 1)//在B模式下，并且启动系统了
                {
                    time_Last = 0;
                    Beep_Time = 0.1;//蜂鸣器响0.1S
                }
                else
                {
                    if(Run_Status > 0) //运行中不能设置
                    {
                        Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
                    }
                    else if(Param.Mode_Val ) //运行中不能设置
                    {
                        Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
                    }
                    else
                    {
                        if(Set_Mode_Enable == 0)
                        {
                            Set_Mode_Enable = 1;//显示p模式的框
                            Select_Option = 1;//进入设定p的位置
                            run_mode = 1;
                            Flash_Read((uint8_t *)(&Param),sizeof(Param));
                            set_time=Param.P_Param[run_mode][1];//开机设置设定时间为20min
                            set_temp=Param.P_Param[run_mode][0];//开机设置设定温度37℃
                            if(set_time > 0 )
                            {
                                SetTime_State = 0;//设定时间退出显示“----”
                                time_Last = 0;
                            }
                            else
                            {
                                SetTime_State = 1;//设定时间显示“----”
                                time_Last = 1;
                            }
                            SetOK_Flag = 1;	
                            Twinkle_On = 6000;//闪烁倒计时，如果停止按键设置，6S后停止闪烁
                            Beep_Time = 0.1;//蜂鸣器响0.1S
                        }
                        else
                        {
                            Set_Mode_Enable = 0;//不显示P模式
                            run_mode_flag = 0;//不显示P模式框
                            set_time=1200;//退出P模式设置设定时间为20min
                            rel_time=1200;//退出P模式设置实际时间为20min
                            set_temp=370;//退出P模式设置设定温度37℃
                            Select_Option = 0;//不闪烁设置
                            run_mode = 0;
                            Flash_Read((uint8_t *)(&Param),sizeof(Param));
                            set_time=Param.P_Param[run_mode][1];//开机设置设定时间为20min
                            set_temp=Param.P_Param[run_mode][0];//开机设置设定温度37℃
                            SetOK_Flag = 1;
                            Beep_Time = 0.1;//蜂鸣器响0.1S
                        }
                    }
                }
			}
			Key_Flag5 = 0;//按键事件结束，等待下一次按下
			LongPress5 = 0;//长按标志清零
			Key_Cnt5 = 0;//按钮计数清零
		}
		if(Key_Cnt5 > 1.5 && Key_Cnt5 < 3.0)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress5 == 0)//如果没有一直一直长按着
			{
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
                if(Param.Mode_Val && Run_Status)//在B模式下，并且启动定时
                {
                    Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
                }
                else
                {
                    if(Run_Status == 0)//系统没启动
                    {
                        Select_Option = 0;//设定选项清零
                        Run_Status = 1; //系统启动         
                        ADD_Mode = 0;//加热状态清零
                        SetOK_Flag = 1;	
                    }
                    else
                    {
                        Run_Status = 0;//关闭系统
                        ADD_Mode = 0;//加热状态清零
                        SetOK_Flag = 1;
                    }
                    Beep_Time = 0.1;//蜂鸣器响0.1S
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
                if(Param.Mode_Val && time_Last == 1)//在B模式下，并且没有启动定时
                {
                    Param.Mode_Val = 0;
                    run_mode = 0;
                    SetOK_Flag = 1;
                    Save_Param_En = 1;
                    ADD_Mode = 0;//加热状态清零
                    Run_Status = 0;//关闭系统
                    time_Last = 0;
                    set_time=Param.P_Param[run_mode][1];//开机设置设定时间为20min
                    set_temp=Param.P_Param[run_mode][0];//开机设置设定温度37℃
                    Beep_Time = 0.1;//蜂鸣器响0.1S
                }
                else if(Param.Mode_Val == 0 && Run_Status == 0)//在A模式下，并且没有启动系统
                {
                    Param.Mode_Val = 1;
                    run_mode = 10;
                    SetOK_Flag = 1;
                    Save_Param_En = 1;
                    ADD_Mode = 0;//加热状态清零
                    Run_Status = 0;//关闭系统
                    time_Last = 1;
                    Set_Mode_Enable = 0;//不显示P模式
                    run_mode_flag = 0;//不显示P模式框
                    Select_Option = 0;//不闪烁设置
                    Twinkle_On = 0;
                    set_time=Param.P_Param[run_mode][1];//开机设置设定时间为20min
                    set_temp=Param.P_Param[run_mode][0];//开机设置设定温度37℃
                    Beep_Time = 0.1;//蜂鸣器响0.1S
                }
                else
                {
                    Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
                }
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
    if(Key_Status)
        Key_Status--;
}
