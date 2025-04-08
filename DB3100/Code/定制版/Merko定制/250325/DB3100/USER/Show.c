#include "Show.h"

/**********全局变量**********/
int32_t rel_time;//实时时间
int32_t set_time;//设定时间
uint8_t time_status;//时间显示模式
uint8_t Set_Mode_Enable;//P键进入设置模式 0：模式设置不予显示 1：模式设置显示
uint8_t run_mode_flag;//进入P时显示
uint8_t Select_Option;//设置时当前设置的选项
uint16_t Twinkle_Time;//闪烁的时间
uint16_t Twinkle_On;//闪烁倒计时
uint8_t circle_dis;//梯度模式下外圈转动显示（本代码不操作此寄存器，单加热）
uint8_t circle_dis_flag;//外圈开始转动（本代码不操作此寄存器，单加热）
uint8_t mode_flag_p1;//梯度模式下P1的闪烁（本代码不操作此寄存器，单加热）
uint8_t mode_flag_p2;//梯度模式下P1的闪烁（本代码不操作此寄存器，单加热）
uint8_t mode_run_p1;//梯度模式下P1的值（本代码不操作此寄存器，单加热）
uint8_t mode_run_p2;//梯度模式下P1的值（本代码不操作此寄存器，单加热）
uint8_t set_mode_p;//P模式下切换梯度模式还是就记忆模式 1：梯度模式 0：p模式（本代码不操作此寄存器，单加热）
uint8_t ADD_Wait_Count;//升温显示缓慢上升
uint8_t SetTime_State;//未设定时间显示“----”

/**********局部变量**********/
uint8_t FIRST_Tab[] = {0xee, 0x24, 0xba, 0xb6, 0x74, 0xd6, 0xde, 0xa4, 0xfe, 0xf6};
uint8_t LAST_Tab[] = {0x77, 0X24, 0x5d, 0x6d, 0x2e, 0x6b, 0x7b, 0x25, 0x7f, 0x6f};
uint8_t MID_Tab[] =  {0x77, 0x12, 0x5d, 0x5b, 0x3a, 0x6b, 0x6f, 0x52, 0x7f, 0x7b};
uint8_t Tab[4] = {0, 0, 0, 0};
int Dis_Rel_Temp;//显示实际温度
int Dis_Set_Temp;//显示温度
int Dis_Rel_Time;//实时时间
int Dis_Set_Time;//设定时间
uint8_t temp_flag;//选中设置温度时闪烁
uint8_t time_flag;//选中设置时间时闪烁
uint8_t mode_flag;//选中设置模式时闪烁
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
	if(Run_Status == 1 && ADD_Mode == 2)
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
	if(Run_Status == 1 && set_temp > Dis_Rel_Temp)
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
 * 函数原型： void Circle_Go(void)
 * 功    能： 跑梯度模式-单加热没有用到
*****************************************************************
*/
void Circle_Go(void)
{
//    run_mode_flag = 1;//不固定显示外框
//    circle_dis_flag = 1;//外框开始跑圈（本代码不操作此寄存器，单加热）
    if((circle_dis_flag ) && (Run_Status > 0))//跑梯度标志位置一，系统启动
    {
        circle_dis -= 1;//显示--
        if(circle_dis < 1)//小于1表示一圈跑完
        circle_dis = 12;//从头跑
    }
}

/*
*****************************************************************
 * 函数原型： void Cheak_ShowFlag(uint16_t dT)
 * 功    能： 闪烁检测
 * 输    入:  dT:执行周期
 * 参    数： uint16_t dT
*****************************************************************
*/
void Cheak_ShowFlag(uint16_t dT)
{
    if(Select_Option == 0 || Key_Status)//如果没在设置选项中，则都点亮，不闪烁
    {
        temp_flag = 0;//点亮
        time_flag = 0;//点亮
        mode_flag = 0;//点亮
        return;
    }
    Twinkle_Time += dT;//闪烁计时
    Twinkle_On -= dT;//无操作闪烁倒计时
    if(Select_Option == 2)//设置温度
    {
        if(Twinkle_Time % 500 == 0)//每0.5S转换状态
        {
            temp_flag = ~ temp_flag;
            time_flag = 0;
            mode_flag = 0;
        }
    }
    else if(Select_Option == 3)//设置时间
    {
        if(Twinkle_Time % 500 == 0)//每0.5S转换状态
        {
            time_flag = ~ time_flag;
            temp_flag = 0;
            mode_flag = 0;
        }
    }
    else if(Select_Option == 1)//设置模式
    {
        if(Twinkle_Time % 500 == 0)//每0.5S转换状态
        {
            temp_flag = 0;
            time_flag = 0;
            mode_flag = ~ mode_flag;
        }
    }
    else if(Select_Option == 4)//在梯度模式下闪烁P1（本代码不操作此寄存器，单加热）
    {
        if(Twinkle_Time % 500 == 0)//每0.5S转换状态
        {
            mode_flag_p1 = ~mode_flag_p1;
            mode_flag_p2 = ~mode_flag_p2;
        }
    }
    else if(Select_Option == 5)//在梯度模式下闪烁P2（本代码不操作此寄存器，单加热）
    {
        if(Twinkle_Time % 500 == 0)//每0.5S转换状态
        {
            mode_flag_p1 = ~mode_flag_p1;
            mode_flag_p2 = ~mode_flag_p2;
        }
    }
    if(Twinkle_Time == 10000)//闪烁6次，约10S
    {
        Twinkle_Time = 0;
    }
    if(Twinkle_On == 0)//如果闪烁倒计时完了
    {
        Twinkle_Time = 0;//把闪烁计时清零
        setting_Mode = 0;
        Select_Option = 0;//选项闪烁结束
		SetOK_Flag = 1;
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
    
	if(Run_Status == 1)
	{
		if(set_temp > Dis_Rel_Temp)
		{
			if(tempicn_flag)//开始控制温度时
				Tab[2]=Tab[2]|0x80;//加热图标
			else
				Tab[2]=Tab[2]|0x00;//不显示加热图标
		}
		else 
			Tab[2]=Tab[2]|0x80;//加热图标
	}


    Tab[3] = Tab[3] | 0x80;//实际温度的小数点
    Tab[0] = Tab[0] | 0x80;//设置温度的℃符号

    if(Set_Mode_Enable)//（本代码不操作此寄存器，单加热）
    {
        if((((circle_dis<10)&&(circle_dis>3))&&(circle_dis!=0))||(circle_dis==13))
        {
            Tab[1]=Tab[1]|0x80;//模式外圈显示
        }
        else if((circle_dis==3)||(circle_dis==0))
            Tab[1]=Tab[1]&0x7f;//模式外圈不显示
        if(run_mode_flag==0)
            Tab[1]=Tab[1]|0x80;//模式外圈显示
    }
    else
    {
        Tab[1]=Tab[1]&0x7f;//模式外圈不显示
    }
    write_addr_dat_n(0, Tab[0], 1);
    write_addr_dat_n(2, Tab[1], 1);
    write_addr_dat_n(4, Tab[2], 1);
    write_addr_dat_n(6, Tab[3], 1);
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

    if(temp_flag)//闪烁
    {
        Tab[0] = 0;
        Tab[1] = 0;
        Tab[2] = 0;
        Tab[3] = 0;
    }

    write_addr_dat_n(32, Tab[3], 1);
    write_addr_dat_n(34, Tab[2], 1);
    write_addr_dat_n(36, Tab[1], 1);
    write_addr_dat_n(38, Tab[0], 1);
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
    if(time_status ==0)//在秒显示状态下
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
	{
		Tab[2]=Tab[2]|0x80;//实时时间冒号
	}
	else
	{
		Tab[2]=Tab[2]|0x00;//不显示实时时间冒号
	}
	
	if(SetTime_State)//未设定时间显示“----”
    {
        Tab[3]= 0x08;
        Tab[2]= 0x08;
        Tab[1]= 0x08;
        Tab[0]= 0x08;
    }
    
//    Tab[0]=Tab[0]|0x80;//制冷图标

    write_addr_dat_n(8,Tab[0], 1);
    write_addr_dat_n(10,Tab[1], 1);
    write_addr_dat_n(12,Tab[2], 1);
    write_addr_dat_n(14,Tab[3], 1);
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
        time_status=1;//单位变成分
    }
    else
        time_status=0;//不然就是秒

    if(time_status ==0)//在秒显示状态下
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
	{
		Tab[1]=Tab[1]|0x80;//设定时间冒号
	}
	else
	{
		Tab[1]=Tab[1]|0x00;//不显示设定时间冒号
	}
    if(SetTime_State)//未设定时间显示“----”
    {
        Tab[3]= 0x08;
        Tab[2]= 0x08;
        Tab[1]= 0x08;
        Tab[0]= 0x08;
    }
    
    if(time_flag)//闪烁
    {
        Tab[0]=0;
        Tab[1]=0;
        Tab[2]=0;
        Tab[3]=0;
    }

   
    if(time_status)
        Tab[3]=Tab[3]|0x80;//分钟单位显示
    else
        Tab[2]=Tab[2]|0x80;//秒单位显示

    write_addr_dat_n(16,Tab[3], 1);
    write_addr_dat_n(18,Tab[2], 1);
    write_addr_dat_n(20,Tab[1], 1);
    write_addr_dat_n(22,Tab[0], 1);
}

/*
*****************************************************************
 * 函数原型： void Dis_RunMode(uint8_t E,uint8_t P,uint8_t P1,uint8_t P2)
 * 功    能： 显示运行模式
 * 输    入:  E：P模式框显示   P：记忆和梯度选择 P1：梯度模式下P1值 P2：梯度模式下P2值 
 * 参    数： uint8_t E,uint8_t P,uint8_t P1,uint8_t P2
*****************************************************************
*/
void Dis_RunMode(uint8_t E,uint8_t P,uint8_t P1,uint8_t P2)
{
    static uint8_t tab1=0;
    if(E)//进入P模式显示
    {
        if(circle_dis)//如果标准位大于一
        {
            switch(circle_dis)//用switch语句实现动画转圈
            {
                case 0:write_addr_dat_n(24,0x00, 1);
                    break;
                case 1: tab1|=0X01;tab1&=0Xbf; write_addr_dat_n(24,tab1, 1);
                    break;
                case 2: tab1|=0X02;tab1&=0X7f; write_addr_dat_n(24,tab1, 1);
                    break;
                case 3: tab1|=0X04; write_addr_dat_n(24,tab1, 1);
                    break;
                case 4: tab1|=0X08; write_addr_dat_n(24,tab1, 1);
                    break;
                case 5: tab1|=0X10; write_addr_dat_n(24,tab1, 1);
                    break;
                case 6: tab1|=0X20; write_addr_dat_n(24,tab1, 1);
                    break;
                case 7: tab1|=0X40;tab1&=0XFE; write_addr_dat_n(24,tab1, 1);
                    break;
                case 8: tab1|=0X80;tab1&=0XFC; write_addr_dat_n(24,tab1, 1);
                    break;
                case 9: tab1&=0XFB; write_addr_dat_n(24,tab1, 1);
                    break;
                case 10: tab1&=0XF7; write_addr_dat_n(24,tab1, 1);
                    break;
                case 11: tab1&=0XEF; write_addr_dat_n(24,tab1, 1);
                    break;
                case 12: tab1&=0XCF; write_addr_dat_n(24,tab1, 1);
                    break;
                case 13: tab1&=0XCF; write_addr_dat_n(24,0xff, 1);
                    break;
            }
        }

        if(run_mode_flag==0)//加入不在p模式下
            write_addr_dat_n(24,0xff, 1);//外框消失，方便转圈


        //模式选择
        if(P)//梯度模式下
        {
            Tab[2]=MID_Tab[P1];//模式一
            Tab[1]=0X08;//-
            Tab[0]=MID_Tab[P2];//模式二
        }
        else//记忆模式下
        {
            Tab[0]=MID_Tab[run_mode];//显示模式数
			Tab[1]=0X08;//-
			Tab[2]=0x7c;//显示字母P
        }

        if(mode_flag)//闪烁显示
        {
            Tab[0]=0;
            Tab[1]=0;
            Tab[2]=0;
        }

        if(mode_flag_p1)//梯度模式下P1闪烁（本代码不操作此寄存器，单加热）
            Tab[2]=0;
        if(mode_flag_p2)//梯度模式下P2闪烁（本代码不操作此寄存器，单加热）
            Tab[0]=0;

        //模式外圈显示
        if((((circle_dis<11)&&(circle_dis>4))&&(circle_dis!=0))||(circle_dis==13))
            Tab[2]=Tab[2]|0x80;//模式外圈显示
        else if((circle_dis==4)||(circle_dis==0))
            Tab[2]=Tab[2]&0x7f;//模式外圈不显示
        if(circle_dis==0)
            Tab[2]=Tab[2]|0x80;//模式外圈显示
        if((((circle_dis<13)&&(circle_dis>6))&&(circle_dis!=0))||(circle_dis==13))
            Tab[0]=Tab[0]|0x80;//模式外圈显示
        else if((circle_dis==6)||(circle_dis==0))
            Tab[0]=Tab[0]&0x7f;//模式外圈不显示
        if(circle_dis==0)
            Tab[0]=Tab[0]|0x80;//模式外圈显示
        if((((circle_dis<12)&&(circle_dis>5))&&(circle_dis!=0))||(circle_dis==13))
            Tab[1]=Tab[1]|0x80;//模式外圈显示
        else if((circle_dis==5)||(circle_dis==0))
            Tab[1]=Tab[1]&0x7f;//模式外圈不显示
        if(circle_dis==0)
            Tab[1]=Tab[1]|0x80;//模式外圈显示
    }
    else//不显示
    {
        Tab[0]=0;
        Tab[1]=0;
        Tab[2]=0;
        write_addr_dat_n(24,0x00, 1);
    }

    write_addr_dat_n(26,Tab[0], 1);
    write_addr_dat_n(28,Tab[1], 1);
    write_addr_dat_n(30,Tab[2], 1);
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
    if(ADD_Wait_Count)//加入慢速上升标志位大于一并且升温状态在慢速上升时
    {
        T += dT;
        if(T == 1000)//1S
        {
            ADD_Wait_Count--;//慢速上声标志位--
            if(ADD_Wait_Count == 0)//慢速上升标志位等于0时
                ADD_Mode = 2;//进入稳定温度模式
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
    static int Temp_New,Temp_Last;//现在温度、之前温度
	if(Run_Status == 0)//没启动的情况下
    {
		ADD_Mode = 0;
		Dis_Rel_Temp = rel_temp;      
    }
    else//启动的情况下
    {
        if(ADD_Mode == 0)//判断数据处理显示
        {     
		   if(set_temp > Dis_Rel_Temp)//设定温度大于显示温度
		   { 
				ADD_Mode = 1;//进入加热模式下
				Temp_New = 0;//将之前的记入值清零
				Temp_Last = 0;//将之前的记入值清零  
			}
		   else
		   {
				ADD_Mode = 4;//进入降温模式下
				Temp_New = 0;//将之前的记入值清零
				Temp_Last = rel_temp;//将之前的记入值清零  
			}
        }
        if(ADD_Mode==1)//在加热模式下
        {
			if(Dis_Rel_Temp >= set_temp - 20)//实际温度大于等于设定温度-2℃
            {
                ADD_Wait_Count = (-(Dis_Rel_Temp-set_temp)*10);//200S的缓慢升温显示  
				ADD_Mode = 3;
				return;
            }
            Temp_New = rel_temp;//记录当前温度
            if(Temp_New > Temp_Last)//当前温度大于上一次温度
                Dis_Rel_Temp = Temp_New;//显示当前温度
            else//当前温度小于上一次温度
            {
                Dis_Rel_Temp = Temp_Last;//显示上一次温度，不让温度小于当前温度。呈现攀升温度的现象
                Temp_New = Temp_Last;//将上一次温度赋值给当前温度
            }
            Temp_Last = Temp_New;//将当前温度保存 
			
        }
        else if(ADD_Mode == 2)//温度稳定模式下
        {
			Dis_Rel_Temp = set_temp;//显示当前显示温度
        }   
		else if(ADD_Mode == 3)//等待降温后开始升温
        {
			if(Dis_Rel_Temp < set_temp)
				Dis_Rel_Temp=(set_temp-20)+(20-(ADD_Wait_Count)*2/20);//缓慢显示数值
			else if(Dis_Rel_Temp > set_temp)
				Dis_Rel_Temp=(set_temp+20)-(20-(ADD_Wait_Count)*2/20);//缓慢显示数值
			else
				ADD_Mode = 2;
        }  
		else if(ADD_Mode == 4)//降温模式下
        {
            if(Dis_Rel_Temp <= set_temp + 20)//实际温度小于等于设定温度
            {
                ADD_Wait_Count = (-(set_temp-Dis_Rel_Temp)*10);
				ADD_Mode = 3;
				return;
            }
            Temp_New = rel_temp;//记录当前温度
            if(Temp_New < Temp_Last)//当前温度小于上一次温度
                Dis_Rel_Temp = Temp_New;//显示当前温度
            else//当前温度大于上一次温度
            {
                Dis_Rel_Temp = Temp_Last;//显示上一次温度，不让温度大于当前温度。呈现下降温度的现象
                Temp_New = Temp_Last;//将上一次温度赋值给当前温度
            }
            Temp_Last = Temp_New;//将当前温度保存
        }  		
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
    Deal_Temp();
    
    /*********************显示实际温度********************/
    Dis_RelTemp(Dis_Rel_Temp);

    /*********************显示设定温度********************/
    Dis_Set_Temp = set_temp;
    Dis_SetTemp(Dis_Set_Temp);

    /*********************显示实际时间********************/
    Dis_Rel_Time = rel_time;
    Dis_RelTime(Dis_Rel_Time);

    /*********************显示设定时间********************/
    Dis_Set_Time = set_time;
    Dis_SetTime(Dis_Set_Time);

    Dis_RunMode(Set_Mode_Enable,set_mode_p,mode_run_p1,mode_run_p2);//P模式

}
