#include "PID.h"
// 全局变量（模拟实际系统）
float process_variable = 0.0; // 系统输出（如水温）
float control_signal = 0.0;   // 控制信号
float setpoint = 370;        // 目标值
float Ku = 0.0;               // 临界增益
float Tu = 0.0;               // 临界周期

// 模拟读取温度传感器值（实际需替换为 ADC 或其他接口）
float readTemperature() {
    // 示例代码，实际系统应替换为传感器采集逻辑
    process_variable = Temp.Rel;
    return process_variable;
}

// 设置 PWM 输出（控制加热器）
void setPWM(float duty_cycle) {
    if (duty_cycle < 0) duty_cycle = 0;
    if (duty_cycle > 200) duty_cycle = 200;
    HEAT = duty_cycle;
}


float Kp = 0.1;        // 初始增益
float Ki;
float Kd;
// 自动调参模块
bool autoTunePID(float dt, float *Ku, float *Tu) {
    static float last_peak_time = 0.0;
    static int oscillation_count = 0;
    static float last_temp = 0.0;
    static float peak_time[2] = {0.0, 0.0}; // 记录两个峰值的时间

    // 使用比例控制
    control_signal = Kp * (setpoint - process_variable);
    if(control_signal>200)
        control_signal = 200;
    setPWM(control_signal);
    process_variable = readTemperature();

    // 检测振荡
    if (process_variable > setpoint && last_temp < setpoint) {
        if (oscillation_count < 2) {
            peak_time[oscillation_count] = last_peak_time;
        }
        oscillation_count++;
    }
    last_temp = process_variable;
    last_peak_time += dt;

    // 计算 Ku 和 Tu
    if (oscillation_count >= 2) {
        *Ku = Kp;
        *Tu = peak_time[1] - peak_time[0];
        return true; // 自动调参完成
    }

    // 增加增益
    Kp += 0.005;
    return false; // 尚未完成
}

// PID 控制模块
float pidControl(float error, float dt, float Kp, float Ki, float Kd) {
    static float integral = 0.0;
    static float last_error = 0.0;

    // PID 计算
    integral += error * dt;
    if(integral>200)
        integral = 200;
    if(integral < -200)
        integral = -200;
    float derivative = (error - last_error) / dt;
    float output = Kp * error + Ki * integral + Kd * derivative;
    last_error = error;

    return output;
}

uint8_t falg = 0;
uint8_t falg1 = 0;
// 主调度函数
void controlLoop(void) {
    static int cycle_count = 0;
    static bool tuning_complete = false;

    float dt = 0.1; // 100ms
    float error = setpoint - process_variable;

    // 自动调参阶段
    if (!tuning_complete) {
        tuning_complete = autoTunePID(dt, &Ku, &Tu);
        if (tuning_complete) {
//            printf("自动调参完成: Ku = %.2f, Tu = %.2f\n", Ku, Tu);
            falg = 1;
        }
        return;
    }

    // 使用 Ziegler-Nichols 规则计算 PID 参数
     Kp = 0.6 * Ku;
     Ki = 2 * Kp / Tu;
//     Kd = Kp * Tu / 8;

    // PID 控制
    control_signal = pidControl(error, dt, Kp, Ki, Kd);
    
    // 将控制信号映射到 PWM 范围（0-100%）
    setPWM(control_signal);
    
    // 读取温度传感器值
    process_variable = readTemperature();
    
    // 打印调试信息
    if (cycle_count % 10 == 0) { // 每秒打印一次
        falg1 = 1;
//        printf("周期: %d, 当前温度: %.2f, 控制信号: %.2f\n", cycle_count, process_variable, control_signal);
    }

    cycle_count++;
}
