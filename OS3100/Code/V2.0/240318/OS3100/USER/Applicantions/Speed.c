#include "Speed.h"

/*
*****************************************************************
 * ����ԭ�ͣ� void Encoder_Init(void)
 * ��    �ܣ� ��������ʼ�� 
*****************************************************************
*/
void Encoder_Init(void)
{   
	HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_2);//motor���벶��
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Check_Speed(void)
 * ��    �ܣ� ����ٶ��Ƿ�ֹͣ
*****************************************************************
*/
void Check_Speed(void)
{
   Speed_Cnt++;//ÿ50ms����
    if(Speed_Cnt>=10)//0.5s����û�������벶��
        Rel_Speed = 0;//���ٶ�����
}

/*
*****************************************************************
 * ����ԭ�ͣ� void TIM1CaptureChannel2Callback(void)
 * ��    �ܣ� Tim1ͨ��2�����벶��ص�����
*****************************************************************
*/
uint32_t capture, capture1, capture2;
uint32_t rel;
void TIM1CaptureChannel2Callback()
{
	if(sys.Run_Status == 1)
	{
		capture1 = __HAL_TIM_GET_COMPARE(&htim1, TIM_CHANNEL_2);
		if(capture1 > capture2)
			capture = capture1 - capture2;
		else
			capture = capture1 + (0xFFFF - capture2);
		if(capture < 100)
			return;
		rel = 60000000 / capture / 5;
		if((rel - Rel_Speed < 500 && rel - Rel_Speed > 0)  || (Rel_Speed - rel < 500 && Rel_Speed - rel > 0))
			Rel_Speed = rel;
		capture2 = capture1;
		Speed_Cnt = 0;
	}
	else
	{
		capture1 = 0;
		capture2 = 0;
		rel = 0;
	}
}


/*
*****************************************************************
 * ����ԭ�ͣ� void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
 * ��    �ܣ� TIM_IC�ص�����
*****************************************************************
*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM1)
    {
        if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
        {
            TIM1CaptureChannel2Callback();
        }
    }

}
