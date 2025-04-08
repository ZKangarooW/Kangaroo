#include "Ctrl_Motor.h"

/**********�ṹ��************/
_PID_Arg_ Speed_Arg;
_PID_Val_ Speed_Val[4];

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

int8_t Motor[4];//���������pwmֵ
/*
*****************************************************************
 * ����ԭ�ͣ�void Motor_Out(int16_t Motor_Pwm[MOTOR_NUM])
 * ��    �ܣ��������
 * ��    �룺int16_t Motor_Pwm[MOTOR_NUM]
 * ��    ����Motor_Pwm[MOTOR_NUM]����Motor��PWMռ�ձ�ֵ
*****************************************************************
*/
void Motor_Out(int8_t Motor_Pwm[4])
{
    PWM0 = (uint8_t)Motor_Pwm[0];
    PWM1 = (uint8_t)Motor_Pwm[1];
    PWM2 = (uint8_t)Motor_Pwm[2];
    PWM3 = (uint8_t)Motor_Pwm[3];
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Motor_Ctrl(float dT)
 * ��    �ܣ��������
*****************************************************************
*/
void Motor_Ctrl(float dT)
{
    for(uint8_t i = 0;i<4;i++)
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
                    if(Speed_Val[i].Out <= 20)
                        Speed_Val[i].Out = 20;
                    Motor[i] = Speed_Val[i].Out;//pid���
                    
                }
            }
            else
            {
                if(Speed_Val[i].Out)
                    Speed_Val[i].Out -= 1;//����̫��*2
                if(Speed_Val[i].Out < 20)
                {
                    Speed_Val[i].Out = 0;
                }
                Motor[i] = Speed_Val[i].Out;//pid���
            }
        }
        else
        {
            Speed_Val[i].Integral = 20;
            Motor[i] = 0;//pwm�����
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
	static float T[4];
    for(uint8_t i = 0;i<4;i++)
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
                    if(Work_Num[0].Run_Status != 1 && Work_Num[1].Run_Status != 1 && 
                    Work_Num[2].Run_Status != 1 && Work_Num[3].Run_Status != 1)//ϵͳû�����Ļ�
                    {
                        Work_Num[0].Time.Rel = Work_Num[0].Time.Set;
                        Work_Num[1].Time.Rel = Work_Num[1].Time.Set;
                        Work_Num[2].Time.Rel = Work_Num[2].Time.Set;
                        Work_Num[3].Time.Rel = Work_Num[3].Time.Set;
                    }
                    T[i] = 0;
                }
            }
        }
    }
}
