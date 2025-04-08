#include "Ctrl_Motor.h"

/**********�ṹ��************/
_PID_Arg_ Speed_Arg;
_PID_Val_ Speed_Val[4];
int8_t Motor[4];//���������pwmֵ

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
        if(sys.Run_Status)//����
        {
            HAL_GPIO_WritePin(MO_GPIO_Port, MO_Pin, GPIO_PIN_SET);//��ʹ�ܵ��
            if(Speed.Ctrl)
            {
                if(sys.Motor_Stop)
                {
                    if(Speed_Val[i].Out)
                        Speed_Val[i].Out -= 1;//����̫��*2
                    if(Speed_Val[i].Out < 0)
                        Speed_Val[i].Out = 0;
                    Motor[i] = Speed_Val[i].Out;//pid���
                }
                else
                {
                    AltPID_Calculation(dT,Speed.Ctrl,Speed.Rel[i],&Speed_Arg,&Speed_Val[i],200,200);//���PID����
                    if(Speed_Val[i].Out < 20)
                        Speed_Val[i].Out = 20;
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
            Speed_Val[i].Integral = 20;
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
	static float T;
    if(sys.Motor_Stop)
    {
        if(Speed.Display_Rel <= 300)
        {
            T += dT;
            if(T > 1.0f)
            {
                sys.Run_Status = 0;//�ر�
                sys.Motor_Stop = 0;//����Ѿ�ֹͣ
                HAL_GPIO_WritePin(MO_GPIO_Port, MO_Pin, GPIO_PIN_RESET);//��ʹ�ܵ��
                TimeSet_Flag=1;//���ñ���
                T = 0;
            }
        }
    }
}
