#include "Speed.h"

uint32_t capture[15], capture1[15], capture2[15];
float frq[15];

/**
 * @brief ��������ʼ��
 *
 */
void Encoder_Init(void)
{
    HAL_TIM_Base_Start_IT(&htim3);
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);//����time3ͨ��1���벶��
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_2);//����time3ͨ��2���벶��
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_3);//����time3ͨ��3���벶��
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_4);//����time3ͨ��4���벶��
    HAL_TIM_Base_Start_IT(&htim2);
    HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);//����time2ͨ��1���벶��
    HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);//����time2ͨ��2���벶��
    HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_3);//����time2ͨ��3���벶��
    HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_4);//����time2ͨ��4���벶��
    HAL_TIM_Base_Start_IT(&htim4);
    HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_1);//����time4ͨ��1���벶��
    HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_2);//����time4ͨ��2���벶��
    HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_3);//����time4ͨ��3���벶��
    HAL_TIM_Base_Start_IT(&htim8);
    HAL_TIM_IC_Start_IT(&htim8, TIM_CHANNEL_1);//����time8ͨ��1���벶��
    HAL_TIM_IC_Start_IT(&htim8, TIM_CHANNEL_2);//����time8ͨ��2���벶��
    HAL_TIM_IC_Start_IT(&htim8, TIM_CHANNEL_3);//����time8ͨ��3���벶��
    HAL_TIM_IC_Start_IT(&htim8, TIM_CHANNEL_4);//����time8ͨ��4���벶��
}

/**
 * @brief ����ٶ��Ƿ�ֹͣ-0.05s
 *
 * @param dT ��������
 */
void Check_Speed(float dT)
{
    for(uint8_t i = 0;i<15;i++)
    {
        Work_Num[i].Speed.Stop_Cnt += dT;//ÿ50ms����
        if (Work_Num[i].Speed.Stop_Cnt >= 1.0) // 0.5s����û�������벶��
        {
            Work_Num[i].Speed.Rel = 0;      // ���ٶ�����
            Work_Num[i].Speed.Stop_Cnt = 0; // ��������
        }
    }
}

/**
 * @brief Tim3ͨ��4�����벶��ص�����
 *
 */
void CaptureChanneCallback(uint8_t i)
{
    if (capture1[i] > capture2[i])
        capture[i] = capture1[i] - capture2[i];
    else
        capture[i] = capture1[i] + (0xFFFF - capture2[i]);
    frq[i] = 10000.0f / (float)capture[i];//����Ƶ��
    capture2[i] = capture1[i];
    Work_Num[i].Speed.Rel = frq[i] * 60 / 5;
    Work_Num[i].Speed.Stop_Cnt = 0;
}

/**
 * @brief TIM_IC�ص�����
 *
 * @param htim
 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM3)
    {
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
        {
            capture1[6] = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_1);//��ȡTim3ͨ��1�����벶��
            CaptureChanneCallback(6);
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
        {
            capture1[7] = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_2);//��ȡTim3ͨ��2�����벶��
            CaptureChanneCallback(7);
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
        {
            capture1[9] = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_3);//��ȡTim3ͨ��3�����벶��
            CaptureChanneCallback(9);
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)
        {
            capture1[10] = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_4);//��ȡTim3ͨ��4�����벶��
            CaptureChanneCallback(10);
        }
    }
    if (htim->Instance == TIM2)
    {
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
        {
            capture1[0] = __HAL_TIM_GET_COMPARE(&htim2, TIM_CHANNEL_1);//��ȡTim3ͨ��1�����벶��
            CaptureChanneCallback(0);
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
        {
            capture1[1] = __HAL_TIM_GET_COMPARE(&htim2, TIM_CHANNEL_2);//��ȡTim3ͨ��2�����벶��
            CaptureChanneCallback(1);
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
        {
            capture1[3] = __HAL_TIM_GET_COMPARE(&htim2, TIM_CHANNEL_3);//��ȡTim3ͨ��3�����벶��
            CaptureChanneCallback(3);
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)
        {
            capture1[4] = __HAL_TIM_GET_COMPARE(&htim2, TIM_CHANNEL_4);//��ȡTim3ͨ��4�����벶��
            CaptureChanneCallback(4);
        }
    }
    if (htim->Instance == TIM4)
    {
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
        {
            capture1[8] = __HAL_TIM_GET_COMPARE(&htim4, TIM_CHANNEL_1);//��ȡTim3ͨ��1�����벶��
            CaptureChanneCallback(8);
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
        {
            capture1[11] = __HAL_TIM_GET_COMPARE(&htim4, TIM_CHANNEL_2);//��ȡTim3ͨ��2�����벶��
            CaptureChanneCallback(11);
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
        {
            capture1[14] = __HAL_TIM_GET_COMPARE(&htim4, TIM_CHANNEL_3);//��ȡTim3ͨ��3�����벶��
            CaptureChanneCallback(14);
        }
    }
    if (htim->Instance == TIM8)
    {
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
        {
            capture1[12] = __HAL_TIM_GET_COMPARE(&htim8, TIM_CHANNEL_1);//��ȡTim3ͨ��1�����벶��
            CaptureChanneCallback(12);
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
        {
            capture1[13] = __HAL_TIM_GET_COMPARE(&htim8, TIM_CHANNEL_2);//��ȡTim3ͨ��2�����벶��
            CaptureChanneCallback(13);
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
        {
            capture1[2] = __HAL_TIM_GET_COMPARE(&htim8, TIM_CHANNEL_3);//��ȡTim3ͨ��3�����벶��
            CaptureChanneCallback(2);
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)
        {
            capture1[5] = __HAL_TIM_GET_COMPARE(&htim8, TIM_CHANNEL_4);//��ȡTim3ͨ��4�����벶��
            CaptureChanneCallback(5);
        }
    }
}
