#include "Ctrl_ControlTemp.h"

/*
*****************************************************************
 * 函数原型：void Temp_Iint(void)
 * 功    能：温度初始化
*****************************************************************
*/
void Temp_Iint(void)
{
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);//开启tim1通道2的PWM
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);//开启tim3通道2的PWM
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);//开启tim3通道2的PWM
}

/**********结构体************/
_PID_Val_ HeatTemp_Val;//pid数据结构
_PID_Arg_ HeatTemp_Arg;//pid数据系数
_PID_Val_ CoolTemp_Val;//pid数据结构
_PID_Arg_ CoolTemp_Arg;//pid数据系数

/*
*****************************************************************
 * 函数原型： void PID_Init(void)
 * 功    能： pid系数初始化
*****************************************************************
*/
void PID_Init(void)
{
	HeatTemp_Arg.Kp=0;
	HeatTemp_Arg.Ki=0;
	HeatTemp_Arg.Kd=0;
	HeatTemp_Arg.Kp_i = 0.1;
    
	CoolTemp_Arg.Kp=0;
	CoolTemp_Arg.Ki=0;
	CoolTemp_Arg.Kd=0;
    CoolTemp_Arg.Kp_i = 0.1;
}
/*
*****************************************************************
 * 函数原型：void CoolTemp_Mode(float dT,int pwm)
 * 功    能：加热制冷切换
*****************************************************************
*/uint8_t Mode,mode;//临时存储当前模式
void CoolTemp_Mode(float dT,float Ctrl_temp,float pwm)
{
	static float T;
//	static 
	
	if(pwm >= 40 && (Ctrl_temp > Cool_Temp.Rel_Temp))
	{
		if(pwm > 50)
			WIND_OFF;
		mode = 0;//加热
	}
	else if(pwm < 40 && (Ctrl_temp < Cool_Temp.Rel_Temp))
	{
		if(pwm < -60)
			WIND_ON;
		mode = 1;//制冷
	}
		
	if(Mode != mode)//如果模式变换了
	{
		T += dT;//开始计时
		if(T <= 1.0f)//一秒没把加热和制冷都拉低不工作
		{
			COLD = 0;
			HEAT = 0;
		}
		else//一秒后将改的模式赋值
		{
			T = 0;
			Mode = mode;
		}
	}
	else//没有改变模式的情况下
	{
		if(Ctrl_temp > Cool_Temp.Rel_Temp)
		{
			HEAT = (int)(ABS(pwm*10));
            COLD = 0;
		}			
		else if(Ctrl_temp < Cool_Temp.Rel_Temp)
		{
            HEAT = 0;
			COLD = (int)(ABS(pwm*10));
		}
        else
        {
            COLD = 0;
			HEAT = 0;
        }
	}
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
 * 函数原型：void setPWM(float duty_cycle)
 * 功    能：设置 PWM 输出（控制加热器）
*****************************************************************
*/
void setPWM(float Ctrl_Temp,float duty_cycle)
{
    if(duty_cycle>100)
        duty_cycle = 100;
    if(duty_cycle<0)
        duty_cycle = 0;
    if(Heat_Temp.Rel_Temp >= Ctrl_Temp)
        duty_cycle = 0;
    UC_HEAT = (int)(duty_cycle*10);
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
bool AutoTunePID(float dT,float temp_ctrl, float *Ku, float *Tu) 
{    
    static float last_temp = 0.0;
    static float peak_time[2] = {0.0, 0.0}; // 记录两个峰值的时间
    
    //使用比例控制
    HeatTemp_Val.Out = HeatTemp_Arg.Kp_i * (temp_ctrl - Heat_Temp.Rel_Temp);
    setPWM(temp_ctrl,HeatTemp_Val.Out);
    
    //检测振荡
    if (Heat_Temp.Rel_Temp > temp_ctrl && last_temp < temp_ctrl) 
    {
        if (oscillation_count < 2) {
            peak_time[oscillation_count] = last_peak_time;
        }
        oscillation_count++;
    }
    last_temp = Heat_Temp.Rel_Temp;
    last_peak_time += dT;

    //计算 Ku 和 Tu
    if (oscillation_count >= 2) 
    {
        *Ku = HeatTemp_Arg.Kp_i;
        *Tu = peak_time[1] - peak_time[0];
        oscillation_count = 0;
        return true; //自动调参完成
    }

    //增加增益
    if(Heat_Temp.Rel_Temp < temp_ctrl)
//        HeatTemp_Arg.Kp_i += 0.01;
    HeatTemp_Arg.Kp_i += 0.1;
    return false; //尚未完成
}
/**********局部变量声明******/
float Ku1 = 0.0;//临界增益
float Tu1 = 0.0;//临界周期

/**********全局变量声明******/
bool tuning_complete1 = false;//自动调参标志位
float last_peak_time1 = 0.0;//上一个周期
int oscillation_count1 = 0;//震荡周期
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
bool AutoCoolTunePID(float dT, float ctrl_Temp,float *Ku, float *Tu) 
{    
    static float last_temp = 0.0;
    static float peak_time[2] = {0.0, 0.0}; // 记录两个峰值的时间
    
    //使用比例控制
    CoolTemp_Val.Out = CoolTemp_Arg.Kp_i * (ctrl_Temp - Cool_Temp.Rel_Temp);
    CoolTemp_Mode(dT,ctrl_Temp,CoolTemp_Val.Out);
    
    //检测振荡
    if (Cool_Temp.Rel_Temp > ctrl_Temp && last_temp < ctrl_Temp) 
    {
        if (oscillation_count1 < 2) {
            peak_time[oscillation_count1] = last_peak_time1;
        }
        oscillation_count1++;
    }
    last_temp = Cool_Temp.Rel_Temp;
    last_peak_time1 += dT;

    //计算 Ku 和 Tu
    if (oscillation_count1 >= 2) 
    {
        *Ku = CoolTemp_Arg.Kp_i;
        *Tu = peak_time[1] - peak_time[0];
        oscillation_count1 = 0;
        return true; //自动调参完成
    }

    //增加增益
//    CoolTemp_Arg.Kp_i += 0.008;
    CoolTemp_Arg.Kp_i += 0.08;
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
	if((sys.SetMode_Option == 0 || sys.SetMode_Option == 3) && sys.Calibration == 0)
	{
		// 自动调参阶段
        if (!tuning_complete) {
            tuning_complete = AutoTunePID(dT,Heat_Temp.Ctrl_Temp, &Ku, &Tu);
            if(tuning_complete)
            {
                HeatTemp_Arg.Kp = 0.6 * Ku;
                HeatTemp_Arg.Ki = 2 * HeatTemp_Arg.Kp_i / Tu;
                HeatTemp_Arg.Kd = HeatTemp_Arg.Kp_i * Tu / 8; 
                HeatTemp_Arg.Kp_i = 0.1;// 初始增益
            }
            return;
        }
        AltPID_Calculation(dT,Heat_Temp.Ctrl_Temp,Heat_Temp.Rel_Temp,&HeatTemp_Arg,&HeatTemp_Val,80,20);   
        setPWM(Heat_Temp.Ctrl_Temp, HeatTemp_Val.Out);
	}
	else
	{
        tuning_complete = false;//自动调参设置为false
        last_peak_time = 0.0;//上一个周期清零
        oscillation_count = 0;//震荡清零
		setPWM(Heat_Temp.Ctrl_Temp,0);
	}
}

void Cool_Temp_Control(float dT)
{ 
	if((sys.SetMode_Option == 0 || sys.SetMode_Option == 3) && sys.Calibration == 0)
	{
        // 自动调参阶段
        if (!tuning_complete1) {
            tuning_complete1 = AutoCoolTunePID(dT, Cool_Temp.Ctrl_Temp,&Ku1, &Tu1);
            if(tuning_complete1)
            {
                CoolTemp_Arg.Kp = 0.6 * Ku1;
                CoolTemp_Arg.Ki = 2 * CoolTemp_Arg.Kp_i / Tu1;
//                CoolTemp_Arg.Kd = CoolTemp_Arg.Kp_i * Tu1 / 8; 
                CoolTemp_Arg.Kp_i = 0.1;// 初始增益
            }
            return;
        }
        AltPID_Calculation(dT,Cool_Temp.Ctrl_Temp,Cool_Temp.Rel_Temp,&CoolTemp_Arg,&CoolTemp_Val,80,20);   
        CoolTemp_Mode(dT,Cool_Temp.Ctrl_Temp,CoolTemp_Val.Out);
	}
    else if(sys.Calibration == 1)
	{
		WIND_OFF;//关闭风扇
		if(sys.Calibration_Step == 0)
		{
			 // 自动调参阶段
            if (!tuning_complete1) {
                tuning_complete1 = AutoCoolTunePID(dT, 260,&Ku1, &Tu1);
                if(tuning_complete1)
                {
                    CoolTemp_Arg.Kp = 0.6 * Ku1;
                    CoolTemp_Arg.Ki = 2 * CoolTemp_Arg.Kp_i / Tu1;
    //                CoolTemp_Arg.Kd = CoolTemp_Arg.Kp_i * Tu1 / 8; 
                    CoolTemp_Arg.Kp_i = 0.1;// 初始增益
                }
                return;
            }
            AltPID_Calculation(dT,260,Cool_Temp.Rel_Temp,&CoolTemp_Arg,&CoolTemp_Val,80,20);   
            CoolTemp_Mode(dT,260,CoolTemp_Val.Out);
		}
		else
		{
			// 自动调参阶段
            if (!tuning_complete1) {
                tuning_complete1 = AutoCoolTunePID(dT, 400,&Ku1, &Tu1);
                if(tuning_complete1)
                {
                    CoolTemp_Arg.Kp = 0.6 * Ku1;
                    CoolTemp_Arg.Ki = 2 * CoolTemp_Arg.Kp_i / Tu1;
    //                CoolTemp_Arg.Kd = CoolTemp_Arg.Kp_i * Tu1 / 8; 
                    CoolTemp_Arg.Kp_i = 0.1;// 初始增益
                }
                return;
            }
            AltPID_Calculation(dT,400,Cool_Temp.Rel_Temp,&CoolTemp_Arg,&CoolTemp_Val,80,20);   
            CoolTemp_Mode(dT,400,CoolTemp_Val.Out);
		}
	}
	else
	{
		WIND_OFF;//关闭风扇
        tuning_complete1 = false;//自动调参设置为false
        last_peak_time1 = 0.0;//上一个周期清零
        oscillation_count1 = 0;//震荡清零
        CoolTemp_Mode(dT,0,0);
	}
}
