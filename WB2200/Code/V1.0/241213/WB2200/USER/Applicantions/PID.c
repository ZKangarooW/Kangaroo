#include "PID.h"
// ȫ�ֱ�����ģ��ʵ��ϵͳ��
float process_variable = 0.0; // ϵͳ�������ˮ�£�
float control_signal = 0.0;   // �����ź�
float setpoint = 370;        // Ŀ��ֵ
float Ku = 0.0;               // �ٽ�����
float Tu = 0.0;               // �ٽ�����

// ģ���ȡ�¶ȴ�����ֵ��ʵ�����滻Ϊ ADC �������ӿڣ�
float readTemperature() {
    // ʾ�����룬ʵ��ϵͳӦ�滻Ϊ�������ɼ��߼�
    process_variable = Temp.Rel;
    return process_variable;
}

// ���� PWM ��������Ƽ�������
void setPWM(float duty_cycle) {
    if (duty_cycle < 0) duty_cycle = 0;
    if (duty_cycle > 200) duty_cycle = 200;
    HEAT = duty_cycle;
}


float Kp = 0.1;        // ��ʼ����
float Ki;
float Kd;
// �Զ�����ģ��
bool autoTunePID(float dt, float *Ku, float *Tu) {
    static float last_peak_time = 0.0;
    static int oscillation_count = 0;
    static float last_temp = 0.0;
    static float peak_time[2] = {0.0, 0.0}; // ��¼������ֵ��ʱ��

    // ʹ�ñ�������
    control_signal = Kp * (setpoint - process_variable);
    if(control_signal>200)
        control_signal = 200;
    setPWM(control_signal);
    process_variable = readTemperature();

    // �����
    if (process_variable > setpoint && last_temp < setpoint) {
        if (oscillation_count < 2) {
            peak_time[oscillation_count] = last_peak_time;
        }
        oscillation_count++;
    }
    last_temp = process_variable;
    last_peak_time += dt;

    // ���� Ku �� Tu
    if (oscillation_count >= 2) {
        *Ku = Kp;
        *Tu = peak_time[1] - peak_time[0];
        return true; // �Զ��������
    }

    // ��������
    Kp += 0.005;
    return false; // ��δ���
}

// PID ����ģ��
float pidControl(float error, float dt, float Kp, float Ki, float Kd) {
    static float integral = 0.0;
    static float last_error = 0.0;

    // PID ����
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
// �����Ⱥ���
void controlLoop(void) {
    static int cycle_count = 0;
    static bool tuning_complete = false;

    float dt = 0.1; // 100ms
    float error = setpoint - process_variable;

    // �Զ����ν׶�
    if (!tuning_complete) {
        tuning_complete = autoTunePID(dt, &Ku, &Tu);
        if (tuning_complete) {
//            printf("�Զ��������: Ku = %.2f, Tu = %.2f\n", Ku, Tu);
            falg = 1;
        }
        return;
    }

    // ʹ�� Ziegler-Nichols ������� PID ����
     Kp = 0.6 * Ku;
     Ki = 2 * Kp / Tu;
//     Kd = Kp * Tu / 8;

    // PID ����
    control_signal = pidControl(error, dt, Kp, Ki, Kd);
    
    // �������ź�ӳ�䵽 PWM ��Χ��0-100%��
    setPWM(control_signal);
    
    // ��ȡ�¶ȴ�����ֵ
    process_variable = readTemperature();
    
    // ��ӡ������Ϣ
    if (cycle_count % 10 == 0) { // ÿ���ӡһ��
        falg1 = 1;
//        printf("����: %d, ��ǰ�¶�: %.2f, �����ź�: %.2f\n", cycle_count, process_variable, control_signal);
    }

    cycle_count++;
}
