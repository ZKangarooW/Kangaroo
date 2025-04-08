#include "Show.h"

/**********全局变量**********/
uint16_t Twinkle_Time;//闪烁时间

/**********局部变量**********/
uint8_t FIRST_Tab[] = {0xee, 0x24, 0xba, 0xb6, 0x74, 0xd6, 0xde, 0xa4, 0xfe, 0xf6};
uint8_t LAST_Tab[] = {0x77, 0X24, 0x5d, 0x6d, 0x2e, 0x6b, 0x7b, 0x25, 0x7f, 0x6f};
uint8_t MID_Tab[] =  {0x77, 0x12, 0x5d, 0x5b, 0x3a, 0x6b, 0x6f, 0x52, 0x7f, 0x7b};
uint8_t Tab[4] = {0, 0, 0, 0};
uint8_t Temp_ShowFlag,Time_ShowFlag,P_ShowFlag;//速度、温度、时间显示的标志位 0:常亮 1：熄灭
uint8_t mode_flag,mode_flag_p1,mode_flag_p2;
uint8_t timeicn_flag,tempicn_flag;//启动时时间图标和温度图标闪烁

/*
*****************************************************************
 * 函数原型： void time_icn(float dT)
 * 功    能： 启动时时间图标闪烁
*****************************************************************
*/
void time_icn(float dT)
{
	static float T,T1;
	if(sys.Run_Status == 1 && Temp_ADDMode == 3)
	{
		T += dT;
		if(T >= 0.5f)
		{
			timeicn_flag = ~ timeicn_flag;
			T = 0;
		}
	}
	else
	{
		timeicn_flag = 0;
		T = 0;
	}
	if(sys.Run_Status == 1 && Temp_ADDMode != 3)
	{
		T1 += dT;
		if(T1 >= 1.0f)
		{
			tempicn_flag = ~ tempicn_flag;
			T1 = 0;
		}
	}
	else
	{
		tempicn_flag = 0;
		T1 = 0;
	}
}

/*
*****************************************************************
 * 函数原型： void Check_ShowFlag(uint16_t dT)
 * 功    能： 闪烁检测
 * 输    入:  dT:执行周期
 * 参    数： uint16_t dT
*****************************************************************
*/
void Check_ShowFlag(uint16_t dT)
{
    if(sys.SetMode_Option == 0)//如果没在设置选项中，则都点亮，不闪烁
    {
        Temp_ShowFlag = 0;//常亮
        Time_ShowFlag = 0;//常亮
		P_ShowFlag = 0;
    }
	if(sys.SetP_Mode_Option == 0)
	{
		mode_flag_p1 = 0;
		mode_flag_p2 = 0;
		mode_flag = 0;
	}
	if(sys.SetP_Mode_Option == 0 && sys.SetMode_Option == 0)
	{
		Twinkle_Time = 0;//闪烁计时清零
	}
    if(Twinkle_Time && Key_Status==0)//闪烁和没有操作旋钮时
    {
        Twinkle_Time -= dT;//闪烁计时
        if(sys.SetMode_Option == 2)//设置速度
        {
            Temp_ShowFlag = ~Temp_ShowFlag;//温度闪烁
            Time_ShowFlag = 0;//时间常亮
			P_ShowFlag = 0;
        }
        else if(sys.SetMode_Option == 3)//设置温度
        {
            Temp_ShowFlag = 0;//温度常亮
            Time_ShowFlag = ~Time_ShowFlag;//时间闪烁
			P_ShowFlag = 0;
        }
		else if(sys.SetMode_Option == 1)//设置温度
        {
            Temp_ShowFlag = 0;//温度常亮
            Time_ShowFlag = 0;//时间闪烁
			P_ShowFlag = ~P_ShowFlag;
        }
		else if(sys.SetP_Mode_Option == 1)//设置P1
        {
			mode_flag_p1 = ~mode_flag_p1;//时间闪烁
			mode_flag_p2 = 0;
			mode_flag = 0;
        }
		else if(sys.SetP_Mode_Option == 2)//设置温度
        {
			mode_flag = 0;
			mode_flag_p1 = 0;
            mode_flag_p2 = ~mode_flag_p2;//时间闪烁
        }
        if(Twinkle_Time == 0)//如果闪烁结束
        {
            sys.SetMode_Option = 0;//模式选择清零
			sys.SetP_Mode_Option = 0;
			SetOK_Flag = 1;
        }        
    }
}

/*
*****************************************************************
 * 函数原型： void Check_Show_PModeFlag(float dT)
 * 功    能： 梯度模式运行闪烁
 * 输    入:  dT:执行周期
 * 参    数： float dT
*****************************************************************
*/
void Check_Show_PModeFlag(float dT)
{
    static float T;
	if(sys.Run_Status == 1)
	{
		if(PMode_Status == 2)
		{
			T += dT;
			if(T > 2)
			{
				PMode_Mode = 1;
				if(T >= 4)
					T = 0;
			}
			else
			{
				PMode_Mode = 0;
			}
		}
		else
		{
			T = 0;
		}
	}
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
	if(tempicn_flag == 0)
	{
		if(HEAT_ICO == 1 && sys.Run_Status == 1)//开始控制温度时
			Tab[3]=Tab[3]|0x80;//加热图标
	}
	else
	{
		if(HEAT_ICO == 1 && sys.Run_Status == 1)//开始控制温度时
			Tab[3]=Tab[3]|0x00;//不显示加热图标
	}

    Tab[2] = Tab[2] | 0x80;//实际温度的小数点
    Tab[0] = Tab[0] | 0x80;//设置温度的℃符号
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

        Tab[0] = FIRST_Tab[dis_set_temp / 1000];
        Tab[1] = FIRST_Tab[dis_set_temp / 100 % 10];
        Tab[2] = FIRST_Tab[dis_set_temp / 10 % 10];
        Tab[3] = FIRST_Tab[dis_set_temp % 10];
    }
    else if(dis_set_temp > 99)//百位
    {

        Tab[0] = 0;
        Tab[1] = FIRST_Tab[dis_set_temp / 100];
        Tab[2] = FIRST_Tab[dis_set_temp / 10 % 10];
        Tab[3] = FIRST_Tab[dis_set_temp % 10];
    }
    else if(dis_set_temp > -1)//十位
    {

        Tab[0] = 0;
        Tab[1] = 0;
        Tab[2] = FIRST_Tab[dis_set_temp / 10];
        Tab[3] = FIRST_Tab[dis_set_temp % 10];
    }
    else if(dis_set_temp > -10)//个位
    {
        Tab[0] = 0;
        Tab[1] = 0x10;
        Tab[2] = FIRST_Tab[0];
        Tab[3] = FIRST_Tab[(-dis_set_temp)];
    }
    else if(dis_set_temp > -100)//负数
    {
        Tab[0] = 0;
        Tab[1] = 0x10;
        Tab[2] = FIRST_Tab[(-dis_set_temp) / 10];
        Tab[3] = FIRST_Tab[(-dis_set_temp) % 10];
    }
    else//负百位
    {
        Tab[0] = 0x10;
        Tab[1] = FIRST_Tab[1];
        Tab[2] = FIRST_Tab[0];
        Tab[3] = FIRST_Tab[0];
    }

    Tab[2] = Tab[2] | 0x01;//设置温度的小数点

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
    if(Time_Unit ==0)//在秒显示状态下
    {
        if(dis_rel_time>59)//分钟以60进一单位
        {
            Tab[0]=LAST_Tab[dis_rel_time/60/10];
            Tab[1]=LAST_Tab[dis_rel_time/60%10];
            Tab[2]=LAST_Tab[dis_rel_time%60/10];
            Tab[3]=LAST_Tab[dis_rel_time%60%10];
        }
        else
        {
            Tab[0]=LAST_Tab[0];
            Tab[1]=LAST_Tab[0];
            Tab[2]=LAST_Tab[dis_rel_time%60/10];
            Tab[3]=LAST_Tab[dis_rel_time%60%10];
        }
    }
    else//在分显示状态下
    {
        Tab[0]=LAST_Tab[dis_rel_time/3600/10];
        Tab[1]=LAST_Tab[dis_rel_time/3600%10];
        Tab[2]=LAST_Tab[dis_rel_time%3600/60/10];
        Tab[3]=LAST_Tab[dis_rel_time%3600/60%10];
    }
	if(timeicn_flag == 0)
		Tab[2]=Tab[2]|0x80;//实时时间冒号
	else
		Tab[2]=Tab[2]|0x00;//不显示实时时间冒号
	
	if(tempicn_flag == 0)
	{
		if(HEAT_ICO == 2 && sys.Run_Status == 1)//开始控制温度时
			Tab[0]=Tab[0]|0x80;//制冷图标
	}
	else	
	{
		if(HEAT_ICO == 2 && sys.Run_Status == 1)//开始控制温度时
			Tab[0]=Tab[0]|0x00;//不显示制冷图标
	}
	
	if(Time_State)//未设定时间显示“----”
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
    if(dis_set_time > 3599)//如果设定时间大于59.59分钟时
    {
        Time_Unit=1;//单位变成分
    }
    else
        Time_Unit=0;//不然就是秒

    if(Time_Unit ==0)//在秒显示状态下
    {
        if(dis_set_time>59)//分钟以60进一单位
        {
            Tab[0]=MID_Tab[dis_set_time/60/10];
            Tab[1]=MID_Tab[dis_set_time/60%10];
            Tab[2]=MID_Tab[dis_set_time%60/10];
            Tab[3]=MID_Tab[dis_set_time%60%10];
        }
        else
        {
            Tab[0]=MID_Tab[0];
            Tab[1]=MID_Tab[0];
            Tab[2]=MID_Tab[dis_set_time%60/10];
            Tab[3]=MID_Tab[dis_set_time%60%10];
        }
    }
    else
    {
        Tab[0]=MID_Tab[dis_set_time/3600/10];
        Tab[1]=MID_Tab[dis_set_time/3600%10];
        Tab[2]=MID_Tab[dis_set_time%3600/60/10];
        Tab[3]=MID_Tab[dis_set_time%3600/60%10];
    }
	if(timeicn_flag == 0)
		Tab[1]=Tab[1]|0x80;//设定时间冒号
	else
		Tab[1]=Tab[1]|0x00;//不显示设定时间冒号
	
    if(Time_State)//未设定时间显示“----”
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
 
    if(Time_Unit)
        Tab[3]=Tab[3]|0x80;//分钟单位显示
    else
        Tab[2]=Tab[2]|0x80;//秒单位显示

    if(PMode_Status)//（本代码不操作此寄存器，单加热）
    {
        if((((Display_Circle<10)&&(Display_Circle>3))&&(Display_Circle!=0))||(Display_Circle==13))
        {
            Tab[0]=Tab[0]|0x80;//模式外圈显示
        }
        else if((Display_Circle==3)||(Display_Circle==0))
            Tab[0]=Tab[0]&0x7f;//模式外圈不显示
        if(Show_Circle==0)
            Tab[0]=Tab[0]|0x80;//模式外圈显示
    }
    else
    {
        Tab[0]=Tab[0]&0x7f;//模式外圈不显示
    }

    Write_Addr_Dat_N(16,Tab[3], 1);
    Write_Addr_Dat_N(18,Tab[2], 1);
    Write_Addr_Dat_N(20,Tab[1], 1);
    Write_Addr_Dat_N(22,Tab[0], 1);
}

/*
*****************************************************************
 * 函数原型： void Display_RunPMode(uint8_t E,uint8_t P,uint8_t P1,uint8_t P2)
 * 功    能： 显示P运行模式
 * 输    入:  E：P模式框显示   P：记忆和梯度选择 P1：梯度模式下P1值 P2：梯度模式下P2值 
 * 参    数： uint8_t E,uint8_t P,uint8_t P1,uint8_t P2
*****************************************************************
*/
void Display_RunPMode(uint8_t E,uint8_t P,uint8_t P1,uint8_t P2)
{
    static uint8_t tab1=0;
    if(E)//进入P模式显示
    {
        if(Display_Circle)//如果标准位大于一
        {
            switch(Display_Circle)//用switch语句实现动画转圈
            {
                case 0:Write_Addr_Dat_N(24,0x00, 1);
                    break;
                case 1: tab1|=0X01;tab1&=0Xbf; Write_Addr_Dat_N(24,tab1, 1);
                    break;
                case 2: tab1|=0X02;tab1&=0X7f; Write_Addr_Dat_N(24,tab1, 1);
                    break;
                case 3: tab1|=0X04; Write_Addr_Dat_N(24,tab1, 1);
                    break;
                case 4: tab1|=0X08; Write_Addr_Dat_N(24,tab1, 1);
                    break;
                case 5: tab1|=0X10; Write_Addr_Dat_N(24,tab1, 1);
                    break;
                case 6: tab1|=0X20; Write_Addr_Dat_N(24,tab1, 1);
                    break;
                case 7: tab1|=0X40;tab1&=0XFE; Write_Addr_Dat_N(24,tab1, 1);
                    break;
                case 8: tab1|=0X80;tab1&=0XFC; Write_Addr_Dat_N(24,tab1, 1);
                    break;
                case 9: tab1&=0XFB; Write_Addr_Dat_N(24,tab1, 1);
                    break;
                case 10: tab1&=0XF7; Write_Addr_Dat_N(24,tab1, 1);
                    break;
                case 11: tab1&=0XEF; Write_Addr_Dat_N(24,tab1, 1);
                    break;
                case 12: tab1&=0XCF; Write_Addr_Dat_N(24,tab1, 1);
                    break;
                case 13: tab1&=0XCF; Write_Addr_Dat_N(24,0xff, 1);
                    break;
            }
        }

        if(Show_Circle==0)//加入不在p模式下
            Write_Addr_Dat_N(24,0xff, 1);//外框消失，方便转圈


        //模式选择
        if(P)//梯度模式下
        {
            Tab[2]=FIRST_Tab[P1];//模式一
            Tab[1]=0X10;//-
            Tab[0]=FIRST_Tab[P2];//模式二
        }
        else//记忆模式下
        {
			
			Tab[0]=FIRST_Tab[PMode_Option];//显示模式数
			Tab[1]=0X10;//-
			Tab[2]=0xf8;//显示字母P
			if(P_ShowFlag && Key_Status==0)
			{
				Tab[0]=0x00;//不显示
				Tab[1]=0x00;//不显示
				Tab[2]=0x00;//不显示
			}
        }

        if(mode_flag && Key_Status==0)//闪烁显示
        {
            Tab[0]=0;
            Tab[1]=0;
            Tab[2]=0;
        }

        if(mode_flag_p1 && Key_Status==0)//梯度模式下P1闪烁
            Tab[2]=0;
        if(mode_flag_p2 && Key_Status==0)//梯度模式下P2闪烁
            Tab[0]=0;

        //模式外圈显示
        if((((Display_Circle<11)&&(Display_Circle>4))&&(Display_Circle!=0))||(Display_Circle==13))
            Tab[2]=Tab[2]|0x01;//模式外圈显示
        else if((Display_Circle==4)||(Display_Circle==0))
            Tab[2]=Tab[2]&0xfe;//模式外圈不显示
        if(Show_Circle==0)
            Tab[2]=Tab[2]|0x01;//模式外圈显示
        if((((Display_Circle<13)&&(Display_Circle>6))&&(Display_Circle!=0))||(Display_Circle==13))
            Tab[0]=Tab[0]|0x01;//模式外圈显示
        else if((Display_Circle==6)||(Display_Circle==0))
            Tab[0]=Tab[0]&0xfe;//模式外圈不显示
        if(Show_Circle==0)
            Tab[0]=Tab[0]|0x01;//模式外圈显示
        if((((Display_Circle<12)&&(Display_Circle>5))&&(Display_Circle!=0))||(Display_Circle==13))
            Tab[1]=Tab[1]|0x01;//模式外圈显示
        else if((Display_Circle==5)||(Display_Circle==0))
            Tab[1]=Tab[1]&0xfe;//模式外圈不显示
        if(Show_Circle==0)
            Tab[1]=Tab[1]|0x01;//模式外圈显示
    }
    else//不显示
    {
        Tab[0]=0;
        Tab[1]=0;
        Tab[2]=0;
        Write_Addr_Dat_N(24,0x00, 1);
    }

    Write_Addr_Dat_N(26,Tab[0], 1);
    Write_Addr_Dat_N(28,Tab[1], 1);
    Write_Addr_Dat_N(30,Tab[2], 1);
}

/*
*****************************************************************
 * 函数原型： void Circle_Go(void)
 * 功    能： 跑梯度模式-单加热没有用到
*****************************************************************
*/
void Circle_Go(void)
{
	if(sys.Run_Status == 1)
	{
		if(Circle_Run)
		{
			Show_Circle = 1;//不固定显示外框
			if((Circle_Run ) && (sys.Run_Status > 0))//跑梯度标志位置一，系统启动
			{
				Display_Circle -= 1;//显示--
				if(Display_Circle < 1)//小于1表示一圈跑完
					Display_Circle = 12;//从头跑
			}
		}
		else
		{
			Show_Circle = 0;//不固定显示外框
			Circle_Run = 0;
		}
	}
	else
	{
		Show_Circle = 0;
	}
}

/*
*****************************************************************
 * 函数原型： void ADD_Show(uint16_t dT)
 * 功    能： 显示上升时间
 * 输    入:  dT:执行周期
 * 参    数： uint16_t dT
*****************************************************************
*/
void ADD_Show(uint16_t dT)
{
    static uint16_t T;
    if(ADD_Wait_Count && Temp_ADDMode == 2)//加入慢速上升标志位大于一并且升温状态在慢速上升时
    {
        T += dT;
        if(T == 1000)//1S
        {
            ADD_Wait_Count--;//慢速上声标志位--
            if(ADD_Wait_Count == 0)//慢速上升标志位等于0时
                Temp_ADDMode = 3;//进入稳定温度模式
            T = 0;
        }
        
    }
}

/*
*****************************************************************
 * 函数原型： void Deal_Temp(void)
 * 功    能： 温度显示处理
*****************************************************************
*/
void Deal_Temp(void)
{
	static uint16_t val;
	if(sys.Run_Status == 0)//没启动的情况下
    {
		Display_RelTemp = Rel_Temp;//显示实际温度  
    }
	else//启动的情况下
    {
		if(sys.CtrlTemp_Mode == 1)
		{
			switch(Temp_ADDMode)
			{
				case 0:
					 if(Ctrl_Temp - Rel_Temp > 20)
					 {
						 Temp_ADDMode = 1;//上升
						 Temp_New = 0;
						 Temp_Last = 0;
					 }
					 else if(Ctrl_Temp - Rel_Temp <= 20 && Ctrl_Temp - Rel_Temp > 0)
					 {
						val = Ctrl_Temp - Rel_Temp;
						ADD_Wait_Count = 200;//200S的缓慢升温显示  
						Temp_ADDMode = 2;//缓慢上升
					 }
					break;	
					
				case 1://
					Temp_New = Rel_Temp;//记录当前温度
					if(Temp_New > Temp_Last)//当前温度大于上一次温度
						Display_RelTemp = Temp_New;//显示当前温度
					else//当前温度小于上一次温度
					{
						Display_RelTemp = Temp_Last;//显示上一次温度，不让温度小于当前温度。呈现攀升温度的现象
						Temp_New = Temp_Last;//将上一次温度赋值给当前温度
					}
					Temp_Last = Temp_New;//将当前温度保存
					if(Ctrl_Temp - Rel_Temp <= 20 && Ctrl_Temp - Rel_Temp > 0)//实际温度大于等于设定温度-2℃
					{
						val = Ctrl_Temp - Rel_Temp;
						Temp_ADDMode = 2;//缓慢上升
						ADD_Wait_Count = 200;//200S的缓慢升温显示  
					}
					break;
			
				case 2:
					Display_RelTemp=(Ctrl_Temp-val)+(val-(ADD_Wait_Count)/(200/val));//缓慢显示数值
					break;
				case 3:		
					Display_RelTemp = Ctrl_Temp;
					sys.DownTime_Status = 1;//开始倒计时
					break;			
				default: break;	
			}	
		}
		if(sys.CtrlTemp_Mode == 2)
		{	
			switch(Temp_ADDMode)
			{
				case 0:
					 if(Rel_Temp - Ctrl_Temp > 20)
					 {
						 Temp_ADDMode = 1;//下降
						 Temp_New = 0;
						 Temp_Last = Rel_Temp;
					 }
					 else if(Rel_Temp - Ctrl_Temp <= 20 && Rel_Temp - Ctrl_Temp > 0)
					 {
						val = Rel_Temp - Ctrl_Temp;
						ADD_Wait_Count = 200;//200S的缓慢降温显示 
						Temp_ADDMode = 2;//缓慢下降
					 }
					break;	
					
				case 1:
					Temp_New = Rel_Temp;//记录当前温度
					if(Temp_New < Temp_Last)//当前温度小于上一次温度
						Display_RelTemp = Temp_New;//显示当前温度
					else//当前温度大于上一次温度
					{
						Display_RelTemp = Temp_Last;//显示上一次温度，不让温度大于当前温度。呈现下降温度的现象
						Temp_New = Temp_Last;//将上一次温度赋值给当前温度
					}
					Temp_Last = Temp_New;//将当前温度保存
					if(Rel_Temp - Ctrl_Temp <= 20 && Rel_Temp - Ctrl_Temp > 0)//实际温度小于等于设定温度-2℃
					{
						val = Rel_Temp - Ctrl_Temp;
						Temp_ADDMode = 2;//缓慢下升
						ADD_Wait_Count = 200;//200S的缓慢降温显示  
					}
					break;
			
				case 2:
					Display_RelTemp=(Ctrl_Temp+val)-(val-(ADD_Wait_Count)/(200/val));//缓慢显示数值
					break;
				case 3:		
					Display_RelTemp = Ctrl_Temp;
					sys.DownTime_Status = 1;//开始倒计时
					break;			
				default: break;	
			}	
		}			
    }
}

void CtrlTemp_Error(float dT)
{
	if(Temp_ADDMode != 3)
		return;
	if(ABS(Rel_Temp - Ctrl_Temp) > 40)
	{
		if(PMode_Status == 2)
		{
			if(PMode_Option > PMode_P2)
			{
				PMode_Option = PMode_P1;
				Flash_Read((uint8_t *)(&Param),sizeof(Param));
				Set_Time=Param.P_Param[PMode_Option][1];//开机设置设定时间为20min
				Ctrl_Time=Param.P_Param[PMode_Option][1];//开机设置实际时间为20min
				Set_Temp=Param.P_Param[PMode_Option][0];//开机设置设定温度37℃
				SetOK_Flag = 1;	
				PMode_Mode = 1;//梯度模式
				sys.CtrlTemp_Mode = 0;
				sys.Run_Status = 0;
			}
		}
		else
		{		
			Ctrl_Time = Time;				
			sys.DownTime_Status = 0;//关闭
			sys.Run_Status = 0;//关闭
		}
		Beep_Flash = 30;
	}
}

/*
*****************************************************************
 * 函数原型：void LCD_Display(void)
 * 功    能：屏幕显示
*****************************************************************
*/
void LCD_Display(void)
{  
    /*********************显示实际温度********************/
	Deal_Temp();
    Dis_RelTemp(Display_RelTemp);

    /*********************显示设定温度********************/
    Display_CtrlTemp = Set_Temp;
    Dis_SetTemp(Display_CtrlTemp);

    /*********************显示实际时间********************/
    Display_CtrlTime = Ctrl_Time;
    Dis_RelTime(Display_CtrlTime);

    /*********************显示设定时间********************/
    Display_SetTime = Set_Time;
    Dis_SetTime(Display_SetTime);
	
	Display_RunPMode(PMode_Status,PMode_Mode,PMode_P1,PMode_P2);//P模式
}
