#include "Show.h"

/**********全局变量声明******/
float Twinkle_Time;//闪烁时间

/**********局部变量声明******/
uint8_t Time_ShowFlag,Speed_ShowFlag,Lock_ShowFlag;//时间、速度显示的标志位 0:常亮 1：熄灭
uint8_t TimeIcn_ShowFlag;//时间图标闪烁
uint8_t Tab[] = {0x5F,0x06,0x3D,0x2F,0x66,0x6B,0x7B,0x0E,0x7F,0x6F};//0·9

/*
*****************************************************************
 * 函数原型：static void Check_Lock(float dT)
 * 功    能：开盖图标闪烁检测
 * 调    用：内部调用
*****************************************************************
*/
static void Check_Lock(float dT)
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
	if(HAL_GPIO_ReadPin(KEY_UP_GPIO_Port,KEY_UP_Pin)== 1)//电磁锁闭合时
		sys.Lock_On = 0;
}

/*
*****************************************************************
 * 函数原型：static void Check_ShowFlag(float dT)
 * 功    能：闪烁检测
 * 输    入: dT:执行周期
 * 参    数：float dT
*****************************************************************
*/
static void Check_ShowFlag(float dT)
{
	static float T,T1;
    if(sys.Run_Status == 1)//系统启动后
	{
		T1 += dT;//闪烁计时
		if(T1 >= 0.5f)//大于0.5S后
		{
			TimeIcn_ShowFlag = ~TimeIcn_ShowFlag;//运行闪烁
			T1 = 0;//计时清零
		}
	}
    else//没启动的情况下
	{
        TimeIcn_ShowFlag = 0;//时间冒号图标常亮
		T1 = 0;//计时清零
	}
    if(sys.SetMode_Option == 0 || Key_Status)//如果没在设置选项中或者按键的情况下，则都点亮，不闪烁
    {
        Speed_ShowFlag = 0;//常亮
        Time_ShowFlag = 0;//常亮
		T = 0;//计时清零
        return;
    }
    if(Twinkle_Time && Key_Status==0)//闪烁和没有操作旋钮时
    {
        T += dT;//闪烁计时
		if(T >= 0.5f)//大于0.5S后
		{
			Twinkle_Time -= 0.5;//闪烁计时
			if(sys.SetMode_Option == 1)//设置速度
			{
				Speed_ShowFlag = ~Speed_ShowFlag;//速度闪烁
				Time_ShowFlag = 0;//时间常亮
			}
			else if(sys.SetMode_Option == 2)//设置时间
			{
				Speed_ShowFlag = 0;//速度常亮
				Time_ShowFlag = ~Time_ShowFlag;//时间闪烁
			}
			if(Twinkle_Time == 0)//如果闪烁结束
			{
				sys.SetMode_Option = 0;//模式选择清零
			}  
			T = 0;//计时清零		
		}		
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
	Check_Lock(dT);//开盖图标闪烁检测
	Check_ShowFlag(dT);//闪烁检测
}


/*
*****************************************************************
 * 函数原型： void Display(int16_t speed,int32_t time)
 * 功    能： 显示速度和时间
*****************************************************************
*/
void Display(int16_t speed,int32_t time)
{
	uint8_t seg,seg1,seg2,seg3,seg4,seg5,seg6;
	seg = 0;seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;
	uint16_t Val;//用于百十个取出来的数字
	uint8_t SM,M;//时间的单位取值
	
	/***********设定转速计算**********/
	if(Speed_ShowFlag == 0)//设置时闪烁
	{
		/***********speed百位***********/
		if(speed > 99)//大于99时
		{
			Val=speed/100;//取出百位
			if(speed > 999)//大于999时
				Val=Val%10;//取出百位
			seg1&=0x80;seg1|=Tab[Val];//数字	
		}
		else
		{
			seg1&=0x80;seg1|=0x00;//不显示
		}
		/***********speed十位***********/
		if(speed > 9)//大于9时
		{
			Val=speed/10;//取出十位
			if(speed > 99)//大于99时
				Val=Val%10;//取出十位
			seg2&=0x80;seg2|=Tab[Val];//数字	
		}
		else
		{
			seg2&=0x80;seg2|=0x00;//不显示
		}
		
		/***********speed个位***********/
		Val=speed%10;//取出个位
		seg3&=0x80;seg3|=Tab[Val];//数字
	}
	else//不显示
	{
		seg1&=0x80;seg1|=0x00;//不显示
		seg2&=0x80;seg2|=0x00;//不显示
		seg3&=0x80;seg3|=0x00;//不显示
	}
	
	/***********时间计算**********/
	if(time >= 60)//如果设定时间大于60秒时
        Time.Time_Unit=1;//单位变成分
    else
        Time.Time_Unit=0;//不然就是秒
	
	if(Time.Time_Unit == 1)//时间单位为分钟时
	{
		SM=time/60/10;//计算十位单位的分钟数
		M=time/60%10;//计算个位单位的分钟数
	}
	else//时间单位为秒时
	{
		SM=time%60/10;//计算十分位单位的秒钟数
		M=time%60%10;//计算十分位单位的秒钟数
	}
	
	if(Time_ShowFlag == 0)//时间设置时闪烁
	{
		/***********set_time第一位***********/
		seg4&=0x80;seg4|=Tab[SM];//数字	
	
		/***********set_time第二位***********/
		seg&=0x80;seg|=Tab[M];//数字			
	}
	else//时间闪烁
	{
		seg4&=0x80;seg4|=0x00;//不显示
		seg&=0x80;seg|=0x00;//不显示
	}
	
	/*************数据拆分*******************/
	seg5 = seg&0xF0;
	seg6 = (seg<<4)&0XF0;
	
	/*************xg&rpm*********************/
	if(TimeIcn_ShowFlag == 0)//转速单位图标闪烁
	{
		if(Speed.Speed_Unit)
		{
			seg1&=0x7F;seg1|=0x80;//显示rcf
		}
		else
		{
			seg4&=0x7F;seg4|=0x80;//显示rpm
		}
	}
	else
	{
		seg1&=0x7F;seg1|=0x00;//不显示rcf
		seg4&=0x7F;seg4|=0x00;//不显示rpm
	}
	
	/*************时间单位图标***************/
	if(TimeIcn_ShowFlag == 0)//时间单位图标闪烁
	{
		if(Time.Time_Unit)//时间单位为分钟时
		{
			seg5&=0xF5;seg5|=0x08;//显示min
		}
		else//时间单位为秒时
		{
			seg5&=0xF5;seg5|=0x01;//显示sec
		}
	}
	else
	{
		seg5&=0xF5;seg5|=0x00;//不显示时间单位图标
	}
	
	/*************盖子图标*******************/
	if(Lock_ShowFlag == 0)
	{
		if(Lock_Status)
		{
			seg2&=0x7F;seg2|=0x80;//开盖图标
		}
		else
		{
			seg3&=0x7F;seg3|=0x80;//关盖图标
		}
		seg5&=0x7F;seg5|=0x80;//盖子底部图标
	}
	else
	{
		seg2&=0x7F;seg2|=0x00;//开盖图标
		seg3&=0x7F;seg3|=0x00;//关盖图标
		seg5&=0x7F;seg5|=0x00;//盖子底部图标
	}
	
	Write_Addr_Dat_N(0,seg1,1);//SEG9
	Write_Addr_Dat_N(2,seg2,1);//SEG10
	Write_Addr_Dat_N(4,seg3,1);//SEG11
	Write_Addr_Dat_N(6,seg4,1);//SEG12
	Write_Addr_Dat_N(8,seg5,1);//SEG13
	Write_Addr_Dat_N(10,seg6,1);//SEG14
}

/*
*****************************************************************
 * 函数原型： void Show_Display(void)
 * 功    能： 显示屏幕内容
*****************************************************************
*/
void Show_Display(void)
{	
	if(sys.Run_Status == 0)//不启动
    {
		if(Speed.Rel_Speed)
		{
			Speed.Display_Speed  = Speed.Rel_Speed;//显示实际速度
            Time.Display_Time = Time.Set_Time; //显示设定时间 
		}
		else
		{
			Speed.Display_Speed  = Speed.Set_Speed;//显示设定速度
			Time.Display_Time  = Time.Set_Time;//显示设定时间
		}
    }
    else//启动后
    {
		Speed.Display_Speed  = Speed.Rel_Speed;//显示实际速度
		Time.Display_Time = Time.Ctrl_Time;//显示实际时间
    }
	Display(Speed.Display_Speed/10,Time.Display_Time);//显示屏幕
}
