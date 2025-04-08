#include "Ctrl_ControlTemp.h"

/**********结构体************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;

/**********局部变量声明******/
float Ku = 0.0;//临界增益
float Tu = 0.0;//临界周期

/**********全局变量声明******/
bool tuning_complete = false;//自动调参标志位
float last_peak_time = 0.0;//上一个周期
int oscillation_count = 0;//震荡周期

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
    Temp_Arg.Kp_i = 0.1;
}

/*
*****************************************************************
 * 函数原型：void setPWM(float duty_cycle)
 * 功    能：设置 PWM 输出（控制加热器）
*****************************************************************
*/
void setPWM(float duty_cycle)
{
    if(duty_cycle>100)
        duty_cycle = 100;
    if(duty_cycle<0)
        duty_cycle = 0;
    if(Temp.Rel >= Temp.Ctrl)
        duty_cycle = 0;
    HEAT = (int)((duty_cycle*2));
}

/*
*****************************************************************
 * 函数原型：bool AutoTunePID(float dt, float *Ku, float *Tu) 
 * 功    能：自动调参模块
 * 输    入：dT：周期（单位：秒）
			 Ku：临界增益
			 Tu：临界周期
 * 参    数：float dT, float *Ku, float *Ku
*****************************************************************
*/
bool AutoTunePID(float dT, float *Ku, float *Tu) 
{    
    static float last_temp = 0.0;
    static float peak_time[2] = {0.0, 0.0}; // 记录两个峰值的时间
    
    //使用比例控制
    Temp_Val.Out = Temp_Arg.Kp_i * (Temp.Ctrl - Temp.Rel);
    setPWM(Temp_Val.Out);
    
    //检测振荡
    if (Temp.Rel > Temp.Ctrl && last_temp < Temp.Ctrl) 
    {
        if (oscillation_count < 2) {
            peak_time[oscillation_count] = last_peak_time;
        }
        oscillation_count++;
    }
    last_temp = Temp.Rel;
    last_peak_time += dT;

    //计算 Ku 和 Tu
    if (oscillation_count >= 2) 
    {
        *Ku = Temp_Arg.Kp_i;
        *Tu = peak_time[1] - peak_time[0];
        oscillation_count = 0;
        return true; //自动调参完成
    }

    //增加增益
    if(Temp.Rel < Temp.Ctrl)
        Temp_Arg.Kp_i += 0.008;
    return false; //尚未完成
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
            // 自动调参阶段
            if (!tuning_complete) {
                tuning_complete = AutoTunePID(dT, &Ku, &Tu);
                if(tuning_complete)
                {
                    Temp_Arg.Kp = 0.6 * Ku;
                    Temp_Arg.Ki = 2 * Temp_Arg.Kp_i / Tu;
                    Temp_Arg.Kd = Temp_Arg.Kp_i * Tu / 8; 
                    Temp_Arg.Kp_i = 0.1;// 初始增益
                }
                return;
            }
            AltPID_Calculation(dT,Temp.Ctrl,Temp.Rel,&Temp_Arg,&Temp_Val,80,20);   
            setPWM(Temp_Val.Out);
        }
	}
	else
	{
        tuning_complete = false;//自动调参设置为false
        last_peak_time = 0.0;//上一个周期清零
        oscillation_count = 0;//震荡清零
		Temp_Val.Out = 0; 
		HEAT = Temp_Val.Out;
	}
}
