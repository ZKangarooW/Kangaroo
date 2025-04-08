#include "Ctrl_ControlTemp.h"

/**********�ṹ��************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;

uint8_t JDQ_Flag;
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
    if(Temp.Rel>Temp.Mesa)
    {
        HEAT = 0;
        HEAT_OFF;
        JDQ_Flag = 0;
    }
    else if (power < 0)
    {
        power = 0;  // ���ƹ���Ϊ0
        HEAT = power;//����С��300��PWM����
        HEAT_OFF;
        JDQ_Flag = 0;
    }
    else if (power < 399)
    {
        HEAT = power;//����С��300��PWM����
        HEAT_OFF;
        JDQ_Flag = 0;
    }
    
//    else//������ʴ���300���Ҳ�С��0���ü̵�������
//    {
//        power = 0;//���ƹ���Ϊ0
//        HEAT = power;//����С��300��PWM����
//        HEAT_OFF;
//        JDQ_Flag = 0;
//    }
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Temp_PID(void)
 * ��    �ܣ��¶ȿ���PIDϵ��
*****************************************************************
*/
void Temp_PID(void)
{
//	Temp_Arg.Kp = 1000*0.001f;
//	Temp_Arg.Ki = 8*0.001f;//18
//	Temp_Arg.Kd = 90*0.001f;;//��̨��
//    Temp_Arg.Kp_i = 0.1;
    
    Temp_Arg.Kp = 774*0.001f;
	Temp_Arg.Ki = 30*0.001f;//18
	Temp_Arg.Kd = 13.846f;;//��̨��
}

/*
*****************************************************************
 * ����ԭ�ͣ�static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
 * ��    �ܣ�̨���¶ȿ���
*****************************************************************
*/
static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
{
    AltPID_Calculation(dT, Ctrl_temp, Temp.Mesa, &Temp_Arg, &Temp_Val, 100, 300);
    Set_Heating_Power(Temp_Val.Out);
}

/**********�ֲ���������******/
float Ku = 0.0;//�ٽ�����
float Tu = 0.0;//�ٽ�����

/**********ȫ�ֱ�������******/
bool tuning_complete = false;//�Զ����α�־λ
float last_peak_time = 0.0;//��һ������
int oscillation_count = 0;//������

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
    Set_Heating_Power(Temp_Val.Out);
    
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
        Temp_Arg.Kp_i += 0.001;
    return false; //��δ���
}
uint8_t tuning_complete1;
uint8_t oscillation_count1;
/*
*****************************************************************
 * ����ԭ�ͣ�void Temp_Control(float dT)
 * ��    �ܣ��¶ȼ��ȿ���
*****************************************************************
*/
void Temp_Control(float dT)
{ 
    static float T;
    static float last_temp1 = 0.0;
    if(sys.Run_Status)//����ϵͳ����̨��
	{
        if(Temp.Ctrl)
        {
            if((Temp.Ctrl - Temp.Rel)>200)//����10��
            {
                tuning_complete1 = 1;
                
                HEAT_ON;
                JDQ_Flag = 1;

                last_temp1 = Temp.Rel;
            }
            else
            {
                // ��ʾ�¶������10��
                if (tuning_complete1) 
                {
                    if (Temp.Rel < Temp.Ctrl && last_temp1 > Temp.Rel) 
                    {
                        oscillation_count1++;
                        if(oscillation_count1 >= 4)
                        {
                            tuning_complete1 = 0;
                        }
                    }
                    last_temp1 = Temp.Rel;
                }
                else
                {
//                    // �Զ����ν׶�
//                    if (!tuning_complete) 
//                    {
//                        tuning_complete = AutoTunePID(dT, &Ku, &Tu);
//                        if(tuning_complete)
//                        {
//                            Temp_Arg.Kp = 0.6 * Ku;
//                            Temp_Arg.Ki = 2 * Temp_Arg.Kp_i / Tu;
//                            Temp_Arg.Kd = Temp_Arg.Kp_i * Tu / 8; 
//                            Temp_Arg.Kp_i = 0.1;// ��ʼ����
//                        }
//                        return;
//                    }
                    Mesa_Ctrl(dT, Temp.Ctrl);
                }
            }
        }
        else
        {
            HEAT = 0;//pwm�����
            HEAT_OFF;
        }
	}
    else
	{
		HEAT = 0;//pwm�����
        HEAT_OFF;
	}
}
