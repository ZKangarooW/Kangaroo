#include "Drv_Remote.h"

uint8_t IRSta = 0; //����״̬��[0:3]�����������[4]����������Ƿ��Ѿ�������,[5]������[6]�õ���һ��������ȫ����Ϣ,[7]�յ����������־
uint16_t Dval; //�ߵ�ƽ��������ֵ�����ݴ��жϸߵ͵�ƽ��ʱ��
uint32_t IRData = 0;  //������յ�����
uint8_t keyCount =0;
uint8_t Remote_Flag;
/**
 * @brief ����ٶ��Ƿ�ֹͣ-0.05s
 *
 * @param dT ��������
 */
float cnt;
void Check_Remote(float dT)
{
    cnt += dT;      // ÿ50ms����
    if (cnt >= 0.5f) // 0.5s����û�������벶��
    {
        Remote_Flag = 0;      // ���ٶ�����
        cnt = 0; // ��������
    }
}
void Remote_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM15)
	{
		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
		{
			if(IR_IN)			//capture��������
			{
				TIM_RESET_CAPTUREPOLARITY(&htim15, TIM_CHANNEL_1);   //�������������
				TIM_SET_CAPTUREPOLARITY(&htim15, TIM_CHANNEL_1, TIM_ICPOLARITY_FALLING); //��ʼ�����½���
				__HAL_TIM_SET_COUNTER(&htim15, 0);  //��ն�ʱ��ֵ
				IRSta |= 0x10;   //[4]��1������־�������Ѳ���
			}
			else  //�����½���
			{
				Dval = HAL_TIM_ReadCapturedValue(&htim15, TIM_CHANNEL_1);   //�½��ؼ���
				TIM_RESET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_1);   //��������½���
				TIM_SET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);  //��ʼ����������
				if(IRSta & 0x10)  //��������һ�θߵ�ƽ���񣬽��������Ƿ���������
				{
					if(Dval>2100 && Dval<2600)  //4.5ms�ߵ�ƽ��������
					{
						Remote_Flag = 1;
						cnt = 0;
							IRSta &= 0xF0;  
					}
				}	
			IRSta &=~(1<<4); //���[4]�����ߵ�ƽ��������
			}
		}
	}
}

void Drv_Remote_Init(void)
{
	HAL_TIM_IC_Start_IT(&htim15, TIM_CHANNEL_1);   //����ͨ��4�Ĳ����жϷ�ʽ��
  __HAL_TIM_ENABLE_IT(&htim15, TIM_IT_UPDATE);   //����ʹ���ж�
}
