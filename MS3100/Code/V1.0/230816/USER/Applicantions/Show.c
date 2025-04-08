#include "Show.h"

/**********全局变量声明******/
float Speed_Twinkle_Time,Time_Twinkle_Time;//速度闪烁时间和时间闪烁时间

/**********局部变量声明******/
uint8_t Tab[] = {0xFA,0x0A,0xD6,0x9E,0x2E,0xBC,0xFC,0x1A,0xFE,0xBE};//0·9
uint8_t Speed_ShowFlag,Time_ShowFlag;//速度、时间显示的标志位 0:常亮 1：熄灭
uint8_t SpeedIcn_ShowFlag,TimeIcn_ShowFlag;//速度图标闪烁和时间图标闪烁

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
 * 函数原型：void Display_Speed(int16_t dis_set_speed,int16_t dis_rel_speed)
 * 功    能：显示转速
 * 输    入: dis_set_speed 设定转速  dis_rel_speed 实际转速
 * 参    数：int16_t dis_set_speed,int16_t dis_rel_speed
*****************************************************************
*/
void Display_Speed(int16_t dis_set_speed,int16_t dis_rel_speed)
{
	uint8_t seg10,seg11,seg12,seg13,seg14,seg15,seg16,seg17,seg18,seg19;
	seg10=0;seg11=0;seg12=0;seg13=0;seg14=0;seg15=0;seg16=0;seg17=0;seg18=0;seg19=0;
	uint8_t Speed_QU,Speed_BU,Speed_SU,Speed_GU;//实际速度的计算位数取值
	uint8_t Speed_QD,Speed_BD,Speed_SD,Speed_GD;//设定速度的计算位数取值
	uint16_t Val;//用于百十个取出来的数字
	if(Speed_ShowFlag == 0)
	{
		/***********设定转速计算**********/
		if(dis_set_speed > 999)//大于999时
		{
			Val=dis_set_speed/1000;//取出千位
			Speed_QD = Tab[Val];
		}
		else
		{
			Speed_QD = Tab[0];//显示0
		}
		if(dis_set_speed > 99)//大于99时
		{
			Val=dis_set_speed/100;//取出百位
			if(dis_set_speed > 999)//大于999时
				Val=Val%10;//取出百位
			Speed_BD = Tab[Val];
		}
		else
		{
			Speed_BD = Tab[0];//显示0
		}
		if(dis_set_speed > 9)//大于9时
		{
			Val=dis_set_speed/10;//取出十位
			if(dis_set_speed > 99)//大于99时
				Val=Val%10;//取出十位
			Speed_SD = Tab[Val];
		}
		else
		{
			Speed_SD = Tab[0];//显示0
		}
		Val=dis_set_speed%10;//取出个位
		Speed_GD = Tab[Val];
	}
	else
	{
		Speed_QD = 0x00;//不显示设定速度
		Speed_BD = 0x00;//不显示设定速度
		Speed_SD = 0x00;//不显示设定速度
		Speed_GD = 0x00;//不显示设定速度
	}
	
	/***********实际转速计算**********/
	if(dis_rel_speed > 999)//大于999时
	{
		Val=dis_rel_speed/1000;//取出千位
		Speed_QU = Tab[Val];
	}
	else
	{
		Speed_QU = Tab[0];//显示0
	}
	if(dis_rel_speed > 99)//大于99时
	{
		Val=dis_rel_speed/100;//取出百位
		if(dis_rel_speed > 999)//大于999时
			Val=Val%10;//取出百位
		Speed_BU = Tab[Val];
	}
	else
	{
		Speed_BU = Tab[0];//显示0
	}
	if(dis_rel_speed > 9)//大于9时
	{
		Val=dis_rel_speed/10;//取出十位
		if(dis_rel_speed > 99)//大于99时
			Val=Val%10;//取出十位
		Speed_SU = Tab[Val];
	}
	else
	{
		Speed_SU = Tab[0];//显示0
	}
	Val=dis_rel_speed%10;//取出个位
	Speed_GU = Tab[Val];


	/***************rpm******************/
	seg15 &= 0x7F;seg15 |= 0x80;//rpm
	
    /*************转速图标***************/
	if(SpeedIcn_ShowFlag == 0)
	{
        if(Speed.CwIcn)
        {
            seg10 &= 0xFD;seg10 |= 0x02;//逆转指针
        }
        else
        {
            seg10 &= 0xFE;seg10 |= 0x01;//逆转指针
        }
		seg11 &= 0xFD;seg11 |= 0x02;//转速图标
	}
	else
	{
		seg10 &= 0xFC;seg10 |= 0x00;//不显示逆转指针
		seg11 &= 0xFD;seg11 |= 0x00;//不显示转速图标
	}
    
	/*************数据拆分***************/
	seg19 &= 0xF0;seg19 |= Speed_QU>>4;
	seg18 &= 0xF1;seg18 |= Speed_QU & 0x0E;
	seg19 &= 0x0F;seg19 |= Speed_QD & 0xF0;
	seg18 &= 0x8F;seg18 |= (Speed_QD & 0x0F) << 3;

	seg12 &= 0xF0;seg12 |= Speed_BU>>4;
	seg13 &= 0xF1;seg13 |= Speed_BU & 0x0E;
	seg12 &= 0x0F;seg12 |= Speed_BD & 0xF0;
	seg13 &= 0x8F;seg13 |= (Speed_BD & 0x0F) << 3;
	
	seg14 &= 0xF0;seg14 |= Speed_SU>>4;
	seg15 &= 0xF1;seg15 |= Speed_SU & 0x0E;
	seg14 &= 0x0F;seg14 |= Speed_SD & 0xF0;
	seg15 &= 0x8F;seg15 |= (Speed_SD & 0x0F) << 3;
	
	seg16 &= 0xF0;seg16 |= Speed_GU>>4;
	seg17 &= 0xF1;seg17 |= Speed_GU & 0x0E;
	seg16 &= 0x0F;seg16 |= Speed_GD & 0xF0;
	seg17 &= 0x8F;seg17 |= (Speed_GD & 0x0F) << 3;	
	
	/*************发送数据***************/	
    Write_Addr_Dat_N(18, seg10,1);//SEG16
	Write_Addr_Dat_N(20, seg11,1);//SEG15
	Write_Addr_Dat_N(22, seg12,1);//SEG16
	Write_Addr_Dat_N(24, seg13,1);//SEG15
	Write_Addr_Dat_N(26, seg14,1);//SEG14
	Write_Addr_Dat_N(28, seg15,1);//SEG13
	Write_Addr_Dat_N(30, seg16,1);//SEG12
	Write_Addr_Dat_N(32, seg17,1);//SEG11
	Write_Addr_Dat_N(34, seg18,1);//SEG10
	Write_Addr_Dat_N(36, seg19,1);//SEG9	
}

/*
*****************************************************************
 * 函数原型：void Display_Temp(int32_t dis_set_temp,int32_t dis_rel_temp)
 * 功    能：显示温度
 * 输    入: dis_set_temp 设定温度  dis_rel_temp 实际温度
 * 参    数：int32_t dis_set_temp,int32_t dis_rel_temp
*****************************************************************
*/
void Display_Time(int32_t dis_set_time,int32_t dis_rel_time)
{
	uint8_t seg1,seg2,seg3,seg4,seg5,seg6,seg7,seg8;
	seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;seg7=0;seg8=0;
	uint8_t Time_QU,Time_BU,Time_SU,Time_GU;//实际温度的计算位数取值
	uint8_t Time_QD,Time_BD,Time_SD,Time_GD;//设定温度的计算位数取值
	uint8_t SH,H,SM,M;//时间的单位取值
	
	/***********设定温度计算**********/
    if(Time_ShowFlag == 0)
	{
        if(dis_set_time > 0)
        {
            SH = dis_set_time/3600/10;//计算十位单位的小时数
            H = dis_set_time/3600%10;//计算个位单位的小时数
            SM = dis_set_time%3600/60/10;//计算十分位单位的分钟数
            M = dis_set_time%3600/60%10;//计算个分位单位的分钟数
            Time_QD = Tab[SH];
            Time_BD = Tab[H];
            Time_SD = Tab[SM];
            Time_GD = Tab[M];
            /***********实际时间冒号**********/
            seg4 &= 0x7F;seg4 |= 0x80;
        }
        else
        {
            Time_QD = 0x04;//显示"-"
            Time_BD = 0x04;//显示"-"
            Time_SD = 0x04;//显示"-"
            Time_GD = 0x04;//显示"-"
            /***********实际时间冒号**********/
            seg4 &= 0x7F;seg4 |= 0x00;
        }
	}
    else
    {
        Time_QD = 0x00;//显示"-"
        Time_BD = 0x00;//显示"-"
        Time_SD = 0x00;//显示"-"
        Time_GD = 0x00;//显示"-"
        seg4 &= 0x7F;seg4 |= 0x00;
    }
        
	/***********实际温度计算**********/
    if(dis_set_time > 0)
    {
        SH = dis_rel_time/3600/10;//计算十位单位的小时数
        H = dis_rel_time/3600%10;//计算个位单位的小时数
        SM = dis_rel_time%3600/60/10;//计算十分位单位的分钟数
        M = dis_rel_time%3600/60%10;//计算个分位单位的分钟数
        Time_QU = Tab[SH];
        Time_BU = Tab[H];
        Time_SU = Tab[SM];
        Time_GU = Tab[M];
        
        /***********实际时间冒号**********/
        if(!TimeIcn_ShowFlag)
        {
            seg4 &= 0xFE;seg4 |= 0x01;
        }
        else
        {
            seg4 &= 0xFE;seg4 |= 0x00;
        }
    }
    else
    {
        Time_QU = 0x04;//显示"-"
        Time_BU = 0x04;//显示"-"
        Time_SU = 0x04;//显示"-"
        Time_GU = 0x04;//显示"-"
        /***********实际时间冒号**********/
        seg4 &= 0xFE;seg4 |= 0x00;
    }
		
	/*************数据拆分***************/	
	seg1 &= 0xF0;seg1 |= Time_QU>>4;
	seg2 &= 0xF1;seg2 |= Time_QU & 0x0E;
	seg1 &= 0x0F;seg1 |= Time_QD & 0xF0;
	seg2 &= 0x8F;seg2 |= (Time_QD & 0x0F) << 3;

	seg3 &= 0xF0;seg3 |= Time_BU>>4;
	seg4 &= 0xF1;seg4 |= Time_BU & 0x0E;
	seg3 &= 0x0F;seg3 |= Time_BD & 0xF0;
	seg4 &= 0x8F;seg4 |= (Time_BD & 0x0F) << 3;
	
	seg5 &= 0xF0;seg5 |= Time_SU>>4;
	seg6 &= 0xF1;seg6 |= Time_SU & 0x0E;
	seg5 &= 0x0F;seg5 |= Time_SD & 0xF0;
	seg6 &= 0x8F;seg6 |= (Time_SD & 0x0F) << 3;
	
	seg7 &= 0xF0;seg7 |= Time_GU>>4;
	seg8 &= 0xF1;seg8 |= Time_GU & 0x0E;
	seg7 &= 0x0F;seg7 |= Time_GD & 0xF0;
	seg8 &= 0x8F;seg8 |= (Time_GD & 0x0F) << 3;

	/*************发送数据***************/	
	Write_Addr_Dat_N(0, seg1,1);//SEG27
	Write_Addr_Dat_N(2, seg2,1);//SEG26
	Write_Addr_Dat_N(4, seg3,1);//SEG25
	Write_Addr_Dat_N(6, seg4,1);//SEG24
	Write_Addr_Dat_N(8, seg5,1);//SEG23
	Write_Addr_Dat_N(10, seg6,1);//SEG22
	Write_Addr_Dat_N(12, seg7,1);//SEG21
	Write_Addr_Dat_N(14, seg8,1);//SEG20
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
			Speed.New = Speed.Rel;//记录当前速度
            if(Speed.New > Speed.Display_Rel)//当前速度大于显示速度
			{
				if(Speed.Display_Rel < Speed.New)
					Speed.Display_Rel+=1;//显示当前速度
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
            Speed.New = Speed.Rel;//记录当前速度
            
            if(Speed.New < Speed.Display_Rel)//当前速度小于上一次速度
			{
				if(Speed.Display_Rel > Speed.New)
					Speed.Display_Rel -=1;//显示当前速度
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
 * 函数原型： void Show_Display(void)
 * 功    能： 显示屏幕内容
*****************************************************************
*/
void Show_Display(void)
{
	Speed.Display_Set = Speed.Set;//显示设定转速
	Time.Display_Rel = Time.Rel + 59;//显示控制时间		
	Time.Display_Set = Time.Set;//显示设定时间  

	Display_Speed(Speed.Display_Set, Speed.Display_Rel);//显示转速
	Display_Time(Time.Display_Set, Time.Display_Rel);//显示时间
}
