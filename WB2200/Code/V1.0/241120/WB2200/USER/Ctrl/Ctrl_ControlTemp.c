#include "Ctrl_ControlTemp.h"

/**********结构体************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;

/**********全局变量声明******/
uint8_t Protect;//防干烧
uint16_t LIMIT_Val;//积分限制

/**********局部变量声明******/
float CtrlTempADC_Val,RelTempADC_Val;

/*
*****************************************************************
 * 函数原型：void Temp_PID(void)
 * 功    能：温度控制PID系数
*****************************************************************
*/
void Temp_PID(void)
{
    Temp_Arg.Kp = 2;
    Temp_Arg.Ki = 5 * 0.001f;
    Temp_Arg.Kd = 100;
}

/*
*****************************************************************
 * 函数原型：void Temp_Control(float dT)
 * 功    能：温度加热控制
*****************************************************************
*/
void Temp_Control(float dT)
{ 
	if(sys.Run_Status == 1)
	{
		if(Temp.Ctrl)
		{
            if(HAL_GPIO_ReadPin(FGS_GPIO_Port,FGS_Pin) == 1)
            {
                Protect = 1;//打开防干烧
                Beep_Flash = 30;//蜂鸣器响30下
                sys.Run_Status = 0;
            }
            RelTempADC_Val = ADC_Val;
			CtrlTempADC_Val = Get_ADCVal(Temp.Ctrl);
			AltPID_Calculation(dT,CtrlTempADC_Val,RelTempADC_Val,&Temp_Arg,&Temp_Val,100,LIMIT_Val);//温度PID控制
			if(Temp_Val.Out > 1000)
				Temp_Val.Out = 1000;
			if(Temp_Val.Out <= 0)
				Temp_Val.Out = 0;
			HEAT = (int)Temp_Val.Out;
		}
	}
	else
	{
		Temp_Val.Out = 0; 
		HEAT = Temp_Val.Out;
	}
}
