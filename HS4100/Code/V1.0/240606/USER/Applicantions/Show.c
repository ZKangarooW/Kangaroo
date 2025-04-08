#include "Show.h"

/**********全局变量声明******/
float Speed_Twinkle_Time,Temp_Twinkle_Time,Time_Twinkle_Time;//速度闪烁时间、温度闪烁时间和时间闪烁时间

/**********局部变量声明******/
uint8_t Tab[] = {0xFA,0x0A,0xD6,0x9E,0x2E,0xBC,0xFC,0x1A,0xFE,0xBE};//0·9
uint8_t Temp_ShowFlag,Speed_ShowFlag,Time_ShowFlag;//温度、速度、时间显示的标志位 0:常亮 1：熄灭
uint8_t TempIcn_ShowFlag,TimeIcn_ShowFlag,SpeedIcn_ShowFlag,Lock_ShowFlag;//加热图标闪烁和时间图标闪烁和速度图标闪烁

/*
*****************************************************************
 * 函数原型：static void Icn_Twinkle(float dT)
 * 功    能：图标闪烁
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
			if(Speed.Set)
			{
				if(Speed.CwIcn)
				{
					if(SpeedIcn_ShowFlag > 0)
						SpeedIcn_ShowFlag --;//速度图标闪烁;
					if(SpeedIcn_ShowFlag < 1)
						SpeedIcn_ShowFlag = 3;
				}
				else
				{
					SpeedIcn_ShowFlag ++;//速度图标闪烁;
					if(SpeedIcn_ShowFlag > 3)
						SpeedIcn_ShowFlag = 1;
				}
			}
			else
				SpeedIcn_ShowFlag = 0;
            if(Temp.Set)
				TempIcn_ShowFlag = ~TempIcn_ShowFlag;//温度图标闪烁;
			else
				TempIcn_ShowFlag = 0;
			if(Time.Rel && (!Temp.Ctrl || TempIcn_ShowFlag != TimeIcn_ShowFlag) && (Temp.Set == 0 || Temp.ADDMode == 3))
				TimeIcn_ShowFlag = ~TimeIcn_ShowFlag;//定时图标闪烁;
            else
            {
                TimeIcn_ShowFlag = 0;
            }
			T = 0;
		}
	}
	else
	{
		if(Speed.CwShow)
		{
			T += dT;
			if(T >= 0.5f)
			{
				if(Speed.CwIcn)
				{
					if(SpeedIcn_ShowFlag ==0)
						SpeedIcn_ShowFlag = 3;
					else
					{
						SpeedIcn_ShowFlag --;//速度图标闪烁;
					
						if(SpeedIcn_ShowFlag ==0)
							Speed.CwShow = 0;
					}
				}
				else
				{
					SpeedIcn_ShowFlag ++;//速度图标闪烁;
					if(SpeedIcn_ShowFlag > 3)
					{
						SpeedIcn_ShowFlag = 0;
						Speed.CwShow = 0;
					}
				}
				T = 0;
			}
		}
		else
			SpeedIcn_ShowFlag = 0;//显示时间图标
		
        TempIcn_ShowFlag = 0;//不显示温度图标
		TimeIcn_ShowFlag = 0;//显示时间图标
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
	static float Speed_T,Temp_T,Time_T;
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
//				Beep_Time = 0.1;//蜂鸣器响0.1S
			} 
			Speed_T = 0;		
		}			
    }
	else
	{
		Speed_ShowFlag = 0;//常亮
		Speed_T = 0;
	}
	
	if(Temp_Twinkle_Time && !EC11A[0].EC11A_Knob)//速度闪烁和没有操作按键时
    {
		Temp_T += dT;
		if(Temp_T >= 0.5f)
		{
			Temp_Twinkle_Time -= 0.5;//闪烁计时
			Temp_ShowFlag = ~Temp_ShowFlag;//速度闪烁
			if(Temp_Twinkle_Time == 0)//如果闪烁结束
			{
				TempSet_Flag = 1;//进入速度设定
//				Beep_Time = 0.1;//蜂鸣器响0.1S
			} 
			Temp_T = 0;		
		}			
    }
	else
	{
		Temp_ShowFlag = 0;//常亮
		Temp_T = 0;
	}
	
	if(Time_Twinkle_Time && (!EC11A[1].EC11A_Knob && !EC11A[0].EC11A_Knob))//时间闪烁和没有操作按键时
    {
		Time_T += dT;
		if(Time_T >= 0.5f)
		{
			Time_Twinkle_Time -= 0.5;//闪烁计时
			Time_ShowFlag = ~Time_ShowFlag;//时间闪烁
			if(Time_Twinkle_Time == 0)//如果闪烁结束
			{
				TimeSet_Flag = 1;//进入时间设定
//				Beep_Time = 0.1;//蜂鸣器响0.1S
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

/**
 * @brief 锁定误触图标闪烁检测
 *
 * @param dT 任务周期
 */
void Check_Lock(float dT)
{
    static float T;
	if (sys.Lock_Alarm)
	{
		T += dT;
		if (T >= 0.5f)
		{
			Lock_ShowFlag = ~Lock_ShowFlag;//安全温度图标闪烁
            sys.Lock_Alarm -= 0.5f;
			T = 0;
		}
	}
    else
    {
        Lock_ShowFlag = 0;
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
    Check_Lock(dT);//锁定误触图标闪烁检测
	Icn_Twinkle(dT);//图标闪烁
}

/*
*****************************************************************
 * 函数原型：void Display_Temp(int16_t dis_set_temp,int16_t dis_rel_temp)
 * 功    能：显示温度
 * 输    入: dis_set_temp 设定温度  dis_rel_temp 实际温度
 * 参    数：int16_t dis_set_temp,int16_t dis_rel_temp
*****************************************************************
*/
void Display_Temp(int16_t dis_set_temp,int16_t dis_rel_temp)
{
	uint8_t seg1,seg2,seg3,seg4,seg5,seg6,seg7,seg8;
	seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;seg7=0;seg8=0;
	uint8_t Temp_QU,Temp_BU,Temp_SU,Temp_GU;//实际温度的计算位数取值
	uint8_t Temp_QD,Temp_BD,Temp_SD,Temp_GD;//设定温度的计算位数取值
	uint16_t Val;//用于百十个取出来的数字
	
	/***********设定温度计算**********/
	if(Temp_ShowFlag == 0)
	{
		if(dis_set_temp > 0)
		{
			if(dis_set_temp > 999)//大于999时
			{
				Val=dis_set_temp/1000;//取出千位
				Temp_QD = Tab[Val];
			}
			else
			{
				Temp_QD = 0x00;//不显示
			}
			if(dis_set_temp > 99)//大于99时
			{
				Val=dis_set_temp/100;//取出百位
				if(dis_set_temp > 999)//大于999时
					Val=Val%10;//取出百位
				Temp_BD = Tab[Val];
			}
			else
			{
				Temp_BD = 0x00;//不显示
			}
			if(dis_set_temp > 9)//大于9时
			{
				Val=dis_set_temp/10;//取出十位
				if(dis_set_temp > 99)//大于99时
					Val=Val%10;//取出十位
				Temp_SD = Tab[Val];
			}
			else
			{
				Temp_SD = Tab[0];//不显示0
			}
			Val=dis_set_temp%10;//取出个位
			Temp_GD = Tab[Val];
			seg6 &= 0x7F;seg6 |= 0x80;//设定温度的小数点
		}
		else
		{
			Temp_QD = 0x04;//显示"-"
			Temp_BD = 0x04;//显示"-"
			Temp_SD = 0x04;//显示"-"
			Temp_GD = 0x04;//显示"-"
			seg6 &= 0x7F;seg6 |= 0x00;//不显示设定温度的小数点
		}
	}
	else
	{
		Temp_QD = 0x00;//不显示设定温度
		Temp_BD = 0x00;//不显示设定温度
		Temp_SD = 0x00;//不显示设定温度
		Temp_GD = 0x00;//不显示设定温度
		seg6 &= 0x7F;seg6 |= 0x00;//不显示设定温度的小数点
	}
	
	/***********实际温度计算**********/
	if(dis_rel_temp > 999)//大于999时
	{
		Val=dis_rel_temp/1000;//取出千位
		Temp_QU = Tab[Val];
	}
	else
	{
		Temp_QU = 0x00;//不显示
	}
	if(dis_rel_temp > 99)//大于99时
	{
		Val=dis_rel_temp/100;//取出百位
		if(dis_rel_temp > 999)//大于999时
			Val=Val%10;//取出百位
		Temp_BU = Tab[Val];
	}
	else
	{
		Temp_BU = 0x00;//不显示
	}
	if(dis_rel_temp > 9)//大于9时
	{
		Val=dis_rel_temp/10;//取出十位
		if(dis_rel_temp > 99)//大于99时
			Val=Val%10;//取出十位
		Temp_SU = Tab[Val];
	}
	else
	{
		Temp_SU = Tab[0];//不显示0
	}
	Val=dis_rel_temp%10;//取出个位
	Temp_GU = Tab[Val];
	
	/*************温度小数点的图标*******/
	seg6 &= 0xFE;seg6 |= 0x01;//实际温度的小数点
	
	/****************℃******************/
	seg8 &= 0x7F;seg8 |= 0x80;//℃
	
	/*************外部探头的图标*********/
	if(PT_VALUE_1_TEMP < 2000)//假如插入外部探头
	{
		seg8 &= 0xFE;seg8 |= 0x01;//外部探头的图标
	}
	else
	{
		seg8 &= 0xFE;seg8 |= 0x00;//不显示外部探头的图标
	}
		
	/*************数据拆分***************/	
	seg1 &= 0xF0;seg1 |= Temp_QU>>4;
	seg2 &= 0xF1;seg2 |= Temp_QU & 0x0E;
	seg1 &= 0x0F;seg1 |= Temp_QD & 0xF0;
	seg2 &= 0x8F;seg2 |= (Temp_QD & 0x0F) << 3;

	seg3 &= 0xF0;seg3 |= Temp_BU>>4;
	seg4 &= 0xF1;seg4 |= Temp_BU & 0x0E;
	seg3 &= 0x0F;seg3 |= Temp_BD & 0xF0;
	seg4 &= 0x8F;seg4 |= (Temp_BD & 0x0F) << 3;
	
	seg5 &= 0xF0;seg5 |= Temp_SU>>4;
	seg6 &= 0xF1;seg6 |= Temp_SU & 0x0E;
	seg5 &= 0x0F;seg5 |= Temp_SD & 0xF0;
	seg6 &= 0x8F;seg6 |= (Temp_SD & 0x0F) << 3;
	
	seg7 &= 0xF0;seg7 |= Temp_GU>>4;
	seg8 &= 0xF1;seg8 |= Temp_GU & 0x0E;
	seg7 &= 0x0F;seg7 |= Temp_GD & 0xF0;
	seg8 &= 0x8F;seg8 |= (Temp_GD & 0x0F) << 3;

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
 * 函数原型：void Display_Speed(int16_t dis_set_speed,int16_t dis_rel_speed)
 * 功    能：显示转速
 * 输    入: dis_set_speed 设定转速  dis_rel_speed 实际转速
 * 参    数：int16_t dis_set_speed,int16_t dis_rel_speed
*****************************************************************
*/
void Display_Speed(int16_t dis_set_speed,int16_t dis_rel_speed)
{
	uint8_t seg12,seg13,seg14,seg15,seg16,seg17,seg18,seg19;
	seg12=0;seg13=0;seg14=0;seg15=0;seg16=0;seg17=0;seg18=0;seg19=0;
	uint8_t Speed_QU,Speed_BU,Speed_SU,Speed_GU;//实际速度的计算位数取值
	uint8_t Speed_QD,Speed_BD,Speed_SD,Speed_GD;//设定速度的计算位数取值
	uint16_t Val;//用于百十个取出来的数字
	
	if(Speed_ShowFlag == 0)
	{
		if(dis_set_speed > 0)
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
			Speed_QD = 0x04;//显示"-"
			Speed_BD = 0x04;//显示"-"
			Speed_SD = 0x04;//显示"-"
			Speed_GD = 0x04;//显示"-"
		}
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
		Speed_QU = 0x00;//不显示
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
		Speed_BU = 0x00;//不显示
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
		Speed_SU = 0x00;//不显示
	}
	Val=dis_rel_speed%10;//取出个位
	Speed_GU = Tab[Val];


	/***************rpm******************/
	seg15 &= 0x7F;seg15 |= 0x80;//rpm
	
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
 * 函数原型：void Display_Time(int32_t dis_time)
 * 功    能：显示时间
 * 输    入: dis_time 时间
 * 参    数：int32_t dis_time
*****************************************************************
*/
void Display_Time(int32_t dis_time)
{
	uint8_t seg9,seg10,seg11,seg20,seg21,seg22,seg23,seg24,seg25,seg26,seg27;
	seg9=0;seg10=0;seg11=0;seg20=0;seg21=0;seg22=0;seg23=0;seg24=0;seg25=0;seg26=0;seg27=0;
	uint8_t Time_Q,Time_B,Time_S,Time_G;//时间的计算位数取值
	uint8_t SH,H,SM,M;//时间的单位取值
	
	if(Time.Set || sys.SetMode_Option == 3)//设定时间大于0，在设定时间和闪烁下
	{
		if(!Time_ShowFlag)
        {
			if(Time.Set)//假如设定时间大于0
			{
				/**************时间计算*************/
				SH=dis_time/3600/10;//计算十位单位的小时数
				H=dis_time/3600%10;//计算个位单位的小时数
				SM=dis_time%3600/60/10;//计算十分位单位的分钟数
				M=dis_time%3600/60%10;//计算个分位单位的分钟数
				Time_Q = Tab[SH];
				Time_B = Tab[H];
				Time_S = Tab[SM];
				Time_G = Tab[M];
			}
			else
			{
				Time_Q = 0x04;//显示"-"
				Time_B = 0x04;//显示"-"
				Time_S = 0x04;//显示"-"
				Time_G = 0x04;//显示"-"
			}
		}
		else//设定时间等于0
		{
			Time_Q = 0x00;//不显示时间
			Time_B = 0x00;//不显示时间
			Time_S = 0x00;//不显示时间
			Time_G = 0x00;//不显示时间
		}
	}
	else//设定时间等于0
	{
		Time_Q = 0x00;//不显示时间
		Time_B = 0x00;//不显示时间
		Time_S = 0x00;//不显示时间
		Time_G = 0x00;//不显示时间
	}

	if(Time.Set > 0 || sys.SetMode_Option == 3)
	{
		/************时间冒号图标************/
		seg9 &= 0xFE;seg9 |= 0x01;//时间冒号
		
		/*************时间单位图标***********/
		seg11 &= 0xF7;seg11 |= 0x08;//min
		
		/*************时间图标***************/	
		if(TimeIcn_ShowFlag == 0)
		{
			seg20 &= 0x7F;seg20 |= 0x80;//时间图标
		}
		else
		{
			seg20 &= 0x7F;seg20 |= 0x00;//不显示时间图标
		}
	}
	else
	{
		seg9  &= 0xFE;seg9  |= 0x00;//不显示时间冒号
		seg11 &= 0xF7;seg11 |= 0x00;//不显示min
		seg20 &= 0x7F;seg20 |= 0x00;//不显示显示时间图标
	}

	/*************锁定图标***************/
	if(sys.Lock && !Lock_ShowFlag)
	{
		seg9 &= 0xFD;seg9 |= 0x02;//锁定
	}
	else
	{
		seg9 &= 0xFD;seg9 |= 0x00;//锁定
	}
	
	/*************加热图标***************/
	if(sys.Run_Status && Temp.Ctrl)
	{
		seg9 &= 0xFB;seg9 |= 0x04;//加热图标
	}
	else
	{
		seg9 &= 0xFB;seg9 |= 0x00;//不显示加热图标
	}	
	
	/*************转速图标***************/
    switch(SpeedIcn_ShowFlag)
	{
		case 0: seg10 &= 0xFE;seg10 |= 0x01;//S5
                seg10 &= 0xFD;seg10 |= 0x02;//S4
                seg11 &= 0xFD;seg11 |= 0x02;//S3
			break;
		case 1: seg10 &= 0xFE;seg10 |= 0x00;//S5
                seg10 &= 0xFD;seg10 |= 0x02;//S4
                seg11 &= 0xFD;seg11 |= 0x02;//S3
			break;
		case 2: seg10 &= 0xFE;seg10 |= 0x01;//S5
                seg10 &= 0xFD;seg10 |= 0x02;//S4
                seg11 &= 0xFD;seg11 |= 0x00;//S3
			break;
		case 3: seg10 &= 0xFE;seg10 |= 0x01;//S5
                seg10 &= 0xFD;seg10 |= 0x00;//S4
                seg11 &= 0xFD;seg11 |= 0x02;//S3
			break;
		default:
			break;
	}

	/*************数据拆分***************/
	seg21 &= 0xF0;seg21 |= Time_G>>4;
	seg20 &= 0xF1;seg20 |= Time_G>>1 & 0x07;

	seg23 &= 0xF0;seg23 |= Time_S>>4;
	seg22 &= 0xF1;seg22 |= Time_S>>1 & 0x07;

	seg25 &= 0xF0;seg25 |= Time_B>>4;
	seg24 &= 0xF1;seg24 |= Time_B>>1 & 0x07;
	
	seg27 &= 0xF0;seg27 |= Time_Q>>4;
	seg26 &= 0xF1;seg26 |= Time_Q>>1 & 0x07;
	
	/*************发送数据***************/	
	Write_Addr_Dat_N(16, seg9, 1);//SEG19
	Write_Addr_Dat_N(18, seg10,1);//SEG18
	Write_Addr_Dat_N(20, seg11,1);//SEG17
	Write_Addr_Dat_N(38, seg20,1);//SEG8
	Write_Addr_Dat_N(40, seg21,1);//SEG7
	Write_Addr_Dat_N(42, seg22,1);//SEG6
	Write_Addr_Dat_N(44, seg23,1);//SEG5
	Write_Addr_Dat_N(46, seg24,1);//SEG4
	Write_Addr_Dat_N(48, seg25,1);//SEG3
	Write_Addr_Dat_N(50, seg26,1);//SEG2
	Write_Addr_Dat_N(52, seg27,1);//SEG1	
}

/*
*****************************************************************
 * 函数原型：void Deal_Speed(float dT)
 * 功    能：速度显示处理
*****************************************************************
*/
void Deal_Speed(float dT)
{
	if(sys.Run_Status)
	{
		if(Speed.Ctrl)
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
			if(Speed.Display_Rel)
				Speed.Display_Rel -=1;//显示当前速度
			else
				Speed.Display_Rel =0;//显示当前速度为0
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
 * 函数原型：void Deal_Temp(float dT)
 * 功    能：温度显示处理
*****************************************************************
*/
void Deal_Temp(float dT)
{
    static float T;
	uint8_t val;
	if(sys.Run_Status && Temp.Ctrl)
	{
		if(PT_VALUE_1_TEMP < 2200)//假如插入外部探头
			val = 40;
		else//假如没有插入外部探头
		{
			if(Temp.Ctrl < 2800)
				val = 100;
			else
				val = 140;
		}
		
		if(ABS(Temp.Ctrl - Temp.Rel) < val)
		{
			if(Temp.ADDMode==0)//判断模式
			{ 
				if(Temp.Ctrl > Temp.Rel)
				{
					Temp.ADDMode = 1;//进入升温模式
                    Temp_Arg.Kd = 30; 
					Temp.Last = Temp.Rel;
				}
				else if(Temp.Ctrl < Temp.Rel)
				{
					Temp.ADDMode = 2;//进入降温模式
                    Temp_Arg.Kd = 0; 
					Temp.Last = Temp.Rel;//记录当前温度
				}
				else
				{
					Temp.ADDMode = 3;//进入稳定模式
					Temp_Arg.Kd = 10;//pid参数调整
				}
			}
			else if(Temp.ADDMode==1)//在进入升温模式下
			{ 
				Temp.New = Temp.Rel;//记录当前温度
				if(Temp.New > Temp.Last)//当前温度大于上一次温度
					Temp.Display_Rel = Temp.New;//显示当前温度
				else//当前温度小于上一次温度
				{
                    if(Temp.Ctrl == 1000)
                    {
                        if(Temp.Display_Rel == Temp.Last)
                        {
                            T += dT;
                            if(T > 10)
                            {
                                Temp.Display_Rel += 1;
                                Temp.Last = Temp.Display_Rel;
                                T = 0;
                            }
                        }
                        else
                        {
                            T = 0;
                        }
                    }
					Temp.Display_Rel = Temp.Last;//显示上一次温度，不让温度小于当前温度。呈现攀升速度的现象
					Temp.New = Temp.Last;//将上一次温度赋值给当前温度
				}
                Temp.Last = Temp.New;//将当前温度保存                
				if(Temp.Display_Rel >= Temp.Ctrl)//当前的温度大于等于控制温度
				{
					Temp.ADDMode = 3;//进入稳定模式
                    Temp_Val.Integral = 0;//温度控制积分清零
                    Temp_Arg.Kd = 10;//pid参数调整
				}
			}
            
			else if(Temp.ADDMode==2)//在进入降温模式下
			{ 
				Temp.New = Temp.Rel;//记录当前温度
				if(Temp.New < Temp.Last)//当前温度小于上一次温度
					Temp.Display_Rel = Temp.New;//显示当前温度
				else//当前温度大于上一次温度
				{
					Temp.Display_Rel = Temp.Last;//显示上一次温度，不让温度小于当前温度。呈现攀升速度的现象
					Temp.New = Temp.Last;//将上一次温度赋值给当前温度
				}
				Temp.Last = Temp.New;//将当前温度保存
				if(Temp.Display_Rel <= Temp.Ctrl)//当前的温度小于等于控制温度
				{
					Temp.ADDMode = 3;//进入稳定模式
                    Temp_Val.Integral = 0;//温度控制积分清零
                    Temp_Arg.Kd = 10;//pid参数调整
				}
			}
            
			else if(Temp.ADDMode == 3)//温度稳定模式下
			{
				Temp.Display_Rel = Temp.Ctrl;//显示控制温度
			}
            
		}
		else
		{
			Temp.ADDMode = 0;//进入稳定模式 
			Temp.Display_Rel = Temp.Rel;//显示实际温度
		}
	}
	else
	{
		Temp.Display_Rel = Temp.Rel;//显示实际温度
		Temp.New =0;//现在的速度清零
		Temp.Last = 0;//之前的速度清零
		Temp.ADDMode = 0;//清除显示处理
        T = 0;
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
	Temp.Display_Set = Temp.Set;//显示设定温度

	Speed.Display_Set = Speed.Set;//显示设定转速
	
	if(sys.Run_Status)
	{
		if(sys.SetMode_Option == 3)
			Time.Display = Time.Set;//显示设定时间
		else
			Time.Display = Time.Rel + 59;//显示控制时间
	}
	else			
		Time.Display = Time.Set;//显示设定时间  
        
	Display_Temp(Temp.Display_Set,Temp.Display_Rel);//显示温度
	Display_Speed(Speed.Display_Set,Speed.Display_Rel);//显示转速
	Display_Time(Time.Display);//显示时间
}
