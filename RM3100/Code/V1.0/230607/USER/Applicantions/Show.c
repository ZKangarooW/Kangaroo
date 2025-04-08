#include "Show.h"

/**********全局变量声明******/
float Twinkle_Time;//闪烁时间

/**********局部变量声明******/
uint8_t Time_ShowFlag,Speed_ShowFlag;//时间、速度显示的标志位 0:常亮 1：熄灭
uint8_t TimeIcn_ShowFlag,SpeedIcn_ShowFlag;//时间图标闪烁,速度单位图标闪烁
uint8_t Tab[] = {0x77,0x24,0x5D,0x6D,0x2E,0x6B,0x7B,0x25,0x7F,0x6F};//0·9

/*
*****************************************************************
 * 函数原型： void Check_ShowFlag(float dT)
 * 功    能： 闪烁检测
 * 输    入:  dT:执行周期
 * 参    数： float dT
*****************************************************************
*/  
void Check_ShowFlag(float dT)
{
	static float T,T1;
    if(sys.Run_Status == 1)//系统启动后
	{
		T1 += dT;//闪烁计时
		if(T1 >= 0.5f)//大于0.5S后
		{
			if(Set_Time > 0)//只有设定时间大于0才闪烁
				TimeIcn_ShowFlag = ~TimeIcn_ShowFlag;//运行闪烁
			else
				TimeIcn_ShowFlag = 0;//时间冒号图标常亮
			SpeedIcn_ShowFlag = ~SpeedIcn_ShowFlag;//速度单位运行闪烁
			T1 = 0;//计时清零
		}
	}
    else//没启动的情况下
	{
		SpeedIcn_ShowFlag = 0;//速度单位图标常亮
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
 * 函数原型： void Display(int16_t speed,int32_t time)
 * 功    能： 显示速度和时间
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
	SH=time/3600/10;//计算十位单位的小时数
	H=time/3600%10;//计算个位单位的小时数
	SM=time%3600/60/10;//计算十分位单位的分钟数
	M=time%3600/60%10;//计算个分位单位的分钟数
	
	if(Time_ShowFlag == 0)//时间设置时闪烁
	{
		if(Set_Time > 0)//设置时间大于零时显示时间
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
		seg4&=0x7F;seg4|=0x80;//显示rpm
	}
	else
	{
		seg4&=0x7F;seg4|=0x00;//不显示rpm
	}
	/*************时间冒号图标***************/
	if(TimeIcn_ShowFlag == 0)//时间冒号闪烁
	{
		seg6&=0x7F;seg6|=0x80;//显示时间冒号
	}
	else
	{
		seg6&=0x7F;seg6|=0x00;//不显示时间冒号
	}
	/*************时间单位图标***************/
	seg8&=0x7F;seg8|=0x80;//显示min
	
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
			Display_Speed = Speed;
            if(Ctrl_Speed > Rel_Speed)//控制速度大于实际速度
            {
                Speed_ADDMode = 1;//进入加速模式下
            }
            else if(Ctrl_Speed <= Display_Speed)//控制速度小于显示速度
            {
                Speed_ADDMode = 2;//进入减速模式下
            }
        }
        if(Speed_ADDMode==1)//在进入加速模式下
        { 
			if(Display_Speed< Rel_Speed)
				Display_Speed++;
            if(Display_Speed >= Ctrl_Speed)//实际速度大于等于控制速度
            {
                Speed_ADDMode = 3;//进入稳定模式
                return;
            }
        }
        else if(Speed_ADDMode == 2)//速度下降模式下
        {
			if(Display_Speed>Rel_Speed)
				Display_Speed--;
            if(Rel_Speed <= Ctrl_Speed)//实际速度小于等于控制速度
            {
                Speed_ADDMode = 3;//稳定模式
                return;
            }
        }
        else if(Speed_ADDMode == 3)//速度稳定模式下
        {
            Display_Speed = Ctrl_Speed;//显示控制速度
        }
		else if(Speed_ADDMode == 4)//速度下降停止模式下
        {
			if(Display_Speed>Rel_Speed)
				Display_Speed--;
            if(Rel_Speed <= 0)//实际速度小于等于0
            {
                Speed_ADDMode = 3;//稳定模式
                return;
            }
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
	if(sys.Run_Status == 0)//不启动
    {
        Display_Speed  = Set_Speed;//显示设定速度
        Display_Time  = Set_Time;//显示设定时间
    }
    else//启动后
    {
        if(sys.SetMode_Option == 1)//在设置速度模式下
        {
            Display_Speed  = Set_Speed;//显示设定速度
            Display_Time = Ctrl_Time+59;//显示实际时间
        }
        else if(sys.SetMode_Option == 2)//在设置时间模式下
        {
            Deal_Speed();//速度显示处理
            Display_Time = Set_Time;//显示设定时间 
        }            
        else//在不设置模式下
        {
            Deal_Speed();//速度显示处理 
            Display_Time = Ctrl_Time+59;//显示实际时间
        }
    }
	Display(Display_Speed,Display_Time);//显示屏幕
}
