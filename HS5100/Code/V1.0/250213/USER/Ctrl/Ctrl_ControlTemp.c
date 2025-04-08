#include "Ctrl_ControlTemp.h"

/**********结构体************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;

/**********局部变量声明******/
// 设置加热盘功率
void set_heating_power(float control_signal) {
    // 根据PID输出控制加热盘功率
    int power = (int)control_signal;  // 将控制信号转为功率（范围0-999）
    if (power < 0) power = 0;  // 限制功率为0
    if (power > 999) power = 999;  // 限制功率为999
    // 根据功率值控制硬件（具体的控制方法根据硬件而定）
    if (Temp.Rel >= Temp.Ctrl)
        power = 0;
    HEAT = power;
}

#define N 10  // MPC 预测步数
#define LAMBDA 0.3  // 控制输入的惩罚因子
#define A 0.6  // 温度衰减系数
#define B 0.4  // 加热功率对温度的影响系数

// 温度模型
float model(float T, float u) {
    return T + A * (u - T) + B * u;
}

// 计算成本函数
float cost_function(float T[], float u[], int16_t T_target) {
    float J = 0;
    for (int i = 0; i < N; i++) {
        J += (T_target - T[i]) * (T_target - T[i]);  // 目标温度的平方误差
        J += LAMBDA * u[i] * u[i];  // 加热功率的惩罚项
    }
    return J;
}

// 动态调整MPC学习率
float adjust_learning_rate(float last_cost, float current_cost, float learning_rate) {
    if (current_cost < last_cost) {
        return learning_rate * 1.05;  // 成本函数下降时增加学习率
    } else {
        return learning_rate * 0.95;  // 成本函数上升时减少学习率
    }
}

// MPC 控制器函数
void mpc_control(float current_temp, float *control_signal, int16_t T_target) {
    float u[N] = {0};  // 控制输入（加热功率）
    float T[N];  // 预测温度
    float learning_rate = 0.01;  // 初始学习率
    int max_iterations = 100;  // 最大迭代次数
    float last_cost = 1000.0;  // 初始成本函数值

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

        // 动态调整学习率
        learning_rate = adjust_learning_rate(last_cost, J, learning_rate);
        last_cost = J;

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
/**********局部变量声明******/
float Ku = 0.0;//临界增益
float Tu = 0.0;//临界周期

/**********全局变量声明******/
bool tuning_complete = false;//自动调参标志位
float last_peak_time = 0.0;//上一个周期
//int oscillation_count = 0;//震荡周期
// PID自动调节
bool AutoTunePID(float dT, float temp_ctrl, float *Ku, float *Tu) {
    static float last_temp = 0.0;
    static float peak_time[2] = {0.0, 0.0};  // 记录两个峰值的时间
    static int oscillation_count = 0;  // 震荡计数

    // 使用比例控制
    Temp_Val.Out = Temp_Arg.Kp_i * (temp_ctrl - Temp.Rel);
    set_heating_power(Temp_Val.Out);

    // 检测振荡
    if (Temp.Rel > temp_ctrl && last_temp < temp_ctrl) {
        if (oscillation_count < 2) {
            peak_time[oscillation_count] = last_peak_time;
        }
        oscillation_count++;
    }
    last_temp = Temp.Rel;
    last_peak_time += dT;

    // 计算 Ku 和 Tu
    if (oscillation_count >= 2) {
        *Ku = Temp_Arg.Kp_i;
        *Tu = peak_time[1] - peak_time[0];
        oscillation_count = 0;
        return true; // 自动调参完成
    }

    // 增加增益
    Temp_Arg.Kp_i += 0.001;
    return false;  // 尚未完成
}

// 温度控制主函数
void Temp_PID(void) {
    Temp_Arg.Kp = 1000*0.001f;
	Temp_Arg.Ki = 8*0.001f;//18
	Temp_Arg.Kd = 90*0.001f;;//控台面
    Temp_Arg.Kp_i = 0.1;  // 初始增益
}
 float control_signal;
     float final_control_signal;
// 台面温度控制
static void Mesa_Ctrl(float dT, int32_t Ctrl_temp) {
    
    float pid_output;
    float mpc_weight = 0.5;  // MPC控制信号的权重（0-1），根据需要调整

//    // 自动调参阶段
//    if (!tuning_complete) {
//        tuning_complete = AutoTunePID(dT, Ctrl_temp, &Ku, &Tu);
//        if (tuning_complete) {
//            Temp_Arg.Kp = 0.6 * Ku;
//            Temp_Arg.Ki = 2 * Temp_Arg.Kp / Tu;
//            Temp_Arg.Kd =Temp_Arg.Kp / Tu/8;
//            Temp_Arg.Kp_i = 0.1;  // 初始增益
//        }
//        return;
//    }

    // 获取PID控制输出
    AltPID_Calculation(dT, Ctrl_temp, Temp.Rel, &Temp_Arg, &Temp_Val, 500, 999);
    pid_output = Temp_Val.Out;

    // MPC控制
    mpc_control(Temp.Rel, &control_signal, Ctrl_temp);

    // 根据权重结合PID和MPC的输出
    final_control_signal = pid_output + mpc_weight * control_signal;
    if (final_control_signal < 0) final_control_signal = 0;  // 防止负值
    if (final_control_signal > 999) final_control_signal = 999;  // 防止超过最大功率

    set_heating_power(final_control_signal);
}

// 温度加热控制
void Temp_Control(float dT) {
    if (sys.Run_Status && PT_VALUE_1_TEMP <= 0) {  // 启动系统控制台面
        if (Temp.Ctrl) {
            Mesa_Ctrl(dT, Temp.Ctrl);
        } else {
            HEAT = 0;  // pwm不输出
        }
    }
}
