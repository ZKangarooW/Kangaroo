#include "Speed.h"

uint32_t capture, capture1, capture2;
float frq;

/**
 * @brief ��������ʼ��
 *
 */
void Encoder_Init(void)
{
    HAL_TIM_Base_Start_IT(&htim16);
    HAL_TIM_IC_Start_IT(&htim16, TIM_CHANNEL_1);//����time3ͨ��1���벶��
}

/**
 * @brief ����ٶ��Ƿ�ֹͣ-0.05s
 *
 * @param dT ��������
 */
void Check_Speed(float dT)
{
    Speed.Stop_Cnt += dT;//ÿ50ms����
    if (Speed.Stop_Cnt >= 1.0) // 0.5s����û�������벶��
    {
        Speed.Rel = 0;      // ���ٶ�����
        Speed.Stop_Cnt = 0; // ��������
    }
}

/**
 * @brief Tim16ͨ��1�����벶��ص�����
 *
 */
void CaptureChanneCallback(void)
{
    if (capture1 > capture2)
        capture = capture1 - capture2;
    else
        capture = capture1 + (0xFFFF - capture2);
    frq = 10000.0f / (float)capture;//����Ƶ��
    capture2 = capture1;
    Speed.Rel = frq * 60 / 5;
    Speed.Stop_Cnt = 0;
}

/**
 * @brief TIM_IC�ص�����
 *
 * @param htim
 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM16)
    {
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
        {
            capture1 = __HAL_TIM_GET_COMPARE(&htim16, TIM_CHANNEL_1);//��ȡTim3ͨ��1�����벶��
            CaptureChanneCallback();
        }
        
    }
}
