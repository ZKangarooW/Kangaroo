#include "Show.h"

/**********全局变量声明******/
float Twinkle_Time;//闪烁时间

/**********局部变量声明******/
uint8_t Time_ShowFlag,Speed_ShowFlag;//时间、速度显示的标志位 0:常亮 1：熄灭
uint8_t Lock_ShowFlag,TimeIcn_ShowFlag,SpeedIcn_ShowFlag;//开盖图标和时间图标闪烁和速度单位图标闪烁
uint8_t Tab[] = {0x77,0x24,0x5D,0x6D,0x2E,0x6B,0x7B,0x25,0x7F,0x6F};//0·9

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
        Time_ShowFlag = 0;//常亮
        Twinkle_Time = 0;//闪烁计时清零
        return;
    }
    if(Twinkle_Time && Key_Status==0)//闪烁和没有操作按键时
    {
		T += dT;
		if(T >= 0.5f)
		{
			Twinkle_Time -= 0.5;//闪烁计时
			if(sys.SetMode_Option == 1)//设置时速度
			{
				Speed_ShowFlag = ~Speed_ShowFlag;//速度常亮
				Time_ShowFlag = 0;//时间常亮
			}
			else if(sys.SetMode_Option == 2)//设置时间
			{
				Time_ShowFlag = ~Time_ShowFlag;//时间闪烁
				Speed_ShowFlag = 0;//速度常亮			
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
        Time_ShowFlag = 0;//常亮
		T = 0;
	}
}

/*
*****************************************************************
 * 函数原型：static void Time_Twinkle(float dT)
 * 功    能：时间图标闪烁
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
			TimeIcn_ShowFlag = ~TimeIcn_ShowFlag;//时间图标闪烁;
			SpeedIcn_ShowFlag = ~SpeedIcn_ShowFlag;//速度图标闪烁;
			T = 0;
		}
	}
	else
	{
		TimeIcn_ShowFlag = 0;//显示时间图标
		SpeedIcn_ShowFlag = 0;//显示速度图标;
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
	if(HAL_GPIO_ReadPin(UC_IN_GPIO_Port,UC_IN_Pin)== 1)//电磁锁1和电磁锁2都闭合时
		sys.Lock_On = 0;
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
	Check_Lock(dT);//开盖图标闪烁
}

/*
*****************************************************************
 * 函数原型：void Display(int16_t speed,int32_t time)
 * 功    能：显示速度和时间
*****************************************************************
*/
void Display(int16_t speed,int32_t time)
{
	uint8_t seg1,seg2,seg3,seg4,seg5,seg6,seg7,seg8;
	seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;seg7=0;seg8=0;
	uint16_t Val;//用于百十个取出来的数字
	uint8_t SH,H,SM,M;//时间的单位取值
	
	/***********设定转速计算**********/
	if(Speed_ShowFlag == 0)//设置时闪烁
	{
		/***********speed千位***********/
		if(speed > 999)//大于999时
		{
			Val = speed/1000;//取出千位
			seg1&=0x80;seg1|=Tab[Val];//数字		
		}
		else
		{
			seg1&=0x80;seg1|=0x00;//不显示
		}

		/***********speed百位***********/
		if(speed > 99)//大于99时
		{
			Val=speed/100;//取出百位
			if(speed > 999)//大于999时
				Val=Val%10;//取出百位
			seg2&=0x80;seg2|=Tab[Val];//数字	
		}
		else
		{
			seg2&=0x80;seg2|=0x00;//不显示
		}
		/***********speed十位***********/
		if(speed > 9)//大于9时
		{
			Val=speed/10;//取出十位
			if(speed > 99)//大于99时
				Val=Val%10;//取出十位
			seg3&=0x80;seg3|=Tab[Val];//数字	
		}
		else
		{
			seg3&=0x80;seg3|=0x00;//不显示
		}
		
		/***********speed个位***********/
		Val=speed%10;//取出个位
		seg4&=0x80;seg4|=Tab[Val];//数字
	}
	else//不显示
	{
		seg1&=0x80;seg1|=0x00;//不显示
		seg2&=0x80;seg2|=0x00;//不显示
		seg3&=0x80;seg3|=0x00;//不显示
		seg4&=0x80;seg4|=0x00;//不显示
	}
	
	/***********时间计算**********/
	SH=time%3600/60/10;//计算十位单位的分钟数
	H=time%3600/60%10;//计算个位单位的分钟数
	SM=time%60/10;//计算十分位单位的秒钟数
	M=time%60%10;//计算十分位单位的秒钟数
	
	if(Time_ShowFlag == 0)//时间设置时闪烁
	{
		if(Time.Set > 0)//设置时间大于零时显示时间
		{
			/***********set_time十小时位***********/
			seg5&=0x80;seg5|=Tab[SH];//数字	
		
			/***********set_time小时位***********/
			seg6&=0x80;seg6|=Tab[H];//数字	
			
			/***********set_time十分位***********/
			seg7&=0x80;seg7|=Tab[SM%10];//数字	
			
			/***********set_time分位***********/
			seg8&=0x80;seg8|=Tab[M%10];//数字		
		}
		else//设置时间小于等于0时显示“-- --”
		{
			seg5&=0x80;seg5|=0x08;//"-"
			seg6&=0x80;seg6|=0x08;//"-"
			seg7&=0x80;seg7|=0x08;//"-"
			seg8&=0x80;seg8|=0x08;//"-"
		}	
	}
	else//时间闪烁
	{
		seg5&=0x80;seg5|=0x00;//不显示
		seg6&=0x80;seg6|=0x00;//不显示
		seg7&=0x80;seg7|=0x00;//不显示
		seg8&=0x80;seg8|=0x00;//不显示
	}
	/*************xg&rpm*********************/
	if(SpeedIcn_ShowFlag == 0)//速度单位闪烁
	{
		if(Speed.Unit)
		{
			seg5&=0x7F;seg5|=0x80;//显示xg
		}
		else
		{
			seg4&=0x7F;seg4|=0x80;//显示rpm
		}
	}
	else
	{
		seg4&=0x7F;seg4|=0x00;//不显示rpm
		seg5&=0x7F;seg5|=0x00;//不显示xg
	}
	/*************时间冒号图标***************/
	if(TimeIcn_ShowFlag == 0)//时间冒号闪烁
	{
		seg6&=0x7F;seg6|=0x80;//显示时间冒号
		seg7&=0x7F;seg7|=0x80;//显示sec
	}
	else
	{
		seg6&=0x7F;seg6|=0x00;//不显示时间冒号
		seg7&=0x7F;seg7|=0x00;//显示sec
	}
	/*************时间单位图标***************/
	seg7&=0x7F;seg7|=0x80;//显示sec
	
	/*************开盖关盖图标***************/
	if(Lid_State == 0)
	{
		seg2&=0x7F;seg2|=0x80;//显示底部方块
		seg3&=0x7F;seg3|=0x80;//显示关盖
	}
	else
	{
		if(Lock_ShowFlag == 0)//盖子底部
		{
			seg1&=0x7F;seg1|=0x80;//显示开盖
			seg2&=0x7F;seg2|=0x80;//显示盖子底部
		}
		else
		{
			seg1&=0x7F;seg1|=0x00;//不显示开盖
			seg2&=0x7F;seg2|=0x00;//不显示盖子底部
		}
	}
	
	Write_Addr_Dat_N(0,seg1,1);//SEG9
	Write_Addr_Dat_N(2,seg2,1);//SEG10
	Write_Addr_Dat_N(4,seg3,1);//SEG11
	Write_Addr_Dat_N(6,seg4,1);//SEG12
	Write_Addr_Dat_N(8,seg5,1);//SEG13
	Write_Addr_Dat_N(10,seg6,1);//SEG14
	Write_Addr_Dat_N(12,seg7,1);//SEG15
	Write_Addr_Dat_N(14,seg8,1);//SEG16
}

/*
*****************************************************************
 * 函数原型：void Deal_Speed(float dT)
 * 功    能：速度显示处理
*****************************************************************
*/
float Speed_Xg;
void Deal_Speed(float dT)
{
    if(sys.Run_Status == 1)//启动的情况下
    {
        if(Speed.Unit)
        {
            Speed_Xg = 11.18f * ((float)Speed.Rel/1000.0f) * ((float)Speed.Rel/1000.0f) * 9.6f;
        }
        else
        {
            Speed_Xg = Speed.Rel;
        }
        
        if(Speed.ADDMode == 0)//在电机控制中，速度未处理
        {
			Speed.Display = 0;
			Speed.New =0;//现在的速度清零
			Speed.Last = 0;//之前的速度清零
			Speed.ADDMode = 1;//进入加速模式下
        }
        else if(Speed.ADDMode==1)//在进入加速模式下
        { 
            Speed.New = Speed_Xg;//记录当前速度
            if(Speed.New > Speed.Display)//当前速度大于显示速度
			{
				if(Speed.Display < Speed.New)
//                    Speed.Display = Speed.New;//显示当前速度
					Speed.Display += 1;//显示当前速度
			}
            else//当前速度小于上一次速度
            {
                Speed.Display = Speed.Display;//显示上一次速度，不让速度小于当前速度。呈现攀升速度的现象
            }  
			if(sys.Motor_Stop == 0)
			{
				if(Speed.Display >= Speed.Ctrl)//实际速度大于等于控制速度
				{
					Speed.ADDMode = 3;//进入稳定模式
					return;
				}
			}
        }
		else if(Speed.ADDMode==2)//在进入加速模式下
        { 
			Speed.New = Speed_Xg;//记录当前速度
            
            if(Speed.New < Speed.Display)//当前速度小于上一次速度
			{
				if(Speed.Display > Speed.New)
					Speed.Display -= 1;//显示当前速度
//                    Speed.Display = Speed.New;//显示当前速度
			}
            else//当前速度大于上一次速度
            {
                Speed.Display = Speed.Display;//显示上一次速度，不让速度大于当前速度。呈现下降速度的现象
            }
			if(sys.Motor_Stop == 0)
			{
				if(Speed.Display <= Speed.Ctrl)//实际速度小于等于控制速度
				{
					Speed.ADDMode = 3;//进入稳定模式
					return;
				}
			}
        }
        else if(Speed.ADDMode == 3)//速度稳定模式下
        {
            Speed.Display = Speed.Ctrl;//显示控制速度
        }
	}
	else
	{
		Speed.Display = Speed.Set;
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
	if(sys.Run_Status == 0)
	{
		Time.Display = Time.Set;
	}
	else
	{
		Time.Display = Time.Ctrl;
	}
	Display(Speed.Display,Time.Display);//显示速度和时间
}
