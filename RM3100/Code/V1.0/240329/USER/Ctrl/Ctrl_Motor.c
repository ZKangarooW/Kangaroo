#include "Ctrl_Motor.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void Motor_Ctrl(float dT)
 * ��    �ܣ��������
*****************************************************************
*/
void Motor_Ctrl(float dT)
{   
    if(sys.Run_Status == 1)//����
    {
		if(Ctrl_Speed && ((DownTime_Over == 0)||(Ctrl_Time)))//�ٶȴ���0�Ͷ�ʱ��û�н���
		{
			if(sys.Motor_Stop)//��ֹͣ����ģʽ��
			{			
				if(Speed_Val.Out)
				{
					Speed_Val.Out -= (dT*6);
				}
				PWM = Speed_Val.Out;//PID���
			}
			else
			{	
				PID_Speed(Ctrl_Speed,Rel_Speed,&Speed_Arg,&Speed_Val);//���PID����
//				if(Speed_Val.Out < 100)
//					Speed_Val.Out = 100;
				PWM = Speed_Val.Out;//PID���
			}
		}
		else
		{
			sys.Motor_Stop = 1;//�����
			if(sys.Motor_Stop)//��ֹͣ����ģʽ��
			{
				if(Speed_Val.Out)
				{
					Speed_Val.Out -= (dT*6);
				}
				PWM = Speed_Val.Out;//PID���
			}
		}
    }
    else
    {
        PWM = 0;//PWM�����
		Speed_Val.SumError = 0;//��ֹ�ر��ٴ�ʱ�ٶ�һ���Ӿͳ嵽֮ǰ���ٶ�	
    }      
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_MotorStop(float dT)
 * ��    �ܣ�������Ƿ�ֹͣ
*****************************************************************
*/
void Check_MotorStop(float dT)
{
	if(sys.Motor_Stop)//��ֹͣ����ģʽ��
	{
		if(Rel_Speed <= 15)//�ٶ�Ϊ15
		{
			SetOK_Flag = 1;//���ò�����һ
			sys.Run_Status = 0;//�ر�
			sys.Motor_Stop = 0;//����Ѿ�ֹͣ
		}
	}
}
