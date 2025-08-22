#include "Show.h"

/**********全局变量声明******/
float Speed_Twinkle_Time,Time_Twinkle_Time;//速度闪烁时间和时间闪烁时间

/**********局部变量声明******/
uint8_t TimeIcn_ShowFlag,SpeedIcn_ShowFlag;//时间图标闪烁和速度图标闪烁
uint8_t Speed_ShowFlag,Time_ShowFlag;//速度、时间显示的标志位 0:常亮 1：熄灭
uint8_t DOWNL_Tab[]={0x77,0X24,0x5d,0x6d,0x2e,0x6b,0x7b,0x25,0x7f,0x6f};//0·9
uint8_t UP_Tab[]={0xee,0x24,0xba,0xb6,0x74,0xd6,0xde,0xa4,0xfe,0xf6};//0·9
uint8_t DOWNR_Tab[]={0xee,0x48,0xba,0xda,0x5c,0xd6,0xf6,0x4a,0xfe,0xde};//0·9

/*
*****************************************************************
 * 函数原型：static void Icn_Twinkle(float dT)
 * 功    能：图标闪烁
 * 输    入: dT:执行周期
 * 参    数：float dT
 * 调    用：内部调用
*****************************************************************
*/
static void Icn_Twinkle(float dT)
{
	static float T;
	if(sys.Run_Status)		
	{
		T += dT;
		if(T >= 0.5f)
		{
			SpeedIcn_ShowFlag = ~SpeedIcn_ShowFlag;//转速图标闪烁;
			if(Time.Rel && (SpeedIcn_ShowFlag != TimeIcn_ShowFlag))
				TimeIcn_ShowFlag = ~TimeIcn_ShowFlag;//时间图标闪烁;
			else
			{
				TimeIcn_ShowFlag = 0;
			}
			T = 0;
		}
	}
	else
	{
		SpeedIcn_ShowFlag = 0;//不显示速度图标
		TimeIcn_ShowFlag = 0;//不显示时间图标
	}
}

/*
*****************************************************************
 * 函数原型：static void Check_ShowFlag(float dT)
 * 功    能：闪烁检测
 * 输    入: dT:执行周期
 * 参    数：float dT
 * 调    用：内部调用
*****************************************************************
*/
static void Check_ShowFlag(float dT)
{
	static float Speed_T,Time_T;
	if(Speed_Twinkle_Time && !EC11A[1].EC11A_Knob)//速度闪烁和没有操作按键时
    {
		Speed_T += dT;
		if(Speed_T >= 0.5f)
		{
			Speed_Twinkle_Time -= 0.5;//闪烁计时
			Speed_ShowFlag = ~Speed_ShowFlag;//速度闪烁
			if(Speed_Twinkle_Time == 0)//如果闪烁结束
			{
				SpeedSet_Flag = 1;//进入速度设定
				Beep_Time = 0.1;//蜂鸣器响0.1S
			} 
			Speed_T = 0;		
		}			
    }
	else
	{
		Speed_ShowFlag = 0;//常亮
		Speed_T = 0;
	}
	
	if(Time_Twinkle_Time && !EC11A[0].EC11A_Knob)//时间闪烁和没有操作按键时
    {
		Time_T += dT;
		if(Time_T >= 0.5f)
		{
			Time_Twinkle_Time -= 0.5;//闪烁计时
			Time_ShowFlag = ~Time_ShowFlag;//时间闪烁
			if(Time_Twinkle_Time == 0)//如果闪烁结束
			{
				TimeSet_Flag = 1;//进入时间设定
				Beep_Time = 0.1;//蜂鸣器响0.1S
			} 
			Time_T = 0;			
		}			
    }
	else
	{
		Time_ShowFlag = 0;//常亮
		Time_T = 0;
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
	Check_ShowFlag(dT);//闪烁检测
	Icn_Twinkle(dT);//图标闪烁
}

/*
*****************************************************************
 * 函数原型：void Display_Set_Time(int32_t dis_set_time)
 * 功    能：写最左边的设定时间
 * 输    入：dis_set_time:左边最下面的时间
 * 参    数：int32_t dis_set_time
*****************************************************************
*/
void Display_Set_Time(int32_t dis_set_time)
{
	uint8_t seg1,seg2,seg3,seg4;
	seg1=0;seg2=0;seg3=0;seg4=0;
	uint8_t SH,H,SM,M;//时间的单位取值
	
	if(!Time_ShowFlag)//显示时间表示为0
	{
		if(dis_set_time)//设定时间大于0
		{
			SH=dis_set_time/3600/10;//计算十位单位的小时数
			H=dis_set_time/3600%10;//计算个位单位的小时数
			SM=dis_set_time%3600/60/10;//计算十分位单位的分钟数
			M=dis_set_time%3600/60%10;//计算个分位单位的分钟数
			seg1 = DOWNL_Tab[SH];//时间十位单位的小时数
			seg2 = DOWNL_Tab[H];//时间个位单位的小时数
			seg3 = DOWNL_Tab[SM];//时间十分位单位的分钟数
			seg4 = DOWNL_Tab[M];//时间个分位单位的分钟数
		}
		else//没有设置时间,显示“--:--”
		{
			seg1=(seg1&0x80)|0x08;
			seg2=(seg2&0x80)|0x08;
			seg3=(seg3&0x80)|0x08;
			seg4=(seg4&0x00)|0x08;//0x00将会把单位"min"去掉
		}
	}
	else
	{
		seg1&=0x00;//不显示时间
		seg2&=0x00;//不显示时间
		seg3&=0x00;//不显示时间
		seg4&=0x80;//不显示时间
	}

	seg2 = seg2|0x80;//设定时间冒号（下面）
//	seg3 = seg3|0x80;//设定时间小数点（下面）
	seg4 = seg4|0x80;//设定时间min文本显示
	
	Write_Addr_Dat_N(0, seg1,1);
	Write_Addr_Dat_N(2, seg2,1);
 	Write_Addr_Dat_N(4, seg3,1);
	Write_Addr_Dat_N(6, seg4,1);
}

/*
*****************************************************************
 * 函数原型：void Display_Rel_Time(int32_t dis_rel_time)
 * 功    能：写最左边的设定时间
 * 输    入：dis_rel_time:左边最下面的时间
 * 参    数：int32_t dis_rel_time
*****************************************************************
*/
void Display_Rel_Time(int32_t dis_rel_time)
{
	uint8_t seg1,seg2,seg3,seg4;
	seg1=0;seg2=0;seg3=0;seg4=0;
	uint8_t SH,H,SM,M;//时间的单位取值
	
	if(Time.Rel || Time.Set)//显示时间表示为0
	{
		SH=dis_rel_time/3600/10;//计算十位单位的小时数
		H=dis_rel_time/3600%10;//计算个位单位的小时数
		SM=dis_rel_time%3600/60/10;//计算十分位单位的分钟数
		M=dis_rel_time%3600/60%10;//计算个分位单位的分钟数
		seg1 = UP_Tab[SH];//时间十位单位的小时数
		seg2 = UP_Tab[H];//时间个位单位的小时数
		seg3 = UP_Tab[SM];//时间十分位单位的分钟数
		seg4 = UP_Tab[M];//时间个分位单位的分钟数
	
	}
	else//没有设置时间,显示“--:--”
	{
		seg1=(seg1&0x01)|0x10;
		seg2=(seg2&0x01)|0x10;
		seg3=(seg3&0x01)|0x10;
		seg4=(seg4&0x01)|0x10;
	}
	
	
//	seg1 = seg1|0x01;//温度符号“℃”图标（下面）
	seg2 = seg2|0x01;//实际时间冒号（上面）
//	seg3 = seg3|0x01;//实际时间小数点（上面）
	seg4 = seg4|0x01;//时间图标（上面）
	
    if(sys.Run_Status && TimeIcn_ShowFlag)//运行时
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
 * 函数原型：void Display_SetSpeed(int16_t dis_set_speed)
 * 功    能：写最右边的设定速度
 * 输    入：dis_set_speed:右边最下面的速度
 * 参    数：int16_t dis_set_speed
*****************************************************************
*/
void Display_Set_Speed(int16_t dis_set_speed)
{
	uint8_t seg1,seg2,seg3,seg4;
	seg1=0;seg2=0;seg3=0;seg4=0;
	uint16_t Val;//用于百十个取出来的数字
	
	/***********设定转速计算**********/
	if(!Speed_ShowFlag)//闪烁标志为0
	{
		if(dis_set_speed>999)
		{	
			Val=dis_set_speed/1000;//取出千位
			seg1 = DOWNR_Tab[Val];
		}
		else
		{
			seg1 = DOWNR_Tab[0];//显示0
		}	
		if(dis_set_speed > 99)//大于99时
		{
			Val=dis_set_speed/100;//取出百位
			if(dis_set_speed > 999)//大于999时
				Val=Val%10;//取出百位
			seg2 = DOWNR_Tab[Val];
		}
		else
		{
			seg2 = DOWNR_Tab[0];//显示0
		}
		if(dis_set_speed > 9)//大于9时
		{
			Val=dis_set_speed/10;//取出十位
			if(dis_set_speed > 99)//大于99时
				Val=Val%10;//取出十位
			seg3 = DOWNR_Tab[Val];
		}
		else
		{
			seg3 = DOWNR_Tab[0];//显示0
		}
		Val=dis_set_speed%10;//取出个位
		seg4 = DOWNR_Tab[Val];
	}
	else
	{
		seg1&=0x00;
		seg2&=0x00;
		seg3&=0x00;
		seg4&=0x01;//0x00将会把rpm单位去掉
	}
	seg4 = seg4|0x01;//rpm文本显示

	Write_Addr_Dat_N(26, seg1,1);
	Write_Addr_Dat_N(28, seg2,1);
 	Write_Addr_Dat_N(30, seg3,1);
	Write_Addr_Dat_N(32, seg4,1);
}

/*
*****************************************************************
 * 函数原型：void Display_RelSpeed(int16_t dis_rel_speed)
 * 功    能：写最右边的实际速度
 * 输    入：dis_rel_speed:右边最上面的速度
 * 参    数：int16_t dis_rel_speed
*****************************************************************
*/
void Display_Rel_Speed(int16_t dis_rel_speed)
{
	uint8_t seg1,seg2,seg3,seg4;
	seg1=0;seg2=0;seg3=0;seg4=0;;
	uint16_t Val;//用于百十个取出来的数字
	
	/***********实际转速计算**********/
	if(dis_rel_speed>999)
	{	
		Val=dis_rel_speed/1000;//取出千位
		seg1 = UP_Tab[Val];
	}
	else
	{
		seg1 = UP_Tab[0];//显示0
	}	
	if(dis_rel_speed > 99)//大于99时
	{
		Val=dis_rel_speed/100;//取出百位
		if(dis_rel_speed > 999)//大于999时
			Val=Val%10;//取出百位
		seg2 = UP_Tab[Val];
	}
	else
	{
		seg2 = UP_Tab[0];//显示0
	}
	if(dis_rel_speed > 9)//大于9时
	{
		Val=dis_rel_speed/10;//取出十位
		if(dis_rel_speed > 99)//大于99时
			Val=Val%10;//取出十位
		seg3 = UP_Tab[Val];
	}
	else
	{
		seg3 = UP_Tab[0];//显示0
	}
	Val=dis_rel_speed%10;//取出个位
	seg4 = UP_Tab[Val];
	
	seg1 = seg1|0x01;//圆图标的尾巴
    
//		seg2 = seg2|0x01;//顺时针的三角形
		seg3 = seg3|0x01;//逆时针的三角形
    
//	seg4 = seg4|0x01;//加热图标
    
	if(SpeedIcn_ShowFlag)//运行时
    { 
		seg1&=0xfe;//圆图标的尾巴消失
		seg2&=0xfe;//顺时针的三角形消失
		seg3&=0xfe;//逆时针的三角形消失
    }
	
	Write_Addr_Dat_N(46, seg1,1);
	Write_Addr_Dat_N(44, seg2,1);
 	Write_Addr_Dat_N(42, seg3,1);
	Write_Addr_Dat_N(40, seg4,1);
}

/*
*****************************************************************
 * 函数原型：void Deal_Speed(float dT)
 * 功    能：速度显示处理
*****************************************************************
*/
void Deal_Speed(float dT)
{
    if(sys.Run_Status)//启动的情况下
	{
		if(Speed.ADDMode==0)//在电机控制中，速度未处理
		{ 
			if(Speed.Ctrl >= Speed.Display_Rel)//控制速度大于实际速度
            {
                Speed.ADDMode = 1;//进入加速模式下
            }
            else if(Speed.Ctrl < Speed.Display_Rel)//控制速度小于实际速度
            {
                Speed.ADDMode = 2;//进入减速模式下
            }
		}
		if(Speed.ADDMode==1)//在进入加速模式下
		{
			Speed.New = (Speed.Rel[0]+Speed.Rel[1]+Speed.Rel[2]+Speed.Rel[3])/4;//记录当前速度
            if(Speed.New > Speed.Display_Rel)//当前速度大于显示速度
			{
				if(Speed.Display_Rel < Speed.New)
					Speed.Display_Rel = Speed.New;//显示当前速度
			}
            else//当前速度小于上一次速度
            {
                Speed.Display_Rel = Speed.Display_Rel;//显示上一次速度，不让速度小于当前速度。呈现攀升速度的现象
            }  
			if(sys.Motor_Stop == 0)
			{
				if(Speed.Display_Rel >= Speed.Ctrl)//实际速度大于等于控制速度
				{
					Speed.ADDMode = 3;//进入稳定模式
					return;
				}
			}
		}
		if(Speed.ADDMode == 2)//速度下降模式下
        {
            Speed.New = (Speed.Rel[0]+Speed.Rel[1]+Speed.Rel[2]+Speed.Rel[3])/4;//记录当前速度
            if(Speed.Ctrl <= 260 && Speed.New <= 260)
            {
                    Speed.ADDMode = 3;//进入稳定模式
            }
            if(Speed.New < Speed.Display_Rel)//当前速度小于上一次速度
			{
				if(Speed.Display_Rel > Speed.New)
					Speed.Display_Rel = Speed.New;//显示当前速度
			}
            else//当前速度大于上一次速度
            {
                Speed.Display_Rel = Speed.Display_Rel;//显示上一次速度，不让速度大于当前速度。呈现下降速度的现象
            }
			if(sys.Motor_Stop == 0)
			{
				if(Speed.Display_Rel <= Speed.Ctrl)//实际速度小于等于控制速度
				{
					Speed.ADDMode = 3;//进入稳定模式
					return;
				}
			}
        }
        else if(Speed.ADDMode == 3)//速度稳定模式下
        {
            Speed.Display_Rel = Speed.Ctrl;//显示控制速度
        }
	}
	else
	{
		Speed.Display_Rel = 0;//实际速度显示为零
		Speed.New =0;//现在的速度清零
		Speed.ADDMode = 0;//清除显示处理
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
	Speed.Display_Set = Speed.Set;//显示设定速度
	Time.Display_Set = Time.Set;//显示设定时间
	Time.Display_Rel = Time.Rel + 59;//显示实际时间+59s

    Display_Set_Time(Time.Display_Set);
	Display_Rel_Time(Time.Display_Rel);
	Display_Set_Speed(Speed.Display_Set);
	Display_Rel_Speed(Speed.Display_Rel);
}
