#include "Ctrl_ControlTemp.h"

/**********�ṹ��************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;

/**********ȫ�ֱ�������******/
uint8_t Protect;//������

/*
*****************************************************************
 * ����ԭ�ͣ�void Temp_PID(void)
 * ��    �ܣ��¶ȿ���PIDϵ��
*****************************************************************
*/
void Temp_PID(void)
{
    Temp_Arg.Kp = 0;
    Temp_Arg.Ki = 0;
    Temp_Arg.Kd = 0;
}

// ���� PWM ��������Ƽ�������
void setPWM(float duty_cycle)
{
    HEAT = (int)((duty_cycle/100)*200);
}

float Ku = 0.0;               // �ٽ�����
float Tu = 0.0;               // �ٽ�����
float Kp = 0.1;// ��ʼ����
float control_signal = 0.0;   // �����ź�
// �Զ�����ģ��
bool AutoTunePID(float dt, float *Ku, float *Tu) {
    static float last_peak_time = 0.0;
    static int oscillation_count = 0;
    static float last_temp = 0.0;
    static float peak_time[2] = {0.0, 0.0}; // ��¼������ֵ��ʱ��

    // ʹ�ñ�������
    control_signal = Kp * (Temp.Ctrl - Temp.Rel);
    if(control_signal>100)
        control_signal = 100;
    if(control_signal<0)
        control_signal = 0;
    setPWM(control_signal);

    // �����
    if (Temp.Rel >= Temp.Ctrl && last_temp < Temp.Ctrl) {
        if (oscillation_count < 2) {
            peak_time[oscillation_count] = last_peak_time;
        }
        oscillation_count++;
    }
    last_temp = Temp.Rel;
    last_peak_time += dt;

    // ���� Ku �� Tu
    if (oscillation_count >= 2) {
        *Ku = Kp;
        *Tu = peak_time[1] - peak_time[0];
        return true; // �Զ��������
    }

    // ��������
    Kp += dt/500;
    return false; // ��δ���
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Temp_Control(float dT)
 * ��    �ܣ��¶ȼ��ȿ���
*****************************************************************
*/
void Temp_Control(float dT)
{ 
    static bool tuning_complete = false;
	if(sys.Run_Status == 1)
	{
		if(Temp.Ctrl)
		{
            // �Զ����ν׶�
            if (!tuning_complete) {
                tuning_complete = AutoTunePID(dT, &Ku, &Tu);
                return;
            }
            Temp_Arg.Kp = 0.6 * Ku;
            Temp_Arg.Ki = 2 * Kp / Tu;
            Temp_Arg.Kd = Kp * Tu / 8;        
                    
			IncPID_Calculation(dT,Temp.Ctrl,Temp.Rel,&Temp_Arg,&Temp_Val,80);//�¶�PID����
            setPWM(Temp_Val.Out);
		}
	}
	else
	{
		Temp_Val.Out = 0; 
		HEAT = Temp_Val.Out;
	}
}
