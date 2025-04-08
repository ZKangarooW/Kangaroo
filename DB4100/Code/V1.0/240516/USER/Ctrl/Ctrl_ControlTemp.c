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
	if(sys.Run_Status == 1)//启动系统
	{
		CtrlTempADC_Val = Get_ADCVal(Temp.Ctrl);
		RelTempADC_Val = ADC_Val;
		AltPID_Calculation(dT, CtrlTempADC_Val, RelTempADC_Val, &Temp_Arg, &Temp_Val, 400, 400);
		if(Temp_Val.Out < 0) Temp_Val.Out = 0;
		HEAT = (int)Temp_Val.Out;
    }
	else
	{
        Temp_Val.Out = 0;
		HEAT = 0;//pwm不输出
	}
}
