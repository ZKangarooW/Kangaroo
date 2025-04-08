#include "Ctrl_ControlTemp.h"

/**********结构体************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;

/**********局部变量声明******/
float CtrlTempADC_Val,RelTempADC_Val;//控制温度和实际温度的ADC值

/*
*****************************************************************
 * 函数原型：void Temp_PID(void)
 * 功    能：温度控制PID系数
*****************************************************************
*/
void Temp_PID(void)
{
	Temp_Arg.Kp = 120;
	Temp_Arg.Ki = 50*0.001f;
	Temp_Arg.Kd = 20000*0.001f;
}

/*
*****************************************************************
 * 函数原型：void Temp_Control(float dT)
 * 功    能：温度加热控制
*****************************************************************
*/
void Temp_Control(float dT)
{ 
	if(sys.Run_Status)//启动系统
	{
		CtrlTempADC_Val = Get_ADCVal(Temp.Ctrl);
		RelTempADC_Val = ADC_Val;
		AltPID_Calculation(dT, CtrlTempADC_Val, RelTempADC_Val, &Temp_Arg, &Temp_Val, 100, 1000);
		if(Temp_Val.Out < 0) Temp_Val.Out = 0;
		HEAT =(int)Temp_Val.Out;
    }
	else
	{
        Temp_Val.Out = 0;
		HEAT = 0;//pwm不输出
	}
}

/*
*****************************************************************
 * 函数原型：void Check_Temp_Time(float dT)
 * 功    能：后台检测加热的时间
*****************************************************************
*/
void Check_Temp_Time(float dT)
{
    static float T;
    if(sys.Run_Status && Temp.Ctrl)
    {
        T += dT;
        if(T > 28800.0f)//8小时
        {
            sys.Run_Status = 0;//系统关闭
            sys.Time_Status = 0;//倒计时关闭
            SpeedSet_Flag = TimeSet_Flag = 1;//速度设置，时间设置
            Temp_Twinkle_Time = Time_Twinkle_Time =0;//闪烁时间清零
            EC11A[0].EC11A_Knob = EC11A[1].EC11A_Knob = 0;//旋钮时间清零
            Beep_Time = 5.0f;//蜂鸣器响0.1S
            Temp.ADDMode = 0;//加热显示模式清零
            T = 0;
        }
    }
    else
    {
        T = 0;
    }
}
