#include "Show.h"

/**********全局变量声明******/
float Twinkle_Time;//闪烁时间

/**********局部变量声明******/
uint8_t Time_ShowFlag,Speed_ShowFlag,Temp_ShowFlag;//时间、速度、温度显示的标志位 0:常亮 1：熄灭
uint8_t Lock_ShowFlag,TimeIcn_ShowFlag,P_ShowFlag,Xg_ShowFlag;//开盖图标和时间图标闪烁和P模式闪烁和离心率闪烁

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
	if(sys.Run_Status)
	{
		T += dT;
		if(T >= 0.5f)
		{
			TimeIcn_ShowFlag = ~TimeIcn_ShowFlag;//开盖图标闪烁;
			T = 0;
		}
	}
	else
	{
		TimeIcn_ShowFlag = 0;//显示时间图标
	}
}

/*
*****************************************************************
 * 函数原型：void Check_Lock(float dT)
 * 功    能：开盖图标闪烁检测
*****************************************************************
*/
void Check_Lock(float dT)
{
	static float T;
	if(sys.Lock_On == 0)
	{
		Lock_ShowFlag = 0;
		return;
	}
	T += dT;
	if(T >= 0.5f)
	{
		Lock_ShowFlag = ~Lock_ShowFlag;//开盖图标闪烁;
		T = 0;
	}
	if((HAL_GPIO_ReadPin(UC_IN1_GPIO_Port,UC_IN1_Pin)== 1)&&(HAL_GPIO_ReadPin(UC_IN2_GPIO_Port,UC_IN2_Pin)== 1))//电磁锁1和电磁锁2都闭合时
		sys.Lock_On = 0;
}

/*
*****************************************************************
 * 函数原型：void Start_CircleRun(float dT)
 * 功    能：外框跑圈动画
*****************************************************************
*/
void Start_CircleRun(float dT)
{
	static float T;
	if(sys.Run_Status)
	{
		T += dT;
		if(T >= 0.5)
		{
			PModeIcon_Step++;
			if(PModeIcon_Step > 18)
				PModeIcon_Step = 7;
			T = 0;
		}
	}
	else
	{
		Circle_Run = 0;//停止动画
		PModeIcon_Step = 0;
	}
}

/*
*****************************************************************
 * 函数原型：void Start_SpeedRun(float dT)
 * 功    能：转速动画
*****************************************************************
*/
void Start_SpeedRun(float dT)
{
	static float T;
	if(sys.Run_Status == 0)
	{
		SpeedIcon_Step = 0;
		T = 0;
		return;
	}
	T += dT;
	if(T >= 0.5)
	{
		SpeedIcon_Step++;
		if(SpeedIcon_Step > 3)
			SpeedIcon_Step = 1;
		T = 0;
	}
}

/*
*****************************************************************
 * 函数原型：static void Check_Safe_Mode(float dT)
 * 功    能：安全温度图标闪烁检测
 * 调    用：内部调用
*****************************************************************
*/
static void Check_Safe_Mode(float dT)
{
	static float T;
	if(Safe_Temp_Twinkleg)
	{
		T += dT;
		if(T >= 0.5f)
		{
			Safe_Mode = ~Safe_Mode;//安全温度图标闪烁
			T = 0;
		}
	}
	else
	{
		if(sys.SetMode_Option == 4)
			Safe_Mode = 1;
		else
			Safe_Mode = 0;
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
	static float T;
    if(sys.SetMode_Option == 0)//如果没在设置选项中，则都点亮，不闪烁
    {
        Speed_ShowFlag = 0;//常亮
        Temp_ShowFlag = 0;//常亮
        Time_ShowFlag = 0;//常亮
		P_ShowFlag = 0;//常亮
		Xg_ShowFlag = 0;//离心率常亮
        Twinkle_Time = 0;//闪烁计时清零
        return;
    }
    if(Twinkle_Time && Key_Status==0)//闪烁和没有操作按键时
    {
		T += dT;
		if(T >= 0.5f)
		{
			Twinkle_Time -= 0.5;//闪烁计时
			if(sys.SetMode_Option == 1)//设置P值
			{
				Speed_ShowFlag = 0;//速度常亮
				Time_ShowFlag = 0;//时间常亮
				P_ShowFlag = ~P_ShowFlag;//P闪烁
				Temp_ShowFlag = 0;//温度常亮
				Xg_ShowFlag = 0;//离心率常亮
			}
			else if(sys.SetMode_Option == 2)//设置时间
			{
				Time_ShowFlag = ~Time_ShowFlag;//时间闪烁
				Speed_ShowFlag = 0;//速度常亮
				Temp_ShowFlag = 0;//温度常亮 
				P_ShowFlag = 0;//P常亮	
				Xg_ShowFlag = 0;//离心率常亮				
			}
			else if(sys.SetMode_Option == 3)//设置速度
			{ 
				Time_ShowFlag = 0;//时间常亮
				Speed_ShowFlag = ~Speed_ShowFlag;//速度闪烁
				Temp_ShowFlag = 0;//温度常亮
				P_ShowFlag = 0;//P常亮
				Xg_ShowFlag = 0;//离心率常亮
			}
			else if(sys.SetMode_Option == 4)//设置温度
			{
				Safe_Mode = 1;//点亮"SAFE"图标
				Speed_ShowFlag = 0;//速度常亮
				Time_ShowFlag = 0;//时间常亮
				Temp_ShowFlag = ~Temp_ShowFlag;//温度闪烁
				P_ShowFlag = 0;//P常亮
				Xg_ShowFlag = 0;//离心率常亮
			}
			else if(sys.SetMode_Option == 5)//设置离心率模块
			{
				Speed_ShowFlag = 0;//速度常亮
				Time_ShowFlag = 0;//时间常亮
				Temp_ShowFlag = 0;//温度常亮
				P_ShowFlag = 0;//P常亮
				Xg_ShowFlag = ~Xg_ShowFlag;//离心率闪烁
			}
			if(Twinkle_Time == 0)//如果闪烁结束
			{
				sys.SetMode_Option = 0;//模式选择清零
			} 
			T = 0;			
		}			
    }
	else
	{
		Speed_ShowFlag = 0;//常亮
        Temp_ShowFlag = 0;//常亮
        Time_ShowFlag = 0;//常亮
		Xg_ShowFlag = 0;//离心率常亮
		P_ShowFlag = 0;//P常亮
		T = 0;
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
	Time_Twinkle(dT);//时间图标闪烁
	Check_Lock(dT);//开盖图标闪烁检测
	Check_Safe_Mode(dT);//安全温度图标闪烁检测
	Start_SpeedRun(dT);//转速动画
	Start_CircleRun(dT);//外框跑圈动画
	Check_ShowFlag(dT);//闪烁检测
}

/*
*****************************************************************
 * 函数原型：void Display_Time(int32_t dis_set_time,int32_t dis_rel_time)
 * 功    能：显示时间
 * 输    入: dis_set_time 设定时间  dis_rel_time 实际时间
 * 参    数：int32_t dis_set_time,int32_t dis_rel_time
*****************************************************************
*/
void Display_Time(int32_t dis_set_time,int32_t dis_rel_time)
{
	uint8_t seg1,seg2,seg3,seg4,seg5,seg6,seg7,seg8,seg9;
	seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;seg7=0;seg8=0;seg9=0;
	uint8_t SH,H,SM,M;//时间的单位取值
	
	/***********设定时间计算**********/
    if(dis_set_time > 3599)//如果设定时间大于59.59分钟时
        Time_Unit=1;//单位变成分
    else
        Time_Unit=0;//不然就是秒
	
		if(Time_Unit == 1)
		{
			SH=dis_set_time/3600/10;//计算十位单位的小时数
			H=dis_set_time/3600%10;//计算个位单位的小时数
			SM=dis_set_time%3600/60/10;//计算十分位单位的分钟数
			M=dis_set_time%3600/60%10;//计算个分位单位的分钟数
		}
		else
		{
			SH=dis_set_time%3600/60/10;//计算十位单位的分钟数
			H=dis_set_time%3600/60%10;//计算个位单位的分钟数
			SM=dis_set_time%60/10;//计算十分位单位的秒钟数
			M=dis_set_time%60%10;//计算十分位单位的秒钟数
		}
	if(Time_ShowFlag == 0)
	{
		/***********set_time十小时位***********/
		switch(SH)
		{
			case 0:seg2&=0x0F;seg3&=0x8F;seg2|=0xF0;seg3|=0x50;//数字0
				break;
			case 1:seg2&=0x0F;seg3&=0x8F;seg2|=0x00;seg3|=0x50;//数字1
				break;
			case 2:seg2&=0x0F;seg3&=0x8F;seg2|=0xD0;seg3|=0x30;//数字2
				break;
			case 3:seg2&=0x0F;seg3&=0x8F;seg2|=0x90;seg3|=0x70;//数字3
				break;	
			case 4:seg2&=0x0F;seg3&=0x8F;seg2|=0x20;seg3|=0x70;//数字4
				break;	
			case 5:seg2&=0x0F;seg3&=0x8F;seg2|=0xB0;seg3|=0x60;//数字5
				break;	
			case 6:seg2&=0x0F;seg3&=0x8F;seg2|=0xF0;seg3|=0x60;//数字6
				break;	
			case 7:seg2&=0x0F;seg3&=0x8F;seg2|=0x10;seg3|=0x50;//数字7
				break;	
			case 8:seg2&=0x0F;seg3&=0x8F;seg2|=0xF0;seg3|=0x70;//数字8
				break;	
			case 9:seg2&=0x0F;seg3&=0x8F;seg2|=0xB0;seg3|=0x70;//数字9
				break;
			default:
				break;
		}	
		/***********set_time小时位***********/
		switch(H)
		{
			case 0:seg4&=0x0F;seg5&=0x8F;seg4|=0xF0;seg5|=0x50;//数字0
				break;
			case 1:seg4&=0x0F;seg5&=0x8F;seg4|=0x00;seg5|=0x50;//数字1
				break;
			case 2:seg4&=0x0F;seg5&=0x8F;seg4|=0xD0;seg5|=0x30;//数字2
				break;
			case 3:seg4&=0x0F;seg5&=0x8F;seg4|=0x90;seg5|=0x70;//数字3
				break;	
			case 4:seg4&=0x0F;seg5&=0x8F;seg4|=0x20;seg5|=0x70;//数字4
				break;	
			case 5:seg4&=0x0F;seg5&=0x8F;seg4|=0xB0;seg5|=0x60;//数字5
				break;	
			case 6:seg4&=0x0F;seg5&=0x8F;seg4|=0xF0;seg5|=0x60;//数字6
				break;	
			case 7:seg4&=0x0F;seg5&=0x8F;seg4|=0x10;seg5|=0x50;//数字7
				break;	
			case 8:seg4&=0x0F;seg5&=0x8F;seg4|=0xF0;seg5|=0x70;//数字8
				break;	
			case 9:seg4&=0x0F;seg5&=0x8F;seg4|=0xB0;seg5|=0x70;//数字9
				break;
			default:
				break;
		}	
		
		/***********set_time十分位***********/
		switch(SM%10)
		{
			case 0:seg6&=0x0F;seg7&=0x8F;seg6|=0xF0;seg7|=0x50;//数字0
				break;
			case 1:seg6&=0x0F;seg7&=0x8F;seg6|=0x00;seg7|=0x50;//数字1
				break;
			case 2:seg6&=0x0F;seg7&=0x8F;seg6|=0xD0;seg7|=0x30;//数字2
				break;
			case 3:seg6&=0x0F;seg7&=0x8F;seg6|=0x90;seg7|=0x70;//数字3
				break;	
			case 4:seg6&=0x0F;seg7&=0x8F;seg6|=0x20;seg7|=0x70;//数字4
				break;	
			case 5:seg6&=0x0F;seg7&=0x8F;seg6|=0xB0;seg7|=0x60;//数字5
				break;	
			case 6:seg6&=0x0F;seg7&=0x8F;seg6|=0xF0;seg7|=0x60;//数字6
				break;	
			case 7:seg6&=0x0F;seg7&=0x8F;seg6|=0x10;seg7|=0x50;//数字7
				break;	
			case 8:seg6&=0x0F;seg7&=0x8F;seg6|=0xF0;seg7|=0x70;//数字8
				break;	
			case 9:seg6&=0x0F;seg7&=0x8F;seg6|=0xB0;seg7|=0x70;//数字9
				break;
			default:
				break;
		}		
		
		/***********set_time分位***********/
		switch(M%10)
		{
			case 0:seg8&=0x0F;seg9&=0x8F;seg8|=0xF0;seg9|=0x50;//数字0
				break;
			case 1:seg8&=0x0F;seg9&=0x8F;seg8|=0x00;seg9|=0x50;//数字1
				break;
			case 2:seg8&=0x0F;seg9&=0x8F;seg8|=0xD0;seg9|=0x30;//数字2
				break;
			case 3:seg8&=0x0F;seg9&=0x8F;seg8|=0x90;seg9|=0x70;//数字3
				break;	
			case 4:seg8&=0x0F;seg9&=0x8F;seg8|=0x20;seg9|=0x70;//数字4
				break;	
			case 5:seg8&=0x0F;seg9&=0x8F;seg8|=0xB0;seg9|=0x60;//数字5
				break;	
			case 6:seg8&=0x0F;seg9&=0x8F;seg8|=0xF0;seg9|=0x60;//数字6
				break;	
			case 7:seg8&=0x0F;seg9&=0x8F;seg8|=0x10;seg9|=0x50;//数字7
				break;	
			case 8:seg8&=0x0F;seg9&=0x8F;seg8|=0xF0;seg9|=0x70;//数字8
				break;	
			case 9:seg8&=0x0F;seg9&=0x8F;seg8|=0xB0;seg9|=0x70;//数字9
				break;
			default:
				break;
		}			
	}
	else
	{
		seg2&=0x0F;seg3&=0x8F;seg2|=0x00;seg3|=0x00;//不显示
		seg4&=0x0F;seg5&=0x8F;seg4|=0x00;seg5|=0x00;//不显示
		seg6&=0x0F;seg7&=0x8F;seg6|=0x00;seg7|=0x00;//不显示
		seg8&=0x0F;seg9&=0x8F;seg8|=0x00;seg9|=0x00;//不显示
	}
	/***********实际时间计算**********/
	if(Time_Unit == 1)
	{
		SH=dis_rel_time/3600/10;//计算十位单位的小时数
		H=dis_rel_time/3600%10;//计算个位单位的小时数
		SM=dis_rel_time%3600/60/10;//计算十分位单位的分钟数
		M=dis_rel_time%3600/60%10;//计算个分位单位的分钟数
	}
	else
	{
		SH=dis_rel_time%3600/60/10;//计算十位单位的分钟数
		H=dis_rel_time%3600/60%10;//计算个位单位的分钟数
		SM=dis_rel_time%60/10;//计算十分位单位的秒钟数
		M=dis_rel_time%60%10;//计算十分位单位的秒钟数
	}
	/***********dis_rel_time十小时位***********/
	switch(SH)
	{
		case 0:seg1&=0xF0;seg2&=0xF1;seg1|=0x0F;seg2|=0x0A;//数字0
			break;
		case 1:seg1&=0xF0;seg2&=0xF1;seg1|=0x00;seg2|=0x0A;//数字1
			break;
		case 2:seg1&=0xF0;seg2&=0xF1;seg1|=0x0D;seg2|=0x06;//数字2
			break;
		case 3:seg1&=0xF0;seg2&=0xF1;seg1|=0x09;seg2|=0x0E;//数字3
			break;	
		case 4:seg1&=0xF0;seg2&=0xF1;seg1|=0x02;seg2|=0x0E;//数字4
			break;	
		case 5:seg1&=0xF0;seg2&=0xF1;seg1|=0x0B;seg2|=0x0D;//数字5
			break;	
		case 6:seg1&=0xF0;seg2&=0xF1;seg1|=0x0F;seg2|=0x0D;//数字6
			break;	
		case 7:seg1&=0xF0;seg2&=0xF1;seg1|=0x01;seg2|=0x0A;//数字7
			break;	
		case 8:seg1&=0xF0;seg2&=0xF1;seg1|=0x0F;seg2|=0x0E;//数字8
			break;	
		case 9:seg1&=0xF0;seg2&=0xF1;seg1|=0x0B;seg2|=0x0E;//数字9
			break;
		default:
			break;
	}	

	/***********dis_rel_time小时位***********/
	switch(H)
	{
		case 0:seg3&=0xF0;seg4&=0xF1;seg3|=0x0F;seg4|=0x0A;//数字0
			break;
		case 1:seg3&=0xF0;seg4&=0xF1;seg3|=0x00;seg4|=0x0A;//数字1
			break;
		case 2:seg3&=0xF0;seg4&=0xF1;seg3|=0x0D;seg4|=0x06;//数字2
			break;
		case 3:seg3&=0xF0;seg4&=0xF1;seg3|=0x09;seg4|=0x0E;//数字3
			break;	
		case 4:seg3&=0xF0;seg4&=0xF1;seg3|=0x02;seg4|=0x0E;//数字4
			break;	
		case 5:seg3&=0xF0;seg4&=0xF1;seg3|=0x0B;seg4|=0x0D;//数字5
			break;	
		case 6:seg3&=0xF0;seg4&=0xF1;seg3|=0x0F;seg4|=0x0D;//数字6
			break;	
		case 7:seg3&=0xF0;seg4&=0xF1;seg3|=0x01;seg4|=0x0A;//数字7
			break;	
		case 8:seg3&=0xF0;seg4&=0xF1;seg3|=0x0F;seg4|=0x0E;//数字8
			break;	
		case 9:seg3&=0xF0;seg4&=0xF1;seg3|=0x0B;seg4|=0x0E;//数字9
			break;
		default:
			break;
	}	
	
	/***********dis_rel_time十分位***********/
	switch(SM%10)
	{
		case 0:seg5&=0xF0;seg6&=0xF1;seg5|=0x0F;seg6|=0x0A;//数字0
			break;
		case 1:seg5&=0xF0;seg6&=0xF1;seg5|=0x00;seg6|=0x0A;//数字1
			break;
		case 2:seg5&=0xF0;seg6&=0xF1;seg5|=0x0D;seg6|=0x06;//数字2
			break;
		case 3:seg5&=0xF0;seg6&=0xF1;seg5|=0x09;seg6|=0x0E;//数字3
			break;	
		case 4:seg5&=0xF0;seg6&=0xF1;seg5|=0x02;seg6|=0x0E;//数字4
			break;	
		case 5:seg5&=0xF0;seg6&=0xF1;seg5|=0x0B;seg6|=0x0D;//数字5
			break;	
		case 6:seg5&=0xF0;seg6&=0xF1;seg5|=0x0F;seg6|=0x0D;//数字6
			break;	
		case 7:seg5&=0xF0;seg6&=0xF1;seg5|=0x01;seg6|=0x0A;//数字7
			break;	
		case 8:seg5&=0xF0;seg6&=0xF1;seg5|=0x0F;seg6|=0x0E;//数字8
			break;	
		case 9:seg5&=0xF0;seg6&=0xF1;seg5|=0x0B;seg6|=0x0E;//数字9
			break;
		default: 
			break;
	}		
	
	/***********dis_rel_time分位***********/
	switch(M%10)
	{
		case 0:seg7&=0xF0;seg8&=0xF1;seg7|=0x0F;seg8|=0x0A;//数字0
			break;
		case 1:seg7&=0xF0;seg8&=0xF1;seg7|=0x00;seg8|=0x0A;//数字1
			break;
		case 2:seg7&=0xF0;seg8&=0xF1;seg7|=0x0D;seg8|=0x06;//数字2
			break;
		case 3:seg7&=0xF0;seg8&=0xF1;seg7|=0x09;seg8|=0x0E;//数字3
			break;	
		case 4:seg7&=0xF0;seg8&=0xF1;seg7|=0x02;seg8|=0x0E;//数字4
			break;	
		case 5:seg7&=0xF0;seg8&=0xF1;seg7|=0x0B;seg8|=0x0D;//数字5
			break;	
		case 6:seg7&=0xF0;seg8&=0xF1;seg7|=0x0F;seg8|=0x0D;//数字6
			break;	
		case 7:seg7&=0xF0;seg8&=0xF1;seg7|=0x01;seg8|=0x0A;//数字7
			break;	
		case 8:seg7&=0xF0;seg8&=0xF1;seg7|=0x0F;seg8|=0x0E;//数字8
			break;	
		case 9:seg7&=0xF0;seg8&=0xF1;seg7|=0x0B;seg8|=0x0E;//数字9
			break;
		default:
			break;
	}
		
	/*************时间冒号图标***************/
	seg4&=0xFE; seg4|=0x01;//实际时间冒号
	seg5&=0x7F; seg5|=0x80;//设定时间冒号
	
    if(Time_Unit ==1)//时间单位切换
    {
        seg9&=0xF7;seg9|=0x08;//显示min
    }
    else
    {
        seg7&=0x7F;seg7|=0x80;//显示sec
    }
	
	
	/*************关闭盖子图标***************/
	if(Lock_ShowFlag == 0)//盖子底部
	{
		seg9&=0xFD;seg9|=0x02;//显示盖子底部
	}
	else
	{
		seg9&=0xFD;seg9|=0x00;//不显示盖子底部
	}
	if(Lid_State == 0)
	{
		seg9&=0xFE;seg9|=0x01;//关闭盖子图标
	}
	else
	{
		seg9&=0xFE;seg9|=0x00;//关闭盖子图标不显示
	}
	
	/****************************************/
	
	/*************时间图标***************/	
	if(TimeIcn_ShowFlag == 0)
	{
		seg9&=0xFB;seg9|=0x04;//显示
	}
	else
	{
		seg9&=0xFB;seg9|=0x00;//不显示
	}
	
	/************************************/
	Write_Addr_Dat_N(0, seg1,1);//SEG29
	Write_Addr_Dat_N(2, seg2,1);//SEG28
	Write_Addr_Dat_N(4, seg3,1);//SEG27
	Write_Addr_Dat_N(6, seg4,1);//SEG26
	Write_Addr_Dat_N(8, seg5,1);//SEG25
	Write_Addr_Dat_N(10, seg6,1);//SEG24
	Write_Addr_Dat_N(12, seg7,1);//SEG23
	Write_Addr_Dat_N(14, seg8,1);//SEG22
	Write_Addr_Dat_N(16, seg9,1);//SEG21
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
	uint8_t seg10,seg11,seg12,seg13,seg14,seg15,seg16,seg17,seg18,seg19,seg20,seg21;
	seg10=0;seg11=0;seg12=0;seg13=0;seg14=0;seg15=0;seg16=0;seg17=0;seg18=0;seg19=0;seg20=0;seg21=0;
	uint16_t Val;//用于百十个取出来的数字
	
	/***********设定转速计算**********/
	if(Speed_ShowFlag == 0)
	{
		/***********dis_set_speed千位***********/
		if(dis_set_speed > 9999)//大于9999时
		{
			seg20&=0x7F;seg20|=0x80;//显示1		
		}
		else//小于9999时
		{
			seg20&=0x7F;seg20|=0x00;//不显示
		}
		
		/***********dis_set_speed千位***********/
		if(dis_set_speed > 999)//大于999时
		{
			Val=dis_set_speed/1000;//取出千位
			if(dis_set_speed > 9999)//大于9999时
				Val=Val%10;//取出千位
			switch(Val)
			{
				case 0:seg20&=0x8F;seg21&=0x0F;seg20|=0x50;seg21|=0xF0;//数字0
					break;
				case 1:seg20&=0x8F;seg21&=0x0F;seg20|=0x50;seg21|=0x00;//数字1
					break;
				case 2:seg20&=0x8F;seg21&=0x0F;seg20|=0x30;seg21|=0xD0;//数字2
					break;
				case 3:seg20&=0x8F;seg21&=0x0F;seg20|=0x70;seg21|=0x90;//数字3
					break;	
				case 4:seg20&=0x8F;seg21&=0x0F;seg20|=0x70;seg21|=0x20;//数字4
					break;	
				case 5:seg20&=0x8F;seg21&=0x0F;seg20|=0x60;seg21|=0xB0;//数字5
					break;	
				case 6:seg20&=0x8F;seg21&=0x0F;seg20|=0x60;seg21|=0xF0;//数字6
					break;	
				case 7:seg20&=0x8F;seg21&=0x0F;seg20|=0x50;seg21|=0x10;//数字7
					break;	
				case 8:seg20&=0x8F;seg21&=0x0F;seg20|=0x70;seg21|=0xF0;//数字8
					break;	
				case 9:seg20&=0x8F;seg21&=0x0F;seg20|=0x70;seg21|=0xB0;//数字9
					break;
				default:
					break;
			}			
		}
		else
		{
			seg20&=0x8F;seg21&=0x0F;seg20|=0x00;seg21|=0x00;//不显示
		}

		/***********dis_set_speed百位***********/
		if(dis_set_speed > 99)//大于99时
		{
			Val=dis_set_speed/100;//取出百位
			if(dis_set_speed > 999)//大于999时
				Val=Val%10;//取出百位
			switch(Val)
			{
				case 0:seg15&=0x8F;seg14&=0x0F;seg15|=0x50;seg14|=0xF0;//数字0
					break;
				case 1:seg15&=0x8F;seg14&=0x0F;seg15|=0x50;seg14|=0x00;//数字1
					break;
				case 2:seg15&=0x8F;seg14&=0x0F;seg15|=0x30;seg14|=0xD0;//数字2
					break;
				case 3:seg15&=0x8F;seg14&=0x0F;seg15|=0x70;seg14|=0x90;//数字3
					break;
				case 4:seg15&=0x8F;seg14&=0x0F;seg15|=0x70;seg14|=0x20;//数字4
					break;	
				case 5:seg15&=0x8F;seg14&=0x0F;seg15|=0x60;seg14|=0xB0;//数字5
					break;
				case 6:seg15&=0x8F;seg14&=0x0F;seg15|=0x60;seg14|=0xF0;//数字6
					break;	
				case 7:seg15&=0x8F;seg14&=0x0F;seg15|=0x50;seg14|=0x10;//数字7
					break;	
				case 8:seg15&=0x8F;seg14&=0x0F;seg15|=0x70;seg14|=0xF0;//数字8
					break;	
				case 9:seg15&=0x8F;seg14&=0x0F;seg15|=0x70;seg14|=0xB0;//数字9
					break;
				default:
					break;
			}			
		}
		else
		{
			seg15&=0x8F;seg14&=0x0F;seg15|=0x00;seg14|=0x00;//不显示
		}
		/***********dis_set_speed十位***********/
		if(dis_set_speed > 9)//大于9时
		{
			Val=dis_set_speed/10;//取出十位
			if(dis_set_speed > 99)//大于99时
				Val=Val%10;//取出十位
			switch(Val)
			{
				case 0:seg17&=0x8F;seg16&=0x0F;seg17|=0x50;seg16|=0xF0;//数字0
					break;
				case 1:seg17&=0x8F;seg16&=0x0F;seg17|=0x50;seg16|=0x00;//数字1
					break;
				case 2:seg17&=0x8F;seg16&=0x0F;seg17|=0x30;seg16|=0xD0;//数字2
					break;
				case 3:seg17&=0x8F;seg16&=0x0F;seg17|=0x70;seg16|=0x90;//数字3
					break;
				case 4:seg17&=0x8F;seg16&=0x0F;seg17|=0x70;seg16|=0x20;//数字4
					break;	
				case 5:seg17&=0x8F;seg16&=0x0F;seg17|=0x60;seg16|=0xB0;//数字5
					break;
				case 6:seg17&=0x8F;seg16&=0x0F;seg17|=0x60;seg16|=0xF0;//数字6
					break;	
				case 7:seg17&=0x8F;seg16&=0x0F;seg17|=0x50;seg16|=0x10;//数字7
					break;	
				case 8:seg17&=0x8F;seg16&=0x0F;seg17|=0x70;seg16|=0xF0;//数字8
					break;	
				case 9:seg17&=0x8F;seg16&=0x0F;seg17|=0x70;seg16|=0xB0;//数字9
					break;
				default:
					break;
			}			
		}
		else
		{
			seg17&=0x8F;seg16&=0x0F;seg17|=0x00;seg16|=0x00;//不显示
		}
		/***********dis_set_speed个位***********/
		Val=dis_set_speed%10;//取出个位
		switch(Val)
		{
			case 0:seg19&=0x8F;seg18&=0x0F;seg19|=0x50;seg18|=0xF0;//数字0
				break;
			case 1:seg19&=0x8F;seg18&=0x0F;seg19|=0x50;seg18|=0x00;//数字1
				break;
			case 2:seg19&=0x8F;seg18&=0x0F;seg19|=0x30;seg18|=0xD0;//数字2
				break;
			case 3:seg19&=0x8F;seg18&=0x0F;seg19|=0x70;seg18|=0x90;//数字3
				break;
			case 4:seg19&=0x8F;seg18&=0x0F;seg19|=0x70;seg18|=0x20;//数字4
				break;	
			case 5:seg19&=0x8F;seg18&=0x0F;seg19|=0x60;seg18|=0xB0;//数字5
				break;
			case 6:seg19&=0x8F;seg18&=0x0F;seg19|=0x60;seg18|=0xF0;//数字6
				break;	
			case 7:seg19&=0x8F;seg18&=0x0F;seg19|=0x50;seg18|=0x10;//数字7
				break;	
			case 8:seg19&=0x8F;seg18&=0x0F;seg19|=0x70;seg18|=0xF0;//数字8
				break;	
			case 9:seg19&=0x8F;seg18&=0x0F;seg19|=0x70;seg18|=0xB0;//数字9
				break;
			default:
				break;
		}	
	}
	else
	{		
		seg20&=0x7F;seg20|=0x00;//不显示
		seg20&=0x8F;seg21&=0x0F;seg20|=0x00;seg21|=0x00;//不显示
		seg15&=0x8F;seg14&=0x0F;seg15|=0x00;seg14|=0x00;//不显示
		seg17&=0x8F;seg16&=0x0F;seg17|=0x00;seg16|=0x00;//不显示
		seg19&=0x8F;seg18&=0x0F;seg19|=0x00;seg18|=0x00;//不显示
	}
	/***********实际转速计算**********/
	if((Speed_ModeFlag == 0) || (sys.Run_Status == 1))
	{
		/***********dis_rel_speed万位***********/
		if(dis_rel_speed > 9999)//大于9999时
		{
			Val=dis_rel_speed/10000;//取出万位
			switch(Val)
			{
				case 0:seg12&=0xF0;seg13&=0xF1;seg12|=0x0F;seg13|=0x0A;//数字0
					break;
				case 1:seg12&=0xF0;seg13&=0xF1;seg12|=0x00;seg13|=0x0A;//数字1
					break;
				case 2:seg12&=0xF0;seg13&=0xF1;seg12|=0x0D;seg13|=0x06;//数字2
					break;
				case 3:seg12&=0xF0;seg13&=0xF1;seg12|=0x09;seg13|=0x0E;//数字3
					break;	
				case 4:seg12&=0xF0;seg13&=0xF1;seg12|=0x02;seg13|=0x0E;//数字4
					break;	
				case 5:seg12&=0xF0;seg13&=0xF1;seg12|=0x0B;seg13|=0x0C;//数字5
					break;	
				case 6:seg12&=0xF0;seg13&=0xF1;seg12|=0x0F;seg13|=0x0C;//数字6
					break;	
				case 7:seg12&=0xF0;seg13&=0xF1;seg12|=0x01;seg13|=0x0A;//数字7
					break;	
				case 8:seg12&=0xF0;seg13&=0xF1;seg12|=0x0F;seg13|=0x0E;//数字8
					break;	
				case 9:seg12&=0xF0;seg13&=0xF1;seg12|=0x0B;seg13|=0x0E;//数字9
					break;
				default:
					break;
			}
		}
		else//小于9999时
		{
			seg12&=0xF0;seg13&=0xF1;seg12|=0x00;seg13|=0x00;//不显示
		}
		/***********dis_rel_speed千位***********/
		if(dis_rel_speed > 999)//大于999时
		{
			Val=dis_rel_speed/1000;//取出千位
			if(dis_rel_speed > 9999)//大于9999时
				Val=Val%10;//取出千位
			switch(Val)
			{
				case 0:seg21&=0xF0;seg20&=0xF1;seg21|=0x0F;seg20|=0x0A;//数字0
					break;
				case 1:seg21&=0xF0;seg20&=0xF1;seg21|=0x00;seg20|=0x0A;//数字1
					break;
				case 2:seg21&=0xF0;seg20&=0xF1;seg21|=0x0D;seg20|=0x06;//数字2
					break;
				case 3:seg21&=0xF0;seg20&=0xF1;seg21|=0x09;seg20|=0x0E;//数字3
					break;	
				case 4:seg21&=0xF0;seg20&=0xF1;seg21|=0x02;seg20|=0x0E;//数字4
					break;	
				case 5:seg21&=0xF0;seg20&=0xF1;seg21|=0x0B;seg20|=0x0C;//数字5
					break;	
				case 6:seg21&=0xF0;seg20&=0xF1;seg21|=0x0F;seg20|=0x0C;//数字6
					break;	
				case 7:seg21&=0xF0;seg20&=0xF1;seg21|=0x01;seg20|=0x0A;//数字7
					break;
				case 8:seg21&=0xF0;seg20&=0xF1;seg21|=0x0F;seg20|=0x0E;//数字8
					break;	
				case 9:seg21&=0xF0;seg20&=0xF1;seg21|=0x0B;seg20|=0x0E;//数字9
					break;
				default:
					break;
			}
		}
		else//小于999时
		{
			seg21&=0xF0;seg20&=0xF1;seg21|=0x00;seg20|=0x00;//不显示
		}
		/***********dis_rel_speed百位***********/
		if(dis_rel_speed > 99)//大于99时
		{
			Val=dis_rel_speed/100;//取出百位
			if(dis_rel_speed > 999)//大于999时
				Val=Val%10;//取出百位
			switch(Val)
			{
				case 0:seg14&=0xF0;seg15&=0xF1;seg14|=0x0F;seg15|=0x0A;//数字0
					break;
				case 1:seg14&=0xF0;seg15&=0xF1;seg14|=0x00;seg15|=0x0A;//数字1
					break;
				case 2:seg14&=0xF0;seg15&=0xF1;seg14|=0x0D;seg15|=0x06;//数字2
					break;
				case 3:seg14&=0xF0;seg15&=0xF1;seg14|=0x09;seg15|=0x0E;//数字3
					break;	
				case 4:seg14&=0xF0;seg15&=0xF1;seg14|=0x02;seg15|=0x0E;//数字4
					break;	
				case 5:seg14&=0xF0;seg15&=0xF1;seg14|=0x0B;seg15|=0x0C;//数字5
					break;	
				case 6:seg14&=0xF0;seg15&=0xF1;seg14|=0x0F;seg15|=0x0C;//数字6
					break;	
				case 7:seg14&=0xF0;seg15&=0xF1;seg14|=0x01;seg15|=0x0A;//数字7
					break;
				case 8:seg14&=0xF0;seg15&=0xF1;seg14|=0x0F;seg15|=0x0E;//数字8
					break;	
				case 9:seg14&=0xF0;seg15&=0xF1;seg14|=0x0B;seg15|=0x0E;//数字9
					break;
				default:
					break;
			}
		}
		else//小于99时
		{
			seg14&=0xF0;seg15&=0xF1;seg14|=0x00;seg15|=0x00;//不显示
		}
		/***********dis_rel_speed十位***********/
		if(dis_rel_speed > 9)//大于9时
		{
			Val=dis_rel_speed/10;//取出十位
			if(dis_rel_speed > 99)//大于999时
				Val=Val%10;//取出十位
			switch(Val)
			{
				case 0:seg16&=0xF0;seg17&=0xF1;seg16|=0x0F;seg17|=0x0A;//数字0
					break;
				case 1:seg16&=0xF0;seg17&=0xF1;seg16|=0x00;seg17|=0x0A;//数字1
					break;
				case 2:seg16&=0xF0;seg17&=0xF1;seg16|=0x0D;seg17|=0x06;//数字2
					break;
				case 3:seg16&=0xF0;seg17&=0xF1;seg16|=0x09;seg17|=0x0E;//数字3
					break;	
				case 4:seg16&=0xF0;seg17&=0xF1;seg16|=0x02;seg17|=0x0E;//数字4
					break;	
				case 5:seg16&=0xF0;seg17&=0xF1;seg16|=0x0B;seg17|=0x0C;//数字5
					break;	
				case 6:seg16&=0xF0;seg17&=0xF1;seg16|=0x0F;seg17|=0x0C;//数字6
					break;	
				case 7:seg16&=0xF0;seg17&=0xF1;seg16|=0x01;seg17|=0x0A;//数字7
					break;
				case 8:seg16&=0xF0;seg17&=0xF1;seg16|=0x0F;seg17|=0x0E;//数字8
					break;	
				case 9:seg16&=0xF0;seg17&=0xF1;seg16|=0x0B;seg17|=0x0E;//数字9
					break;
				default:
					break;
			}
		}
		else//小于9时
		{
			seg16&=0xF0;seg17&=0xF1;seg16|=0x00;seg17|=0x00;//不显示
		}
		/***********dis_rel_speed个位***********/
		Val=dis_rel_speed%10;//取出个位
		switch(Val)
		{
			case 0:seg18&=0xF0;seg19&=0xF1;seg18|=0x0F;seg19|=0x0A;//数字0
				break;
			case 1:seg18&=0xF0;seg19&=0xF1;seg18|=0x00;seg19|=0x0A;//数字1
				break;
			case 2:seg18&=0xF0;seg19&=0xF1;seg18|=0x0D;seg19|=0x06;//数字2
				break;
			case 3:seg18&=0xF0;seg19&=0xF1;seg18|=0x09;seg19|=0x0E;//数字3
				break;	
			case 4:seg18&=0xF0;seg19&=0xF1;seg18|=0x02;seg19|=0x0E;//数字4
				break;	
			case 5:seg18&=0xF0;seg19&=0xF1;seg18|=0x0B;seg19|=0x0C;//数字5
				break;	
			case 6:seg18&=0xF0;seg19&=0xF1;seg18|=0x0F;seg19|=0x0C;//数字6
				break;	
			case 7:seg18&=0xF0;seg19&=0xF1;seg18|=0x01;seg19|=0x0A;//数字7
				break;
			case 8:seg18&=0xF0;seg19&=0xF1;seg18|=0x0F;seg19|=0x0E;//数字8
				break;	
			case 9:seg18&=0xF0;seg19&=0xF1;seg18|=0x0B;seg19|=0x0E;//数字9
				break;
			default:
				break;
		}
	}
	else if((Speed_ModeFlag) && (sys.Run_Status == 0))/*离心力显示模式*/
	{
		if(Xg_ShowFlag == 0)//闪烁显示部分
		{
			seg12&=0xF0;seg13&=0xF1;seg12|=0x00;seg13|=0x00;//不显示
			seg21&=0xF0;seg20&=0xF1;seg21|=0x07;seg20|=0x06;//数字P
			seg14&=0xF0;seg15&=0xF1;seg14|=0x00;seg15|=0x04;//显示"-"
			/***********dis_rel_speed十位***********/
			if(Xg_Mode > 9)//大于9时
			{
				Val=Xg_Mode/10;//取出十位
				if(Xg_Mode > 99)//大于999时
					Val=Val%10;//取出十位
				switch(Val)
				{
					case 0:seg16&=0xF0;seg17&=0xF1;seg16|=0x0F;seg17|=0x0A;//数字0
						break;
					case 1:seg16&=0xF0;seg17&=0xF1;seg16|=0x00;seg17|=0x0A;//数字1
						break;
					case 2:seg16&=0xF0;seg17&=0xF1;seg16|=0x0D;seg17|=0x06;//数字2
						break;
					case 3:seg16&=0xF0;seg17&=0xF1;seg16|=0x09;seg17|=0x0E;//数字3
						break;	
					case 4:seg16&=0xF0;seg17&=0xF1;seg16|=0x02;seg17|=0x0E;//数字4
						break;	
					case 5:seg16&=0xF0;seg17&=0xF1;seg16|=0x0B;seg17|=0x0C;//数字5
						break;	
					case 6:seg16&=0xF0;seg17&=0xF1;seg16|=0x0F;seg17|=0x0C;//数字6
						break;	
					case 7:seg16&=0xF0;seg17&=0xF1;seg16|=0x01;seg17|=0x0A;//数字7
						break;
					case 8:seg16&=0xF0;seg17&=0xF1;seg16|=0x0F;seg17|=0x0E;//数字8
						break;	
					case 9:seg16&=0xF0;seg17&=0xF1;seg16|=0x0B;seg17|=0x0E;//数字9
						break;
					default:
						break;
				}
			}
			else//小于9时
			{
				seg16&=0xF0;seg17&=0xF1;seg16|=0x0F;seg17|=0x0A;//数字0
			}
			/***********dis_rel_speed个位***********/
			Val=Xg_Mode%10;//取出个位
			switch(Val)
			{
				case 0:seg18&=0xF0;seg19&=0xF1;seg18|=0x0F;seg19|=0x0A;//数字0
					break;
				case 1:seg18&=0xF0;seg19&=0xF1;seg18|=0x00;seg19|=0x0A;//数字1
					break;
				case 2:seg18&=0xF0;seg19&=0xF1;seg18|=0x0D;seg19|=0x06;//数字2
					break;
				case 3:seg18&=0xF0;seg19&=0xF1;seg18|=0x09;seg19|=0x0E;//数字3
					break;	
				case 4:seg18&=0xF0;seg19&=0xF1;seg18|=0x02;seg19|=0x0E;//数字4
					break;	
				case 5:seg18&=0xF0;seg19&=0xF1;seg18|=0x0B;seg19|=0x0C;//数字5
					break;	
				case 6:seg18&=0xF0;seg19&=0xF1;seg18|=0x0F;seg19|=0x0C;//数字6
					break;	
				case 7:seg18&=0xF0;seg19&=0xF1;seg18|=0x01;seg19|=0x0A;//数字7
					break;
				case 8:seg18&=0xF0;seg19&=0xF1;seg18|=0x0F;seg19|=0x0E;//数字8
					break;	
				case 9:seg18&=0xF0;seg19&=0xF1;seg18|=0x0B;seg19|=0x0E;//数字9
					break;
				default:
					break;
			}
		}
		else
		{
			seg12&=0xF0;seg13&=0xF1;seg12|=0x00;seg13|=0x00;//不显示
			seg21&=0xF0;seg20&=0xF1;seg21|=0x00;seg20|=0x00;//不显示
			seg14&=0xF0;seg15&=0xF1;seg14|=0x00;seg15|=0x00;//不显示
			seg16&=0xF0;seg17&=0xF1;seg16|=0x00;seg17|=0x00;//不显示
			seg18&=0xF0;seg19&=0xF1;seg18|=0x00;seg19|=0x00;//不显示
		}
	}
	/*****************盖子打开******************/
	if(Lid_State && (Lock_ShowFlag == 0))
	{
		seg10&=0xFE;seg10|=0x01;//开盖
	}
	else
	{
		seg10&=0xFE;seg10|=0x00;//开盖不显示
	}
	
	/*******************************************/
	
	/*****************转速图标******************/
	switch(SpeedIcon_Step)
	{
		case 0:seg10&=0xF1;seg11&=0xF1;seg10|=0x0E;seg11|=0x0E;//常亮
			break;
		case 1:seg11&=0xF1;seg11|=0x06;seg10&=0xF1;seg10|=0x0C;//S5&S6&S8&S9
			break;
		case 2:seg10&=0xF1;seg11&=0xF1;seg10|=0x0A;seg11|=0x0A;//S10&S5&S7&S8
			break;
		case 3:seg11&=0xF1;seg11|=0x0C;seg10&=0xF1;seg10|=0x06;//S6&S7&S9&S10
			break;
		default:
			break;
	}
	
	/******************************************/
	
	/*************℃&℉图标**************/
//	seg12&=0xEF;seg12|=0x10;//华氏度
	seg13&=0xEF;seg13|=0x10;//摄氏度
	
	/******************************************/
	
	/*************xg&rpm**************/
	if(Speed_Unit)
	{
		seg19&=0x7F;seg19|=0x80;//xg
	}
	else
	{
		seg17&=0x7F;seg17|=0x80;//rpm
	}
	/******************************************/
	
	Write_Addr_Dat_N(18, seg10,1);//SEG20
	Write_Addr_Dat_N(20, seg11,1);//SEG19
	Write_Addr_Dat_N(22, seg12,1);//SEG18
	Write_Addr_Dat_N(24, seg13,1);//SEG17
	Write_Addr_Dat_N(26, seg14,1);//SEG16
	Write_Addr_Dat_N(28, seg15,1);//SEG15
	Write_Addr_Dat_N(30, seg16,1);//SEG14
	Write_Addr_Dat_N(32, seg17,1);//SEG13
	Write_Addr_Dat_N(34, seg18,1);//SEG12
	Write_Addr_Dat_N(36, seg19,1);//SEG11
	Write_Addr_Dat_N(38, seg20,1);//SEG10
	Write_Addr_Dat_N(40, seg21,1);//SEG9
}

/*
*****************************************************************
 * 函数原型：void Display_RunMode(uint16_t temp,uint8_t P)
 * 功    能：显示安全温度和记忆模式
 * 输    入: temp 安全温度  P 记忆模式
 * 参    数：uint16_t temp,uint8_t P
*****************************************************************
*/
void Display_RunMode(uint16_t temp,uint8_t P)
{
	uint8_t seg22,seg23,seg24,seg25,seg26,seg27,seg28,seg29;
	seg22=0;seg23=0;seg24=0;seg25=0;seg26=0;seg27=0;seg28=0;seg29=0;
	uint16_t Val;//用于百十个取出来的数字
	if(Temp_ShowFlag == 0)
	{
		/***********temp千位***********/
		if(temp > 999)//大于999时
		{
			Val=temp/1000;//取出千位
			switch(Val)
			{
				case 0:seg29&=0xF0;seg28&=0xF8;seg29|=0x0F;seg28|=0x05;//数字0
					break;
				case 1:seg29&=0xF0;seg28&=0xF8;seg29|=0x00;seg28|=0x05;//数字1
					break;
				case 2:seg29&=0xF0;seg28&=0xF8;seg29|=0x0D;seg28|=0x03;//数字2
					break;
				case 3:seg29&=0xF0;seg28&=0xF8;seg29|=0x09;seg28|=0x07;//数字3
					break;	
				case 4:seg29&=0xF0;seg28&=0xF8;seg29|=0x02;seg28|=0x07;//数字4
					break;	
				case 5:seg29&=0xF0;seg28&=0xF8;seg29|=0x0B;seg28|=0x06;//数字5
					break;	
				case 6:seg29&=0xF0;seg28&=0xF8;seg29|=0x0F;seg28|=0x06;//数字6
					break;	
				case 7:seg29&=0xF0;seg28&=0xF8;seg29|=0x01;seg28|=0x05;//数字7
					break;
				case 8:seg29&=0xF0;seg28&=0xF8;seg29|=0x0F;seg28|=0x07;//数字8
					break;	
				case 9:seg29&=0xF0;seg28&=0xF8;seg29|=0x0B;seg28|=0x07;//数字9
					break;
				default:
					break;
			}
		}
		else//小于999时
		{
			seg29&=0xF0;seg28&=0xF8;seg29|=0x00;seg28|=0x00;//不显示
		}

		/***********temp百位***********/
		if(temp > 99)//大于99时
		{
			Val=temp/100;//取出百位
			if(temp > 999)//大于999时
				Val=Val%10;//取出百位
			switch(Val)
			{
				case 0:seg27&=0xF0;seg26&=0xF8;seg27|=0x0F;seg26|=0x05;//数字0
					break;
				case 1:seg27&=0xF0;seg26&=0xF8;seg27|=0x00;seg26|=0x05;//数字1
					break;
				case 2:seg27&=0xF0;seg26&=0xF8;seg27|=0x0D;seg26|=0x03;//数字2
					break;
				case 3:seg27&=0xF0;seg26&=0xF8;seg27|=0x09;seg26|=0x07;//数字3
					break;	
				case 4:seg27&=0xF0;seg26&=0xF8;seg27|=0x02;seg26|=0x07;//数字4
					break;	
				case 5:seg27&=0xF0;seg26&=0xF8;seg27|=0x0B;seg26|=0x06;//数字5
					break;	
				case 6:seg27&=0xF0;seg26&=0xF8;seg27|=0x0F;seg26|=0x06;//数字6
					break;	
				case 7:seg27&=0xF0;seg26&=0xF8;seg27|=0x01;seg26|=0x05;//数字7
					break;
				case 8:seg27&=0xF0;seg26&=0xF8;seg27|=0x0F;seg26|=0x07;//数字8
					break;
				case 9:seg27&=0xF0;seg26&=0xF8;seg27|=0x0B;seg26|=0x07;//数字9
					break;
				default:
					break;
			}
		}
		else//小于99时
		{
			seg27&=0xF0;seg26&=0xF8;seg27|=0x00;seg26|=0x00;//不显示
		}
		
		/***********temp十位***********/
		if(temp > 9)//大于9时
		{
			Val=temp/10;//取出十位
			if(temp > 99)//大于999时
				Val=Val%10;//取出十位
			switch(Val)
			{
				case 0:seg25&=0xF0;seg24&=0xF8;seg25|=0x0F;seg24|=0x05;//数字0
					break;
				case 1:seg25&=0xF0;seg24&=0xF8;seg25|=0x00;seg24|=0x05;//数字1
					break;
				case 2:seg25&=0xF0;seg24&=0xF8;seg25|=0x0D;seg24|=0x03;//数字2
					break;
				case 3:seg25&=0xF0;seg24&=0xF8;seg25|=0x09;seg24|=0x07;//数字3
					break;	
				case 4:seg25&=0xF0;seg24&=0xF8;seg25|=0x02;seg24|=0x07;//数字4
					break;	
				case 5:seg25&=0xF0;seg24&=0xF8;seg25|=0x0B;seg24|=0x06;//数字5
					break;	
				case 6:seg25&=0xF0;seg24&=0xF8;seg25|=0x0F;seg24|=0x06;//数字6
					break;	
				case 7:seg25&=0xF0;seg24&=0xF8;seg25|=0x01;seg24|=0x05;//数字7
					break;
				case 8:seg25&=0xF0;seg24&=0xF8;seg25|=0x0F;seg24|=0x07;//数字8
					break;	
				case 9:seg25&=0xF0;seg24&=0xF8;seg25|=0x0B;seg24|=0x07;//数字9
					break;
				default:
					break;
			}
		}
		else//小于9时
		{
			seg25&=0xF0;seg24&=0xF8;seg25|=0x0F;seg24|=0x05;//数字0
		}

	/***********temp个位***********/
		Val=temp%10;//取出个位
		switch(Val)
		{
			case 0:seg23&=0xF0;seg22&=0xF8;seg23|=0x0F;seg22|=0x05;//数字0
				break;
			case 1:seg23&=0xF0;seg22&=0xF8;seg23|=0x00;seg22|=0x05;//数字1
				break;
			case 2:seg23&=0xF0;seg22&=0xF8;seg23|=0x0D;seg22|=0x03;//数字2
				break;
			case 3:seg23&=0xF0;seg22&=0xF8;seg23|=0x09;seg22|=0x07;//数字3
				break;	
			case 4:seg23&=0xF0;seg22&=0xF8;seg23|=0x02;seg22|=0x07;//数字4
				break;	
			case 5:seg23&=0xF0;seg22&=0xF8;seg23|=0x0B;seg22|=0x06;//数字5
				break;	
			case 6:seg23&=0xF0;seg22&=0xF8;seg23|=0x0F;seg22|=0x06;//数字6
				break;	
			case 7:seg23&=0xF0;seg22&=0xF8;seg23|=0x01;seg22|=0x05;//数字7
				break;
			case 8:seg23&=0xF0;seg22&=0xF8;seg23|=0x0F;seg22|=0x07;//数字8
				break;	
			case 9:seg23&=0xF0;seg22&=0xF8;seg23|=0x0B;seg22|=0x07;//数字9
				break;
			default:
				break;
		}
	}
	else
	{
		seg25&=0xF0;seg24&=0xF8;seg25|=0x00;seg24|=0x00;//不显示
		seg27&=0xF0;seg26&=0xF8;seg27|=0x00;seg26|=0x00;//不显示
		seg29&=0xF0;seg28&=0xF8;seg29|=0x00;seg28|=0x00;//不显示
		seg23&=0xF0;seg22&=0xF8;seg23|=0x00;seg22|=0x00;//不显示
	}	
	
	/*********温度小数点*********/
	seg24&=0xF7;seg24|=0x08;
		
	/*********显示"SAFE"*********/
	if(Safe_Mode)
	{
		seg22&=0x7F;seg22|=0x80;//显示"SAFE"
	}	
	else
	{
		seg22&=0x7F;seg22|=0x00;//不显示
	}

	/*********************P模式********************/
	if(Show_Circle)
	{
		switch(PModeIcon_Step)
		{
			case 0:seg29&=0x0F;seg27&=0x7F;seg26&=0xF7;seg29|=0xF0;seg27|=0x80;seg26|=0x08;
				   seg25&=0x7F;seg23&=0x7F;seg22&=0x87;seg25|=0x80;seg23|=0x80;seg22|=0x78;//外框全部亮
				break;
			case 1:seg29&=0x0F;seg29|=0x10;//L1
				break;
			case 2:seg26&=0xF7;seg26|=0x08;seg29&=0x0F;seg29|=0x10;//l1-L2
				break;
			case 3:seg26&=0xF7;seg26|=0x08;seg29&=0x0F;seg29|=0x10;seg22&=0x87;seg22|=0x08;//L1-L3
				break;	
			case 4:seg26&=0xF7;seg26|=0x08;seg29&=0x0F;seg29|=0x10;seg22&=0x87;seg22|=0x18;//L1-L4
				break;	
			case 5:seg26&=0xF7;seg26|=0x08;seg29&=0x0F;seg29|=0x10;seg22&=0x87;seg22|=0x38;//L1-L5
				break;	
			case 6:seg26&=0xF7;seg26|=0x08;seg29&=0x0F;seg29|=0x10;seg22&=0x87;seg22|=0x78;//L1-L6
				break;	
			case 7:seg26&=0xF7;seg22&=0x87;seg23&=0x7F;seg26|=0x08;seg22|=0x78;seg23|=0x80;//L2-L7
				break;
			case 8:seg22&=0x87;seg23&=0x7F;seg25&=0x7F;seg22|=0x78;seg23|=0x80;seg25|=0x80;//L3-L8
				break;	
			case 9:seg22&=0x87;seg23&=0x7F;seg25&=0x7F;seg27&=0x7F;seg22|=0x70;seg23|=0x80;seg25|=0x80;seg27|=0x80;//L4-L9
				break;
			case 10:seg22&=0x87;seg23&=0x7F;seg25&=0x7F;seg27&=0x7F;seg29&=0x0F;seg22|=0x60;seg23|=0x80;seg25|=0x80;seg27|=0x80;seg29|=0x80;//L5-L10
				break;
			case 11:seg22&=0x87;seg23&=0x7F;seg25&=0x7F;seg27&=0x7F;seg29&=0x0F;seg22|=0x40;seg23|=0x80;seg25|=0x80;seg27|=0x80;seg29|=0xC0;//L6-L11
				break;
			case 12:seg23&=0x7F;seg25&=0x7F;seg27&=0x7F;seg29&=0x0F;seg23|=0x80;seg25|=0x80;seg27|=0x80;seg29|=0xE0;//L7-L12
				break;
			case 13:seg29&=0x0F;seg25&=0x7F;seg27&=0x7F;seg25|=0x80;seg27|=0x80;seg29|=0xF0;//L8-L1
				break;
			case 14:seg26&=0xF7;seg29&=0x0F;seg27&=0x7F;seg27|=0x80;seg29|=0xF0;seg26|=0x08;//L9-L2
				break;
			case 15:seg22&=0x87;seg26&=0xF7;seg29&=0x0F;seg29|=0xF0;seg26|=0x08;seg22|=0x08;//L10-L3
				break;
			case 16:seg22&=0x87;seg26&=0xF7;seg29&=0x0F;seg29|=0x70;seg26|=0x08;seg22|=0x18;//L11-L4
				break;
			case 17:seg22&=0x87;seg26&=0xF7;seg29&=0x0F;seg29|=0x30;seg26|=0x08;seg22|=0x38;//L12-L5
				break;
			case 18:seg22&=0x87;seg26&=0xF7;seg29&=0x0F;seg29|=0x10;seg26|=0x08;seg22|=0x78;//L1-L6
				break;
			default:
				break;
		}
		if(P_ShowFlag == 0)
		{
			seg28&=0x0F;seg27&=0x8F;seg28|=0x70;seg27|=0x30;//P
			seg25&=0x8F;seg25|=0x20;//"-"
			switch(P)
			{
				case 0:seg23&=0x8F;seg24&=0x0F;seg23|=0x50;seg24|=0xF0;//数字0
					break;
				case 1:seg23&=0x8F;seg24&=0x0F;seg23|=0x50;seg24|=0x00;//数字1
					break;
				case 2:seg23&=0x8F;seg24&=0x0F;seg23|=0x30;seg24|=0xD0;//数字2
					break;
				case 3:seg23&=0x8F;seg24&=0x0F;seg23|=0x70;seg24|=0x90;//数字3
					break;	
				case 4:seg23&=0x8F;seg24&=0x0F;seg23|=0x70;seg24|=0x20;//数字4
					break;	
				case 5:seg23&=0x8F;seg24&=0x0F;seg23|=0x60;seg24|=0xB0;//数字5
					break;	
				case 6:seg23&=0x8F;seg24&=0x0F;seg23|=0x60;seg24|=0xF0;//数字6
					break;	
				case 7:seg23&=0x8F;seg24&=0x0F;seg23|=0x50;seg24|=0x10;//数字7
					break;	
				case 8:seg23&=0x8F;seg24&=0x0F;seg23|=0x70;seg24|=0xF0;//数字8
					break;	
				case 9:seg23&=0x8F;seg24&=0x0F;seg23|=0x70;seg24|=0xB0;//数字9
					break;
				default:
					break;
			}
		}
		else
		{
			seg28&=0x0F;seg27&=0x8F;seg28|=0x00;seg27|=0x00;//P
			seg25&=0x8F;seg25|=0x00;//"-"
			seg23&=0x8F;seg24&=0x0F;seg23|=0x00;seg24|=0x00;
		}
	}
	else
	{
		seg28&=0x0F;seg27&=0x8F;seg28|=0x00;seg27|=0x00;//P
		seg25&=0x8F;seg25|=0x00;//"-"
		seg23&=0x8F;seg24&=0x0F;seg23|=0x00;seg24|=0x00;
		seg29&=0x0F;seg27&=0x7F;seg26&=0xF7;seg29|=0x00;seg27|=0x00;seg26|=0x00;
		seg25&=0x7F;seg23&=0x7F;seg22&=0x87;seg25|=0x00;seg23|=0x00;seg22|=0x00;//外框全部灭
	}
	
	/**********************************************/
	Write_Addr_Dat_N(42, seg22,1);//SEG8
	Write_Addr_Dat_N(44, seg23,1);//SEG7
	Write_Addr_Dat_N(46, seg24,1);//SEG6
	Write_Addr_Dat_N(48, seg25,1);//SEG5
	Write_Addr_Dat_N(50, seg26,1);//SEG4
	Write_Addr_Dat_N(52, seg27,1);//SEG3
	Write_Addr_Dat_N(54, seg28,1);//SEG2
	Write_Addr_Dat_N(56, seg29,1);//SEG1
}

/*
*****************************************************************
 * 函数原型：void Deal_Speed(float dT)
 * 功    能：速度显示处理
*****************************************************************
*/
void Deal_Speed(float dT)
{
    if(sys.Run_Status == 1)//启动的情况下
    {
        if(Speed_ADDMode == 0)//在电机控制中，速度未处理
        {
			Display_RelSpeed = 0;
			Speed_ADDMode = 1;//进入加速模式下
        }
        else if(Speed_ADDMode==1)//在进入加速模式下
        { 
			if(Display_RelSpeed < Rel_Speed)
				Display_RelSpeed++;
			if(Display_RelSpeed >= Ctrl_Speed)//实际速度大于等于控制速度
				Speed_ADDMode = 3;//进入稳定模式
        }
		else if(Speed_ADDMode==2)//在进入加速模式下
        { 
			if(Display_RelSpeed > Rel_Speed)
				Display_RelSpeed--;
			if(!sys.Motor_Stop && (Display_RelSpeed <= Rel_Speed))
				Speed_ADDMode = 3;//进入稳定模式
        }
        else if(Speed_ADDMode == 3)//速度稳定模式下
        {
            Display_RelSpeed = Ctrl_Speed;//显示控制速度
        }
	}
	else
	{
		if(Speed_ADDMode==2)//在进入加速模式下
        { 
			if(Display_RelSpeed > Rel_Speed)
				Display_RelSpeed--;
			if((Display_RelSpeed <= Rel_Speed))
				Display_RelSpeed = 0;
        }
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
	if(HAL_GPIO_ReadPin(UC_IN2_GPIO_Port,UC_IN2_Pin)== 1)
	{
		Display_CtrlTime = 1;
	}	
	else
	{
		Display_CtrlTime = 0;
	}
	
	if(HAL_GPIO_ReadPin(UC_IN1_GPIO_Port,UC_IN1_Pin)== 1)
	{
		Display_RelSpeed = 1;
	}
	else
	{
		Display_RelSpeed = 0;
	}
	
	Display_SetTime = 0;
	
	Display_Time(Display_SetTime,Display_CtrlTime);
	Display_SetSpeed = 0;
	Display_Speed(Display_SetSpeed,Display_RelSpeed);
//	Display_RunMode(Display_SafeTemp,PMode_Option);
}
