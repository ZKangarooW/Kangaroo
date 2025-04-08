#include "Speed.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void Encoder_Init(void)
 * ��    �ܣ���������ʼ�� 
*****************************************************************
*/
void Encoder_Init(void)
{   
    HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);//motor1 ���벶��
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_Speed(float dT)
 * ��    �ܣ�����ٶ��Ƿ�ֹͣ-0.05s
*****************************************************************
*/
void Check_Speed(float dT)
{
	Speed.Stop_Cnt++;//ÿ50ms����
    if(Speed.Stop_Cnt >= 10)//0.5s����û�������벶��
	{
        Speed.Rel = 0;//���ٶ�����
		Speed.Stop_Cnt = 0;//��������
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ�void TIM1CaptureChannel1Callback(void)
 * ��    �ܣ�Tim1ͨ��1�����벶��ص�����
*****************************************************************
*/
uint32_t Capture, Capture1, Capture2;
uint32_t rel;
void TIM1CaptureChannel1Callback(void)
{
    Capture1 = __HAL_TIM_GET_COMPARE(&htim1, TIM_CHANNEL_1);//��ȡ��������ֵ
    if(Capture1 > Capture2)//���������ֵ������һ�ε�ֵ
        Capture = Capture1 - Capture2;//�ó���ǰ��ֵ
    else
        Capture = Capture1 + (0xFFFF - Capture2);//���С���ϴε�ֵ��0xFFFF-��һ�ε�ֵ
    if(Capture < 100)//����С��100��
        return;
    rel = 60000000 / (Capture * 12);//��1S/��������ֵ*һȦ������
    Capture2 = Capture1;//��������ֵ��ֵ����һ�ε�ֵ
	Speed.Rel = rel;
    Speed.Stop_Cnt = 0;//������ٶȵ�ʱ������
}

/*
*****************************************************************
 * ����ԭ�ͣ�void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
 * ��    �ܣ�TIM_IC�ص�����
*****************************************************************
*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM1) 
    {
        if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_1) 
        {
            TIM1CaptureChannel1Callback();
        }     
    }
}
