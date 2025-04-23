#include "Speed.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void Encoder_Init(void)
 * ��    �ܣ���������ʼ�� 
*****************************************************************
*/
void Encoder_Init(void)
{   
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);//Motor���벶��
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_Speed(float dT)
 * ��    �ܣ�����ٶ��Ƿ�ֹͣ-0.05s
*****************************************************************
*/
void Check_Speed(float dT)
{
	Speed_Cnt++;//ÿ50ms����
    if(Speed_Cnt >= 10)//0.5s����û�������벶��
	{
        Rel_Speed = 0;//���ٶ�����
		Speed_Cnt = 0;//��������
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ�void TIM3CaptureChannel3Callback(void)
 * ��    �ܣ�Tim3ͨ��3�����벶��ص�����
*****************************************************************
*/
uint32_t Capture, Capture1, Capture2;//����ͼ����ֵ
uint32_t rel;//ʵ�ʼ������ٶ�
void TIM3CaptureChannel1Callback(void)
{
    Capture1 = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_1);//���벶�񵽵���ֵ
    if(Capture1 > Capture2)//��ǰ����ֵ����֮ǰ����ʱ
        Capture = Capture1 - Capture2;//������񵽵���
    else//���뵱ǰ��ֵС��֮ǰ����ֵʱ����ʾ�����
        Capture = Capture1 + (0xFFFF - Capture2);//�õ�ǰ��ֵ����65535-֮ǰ��ֵ
    if(Capture < 100)//����
        return;
	rel = (60000000 / (Capture * 4))/60;//(60000000us/(���񵽵�ֵ*һȦ9������))/56�ļ��ٱ�,RM3100
    Capture2 = Capture1;//��ǰ��ֵ��ֵ��֮ǰ��ֵ������¼
    Rel_Speed = rel;
    Speed_Cnt = 0;//�ٶȼ������㣬�����ж��ٶ��Ƿ�Ϊ0
}

/*
*****************************************************************
 * ����ԭ�ͣ�void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
 * ��    �ܣ�TIM_IC�ص�����
*****************************************************************
*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM3)//����TIM3���ж�
    {
        if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_1)//����TIM3ͨ��һ���ж�
        {
            TIM3CaptureChannel1Callback();//��������ٶȵĺ���
        }     
    }
}
