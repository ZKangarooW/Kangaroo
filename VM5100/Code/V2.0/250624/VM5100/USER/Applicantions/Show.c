#include "Show.h"

/**********全局变量声明******/
uint16_t Twinkle_Time1,Twinkle_Time2;//闪烁时间

/**********局部变量声明******/
uint8_t Run_Flag;//运行闪烁图标
uint8_t Speed_ShowFlag,Time_ShowFlag;//速度、时间显示的标志位 0:常亮 1：熄灭
uint8_t DOWNL_Tab[]={0x77,0X24,0x5d,0x6d,0x2e,0x6b,0x7b,0x25,0x7f,0x6f};
uint8_t UP_Tab[]={0xee,0x24,0xba,0xb6,0x74,0xd6,0xde,0xa4,0xfe,0xf6};
uint8_t DOWNR_Tab[]={0xee,0x48,0xba,0xda,0x5c,0xd6,0xf6,0x4a,0xfe,0xde};

/*
*****************************************************************
 * 函数原型： void Check_ShowFlag(float dT)
 * 功    能： 闪烁检测
 * 输    入:  dT:执行周期
 * 参    数： uint16_t dT
*****************************************************************
*/
void Check_ShowFlag(float dT)
{
    if(sys.Run_Status)//运行时
        Run_Flag = ~Run_Flag;//运行时闪烁
	
	if(Twinkle_Time1 && EC11A[1].EC11A_Knob==0)//闪烁和没有操作旋钮时
    {
        Twinkle_Time1 -= 0.5f;//闪烁计时
		Speed_ShowFlag = ~Speed_ShowFlag;//速度闪烁
        if(Twinkle_Time1 == 0)//如果闪烁结束
        {
			SpeedSet_Flag = 1;
			Beep_Time = 0.1;
        }
    }
	else
		Speed_ShowFlag = 0;//速度闪烁清零

	if(Twinkle_Time2 && EC11A[0].EC11A_Knob==0)//闪烁和没有操作旋钮时
    {
        Twinkle_Time2 -= 0.5f;//闪烁计时
		Time_ShowFlag = ~Time_ShowFlag;//时间闪烁
        if(Twinkle_Time2 == 0)//如果闪烁结束
        {
			TimeSet_Flag = 1;
            Beep_Time = 0.1;
        }        
    }
	else
		Time_ShowFlag = 0;//时间闪烁清零
}

/*
*****************************************************************
 * 函数原型： void LCD_Light(short LCD_Status) 
 * 功    能： 打开和关闭背光显示
 * 输    入:  LCD_Status：1、打开背光 0：关闭背光
 * 参    数： short LCD_Status
*****************************************************************
*/
void LCD_Light(short LCD_Status)
{
    switch(LCD_Status)
    {
        case 0 :
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);//不输出pwm
            break ;
        case 1 :
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 45);//不输出pwm
            break ;
    }
}

/*
*****************************************************************
 * 函数原型： void Display_Set_Time(uint32_t dis_set_time)
 * 功    能： 写最左边的设定时间
 * 输    入:  dis_set_time 左边最下面的时间
 * 参    数： uint32_t dis_set_time
*****************************************************************
*/
void Display_Set_Time(uint32_t dis_set_time)
{
	uint8_t seg1,seg2,seg3,seg4;
	seg1=0;seg2=0;seg3=0;seg4=0;;
	uint8_t SH,H,SM,M;//时间的单位取值
	
	SH=dis_set_time/3600/10;//计算十位单位的小时数
	H=dis_set_time/3600%10;//计算个位单位的小时数
	SM=dis_set_time%3600/60/10;//计算十分位单位的分钟数
	M=dis_set_time%3600/60%10;//计算个分位单位的分钟数
	
	seg1 = DOWNL_Tab[SH];//时间十位单位的小时数
	seg2 = DOWNL_Tab[H];//时间个位单位的小时数
	seg3 = DOWNL_Tab[SM];//时间十分位单位的分钟数
	seg4 = DOWNL_Tab[M];//时间个分位单位的分钟数

	seg2 = seg2|0x80;//设定时间冒号（下面）
//	seg3 = seg3|0x80;//设定时间小数点（下面）
	seg4 = seg4|0x80;//设定时间min文本显示
	
	if(Time_State == 0)//没有设置时间,显示“--:--”
	{
		seg1=(seg1&0x80)|0x08;
		seg2=(seg2&0x80)|0x08;
		seg3=(seg3&0x80)|0x08;
		seg4=(seg4&0x00)|0x08;//0x00将单位"min"去掉
	}
	
	if(Time_ShowFlag && EC11A[0].EC11A_Knob == 0 && Time_State == 1)//时间到和旋钮无操作时
	{
		seg1&=0x00;
		seg2&=0x00;
		seg3&=0x00;
		seg4&=0x80;
	}
	
	Write_Addr_Dat_N(0, seg1,1);
	Write_Addr_Dat_N(2, seg2,1);
 	Write_Addr_Dat_N(4, seg3,1);
	Write_Addr_Dat_N(6, seg4,1);
}

/*
*****************************************************************
 * 函数原型： void Display_Rel_Time(uint32_t dis_rel_time)
 * 功    能： 写最左边的设定时间
 * 输    入:  dis_rel_time 左边最下面的时间
 * 参    数： uint32_t dis_rel_time
*****************************************************************
*/
void Display_Rel_Time(uint32_t dis_rel_time)
{
	uint8_t seg1,seg2,seg3,seg4;
	seg1=0;seg2=0;seg3=0;seg4=0;;
	uint8_t SH,H,SM,M;//时间的单位取值
	
	SH=dis_rel_time/3600/10;//计算十位单位的小时数
	H=dis_rel_time/3600%10;//计算个位单位的小时数
	SM=dis_rel_time%3600/60/10;//计算十分位单位的分钟数
	M=dis_rel_time%3600/60%10;//计算个分位单位的分钟数
	
	seg1 = UP_Tab[SH];//时间十位单位的小时数
	seg2 = UP_Tab[H];//时间个位单位的小时数
	seg3 = UP_Tab[SM];//时间十分位单位的分钟数
	seg4 = UP_Tab[M];//时间个分位单位的分钟数
	
//	seg1 = seg1|0x01;//温度符号“℃”图标（下面）
	seg2 = seg2|0x01;//实际时间冒号（上面）
//	seg3 = seg3|0x01;//实际时间小数点（上面）
	seg4 = seg4|0x01;//时间图标（上面）
	
	if(Time_State == 0)//没有设置时间,显示“--:--”
	{
		seg1=(seg1&0x01)|0x10;
		seg2=(seg2&0x01)|0x10;
		seg3=(seg3&0x01)|0x10;
		seg4=(seg4&0x01)|0x10;
	}
    if(sys.Run_Status == 1 && Run_Flag > 1 && DownTime_Over == 0 && Time_State == 1)//运行时
    {
		seg2&=0xFE;//实际时间冒号（上面）消失
		seg4&=0xFE;//时间图标（上面）消失
	}
	Write_Addr_Dat_N(54, seg1,1);
	Write_Addr_Dat_N(52, seg2,1);
 	Write_Addr_Dat_N(50, seg3,1);
	Write_Addr_Dat_N(48, seg4,1);
}

/*
*****************************************************************
 * 函数原型： void Display_SetSpeed(uint16_t dis_set_speed)
 * 功    能： 写最右边的设定速度
 * 输    入:  dis_set_speed 右边最下面的速度
 * 参    数： uint16_t dis_set_speed
*****************************************************************
*/
void Display_Set_Speed(uint16_t dis_set_speed)
{
	uint8_t seg1,seg2,seg3,seg4;
	seg1=0;seg2=0;seg3=0;seg4=0;;
	
	//设定速度
	if(dis_set_speed>999)
	{	
		seg1=DOWNR_Tab[dis_set_speed/1000]; 
		seg2=DOWNR_Tab[dis_set_speed/100%10]; 
		seg3=DOWNR_Tab[dis_set_speed/10%10]; 
		seg4=DOWNR_Tab[dis_set_speed%10];
	}	
	else if(dis_set_speed >99)
	{
		seg1=DOWNR_Tab[0]; 
		seg2=DOWNR_Tab[dis_set_speed/100];
		seg3=DOWNR_Tab[dis_set_speed/10%10];
		seg4=DOWNR_Tab[dis_set_speed%10];
	}
	else if(dis_set_speed >9)
	{
		seg1=DOWNR_Tab[0]; 
		seg2=DOWNR_Tab[0];
		seg3=DOWNR_Tab[dis_set_speed/10];
		seg4=DOWNR_Tab[dis_set_speed%10];
	}	
	else
	{
		seg1=DOWNR_Tab[0]; 
		seg2=DOWNR_Tab[0];
		seg3=DOWNR_Tab[0];
		seg4=DOWNR_Tab[dis_set_speed%10];
	}	
	
	if(Speed_ShowFlag && EC11A[1].EC11A_Knob == 0)//时间到和旋钮无操作时
	{
		seg1&=0x00;
		seg2&=0x00;
		seg3&=0x00;
		seg4&=0x01;
	}
	seg4 = seg4|0x01;//rpm文本显示
  
	Write_Addr_Dat_N(26, seg1,1);
	Write_Addr_Dat_N(28, seg2,1);
 	Write_Addr_Dat_N(30, seg3,1);
	Write_Addr_Dat_N(32, seg4,1);
}

/*
*****************************************************************
 * 函数原型： void Display_RelSpeed(uint16_t dis_rel_speed)
 * 功    能： 写最右边的实际速度
 * 输    入:  dis_rel_speed 右边最上面的速度
 * 参    数： uint16_t dis_rel_speed
*****************************************************************
*/
void Display_Rel_Speed(uint16_t dis_rel_speed)
{
	uint8_t seg1,seg2,seg3,seg4;
	seg1=0;seg2=0;seg3=0;seg4=0;;
	
	//设定速度
	if(dis_rel_speed>999)
	{	
		seg1=UP_Tab[dis_rel_speed/1000]; 
		seg2=UP_Tab[dis_rel_speed/100%10]; 
		seg3=UP_Tab[dis_rel_speed/10%10]; 
		seg4=UP_Tab[dis_rel_speed%10];
	}	
	else if(dis_rel_speed >99)
	{
		seg1=UP_Tab[0]; 
		seg2=UP_Tab[dis_rel_speed/100];
		seg3=UP_Tab[dis_rel_speed/10%10];
		seg4=UP_Tab[dis_rel_speed%10];
	}
	else if(dis_rel_speed >9)
	{
		seg1=UP_Tab[0]; 
		seg2=UP_Tab[0];
		seg3=UP_Tab[dis_rel_speed/10];
		seg4=UP_Tab[dis_rel_speed%10];
	}	
	else
	{
		seg1=UP_Tab[0]; 
		seg2=UP_Tab[0];
		seg3=UP_Tab[0];
		seg4=UP_Tab[dis_rel_speed%10];
	}	
	seg1 = seg1|0x01;//圆图标的尾巴
//	seg2 = seg2|0x01;//顺时针的三角形
	seg3 = seg3|0x01;//逆时针的三角形
//	seg4 = seg4|0x01;//加热图标
//	if(sys.Run_Status == 1 && Run_Flag > 1 && Set_Speed > 0 && Rel_Speed)//运行时
	if(sys.Run_Status == 1 && Run_Flag > 1 )//运行时
    {
        seg1&=0xfe;//圆图标的尾巴消失
//	seg2&=0xfe;//顺时针的三角形消失
        seg3&=0xfe;//逆时针的三角形消失
    }
	Write_Addr_Dat_N(46, seg1,1);
	Write_Addr_Dat_N(44, seg2,1);
 	Write_Addr_Dat_N(42, seg3,1);
	Write_Addr_Dat_N(40, seg4,1);
}

/*
*****************************************************************
 * 函数原型： void Deal_Speed(void)
 * 功    能： 速度显示处理
*****************************************************************
*/
void Deal_Speed(void)
{
    /**********SpeedL1_ADD_Mode**********/
    if(sys.Run_Status == 1)//启动的情况下
    {
        if(Speed_ADDMode == 0)//在电机控制中，速度未处理
        {
            if(Ctrl_Speed >= Display_RelSpeed)//控制速度大于实际速度
            {
                Speed_New =0;//现在的速度清零
                Speed_Last = 0;//之前的速度清零
                Speed_ADDMode = 1;//进入加速模式下
            }
            else if(Ctrl_Speed < Display_RelSpeed)//控制速度小于实际速度
            {
                Speed_New=0;//现在的速度清零
                Speed_Last = Display_RelSpeed;//之前的速度等于当前显示速度
                Speed_ADDMode = 2;//进入减速模式下
            }
        }
        if(Speed_ADDMode==1)//在进入加速模式下
        { 
			if(sys.Motor_Stop == 0)
			{
				if(Rel_Speed >= Ctrl_Speed)//实际速度大于等于控制速度
				{
					Speed_ADDMode = 3;//进入稳定模式
					return;
				}
			}
            Speed_New = Rel_Speed;//记录当前速度
            if(Speed_New > Speed_Last)//当前速度大于上一次速度
                Display_RelSpeed = Speed_New;//显示当前速度
            else//当前速度小于上一次速度
            {
                Display_RelSpeed = Speed_Last;//显示上一次速度，不让速度小于当前速度。呈现攀升速度的现象
                Speed_New = Speed_Last;//将上一次速度赋值给当前速度
            }
            Speed_Last = Speed_New;//将当前速度保存    
        }
        else if(Speed_ADDMode == 2)//速度下降模式下
        {
			if(sys.Motor_Stop == 0)
			{
				if(Param.type==0)
				{
					if(Rel_Speed-500 <= Ctrl_Speed)//实际速度小于等于控制速度
					{
						Speed_ADDMode = 3;//稳定模式
						return;
					}
				}
				else if(Param.type == 1)
				{
					if(Rel_Speed <= Ctrl_Speed)//实际速度小于等于控制速度
					{
						Speed_ADDMode = 3;//稳定模式
						return;
					}
				}
			}
			if(Param.type==0)
			{
				Speed_New = Rel_Speed-500;//记录当前速度
			}
			else if(Param.type == 1)
			{
				Speed_New = Rel_Speed;//记录当前速度
			}
            if(Speed_New < Speed_Last)//当前速度小于上一次速度
                Display_RelSpeed = Speed_New;//显示当前速度
            else//当前速度大于上一次速度
            {
                Display_RelSpeed = Speed_Last;//显示上一次速度，不让速度大于当前速度。呈现下降速度的现象
                Speed_New = Speed_Last;//将上一次速度赋值给当前速度
            }
            Speed_Last = Speed_New;//将当前速度保存
            
        }
        else if(Speed_ADDMode == 3)//速度稳定模式下
        {
            Display_RelSpeed = Ctrl_Speed;//显示控制速度
        }
	}
	else
	{
		Speed_New =0;//现在的速度清零
		Speed_Last = 0;//之前的速度清零
		Speed_ADDMode = 0;
		Display_RelSpeed = 0;
	}
}

/*
*****************************************************************
 * 函数原型： void Show_Display(void)
 * 功    能： 显示屏幕内容
*****************************************************************
*/
void Show_Display(void)
{	
	Deal_Speed();
	Display_SetSpeed = Set_Speed;
	Display_SetTime = Set_Time;//显示设定时间
	Display_CtrlTime = Ctrl_Time+59;//显示实际时间

	
    Display_Set_Time(Display_SetTime);
	Display_Rel_Time(Display_CtrlTime);
	Display_Set_Speed(Display_SetSpeed);
	Display_Rel_Speed(Display_RelSpeed);
}
