#include "Speed.h"

/**********�ֲ���������******/
uint32_t high,cycle;//�ߵ�ƽʱ�䣨us����������ʱ�䣨us��
float frq;//����Ƶ��ֵ
__IO uint32_t TIM1_TIMEOUT_COUNT = 0;//��ʱ��1��ʱ�������
uint32_t TIM1_CAPTURE_BUF[3] = {0, 0, 0};//�ֱ�洢�����ؼ������½��ؼ������¸������ؼ���
__IO uint8_t TIM1_CAPTURE_STA = 0;//״̬���

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
	Speed.Cnt++;//ÿ50ms����
    if(Speed.Cnt >= 10)//0.5s����û�������벶��
	{
        Speed.Rel = 0;//���ٶ�����
		Speed.Cnt = 0;//��������
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ�void TIM1_SetCapturePolarity(uint32_t TIM_ICPolarity)
 * ��    �ܣ�����TIM1���벶����
 * ��    ��: TIM_INPUTCHANNELPOLARITY_RISING  �������ز���
 *           TIM_INPUTCHANNELPOLARITY_FALLING ���½��ز���
 *           TIM_INPUTCHANNELPOLARITY_BOTHEDGE�������غ��½��ض�����
*****************************************************************
*/
void TIM1_SetCapturePolarity(uint32_t TIM_ICPolarity)
{
    htim1.Instance->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC1NP);
    htim1.Instance->CCER |= (TIM_ICPolarity & (TIM_CCER_CC1P | TIM_CCER_CC1NP));
}

/*
*****************************************************************
 * ����ԭ�ͣ�void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 * ��    �ܣ���ʱ��1ʱ������ص�����
*****************************************************************
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == htim1.Instance)
    {
        TIM1_TIMEOUT_COUNT++;//�����������
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ�void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
 * ��    �ܣ����벶��ص�����
*****************************************************************
*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == htim1.Instance)
    {
        Speed.Cnt = 0;
        switch (TIM1_CAPTURE_STA)
        {
        case 1:
            {
                TIM1_CAPTURE_BUF[0] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1) + TIM1_TIMEOUT_COUNT * 50;//��Ϊ���ڸߵ�ƽ�Σ�����25�ļ��㷽ʽΪ=��1/(48000000/��Ƶ��12)*����ֵ200��/�����ص�ԭ�����Գ���2
                TIM1_SetCapturePolarity(TIM_INPUTCHANNELPOLARITY_FALLING);//����Ϊ�½��ش���
                TIM1_CAPTURE_STA++;//��һ����
                break;
            }
        case 2:
            {
                TIM1_CAPTURE_BUF[1] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1) + TIM1_TIMEOUT_COUNT * 50;//��Ϊ���ڵ͵�ƽ�Σ�����25�ļ��㷽ʽΪ=��1/(48000000/��Ƶ��12)*����ֵ200��/�½��ص�ԭ�����Գ���2
                TIM1_SetCapturePolarity(TIM_INPUTCHANNELPOLARITY_RISING);//����Ϊ�����ش���
                TIM1_CAPTURE_STA++;//��һ����
                break;
            }
        case 3:
            {
                TIM1_CAPTURE_BUF[2] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1) + TIM1_TIMEOUT_COUNT * 50;//��Ϊ���ڸߵ�ƽ�Σ�����25�ļ��㷽ʽΪ=��1/(48000000/��Ƶ��12)*����ֵ200��/�����ص�ԭ�����Գ���2
                HAL_TIM_IC_Stop_IT(htim, TIM_CHANNEL_1);//ֹͣ����
                HAL_TIM_Base_Stop_IT(&htim1);//ֹͣ��ʱ�������ж�
                TIM1_CAPTURE_STA++;//��һ����
                break;
            }
        default:
            break;
        }
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ�void TIM1_Poll(void)
 * ��    �ܣ�TIM1��ѵ״̬�л�
*****************************************************************
*/
uint32_t rel;
void TIM1_Poll(void)
{
    switch (TIM1_CAPTURE_STA)
    {
    case 0:
        {
            TIM1_TIMEOUT_COUNT = 0;//�������
            __HAL_TIM_SET_COUNTER(&htim1, 0);//�����ʱ��2���м���
            memset(TIM1_CAPTURE_BUF, 0, sizeof(TIM1_CAPTURE_BUF));//����������
            TIM1_SetCapturePolarity(TIM_INPUTCHANNELPOLARITY_RISING);//����Ϊ�����ش���
            HAL_TIM_Base_Start_IT(&htim1);//������ʱ�������ж�
            HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);//���������ж�
            TIM1_CAPTURE_STA++;//��һ����
            break;
        }
    case 4:
        {
            high  = TIM1_CAPTURE_BUF[1] - TIM1_CAPTURE_BUF[0];//�ߵ�ƽ����ʱ��
            cycle = TIM1_CAPTURE_BUF[2] - TIM1_CAPTURE_BUF[0];//����  
            frq = 1.0 / (((float)cycle) / 1000000.0);//Ƶ�ʼ��㣬��1S/������/1000000.0) ;������/1000000.0)Ϊת����λΪS
            TIM1_CAPTURE_STA = 0;//���²��ƽ
			rel = 60 * frq / 2;//��һ����/�ߵ�ƽʱ��/�����һȦ����
            Speed.Rel = rel;
            break;
        }
    default:
        break;
    }
}
