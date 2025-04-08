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
    HEAT = (int)((duty_cycle*2));
}

float Ku = 0.0;               // �ٽ�����
float Tu = 0.0;               // �ٽ�����
float Kp = 0.1;// ��ʼ����
float control_signal = 0.0;   // �����ź�
int oscillation_count = 0;
float last_temp = 0.0;
float last_peak_time = 0.0;
float peak_time[2] = {0.0, 0.0}; // ��¼������ֵ��ʱ��
// �Զ�����ģ��
bool AutoTunePID(float dt, float *Ku, float *Tu) {

    // ʹ�ñ�������
    control_signal = Kp * (Temp.Ctrl - Temp.Rel);
    if(control_signal>100)
        control_signal = 100;
    if(control_signal<0)
        control_signal = 0;
    if(Temp.Rel >= Temp.Ctrl)
        control_signal = 0;
    setPWM(control_signal);
    // �����
    if (Temp.Rel > Temp.Ctrl && last_temp < Temp.Ctrl) {
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
    if(Temp.Rel < Temp.Ctrl)
        Kp += 0.008;
    return false; // ��δ���
}
float Error_Val,Ki_Val;
/*
*****************************************************************
 * ����ԭ�ͣ�void Temp_Control(float dT)
 * ��    �ܣ��¶ȼ��ȿ���
*****************************************************************
*/
bool tuning_complete = false;
void Temp_Control(float dT)
{ 
//    static float T;
	if(sys.Run_Status == 1)
	{
        if(Temp.Ctrl)
        {
//            T += dT;
//            if(T >= 4.0f)
//            {
                // �Զ����ν׶�
                if (!tuning_complete) {
                    tuning_complete = AutoTunePID(dT, &Ku, &Tu);
                    if(tuning_complete)
                    {
//                        Temp_Arg.Kp = Ku; 
                        Temp_Arg.Kp = 0.6 * Ku;
                        Temp_Arg.Ki = 2 * Kp / Tu;
                        Temp_Arg.Kd = Kp * Tu / 8; 
                    }
//                    T = 0;
                    return;
                }
                AltPID_Calculation(dT,Temp.Ctrl,Temp.Rel,&Temp_Arg,&Temp_Val,80,20);
//                IncPID_Calculation(dT,Temp.Ctrl,Temp.Rel,&Temp_Arg,&Temp_Val,80);//�¶�PID����
                
                control_signal = Temp_Val.Out; 
//                control_signal = (Temp_Arg.Kp+ Ki_Val) * (Temp.Ctrl - Temp.Rel) ;
//                if(Temp.Rel < Temp.Ctrl)
//                {
//                    Error_Val = Ki_Val;
//                    Ki_Val += 0.001;
//                }
//                else
//                    Ki_Val = Error_Val;
//                T = 0;
//            }
            if(control_signal>100)
                control_signal = 100;
            if(control_signal<0)
                control_signal = 0;
            if(Temp.Rel >= Temp.Ctrl)
                control_signal = 0;
            setPWM(control_signal);
        }
	}
	else
	{
		Temp_Val.Out = 0; 
		HEAT = Temp_Val.Out;
	}
}
