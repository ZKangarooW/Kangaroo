#include "Ctrl_ControlTemp.h"

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
		if(Temp.Ctrl == 1)//高温
        {
            Heater.PWM = 30;
        }
        else
        {
            Heater.PWM = 50;
        }
	}
	else
	{
		Heater.PWM = 0;
	}
}
