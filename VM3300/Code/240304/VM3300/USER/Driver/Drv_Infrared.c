#include "Drv_Infrared.h"

/**********�ṹ��************/
_Infrared_ Infrared[2];

/**********�ֲ���������*******/
uint32_t Infrared_Time;//���͵�ʱ��
uint8_t Infrared_Step;//���͵Ĳ���

/**
 * @brief ����������ʼ��
 *
 */
void Drv_Infrared_Init(void)
{
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);//����tim3ͨ��һ
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);//����tim3ͨ����
	
	HAL_TIM_IC_Start_IT(&htim15, TIM_CHANNEL_1);   //����tim15ͨ��1�Ĳ����жϷ�ʽ��
	HAL_TIM_IC_Start_IT(&htim15, TIM_CHANNEL_2);   //����tim15ͨ��2�Ĳ����жϷ�ʽ��
	__HAL_TIM_ENABLE_IT(&htim15, TIM_IT_UPDATE);   //����ʹ���ж�
	
	HAL_TIM_Base_Start_IT(&htim6);//��ʼ��ʱ��
}

/**
 * @brief ����ٶ��Ƿ�ֹͣ-0.05s
 *
 * @param dT ��������
 */
void Check_Infrared(float dT)
{
    Infrared[0].Someone_Time += dT;//ÿ100ms����
	Infrared[1].Someone_Time += dT;//ÿ100ms����
    if (Infrared[0].Someone_Time >= 0.5f)// 0.5s����û�������벶��
    {
        Infrared[0].Someone = 0;// ����������
        Infrared[0].Someone_Time = 0;//��������
    }
	if (Infrared[1].Someone_Time >= 0.5f)// 0.5s����û�������벶��
    {
        Infrared[1].Someone = 0;// ����������
        Infrared[1].Someone_Time = 0;//��������
    }
}

/**
 * @brief ��ʱ�������ж�
 *
 */
void Infrared_TIM_Interrupt(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == htim6.Instance) 
	{
		if(Infrared_Step == 0)
		{
			Infrared_Send1 = 79;
//			Infrared_Send2 = 79;
			Infrared_Time++;
			if(Infrared_Time >= 900)
			{
				Infrared_Step = 1;
				Infrared_Time = 0;
			}
		}
		if(Infrared_Step == 1)
		{
			Infrared_Send1 = 0;
//			Infrared_Send2 = 0;
			Infrared_Time++;
			if(Infrared_Time >= 225)
			{
				Infrared_Step = 2;
				Infrared_Time = 0;
			}
		}
		if(Infrared_Step == 2)
		{
			Infrared_Send1 = 79;
//			Infrared_Send2 = 79;
			Infrared_Time++;
			if(Infrared_Time >= 56)
			{
				Infrared_Step = 3;
				Infrared_Time = 0;
			}
		}
		if(Infrared_Step == 3)
		{
			Infrared_Send1 = 0;
//			Infrared_Send2 = 0;
			Infrared_Time++;
			if(Infrared_Time >= 9819)
			{
				Infrared_Step = 0;
				Infrared_Time = 0;
			}
		}
	}
}

/**
 * @brief �������źű仯��ʱ������
 *
 */
void Infrared_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM15)
	{
		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
		{
			if(IR1_IN)//capture��������
			{
				TIM_RESET_CAPTUREPOLARITY(&htim15, TIM_CHANNEL_2);//�������������
				TIM_SET_CAPTUREPOLARITY(&htim15, TIM_CHANNEL_2, TIM_ICPOLARITY_FALLING);//��ʼ�����½���
				__HAL_TIM_SET_COUNTER(&htim15, 0);//��ն�ʱ��ֵ
				Infrared[0].IRSta |= 0x10;//[4]��1������־�������Ѳ���
			}
			else  //�����½���
			{
				Infrared[0].Dval = HAL_TIM_ReadCapturedValue(&htim15, TIM_CHANNEL_2);//�½��ؼ���
				TIM_RESET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_2);//��������½���
				TIM_SET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_2,TIM_ICPOLARITY_RISING);//��ʼ����������
				if(Infrared[0].IRSta & 0x10)  //��������һ�θߵ�ƽ���񣬽��������Ƿ���������
				{
					if(Infrared[0].Dval>2100 && Infrared[0].Dval<2400)//2.25ms�ߵ�ƽ��������
					{
						Infrared[0].Someone = 1;
						Infrared[0].Someone_Time = 0;
						Infrared[0].IRSta &= 0xF0;  
					}
				}	
				Infrared[0].IRSta &=~(1<<4);//���[4]�����ߵ�ƽ��������
			}
		}
//		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
//		{
//			if(IR2_IN)//capture��������
//			{
//				TIM_RESET_CAPTUREPOLARITY(&htim15, TIM_CHANNEL_1);//�������������
//				TIM_SET_CAPTUREPOLARITY(&htim15, TIM_CHANNEL_1, TIM_ICPOLARITY_FALLING);//��ʼ�����½���
//				__HAL_TIM_SET_COUNTER(&htim15, 0);//��ն�ʱ��ֵ
//				Infrared[1].IRSta |= 0x10;//[4]��1������־�������Ѳ���
//			}
//			else  //�����½���
//			{
//				Infrared[1].Dval = HAL_TIM_ReadCapturedValue(&htim15, TIM_CHANNEL_1);//�½��ؼ���
//				TIM_RESET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_1);//��������½���
//				TIM_SET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);//��ʼ����������
//				if(Infrared[1].IRSta & 0x10)//��������һ�θߵ�ƽ���񣬽��������Ƿ���������
//				{
//					if(Infrared[1].Dval>2100 && Infrared[1].Dval<2600)//2.25ms�ߵ�ƽ��������
//					{
//						Infrared[1].Someone = 1;
//						Infrared[1].Someone_Time = 0;
//						Infrared[1].IRSta &= 0xF0;  
//					}
//				}	
//				Infrared[1].IRSta &=~(1<<4); //���[4]�����ߵ�ƽ��������
//			}
//		}
	}
}
