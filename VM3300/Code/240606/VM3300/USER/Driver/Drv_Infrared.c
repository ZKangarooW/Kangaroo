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

///**
// * @brief �Ƿ�����
// *
// * @param dT ��������
// */
//void Check_Infrared(float dT)
//{
//    Infrared[0].Someone_Time += dT;//ÿ100ms����
//	Infrared[1].Someone_Time += dT;//ÿ100ms����
//    if (Infrared[0].Someone_Time >= 0.5f)// 0.5s����û�������벶��
//    {
//        Infrared[0].Someone = 0;// ����������
//        Infrared[0].Someone_Time = 0;//��������
//    }
//	if (Infrared[1].Someone_Time >= 0.5f)// 0.5s����û�������벶��
//    {
//        Infrared[1].Someone = 0;// ����������
//        Infrared[1].Someone_Time = 0;//��������
//    }
//}

//void Delay_us(uint32_t us_cnt)
//{
//	TIM6->CNT = us_cnt - 1;
//	TIM6->CR1 |= TIM_CR1_CEN;
//	while ((TIM6->SR & TIM_FLAG_UPDATE) != SET);
//	TIM6->SR = (uint16_t)~TIM_FLAG_UPDATE;
//	TIM6->CR1 &= ~TIM_CR1_CEN;
//}

///**
// * @brief ��ʱ�������ж�
// *
// */
//void Infrared_TIM_Interrupt(TIM_HandleTypeDef *htim)
//{
//	if(htim->Instance == htim6.Instance) 
//	{
//        
//	}
//}





/**
 * @brief �������źű仯��ʱ������
 *
 */
uint16_t val1;
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
                    if (Infrared[0].STA_Head == 0x01) //ֻ�н��յ���������֮��õ��Ĳ�������
                    {
                        if (Infrared[0].Dval > NEC_ZERO_MIN && Infrared[0].Dval < NEC_ZERO_MAX)  //560Ϊ��׼ֵ,560us min=392 max=728               ʵ��ֵΪ0.68ms
                        {
                            //������յ������ݣ�0
                            Infrared[0].RmtRec <<= 1;                 //����һλ.
                            Infrared[0].RmtRec |= 0;                  //���յ�0
                        }
                        else if (Infrared[0].Dval > NEC_ONE_MIN && Infrared[0].Dval < NEC_ONE_MAX)  //1680Ϊ��׼ֵ,1680us min=1.176ms max=2.148ms    ʵ��ֵΪ1.96ms
                        {
                            //������յ������ݣ�1
                            Infrared[0].RmtRec <<= 1;                 //����һλ.
                            Infrared[0].RmtRec |= 1;                  //���յ�1
             
                        }
                        else if (300 < Infrared[0].Dval && Infrared[0].Dval < 8800)//�õ�������ֵ���ӵ���Ϣ 2500Ϊ��׼ֵ2.5ms
                        {
                            Infrared[0].RecFlag = 0x01;
                            Infrared[0].STA_Head = 0x00; //׼��������һ֡����
                        }
                    }
                    else if (Infrared[0].Dval > NEC_HEAD_MIN && Infrared[0].Dval < NEC_HEAD_MAX)       //4500Ϊ��׼ֵ4.5ms  ʵ��5773 //4500 -6300
                    {
                        Infrared[0].STA_Head = 0x01;  //��ǳɹ����յ���������
											  //����ȥ���ȴ���һ���ߵ�ƽ
                    }
				}	
				Infrared[0].IRSta &=~(1<<4);//���[4]�����ߵ�ƽ��������
			}
            
            
		}
	}
}

void NEC_GetValue(uint8_t *addr, uint16_t *value)
{
	uint8_t t1, t2;
	*addr = 0;
	*value = 0;
	if (Infrared[0].RecFlag == 0x01)    //���յ�һ������
	{
		Infrared[0].RecFlag = 0x00;
		t1 = Infrared[0].RmtRec >> 24;             //�õ���ַ��
		t2 = (Infrared[0].RmtRec >> 16) & 0xff;    //�õ���ַ����
		if (t1 == (uint8_t)~t2)             //����ң��ʶ����(ID)����ַ
		{
			*addr = t1;
			t1 = 0;
			t2 = 0;
		}
		else
		{*addr = 0; }
		t1 = (Infrared[0].RmtRec >> 8) & 0xff;  //�õ�����
		t2 = Infrared[0].RmtRec & 0xff;         //�õ����ݷ���
		if (t1 == (uint8_t)~t2)           //���������뼰���ݷ���
		{*value = t1;}
		else
		{*value = 0; }
		Infrared[0].RmtRec = 0;
	}
}

