#include "Ctrl_ControlTemp.h"

/**********�ṹ��************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;

/**********�ֲ���������******/

// ���ü����̹���
void set_heating_power(float control_signal) {
    // ����PID������Ƽ����̹���
    int power = (int)control_signal;  // �������ź�תΪ���ʣ���Χ0-255��
    if (power < 0) power = 0;  // ���ƹ���Ϊ0
    if (power > 399) power = 399;  // ���ƹ���Ϊ255
    // ���ݹ���ֵ����Ӳ��������Ŀ��Ʒ�������Ӳ��������
    HEAT = power;
}

#define N 10  // MPC Ԥ�ⲽ��
#define LAMBDA 0.3  // ��������ĳͷ�����
#define A 0.6  // �¶�˥��ϵ��//0.6
#define B 0.4  // ���ȹ��ʶ��¶ȵ�Ӱ��ϵ��

// �¶�ģ��
float model(float T, float u) {
    return T + A * (u - T) + B * u;
}

// ����ɱ�����
float cost_function(float T[], float u[],int16_t T_target) {
    float J = 0;
    for (int i = 0; i < N; i++) {
        J += (T_target - T[i]) * (T_target - T[i]);  // Ŀ���¶ȵ�ƽ�����
        J += LAMBDA * u[i] * u[i];  // ���ȹ��ʵĳͷ���
    }
    return J;
}

// MPC ����������
void mpc_control(float current_temp, float *control_signal,int16_t T_target) {
    float u[N] = {0};  // �������루���ȹ��ʣ�
    float T[N];  // Ԥ���¶�
    float learning_rate = 0.01;  // ѧϰ��
    int max_iterations = 100;  // ����������

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

/*
*****************************************************************
 * ����ԭ�ͣ�void Temp_PID(void)
 * ��    �ܣ��¶ȿ���PIDϵ��
*****************************************************************
*/
void Temp_PID(void)
{
	Temp_Arg.Kp = 1000*0.001f;
	Temp_Arg.Ki = 8*0.001f;//18
	Temp_Arg.Kd = 90*0.001f;;//��̨��
}

/*
*****************************************************************
 * ����ԭ�ͣ�static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
 * ��    �ܣ�̨���¶ȿ���
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
 * ����ԭ�ͣ�void Temp_Control(float dT)
 * ��    �ܣ��¶ȼ��ȿ���
*****************************************************************
*/
void Temp_Control(float dT)
{ 
    if(sys.Run_Status && PT_VALUE_1_TEMP <= 0)//����ϵͳ����̨��
	{
		if(Temp.Ctrl)
		{
			Mesa_Ctrl(dT, Temp.Ctrl);
		}
		else
		{
			HEAT = 0;//pwm�����
		}
	}
}
