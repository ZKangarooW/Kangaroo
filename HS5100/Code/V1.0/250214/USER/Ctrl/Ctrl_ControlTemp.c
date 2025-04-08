#include "Ctrl_ControlTemp.h"

/**********�ṹ��************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;

#define N 10  // MPC Ԥ�ⲽ��
#define LAMBDA 0.3  // ��������ĳͷ�����
#define A 0.6  // �¶�˥��ϵ��//0.6
#define B 0.4  // ���ȹ��ʶ��¶ȵ�Ӱ��ϵ��

/**********�ֲ���������******/

/*
*****************************************************************
 * ����ԭ�ͣ�static void Set_Heating_Power(float pwm)
 * ��    �ܣ����ü����̹���
 * ��    ��: ���ȵ�pwm���� 
 * ��    ����float control_signal
*****************************************************************
*/
static void Set_Heating_Power(float pwm)
{
    // ����PID������Ƽ����̹���
    int power = (int)pwm;  // �������ź�תΪ���ʣ���Χ0-255��
    if (power < 0) power = 0;  // ���ƹ���Ϊ0
    if (power > 399) power = 399;  // ���ƹ���Ϊ255
    // ���ݹ���ֵ����Ӳ��������Ŀ��Ʒ�������Ӳ��������
    HEAT = power;
}

/*
*****************************************************************
 * ����ԭ�ͣ�float Temp_Model(float T, float u)
 * ��    �ܣ��¶�ģ��,����mpc�Ƚ�
 * ��    ��: T��Ԥ���¶ȣ�u���������루���ȹ��ʣ�
 * ��    ����Ԥ�⵽���¶�
 * ��    ����float T, float u
*****************************************************************
*/
float Temp_Model(float T, float u)
{
    return T + A * (u - T) + B * u;
}

/*
*****************************************************************
 * ����ԭ�ͣ�float Cost_Function(float T[], float u[],int16_t Temp_Ctrl)
 * ��    �ܣ�����ɱ�����
 * ��    ��: T��Ԥ���¶ȣ�u���������루���ȹ��ʣ�, Temp_Ctrl�������¶�
 * ��    �������ȹ��ʵĳͷ���
 * ��    ����float T[], float u[],int16_t Temp_Ctrl
*****************************************************************
*/
float Cost_Function(float T[], float u[],int16_t Temp_Ctrl)
{
    float J = 0;
    for (int i = 0; i < N; i++) 
    {
        J += (Temp_Ctrl - T[i]) * (Temp_Ctrl - T[i]); // Ŀ���¶ȵ�ƽ�����
        J += LAMBDA * u[i] * u[i];  // ���ȹ��ʵĳͷ���
    }
    return J;
}

/*
*****************************************************************
 * ����ԭ�ͣ�void MPC_Control(float Temp_Rel, float *control_signal,int16_t v)
 * ��    �ܣ�MPC ����������
 * ��    ��: Temp_Rel��ʵ���¶ȣ�control_signal�����ȹ���, Temp_Ctrl�������¶�
 * ��    ����float Temp_Rel, float *control_signal,int16_t Temp_Ctrl
*****************************************************************
*/
void MPC_Control(float Temp_Rel, float *control_signal,int16_t Temp_Ctrl)
{
    float u[N] = {0};  // �������루���ȹ��ʣ�
    float T[N];  // Ԥ���¶�
    float learning_rate = 0.01;  // ѧϰ��
    int max_iterations = 100;  // ����������

    // ��ʼ�¶�Ԥ��
    T[0] = Temp_Rel;
    for (int i = 1; i < N; i++) 
    {
        T[i] = Temp_Model(T[i-1], u[i-1]);
    }

    // �����Ż���������
    for (int iter = 0; iter < max_iterations; iter++) 
    {
        // ���㵱ǰ�¶�Ԥ��
        for (int i = 1; i < N; i++) {
            T[i] = Temp_Model(T[i-1], u[i-1]);
        }
        // ����ɱ�����
        float J = Cost_Function(T, u, Temp_Ctrl);
        // �ݶ��½����¿�������u
        for (int i = 0; i < N; i++) {
            float grad_u = 2 * (T[i] - Temp_Ctrl) * (-A * (T[i-1] - T[i]) - B) + 2 * LAMBDA * u[i];
            u[i] -= learning_rate * grad_u;
        }
        // ��ӡ��ǰ��������ͳɱ�����ֵ
//        printf("Iteration %d, Cost: %.4f, u[0]: %.4f\n", iter, J, u[0]);
        // ����Ƿ�����ֹͣ����������ɱ��������ٱ仯��
        if (J < 0.01) 
        {
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
*/
float control_signal;
float final_control_signal;
static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
{
    mpc_control(Temp.Rel, &control_signal,Ctrl_temp);
    AltPID_Calculation(dT, Ctrl_temp, Temp.Rel, &Temp_Arg, &Temp_Val, 100, 300);
    final_control_signal = (control_signal/1000) + Temp_Val.Out;
    
    Set_Heating_Power(final_control_signal);
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
