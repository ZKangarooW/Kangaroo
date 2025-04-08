#include "Ctrl_ControlTemp.h"

/**********�ṹ��************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;

/**********�ֲ���������******/
float Ku = 0.0;//�ٽ�����
float Tu = 0.0;//�ٽ�����

/**********ȫ�ֱ�������******/
bool tuning_complete = false;//�Զ����α�־λ
float last_peak_time = 0.0;//��һ������
int oscillation_count = 0;//������

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
    Temp_Arg.Kp_i = 0.1;
}

/*
*****************************************************************
 * ����ԭ�ͣ�void setPWM(float duty_cycle)
 * ��    �ܣ����� PWM ��������Ƽ�������
*****************************************************************
*/
void setPWM(float duty_cycle)
{
    if(duty_cycle>100)
        duty_cycle = 100;
    if(duty_cycle<0)
        duty_cycle = 0;
    if(Temp.Rel >= Temp.Ctrl)
        duty_cycle = 0;
    HEAT = (int)((duty_cycle*2));
}

/*
*****************************************************************
 * ����ԭ�ͣ�bool AutoTunePID(float dt, float *Ku, float *Tu) 
 * ��    �ܣ��Զ�����ģ��
 * ��    �룺dT�����ڣ���λ���룩
			 Ku���ٽ�����
			 Tu���ٽ�����
 * ��    ����float dT, float *Ku, float *Ku
*****************************************************************
*/
bool AutoTunePID(float dT, float *Ku, float *Tu) 
{    
    static float last_temp = 0.0;
    static float peak_time[2] = {0.0, 0.0}; // ��¼������ֵ��ʱ��
    
    //ʹ�ñ�������
    Temp_Val.Out = Temp_Arg.Kp_i * (Temp.Ctrl - Temp.Rel);
    setPWM(Temp_Val.Out);
    
    //�����
    if (Temp.Rel > Temp.Ctrl && last_temp < Temp.Ctrl) 
    {
        if (oscillation_count < 2) {
            peak_time[oscillation_count] = last_peak_time;
        }
        oscillation_count++;
    }
    last_temp = Temp.Rel;
    last_peak_time += dT;

    //���� Ku �� Tu
    if (oscillation_count >= 2) 
    {
        *Ku = Temp_Arg.Kp_i;
        *Tu = peak_time[1] - peak_time[0];
        oscillation_count = 0;
        return true; //�Զ��������
    }

    //��������
    if(Temp.Rel < Temp.Ctrl)
        Temp_Arg.Kp_i += 0.008;
    return false; //��δ���
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Temp_Control(float dT)
 * ��    �ܣ��¶ȼ��ȿ���
*****************************************************************
*/
void Temp_Control(float dT)
{ 
	if(sys.Run_Status == 1)
	{
        if(Temp.Ctrl)
        {
            // �Զ����ν׶�
            if (!tuning_complete) {
                tuning_complete = AutoTunePID(dT, &Ku, &Tu);
                if(tuning_complete)
                {
                    Temp_Arg.Kp = 0.6 * Ku;
                    Temp_Arg.Ki = 2 * Temp_Arg.Kp_i / Tu;
                    Temp_Arg.Kd = Temp_Arg.Kp_i * Tu / 8; 
                    Temp_Arg.Kp_i = 0.1;// ��ʼ����
                }
                return;
            }
            AltPID_Calculation(dT,Temp.Ctrl,Temp.Rel,&Temp_Arg,&Temp_Val,80,20);   
            setPWM(Temp_Val.Out);
        }
	}
	else
	{
        tuning_complete = false;//�Զ���������Ϊfalse
        last_peak_time = 0.0;//��һ����������
        oscillation_count = 0;//������
		Temp_Val.Out = 0; 
		HEAT = Temp_Val.Out;
	}
}
