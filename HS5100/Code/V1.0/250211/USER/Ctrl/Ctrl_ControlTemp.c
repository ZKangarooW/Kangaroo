#include "Ctrl_ControlTemp.h"

/**********结构体************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;

/**********局部变量声明******/

// 设置加热盘功率
void set_heating_power(float control_signal) {
    // 根据PID输出控制加热盘功率
    int power = (int)control_signal;  // 将控制信号转为功率（范围0-255）
    if (power < 0) power = 0;  // 限制功率为0
    if (power > 399) power = 399;  // 限制功率为255
    // 根据功率值控制硬件（具体的控制方法根据硬件而定）
    HEAT = power;
}

#define N 10  // MPC 预测步数
#define LAMBDA 0.3  // 控制输入的惩罚因子
#define A 0.6  // 温度衰减系数//0.6
#define B 0.4  // 加热功率对温度的影响系数

// 温度模型
float model(float T, float u) {
    return T + A * (u - T) + B * u;
}

// 计算成本函数
float cost_function(float T[], float u[],int16_t T_target) {
    float J = 0;
    for (int i = 0; i < N; i++) {
        J += (T_target - T[i]) * (T_target - T[i]);  // 目标温度的平方误差
        J += LAMBDA * u[i] * u[i];  // 加热功率的惩罚项
    }
    return J;
}

// MPC 控制器函数
void mpc_control(float current_temp, float *control_signal,int16_t T_target) {
    float u[N] = {0};  // 控制输入（加热功率）
    float T[N];  // 预测温度
    float learning_rate = 0.01;  // 学习率
    int max_iterations = 100;  // 最大迭代次数

    // 初始温度预测
    T[0] = current_temp;
    for (int i = 1; i < N; i++) {
        T[i] = model(T[i-1], u[i-1]);
    }

    // 迭代优化控制输入
    for (int iter = 0; iter < max_iterations; iter++) {
        // 计算当前温度预测
        for (int i = 1; i < N; i++) {
            T[i] = model(T[i-1], u[i-1]);
        }

        // 计算成本函数
        float J = cost_function(T, u, T_target);

        // 梯度下降更新控制输入u
        for (int i = 0; i < N; i++) {
            float grad_u = 2 * (T[i] - T_target) * (-A * (T[i-1] - T[i]) - B) + 2 * LAMBDA * u[i];
            u[i] -= learning_rate * grad_u;
        }

        // 打印当前控制输入和成本函数值
//        printf("Iteration %d, Cost: %.4f, u[0]: %.4f\n", iter, J, u[0]);

        // 检查是否满足停止条件（例如成本函数不再变化）
        if (J < 0.01) {
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
}

/*
*****************************************************************
 * 函数原型：static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
 * 功    能：台面温度控制
*****************************************************************
*/float control_signal;
float final_control_signal;
static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
{
    static float T;
    static float T1;
    mpc_control(Temp.Rel, &control_signal,Ctrl_temp);
    AltPID_Calculation(dT, Ctrl_temp, Temp.Rel, &Temp_Arg, &Temp_Val, 100, 300);
    final_control_signal = (control_signal/1000) + Temp_Val.Out;
    
    set_heating_power(final_control_signal);
}

/*
*****************************************************************
 * 函数原型：void Temp_Control(float dT)
 * 功    能：温度加热控制
*****************************************************************
*/
void Temp_Control(float dT)
{ 
    if(sys.Run_Status && PT_VALUE_1_TEMP <= 0)//启动系统控制台面
	{
		if(Temp.Ctrl)
		{
			Mesa_Ctrl(dT, Temp.Ctrl);
		}
		else
		{
			HEAT = 0;//pwm不输出
		}
	}
}
