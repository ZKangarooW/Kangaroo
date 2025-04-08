#include "Ctrl_Motor.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void Motor_Ctrl(float dT)
 * ��    �ܣ��������
*****************************************************************
*/
uint16_t Ctrl_Val;
void Motor_Ctrl(float dT)
{   
    if(sys.Run_Status == 1)//����
    {
		if(Ctrl_Speed && ((DownTime_Over == 0)||(Ctrl_Time)))//�ٶȴ���0�Ͷ�ʱ��û�н���
		{
			if(sys.Motor_Stop)//��ֹͣ����ģʽ��
			{			
				PID_Speed(0,Rel_Speed,&Speed_Arg,&Speed_Val);//���PID����
				__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,Speed_Val.Out);
			}
			else
			{	
                if(Ctrl_Speed >= 2200)
                    Ctrl_Val = 2600-(3000 - Ctrl_Speed)/2;
                else
                    Ctrl_Val = Ctrl_Speed;
				PID_Speed(Ctrl_Val,Rel_Speed,&Speed_Arg,&Speed_Val);//���PID����ת��
				__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,Speed_Val.Out);
			}
		}
		else
		{
			sys.Motor_Stop = 1;//�����
			if(sys.Motor_Stop)//��ֹͣ����ģʽ��
			{
				PID_Speed(0,Rel_Speed,&Speed_Arg,&Speed_Val);//���PID����
				__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,Speed_Val.Out);
			}
		}
    }
    else
    {
        __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,0);
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
	static float T;
	if(sys.Motor_Stop)//��ֹͣ����ģʽ��
	{
		if(Rel_Speed < 10)
		{
			T += dT;//ʱ���dT
			if(T>0.5f)//�ٶ�Ϊ��ʱ�����1Sʱ
			{
				SetOK_Flag = 1;//���ò�����һ
				sys.Run_Status = 0;//�ر�
				sys.Motor_Stop = 0;//����Ѿ�ֹͣ
				Time_State = 0;//ʱ����ʾ
				T = 0;//ʱ������
			}
		}
	}
	else
	{
		T = 0;//ʱ������
	}
}
