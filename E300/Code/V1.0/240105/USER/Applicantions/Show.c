#include "Show.h"

/**********全局变量声明******/
float Temp_Twinkle_Time,Time_Twinkle_Time;//温度闪烁时间和时间闪烁时间

/**********局部变量声明******/
uint8_t TempIcn_ShowFlag,TimeIcn_ShowFlag;//温度图标闪烁和时间图标闪烁
uint8_t Temp_ShowFlag,Time_ShowFlag;//温度、时间显示的标志位 0:常亮 1：熄灭
uint8_t Tab[] = {0x77,0x24,0x5D,0x6D,0x2E,0x6B,0x7B,0x25,0x7F,0x6F};//0·9
uint8_t Tab1[] = {0x77,0x12,0x5D,0x5B,0x3A,0x6B,0x6F,0x52,0x7F,0x7B};//0·9
uint8_t Tab2[] = {0xEE,0x24,0xBA,0xB6,0x74,0xD6,0xDE,0xA4,0xFE,0xF6};//0·9

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
			TempIcn_ShowFlag = ~TempIcn_ShowFlag;//转速图标闪烁;
			if(Time.Rel && (TempIcn_ShowFlag != TimeIcn_ShowFlag) && sys.Time_Status)
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
		TempIcn_ShowFlag = 0;//不显示速度图标
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
	if(Temp_Twinkle_Time && !EC11A[0].EC11A_Knob)//速度闪烁和没有操作按键时
    {
		Speed_T += dT;
		if(Speed_T >= 0.5f)
		{
			Temp_Twinkle_Time -= 0.5;//闪烁计时
			Temp_ShowFlag = ~Temp_ShowFlag;//速度闪烁
			if(Temp_Twinkle_Time == 0)//如果闪烁结束
			{
				SpeedSet_Flag = 1;//进入速度设定
				Beep_Time = 0.1;//蜂鸣器响0.1S
			} 
			Speed_T = 0;		
		}			
    }
	else
	{
		Temp_ShowFlag = 0;//常亮
		Speed_T = 0;
	}
	
	if(Time_Twinkle_Time && !EC11A[1].EC11A_Knob)//时间闪烁和没有操作按键时
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
 * 函数原型：void Display_RelVal(uint16_t val1, uint32_t val2, uint16_t val3)
 * 功    能：显示实际的值
 * 输    入: val1：显示左边的数值;val2：显示中间的数值;val3：显示右边的数值
 * 参    数：uint16_t val1, uint32_t val2, uint16_t val3
*****************************************************************
*/
void Display_RelVal(uint16_t val1, uint32_t val2, uint16_t val3)
{
    uint8_t seg1,seg2,seg3,seg4,seg5,seg6,seg7,seg8;
    seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;seg7=0;seg8=0;
	uint16_t Val;//用于百十个取出来的数字

    /*****************屏幕设定左边数值******************/
    /***********val1百位***********/
    if(val1 > 999)//大于999时
    {
        Val=val1/1000;//除以1000
        if(val1 > 9)//如果大于9，那么说明除以1000后是两位数
            Val=Val%10;//除以10取余，得出千位上的数
        seg1&=0x80;seg1|=Tab[Val];
    }
    else
    {
        seg1&=0x80;seg1|=0x00;
    }

    /***********val1十位***********/
    if(val1 > 99)//大于99时
    {
        Val=val1/100;//除以100
        if(val1 > 9)//如果大于9，那么说明除以100后是两位数
            Val=Val%10;//除以10取余，得出百位上的数
        seg2&=0x80;seg2|=Tab[Val];
    }
    else
    {
        seg2&=0x80;seg2|=0x00;
    }

    /***********val1个位***********/
    if(val1 > 9)//大于9时
    {
        Val=val1/10;//除以10
        if(val1 > 9)//如果大于9，那么说明除以10后是两位数
            Val=Val%10;//除以10取余，得出十位上的数
        seg3&=0x80;seg3|=Tab[Val];
    }
    else
    {
        seg3&=0x80;seg3|=Tab[0];
    }

    /***********val1小数位***********/
    Val=val1%10;//取出个位
    seg4&=0x80;seg4|=Tab[Val];

    uint8_t SH,H,SM,M;//时间的单位取值
    if(val2 && Time.Set != 0)
    {
        if(Time.Set > 3599)
        {
            SH=val2/3600/10;//计算十位单位的小时数
            H=val2/3600%10;//计算个位单位的小时数
            SM=val2%3600/60/10;//计算十分位单位的分钟数
            M=val2%3600/60%10;//计算个分位单位的分钟数
        }
        else
        {
            if(Time.Set > 59)
            {
                SH=val2/60/10;//计算十位单位的小时数
                H=val2/60%10;//计算个位单位的小时数
                SM=val2%60/10;//计算十分位单位的分钟数
                M=val2%60%10;//计算个分位单位的分钟数
            }
            else
            {
                SH = 0;
                H  = 0;
                SM = val2%60/10;
                M  = val2%60%10;
            }
        }
        
        seg5&=0x80;seg5|=Tab[SH];
        seg6&=0x80;seg6|=Tab[H];
        seg7&=0x80;seg7|=Tab[SM];
        seg8&=0x80;seg8|=Tab[M];
    }
    else
    {
        if(Beep_Flash)
        {
            if(Time.Set > 3599)
            {
                SH=val2/3600/10;//计算十位单位的小时数
                H=val2/3600%10;//计算个位单位的小时数
                SM=val2%3600/60/10;//计算十分位单位的分钟数
                M=val2%3600/60%10;//计算个分位单位的分钟数
            }
            else
            {
                if(Time.Set > 59)
                {
                    SH=val2/60/10;//计算十位单位的小时数
                    H=val2/60%10;//计算个位单位的小时数
                    SM=val2%60/10;//计算十分位单位的分钟数
                    M=val2%60%10;//计算个分位单位的分钟数
                }
                else
                {
                    SH = 0;
                    H  = 0;
                    SM = val2%60/10;
                    M  = val2%60%10;
                }
            }
        
            seg5&=0x80;seg5|=Tab[SH];
            seg6&=0x80;seg6|=Tab[H];
            seg7&=0x80;seg7|=Tab[SM];
            seg8&=0x80;seg8|=Tab[M];
        }
        else
        {
            seg5&=0x80;seg5|=0x08;
            seg6&=0x80;seg6|=0x08;
            seg7&=0x80;seg7|=0x08;
            seg8&=0x80;seg8|=0x08;
        }
    }
    
    /*****************图标******************/
    seg3&=0x7F;seg3|=0x80;//实际温度的小数点
    seg1&=0x7F;seg1|=0x80;//设置温度的℃符号

    
    if(TempIcn_ShowFlag)
    {
        seg4&=0x7F;seg4|=0x00;//显示加热图标
    }
    else
    {
        seg4&=0x7F;seg4|=0x80;//不显示加热图标
    }
    
    if(TimeIcn_ShowFlag)
    {
        seg7&=0x7F;seg7|=0x00;//实际温度的小数点
    }
    else
    {
        seg7&=0x7F;seg7|=0x80;//不显示实际温度的小数点
    }

    Write_Addr_Dat_N(0,seg1,1);
    Write_Addr_Dat_N(2,seg2,1);
    Write_Addr_Dat_N(4,seg3,1);
    Write_Addr_Dat_N(6,seg4,1);
    Write_Addr_Dat_N(8,seg5,1);
    Write_Addr_Dat_N(10,seg6,1);
    Write_Addr_Dat_N(12,seg7,1);
    Write_Addr_Dat_N(14,seg8,1);
}

/*
*****************************************************************
 * 函数原型：void Display_SetVal(uint16_t val1, uint32_t val2, uint16_t val3)
 * 功    能：显示设定的值
 * 输    入: val1：显示左边的数值;val2：显示右边的数值;val3：显示右边的数值
 * 参    数：uint16_t val1, uint32_t val2, uint16_t val3
*****************************************************************
*/
void Display_SetVal(uint16_t val1, uint32_t val2, uint16_t val3)
{
    uint8_t seg1,seg2,seg3,seg4,seg5,seg6,seg7,seg8,seg9,seg10,seg11,seg12;
    seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;seg7=0;seg8=0;seg9=0;seg10=0;seg11=0;seg12=0;
	uint16_t Val;//用于百十个取出来的数字
    uint8_t SH,H,SM,M;//时间的单位取值

    /*****************屏幕设定左边数值******************/
    /***********val1百位***********/
    if(!Temp_ShowFlag)
    {
		if(val1 > 999)//大于999时
		{
			Val=val1/1000;//除以1000
			if(val1 > 9)//如果大于9，那么说明除以1000后是两位数
				Val=Val%10;//除以10取余，得出千位上的数
			seg1&=0x80;seg1|=Tab2[Val];
		}
		else
		{
			seg1&=0x80;seg1|=0x00;
		}

		/***********val1十位***********/
		if(val1 > 99)//大于99时
		{
			Val=val1/100;//除以100
			if(val1 > 9)//如果大于9，那么说明除以100后是两位数
				Val=Val%10;//除以10取余，得出百位上的数
			seg2&=0x80;seg2|=Tab2[Val];
		}
		else
		{
			seg2&=0x80;seg2|=0x00;
		}

		
		/***********val1个位***********/
		if(val1 > 9)//大于9时
		{
			Val=val1/10;//除以10
			if(val1 > 9)//如果大于9，那么说明除以10后是两位数
				Val=Val%10;//除以10取余，得出十位上的数
			seg3&=0x80;seg3|=Tab2[Val];
		}
		else
		{
			seg3&=0x80;seg3|=Tab2[0];
		}
		
		/***********val1小数位***********/
		Val=val1%10;//取出个位
		seg4&=0x01;seg4|=Tab2[Val];
    }
    else//闪烁不显示
    {
        seg1&=0x10;seg1|=0x00;
        seg2&=0x10;seg2|=0x00;
        seg3&=0x10;seg3|=0x00;
        seg4&=0x10;seg4|=0x00;
    } 

    /*****************屏幕设定右边数值******************/
    if(!Time_ShowFlag)
    {
        if(val2)
        {
            if(Time.Set > 3599)
            {
                SH=val2/3600/10;//计算十位单位的小时数
                H=val2/3600%10;//计算个位单位的小时数
                SM=val2%3600/60/10;//计算十分位单位的分钟数
                M=val2%3600/60%10;//计算个分位单位的分钟数
            }
            else
            {
                if(Time.Set > 59)
                {
                    SH=val2/60/10;//计算十位单位的小时数
                    H=val2/60%10;//计算个位单位的小时数
                    SM=val2%60/10;//计算十分位单位的分钟数
                    M=val2%60%10;//计算个分位单位的分钟数
                }
                else
                {
                    SH = 0;
                    H  = 0;
                    SM = val2%60/10;
                    M  = val2%60%10;
                }
            }
            
            seg9&=0x80;seg9|=Tab1[SH];
            seg10&=0x80;seg10|=Tab1[H];
            seg11&=0x80;seg11|=Tab1[SM];
            seg12&=0x80;seg12|=Tab1[M];
        }
        else
        {
            seg9&=0x80;seg9|=0x08;//显示‘-’
            seg10&=0x80;seg10|=0x08;//显示‘-’
            seg11&=0x80;seg11|=0x08;//显示‘-’
            seg12&=0x80;seg12|=0x08;//显示‘-’
        }
    }
    else
    {
        seg9&=0x80;seg9|=0x00;
        seg10&=0x80;seg10|=0x00;
        seg11&=0x80;seg11|=0x00;
        seg12&=0x80;seg12|=0x00;
    }
    
    /*****************图标******************/
    seg3&=0xFE;seg3|=0x01;//温度小数点
    seg10&=0x7f;seg10|=0x80;;//设定时间冒号
    
    /*****************时间单位******************/
    if(Time.Set > 3599)
    {
        seg12&=0x7f;seg12|=0x80;//显示min
    }
    else
    {
        seg11&=0x7f;seg11|=0x80;//显示sec
    }
   
    Write_Addr_Dat_N(38,seg1,1);
    Write_Addr_Dat_N(36,seg2,1);
    Write_Addr_Dat_N(34,seg3,1);
    Write_Addr_Dat_N(32,seg4,1);
    Write_Addr_Dat_N(30,seg5,1);
    Write_Addr_Dat_N(28,seg6,1);
    Write_Addr_Dat_N(26,seg7,1);
    Write_Addr_Dat_N(24,seg8,1);
    Write_Addr_Dat_N(22,seg9,1);
    Write_Addr_Dat_N(20,seg10,1);
    Write_Addr_Dat_N(18,seg11,1);
    Write_Addr_Dat_N(16,seg12,1);
}

/*
*****************************************************************
 * 函数原型：void Deal_Temp(void)
 * 功    能：温度显示处理
*****************************************************************
*/
void Deal_Temp(void)
{
	if(sys.Run_Status == 0)//没启动的情况下
    {
		Temp.ADDMode = 0;
		Temp.Display_Rel = Temp.Rel;      
    }
    else//启动的情况下
    {
        if(Temp.ADDMode == 0)//判断数据处理显示
        {     
		   if(Temp.Ctrl > Temp.Display_Rel)//设定温度大于显示温度
		   { 
				Temp.ADDMode = 1;//进入加热模式下
				Temp.New = 0;//将之前的记入值清零
				Temp.Last = 0;//将之前的记入值清零  
			}
		   else
		   {
				Temp.ADDMode = 2;//进入降温模式下
				Temp.New = 0;//将之前的记入值清零
				Temp.Last = Temp.Rel;//将之前的记入值清零  
			}
        }
        if(Temp.ADDMode == 1)//在加热模式下
        {
            Temp.New = Temp.Rel;//记录当前温度
            if(Temp.New > Temp.Display_Rel && Temp.Display_Rel <= Temp.Ctrl)
                Temp.Display_Rel = Temp.New;
            else//当前温度小于上一次温度
            {
                Temp.Display_Rel = Temp.Display_Rel;
            }
            if(Temp.Display_Rel >= Temp.Ctrl)
            {
                Temp.ADDMode = 3;//进入稳定模式
                Temp_Val.Integral = 0;//积分清零
            }
        }
		else if(Temp.ADDMode == 2)//降温模式下
        {
            Temp.New = Temp.Rel;//记录当前温度
            if(Temp.New < Temp.Display_Rel && Temp.Display_Rel >= Temp.Ctrl)//当前温度小于上一次温度
                Temp.Display_Rel = Temp.New;//显示当前温度
            else//当前温度大于上一次温度
            {
                Temp.Display_Rel = Temp.Last;//显示上一次温度，不让温度大于当前温度。呈现下降温度的现象
            }
            if(Temp.Display_Rel <= Temp.Ctrl)
            {
                Temp.ADDMode = 3;//进入稳定模式
                Temp_Val.Integral = 0;//积分清零
            }
        }  	
        else if(Temp.ADDMode == 3)//温度稳定模式下
        {
			Temp.Display_Rel = Temp.Ctrl;//显示当前显示温度
        }   	
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
	Temp.Display_Set = Temp.Set;//显示设定温度
	Deal_Temp();//温度显示处理
    
    Time.Display_Set = Time.Set;
    Time.Display_Rel = Time.Rel;
    
	Display_RelVal(Temp.Display_Rel, Time.Display_Rel, 0);
    Display_SetVal(Temp.Display_Set, Time.Display_Set, 0);
}
