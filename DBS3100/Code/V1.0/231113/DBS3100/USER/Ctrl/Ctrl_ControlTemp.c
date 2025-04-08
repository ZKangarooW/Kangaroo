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
    Temp_Arg.Kp = 0 * 0.001f;
    Temp_Arg.Ki = 0 * 0.001f;
    Temp_Arg.Kd = 0 * 0.001f;
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
        CtrlTempADC_Val = Get_ADCVal(Temp.Set);
        AltPID_Calculation(dT, CtrlTempADC_Val, ADC_Val1, &Temp_Arg, &Temp_Val, 200, 200); // 加热制冷控制
        HEAT_Duty(dT, Temp_Val.Out);
        if (ADC_Val2)
        {
            AltPID_Calculation(dT, CtrlTempADC_Val, ADC_Val2, &Temp_Arg, &HEATGAITemp_Val, 200, 200); // 热盖加热控制
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
        HEAT_Duty(dT, Temp_Val.Out);
        HEATGAI = 0;
    }
}