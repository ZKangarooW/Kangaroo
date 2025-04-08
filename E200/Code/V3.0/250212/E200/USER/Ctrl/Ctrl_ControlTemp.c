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
	HeatTemp_Arg.Kp=3.75;
	HeatTemp_Arg.Ki=0.0798;
	HeatTemp_Arg.Kd=0;
	HeatTemp_Arg.Kp_i = 0.3;
    
	CoolTemp_Arg.Kp=3.15;
	CoolTemp_Arg.Ki=0.0116;
	CoolTemp_Arg.Kd=0;
    CoolTemp_Arg.Kp_i = 0.3;
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
	static float T1;
	
	if(pwm >= 10 && (Ctrl_temp > Cool_Temp.Rel_Temp))
	{
		mode = 0;//加热
	}
	else if(pwm < -10 && (Ctrl_temp < Cool_Temp.Rel_Temp))
	{
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
        if(Mode == 1)//制冷
        {
            if(pwm < -60)
            {
                T1 +=dT;
                if(T1 > 10.0)
                {
                    T1 = 0;
                    WIND_ON;
                }
            }
            else if(pwm > 10)
            {
                T1 +=dT;
                if(T1 > 10.0)
                {
                    T1 = 0;
                    WIND_OFF;
                }
            }
            else
            {
                T1 = 0;
            }
                
            if(Ctrl_temp < Cool_Temp.Rel_Temp && pwm <0)
            {
                HEAT = 0;
                COLD = (int)(ABS(pwm*10));
            }
            else
            {
                HEAT = 0;
                COLD = 0;
            }
        }
        else
        {
            if(pwm > 50)
                WIND_OFF;
            if(Ctrl_temp > Cool_Temp.Rel_Temp&& pwm >0)
            {
                HEAT = (int)(pwm*10);
                COLD = 0;
            }
            else
            {
                HEAT = 0;
                COLD = 0;
            } 
        }
	}
}

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
 * 函数原型：void Temp_Control(float dT)
 * 功    能：温度加热控制
*****************************************************************
*/
void Temp_Control(float dT)
{ 
	if((sys.SetMode_Option == 0 || sys.SetMode_Option == 3) && sys.Calibration == 0)
	{
        AltPID_Calculation(dT,Heat_Temp.Ctrl_Temp,Heat_Temp.Rel_Temp,&HeatTemp_Arg,&HeatTemp_Val,80,20);   
        setPWM(Heat_Temp.Ctrl_Temp, HeatTemp_Val.Out);
	}
	else
	{
		setPWM(Heat_Temp.Ctrl_Temp,0);
	}
}

void Cool_Temp_Control(float dT)
{ 
	if((sys.SetMode_Option == 0 || sys.SetMode_Option == 3) && sys.Calibration == 0)
	{
        AltPID_Calculation(dT,Cool_Temp.Ctrl_Temp,Cool_Temp.Rel_Temp,&CoolTemp_Arg,&CoolTemp_Val,80,20);   
        CoolTemp_Mode(dT,Cool_Temp.Ctrl_Temp,CoolTemp_Val.Out);
	}
    else if(sys.Calibration == 1)
	{
		WIND_OFF;//关闭风扇
		if(sys.Calibration_Step == 0)
		{
            AltPID_Calculation(dT,260,Cool_Temp.Rel_Temp,&CoolTemp_Arg,&CoolTemp_Val,80,20);   
            CoolTemp_Mode(dT,260,CoolTemp_Val.Out);
		}
		else
		{
            AltPID_Calculation(dT,400,Cool_Temp.Rel_Temp,&CoolTemp_Arg,&CoolTemp_Val,80,20);   
            CoolTemp_Mode(dT,400,CoolTemp_Val.Out);
		}
	}
	else
	{
		WIND_OFF;//关闭风扇
        CoolTemp_Mode(dT,0,0);
	}
}
