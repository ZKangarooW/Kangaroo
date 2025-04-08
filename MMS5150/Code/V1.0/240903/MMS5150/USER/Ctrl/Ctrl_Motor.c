#include "Ctrl_Motor.h"

/**********�ṹ��************/
_PID_Arg_ Speed_Arg;
_PID_Val_ Speed_Val[15];

/*
*****************************************************************
 * ����ԭ�ͣ�void Motor_PID(void)
 * ��    �ܣ��������PIDϵ��
*****************************************************************
*/
void Motor_PID(void)
{
    Speed_Arg.Kp = 40 * 0.001f;
    Speed_Arg.Ki = 60 * 0.001f;
    Speed_Arg.Kd = 0 * 0.001f;
}

int8_t Motor[15];//���������pwmֵ
/*
*****************************************************************
 * ����ԭ�ͣ�void Motor_Out(int16_t Motor_Pwm[MOTOR_NUM])
 * ��    �ܣ��������
 * ��    �룺int16_t Motor_Pwm[MOTOR_NUM]
 * ��    ����Motor_Pwm[MOTOR_NUM]����Motor��PWMռ�ձ�ֵ
*****************************************************************
*/
void Motor_Out(int8_t Motor_Pwm[15])
{
    for(uint8_t i = 0; i<15;i++)
    {
        Motor_PWM[i] = Motor_Pwm[i];
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Motor_Ctrl(float dT)
 * ��    �ܣ��������
*****************************************************************
*/
void Motor_Ctrl(float dT)
{
    for(uint8_t i = 0;i<15;i++)
    {
        if(Work_Num[i].Run_Status)//����
        {
            if(Work_Num[i].Speed.Ctrl)
            {
                if(Work_Num[i].Motor_Stop)
                {
                    if(Speed_Val[i].Out)
                        Speed_Val[i].Out -= 1;//����̫��*2
                    if(Speed_Val[i].Out < 0)
                        Speed_Val[i].Out = 0;
                    Motor[i] = Speed_Val[i].Out;//pid���
                }
                else
                {
                    AltPID_Calculation(dT,Work_Num[i].Speed.Ctrl,Work_Num[i].Speed.Rel,&Speed_Arg,&Speed_Val[i],200,200);//���PID����
                    if(Speed_Val[i].Out > 199)
                        Speed_Val[i].Out = 199; 
                    Motor[i] = Speed_Val[i].Out;//pid���
                }
            }
            else
            {
                if(Speed_Val[i].Out)
                    Speed_Val[i].Out -= 1;//����̫��*2
                if(Speed_Val[i].Out < 20)
                    Speed_Val[i].Out = 0;
                Motor[i] = Speed_Val[i].Out;//pid���
            }
        }
        else
        {
            Speed_Val[i].Out = 15;
            Motor[i] = Speed_Val[i].Out;//pwm�����
        }
    }
    Motor_Out(Motor);
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_MotorStop(float dT)
 * ��    �ܣ�������Ƿ�ֹͣ
*****************************************************************
*/
void Check_MotorStop(float dT)
{
	static float T[15];
    for(uint8_t i = 0;i<15;i++)
    {
        if(Work_Num[i].Motor_Stop)
        {
            if(Work_Num[i].Speed.Rel <= 100)
            {
                T[i] += dT;
                if(T[i] > 1.0f)
                {
                    Work_Num[i].Run_Status = 0;//�ر�
                    Work_Num[i].Motor_Stop = 0;//����Ѿ�ֹͣ
                    sys.SetMode_Option = 0;
                    SetOK_Flag = 1;
                    Twinkle_Time = 0;
                    if(Work_Num[0].Run_Status != 1 && Work_Num[1].Run_Status != 1 
                    && Work_Num[2].Run_Status != 1 && Work_Num[3].Run_Status != 1
                    && Work_Num[4].Run_Status != 1 && Work_Num[5].Run_Status != 1
                    && Work_Num[6].Run_Status != 1 && Work_Num[7].Run_Status != 1
                    && Work_Num[8].Run_Status != 1 && Work_Num[9].Run_Status != 1
                    && Work_Num[10].Run_Status != 1 && Work_Num[11].Run_Status != 1
                    && Work_Num[12].Run_Status != 1 
                    && Work_Num[14].Run_Status != 1)//ϵͳû�����Ļ�
                    {
                        for(uint8_t i = 0;i<15;i++)
                        {
                            Work_Num[i].Time.Rel = Work_Num[i].Time.Set;
                        }
                    }
                    T[i] = 0;
                }
            }
        }
    }
}
