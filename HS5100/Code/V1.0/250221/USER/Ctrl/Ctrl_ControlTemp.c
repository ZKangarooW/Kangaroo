#include "Ctrl_ControlTemp.h"

/**********结构体************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;
_PID_Arg_ W_Temp_Arg;
_PID_Val_ W_Temp_Val;


#define N 10  // MPC 预测步数
#define LAMBDA 0.3  // 控制输入的惩罚因子
#define A 0.6  // 温度衰减系数//0.6
#define B 0.4  // 加热功率对温度的影响系数

/**********局部变量声明******/
uint8_t Temp_type;//温度类型

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
    if (power < 0) power = 0;  // 限制功率为0
    if (power > 399) power = 399;  // 限制功率为255
    // 根据功率值控制硬件（具体的控制方法根据硬件而定）
    HEAT = power;
}

/*
*****************************************************************
 * 函数原型：float Temp_Model(float T, float u)
 * 功    能：温度模型,用于mpc比较
 * 输    入: T：预测温度，u：控制输入（加热功率）
 * 输    出：预测到的温度
 * 参    数：float T, float u
*****************************************************************
*/
float Temp_Model(float T, float u)
{
    return T + A * (u - T) + B * u;
}

/*
*****************************************************************
 * 函数原型：float Cost_Function(float T[], float u[],int16_t Temp_Ctrl)
 * 功    能：计算成本函数
 * 输    入: T：预测温度，u：控制输入（加热功率）, Temp_Ctrl：控制温度
 * 输    出：加热功率的惩罚项
 * 参    数：float T[], float u[],int16_t Temp_Ctrl
*****************************************************************
*/
float Cost_Function(float T[], float u[],int16_t Temp_Ctrl)
{
    float J = 0;
    for (int i = 0; i < N; i++) 
    {
        J += (Temp_Ctrl - T[i]) * (Temp_Ctrl - T[i]); // 目标温度的平方误差
        J += LAMBDA * u[i] * u[i];  // 加热功率的惩罚项
    }
    return J;
}

/*
*****************************************************************
 * 函数原型：void MPC_Control(float Temp_Rel, float *control_signal,int16_t v)
 * 功    能：MPC 控制器函数
 * 输    入: Temp_Rel：实际温度，control_signal：加热功率, Temp_Ctrl：控制温度
 * 参    数：float Temp_Rel, float *control_signal,int16_t Temp_Ctrl
*****************************************************************
*/
void MPC_Control(float Temp_Rel, float *control_signal,int16_t Temp_Ctrl)
{
    float u[N] = {0};  // 控制输入（加热功率）
    float T[N];  // 预测温度
    float learning_rate = 0.01;  // 学习率
    int max_iterations = 100;  // 最大迭代次数

    // 初始温度预测
    T[0] = Temp_Rel;
    for (int i = 1; i < N; i++) 
    {
        T[i] = Temp_Model(T[i-1], u[i-1]);
    }

    // 迭代优化控制输入
    for (int iter = 0; iter < max_iterations; iter++) 
    {
        // 计算当前温度预测
        for (int i = 1; i < N; i++) {
            T[i] = Temp_Model(T[i-1], u[i-1]);
        }
        // 计算成本函数
        float J = Cost_Function(T, u, Temp_Ctrl);
        // 梯度下降更新控制输入u
        for (int i = 0; i < N; i++) {
            float grad_u = 2 * (T[i] - Temp_Ctrl) * (-A * (T[i-1] - T[i]) - B) + 2 * LAMBDA * u[i];
            u[i] -= learning_rate * grad_u;
        }
        // 打印当前控制输入和成本函数值
//        printf("Iteration %d, Cost: %.4f, u[0]: %.4f\n", iter, J, u[0]);
        // 检查是否满足停止条件（例如成本函数不再变化）
        if (J < 0.01) 
        {
            break;
        }
    }
    // 返回最优控制输入
    *control_signal = u[0];
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
	Temp_Arg.Kd = 90*0.001f;;//控台面
    
    W_Temp_Arg.Kp = 20000*0.001f;
    W_Temp_Arg.Ki = 80*0.001f;//18
	W_Temp_Arg.Kd = 900*0.001f;;//控台面
}

/*
*****************************************************************
 * 函数原型：static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
 * 功    能：台面温度控制
*****************************************************************
*/
static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
{
    float control_signal;
    float final_control_signal;
    MPC_Control(Temp.Mesa, &control_signal,Ctrl_temp);
    AltPID_Calculation(dT, Ctrl_temp, Temp.Mesa, &Temp_Arg, &Temp_Val, 100, 300);
    final_control_signal = (control_signal/1000) + Temp_Val.Out;
    Set_Heating_Power(final_control_signal);
}

/*
*****************************************************************
 * 函数原型：static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
 * 功    能：控制台面得温度
*****************************************************************
*/
void set_Mesa_power(float dT,float control_signal) 
{
    // 根据输入温度控制加热盘功率
    int power = (int)control_signal;  // 将控制信号转为功率（范围0-255）
    if (power < Temp.Ctrl) power = Temp.Ctrl;  // 限制功率为0
    if (power > Temp_MAX) power = Temp_MAX;  // 限制功率为255
    // 根据功率值控制硬件（具体的控制方法根据硬件而定）
    if(Temp.Rel>Temp.Ctrl)
    {
        HEAT = 0;
    }
    else
    {
        Mesa_Ctrl(dT, power);
    }
}

/*
*****************************************************************
 * 函数原型：static void Water_Ctrl(float dT, int32_t Ctrl_temp)
 * 功    能：控制水温
*****************************************************************
*/
static void Water_Ctrl(float dT, int32_t Ctrl_temp)
{
    if(Temp.Up_Speed == 1)//快速
    {
        if(Temp.Rel<Temp.Ctrl-50)
        {
            set_Mesa_power(dT,Temp.Ctrl*3.5);
            IncPID_Calculation(dT, Ctrl_temp, Temp.Outside, &W_Temp_Arg, &W_Temp_Val,10, 300);
        } 
        else
        {
            IncPID_Calculation(dT, Ctrl_temp, Temp.Outside, &W_Temp_Arg, &W_Temp_Val,10, 300);
            set_Mesa_power(dT,Ctrl_temp+W_Temp_Val.Out);
        }
    }
    else if(Temp.Up_Speed == 2)//慢速
    {
        if(Temp.Rel<Temp.Ctrl-100)
        {
            set_Mesa_power(dT,Temp.Ctrl*2.8);
        } 
        else if(Temp.Rel<Temp.Ctrl-60)
        {
            set_Mesa_power(dT,Temp.Ctrl*2.5);
        } 
        else if(Temp.Rel<Temp.Ctrl-30)
        {
            set_Mesa_power(dT,Temp.Ctrl*2.1);
            IncPID_Calculation(dT, Ctrl_temp, Temp.Outside, &W_Temp_Arg, &W_Temp_Val,10, 300);
        } 
        else
        {
            IncPID_Calculation(dT, Ctrl_temp, Temp.Outside, &W_Temp_Arg, &W_Temp_Val,10, 300);
            set_Mesa_power(dT,Ctrl_temp+W_Temp_Val.Out);
        }
    }
    else//正常
    {
        if(Temp.Rel<Temp.Ctrl-100)
        {
            set_Mesa_power(dT,Temp.Ctrl*3.5);
        } 
        else if(Temp.Rel<Temp.Ctrl-60)
        {
            set_Mesa_power(dT,Temp.Ctrl*3.0);
        } 
        else if(Temp.Rel<Temp.Ctrl-30)
        {
            set_Mesa_power(dT,Temp.Ctrl*2.5);
            IncPID_Calculation(dT, Ctrl_temp, Temp.Outside, &W_Temp_Arg, &W_Temp_Val,10, 300);
        } 
        else
        {
            IncPID_Calculation(dT, Ctrl_temp, Temp.Outside, &W_Temp_Arg, &W_Temp_Val,10, 300);
            set_Mesa_power(dT,Ctrl_temp+W_Temp_Val.Out);
        }
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
    if(sys.Run_Status && PT_VALUE_1_TEMP >= 2400)//启动系统控制台面
	{
        if(Temp.Ctrl)
        {
            if(Temp_type == 1)//如果是外部探头切换过来
            {
                Temp.ADDMode = 0;
                Temp_type = 0;
            }
            Mesa_Ctrl(dT, Temp.Ctrl);
        }
        else
        {
            HEAT = 0;//pwm不输出
        }
	}
    else if(sys.Run_Status && PT_VALUE_1_TEMP < 2400)//启动系统控制水温
	{
        if(Temp.Ctrl)
		{	
            if(Temp_type == 0)//如果是台面探头切换过来
			{
				Temp.ADDMode = 0;
				Temp_type = 1;
			}
            Water_Ctrl(dT, Temp.Ctrl);
        }
        else
		{
			HEAT = 0;//pwm不输出
		}
    }
    else
	{
		HEAT = 0;//pwm不输出
	}
}
