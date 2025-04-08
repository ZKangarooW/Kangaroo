#include "Ctrl_ControlTemp.h"

/**********�ṹ��************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;
_PID_Arg_ W_Temp_Arg;
_PID_Val_ W_Temp_Val;

/**********�ֲ���������******/

// ���ü����̹���
void set_heating_power(float control_signal) 
{
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
    
    W_Temp_Arg.Kp = 20000*0.001f;
    W_Temp_Arg.Ki = 80*0.001f;//18
	W_Temp_Arg.Kd = 900*0.001f;;//��̨��
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
    mpc_control(Temp.Mesa, &control_signal,Ctrl_temp);
    AltPID_Calculation(dT, Ctrl_temp, Temp.Mesa, &Temp_Arg, &Temp_Val, 100, 300);
    final_control_signal = (control_signal/1000) + Temp_Val.Out;
    
    set_heating_power(final_control_signal);
}

//����̨����¶�
void set_Mesa_power(float dT,float control_signal) {
    // ����PID������Ƽ����̹���
    int power = (int)control_signal;  // �������ź�תΪ���ʣ���Χ0-255��
    if (power < Temp.Ctrl) power = Temp.Ctrl;  // ���ƹ���Ϊ0
    if (power > 3500) power = 3500;  // ���ƹ���Ϊ255
    // ���ݹ���ֵ����Ӳ��������Ŀ��Ʒ�������Ӳ��������
    if(Temp.Rel>Temp.Ctrl)
    {
        HEAT = 0;
    }
    else
    {
        Mesa_Ctrl(dT, power);
    }
}
float control_signal1;
float final_control_signal1;
static void Water_Ctrl(float dT, int32_t Ctrl_temp)
{
    if(Temp.Rel<Temp.Ctrl-100)
    {
        final_control_signal1 = Temp.Ctrl*3.5;
        set_Mesa_power(dT,final_control_signal1);
    } 
    else if(Temp.Rel<Temp.Ctrl-60)
    {
        final_control_signal1 = Temp.Ctrl*3.0;
        set_Mesa_power(dT,final_control_signal1);
    } 
    else if(Temp.Rel<Temp.Ctrl-30)
    {
        final_control_signal1 = Temp.Ctrl*2.5;
        set_Mesa_power(dT,final_control_signal1);
        IncPID_Calculation(dT, Ctrl_temp, Temp.Outside, &W_Temp_Arg, &W_Temp_Val,10, 300);
    } 
    else
    {
        mpc_control(Temp.Outside, &control_signal1,Ctrl_temp);
        IncPID_Calculation(dT, Ctrl_temp, Temp.Outside, &W_Temp_Arg, &W_Temp_Val,10, 300);
        
        final_control_signal1 = (control_signal1/1000) + W_Temp_Val.Out;
        
        set_Mesa_power(dT,Ctrl_temp+final_control_signal1);
    }
}

uint8_t Temp_type;//�¶�����
/*
*****************************************************************
 * ����ԭ�ͣ�void Temp_Control(float dT)
 * ��    �ܣ��¶ȼ��ȿ���
*****************************************************************
*/
void Temp_Control(float dT)
{ 
    if(sys.Run_Status && PT_VALUE_1_TEMP >= 2400)//����ϵͳ����̨��
	{
        if(Temp.Ctrl)
        {
            if(Temp_type == 1)//������ⲿ̽ͷ�л�����
            {
                Temp.ADDMode = 0;
                Temp_type = 0;
            }
            Mesa_Ctrl(dT, Temp.Ctrl);
        }
        else
        {
            HEAT = 0;//pwm�����
        }
	}
    else if(sys.Run_Status && PT_VALUE_1_TEMP < 2200)//����ϵͳ����ˮ��
	{
        if(Temp.Ctrl)
		{	
            if(Temp_type == 0)//�����̨��̽ͷ�л�����
			{
				Temp.ADDMode = 0;
				Temp_type = 1;
			}
            Water_Ctrl(dT, Temp.Ctrl);
        }
        else
		{
			HEAT = 0;//pwm�����
		}
    }
    else
	{
		HEAT = 0;//pwm�����
	} 
}
