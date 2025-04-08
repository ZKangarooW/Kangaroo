#include "Speed.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void Encoder_Init(void)
 * ��    �ܣ���������ʼ��
*****************************************************************
*/
void Encoder_Init(void)
{
	HAL_TIM_Base_Start_IT(&htim3);
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);//����time1ͨ��3���벶��
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_Speed(float dT)
 * ��    �ܣ�����ٶ��Ƿ�ֹͣ-0.05s
*****************************************************************
*/
void Check_Speed(float dT)
{
	Speed.Stop_Cnt += dT;//ÿ50ms����
    if(Speed.Stop_Cnt >= 1.0)//0.5s����û�������벶��
	{
        Speed.Rel = 0;//���ٶ�����
		Speed.Stop_Cnt = 0;//��������
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ�void TIM3CaptureChannel1Callback(void)
 * ��    �ܣ�Tim3ͨ��1�����벶��ص�����
*****************************************************************
*/
uint32_t L1_capture,L1_capture1,L1_capture2;
float rel1;
void TIM3CaptureChannel1Callback(void)
{
    L1_capture1=__HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_1);//��ȡTim3ͨ��1�����벶��
    if(L1_capture1>L1_capture2)
        L1_capture=L1_capture1-L1_capture2;
    else
        L1_capture=L1_capture1+(0xFFFF-L1_capture2);
    if(L1_capture<100)
        return;
    rel1=10000.0f/(float)L1_capture;//�����ٶ�
    L1_capture2=L1_capture1;
    Speed.Rel=rel1*60/2;//���ٶȸ�ֵ��L1��ʵ���ٶ�	
    Speed.Stop_Cnt = 0;
}	

/*
*****************************************************************
 * ����ԭ�ͣ� void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
 * ��    �ܣ� TIM_IC�ص�����
*****************************************************************
*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM3) 
    {
        if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_1) 
        {
            TIM3CaptureChannel1Callback();
        } 
    }
}
