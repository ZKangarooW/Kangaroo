#include "Ctrl_ControlTemp.h"

/**********结构体************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;

/**********全局变量声明******/
uint8_t Protect;//防干烧

/*
*****************************************************************
 * 函数原型：void Temp_PID(void)
 * 功    能：温度控制PID系数
*****************************************************************
*/
void Temp_PID(void)
{
    Temp_Arg.Kp = 0;
    Temp_Arg.Ki = 0;
    Temp_Arg.Kd = 0;
}

// 设置 PWM 输出（控制加热器）
void setPWM(float duty_cycle)
{
    HEAT = (int)((duty_cycle*2));
}

float Ku = 0.0;               // 临界增益
float Tu = 0.0;               // 临界周期
float Kp = 0.1;// 初始增益
float control_signal = 0.0;   // 控制信号
int oscillation_count = 0;
float last_temp = 0.0;
float last_peak_time = 0.0;
float peak_time[2] = {0.0, 0.0}; // 记录两个峰值的时间
// 自动调参模块
bool AutoTunePID(float dt, float *Ku, float *Tu) {

    // 使用比例控制
    control_signal = Kp * (Temp.Ctrl - Temp.Rel);
    if(control_signal>100)
        control_signal = 100;
    if(control_signal<0)
        control_signal = 0;
    if(Temp.Rel >= Temp.Ctrl)
        control_signal = 0;
    setPWM(control_signal);
    // 检测振荡
    if (Temp.Rel > Temp.Ctrl && last_temp < Temp.Ctrl) {
        if (oscillation_count < 2) {
            peak_time[oscillation_count] = last_peak_time;
        }
        oscillation_count++;
    }
    last_temp = Temp.Rel;
    last_peak_time += dt;

    // 计算 Ku 和 Tu
    if (oscillation_count >= 2) {
        *Ku = Kp;
        *Tu = peak_time[1] - peak_time[0];
        return true; // 自动调参完成
    }

    // 增加增益
    if(Temp.Rel < Temp.Ctrl)
        Kp += 0.008;
    return false; // 尚未完成
}
float Error_Val,Ki_Val;
/*
*****************************************************************
 * 函数原型：void Temp_Control(float dT)
 * 功    能：温度加热控制
*****************************************************************
*/
bool tuning_complete = false;
void Temp_Control(float dT)
{ 
//    static float T;
	if(sys.Run_Status == 1)
	{
        if(Temp.Ctrl)
        {
//            T += dT;
//            if(T >= 4.0f)
//            {
                // 自动调参阶段
                if (!tuning_complete) {
                    tuning_complete = AutoTunePID(dT, &Ku, &Tu);
                    if(tuning_complete)
                    {
//                        Temp_Arg.Kp = Ku; 
                        Temp_Arg.Kp = 0.6 * Ku;
                        Temp_Arg.Ki = 2 * Kp / Tu;
                        Temp_Arg.Kd = Kp * Tu / 8; 
                    }
//                    T = 0;
                    return;
                }
                AltPID_Calculation(dT,Temp.Ctrl,Temp.Rel,&Temp_Arg,&Temp_Val,80,20);
//                IncPID_Calculation(dT,Temp.Ctrl,Temp.Rel,&Temp_Arg,&Temp_Val,80);//温度PID控制
                
                control_signal = Temp_Val.Out; 
//                control_signal = (Temp_Arg.Kp+ Ki_Val) * (Temp.Ctrl - Temp.Rel) ;
//                if(Temp.Rel < Temp.Ctrl)
//                {
//                    Error_Val = Ki_Val;
//                    Ki_Val += 0.001;
//                }
//                else
//                    Ki_Val = Error_Val;
//                T = 0;
//            }
            if(control_signal>100)
                control_signal = 100;
            if(control_signal<0)
                control_signal = 0;
            if(Temp.Rel >= Temp.Ctrl)
                control_signal = 0;
            setPWM(control_signal);
        }
	}
	else
	{
		Temp_Val.Out = 0; 
		HEAT = Temp_Val.Out;
	}
}
