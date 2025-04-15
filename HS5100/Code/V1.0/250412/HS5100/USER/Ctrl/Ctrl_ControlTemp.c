#include "Ctrl_ControlTemp.h"

/**********�ṹ��************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;
_PID_Arg_ W_Temp_Arg;
_PID_Val_ W_Temp_Val;

/**********�궨��************/

/**********�ֲ���������******/
uint8_t Temp_type;//�¶�����

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
static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
{
    float final_control_signal;
    AltPID_Calculation(dT, Ctrl_temp, Temp.Mesa, &Temp_Arg, &Temp_Val, 100, 300);
    final_control_signal = Temp_Val.Out;
    Set_Heating_Power(final_control_signal);
}

/*
*****************************************************************
 * ����ԭ�ͣ�static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
 * ��    �ܣ�����̨����¶�
*****************************************************************
*/
void set_Mesa_power(float dT,float control_signal) 
{
    // ���������¶ȿ��Ƽ����̹���
    int power = (int)control_signal;  // �������ź�תΪ���ʣ���Χ0-255��
    if (power < Temp.Ctrl) power = Temp.Ctrl;  // ���ƹ���Ϊ0
    if (power > Temp_MAX) power = Temp_MAX;  // ���ƹ���Ϊ255
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

/*
*****************************************************************
 * ����ԭ�ͣ�static void Water_Ctrl(float dT, int32_t Ctrl_temp)
 * ��    �ܣ�����ˮ��
*****************************************************************
*/
static void Water_Ctrl(float dT, int32_t Ctrl_temp)
{
    if(Temp.Up_Speed == 1)//����
    {
        if(Temp.Rel<Temp.Ctrl-50)
        {
            set_Mesa_power(dT,Temp.Ctrl*3.5);
            IncPID_Calculation(dT, Ctrl_temp, Temp.Outside, &W_Temp_Arg, &W_Temp_Val,10, 300);
        } 
        else
        {
            IncPID_Calculation(dT, Ctrl_temp, Temp.Outside, &W_Temp_Arg, &W_Temp_Val,10, 300);
            set_Mesa_power(dT,Ctrl_temp+W_Temp_Val.Out);
        }
    }
    else if(Temp.Up_Speed == 2)//����
    {
        if(Temp.Rel<Temp.Ctrl-100)
        {
            set_Mesa_power(dT,Temp.Ctrl*2.8);
        } 
        else if(Temp.Rel<Temp.Ctrl-60)
        {
            set_Mesa_power(dT,Temp.Ctrl*2.5);
        } 
        else if(Temp.Rel<Temp.Ctrl-30)
        {
            set_Mesa_power(dT,Temp.Ctrl*2.1);
            IncPID_Calculation(dT, Ctrl_temp, Temp.Outside, &W_Temp_Arg, &W_Temp_Val,10, 300);
        } 
        else
        {
            IncPID_Calculation(dT, Ctrl_temp, Temp.Outside, &W_Temp_Arg, &W_Temp_Val,10, 300);
            set_Mesa_power(dT,Ctrl_temp+W_Temp_Val.Out);
        }
    }
    else//����
    {
        if(Temp.Rel<Temp.Ctrl-100)
        {
            set_Mesa_power(dT,Temp.Ctrl*3.5);
        } 
        else if(Temp.Rel<Temp.Ctrl-60)
        {
            set_Mesa_power(dT,Temp.Ctrl*3.0);
        } 
        else if(Temp.Rel<Temp.Ctrl-30)
        {
            set_Mesa_power(dT,Temp.Ctrl*2.5);
            IncPID_Calculation(dT, Ctrl_temp, Temp.Outside, &W_Temp_Arg, &W_Temp_Val,10, 300);
        } 
        else
        {
            IncPID_Calculation(dT, Ctrl_temp, Temp.Outside, &W_Temp_Arg, &W_Temp_Val,10, 300);
            set_Mesa_power(dT,Ctrl_temp+W_Temp_Val.Out);
        }
    }
}

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
    else if(sys.Run_Status && PT_VALUE_1_TEMP < 2400)//����ϵͳ����ˮ��
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
