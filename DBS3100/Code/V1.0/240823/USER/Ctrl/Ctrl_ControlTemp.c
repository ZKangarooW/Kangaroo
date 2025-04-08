#include "Ctrl_ControlTemp.h"

/**********结构体************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;
_PID_Val_ HEATGAITemp_Val;

/**********局部变量**********/
uint16_t CtrlTempADC_Val;

/**
 * @brief 温度控制PID系数
 *
 */
void Temp_PID(void)
{
    Temp_Arg.Kp = 2;
    Temp_Arg.Ki = 0.04;
    Temp_Arg.Kd = 0 * 0.001f;
}

/**
 * @brief 温度控制
 *
 * @param dT 任务周期
 */
uint8_t Out_Enable;
void Temp_Control(float dT)
{
    if (sys.Run_Status == 1)
    {
		CtrlTempADC_Val = Get_ADCVal(Temp.Ctrl/1.02);

		if((CtrlTempADC_Val - ADC_Val1 > -100 && CtrlTempADC_Val - ADC_Val1 < 100))
			Out_Enable = 1;
		else
			Out_Enable = 0;
        AltPID_Calculation(dT, CtrlTempADC_Val, ADC_Val1, &Temp_Arg, &Temp_Val, 100, Out_Enable * 989); // 加热制冷控制
        
		if(Temp_Val.Out< -200)
			Temp_Val.Out = -200;
		
		HEAT_Duty(dT, (int)Temp_Val.Out);
		
        if (ADC_Val2)
        {
            AltPID_Calculation(dT, CtrlTempADC_Val, ADC_Val2, &Temp_Arg, &HEATGAITemp_Val, 199, 199); // 热盖加热控制
            HEATGAI = HEATGAITemp_Val.Out;
        }
        else
        {
            HEATGAI = 0;
        }
    }
    else
    {
        Temp_Val.Out = 0;
        COLD = 0;
		HEAT = 0;
        HEATGAI = 0;
    }
}
