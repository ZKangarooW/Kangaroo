#include "Ctrl_ControlTemp.h"

/**********结构体************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val[Motor_Num];
_PID_Arg_ W_Temp_Arg;
_PID_Val_ W_Temp_Val[Motor_Num];

/**********局部变量声明******/
uint8_t Temp_type[Motor_Num];//温度类型
int8_t HEAT_PWM[Motor_Num];//各个发热盘的功率

void Heat_Out(int8_t Heat[Motor_Num])
{
    HEAT5 = (int8_t)Heat[0];
    HEAT0 = (int8_t)Heat[1];
    HEAT4 = (int8_t)Heat[2];
    HEAT2 = (int8_t)Heat[3];
	HEAT1 = (int8_t)Heat[4];
    HEAT3 = (int8_t)Heat[5];
}

/*
*****************************************************************
 * 函数原型：static void Set_Heating_Power(float pwm)
 * 功    能：设置加热盘功率
 * 输    入: 加热的pwm功率 
 * 参    数：float control_signal
*****************************************************************
*/
static void Set_Heating_Power(uint8_t i,float pwm)
{
    // 根据PID输出控制加热盘功率
    int power = (int)pwm;  // 将控制信号转为功率（范围0-255）
    if (power < 0) power = 0;  // 限制功率为0
    if (power > 399) power = 399;  // 限制功率为255
    // 根据功率值控制硬件（具体的控制方法根据硬件而定）
	HEAT_PWM[i] = power;
}

/*
*****************************************************************
 * 函数原型：void Temp_PID(void)
 * 功    能：温度控制PID系数
*****************************************************************
*/
void Temp_PID(void)
{
	Temp_Arg.Kp = 1000*0.001f;
	Temp_Arg.Ki = 8*0.001f;//18
	Temp_Arg.Kd = 30*0.001f;;//控台面
    
    W_Temp_Arg.Kp = 2000*0.001f;
    W_Temp_Arg.Ki = 32*0.001f;//18
    W_Temp_Arg.Kd = 90*0.001f;;//控水温
}

/*
*****************************************************************
 * 函数原型：static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
 * 功    能：台面温度控制
*****************************************************************
*/
static void Mesa_Ctrl(float dT, uint8_t i, int32_t Ctrl_temp)
{
    AltPID_Calculation(dT, Ctrl_temp, Work_Num[i].Temp.Mesa, &Temp_Arg, &Temp_Val[i], 100, 300);
    Set_Heating_Power(i, Temp_Val[i].Out);
}

/*
*****************************************************************
 * 函数原型：static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
 * 功    能：控制台面得温度
*****************************************************************
*/
void set_Mesa_power(float dT, uint8_t i, float control_signal) 
{
    // 根据输入温度控制加热盘功率
    int power = (int)control_signal;  // 将控制信号转为功率（范围0-255）
    if (power < Work_Num[i].Temp.Ctrl) power = Work_Num[i].Temp.Ctrl;  // 限制功率为0
    if (power > Temp_MAX) power = Temp_MAX;  // 限制功率为255
    // 根据功率值控制硬件（具体的控制方法根据硬件而定）
    if(Work_Num[i].Temp.Rel>Work_Num[i].Temp.Ctrl)
    {
        power = 0;
    }
    else
    {
        Mesa_Ctrl(dT, i, power);
    }
}

/*
*****************************************************************
 * 函数原型：static void Water_Ctrl(float dT, int32_t Ctrl_temp)
 * 功    能：控制水温
*****************************************************************
*/
static void Water_Ctrl(float dT, uint8_t i, int32_t Ctrl_temp)
{
	if(Work_Num[i].Temp.Rel<Work_Num[i].Temp.Ctrl-30)
	{
		IncPID_Calculation(dT, Ctrl_temp, Work_Num[i].Temp.Outside, &W_Temp_Arg, &W_Temp_Val[i],30, 300);
		set_Mesa_power(dT,i,Work_Num[i].Temp.Ctrl*1.7+W_Temp_Val[i].Out);
	} 
	else
	{
		IncPID_Calculation(dT, Ctrl_temp, Work_Num[i].Temp.Outside, &W_Temp_Arg, &W_Temp_Val[i],30, 300);
		set_Mesa_power(dT,i,Ctrl_temp+W_Temp_Val[i].Out);
	}
}

/*
*****************************************************************
 * 函数原型：void Temp_Control(float dT)
 * 功    能：温度加热控制
*****************************************************************
*/
void Temp_Control(float dT)
{ 
	for(uint8_t i = 0;i<Motor_Num;i++)
    {
		if(Work_Num[i].Run_Status && PT_VALUE_1_TEMP[i] >= 2200)//启动系统控制台面
		{
			if(Work_Num[i].Temp.Ctrl)
			{
				if(Temp_type[i] == 1)//如果是外部探头切换过来
				{
					Work_Num[i].Temp.ADDMode = 0;
					Temp_type[i] = 0;
				}
				Mesa_Ctrl(dT,i, Work_Num[i].Temp.Ctrl);
			}
			else
			{
				HEAT_PWM[i] = 0;//pwm不输出
			}
		}
		else if(Work_Num[i].Run_Status && PT_VALUE_1_TEMP[i] < 2200)//启动系统控制水温
		{
			if(Work_Num[i].Temp.Ctrl)
			{	
				if(Temp_type[i] == 0)//如果是台面探头切换过来
				{
					Work_Num[i].Temp.ADDMode = 0;
					Temp_type[i] = 1;
				}
				Water_Ctrl(dT, i, Work_Num[i].Temp.Ctrl);
			}
			else
			{
				HEAT_PWM[i] = 0;//pwm不输出
			}
		}
		else
		{
			HEAT_PWM[i] = 0;//pwm不输出
		}
	}
	Heat_Out(HEAT_PWM);
}

/**
 * @brief 温度任务
 * 
 */
void Temp_Task(void *p)
{
    TickType_t xLastWakeTime;//刚开始唤醒的时间
    xLastWakeTime = xTaskGetTickCount ();
    
    Temp_PID();
    
    while(1)
    {
        Temp_Control(0.01f);
        vTaskDelayUntil(&xLastWakeTime, 10);
    }
}

