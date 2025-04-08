#include "Ctrl_ControlTemp.h"

/**********�ṹ��************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;

/**********�ֲ���������******/
uint8_t Out_Enable;//��������Ŀ���
float adc_val,ctrl_val;
uint8_t water_type,step;//�ж����ͻ���ˮ0��ˮ��1��
uint8_t Temp_type;//�¶�����
int Heat;//�����̵�pwmֵ

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
static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
{
    static float T;
    static float T1;
    
    if(Ctrl_temp > Temp.Safe_Temp - 500) Ctrl_temp = Temp.Safe_Temp - 500;//��߼���Temp_MAX��
    if ((Ctrl_temp > 1000)&&(Temp.Rel < Ctrl_temp - 150))//�ﵽĿ���¶�-0.5��ǰȫ�ټ���
    {
        Heat = 399;
    }
    else if ((Ctrl_temp <= 1000)&&Temp.Rel < Ctrl_temp - 100)//�ﵽĿ���¶�-0.5��ǰȫ�ټ���
    {
        T += dT;
        if(T <3.0f)
            Heat = 399;
        else if(T >= 3.0f && T < 5.0f)
            Heat = 0;
        else
             T = 0;
    }
    else if ((Ctrl_temp > 1000)&&Temp.Rel < Ctrl_temp)//�ﵽĿ���¶�-0.5��ǰȫ�ټ���
    {
        Heat = 399;
    }
    else if (Temp.Rel >= Ctrl_temp + 10) //��������ֵ1��ʱȫ��
    {
        Heat = 0;
    }
    else    //PID����
    {   //�趨��������Ϊ1000ms��1000��֮PID_Para.pid_result���뿪������
        ctrl_val = Get_ADCVal(Ctrl_temp);//����ADCֵ
        
        adc_val = PT_VALUE_2_TEMP;//ʵ�ʵ�adcֵ
        
        if(Ctrl_temp > 2300 && Temp.Mesa > 2000)//��������¶ȴ���230�ȣ�̨���¶ȳ���200��
            Out_Enable = 1;//�򿪻��ּ���
        else if((ctrl_val - adc_val > -200 && ctrl_val - adc_val < 200))
            Out_Enable = 1;//�򿪻��ּ���
        else
            Out_Enable = 0;//�رջ��ּ���
        
        if(Temp.Up_Speed == 1)//����
        {
            Temp_Arg.Kp = 1000*0.001f;
            Temp_Arg.Ki = 12*0.001f;//18
            Temp_Arg.Kd = 0 * 0.001f;
        }
        else if(Speed.Up_Speed == 2)//����
        {
            Temp_Arg.Kp = 200*0.001f;
            Temp_Arg.Ki = 3*0.001f;//18
            Temp_Arg.Kd = 0 * 0.001f;
        }
        else//����
        {
            Temp_Arg.Kp = 500*0.001f;
            Temp_Arg.Ki = 6*0.001f;//18
            Temp_Arg.Kd = 0 * 0.001f;
        }
            
        AltPID_Calculation(dT, ctrl_val, adc_val, &Temp_Arg, &Temp_Val, 100, Out_Enable * 100);
        if(Temp_Val.Out < 0)
            Temp_Val.Out = 0;
        if(Temp_Val.Out > 100)
            Temp_Val.Out = 100;
        
        T1 += dT;
        if (T1 <= (float)(Temp_Val.Out/10))
        {
            Heat =300;
        }
        else
        {
            Heat =0;
        }
        if(T1 > 10.0f)
            T1 = 0;
    }
    if(Temp.Rel<=Temp.Ctrl)
        HEAT = Heat;
    else
        HEAT = 0;
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Temp_Control(float dT)
 * ��    �ܣ��¶ȼ��ȿ���
*****************************************************************
*/
void Temp_Control(float dT)
{ 
	if(sys.Run_Status && PT_VALUE_1_TEMP >= 2200)//����ϵͳ����̨��
	{
		if(Temp_type == 1)//������ⲿ̽ͷ�л�����
		{
			Temp.ADDMode = 0;
			Temp_type = 0;
		}
		if(Temp.Ctrl)
		{
			Mesa_Ctrl(dT, Temp.Ctrl);
		}
		else
		{
			water_type = 0;
			HEAT = 0;//pwm�����
			step = 0;
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
			if(Temp.Ctrl < 1000)//�����¶�С��100��
			{
                if(Temp.Ctrl - Temp.Rel >= 150)
				{
					Mesa_Ctrl(dT, Temp.Ctrl * 3.1f);
				}
				else if(Temp.Ctrl - Temp.Rel < 150 && Temp.Ctrl - Temp.Rel >= 100)
				{
					Mesa_Ctrl(dT, Temp.Ctrl * 2.8f);
				}
				else if(Temp.Ctrl - Temp.Rel < 100 && Temp.Ctrl - Temp.Rel >= 50)
				{
					Mesa_Ctrl(dT, Temp.Ctrl * 2.5f);
				}
				else if(Temp.Ctrl - Temp.Rel < 50 && Temp.Ctrl - Temp.Rel >= 10)
				{
					Mesa_Ctrl(dT, Temp.Ctrl * 2.2f);
				}
				else if(Temp.Ctrl - Temp.Rel < 10 && Temp.Ctrl - Temp.Rel > 0)
				{
					Mesa_Ctrl(dT, Temp.Ctrl * 1.8f);
				}
				else
				{
					Temp_Val.Out = 0;
					HEAT = (int)Temp_Val.Out;
				}
			}
			else if(Temp.Ctrl == 1000)//�����¶ȵ���100��
			{
				if(!water_type)
				{
					if(step == 0)
					{
						Mesa_Ctrl(dT, 3100);
						if(Temp.Rel >= 1000)
						{
							step = 1;
						}
					}
					else if(step == 1)
					{
						Mesa_Ctrl(dT, 2200);
					}
					if(Temp.Rel >= 1040)
					{
						water_type = 1;//�ж�Ϊ��
					}
				}
				else
				{
					if(Temp.Ctrl - Temp.Rel >= 150)
                    {
                        Mesa_Ctrl(dT, Temp.Ctrl * 3.1f);
                    }
                    else if(Temp.Ctrl - Temp.Rel < 150 && Temp.Ctrl - Temp.Rel >= 100)
                    {
                        Mesa_Ctrl(dT, Temp.Ctrl * 2.8f);
                    }
                    else if(Temp.Ctrl - Temp.Rel < 100 && Temp.Ctrl - Temp.Rel >= 50)
                    {
                        Mesa_Ctrl(dT, Temp.Ctrl * 2.5f);
                    }
                    else if(Temp.Ctrl - Temp.Rel < 50 && Temp.Ctrl - Temp.Rel >= 10)
                    {
                        Mesa_Ctrl(dT, Temp.Ctrl * 2.2f);
                    }
                    else if(Temp.Ctrl - Temp.Rel < 10 && Temp.Ctrl - Temp.Rel > 0)
                    {
                        Mesa_Ctrl(dT, Temp.Ctrl * 1.8f);
                    }
					else
					{
						Temp_Val.Out = 0;
						HEAT = (int)Temp_Val.Out;
					}
				}
			}
			else if(Temp.Ctrl > 1000)//�����¶ȴ���100��
			{
				if(Temp.Ctrl - Temp.Rel >= 150)
				{
					Mesa_Ctrl(dT, Temp.Ctrl * 3.1f);
				}
				else if(Temp.Ctrl - Temp.Rel < 150 && Temp.Ctrl - Temp.Rel >= 100)
				{
					Mesa_Ctrl(dT, Temp.Ctrl * 2.8f);
				}
				if(Temp.Ctrl - Temp.Rel > 100)
				{
					Mesa_Ctrl(dT, Temp.Ctrl * 2.2f);
				}
				else if(Temp.Ctrl - Temp.Rel < 100 && Temp.Ctrl - Temp.Rel >= 50)
				{
					Mesa_Ctrl(dT, Temp.Ctrl * 2.0f);
				}
				else if(Temp.Ctrl - Temp.Rel < 50 && Temp.Ctrl - Temp.Rel > 0)
				{
					Mesa_Ctrl(dT, Temp.Ctrl * 1.8f);
				}
				else
				{
					Temp_Val.Out = 0;
					HEAT =(int)Temp_Val.Out;
				}
			}
		}
		else
		{
			water_type = 0;
			HEAT = 0;//pwm�����
			step = 0;
		}
	}
	else
	{
		water_type = 0;
		HEAT = 0;//pwm�����
		step = 0;
	}
}
