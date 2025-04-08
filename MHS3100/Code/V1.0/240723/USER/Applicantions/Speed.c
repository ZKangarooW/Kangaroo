#include "Speed.h"

/**********ȫ�ֱ�������******/
uint32_t capture[4], capture1[4], capture2[4];
int16_t FilterSpeed[4];//�˲����ٶ�
float frq[4];

/*
*****************************************************************
 * ����ԭ�ͣ�void Encoder_Init(void)
 * ��    �ܣ���������ʼ��
*****************************************************************
*/
void Encoder_Init(void)
{
	HAL_TIM_Base_Start_IT(&htim3);
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);//����time3ͨ��1���벶��
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_2);//����time3ͨ��2���벶��
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_3);//����time3ͨ��3���벶��
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_4);//����time3ͨ��4���벶��
}

/*
*****************************************************************
 * ����ԭ�ͣ�int Filter_ADC(void)
 * ��    �ܣ�����ƽ��ֵ�˲�
 * ��    �����˲����ֵ
*****************************************************************
*/
#define S 10//�ɼ�10��
int SpeedValue_Buf[4][S];//���ڴ���ɼ�����Speedֵ
int k[4];//����ֵ
int Filter_Speed(uint8_t new_work,int16_t speed)
{
    char count;
    long sum = 0;

    SpeedValue_Buf[new_work][k[new_work]++] = speed;
	
    if(k[new_work] == S)//�������100��ʹ��¿�ʼ
    {
        k[new_work] = 0;
    }
    for(count = 0; count < S; count++)
    {
        sum += SpeedValue_Buf[new_work][count];//100�����
    }
    if(SpeedValue_Buf[new_work][S-1] == 0)//���û�ж���100����õ�һ�ζ�������
        return SpeedValue_Buf[new_work][0];
    else//����100���
        return (int)(sum / S);//���ƽ��ֵ
}

/**
 * @brief ����ٶ��Ƿ�ֹͣ-0.05s
 *
 * @param dT ��������
 */
void Check_Speed(float dT)
{
    for(uint8_t i = 0;i<4;i++)
    {
        Speed.Stop_Cnt[i] += dT;//ÿ50ms����
        if (Speed.Stop_Cnt[i] >= 1.0) // 1.0s����û�������벶��
        {
            FilterSpeed[i] = 0;
            k[i] = 0;
            memset(SpeedValue_Buf[i],0,sizeof (SpeedValue_Buf[i]));
            Speed.Rel[i] = 0;// ���ٶ�����
            Speed.Stop_Cnt[i] = 0; // ��������
        }
    }
}

/**
 * @brief ���벶��ص�����
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
    FilterSpeed[i] = frq[i] * 60 / 2;
    Speed.Rel[i] = Filter_Speed(i, FilterSpeed[i]);//���ٶȸ�ֵ��L1��ʵ���ٶ�
//    Speed.Rel[i] = FilterSpeed[i];
    Speed.Stop_Cnt[i] = 0;
}

/**
 * @brief TIM_IC�ص�����
 *
 * @param htim
 */
void Speed_Capture_Interrupt(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM3)
    {
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
        {
            capture1[0] = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_1);//��ȡTim3ͨ��1�����벶��
            CaptureChanneCallback(0);
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
        {
            capture1[1] = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_2);//��ȡTim3ͨ��2�����벶��
            CaptureChanneCallback(1);
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
        {
            capture1[2] = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_3);//��ȡTim3ͨ��3�����벶��
            CaptureChanneCallback(2);
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)
        {
            capture1[3] = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_4);//��ȡTim3ͨ��4�����벶��
            CaptureChanneCallback(3);
        }
    }
}
