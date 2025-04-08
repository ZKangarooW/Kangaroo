#include "Ctrl_ControlTemp.h"

/**********�ṹ��************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;

/**********�ֲ���������******/
// ���ü����̹���
void set_heating_power(float control_signal) {
    // ����PID������Ƽ����̹���
    int power = (int)control_signal;  // �������ź�תΪ���ʣ���Χ0-999��
    if (power < 0) power = 0;  // ���ƹ���Ϊ0
    if (power > 999) power = 999;  // ���ƹ���Ϊ999
    // ���ݹ���ֵ����Ӳ��������Ŀ��Ʒ�������Ӳ��������
    if (Temp.Rel >= Temp.Ctrl)
        power = 0;
    HEAT = power;
}

#define N 10  // MPC Ԥ�ⲽ��
#define LAMBDA 0.3  // ��������ĳͷ�����
#define A 0.6  // �¶�˥��ϵ��
#define B 0.4  // ���ȹ��ʶ��¶ȵ�Ӱ��ϵ��

// �¶�ģ��
float model(float T, float u) {
    return T + A * (u - T) + B * u;
}

// ����ɱ�����
float cost_function(float T[], float u[], int16_t T_target) {
    float J = 0;
    for (int i = 0; i < N; i++) {
        J += (T_target - T[i]) * (T_target - T[i]);  // Ŀ���¶ȵ�ƽ�����
        J += LAMBDA * u[i] * u[i];  // ���ȹ��ʵĳͷ���
    }
    return J;
}

// ��̬����MPCѧϰ��
float adjust_learning_rate(float last_cost, float current_cost, float learning_rate) {
    if (current_cost < last_cost) {
        return learning_rate * 1.05;  // �ɱ������½�ʱ����ѧϰ��
    } else {
        return learning_rate * 0.95;  // �ɱ���������ʱ����ѧϰ��
    }
}

// MPC ����������
void mpc_control(float current_temp, float *control_signal, int16_t T_target) {
    float u[N] = {0};  // �������루���ȹ��ʣ�
    float T[N];  // Ԥ���¶�
    float learning_rate = 0.01;  // ��ʼѧϰ��
    int max_iterations = 100;  // ����������
    float last_cost = 1000.0;  // ��ʼ�ɱ�����ֵ

    // ��ʼ�¶�Ԥ��
    T[0] = current_temp;
    for (int i = 1; i < N; i++) {
        T[i] = model(T[i-1], u[i-1]);
    }

    // �����Ż���������
    for (int iter = 0; iter < max_iterations; iter++) {
        // ���㵱ǰ�¶�Ԥ��
        for (int i = 1; i < N; i++) {
            T[i] = model(T[i-1], u[i-1]);
        }

        // ����ɱ�����
        float J = cost_function(T, u, T_target);

        // ��̬����ѧϰ��
        learning_rate = adjust_learning_rate(last_cost, J, learning_rate);
        last_cost = J;

        // �ݶ��½����¿�������u
        for (int i = 0; i < N; i++) {
            float grad_u = 2 * (T[i] - T_target) * (-A * (T[i-1] - T[i]) - B) + 2 * LAMBDA * u[i];
            u[i] -= learning_rate * grad_u;
        }

        // ��ӡ��ǰ��������ͳɱ�����ֵ
//        printf("Iteration %d, Cost: %.4f, u[0]: %.4f\n", iter, J, u[0]);

        // ����Ƿ�����ֹͣ����������ɱ��������ٱ仯��
        if (J < 0.01) {
            break;
        }
    }

    // �������ſ�������
    *control_signal = u[0];
}
/**********�ֲ���������******/
float Ku = 0.0;//�ٽ�����
float Tu = 0.0;//�ٽ�����

/**********ȫ�ֱ�������******/
bool tuning_complete = false;//�Զ����α�־λ
float last_peak_time = 0.0;//��һ������
//int oscillation_count = 0;//������
// PID�Զ�����
bool AutoTunePID(float dT, float temp_ctrl, float *Ku, float *Tu) {
    static float last_temp = 0.0;
    static float peak_time[2] = {0.0, 0.0};  // ��¼������ֵ��ʱ��
    static int oscillation_count = 0;  // �𵴼���

    // ʹ�ñ�������
    Temp_Val.Out = Temp_Arg.Kp_i * (temp_ctrl - Temp.Rel);
    set_heating_power(Temp_Val.Out);

    // �����
    if (Temp.Rel > temp_ctrl && last_temp < temp_ctrl) {
        if (oscillation_count < 2) {
            peak_time[oscillation_count] = last_peak_time;
        }
        oscillation_count++;
    }
    last_temp = Temp.Rel;
    last_peak_time += dT;

    // ���� Ku �� Tu
    if (oscillation_count >= 2) {
        *Ku = Temp_Arg.Kp_i;
        *Tu = peak_time[1] - peak_time[0];
        oscillation_count = 0;
        return true; // �Զ��������
    }

    // ��������
    Temp_Arg.Kp_i += 0.001;
    return false;  // ��δ���
}

// �¶ȿ���������
void Temp_PID(void) {
    Temp_Arg.Kp = 1000*0.001f;
	Temp_Arg.Ki = 8*0.001f;//18
	Temp_Arg.Kd = 90*0.001f;;//��̨��
    Temp_Arg.Kp_i = 0.1;  // ��ʼ����
}
 float control_signal;
     float final_control_signal;
// ̨���¶ȿ���
static void Mesa_Ctrl(float dT, int32_t Ctrl_temp) {
    
    float pid_output;
    float mpc_weight = 0.5;  // MPC�����źŵ�Ȩ�أ�0-1����������Ҫ����

//    // �Զ����ν׶�
//    if (!tuning_complete) {
//        tuning_complete = AutoTunePID(dT, Ctrl_temp, &Ku, &Tu);
//        if (tuning_complete) {
//            Temp_Arg.Kp = 0.6 * Ku;
//            Temp_Arg.Ki = 2 * Temp_Arg.Kp / Tu;
//            Temp_Arg.Kd =Temp_Arg.Kp / Tu/8;
//            Temp_Arg.Kp_i = 0.1;  // ��ʼ����
//        }
//        return;
//    }

    // ��ȡPID�������
    AltPID_Calculation(dT, Ctrl_temp, Temp.Rel, &Temp_Arg, &Temp_Val, 500, 999);
    pid_output = Temp_Val.Out;

    // MPC����
    mpc_control(Temp.Rel, &control_signal, Ctrl_temp);

    // ����Ȩ�ؽ��PID��MPC�����
    final_control_signal = pid_output + mpc_weight * control_signal;
    if (final_control_signal < 0) final_control_signal = 0;  // ��ֹ��ֵ
    if (final_control_signal > 999) final_control_signal = 999;  // ��ֹ���������

    set_heating_power(final_control_signal);
}

// �¶ȼ��ȿ���
void Temp_Control(float dT) {
    if (sys.Run_Status && PT_VALUE_1_TEMP <= 0) {  // ����ϵͳ����̨��
        if (Temp.Ctrl) {
            Mesa_Ctrl(dT, Temp.Ctrl);
        } else {
            HEAT = 0;  // pwm�����
        }
    }
}
