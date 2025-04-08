#include "Ctrl_ControlTemp.h"

/**********�ṹ��************/
_PID_Arg_ Temp_Arg[4];
_PID_Val_ Temp_Val[4];
_PID_Arg_ Temp_Speed_Arg[4];
_PID_Val_ Temp_Speed_Val[4];
_PID_Arg_ Temp_Out_Arg[4];
_PID_Val_ Temp_Out_Val[4];

/**********�ֲ���������******/
uint8_t Out_Enable[4];//��������Ŀ���
float adc_val[4],ctrl_val[4];
uint8_t water_type[4],step[4];//�ж����ͻ���ˮ0��ˮ��1��
uint8_t Temp_type[4];//�¶�����
int Heat[4];//���������̵�pwmֵ

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
        Temp_Arg[i].Kp = 1600*0.001f;
        Temp_Arg[i].Ki = 8*0.001f;//18
        Temp_Arg[i].Kd = 90*0.001f;;//��̨��
        
        Temp_Speed_Arg[i].Kp = 350;
        Temp_Speed_Arg[i].Ki = 400*0.001f;//18
        Temp_Speed_Arg[i].Kd = 0*0.001f;;//��̨��
        
        Temp_Out_Arg[i].Kp = 2500*0.001f;
        Temp_Out_Arg[i].Ki = 10*0.001f;//18
        Temp_Out_Arg[i].Kd = 0*0.001f;;//��̨��
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
void Heat_Out(int Heat_Pwm[4])
{
    HEAT0 = (int)Heat_Pwm[0];
    HEAT1 = (int)Heat_Pwm[1];
    HEAT2 = (int)Heat_Pwm[2];
    HEAT3 = (int)Heat_Pwm[3];
}

/*
*****************************************************************
 * ����ԭ�ͣ�static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
* ��    �ܣ�̨���¶ȿ���temp_c:���µı���
*****************************************************************
*/
static void Mesa_Ctrl(float dT, uint8_t i,int32_t Ctrl_temp)
{
    static float T[4];
    static float T1[4];

	if(Ctrl_temp > Temp_MAX) Ctrl_temp = Temp_MAX;//��߼���Temp_MAX��
    if (Work_Num[i].Temp.Mesa < Ctrl_temp - 150)//�ﵽĿ���¶�-15��ǰȫ�ټ���
    {
        Heat[i] = 399;
    }
    else if ((Ctrl_temp <= 2000)&&Work_Num[i].Temp.Mesa < Ctrl_temp - 100)//�ﵽĿ���¶�-10��ǰȫ�ټ���
    {
        T[i] += dT;
        if(T[i] <3.0f)
            Heat[i] = 250;
        else if(T[i] >= 3.0f && T[i] < 5.0f)
            Heat[i] = 0;
        else
             T[i] = 0;
    }
    else if ((Ctrl_temp > 2000)&&Work_Num[i].Temp.Mesa < Ctrl_temp)//�ﵽĿ���¶�-0.5��ǰȫ�ټ���
    {
        Heat[i] = 399;
    }
    else if (Work_Num[i].Temp.Mesa >= Ctrl_temp + 10) //��������ֵ1��ʱȫ��
    {
        Heat[i] = 0;
    }
    else    //PID����
    {   //�趨��������Ϊ1000ms��1000��֮PID_Para.pid_result���뿪������
        if((Ctrl_temp - Work_Num[i].Temp.Mesa > -50 && Ctrl_temp - Work_Num[i].Temp.Mesa < 50))
            Out_Enable[i] = 1;//�򿪻��ּ���
        else
            Out_Enable[i] = 0;//�رջ��ּ���
        
        AltPID_Calculation(dT, Ctrl_temp, Work_Num[i].Temp.Mesa, &Temp_Arg[i], &Temp_Val[i], 100, Out_Enable[i] * 100);
        if(Temp_Val[i].Out < 0)
            Temp_Val[i].Out = 0;
        if(Temp_Val[i].Out > 100)
            Temp_Val[i].Out = 100;
        
        if(Ctrl_temp > Work_Num[i].Temp.Mesa)
        {
            AltPID_Calculation(dT, 0.5, Work_Num[i].Temp.Speed, &Temp_Speed_Arg[i], &Temp_Speed_Val[i], 250, 50);
            if(Temp_Speed_Val[i].Out < 0)
                Temp_Speed_Val[i].Out = 0;
            if(Temp_Speed_Val[i].Out > 250)
                Temp_Speed_Val[i].Out = 250;
        }
        else
        {
            Temp_Speed_Val[i].Out = 0;
        }
        
        T1[i] += dT;
        if (T1[i] <= (float)(Temp_Val[i].Out/10))
        {
            Heat[i] =Temp_Speed_Val[i].Out;
        }
        else
        {
            Heat[i] =0;
        }
        if(T1[i] > 10.0f)
            T1[i] = 0;
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ�static void Outside_Ctrl(float dT, int32_t Ctrl_temp)
* ��    �ܣ��ⲿ�¶ȿ���temp_c:���µı���
*****************************************************************
*/
static void Outside_Ctrl(float dT, uint8_t i,int32_t Ctrl_temp)
{
//    static float T[4];
    if (Work_Num[i].Temp.Outside < Ctrl_temp - 150)//�ﵽĿ���¶�-15��ǰȫ�ټ���
    {
        Mesa_Ctrl(dT, i, 3100);
    }
    else if ((Ctrl_temp <= 1000)&&Work_Num[i].Temp.Outside < Ctrl_temp - 100)//�ﵽĿ���¶�-10��ǰȫ�ټ���
    {
        Mesa_Ctrl(dT, i, Ctrl_temp*2.0f);
    }
    else if ((Ctrl_temp > 1000)&&Work_Num[i].Temp.Outside < Ctrl_temp)//�ﵽĿ���¶�-0.5��ǰȫ�ټ���
    {
        Mesa_Ctrl(dT, i, 3100);
    }
    else if (Work_Num[i].Temp.Outside >= Ctrl_temp) //��������ֵ1��ʱȫ��
    {
        Mesa_Ctrl(dT, i, 0);
    }
    else//PID����
    {//�趨��������Ϊ1000ms��1000��֮PID_Para.pid_result���뿪������
        AltPID_Calculation(dT, Ctrl_temp, Work_Num[i].Temp.Outside, &Temp_Out_Arg[i], &Temp_Out_Val[i], 2500, Ctrl_temp*1.5);
        if(Temp_Out_Val[i].Out < 0)
            Temp_Out_Val[i].Out = 0;
        if(Temp_Out_Val[i].Out > Ctrl_temp * 3.1f)
            Temp_Out_Val[i].Out = Ctrl_temp * 3.1f;
        Mesa_Ctrl(dT, i, Ctrl_temp+Temp_Out_Val[i].Out);
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
                Outside_Ctrl(dT, i, Work_Num[i].Temp.Ctrl);
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

void Temp_UpSpeed(float dT)
{
    static float T[4];
    for(uint8_t i = 0;i<4;i++)
    {
        T[i] += dT;
        if(T[i] > 1.0f)
        {
            Work_Num[i].Temp.Speed = Work_Num[i].Temp.Mesa - Work_Num[i].Temp.Old;
            Work_Num[i].Temp.Old = Work_Num[i].Temp.Mesa;
            T[i] = 0;
        }
    }
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
        Temp_UpSpeed(0.01f);
        Temp_Control(0.01f);
        vTaskDelayUntil(&xLastWakeTime, 10);
    }
}

