#include "Ctrl_ControlTemp.h"

/**********结构体************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;

/**********全局变量**********/
uint8_t Protect,Display_Res;//防干烧保护和加水后显示

/*
*****************************************************************
 * 函数原型：void Temp_PID(void)
 * 功    能：温度控制PID系数
*****************************************************************
*/
void Temp_PID(void)
{
    Temp_Arg.Kp = 20000 * 0.001f;
    Temp_Arg.Ki = 50 * 0.001f;
    Temp_Arg.Kd = 6000 * 0.001f;
}

uint16_t Ctrl_Cal,Cnt;
uint16_t LIMIT_Val;
uint16_t PWM_ADD;
/*
*****************************************************************
 * 函数原型：void Check_TempStop(float dT)
 * 功    能：检测温度是否停止上升
*****************************************************************
*/
void Check_TempStop(float dT)
{
	static float T;
	static uint16_t Temp_Old;
	if(sys.Run_Status)
	{
		if(Temp.DisplayMode<3)
		{
			if(Temp.Display_Rel == Temp_Old)
			{
				T += dT;
				if(T > 15.0f)
				{
					PWM_ADD = 50;//加功率
                    Temp.Display_Rel ++;
					T = 0;
				}
			}
			else
			{
				PWM_ADD = 0;//加功率
				T = 0;
			}
			Temp_Old = Temp.Display_Rel;
		}
		else
		{
			PWM_ADD = 0;//加功率
			T = 0;
		}
	}
	else
	{
		PWM_ADD = 0;//加功率
		T = 0;
	}
}

/*
*****************************************************************
 * 函数原型：void Temp_Control(float dT)
 * 功    能：温度加热控制
*****************************************************************
*/
uint16_t CtrlTempADC_Val,RelTempADC_Val;
void Temp_Control(float dT)
{ 
	if(sys.Run_Status)
	{
		if(Temp.Ctrl && Temp.Alarm < Temp.Ctrl)
		{
			LIMIT_Val = 200;
			if(Temp.DisplayMode < 3)
			{
				if(Temp.Alarm < Temp.Ctrl)
					RelTempADC_Val = ADC_Val1;
				else
					RelTempADC_Val = ADC_Val2;
			}
			else
			{
				RelTempADC_Val = ADC_Val2;
			}
			CtrlTempADC_Val = Get_ADCVal(Temp.Ctrl);
			AltPID_Calculation(dT,CtrlTempADC_Val,RelTempADC_Val,&Temp_Arg,&Temp_Val,50,LIMIT_Val);//电机PID控制
			if(Temp_Val.Out > 200)
				Temp_Val.Out = 200;
			if(Temp_Val.Out <= 0)
				Temp_Val.Out = 0;
			HEAT = Temp_Val.Out + PWM_ADD;
		}
		else
		{
			Temp_Val.Out = 0; 
			HEAT = Temp_Val.Out;
		}
	}
	else
	{
		Temp_Val.Out = 0; 
		HEAT = Temp_Val.Out;
	}
}

/*
*****************************************************************
 * 函数原型：void Check_FGS(float dT)
 * 功    能：检测防干烧
*****************************************************************
*/
void Check_FGS(float dT)
{
    static float T;
	if(!Protect && sys.Run_Status == 1 && Temp.Set != 0)
	{
		if(Temp.Alarm - Temp.Rel > 300)
		{
			T += dT;
			if(T > 1.0f)
			{
				Protect = 1;//打开防干烧
				sys.Run_Status = 0;
				Beep_Flash = 30;//响30下
				T = 0;
			}
		}
		else
		{
			T = 0;
		}
	}
}

/*
*****************************************************************
 * 函数原型：void Check_AddWater(float dT)
 * 功    能：检测加水
*****************************************************************
*/
void Check_AddWater(float dT)
{
	static float T;
    if(Temp.DisplayMode)
	{
		if(ABS(Temp.Rel_Speed) > 15)
		{
			Display_Res = 1;//重新显示
			Beep_Flash = 2;//响2下
		}
	}
	else
	{
		if(Display_Res)
		{
			if(ABS(Temp.Rel_Speed) < 5)     	
			{
				T += dT;
				if(T > 4.0f)
				{
					Display_Res = 0;//重新显示关闭
					Judge_TempMode();//温度显示模式检测
					Beep_Flash = 3;//响3下
					T = 0;
				}	
			}
			else
			{
				T = 0;
			}
		}
	}
}
