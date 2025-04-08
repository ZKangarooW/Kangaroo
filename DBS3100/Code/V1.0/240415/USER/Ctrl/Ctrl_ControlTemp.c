#include "Ctrl_ControlTemp.h"
//69->76.7
/**********
30 -> 32.4 = 80.1
70 -> 77.2 = 14.5
25 -> 26


***********/
/**********结构体************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;
_PID_Val_ HEATGAITemp_Val;

/**
 * @brief 温度控制PID系数
 *
 */
void Temp_PID(void)
{
    Temp_Arg.Kp = 4;
    Temp_Arg.Ki = 0.04;
    Temp_Arg.Kd = 0.0f;
}

/**
 * @brief 温度控制
 *
 * @param dT 任务周期
 */
void Temp_Control(float dT)
{
    if (sys.Run_Status == 1)
    {
		if(Temp.Set - Temp.Rel > -10 && Temp.Set - Temp.Rel < 10)
			 Temp_Arg.Ki = 0.04;
		else
			Temp_Arg.Ki = 0.004;
        
        AltPID_Calculation(dT, Temp.Set, Temp.Rel, &Temp_Arg, &Temp_Val, 100, 989); // 加热制冷控制
        
		if(Temp_Val.Out< -200)
			Temp_Val.Out = -200;
		
		HEAT_Duty(dT, (int)Temp_Val.Out);
		
//        if (ADC_Val2)
//        {
//            AltPID_Calculation(dT, CtrlTempADC_Val, ADC_Val2, &Temp_Arg, &HEATGAITemp_Val, 199, 199); // 热盖加热控制
//            HEATGAI = HEATGAITemp_Val.Out;
//        }
//        else
//        {
//            HEATGAI = 0;
//        }
    }
    else
    {
        Temp_Val.Out = 0;
        COLD = 0;
		HEAT = 0;
        HEATGAI = 0;
    }
}
