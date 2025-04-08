#include "Show.h"

/**********全局变量声明******/
float Twinkle_Time;//闪烁时间

/**********局部变量声明******/
uint8_t Time_ShowFlag,Temp_ShowFlag;//时间、温度显示的标志位 0:常亮 1：熄灭
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
                Temp_ShowFlag = 0;//常亮
                Time_ShowFlag = 0;//常亮
            } 
            if(sys.SetMode_Option == 1)//设置温度
			{
				Time_ShowFlag = 0;//时间常亮
				Temp_ShowFlag = ~Temp_ShowFlag;//温度闪烁
			}
			else if(sys.SetMode_Option == 2)//设置时间
			{
				Time_ShowFlag = ~Time_ShowFlag;//时间闪烁
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
        Temp_ShowFlag = 0;//常亮
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
static void Time_Twinkle(float dT)
{
	static float T;
	if(sys.Run_Status == 1)
	{
		T += dT;
		if(T >= 0.5f)
		{
			Time.Icn = ~Time.Icn;//时间图标闪烁;
			T = 0;
		}
	}
	else
	{
		Time.Icn = 0;//显示时间图标
	}
}

/*
*****************************************************************
 * 函数原型：static void Temp_Twinkle(float dT)
 * 功    能：温度图标闪烁
 * 调    用：内部调用
*****************************************************************
*/
static void Temp_Twinkle(float dT)
{
	static float T;
	if(sys.Run_Status == 1)
	{
		T += dT;
		if(T >= 0.5f)
		{
			Temp.Icn = ~Temp.Icn;//温度图标闪烁;
			T = 0;
		}
	}
	else
	{
		Temp.Icn = 0;//显示温度图标
	}
}

/*
*****************************************************************
 * 函数原型：static void Protect_Twinkle(float dT)
 * 功    能：防干烧闪烁
 * 调    用：内部调用
*****************************************************************
*/
static void Protect_Twinkle(float dT)
{
	static float T;
	if(Protect == 1)
	{
		T += dT;
		if(T >= 0.5f)
		{
			Protect_ShowFlag = ~Protect_ShowFlag;//防干烧图标闪烁;
			T = 0;
		}
	}
	else
	{
		Protect_ShowFlag = 0;//显示防干烧图标
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
    Time_Twinkle(dT);//时间图标闪烁
	Temp_Twinkle(dT);//温度图标闪烁
    Protect_Twinkle(dT);//防干烧闪烁
}

/*
*****************************************************************
 * 函数原型：void Display_RelVal(int16_t temp_rel, int32_t time_ctrl)
 * 功    能：显示实际的值
 * 输    入: temp_rel：显示实际温度;time_ctrl：显示控制的时间
 * 参    数：int16_t temp_rel, int32_t time_ctrl
*****************************************************************
*/
void Display_RelVal(int16_t temp_rel, int32_t time_ctrl)
{
    uint8_t seg1,seg2,seg3,seg4,seg5,seg6,seg7,seg8;
    seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;seg7=0;seg8=0;
	uint16_t Val;//用于百十个取出来的数字
    uint8_t SH,H,SM,M;//时间的单位取值
    
    /*****************实际温度数值******************/
    /***********temp_rel百位***********/
    if(temp_rel > 999)//大于999时
    {
        Val=temp_rel/1000;//除以1000
        if(temp_rel > 9)//如果大于9，那么说明除以1000后是两位数
            Val=Val%10;//除以10取余，得出千位上的数
        seg1&=0x80;seg1|=Tab[Val];
    }
    else
    {
        seg1&=0x80;seg1|=0x00;
    }

    /***********temp_rel十位***********/
    if(temp_rel > 99)//大于99时
    {
        Val=temp_rel/100;//除以100
        if(temp_rel > 9)//如果大于9，那么说明除以100后是两位数
            Val=Val%10;//除以10取余，得出百位上的数
        seg2&=0x80;seg2|=Tab[Val];
    }
    else
    {
        seg2&=0x80;seg2|=0x00;
    }

    /***********temp_rel个位***********/
    if(temp_rel > 9)//大于9时
    {
        Val=temp_rel/10;//除以10
        if(temp_rel > 9)//如果大于9，那么说明除以10后是两位数
            Val=Val%10;//除以10取余，得出十位上的数
        seg3&=0x80;seg3|=Tab[Val];
    }
    else
    {
        seg3&=0x80;seg3|=Tab[0];
    }

    /***********temp_rel小数位***********/
    Val=temp_rel%10;//取出个位
    seg4&=0x80;seg4|=Tab[Val];
    
    /*****************控制时间数值******************/
    if(time_ctrl == 0)//显示“----”
    {
        seg5 = 0x08;
        seg6 = 0x08;
        seg7 = 0x08;
        seg8 = 0x08;
    }
    else
    {
        if(time_ctrl < 3600)
        {
            SH = time_ctrl/60/10;//计算十位单位的小时数
            H  = time_ctrl/60%10;//计算个位单位的小时数
            SM = time_ctrl%60/10;//计算十分位单位的分钟数
            M  = time_ctrl%60%10;//计算个分位单位的分钟数
        }
        else
        {
            SH = time_ctrl/3600/10;//计算十位单位的小时数
            H  = time_ctrl/3600%10;//计算个位单位的小时数
            SM = time_ctrl%3600/60/10;//计算十分位单位的分钟数
            M  = time_ctrl%3600/60%10;//计算个分位单位的分钟数
        }
        seg5&=0x80;seg5|=Tab[SH];
        seg6&=0x80;seg6|=Tab[H];
        seg7&=0x80;seg7|=Tab[SM];
        seg8&=0x80;seg8|=Tab[M];
    }
    if(!Temp.Icn)seg4 = seg4 | 0x80;//加热图标
    else seg4 = seg4 | 0x00;//加热图标
    
    seg3 = seg3 | 0x80;//实际温度的小数点
    seg1 = seg1 | 0x80;//设置温度的℃符号
    
    if(Time.Rel  && Temp.ADDMode == 3)
    {
        if(!Time.Icn)seg7 = seg7 | 0x80;//实时时间冒号
        else seg7 = seg7 | 0x00;//实时时间冒号
    }
    else
    {
        seg7 = seg7 | 0x80;
    }
    
    if(Protect)
    {
        if(Protect_ShowFlag)
        {
            seg1 = 0xFF;
            seg2 = 0x7F;
            seg3 = 0xFF;
            seg4 = 0xFF;   
            seg5 = 0x7F;
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
 * 函数原型：void Display_SetVal(int16_t temp_set, int32_t time_set)
 * 功    能：显示设定的值
 * 输    入: temp_set：显示设定温度;time_set：显示设定时间
 * 参    数：int16_t temp_set, int32_t time_set
*****************************************************************
*/
void Display_SetVal(int16_t temp_set, int32_t time_set)
{
    uint8_t seg1,seg2,seg3,seg4,seg5,seg6,seg7,seg8;
    seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;seg7=0;seg8=0;
	uint16_t Val;//用于百十个取出来的数字
    uint8_t SH,H,SM,M;//时间的单位取值
    
    /*****************设定温度数值******************/
    /***********temp_set百位***********/
    if(!Temp_ShowFlag)
    {
        if(temp_set > 999)//大于999时
        {
            Val=temp_set/1000;//除以1000
            if(temp_set > 9)//如果大于9，那么说明除以1000后是两位数
                Val=Val%10;//除以10取余，得出千位上的数
            seg1&=0x80;seg1|=Tab2[Val];
        }
        else
        {
            seg1&=0x80;seg1|=0x00;
        }

        /***********temp_set十位***********/
        if(temp_set > 99)//大于99时
        {
            Val=temp_set/100;//除以100
            if(temp_set > 9)//如果大于9，那么说明除以100后是两位数
                Val=Val%10;//除以10取余，得出百位上的数
            seg2&=0x80;seg2|=Tab2[Val];
        }
        else
        {
            seg2&=0x80;seg2|=0x00;
        }

        /***********temp_set个位***********/
        if(temp_set > 9)//大于9时
        {
            Val=temp_set/10;//除以10
            if(temp_set > 9)//如果大于9，那么说明除以10后是两位数
                Val=Val%10;//除以10取余，得出十位上的数
            seg3&=0x80;seg3|=Tab2[Val];
        }
        else
        {
            seg3&=0x80;seg3|=Tab2[0];
        }

        /***********temp_set小数位***********/
        Val=temp_set%10;//取出个位
        seg4&=0x80;seg4|=Tab2[Val];
    }
    else
    {
        seg1 = 0x00;
        seg2 = 0x00;
        seg3 = 0x00;
        seg4 = 0x00;
    }
    
    /*****************设定时间数值******************/
    if(!Time_ShowFlag)
    {
        if(time_set == 0)//显示“----”
        {
            seg5 = 0x08;
            seg6 = 0x08;
            seg7 = 0x08;
            seg8 = 0x08;
        }
        else
        {
            if(time_set < 3600)
            {
                SH = time_set/60/10;//计算十位单位的小时数
                H  = time_set/60%10;//计算个位单位的小时数
                SM = time_set%60/10;//计算十分位单位的分钟数
                M  = time_set%60%10;//计算个分位单位的分钟数
            }
            else
            {
                SH = time_set/3600/10;//计算十位单位的小时数
                H  = time_set/3600%10;//计算个位单位的小时数
                SM = time_set%3600/60/10;//计算十分位单位的分钟数
                M  = time_set%3600/60%10;//计算个分位单位的分钟数
            }
            seg5&=0x80;seg5|=Tab1[SH];
            seg6&=0x80;seg6|=Tab1[H];
            seg7&=0x80;seg7|=Tab1[SM];
            seg8&=0x80;seg8|=Tab1[M];
        }
    }
    else
    {
        seg5 = 0x00; 
        seg6 = 0x00; 
        seg7 = 0x00; 
        seg8 = 0x00; 
    }

    if(time_set < 3600) seg7 = seg7 | 0x80;//秒单位显示
    else seg8 = seg8 | 0x80;//分钟单位显示
   
    seg3 = seg3 | 0x01;//设置温度的小数点
    
    seg6 = seg6 | 0x80;//实时时间冒号
    
    if(Protect)
    {
        if(Protect_ShowFlag)
        {
            seg1 = 0xFF;
            seg2 = 0xFE;
            seg3 = 0xFF;
            seg4 = 0xFE;   
            seg5 = 0x7F;
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
            
    Write_Addr_Dat_N(38,seg1,1);
    Write_Addr_Dat_N(36,seg2,1);
    Write_Addr_Dat_N(34,seg3,1);
    Write_Addr_Dat_N(32,seg4,1);
    Write_Addr_Dat_N(22,seg5,1);
    Write_Addr_Dat_N(20,seg6,1);
    Write_Addr_Dat_N(18,seg7,1);
    Write_Addr_Dat_N(16,seg8,1);
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
    if(sys.Run_Status == 0)//没启动的情况下
    {
		Temp.ADDMode = 0;
		Temp.Display_Rel = Temp.Rel;
        Temp_Arg.Kp = 2;
        T = 0;
    }
    else if(sys.Run_Status == 1)//启动的情况下
    {
        if(Temp.ADDMode == 0)//判断数据处理显示
        {     
		   if(Temp.Ctrl > Temp.Display_Rel)//设定温度大于显示温度
		   { 
				Temp.ADDMode = 1;//进入加热模式下
			}
		   else
		   {
				Temp.ADDMode = 2;//进入降温模式下
			}
        }
        if(Temp.ADDMode == 1)//在加热模式下
        {
            if(Temp.Rel > Temp.Display_Rel && Temp.Display_Rel <= Temp.Ctrl)
                Temp.Display_Rel++;
            else//当前温度小于上一次温度
            {
                Temp.Display_Rel = Temp.Display_Rel;
            }
            if(Temp.Display_Rel >= Temp.Ctrl)
            {
                Temp.ADDMode = 3;//进入稳定模式
                Temp_Val.Integral = 0;//积分清零
            }
            if(Temp.Rel <= Temp.Display_Rel)
            {
                T +=dT;
                if(T > 10.0f)
                {
                    Temp.Display_Rel ++;
                    LIMIT_Val += 50;
                    if(LIMIT_Val > 1000)
                    {
                        LIMIT_Val = 1000;
                    }
                    T = 0;
                }
            }
            else T = 0;
            
            if(ABS(Temp.Display_Rel - Temp.Rel) > 100)
            {
                Temp.Display_Rel = Temp.Rel;
                Temp.ADDMode = 0;
            }   
        }
		else if(Temp.ADDMode == 2)//降温模式下
        {
             T = 0;
            if(Temp.Rel < Temp.Display_Rel && Temp.Display_Rel >= Temp.Ctrl)//当前温度小于上一次温度
                Temp.Display_Rel --;//显示当前温度
            else//当前温度大于上一次温度
            {
                Temp.Display_Rel = Temp.Display_Rel;//显示上一次温度，不让温度大于当前温度。呈现下降温度的现象
            }
            if(Temp.Display_Rel <= Temp.Ctrl)
            {
                Temp.ADDMode = 3;//进入稳定模式
            }
            if(ABS(Temp.Display_Rel - Temp.Rel) > 100)
            {
                Temp.Display_Rel = Temp.Rel;
                Temp.ADDMode = 0;
            } 
            Temp_Val.Integral = 0;//积分清零            
        }  	
        else if(Temp.ADDMode == 3)//温度稳定模式下
        {
			Temp.Display_Rel = Temp.Ctrl;//显示当前显示温度
            Temp_Arg.Kp = 60; 
            T = 0;
        }  
        if(ABS(Temp.Display_Rel - Temp.Rel) > 100)
        {
            Temp.Display_Rel = Temp.Rel;
            Temp.ADDMode = 0;
        }         
    }
    else if(sys.Run_Status == 2)
    {
        T +=dT;
        if(T > 5.0f)
        {
            if(Temp.Rel < Temp.Display_Rel)
                Temp.Display_Rel --;//显示当前温度
            else if(Temp.Rel > Temp.Display_Rel)
                Temp.Display_Rel ++;//显示当前温度   
            else
                sys.Run_Status = 0;
            T = 0;
        }
        if(ABS(Temp.Display_Rel - Temp.Rel) > 150)
        {
            sys.Run_Status = 0;
        }
        Temp_Arg.Kp = 2;
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
    
    Time.Display_Rel = Time.Rel;
    Time.Display_Set = Time.Set;
    
    Display_RelVal(Temp.Display_Rel, Time.Display_Rel);
    Display_SetVal(Temp.Display_Set, Time.Display_Set);
}
