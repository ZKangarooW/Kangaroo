#include "Show.h"
#if(Type)
/**********全局变量声明******/
uint32_t Twinkle_Time;//闪烁时间

/**********局部变量声明******/
uint8_t Speed_ShowFlag,Time_ShowFlag,Run_ShowFlag;//速度、时间、运行显示的标志位 0:常亮 1：熄灭
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
	if(sys.Run_Status == 1)
        Run_ShowFlag = ~Run_ShowFlag;//运行闪烁
    else
        Run_ShowFlag = 0;
    if(SetMode_Option == 0 || Key_Status)//如果没在设置选项中，则都点亮，不闪烁
    {
        Speed_ShowFlag = 0;//常亮
        Time_ShowFlag = 0;//常亮
        return;
    }
    if(Twinkle_Time && Key_Status==0)//闪烁和没有操作旋钮时
    {
        Twinkle_Time -= dT;//闪烁计时
        if(SetMode_Option == 1)//设置速度
        {
            Speed_ShowFlag = ~Speed_ShowFlag;//速度闪烁
            Time_ShowFlag = 0;//时间常亮
        }
        else if(SetMode_Option == 2)//设置温度
        {
            Speed_ShowFlag = 0;//速度常亮
            Time_ShowFlag = ~Time_ShowFlag;//时间闪烁
        }
        if(Twinkle_Time <= 0)//如果闪烁结束
        {
            SetMode_Option = 0;//模式选择清零
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
			seg6&=0x80;seg6|=Tab1[Val];//数字	
		}
		else
		{
			seg6&=0x80;seg6|=0x00;//不显示
		}
		/***********speed十位***********/
		if(speed > 9)//大于9时
		{
			Val=speed/10;//取出十位
			if(speed > 99)//大于99时
				Val=Val%10;//取出十位
			seg5&=0x80;seg5|=Tab1[Val];//数字	
		}
		else
		{
			seg5&=0x80;seg5|=0x00;//不显示
		}
		
		/***********speed个位***********/
		Val=speed%10;//取出个位
		seg4&=0xC0;seg4|=Tab1[Val];//数字
	}
	else//不显示
	{
		seg1&=0xC0;seg1|=0x00;//不显示
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
		if(Set_Time > 0)//设置时间大于零时显示时间
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
//	if(Set_Speed <= 800)
//	{
//		seg5&=0x7F;seg5|=0x80;//显示方块
//		seg6&=0x7F;seg6|=0x80;//显示园
//	}
//	else if(Set_Speed > 800 && Set_Speed <= 1500)
//	{
//		seg5&=0x7F;seg5|=0x80;//显示方块
//		seg6&=0x7F;seg6|=0x00;//不显示园
//	}
//	else if(Set_Speed > 1500)
//	{
//		seg5&=0x7F;seg5|=0x00;//不显示方块
//		seg6&=0x7F;seg6|=0x00;//不显示园
//	}	
	
	/*************rpm*********************/
	if(Run_ShowFlag == 0)//转速单位图标闪烁
	{
		seg1&=0xEF;seg1|=0x10;//显示rpm
	}
	else
	{
		seg1&=0xEF;seg1|=0x00;//不显示rpm
	}
		
	/*************时间单位图标***************/
	if(Run_ShowFlag == 0 && Set_Time >0)//时间单位图标闪烁
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
//	if(Speed_Mode == 0)//混动模式图标
//	{
//		seg1&=0x3F;seg1|=0xC0;//显示+TOUCH
//		seg4&=0x7F;seg4|=0x80;//显示RUN
//	}
//	else//常动模式图标
//	{
//		seg1&=0x3F;seg1|=0x00;//不显示+TOUCH
//		seg4&=0x7F;seg4|=0x80;//不显示RUN
//	}
	
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
	/**********SpeedL1_ADD_Mode**********/
    if(sys.Run_Status == 1)//启动的情况下
    {
        if(Speed_ADDMode == 0)//在电机控制中，速度未处理
        {
            if(Ctrl_Speed >= Display_Speed)//控制速度大于实际速度
            {
                Speed_New =0;//现在的速度清零
                Speed_Last = 0;//之前的速度清零
                Speed_ADDMode = 1;//进入加速模式下
            }
            else if(Ctrl_Speed < Display_Speed)//控制速度小于实际速度
            {
                Speed_New=0;//现在的速度清零
                Speed_Last = Display_Speed;//之前的速度等于当前显示速度
                Speed_ADDMode = 2;//进入减速模式下
            }
        }
        if(Speed_ADDMode==1)//在进入加速模式下
        { 
            if(Rel_Speed >= Ctrl_Speed)//实际速度大于等于控制速度
            {
                Speed_ADDMode = 3;//进入稳定模式
                return;
            }
            Speed_New = Rel_Speed;//记录当前速度
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
            if(Rel_Speed <= Ctrl_Speed)//实际速度小于等于控制速度
            {
                Speed_ADDMode = 3;//稳定模式
                return;
            }
            Speed_New = Rel_Speed;//记录当前速度
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
        if(SetMode_Option == 1)//在设置速度模式下
        {
            Display_Speed  = Set_Speed;//显示设定速度
            Display_Time = Rel_Time+59;//显示实际时间
        }
        else if(SetMode_Option == 2)//在设置时间模式下
        {
            Deal_Speed();
            Display_Time = Set_Time; //显示设定时间 
        }            
        else//在不设置模式下
        {
            Deal_Speed();       
            Display_Time = Rel_Time+59;//显示实际时间
        }
    }
	Display(Display_Speed,Display_Time);//显示屏幕
}
#elif(Type == 0)
/**********全局变量声明******/
uint32_t Twinkle_Time;//闪烁时间

/**********局部变量声明******/
uint8_t  LCD_ADD[] = {0x5f, 0x06, 0x3d, 0x2f, 0x66, 0x6b, 0x7b, 0x0e, 0x7f, 0x6f};
uint8_t Speed_ShowFlag,Time_ShowFlag,Run_ShowFlag;//速度、时间、运行显示的标志位 0:常亮 1：熄灭

/*
*****************************************************************
 * 函数原型： void Check_ShowFlag(uint16_t dT)
 * 功    能： 闪烁检测
 * 输    入:  dT:执行周期
 * 参    数： uint16_t dT
*****************************************************************
*/
void Check_ShowFlag(uint16_t dT)
{
    if(sys.Run_Status == 1)
        Run_ShowFlag = ~Run_ShowFlag;//运行闪烁
    else
        Run_ShowFlag = 0;
    if(SetMode_Option == 0 || Key_Status)//如果没在设置选项中，则都点亮，不闪烁
    {
        Speed_ShowFlag = 0;//常亮
        Time_ShowFlag = 0;//常亮
        return;
    }
    if(Twinkle_Time && Key_Status==0)//闪烁和没有操作旋钮时
    {
        Twinkle_Time -= dT;//闪烁计时
        if(SetMode_Option == 1)//设置速度
        {
            Speed_ShowFlag = ~Speed_ShowFlag;//速度闪烁
            Time_ShowFlag = 0;//时间常亮
        }
        else if(SetMode_Option == 2)//设置温度
        {
            Speed_ShowFlag = 0;//速度常亮
            Time_ShowFlag = ~Time_ShowFlag;//时间闪烁
        }
        if(Twinkle_Time == 0)//如果闪烁结束
        {
            SetMode_Option = 0;//模式选择清零
        }
    }
}

/*
*****************************************************************
 * 函数原型： void DiaPlay_Speed(uint8_t speed)
 * 功    能： 显示速度
 * 输    入:  speed ：速度
 * 参    数： uint8_t speed
*****************************************************************
*/
void DiaPlay_Speed(uint8_t speed)
{
	uint8_t Val;//用于十个取出来的数字
    uint8_t seg2,seg4;
    seg2 = 0; seg4 = 0;
	Val = speed / 10;//取出十位
    seg2 = LCD_ADD[Val];
	Val = speed % 10;//取出个位数
    seg4 = LCD_ADD[Val];
    
    if(Speed_ShowFlag > 1)//闪烁速度
    {
        seg2 = 0x00;seg4 = 0x00;      
    }
    
    Write_Addr_Dat_N(0x02, seg2, 1);
	Write_Addr_Dat_N(0x04, seg4, 1);
}

/*
*****************************************************************
 * 函数原型： void DisPlay_Time(uint16_t time)
 * 功    能： 显示时间
 * 输    入:  time ：时间
 * 参    数： uint16_t time
*****************************************************************
*/
void DisPlay_Time(uint16_t time)
{
	uint8_t T1,T2;//用于显示时间
	uint8_t seg6,seg8,seg10;
    seg6 = 0; seg8 = 0; seg10 = 0;
    
	if(time > 59)//大于59秒时
		Time_Unit = 1;//显示分钟图标
	else
		Time_Unit = 0;//显示秒钟图标

	if(Time_Unit == 1)//单位是分钟时，最大5940
	{
		T1 = time/60/10;//计算十位的分钟数
		T2 = time/60%10;//计算个位的分钟数
        seg8&=0xF6;seg8|=0x08;//显示"min"图标    
	}
	else
	{
		T1 = time/10;//计算十位的秒钟数
		T2 = time%10;//计算个位的秒钟数
        seg8&=0xF6;seg8|=0x01;//显示"sec"图标            
	}
	switch(T2)
    {
        case 0:seg8&=0x8F;seg10&=0x0F;seg8|=0x50;seg10|=0xF0;//数字0
            break;
        case 1:seg8&=0x8F;seg10&=0x0F;seg8|=0x00;seg10|=0x60;//数字1
            break;
        case 2:seg8&=0x8F;seg10&=0x0F;seg8|=0x30;seg10|=0xD0;//数字2
            break;
        case 3:seg8&=0x8F;seg10&=0x0F;seg8|=0x20;seg10|=0xF0;//数字3
            break;	
        case 4:seg8&=0x8F;seg10&=0x0F;seg8|=0x60;seg10|=0x60;//数字4
            break;	
        case 5:seg8&=0x8F;seg10&=0x0F;seg8|=0x60;seg10|=0xB0;//数字5
            break;	
        case 6:seg8&=0x8F;seg10&=0x0F;seg8|=0x70;seg10|=0xB0;//数字6
            break;	
        case 7:seg8&=0x8F;seg10&=0x0F;seg8|=0x00;seg10|=0xE0;//数字7
            break;	
        case 8:seg8&=0x8F;seg10&=0x0F;seg8|=0x70;seg10|=0xF0;//数字8
            break;	
        case 9:seg8&=0x8F;seg10&=0x0F;seg8|=0x60;seg10|=0xF0;//数字9
            break;
        default:
            break;
    }  
    seg6 = LCD_ADD[T1];

    if(Time_State == 0)//显示"--"
    {
        seg6 &= 0X80; seg6 |= 0X20; seg8 &= 0X00; seg8 |= 0X20; seg10 &= 0X00; seg10 |= 0X00;    
    }
    
    if(Time_ShowFlag > 1)//闪烁时间
    {
        seg6 &= 0X80; seg6 |= 0X00; seg8 &= 0X09; seg8 |= 0X00; seg10 &= 0X00; seg10 |= 0X00;       
    }
    if(Run_ShowFlag == 0)//运行闪烁
    {
        seg6&=0x7F; seg6|=0x80;//显示"rpm
    }
    else
    {
        seg6&=0x7F; seg6|=0x00;//不显示"rpm
    }
    Write_Addr_Dat_N(0x06, seg6, 1);
	Write_Addr_Dat_N(0x08, seg8, 1);
    Write_Addr_Dat_N(0x0A, seg10, 1);
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
            if(Ctrl_Speed >= Display_Speed)//控制速度大于实际速度
            {
                Speed_New =0;//现在的速度清零
                Speed_Last = 0;//之前的速度清零
                Speed_ADDMode = 1;//进入加速模式下
            }
            else if(Ctrl_Speed < Display_Speed)//控制速度小于实际速度
            {
                Speed_New=0;//现在的速度清零
                Speed_Last = Display_Speed;//之前的速度等于当前显示速度
                Speed_ADDMode = 2;//进入减速模式下
            }
        }
        if(Speed_ADDMode==1)//在进入加速模式下
        { 
            if(Rel_Speed >= Ctrl_Speed)//实际速度大于等于控制速度
            {
                Speed_ADDMode = 3;//进入稳定模式
                return;
            }
            Speed_New = Rel_Speed;//记录当前速度
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
            if(Rel_Speed <= Ctrl_Speed)//实际速度小于等于控制速度
            {
                Speed_ADDMode = 3;//稳定模式
                return;
            }
            Speed_New = Rel_Speed;//记录当前速度
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
        if(SetMode_Option == 1)//在设置速度模式下
        {
            Display_Speed  = Set_Speed;//显示设定速度
            Display_Time = Rel_Time;//显示实际时间
        }
        else if(SetMode_Option == 2)//在设置时间模式下
        {
            Deal_Speed();
            Display_Time = Set_Time; //显示设定时间 
        }            
        else//在不设置模式下
        {
            Deal_Speed();       
            Display_Time = Rel_Time;//显示实际时间
        }
    }
	DiaPlay_Speed(Display_Speed);
    DisPlay_Time(Display_Time);
}
#endif
