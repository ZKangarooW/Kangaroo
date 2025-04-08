#include "Ctrl_ControlTemp.h"

/**********结构体************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;

uint8_t JDQ_Flag;
/*
*****************************************************************
 * 函数原型：static void Set_Heating_Power(float pwm)
 * 功    能：设置加热盘功率
 * 输    入: 加热的pwm功率 
 * 参    数：float control_signal
*****************************************************************
*/
static void Set_Heating_Power(float pwm)
{
    // 根据PID输出控制加热盘功率
    int power = (int)pwm;  // 将控制信号转为功率（范围0-255）
    if(Temp.Rel>Temp.Mesa)
    {
        HEAT = 0;
        HEAT_OFF;
        JDQ_Flag = 0;
    }
    else if (power < 0)
    {
        power = 0;  // 限制功率为0
        HEAT = power;//功率小于300用PWM控制
        HEAT_OFF;
        JDQ_Flag = 0;
    }
    else if (power < 399)
    {
        HEAT = power;//功率小于300用PWM控制
        HEAT_OFF;
        JDQ_Flag = 0;
    }
    
//    else//如果功率大于300并且不小于0，用继电器开启
//    {
//        power = 0;//限制功率为0
//        HEAT = power;//功率小于300用PWM控制
//        HEAT_OFF;
//        JDQ_Flag = 0;
//    }
}

/*
*****************************************************************
 * 函数原型：void Temp_PID(void)
 * 功    能：温度控制PID系数
*****************************************************************
*/
void Temp_PID(void)
{
//	Temp_Arg.Kp = 1000*0.001f;
//	Temp_Arg.Ki = 8*0.001f;//18
//	Temp_Arg.Kd = 90*0.001f;;//控台面
//    Temp_Arg.Kp_i = 0.1;
    
    Temp_Arg.Kp = 774*0.001f;
	Temp_Arg.Ki = 30*0.001f;//18
	Temp_Arg.Kd = 13.846f;;//控台面
}

/*
*****************************************************************
 * 函数原型：static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
 * 功    能：台面温度控制
*****************************************************************
*/
static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
{
    AltPID_Calculation(dT, Ctrl_temp, Temp.Mesa, &Temp_Arg, &Temp_Val, 100, 300);
    Set_Heating_Power(Temp_Val.Out);
}

/**********局部变量声明******/
float Ku = 0.0;//临界增益
float Tu = 0.0;//临界周期

/**********全局变量声明******/
bool tuning_complete = false;//自动调参标志位
float last_peak_time = 0.0;//上一个周期
int oscillation_count = 0;//震荡周期

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
    Set_Heating_Power(Temp_Val.Out);
    
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
        Temp_Arg.Kp_i += 0.001;
    return false; //尚未完成
}
uint8_t tuning_complete1;
uint8_t oscillation_count1;
/*
*****************************************************************
 * 函数原型：void Temp_Control(float dT)
 * 功    能：温度加热控制
*****************************************************************
*/
void Temp_Control(float dT)
{ 
    static float T;
    static float last_temp1 = 0.0;
    if(sys.Run_Status)//启动系统控制台面
	{
        if(Temp.Ctrl)
        {
            if((Temp.Ctrl - Temp.Rel)>200)//大于10℃
            {
                tuning_complete1 = 1;
                
                HEAT_ON;
                JDQ_Flag = 1;

                last_temp1 = Temp.Rel;
            }
            else
            {
                // 表示温度相差了10℃
                if (tuning_complete1) 
                {
                    if (Temp.Rel < Temp.Ctrl && last_temp1 > Temp.Rel) 
                    {
                        oscillation_count1++;
                        if(oscillation_count1 >= 4)
                        {
                            tuning_complete1 = 0;
                        }
                    }
                    last_temp1 = Temp.Rel;
                }
                else
                {
//                    // 自动调参阶段
//                    if (!tuning_complete) 
//                    {
//                        tuning_complete = AutoTunePID(dT, &Ku, &Tu);
//                        if(tuning_complete)
//                        {
//                            Temp_Arg.Kp = 0.6 * Ku;
//                            Temp_Arg.Ki = 2 * Temp_Arg.Kp_i / Tu;
//                            Temp_Arg.Kd = Temp_Arg.Kp_i * Tu / 8; 
//                            Temp_Arg.Kp_i = 0.1;// 初始增益
//                        }
//                        return;
//                    }
                    Mesa_Ctrl(dT, Temp.Ctrl);
                }
            }
        }
        else
        {
            HEAT = 0;//pwm不输出
            HEAT_OFF;
        }
	}
    else
	{
		HEAT = 0;//pwm不输出
        HEAT_OFF;
	}
}
