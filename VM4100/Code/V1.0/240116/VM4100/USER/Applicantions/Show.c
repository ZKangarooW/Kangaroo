#include "Show.h"
#if(Type)
/**********全局变量声明******/
float Twinkle_Time;//闪烁时间

/**********局部变量声明******/
uint8_t Time_ShowFlag,Speed_ShowFlag;//时间、速度显示的标志位 0:常亮 1：熄灭
uint8_t TimeIcn_ShowFlag;//时间图标闪烁
uint8_t Tab[] = {0xF5,0x05,0xB6,0x97,0x47,0xD3,0xF3,0x85,0xF7,0xD7};//0·9
uint8_t Tab1[] = {0x5f,0x50,0x6B,0x79,0x74,0x3D,0x3F,0x58,0x7F,0x7D};//0·9

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
 * 函数原型： void Display(int16_t speed,int32_t time)
 * 功    能： 显示速度和时间
*****************************************************************
*/
void Display(int16_t speed,int32_t time)
{
	uint8_t seg1,seg2,seg3,seg4,seg5,seg6;
	seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;
	uint16_t Val;//用于百十个取出来的数字
	uint8_t SM,M;//时间的单位取值	
	
	/***********设定转速计算**********/
	if(Speed_ShowFlag == 0)//设置时闪烁
	{
		/***********speed千位***********/
		if(speed > 999)//大于999时
		{
			Val=speed/1000;//取出千位
			seg6&=0x80;seg6|=Tab1[Val];//数字	
		}
		else
		{
			seg6&=0x80;seg6|=0x00;//不显示
		}
		
		/***********speed百位***********/
		if(speed > 99)//大于99时
		{
			Val=speed/100;//取出百位
			if(speed > 999)//大于999时
				Val=Val%10;//取出百位
			seg5&=0x80;seg5|=Tab1[Val];//数字	
		}
		else
		{
			seg5&=0x80;seg5|=0x00;//不显示
		}
		/***********speed十位***********/
		if(speed > 9)//大于9时
		{
			Val=speed/10;//取出十位
			if(speed > 99)//大于99时
				Val=Val%10;//取出十位
			seg4&=0x80;seg4|=Tab1[Val];//数字	
		}
		else
		{
			seg4&=0x80;seg4|=0x00;//不显示
		}
		
		/***********speed个位***********/
		seg1&=0xD0;seg1|=0x20;//数字
	}
	else//不显示
	{
		seg1&=0xD0;seg1|=0x00;//不显示
		seg4&=0x80;seg2|=0x00;//不显示
		seg5&=0x80;seg3|=0x00;//不显示
		seg6&=0x80;seg1|=0x00;//不显示
	}
	
	/***********时间计算**********/
	if(time >= 3600)//如果设定时间大于3600秒时
        Time_Unit=1;//单位变成小时
    else
        Time_Unit=0;//不然就是分
	
	if(Time_Unit == 1)//时间单位为小时时
	{
		SM=time/3600/10;//计算十位单位的小时数
		M=time/3600%10;//计算个位单位的小时数
	}
	else//时间单位为秒时
	{
		SM=time/60/10;//计算十分位单位分钟数
		M=time/60%10;//计算十分位单位分钟数
	}
	
	if(Time_ShowFlag == 0)//时间设置时闪烁
	{
		if(Set_Time > 0 && Time_State==0)//设置时间大于零时显示时间
		{
			/***********set_time第一位***********/
			seg2&=0x08;seg2|=Tab[SM];//数字	
		
			/***********set_time第二位***********/
			seg3&=0x08;seg3|=Tab[M];//数字		
		}
		else//设置时间小于等于0时显示“-- --”
		{
			seg2&=0x08;seg2|=0x02;//"-"
			seg3&=0x08;seg3|=0x02;//"-"
		}	
	}
	else//时间闪烁
	{
		seg2&=0x08;seg2|=0x00;//不显示
		seg3&=0x08;seg3|=0x00;//不显示
	}

	/*************模块显示图标*************/
	if(Set_Speed <= 800)
	{
		seg5&=0x7F;seg5|=0x80;//显示方块
		seg6&=0x7F;seg6|=0x80;//显示园
	}
	else if(Set_Speed > 800 && Set_Speed <= 1500)
	{
		seg5&=0x7F;seg5|=0x80;//显示方块
		seg6&=0x7F;seg6|=0x00;//不显示园
	}
	else if(Set_Speed > 1500)
	{
		seg5&=0x7F;seg5|=0x00;//不显示方块
		seg6&=0x7F;seg6|=0x00;//不显示园
	}	
	
	/*************rpm*********************/
	if(TimeIcn_ShowFlag == 0)//转速单位图标闪烁
	{
		seg1&=0xEF;seg1|=0x10;//显示rpm
	}
	else
	{
		seg1&=0xEF;seg1|=0x00;//不显示rpm
	}
		
	/*************时间单位图标***************/
	if(TimeIcn_ShowFlag == 0 && Set_Time >0 && Time_State == 0)//时间单位图标闪烁
	{
		if(Time_Unit)//时间单位为小时时
		{
			seg2&=0xF7;seg2|=0x08;//显示H
		}
		else//时间单位为秒时
		{
			seg3&=0xF7;seg3|=0x08;//显示min
		}
	}
	else
	{
		seg2&=0xF7;seg2|=0x00;//不显示时间单位图标
		seg3&=0xF7;seg3|=0x00;//不显示时间单位图标
	}
	
	/*************运行模式图标***************/	
	if(Speed_Mode == 0)//混动模式图标
	{
		seg1&=0x3F;seg1|=0xC0;//显示+TOUCH
		seg4&=0x7F;seg4|=0x80;//显示RUN
	}
	else//常动模式图标
	{
		seg1&=0x3F;seg1|=0x00;//不显示+TOUCH
		seg4&=0x7F;seg4|=0x80;//不显示RUN
	}
	
	Write_Addr_Dat_N(0,seg1,1);//SEG9
	Write_Addr_Dat_N(1,seg2,1);//SEG10
	Write_Addr_Dat_N(3,seg3,1);//SEG11
	Write_Addr_Dat_N(5,seg4,1);//SEG12
	Write_Addr_Dat_N(7,seg5,1);//SEG13
	Write_Addr_Dat_N(9,seg6,1);//SEG14
}

/*
*****************************************************************
 * 函数原型： void Deal_Speed(void)
 * 功    能： 速度显示处理
*****************************************************************
*/
uint16_t Rel_Val;
void Deal_Speed(void)
{
	if(Rel_Speed >= 2200)
		Rel_Val = 3000-(2600 - Rel_Speed)*2;
	else
		Rel_Val = Rel_Speed;
    /**********SpeedL1_ADD_Mode**********/
    if(sys.Run_Status == 1)//启动的情况下
    {
        if(Speed_ADDMode == 0)//在电机控制中，速度未处理
        {
            if(Ctrl_Speed > Rel_Val)//控制速度大于实际速度
            {
                Speed_New =0;//现在的速度清零
                Speed_Last = 0;//之前的速度清零
                Speed_ADDMode = 1;//进入加速模式下
            }
            else if(Ctrl_Speed <= Display_Speed)//控制速度小于显示速度
            {
                Speed_New=0;//现在的速度清零
                Speed_Last = Rel_Val;//之前的速度等于当前显示速度
                Speed_ADDMode = 2;//进入减速模式下
            }
        }
        if(Speed_ADDMode==1)//在进入加速模式下
        { 
			if(Rel_Val >= Ctrl_Speed)//实际速度大于等于控制速度
			{
				Speed_ADDMode = 3;//进入稳定模式
				return;
			}
			Speed_New = Rel_Val;//记录当前速度
			if(Speed_New > Speed_Last)//当前速度大于上一次速度
				Display_Speed = Speed_New;//显示当前速度
			else//当前速度小于上一次速度
			{
				Display_Speed = Speed_Last;//显示上一次速度，不让速度小于当前速度。呈现攀升速度的现象
				Speed_New = Speed_Last;//将上一次速度赋值给当前速度
			}
			Speed_Last = Speed_New;//将当前速度保存 				
        }
        else if(Speed_ADDMode == 2)//速度下降模式下
        {
			if(Rel_Val <= Ctrl_Speed)//实际速度小于等于控制速度
			{
				Speed_ADDMode = 3;//稳定模式
				return;
			}
			Speed_New = Rel_Val;//记录当前速度
			if(Speed_New < Speed_Last)//当前速度小于上一次速度
				Display_Speed = Speed_New;//显示当前速度
			else//当前速度大于上一次速度
			{
				Display_Speed = Speed_Last;//显示上一次速度，不让速度大于当前速度。呈现下降速度的现象
				Speed_New = Speed_Last;//将上一次速度赋值给当前速度
			}
			Speed_Last = Speed_New;//将当前速度保存
        }
        else if(Speed_ADDMode == 3)//速度稳定模式下
        {
            Display_Speed = Ctrl_Speed;//显示控制速度
        }
		else if(Speed_ADDMode == 4)//速度下降停止模式下
        {
            Speed_New = Rel_Val;//记录当前速度
            if(Speed_New < Speed_Last)//当前速度小于上一次速度
                Display_Speed = Speed_New;//显示当前速度
            else//当前速度大于上一次速度
            {
                Display_Speed = Speed_Last;//显示上一次速度，不让速度大于当前速度。呈现下降速度的现象
                Speed_New = Speed_Last;//将上一次速度赋值给当前速度
            }
            Speed_Last = Speed_New;//将当前速度保存
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
            Display_Time = Set_Time; //显示设定时间 
        }            
        else//在不设置模式下
        {
            Deal_Speed();//速度显示处理 
            Display_Time = Ctrl_Time+59;//显示实际时间
        }
    }
	Display(Display_Speed,Display_Time);//显示屏幕
}
#elif(Type == 0)
/**********全局变量声明******/
float Twinkle_Time;//闪烁时间

/**********局部变量声明******/
uint8_t Time_ShowFlag,Speed_ShowFlag;//时间、速度显示的标志位 0:常亮 1：熄灭
uint8_t TimeIcn_ShowFlag;//时间图标闪烁
uint8_t Tab[] = {0x5F,0x06,0x3D,0x2F,0x66,0x6B,0x7B,0x0E,0x7F,0x6F};//0·9

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
        Time_Unit=1;//单位变成分
    else
        Time_Unit=0;//不然就是秒
	
	if(Time_Unit == 1)//时间单位为分钟时
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
		if(Set_Time > 0 && Time_State==0)//设置时间大于零时显示时间
		{
			/***********set_time第一位***********/
			seg4&=0x80;seg4|=Tab[SM];//数字	
		
			/***********set_time第二位***********/
			seg&=0x80;seg|=Tab[M];//数字		
		}
		else//设置时间小于等于0时显示“-- --”
		{
			seg4&=0x80;seg4|=0x20;//"-"
			seg&=0x80;seg|=0x20;//"-"
		}	
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
		seg4&=0x7F;seg4|=0x80;//显示rpm
	}
	else
	{
		seg4&=0x7F;seg4|=0x00;//不显示rpm
	}
		
	
	/*************时间单位图标***************/
	if(TimeIcn_ShowFlag == 0 && Set_Time >0 && Time_State == 0)//时间单位图标闪烁
	{
		if(Time_Unit)//时间单位为分钟时
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
	
	/*************运行模式图标***************/	
	if(Speed_Mode == 0)//点动模式图标
	{
		seg5&=0xF9;seg5|=0x06;//显示上下面的三角形
	}
	else//常动模式图标
	{
		seg5&=0xF9;seg5|=0x04;//显示下面的三角形
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
 * 函数原型： void Deal_Speed(void)
 * 功    能： 速度显示处理
*****************************************************************
*/
uint16_t Rel_Val;
void Deal_Speed(void)
{
	if(Rel_Speed >= 2200)
		Rel_Val = 3000-(2600 - Rel_Speed)*2;
	else
		Rel_Val = Rel_Speed;
    /**********SpeedL1_ADD_Mode**********/
    if(sys.Run_Status == 1)//启动的情况下
    {
        if(Speed_ADDMode == 0)//在电机控制中，速度未处理
        {
            if(Ctrl_Speed > Rel_Val)//控制速度大于实际速度
            {
                Speed_New =0;//现在的速度清零
                Speed_Last = 0;//之前的速度清零
                Speed_ADDMode = 1;//进入加速模式下
            }
            else if(Ctrl_Speed <= Display_Speed)//控制速度小于显示速度
            {
                Speed_New=0;//现在的速度清零
                Speed_Last = Rel_Val;//之前的速度等于当前显示速度
                Speed_ADDMode = 2;//进入减速模式下
            }
        }
        if(Speed_ADDMode==1)//在进入加速模式下
        { 
			if(Rel_Val >= Ctrl_Speed)//实际速度大于等于控制速度
			{
				Speed_ADDMode = 3;//进入稳定模式
				return;
			}
			Speed_New = Rel_Val;//记录当前速度
			if(Speed_New > Speed_Last)//当前速度大于上一次速度
				Display_Speed = Speed_New;//显示当前速度
			else//当前速度小于上一次速度
			{
				Display_Speed = Speed_Last;//显示上一次速度，不让速度小于当前速度。呈现攀升速度的现象
				Speed_New = Speed_Last;//将上一次速度赋值给当前速度
			}
			Speed_Last = Speed_New;//将当前速度保存 				
        }
        else if(Speed_ADDMode == 2)//速度下降模式下
        {
			if(Rel_Val <= Ctrl_Speed)//实际速度小于等于控制速度
			{
				Speed_ADDMode = 3;//稳定模式
				return;
			}
			Speed_New = Rel_Val;//记录当前速度
			if(Speed_New < Speed_Last)//当前速度小于上一次速度
				Display_Speed = Speed_New;//显示当前速度
			else//当前速度大于上一次速度
			{
				Display_Speed = Speed_Last;//显示上一次速度，不让速度大于当前速度。呈现下降速度的现象
				Speed_New = Speed_Last;//将上一次速度赋值给当前速度
			}
			Speed_Last = Speed_New;//将当前速度保存
        }
        else if(Speed_ADDMode == 3)//速度稳定模式下
        {
            Display_Speed = Ctrl_Speed;//显示控制速度
        }
		else if(Speed_ADDMode == 4)//速度下降停止模式下
        {
            Speed_New = Rel_Val;//记录当前速度
            if(Speed_New < Speed_Last)//当前速度小于上一次速度
                Display_Speed = Speed_New;//显示当前速度
            else//当前速度大于上一次速度
            {
                Display_Speed = Speed_Last;//显示上一次速度，不让速度大于当前速度。呈现下降速度的现象
                Speed_New = Speed_Last;//将上一次速度赋值给当前速度
            }
            Speed_Last = Speed_New;//将当前速度保存
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
            Display_Time = Ctrl_Time;//显示实际时间
        }
        else if(sys.SetMode_Option == 2)//在设置时间模式下
        {
            Deal_Speed();//速度显示处理
            Display_Time = Set_Time; //显示设定时间 
        }            
        else//在不设置模式下
        {
            Deal_Speed();//速度显示处理 
            Display_Time = Ctrl_Time;//显示实际时间
        }
    }
	Display(Display_Speed/10,Display_Time);//显示屏幕
}

#endif
