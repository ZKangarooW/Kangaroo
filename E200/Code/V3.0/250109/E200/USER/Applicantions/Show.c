#include "Show.h"

/**********全局变量声明******/
float Twinkle_Time;//闪烁时间

/**********局部变量声明******/
uint8_t Tab[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};//0·9
uint8_t HeatTemp_ShowFlag,CoolTemp_ShowFlag,Time_ShowFlag;//加热温度闪烁,制冷温度闪烁，时间闪烁
uint8_t HeatTemp_XSDFlag,CoolTemp_XSDFlag;//单加热小数点闪烁，制冷小数点闪烁

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
	if(sys.Calibration)
	{
		if(T == 0)
		{
			T += dT;
			if(sys.SetMode_Option == 4)//设置CoolTemp时
			{
				HeatTemp_ShowFlag = 0;//加热温度常亮
				CoolTemp_ShowFlag = !CoolTemp_ShowFlag;//制冷温度闪烁
				Time_ShowFlag = 0;//时间常亮
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
		if(LongPress == 1)
		{
			if(sys.SetMode_Option == 1)//设置HeatTemp时
			{
				HeatTemp_ShowFlag = 1;//加热温度常灭
				CoolTemp_ShowFlag = 0;//制冷温度常亮
				Time_ShowFlag = 0;//时间常亮
			}
			else if(sys.SetMode_Option == 2)//设置CoolTemp时
			{
				HeatTemp_ShowFlag = 0;//加热温度常亮
				CoolTemp_ShowFlag = 1;//制冷温度常灭
				Time_ShowFlag = 0;//时间常亮
			}
			else if(sys.SetMode_Option == 3)//设置CoolTemp时
			{
				HeatTemp_ShowFlag = 0;//加热温度常亮
				CoolTemp_ShowFlag = 0;//制冷温度常亮
				Time_ShowFlag = 1;//时间常灭
			}
			return;
		}
		if(Twinkle_Time && Key_Status==0)//闪烁和没有操作按键时
		{
			if(T == 0)
			{
				T += dT;
				Twinkle_Time -= 0.5;//闪烁计时
				if(Twinkle_Time == 0)//如果闪烁结束
				{
					sys.TempOption_Mun = 0;//温度设置位数复位
					sys.TimeOption_Mun = 0;//时间设置位数复位
					sys.SetMode_Option = 0;//模式选择清零
				} 
				if(sys.SetMode_Option == 1)//设置HeatTemp时
				{
					HeatTemp_ShowFlag = !HeatTemp_ShowFlag;//加热温度闪烁
					CoolTemp_ShowFlag = 0;//制冷温度常亮
					Time_ShowFlag = 0;//时间常亮
				}
				else if(sys.SetMode_Option == 2)//设置CoolTemp时
				{
					HeatTemp_ShowFlag = 0;//加热温度常亮
					CoolTemp_ShowFlag = !CoolTemp_ShowFlag;//制冷温度闪烁
					Time_ShowFlag = 0;//时间常亮
				}
				else if(sys.SetMode_Option == 3)//设置Time时
				{
					HeatTemp_ShowFlag = 0;//加热温度常亮
					CoolTemp_ShowFlag = 0;//制冷温度常亮
					Time_ShowFlag = !Time_ShowFlag;//时间闪烁
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
			HeatTemp_ShowFlag = 0;//加热温度常亮
			CoolTemp_ShowFlag = 0;//制冷温度常亮
			Time_ShowFlag = 0;//时间常亮
			T = 0;
		}
	}
}

/*
*****************************************************************
 * 函数原型：static void Heating_Twinkle(float dT)
 * 功    能：小数点闪烁检测
 * 输    入: dT:执行周期
 * 参    数：float dT
 * 调    用：内部调用
*****************************************************************
*/
static void Heating_Twinkle(float dT)
{
	static float T,T1;
	if(Heat_Temp.ADDMode == 0)
	{
		T += dT;
		if(T >= 0.5f)
		{
			T = 0;
			HeatTemp_XSDFlag = !HeatTemp_XSDFlag;//单加热小数点闪烁
		}
	}
	else
	{
		T = 0;
		HeatTemp_XSDFlag = 0;//常亮
	}
	
	if(Cool_Temp.ADDMode == 0)
	{
		T1 += dT;
		if(T1 >= 0.5f)
		{
			T1 = 0;
			CoolTemp_XSDFlag = !CoolTemp_XSDFlag;//单加热小数点闪烁
		}
	}
	else
	{
		T1 = 0;
		CoolTemp_XSDFlag = 0;//常亮
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
	Heating_Twinkle(dT);//小数点闪烁
}

/*
*****************************************************************
 * 函数原型：void Display_HeatTemp(int16_t temp)
 * 功    能：显示加热区域温度
 * 输    入: temp：加热区域的温度
 * 参    数：int16_t temp
*****************************************************************
*/
void Display_HeatTemp(int16_t temp)
{
	uint8_t seg1,seg2,seg3;
	seg1=0;seg2=0;seg3=0;
	uint16_t Val;//用于百十个取出来的数字
	
	if(temp >= 0)
	{
		/***********temp百位***********/
		if(sys.TempOption_Mun == 1 && HeatTemp_ShowFlag)//假如在位数为百位并且温度在闪烁
			seg1 = 0x00;//不显示
		else
		{
			if(temp > 99)//大于99时
			{
				Val=temp/100;//取出百位
				if(temp > 999)//大于999时
					Val=Val%10;//取出百位
				seg1 = Tab[Val];
			}
		}
		
		/***********temp十位***********/
		if(sys.TempOption_Mun == 0 && HeatTemp_ShowFlag)//假如在位数为十位并且温度在闪烁
			seg2 = 0x00;//不显示
		else
		{
			if(temp > 9)//大于9时
			{
				Val=temp/10;//取出十位
				if(temp > 99)//大于999时
					Val=Val%10;//取出十位
				seg2 = Tab[Val];
			}
		}
		
		/***********temp小数位***********/
		if(sys.TempOption_Mun == 2 && HeatTemp_ShowFlag)//假如在位数为小数位并且温度在闪烁
			seg3 = 0x00;//不显示
		else
		{
			Val=temp%10;//取出个位
			seg3 = Tab[Val];
		}
	}
	else
	{
		/***********temp负号***********/
		seg1 = 0x40;
		
		/***********temp十位***********/
		if((-temp) > 9)//大于9时
		{
			Val=(-temp)/10;//取出十位
			if((-temp) > 99)//大于999时
				Val=Val%10;//取出十位
			seg2 = Tab[Val];
		}
		
		/***********temp小数位***********/
		Val=(-temp)%10;//取出个位
		seg3 = Tab[Val];
	}
	
	/***********temp小数点*********/
	if((sys.SetMode_Option == 0 || sys.SetMode_Option == 3 || sys.SetMode_Option == 4) && HeatTemp_XSDFlag)//假如在加热的情况下，并且小数点闪烁
	{
		seg2&=0x7F;seg2|=0x00;//不显示
	}
	else
	{
		seg2&=0x7F;seg2|=0x80;
	}
	
	/************************************/
	GN1640_Write_DATA(0, seg1);
	GN1640_Write_DATA(1, seg2);
	GN1640_Write_DATA(2, seg3);
}

/*
*****************************************************************
 * 函数原型：void Display_CoolTemp(int16_t temp)
 * 功    能：显示制冷区域温度
 * 输    入: temp：制冷区域的温度
 * 参    数：int16_t temp
*****************************************************************
*/
void Display_CoolTemp(int16_t temp)
{
	uint8_t seg1,seg2,seg3;
	seg1=0;seg2=0;seg3=0;
	uint16_t Val;//用于百十个取出来的数字
	
	if(temp >= 0)
	{
		/***********temp百位***********/
		if(sys.TempOption_Mun == 1 && CoolTemp_ShowFlag)//假如在位数为百位并且温度在闪烁
			seg1 = 0x00;//不显示
		else
		{
			if(temp > 99)//大于99时
			{
				Val=temp/100;//取出百位
				if(temp > 999)//大于999时
					Val=Val%10;//取出百位
				seg1 = Tab[Val];
			}
		}
		
		/***********temp十位***********/
		if(sys.TempOption_Mun == 0 && CoolTemp_ShowFlag)//假如在位数为十位并且温度在闪烁
			seg2 = 0x00;//不显示
		else
		{
			if(temp > 9)//大于9时
			{
				Val=temp/10;//取出十位
				if(temp > 99)//大于999时
					Val=Val%10;//取出十位
				seg2 = Tab[Val];
			}
		}
		
		/***********temp小数位***********/
		if(sys.TempOption_Mun == 2 && CoolTemp_ShowFlag)//假如在位数为小数位并且温度在闪烁
			seg3 = 0x00;//不显示
		else
		{
			Val=temp%10;//取出个位
			seg3 = Tab[Val];
		}
	}
	else
	{
		/***********temp百位***********/
		seg1 = 0x40;
		
		/***********temp十位***********/
		if((-temp) > 9)//大于9时
		{
			Val=(-temp)/10;//取出十位
			if((-temp) > 99)//大于999时
				Val=Val%10;//取出十位
			seg2 = Tab[Val];
		}
		
		/***********temp小数位***********/
		Val=(-temp)%10;//取出个位
		seg3 = Tab[Val];
	}

	/***********temp小数点*********/
	if((sys.SetMode_Option == 0 || sys.SetMode_Option == 3) && CoolTemp_XSDFlag)//假如在加热的情况下，并且小数点闪烁
	{
		seg2&=0x7F;seg2|=0x00;//不显示
	}
	else
	{
		seg2&=0x7F;seg2|=0x80;
	}

	/************************************/
	GN1640_Write_DATA(3, seg1);
	GN1640_Write_DATA(4, seg2);
	GN1640_Write_DATA(5, seg3);
}

/*
*****************************************************************
 * 函数原型：void Display_Time(uint8_t flag,int16_t time)
 * 功    能：显示时间
 * 输    入: flag：是否在校准界面 time：时间
 * 参    数：uint8_t flag,int16_t time
*****************************************************************
*/
void Display_Time(uint8_t flag,int16_t time)
{
	uint8_t seg1,seg2,seg3,seg4;
	seg1=0;seg2=0;seg3=0;seg4=0;
	uint8_t SM,M,SS,S;//时间的单位取值
	
	if(flag)
	{
		seg1 = 0x77;//A
		seg2 = 0x5E;//d
		seg3 = 0x0E;//j
		seg4 = 0x78;//t
	}
	else
	{
		/***********设定时间***********/
		SM=time/60/10;//计算十位单位的分钟数
		M=time/60%10;//计算个位单位的分钟数
		SS=time%60/10;//计算十分位单位的秒钟数
		S=time%60%10;//计算十分位单位的秒钟数
		
		/***********十分时间***********/
		if(sys.TimeOption_Mun == 1 && Time_ShowFlag)//假如在位数为十分并且时间在闪烁
			seg1 = 0x00;//不显示
		else
		{
			seg1 = Tab[SM];
		}
		
		/***********分钟时间***********/
		if(sys.TimeOption_Mun == 0 && Time_ShowFlag)//假如在位数为分并且时间在闪烁
			seg2 = 0x00;//不显示
		else
		{
			seg2 = Tab[M];
		}
		
		/***********十秒时间***********/
		if(sys.TimeOption_Mun == 3 && Time_ShowFlag)//假如在位数为十秒分并且时间在闪烁
			seg3 = 0x00;//不显示
		else
		{
			seg3 = Tab[SS];
		}
		/***********秒钟时间***********/
		if(sys.TimeOption_Mun == 2 && Time_ShowFlag)//假如在位数为秒并且时间在闪烁
			seg4 = 0x00;//不显示
		else
		{
			seg4 = Tab[S];
		}
		
		/***********time冒号***********/
		seg2&=0x7F;seg2|=0x80;
	}

	/************************************/
	GN1640_Write_DATA(6, seg1);
	GN1640_Write_DATA(7, seg2);
	GN1640_Write_DATA(8, seg3);
	GN1640_Write_DATA(9, seg4);
}

/*
*****************************************************************
 * 函数原型：void Deal_Temp(float dT)
 * 功    能：温度处理
*****************************************************************
*/
void Deal_Temp(float dT)
{
	static float T,T1;
    if(ABS(Heat_Temp.Rel_Temp - Heat_Temp.Ctrl_Temp)<=1)
    {
        if(!Heat_Temp.ADDMode)
            T += dT;
        if(T >= 2.0f)
        {
            T = 0;
            Heat_Temp.ADDMode = 1;
        }
    }
    else if(Heat_Temp.Ctrl_Temp - Heat_Temp.Rel_Temp > 5 || Heat_Temp.Ctrl_Temp - Heat_Temp.Rel_Temp < -5 )
    {
        if(Heat_Temp.ADDMode)
            T += dT;
        if(T >= 2.0f)
        {
            T = 0;
            Heat_Temp.ADDMode = 0;
        }
    }

	if(sys.Calibration)
	{
		if(sys.Calibration_Step == 0)
		{
			if(ABS(Cool_Temp.Rel_Temp - 260)<=1)
			{
				if(!Cool_Temp.ADDMode)
					T += dT;
				if(T >= 2.0f)
				{
					T = 0;
					Cool_Temp.ADDMode = 1;
				}
			}
			else if(260 - Cool_Temp.Rel_Temp > 5 || 260 - Cool_Temp.Rel_Temp < -5 )
			{
				if(Cool_Temp.ADDMode)
					T += dT;
				if(T >= 2.0f)
				{
					T = 0;
					Cool_Temp.ADDMode = 0;
				}
			}
		}
		else
		{
			if(ABS(Cool_Temp.Rel_Temp - 400)<=1)
			{
				if(!Cool_Temp.ADDMode)
					T += dT;
				if(T >= 2.0f)
				{
					T = 0;
					Cool_Temp.ADDMode = 1;
				}
			}
			else if(400 - Cool_Temp.Rel_Temp > 5 || 400 - Cool_Temp.Rel_Temp < -5 )
			{
				if(Cool_Temp.ADDMode)
					T += dT;
				if(T >= 2.0f)
				{
					T = 0;
					Cool_Temp.ADDMode = 0;
				}
			}
		}
	}
	else
	{
        if(ABS(Cool_Temp.Rel_Temp - Cool_Temp.Ctrl_Temp)<=1)
        {
            if(!Cool_Temp.ADDMode)
                T1 += dT;
            if(T1 >= 2.0f)
            {
                T1= 0;
                Cool_Temp.ADDMode = 1;
            }
        }
        else if(Cool_Temp.Ctrl_Temp - Cool_Temp.Rel_Temp > 8 || Cool_Temp.Ctrl_Temp - Cool_Temp.Rel_Temp < -8 )
        {
            if(Cool_Temp.ADDMode)
                T1 += dT;
            if(T1 >= 2.0f)
            {
                T1= 0;
                Cool_Temp.ADDMode = 0;
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
	static uint8_t flag = 0;
	
	if(sys.SetMode_Option >0 && sys.SetMode_Option < 3 && sys.Calibration==0)
	{
		Heat_Temp.Display_Temp = Heat_Temp.Set_Temp;
		Cool_Temp.Display_Temp = Cool_Temp.Set_Temp;
	}
	else
	{
		if(sys.Calibration)
		{
			if(Cool_Temp.ADDMode == 0)
				Heat_Temp.Display_Temp = Cool_Temp.Rel_Temp;
			else
			{
				if(sys.Calibration_Step == 0)
					Heat_Temp.Display_Temp = 260;
				else
					Heat_Temp.Display_Temp = 400;
			}
			
			if(sys.Calibration_Step == 0)
				Cool_Temp.Display_Temp = sys.Calibration_Temp1;
			else if(sys.Calibration_Step == 1)
				Cool_Temp.Display_Temp = sys.Calibration_Temp2;
		}
		else
		{
			if(Heat_Temp.ADDMode == 0)
				Heat_Temp.Display_Temp = Heat_Temp.Rel_Temp;
			else
				Heat_Temp.Display_Temp = Heat_Temp.Ctrl_Temp;
			
			if(Cool_Temp.ADDMode == 0)
				Cool_Temp.Display_Temp = Cool_Temp.Rel_Temp;
			else
				Cool_Temp.Display_Temp = Cool_Temp.Ctrl_Temp;
		}
	}

	if(Time.TimeDisplay_Flag)//正计时
	{
		Time.Display_Time = Time.Count_Time;
	}
	else//倒计时
	{
		if(sys.SetMode_Option == 3)
			Time.Display_Time = Time.Set_Time;
		else
			Time.Display_Time = Time.Ctrl_Time;
		if(sys.Calibration)
			flag = 1;
		else
			flag = 0;
	}
	Display_HeatTemp(Heat_Temp.Display_Temp);
	Display_CoolTemp(Cool_Temp.Display_Temp);
	Display_Time(flag,Time.Display_Time);
}
