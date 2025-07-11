#include "Show.h"

/**********全局变量声明******/
float Twinkle_Time;//闪烁时间

/**********局部变量声明******/
uint8_t Temp_ShowFlag,Time_ShowFlag;//温度、时间显示的标志位 0:常亮 1：熄灭
uint8_t Protect_ShowFlag;//防干烧图标
uint8_t FIRST_Tab[] = {0xee, 0x24, 0xba, 0xb6, 0x74, 0xd6, 0xde, 0xa4, 0xfe, 0xf6};
uint8_t LAST_Tab[] = {0x77, 0X24, 0x5d, 0x6d, 0x2e, 0x6b, 0x7b, 0x25, 0x7f, 0x6f};
uint8_t MID_Tab[] =  {0x77, 0x12, 0x5d, 0x5b, 0x3a, 0x6b, 0x6f, 0x52, 0x7f, 0x7b};
uint8_t Tab[4] = {0, 0, 0, 0};


/**
 * @brief 闪烁检测
 *
 * @param dT 任务周期
 */
static void Check_ShowFlag(float dT)
{
    static float T;
    if(Twinkle_Time)
    {
        if (!sys.SetMode_Option) // 如果没有在设置选项中，则都点亮，不闪烁
        {
            Temp_ShowFlag = 0;    // 常亮
            Time_ShowFlag = 0;    // 常亮
            Twinkle_Time = 0;     // 闪烁计时清零
            return;
        }
        if (Twinkle_Time && !Key_Status) // 闪烁和没有操作按键时
        {
            if (T == 0)
            {
                if (Twinkle_Time == 0)
                {
                    sys.SetMode_Option = 0; // 模式选择清零
                    Temp_ShowFlag = 0;      // 常亮
                    Time_ShowFlag = 0;      // 常亮
                }
                else if (sys.SetMode_Option == 1)
                {
                    Temp_ShowFlag = ~Temp_ShowFlag; // 温度闪烁
                    Time_ShowFlag = 0;              // 常亮
                }
                else if (sys.SetMode_Option == 2)
                {
                    Temp_ShowFlag = 0;              // 常亮
                    Time_ShowFlag = ~Time_ShowFlag; // 时间闪烁
                }
            }
            T += dT;
            if (T >= 0.5f)
            {
                Twinkle_Time -= 0.5f;
                if (Twinkle_Time <= 0)
                {
                    sys.SetMode_Option = 0;
                }
                T = 0;
            }
        }
        else
        {
            Temp_ShowFlag = 0;// 常亮
            Time_ShowFlag = 0;// 常亮
            T = 0;
        }
    }
}

/*
*****************************************************************
 * 函数原型：static void Time_Twinkle(float dT)
 * 功    能：时间图标闪烁
 * 调    用：内部调用
*****************************************************************
*/
static void Time_Twinkle(float dT)
{
	static float T;
	if(sys.Run_Status == 1)
	{
		T += dT;
		if(T >= 0.5f)
		{
			Time.Icn = ~Time.Icn;//时间图标闪烁;
			T = 0;
		}
	}
	else
	{
		Time.Icn = 0;//显示时间图标
	}
}

/*
*****************************************************************
 * 函数原型：static void Temp_Twinkle(float dT)
 * 功    能：温度图标闪烁
 * 调    用：内部调用
*****************************************************************
*/
static void Temp_Twinkle(float dT)
{
	static float T;
	if(sys.Run_Status == 1)
	{
		T += dT;
		if(T >= 0.5f)
		{
			Temp.Icn = ~Temp.Icn;//温度图标闪烁;
			T = 0;
		}
	}
	else
	{
		Temp.Icn = 0;//显示温度图标
	}
}

/*
*****************************************************************
 * 函数原型：static void Protect_Twinkle(float dT)
 * 功    能：防干烧闪烁
 * 调    用：内部调用
*****************************************************************
*/
static void Protect_Twinkle(float dT)
{
	static float T;
	if(Protect == 1)
	{
		T += dT;
		if(T >= 0.5f)
		{
			Protect_ShowFlag = ~Protect_ShowFlag;//防干烧图标闪烁;
			T = 0;
		}
	}
	else
	{
		Protect_ShowFlag = 0;//显示防干烧图标
	}
}

/*
*****************************************************************
 * 函数原型：void Twinkle(float dT)
 * 功    能：闪烁函数
*****************************************************************
*/
void Twinkle(float dT)
{
	Check_ShowFlag(dT);//时间图标闪烁
    Time_Twinkle(dT);//时间图标闪烁
	Temp_Twinkle(dT);//温度图标闪烁
    Protect_Twinkle(dT);//防干烧闪烁
}

/*
*****************************************************************
 * 函数原型： void Dis_RelTemp(int dis_rel_temp)
 * 功    能： 显示实际温度
 * 输    入:  dis_rel_temp：实际温度
 * 参    数： int dis_rel_temp
*****************************************************************
*/
void Dis_RelTemp(int dis_rel_temp)
{
    if(dis_rel_temp > 999)//千位
    {
        Tab[0] = LAST_Tab[dis_rel_temp / 1000];
        Tab[1] = LAST_Tab[dis_rel_temp / 100 % 10];
        Tab[2] = LAST_Tab[dis_rel_temp / 10 % 10];
        Tab[3] = LAST_Tab[dis_rel_temp % 10];
    }
    else if(dis_rel_temp > 99)//百位
    {
        Tab[0] = 0;
        Tab[1] = LAST_Tab[dis_rel_temp / 100];
        Tab[2] = LAST_Tab[dis_rel_temp / 10 % 10];
        Tab[3] = LAST_Tab[dis_rel_temp % 10];
    }
    else if(dis_rel_temp > 9)//十位
    {
        Tab[0] = 0;
        Tab[1] = 0;
        Tab[2] = LAST_Tab[dis_rel_temp / 10];
        Tab[3] = LAST_Tab[dis_rel_temp % 10];
    }
    else if(dis_rel_temp > -1)//个位
    {
        Tab[0] = 0;
        Tab[1] = 0;
        Tab[2] = LAST_Tab[dis_rel_temp / 10];
        Tab[3] = LAST_Tab[dis_rel_temp % 10];
    }
    else if(dis_rel_temp > -10)//负数
    {
        Tab[0] = 0;
        Tab[1] = 0x08;
        Tab[2] = LAST_Tab[0];
        Tab[3] = LAST_Tab[(-dis_rel_temp)];
    }
    else if(dis_rel_temp > -100)//负十位
    {
        Tab[0] = 0;
        Tab[1] = 0x08;
        Tab[2] = LAST_Tab[(-dis_rel_temp) / 10];
        Tab[3] = LAST_Tab[(-dis_rel_temp) % 10];
    }
    else//负百位
    {
        Tab[0] = 0x08;
        Tab[1] = LAST_Tab[1];
        Tab[2] = LAST_Tab[0];
        Tab[3] = LAST_Tab[0];
    }

	if(!Temp.Icn)Tab[2]=Tab[2]|0x80;//加热图标
		else Tab[2]=Tab[2]|0x00;//加热图标
	
    Tab[3] = Tab[3] | 0x80;//实际温度的小数点
    Tab[0] = Tab[0] | 0x80;//设置温度的℃符号

//	if(PMode_Status)//（本代码不操作此寄存器，单加热）
//    {
//        if((((Display_Circle<10)&&(Display_Circle>3))&&(Display_Circle!=0))||(Display_Circle==13))
//        {
//            Tab[1]=Tab[1]|0x80;//模式外圈显示
//        }
//        else if((Display_Circle==3)||(Display_Circle==0))
//            Tab[1]=Tab[1]&0x7f;//模式外圈不显示
//        if(Show_Circle==0)
//            Tab[1]=Tab[1]|0x80;//模式外圈显示
//    }
//    else
//    {
//        Tab[1]=Tab[1]&0x7f;//模式外圈不显示
//    }
	
    Write_Addr_Dat_N(0, Tab[0], 1);
    Write_Addr_Dat_N(2, Tab[1], 1);
    Write_Addr_Dat_N(4, Tab[2], 1);
    Write_Addr_Dat_N(6, Tab[3], 1);
}

/*
*****************************************************************
 * 函数原型： void Dis_SetTemp(int dis_set_temp)
 * 功    能： 显示设定温度
 * 输    入:  dis_set_temp：设定温度
 * 参    数： int dis_set_temp
*****************************************************************
*/
void Dis_SetTemp(int dis_set_temp)
{
    if(dis_set_temp > 999)//千位
    {

        Tab[0] = LAST_Tab[dis_set_temp / 1000];
        Tab[1] = LAST_Tab[dis_set_temp / 100 % 10];
        Tab[2] = LAST_Tab[dis_set_temp / 10 % 10];
        Tab[3] = LAST_Tab[dis_set_temp % 10];
    }
    else if(dis_set_temp > 99)//百位
    {

        Tab[0] = 0;
        Tab[1] = LAST_Tab[dis_set_temp / 100];
        Tab[2] = LAST_Tab[dis_set_temp / 10 % 10];
        Tab[3] = LAST_Tab[dis_set_temp % 10];
    }
    else if(dis_set_temp > -1)//十位
    {

        Tab[0] = 0;
        Tab[1] = 0;
        Tab[2] = LAST_Tab[dis_set_temp / 10];
        Tab[3] = LAST_Tab[dis_set_temp % 10];
    }
    else if(dis_set_temp > -10)//个位
    {
        Tab[0] = 0;
        Tab[1] = 0x08;
        Tab[2] = LAST_Tab[0];
        Tab[3] = LAST_Tab[(-dis_set_temp)];
    }
    else if(dis_set_temp > -100)//负数
    {
        Tab[0] = 0;
        Tab[1] = 0x08;
        Tab[2] = LAST_Tab[(-dis_set_temp) / 10];
        Tab[3] = LAST_Tab[(-dis_set_temp) % 10];
    }
    else//负百位
    {
        Tab[0] = 0x08;
        Tab[1] = LAST_Tab[1];
        Tab[2] = LAST_Tab[0];
        Tab[3] = LAST_Tab[0];
    }

    Tab[2] = Tab[2] | 0x80;//设置温度的小数点

    if(Temp_ShowFlag && Key_Status==0)//闪烁
    {
        Tab[0] = 0;
        Tab[1] = 0;
        Tab[2] = 0;
        Tab[3] = 0;
    }

    Write_Addr_Dat_N(32, Tab[3], 1);
    Write_Addr_Dat_N(34, Tab[2], 1);
    Write_Addr_Dat_N(36, Tab[1], 1);
    Write_Addr_Dat_N(38, Tab[0], 1);
}

/*
*****************************************************************
 * 函数原型： void Dis_RelTime(int dis_rel_time)
 * 功    能： 显示实际时间
 * 输    入:  dis_rel_time：实际时间
 * 参    数： int dis_rel_time
*****************************************************************
*/
void Dis_RelTime(int dis_rel_time)
{
//    if(dis_rel_time < 3600)//在秒显示状态下
//    {
//        if(dis_rel_time>59)//分钟以60进一单位
//        {
//            Tab[0]=LAST_Tab[dis_rel_time/60/10];
//            Tab[1]=LAST_Tab[dis_rel_time/60%10];
//            Tab[2]=LAST_Tab[dis_rel_time%60/10];
//            Tab[3]=LAST_Tab[dis_rel_time%60%10];
//        }
//        else
//        {
//            Tab[0]=LAST_Tab[0];
//            Tab[1]=LAST_Tab[0];
//            Tab[2]=LAST_Tab[dis_rel_time%60/10];
//            Tab[3]=LAST_Tab[dis_rel_time%60%10];
//        }
//    }
//    else//在分显示状态下
//    {
        Tab[0]=LAST_Tab[dis_rel_time/3600/10];
        Tab[1]=LAST_Tab[dis_rel_time/3600%10];
        Tab[2]=LAST_Tab[dis_rel_time%3600/60/10];
        Tab[3]=LAST_Tab[dis_rel_time%3600/60%10];
//    }
	if(Time.Icn == 0)
		Tab[2]=Tab[2]|0x80;//实时时间冒号
	else
		Tab[2]=Tab[2]|0x00;//不显示实时时间冒号
	
	Tab[0]=Tab[0]|0x00;//不显示制冷图标

	
	if(dis_rel_time == 0)//未设定时间显示“----”
    {
        Tab[3] &= 0x80;Tab[3] |= 0x08;
        Tab[2] &= 0x80;Tab[2] |= 0x08;
        Tab[1] &= 0x80;Tab[1] |= 0x08;
        Tab[0] &= 0x80;Tab[0] |= 0x08;
    }
	
    Write_Addr_Dat_N(8,Tab[0], 1);
    Write_Addr_Dat_N(10,Tab[1], 1);
    Write_Addr_Dat_N(12,Tab[2], 1);
    Write_Addr_Dat_N(14,Tab[3], 1);
}

/*
*****************************************************************
 * 函数原型： void Dis_SetTime(int dis_set_time)
 * 功    能： 显示设定时间
 * 输    入:  dis_set_time：设定时间
 * 参    数： int dis_set_time
*****************************************************************
*/
void Dis_SetTime(int dis_set_time)
{
//    if(dis_set_time < 3600)//在秒显示状态下
//    {
//        if(dis_set_time>59)//分钟以60进一单位
//        {
//            Tab[0]=MID_Tab[dis_set_time/60/10];
//            Tab[1]=MID_Tab[dis_set_time/60%10];
//            Tab[2]=MID_Tab[dis_set_time%60/10];
//            Tab[3]=MID_Tab[dis_set_time%60%10];
//        }
//        else
//        {
//            Tab[0]=MID_Tab[0];
//            Tab[1]=MID_Tab[0];
//            Tab[2]=MID_Tab[dis_set_time%60/10];
//            Tab[3]=MID_Tab[dis_set_time%60%10];
//        }
//    }
//    else
//    {
        Tab[0]=MID_Tab[dis_set_time/3600/10];
        Tab[1]=MID_Tab[dis_set_time/3600%10];
        Tab[2]=MID_Tab[dis_set_time%3600/60/10];
        Tab[3]=MID_Tab[dis_set_time%3600/60%10];
//    }
//	if(timeicn_flag == 0)
		Tab[1]=Tab[1]|0x80;//设定时间冒号
//	else
//		Tab[1]=Tab[1]|0x00;//不显示设定时间冒号
	
    if(dis_set_time == 0)//未设定时间显示“----”
    {
        Tab[3] &= 0x80;Tab[3] |= 0x08;
        Tab[2] &= 0x80;Tab[2] |= 0x08;
        Tab[1] &= 0x80;Tab[1] |= 0x08;
        Tab[0] &= 0x80;Tab[0] |= 0x08;
    }
    
    if(Time_ShowFlag && Key_Status==0)//闪烁
    {
        Tab[0]=0;
        Tab[1]=0;
        Tab[2]=0;
        Tab[3]=0;
    }
 
//    if(dis_set_time < 3600)
//        Tab[2]=Tab[2]|0x80;//秒单位显示
//    else
        Tab[3]=Tab[3]|0x80;//分钟单位显示

    Write_Addr_Dat_N(16,Tab[3], 1);
    Write_Addr_Dat_N(18,Tab[2], 1);
    Write_Addr_Dat_N(20,Tab[1], 1);
    Write_Addr_Dat_N(22,Tab[0], 1);
}

/**
 * @brief 温度显示处理
 *
 * @param dT 任务周期
 */
void Deal_Temp(float dT)
{
    static float T;
    if (sys.Run_Status == 0)
    {
        Temp.ADDMode = 0;
        Temp.Display_Rel = Temp.Rel;
    }
    else if (sys.Run_Status == 1)
    {
        if (Temp.ADDMode == 0)
        {
            if (Temp.Ctrl > Temp.Display_Rel)
            {
                Temp.ADDMode = 1; // 进入加热模式
            }
            else
            {
                Temp.ADDMode = 2; // 进入制冷模式
            }
        }
        else if (Temp.ADDMode == 1)
        {
            if (Temp.Rel > Temp.Display_Rel && Temp.Display_Rel <= Temp.Ctrl)
            {
                Temp.Display_Rel++;
                T = 0;
            }
            if (Temp.Display_Rel >= Temp.Ctrl - 20)
            {
                Temp.ADDMode = 3;
                return;
            }
        }
        else if (Temp.ADDMode == 2)
        {
            if (Temp.Rel < Temp.Display_Rel && Temp.Display_Rel >= Temp.Ctrl)
            {
                Temp.Display_Rel--;
                T = 0;
            }
            if (Temp.Display_Rel <= Temp.Ctrl + 20)
            {
                Temp.ADDMode = 3;
                return;
            }
        }
        else if (Temp.ADDMode == 3)
        {
            T += dT;
            if (Temp.Display_Rel < Temp.Ctrl)
            {
                if (T >= 2.0f)
                {
                    Temp.Display_Rel += 1;
                    T = 0;
                }
            }
            else if (Temp.Display_Rel > Temp.Ctrl)
            {
                if (T >= 2.0f)
                {
                    Temp.Display_Rel -= 1;
                    T = 0;
                }
            }
            else
            {
                Temp.ADDMode = 4;
                Temp_ShowFlag = 0;//就怕闪烁时，他会正好在黑掉得时候
                T = 0;
            }
        }
        else if (Temp.ADDMode == 4)
        {
            Temp.Display_Rel = Temp.Ctrl;
        }
    }
}

/*
*****************************************************************
 * 函数原型：void Show_Display(void)
 * 功    能：显示屏幕内容
*****************************************************************
*/
void Show_Display(void)
{	
    Temp.Display_Set = Temp.Set;
    
    Time.Display_Rel = Time.Rel + 59;
    Time.Display_Set = Time.Set;
	Dis_RelTemp(Temp.Display_Rel);
	Dis_SetTemp(Temp.Display_Set);
	Dis_RelTime(Time.Display_Rel);
	Dis_SetTime(Time.Display_Set);
}
