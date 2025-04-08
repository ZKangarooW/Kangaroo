#include "Speed.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void Encoder_Init(void)
 * ��    �ܣ���������ʼ�� 
*****************************************************************
*/
void Encoder_Init(void)
{   
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_3);//motor1 ���벶��
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
uint32_t Capture, Capture1, Capture2;
uint32_t rel;
void TIM3CaptureChannel3Callback(void)
{
    Capture1 = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_3);
    if(Capture1 > Capture2)
        Capture = Capture1 - Capture2;
    else
        Capture = Capture1 + (0xFFFF - Capture2);
    if(Capture < 100)
        return;
    rel = 60000000 / (Capture * 6);
    Capture2 = Capture1;
    if((rel - Rel_Speed < 1000 && rel - Rel_Speed > 0)  || (Rel_Speed - rel < 1000 && Rel_Speed - rel > 0))
	{
		Rel_Speed = rel;
	}
    Speed_Cnt =0;
}

/*
*****************************************************************
 * ����ԭ�ͣ�void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
 * ��    �ܣ�TIM_IC�ص�����
*****************************************************************
*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM3) 
    {
        if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_3) 
        {
            TIM3CaptureChannel3Callback();
        }     
    }
}
