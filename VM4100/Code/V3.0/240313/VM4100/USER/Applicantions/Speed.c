#include "Speed.h"

/**********ȫ�ֱ�������******/
uint8_t CAPTURE_Status = 0;//����״̬
uint8_t CAPTURE_First = 1;//�����һ���ߵ�ƽ
uint16_t TIM1CH1_CAPTURE_STA = 0;//����������
uint32_t TIM1CH1_CAPTURE_VAL;//�������ֵ
uint32_t P_Status = 1;//�������ڼ���״̬  1���� 0�ر�
float frq;//����Ƶ��ֵ

/*
*****************************************************************
 * ����ԭ�ͣ�void Encoder_Init(void)
 * ��    �ܣ���������ʼ��
*****************************************************************
*/
void Encoder_Init(void)
{
	HAL_TIM_Base_Start_IT(&htim1);//������ʱ��1
    HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_3);//����time1ͨ��3���벶��
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
 * ����ԭ�ͣ�void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 * ��    �ܣ���ʱ�������ص�����
*****************************************************************
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM1)
    {
        if(P_Status)//�������ڼ���״̬:����
        {    
            TIM1CH1_CAPTURE_STA++;//����������++
        }
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ�void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
 * ��    �ܣ����벶��ص�����
*****************************************************************
*/
uint32_t Capture,rel;//���벶�����ͼ������ٶ�
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if(CAPTURE_Status == 0)
    {   
        if(CAPTURE_First)//���񵽵�һ��������
        {
            CAPTURE_Status = 1;//������
            CAPTURE_First = 0;//��������һ�������ر�־
            TIM1CH1_CAPTURE_VAL = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_3);//��ȡ��ǰ�������ֵ
            Capture = TIM1CH1_CAPTURE_STA;//��ʱ��������ֵ
            Capture *= 50;//һ������50us��48000000/12/200 = 0.00005us��
            Capture += TIM1CH1_CAPTURE_VAL;//���벻�񵽵�΢��������֮ǰ���ڵ�ʱ��
			frq = 1.0 / (((float)Capture) / 1000000.0);//Ƶ�ʼ��㣬��1S/������/1000000.0) ;������/1000000.0)Ϊת����λΪS
			if(Param.type <=1 || Param.type==3)
				rel = 60 * frq / 2;//rpm
			else if(Param.type ==2)
				rel = 60 * frq / 2 / 30;//rpm
			Rel_Speed = rel;
            P_Status = 0;//�������ڼ���״̬:0�ر�
			Speed_Cnt = 0;//����ٶ�
            __HAL_TIM_SET_COUNTER(&htim1, 0);//������벶���ֵ
            __HAL_TIM_DISABLE(&htim1);//�رն�ʱ��һ����
        }
        else
        {
            TIM1CH1_CAPTURE_STA = 0;//������ڼ���
            TIM1CH1_CAPTURE_VAL = 0;//�������Ĵ���
            CAPTURE_First = 1;//�Ѳ����һ��������
            CAPTURE_Status = 0;//�������
            P_Status = 1;//�������ڼ���
        }
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ�void TIM1_Poll(void)
 * ��    �ܣ�TIM1��ѵ״̬�л�
*****************************************************************
*/
void TIM1_Poll(void)
{
    if(CAPTURE_Status)
	{	
		__HAL_TIM_ENABLE(&htim1);//����������ʱ��һ����
		CAPTURE_Status=0;//����״̬Ϊ0
		TIM1CH1_CAPTURE_STA=0;//�������������
	}
}
