#include "Ctrl_ControlTemp.h"

/**********�ṹ��************/
_PID_Arg_ Temp_Arg[4];
_PID_Val_ Temp_Val[4];

/**********�ֲ���������******/
uint8_t Out_Enable[4];//��������Ŀ���
float adc_val[4],ctrl_val[4];
uint8_t water_type[4],step[4];//�ж����ͻ���ˮ0��ˮ��1��
uint8_t Temp_type[4];//�¶�����
int8_t Heat[4];//���������̵�pwmֵ

/*
*****************************************************************
 * ����ԭ�ͣ�void Temp_PID(void)
 * ��    �ܣ��¶ȿ���PIDϵ��
*****************************************************************
*/
void Temp_PID(void)
{
    for(uint8_t i = 0;i<4;i++)
    {
        Temp_Arg[i].Kp = 700*0.001f;
        Temp_Arg[i].Ki = 20*0.001f;
        Temp_Arg[i].Kd = 30;//��̨��
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Motor_Out(int16_t Motor_Pwm[MOTOR_NUM])
 * ��    �ܣ��������
 * ��    �룺int16_t Motor_Pwm[MOTOR_NUM]
 * ��    ����Motor_Pwm[MOTOR_NUM]����Motor��PWMռ�ձ�ֵ
*****************************************************************
*/
void Heat_Out(int8_t Heat_Pwm[4])
{
    HEAT0 = (uint8_t)Heat_Pwm[0];
    HEAT1 = (uint8_t)Heat_Pwm[1];
    HEAT2 = (uint8_t)Heat_Pwm[2];
    HEAT3 = (uint8_t)Heat_Pwm[3];
}

/*
*****************************************************************
 * ����ԭ�ͣ�static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
* ��    �ܣ�̨���¶ȿ���temp_c:���µı���
*****************************************************************
*/
static void Mesa_Ctrl(float dT, uint8_t i,int32_t Ctrl_temp)
{
	if(Ctrl_temp > Temp_MAX) Ctrl_temp = Temp_MAX;//��߼���Temp_MAX��
    
    ctrl_val[i] = Get_ADCVal(Ctrl_temp)*10;//����ADCֵ
    
    adc_val[i] = PT_VALUE_2_TEMP[i]*10;//ʵ�ʵ�adcֵ
    
	if(Ctrl_temp > 2300 && Work_Num[i].Temp.Mesa > 2000)//��������¶ȴ���230�ȣ�̨���¶ȳ���200��
		Out_Enable[i] = 1;//�򿪻��ּ���
	else if((ctrl_val - adc_val > -200 && ctrl_val - adc_val < 200))
		Out_Enable[i] = 1;//�򿪻��ּ���
	else
		Out_Enable[i] = 0;//�رջ��ּ���
    
	AltPID_Calculation(dT, ctrl_val[i], adc_val[i], &Temp_Arg[i], &Temp_Val[i], 100, Out_Enable[i] * 1000);
	if(Temp_Val[i].Out < 0)
		Temp_Val[i].Out = 0;
	Heat[i] =(int)Temp_Val[i].Out;
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Temp_Control(float dT)
 * ��    �ܣ��¶ȼ��ȿ���
*****************************************************************
*/
void Temp_Control(float dT)
{ 
    for(uint8_t i = 0;i<4;i++)
    {
        if(Work_Num[i].Run_Status && PT_VALUE_1_TEMP[i] >= 2200)//����ϵͳ����̨��
        {
            if(Temp_type[i] == 1)//������ⲿ̽ͷ�л�����
            {
                Work_Num[i].Temp.ADDMode = 0;
                Temp_type[i] = 0;
            }
            if(Work_Num[i].Temp.Ctrl)
            {
                Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl);
            }
            else
            {
                water_type[i] = 0;
                Heat[i] = 0;//pwm�����
                step[i] = 0;
            }
        }
        else if(Work_Num[i].Run_Status && PT_VALUE_1_TEMP[i] < 2200)//����ϵͳ����ˮ��
        {
            if(Work_Num[i].Temp.Ctrl)
            {
                if(Temp_type[i] == 0)//�����̨��̽ͷ�л�����
                {
                    Work_Num[i].Temp.ADDMode = 0;
                    Temp_type[i] = 1;
                }
                if(Work_Num[i].Temp.Ctrl < 1000)//�����¶�С��100��
                {
                    if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel >= 150)
                    {
                        Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl * 3.1f);
                    }
                    else if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel < 150 && Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel >= 100)
                    {
                        Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl * 2.8f);
                    }
                    else if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel < 100 && Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel >= 50)
                    {
                        Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl * 2.5f);
                    }
                    else if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel < 50 && Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel >= 10)
                    {
                        Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl * 2.2f);
                    }
                    else if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel < 10 && Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel > 0)
                    {
                        Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl * 1.8f);
                    }
                    else
                    {
                        Temp_Val[i].Out = 0;
                        Heat[i] = (int)Temp_Val[i].Out;
                    }
                }
                else if(Work_Num[i].Temp.Ctrl == 1000)//�����¶ȵ���100��
                {
                    if(!water_type[i])
                    {
                        if(step[i] == 0)
                        {
                            Mesa_Ctrl(dT, i, 3100);
                            if(Work_Num[i].Temp.Rel >= 1000)
                            {
                                step[i] = 1;
                            }
                        }
                        else if(step[i] == 1)
                        {
                            Mesa_Ctrl(dT, i, 2200);
                        }
                        if(Work_Num[i].Temp.Rel >= 1040)
                        {
                            water_type[i] = 1;//�ж�Ϊ��
                        }
                    }
                    else
                    {
                        if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel >= 150)
                        {
                            Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl * 3.1f);
                        }
                        else if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel < 150 && Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel >= 100)
                        {
                            Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl * 2.8f);
                        }
                        else if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel < 100 && Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel >= 50)
                        {
                            Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl * 2.5f);
                        }
                        else if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel < 50 && Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel >= 10)
                        {
                            Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl * 2.2f);
                        }
                        else if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel < 10 && Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel > 0)
                        {
                            Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl * 1.8f);
                        }
                        else
                        {
                            Temp_Val[i].Out = 0;
                            Heat[i] = (int)Temp_Val[i].Out;
                        }
                    }
                }
                else if(Work_Num[i].Temp.Ctrl > 1000)//�����¶ȴ���100��
                {
                    if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel >= 150)
                    {
                        Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl * 3.1f);
                    }
                    else if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel < 150 && Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel >= 100)
                    {
                        Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl * 2.8f);
                    }
                    if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel > 100)
                    {
                        Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl * 2.2f);
                    }
                    else if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel < 100 && Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel >= 50)
                    {
                        Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl * 2.0f);
                    }
                    else if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel < 50 && Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel > 0)
                    {
                        Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl * 1.8f);
                    }
                    else
                    {
                        Temp_Val[i].Out = 0;
                        Heat[i] = (int)Temp_Val[i].Out;
                    }
                }
            }
            else
            {
                water_type[i] = 0;
                Heat[i] = 0;//pwm�����
                step[i] = 0;
            }
        }
        else
        {
            water_type[i] = 0;
            Heat[i] = 0;//pwm�����
            step[i] = 0;
        }
    }
    Heat_Out(Heat);
}

/**
 * @brief �¶�����
 * 
 */
void Temp_Task(void *p)
{
    TickType_t xLastWakeTime;//�տ�ʼ���ѵ�ʱ��
    xLastWakeTime = xTaskGetTickCount ();
    
    Temp_PID();
    
    while(1)
    {
        Temp_Control(1.0f);
        vTaskDelayUntil(&xLastWakeTime, 1000);
    }
}

