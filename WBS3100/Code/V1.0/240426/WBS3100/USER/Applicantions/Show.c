#include "Show.h"

/**********全局变量声明******/
float Twinkle_Time;//闪烁时间

/**********局部变量声明******/
uint8_t Time_ShowFlag,Speed_ShowFlag,Temp_ShowFlag;//时间、速度、温度显示的标志位 0:常亮 1：熄灭
uint8_t Protect_ShowFlag;//防干烧图标
uint8_t Tab[] = {0x77,0x24,0x5D,0x6D,0x2E,0x6B,0x7B,0x25,0x7F,0x6F};//0·9
uint8_t Tab1[] = {0x77,0x12,0x5D,0x5B,0x3A,0x6B,0x6F,0x52,0x7F,0x7B};//0·9
uint8_t Tab2[] = {0xEE,0x24,0xBA,0xB6,0x74,0xD6,0xDE,0xA4,0xFE,0xF6};//0·9

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
        Twinkle_Time = 0;//闪烁计时清零
        return;
    }
    if(Twinkle_Time && Key_Status==0)//闪烁和没有操作按键时
    {
        if(T == 0)
		{
            T += dT;
            Twinkle_Time -= 0.5f;//闪烁计时
            if(Twinkle_Time == 0)//如果闪烁结束
            {
                sys.SetMode_Option = 0;//模式选择清零
                Speed_ShowFlag = 0;//常亮
                Temp_ShowFlag = 0;//常亮
                Time_ShowFlag = 0;//常亮
            } 
            if(sys.SetMode_Option == 1)//设置温度
			{
				Speed_ShowFlag = 0;//速度常亮
				Time_ShowFlag = 0;//时间常亮
				Temp_ShowFlag = ~Temp_ShowFlag;//温度闪烁
			}
			else if(sys.SetMode_Option == 2)//设置速度
			{ 
                #if(Type == 0)
                Time_ShowFlag = ~Time_ShowFlag;//时间闪烁
				Speed_ShowFlag = 0;//速度常亮
				Temp_ShowFlag = 0;//温度常亮 
                #elif(Type == 1)
                Time_ShowFlag = 0;//时间常亮
				Speed_ShowFlag = ~Speed_ShowFlag;//速度闪烁
				Temp_ShowFlag = 0;//温度常亮
                #endif	
			}
			else if(sys.SetMode_Option == 3)//设置时间
			{
				Time_ShowFlag = ~Time_ShowFlag;//时间闪烁
				Speed_ShowFlag = 0;//速度常亮
				Temp_ShowFlag = 0;//温度常亮 			
			}
		}
		else
		{
			T += dT;
			if(T >=0.5f)
				T = 0;	
		}
    }
	else
	{
		Speed_ShowFlag = 0;//常亮
        Temp_ShowFlag = 0;//常亮
        Time_ShowFlag = 0;//常亮
		T = 0;
	}
}

/*
*****************************************************************
 * 函数原型：static void Start_SpeedRun(float dT)
 * 功    能：转速动画
 * 调    用：内部调用
*****************************************************************
*/
static void Start_SpeedRun(float dT)
{
	static float T;
	if(!sys.Run_Status || !Speed.Ctrl)
	{
		Speed.IcnStep = 0;
		T = 0;
		return;
	}
	T += dT;
	if(T >= 0.5)
	{
		Speed.IcnStep++;
		if(Speed.IcnStep > 3)
			Speed.IcnStep = 1;
		T = 0;
	}
}

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
			Temp.Icn = ~Temp.Icn;//温度图标闪烁
			if(Time.Rel && (Temp.Icn != Time.Icn) && (Temp.Set == 0 || Temp.DisplayMode == 3))
				Time.Icn = ~Time.Icn;//时间图标闪烁;
			else
			{
				Time.Icn = 0;
			}
			T = 0;
		}
	}
	else
	{
		Temp.Icn = 0;//不显示速度图标
		Time.Icn = 0;//不显示时间图标
	}
}


/*
*****************************************************************
 * 函数原型：static void Protect_Twinkle(float dT)
 * 功    能：防干烧图标闪烁
 * 调    用：内部调用
*****************************************************************
*/
static void Protect_Twinkle(float dT)
{
	static float T;
	if(Protect)
	{
		T += dT;
		if(T >= 0.5f)
		{
			Protect_ShowFlag = ~Protect_ShowFlag;//温度图标闪烁;
			T = 0;
		}
	}
	else
	{
		Protect_ShowFlag = 0;//显示温度图标
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
	Check_ShowFlag(dT);//时间图标闪烁
    Start_SpeedRun(dT);//转速动画
	Icn_Twinkle(dT);//图标闪烁
	Protect_Twinkle(dT);//防干烧图标闪烁
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
    seg4&=0x7F;seg4|=0x80;//显示温度的小数点

#if(Type == 0)
    uint8_t SH,H,SM,M;//时间的单位取值
    if(val2 && Time.Set != 0)
    {
        SH=val2/3600/10;//计算十位单位的小时数
        H=val2/3600%10;//计算个位单位的小时数
        SM=val2%3600/60/10;//计算十分位单位的分钟数
        M=val2%3600/60%10;//计算个分位单位的分钟数
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
    /*****************时间冒号******************/
    seg7&=0x7f;seg7|=0x80;
#elif(Type == 1)
    /*****************屏幕设定右边数值******************/
    /***********val3千位***********/
    if(val3 > 999)//大于999时
    {
        Val=val3/1000;//除以1000
        if(val3 > 9)//如果大于9，那么说明除以1000后是两位数
            Val=Val%10;//除以10取余，得出千位上的数
        seg5&=0x80;seg5|=Tab[Val];
    }
    else
    {
        seg5&=0x80;seg5|=0x00;
    }

    /***********val3百位***********/
    if(val3 > 99)//大于99时
    {
        Val=val3/100;//除以100
        if(val3 > 9)//如果大于9，那么说明除以100后是两位数
            Val=Val%10;//除以10取余，得出百位上的数
        seg6&=0x80;seg6|=Tab[Val];
    }
    else
    {
        seg6&=0x80;seg6|=0x00;
    }

    /***********val3十位***********/
    if(val3 > 9)//大于9时
    {
        Val=val3/10;//除以10
        if(val3 > 9)//如果大于9，那么说明除以10后是两位数
            Val=Val%10;//除以10取余，得出十位上的数
        seg7&=0x80;seg7|=Tab[Val];
    }
    else
    {
        seg7&=0x80;seg7|=0x00;
    }

    /***********val3个位***********/
    Val=val3%10;//取出个位
    seg8&=0x80;seg8|=Tab[Val];

    /*****************转速图标******************/
	switch(Speed.IcnStep)
	{
		case 0:seg5&=0x7F;seg5|=0x80;seg6&=0x7F;seg6|=0x80;seg8&=0x7F;seg8|=0x80;//常亮
			break;
		case 1:seg5&=0x7F;seg5|=0x80;seg6&=0x7F;seg6|=0x80;seg8&=0x7F;seg8|=0x00;//常亮
			break;
		case 2:seg5&=0x7F;seg5|=0x80;seg6&=0x7F;seg6|=0x00;seg8&=0x7F;seg8|=0x80;//常亮
			break;
		case 3:seg5&=0x7F;seg5|=0x00;seg6&=0x7F;seg6|=0x80;seg8&=0x7F;seg8|=0x80;//常亮
			break;
		default:
			break;
	}
#endif

    /*****************温度图标******************/
    if(!Temp.Icn || !Temp.Ctrl)
    {
        seg2&=0x7F;seg2|=0x80;seg3&=0x7F;seg3|=0x80;
    }
    else
    {
        seg2&=0x7F;seg2|=0x00;seg3&=0x7F;seg3|=0x00;
    }

    /*****************时间图标******************/
    if(!Time.Icn || !Time.Rel)
    {
        seg1&=0x7f;seg1|=0x80;
    }
    else
    {
        seg1&=0x7f;seg1|=0x00;
    }

	if(Protect)
	{
		if(Protect_ShowFlag)
		{
			seg1 = 0xFF;
			seg2 = 0xFF;
			seg3 = 0xFF;
			seg4 = 0xFF;
			seg5 = 0xFF;
			seg6 = 0xFF;
			seg7 = 0xFF;
			seg8 = 0xFF;
		}
		else
		{
			seg1 = 0x00;
			seg2 = 0x00;
			seg3 = 0x00;
			seg4 = 0x00;
			seg5 = 0x00;
			seg6 = 0x00;
			seg7 = 0x00;
			seg8 = 0x00;
		}
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
	seg3&=0x7F;seg3|=0x80;//温度单位图标
    seg4&=0xFE;seg4|=0x01;//温度小数点
    if(!Temp_ShowFlag)
    {
		if(val1)
		{
			if(val1 > 999)//大于999时
			{
				Val=val1/1000;//除以1000
				if(val1 > 9)//如果大于9，那么说明除以1000后是两位数
					Val=Val%10;//除以10取余，得出千位上的数
				seg1&=0x80;seg1|=Tab1[Val];
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
				seg2&=0x80;seg2|=Tab1[Val];
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
				seg3&=0x80;seg3|=Tab1[Val];
			}
			else
			{
				seg3&=0x80;seg3|=Tab1[0];
			}
			
			/***********val1小数位***********/
			Val=val1%10;//取出个位
			seg4&=0x01;seg4|=Tab2[Val];
		}
		else//显示“----”
		{
			seg1&=0x80;seg1|=0x08;
            seg2&=0x80;seg2|=0x08;
            seg3&=0x80;seg3|=0x08;
            seg4&=0x80;seg4|=0x10;
		}
    }
    else//闪烁不显示
    {
        seg1&=0x80;seg1|=0x00;
        seg2&=0x80;seg2|=0x00;
        seg3&=0x80;seg3|=0x00;
        seg4&=0x00;seg4|=0x00;
    } 

#if(Type == 0)
    /*****************屏幕设定右边数值******************/
    if(!Time_ShowFlag)
    {
        if(val2)
        {
            SH=val2/3600/10;//计算十位单位的小时数
            H=val2/3600%10;//计算个位单位的小时数
            SM=val2%3600/60/10;//计算十分位单位的分钟数
            M=val2%3600/60%10;//计算个分位单位的分钟数
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
    /*****************时间冒号******************/
    seg10&=0x7f;seg10|=0x80;
    /*****************时间单位******************/
    seg12&=0x7f;seg12|=0x80;//显示min

#elif(Type == 1)
    /*****************屏幕设定中间数值******************/
    if(Time.Set || sys.SetMode_Option == 3)//设定时间大于0，在设定时间和闪烁下
	{
        if(!Time_ShowFlag)
        {
            if(Time.Set)//假如设定时间大于0
            {
                SH=val2/3600/10;//计算十位单位的小时数
                H=val2/3600%10;//计算个位单位的小时数
                SM=val2%3600/60/10;//计算十分位单位的分钟数
                M=val2%3600/60%10;//计算个分位单位的分钟数
                seg5&=0x80;seg5|=Tab1[SH];
                seg6&=0x80;seg6|=Tab1[H];
                seg7&=0x80;seg7|=Tab1[SM];
                seg8&=0x80;seg8|=Tab1[M];
            }
            else
            {
                seg5&=0x80;seg5|=0x08;//显示‘-’
                seg6&=0x80;seg6|=0x08;//显示‘-’
                seg7&=0x80;seg7|=0x08;//显示‘-’
                seg8&=0x80;seg8|=0x08;//显示‘-’
            }
        }
        else//设定时间等于0
	    {
            seg5&=0x80;seg5|=0x00;
            seg6&=0x80;seg6|=0x00;
            seg7&=0x80;seg7|=0x00;
            seg8&=0x80;seg8|=0x00;
	    }
	}
	else//设定时间等于0
    {
        seg5&=0x80;seg5|=0x00;
        seg6&=0x80;seg6|=0x00;
        seg7&=0x80;seg7|=0x00;
        seg8&=0x80;seg8|=0x00;
    }

	if(Time.Set > 0 || sys.SetMode_Option == 3)
	{
		/*****************时间冒号******************/
        seg6&=0x7f;seg6|=0x80;
        /*****************时间单位******************/
        // seg8&=0x7f;seg8|=0x80;//显示sec
        seg7&=0x7f;seg7|=0x80;//显示min
	}
	else
	{
		seg6&=0x7f;seg6|=0x00;
        seg7&=0x7f;seg7|=0x00;
	}

    /*****************屏幕设定右边数值******************/
    if(!Speed_ShowFlag)
    {
        if(Speed.Set)
        {
            /***********val3千位***********/
            if(val3 > 999)//大于999时
            {
                Val=val3/1000;//除以1000
                if(val3 > 9)//如果大于9，那么说明除以1000后是两位数
                    Val=Val%10;//除以10取余，得出千位上的数
                seg9&=0x80;seg9|=Tab1[Val];
            }
            else
            {
                seg9&=0x80;seg9|=0x00;
            }

            /***********val3百位***********/
            if(val3 > 99)//大于99时
            {
                Val=val3/100;//除以100
                if(val3 > 9)//如果大于9，那么说明除以100后是两位数
                    Val=Val%10;//除以10取余，得出百位上的数
                seg10&=0x80;seg10|=Tab1[Val];
            }
            else
            {
                seg10&=0x80;seg10|=0x00;
            }

            /***********val3十位***********/
            if(val3 > 9)//大于9时
            {
                Val=val3/10;//除以10
                if(val3 > 9)//如果大于9，那么说明除以10后是两位数
                    Val=Val%10;//除以10取余，得出十位上的数
                seg11&=0x80;seg11|=Tab1[Val];
            }
            else
            {
                seg11&=0x80;seg11|=0x00;
            }

            /***********val3个位***********/
            Val=val3%10;//取出个位
            seg12&=0x80;seg12|=Tab1[Val];
        }
        else
        {
            seg9&=0x80;seg9|=0x08;
            seg10&=0x80;seg10|=0x08;
            seg11&=0x80;seg11|=0x08;
            seg12&=0x80;seg12|=0x08;
        }
    }
    else
    {
        seg9&=0x80;seg9|=0x00;
        seg10&=0x80;seg10|=0x00;
        seg11&=0x80;seg11|=0x00;
        seg12&=0x80;seg12|=0x00;
    }
    /*****************速度单位******************/
    seg11&=0x7F;seg11|=0x80;
#endif
	if(Protect)
	{
		if(Protect_ShowFlag)
		{
			seg1 = 0xFF;
			seg2 = 0xFF;
			seg3 = 0xFF;
			seg4 = 0xFF;
			seg5 = 0xFF;
			seg6 = 0xFF;
			seg7 = 0xFF;
			seg8 = 0xFF;
			seg9 = 0xFF;
			seg10 = 0xFF;
			seg11 = 0xFF;
			seg12 = 0xFF;
		}
		else
		{
			seg1 = 0x00;
			seg2 = 0x00;
			seg3 = 0x00;
			seg4 = 0x00;
			seg5 = 0x00;
			seg6 = 0x00;
			seg7 = 0x00;
			seg8 = 0x00;
			seg9 = 0x00;
			seg10 = 0x00;
			seg11 = 0x00;
			seg12 = 0x00;
		}
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
 * 函数原型：void Judge_SpeedMode(void)
 * 功    能：判断速度显示的模式
*****************************************************************
*/
void Judge_SpeedMode(void)
{
    if(!Speed.Set)
    {
        Speed.DisplayMode = 0;
    }
    else if(Speed.Set > Speed.Rel)//升速
    {
        Speed.DisplayMode = 1;
    }
    else//降速
    {
        Speed.DisplayMode = 2;
    }
}

/*
*****************************************************************
 * 函数原型：void Judge_TempMode(void)
 * 功    能：判断温度显示的模式
*****************************************************************
*/
void Judge_TempMode(void)
{
	if(!Temp.Ctrl)
		Temp.DisplayMode = 0;
	else if(Temp.Ctrl > Temp.Rel)
		Temp.DisplayMode = 1;//升温
	else if(Temp.Ctrl < Temp.Rel)
		Temp.DisplayMode = 2;//保温
}

/*
*****************************************************************
 * 函数原型：void Deal_Speed(float dT)
 * 功    能：速度显示处理
*****************************************************************
*/
void Deal_Speed(float dT)
{
	switch(Speed.DisplayMode)
	{
		case 0:Speed.Display_Rel = 0;
			break;
		case 1://升速时
				if(Speed.Display_Rel < Speed.Rel && !sys.SetMode_Option)
					Speed.Display_Rel ++;
				if(Speed.Ctrl == 1200 && Speed.Rel > 1140)
					Speed.Display_Rel ++;
				if(Speed.Display_Rel >= Speed.Ctrl)
					Speed.DisplayMode = 3;
			break;
		case 2://降速时
				if(Speed.Display_Rel > Speed.Rel && !sys.SetMode_Option)
					Speed.Display_Rel --;
				if(sys.Run_Status && (Speed.Display_Rel <= Speed.Ctrl))
					Speed.DisplayMode = 3;
			break;
		case 3: Speed.Display_Rel = Speed.Ctrl;
			break;
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
	if(sys.Run_Status && !Display_Res && Temp.Set != 0)//系统开启，加热功能开启
	{	
		if(Temp.DisplayMode == 0)
		{
			Temp.Display_Rel = Temp.Rel;
		}
		else if(Temp.DisplayMode == 1)
		{
			if(Temp.Display_Rel <= Temp.Rel)
			{
				Temp.Display_Rel ++;
			}
			if(Temp.Display_Rel >= Temp.Ctrl)
			{
				Temp.DisplayMode = 3;
			}
		}
		else if(Temp.DisplayMode == 2)
		{
			if(Temp.Display_Rel >= Temp.Rel)
			{
				Temp.Display_Rel --;
			}
			if(Temp.Display_Rel <= Temp.Ctrl)
			{
				Temp.DisplayMode = 3;
			}
		}
		else if(Temp.DisplayMode == 3)
		{
			Temp.Display_Rel = Temp.Ctrl;
		}
	}
	else
	{
		Temp.Display_Rel = Temp.Rel;
		Temp.DisplayMode = 0;
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
    Temp.Display_Set = Temp.Set;
    Speed.Display_Set = Speed.Set;

#if(Type == 0)
    Time.Display_Set = Time.Set;
    if(sys.Run_Status)
        Time.Display_Rel = Time.Rel+59;
    else
        Time.Display_Rel = Time.Rel;
#elif(Type == 1)
    if(sys.Run_Status && !sys.SetMode_Option)
        Time.Display_Set = Time.Rel+59;
    else
        Time.Display_Set = Time.Set;
#endif
	if(Temp.Display_Rel > 1000)
		Temp.Display_Rel = 1000;
    Display_RelVal(Temp.Display_Rel,Time.Display_Rel,Speed.Display_Rel);
    Display_SetVal(Temp.Display_Set,Time.Display_Set,Speed.Display_Set);
}
