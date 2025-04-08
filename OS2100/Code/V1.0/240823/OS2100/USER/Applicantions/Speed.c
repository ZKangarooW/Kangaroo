#include "Speed.h"

/**
 * @brief ��������ʼ��
 *
 */
void Encoder_Init(void)
{
    HAL_TIM_Base_Start_IT(&htim1);
    HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_2); // ����time1ͨ��2���벶��
}

/**
 * @brief ����ٶ��Ƿ�ֹͣ-0.05s
 *
 * @param dT ��������
 */
void Check_Speed(float dT)
{
    Speed.Stop_Cnt += dT;      // ÿ50ms����
    if (Speed.Stop_Cnt >= 1.0) // 0.5s����û�������벶��
    {
        Speed.Rel = 0;      // ���ٶ�����
        Speed.Stop_Cnt = 0; // ��������
    }
}

uint32_t capture, capture1, capture2;
float rel1;
/**
 * @brief Tim1ͨ��2�����벶��ص�����
 *
 */
void TIM1CaptureChannel2Callback(void)
{
    capture1 = __HAL_TIM_GET_COMPARE(&htim1, TIM_CHANNEL_2); // ��ȡTim14ͨ��1�����벶��
    if (capture1 > capture2)
        capture = capture1 - capture2;
    else
        capture = capture1 + (0xFFFF - capture2);
    rel1 = 10000.0f / (float)capture; // �����ٶ�
    capture2 = capture1;
    Speed.Rel = rel1 * 60 / 5; // ���ٶȸ�ֵ��L1��ʵ���ٶ�
    Speed.Stop_Cnt = 0;
}

/**
 * @brief TIM_IC�ص�����
 *
 * @param htim
 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM1)
    {
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
        {
            TIM1CaptureChannel2Callback();
        }
    }
}
