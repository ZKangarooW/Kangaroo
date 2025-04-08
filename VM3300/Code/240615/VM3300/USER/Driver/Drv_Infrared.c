#include "Drv_Infrared.h"

/**********�ṹ��************/
_Infrared_ Infrared[2];

/**
 * @brief ����������ʼ��
 *
 */
void Drv_Infrared_Init(void)
{
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);//����tim3ͨ��һ PA6���ֱ�
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);//����tim3ͨ���� PA7���ֱ�
	
    
    HAL_TIM_Base_Start_IT(&htim15);
	HAL_TIM_IC_Start_IT(&htim15, TIM_CHANNEL_1);//����tim15ͨ��1�Ĳ����жϷ�ʽ��PA2���ֱ�
	HAL_TIM_IC_Start_IT(&htim15, TIM_CHANNEL_2);//����tim15ͨ��2�Ĳ����жϷ�ʽ��PA3���ֱ�
    HAL_TIM_Base_Start_IT(&htim1);//��������ж�
    Infrared[0].Distance = 10000;// ��������Ϊ10000
    Infrared[1].Distance = 10000;// ��������Ϊ10000
}

/**
 * @brief ��ʱ�����£�������жϻص�����
 *
 */
void Infrared_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM15)
    {
        Infrared[0].Cnt++;
        Infrared[1].Cnt++;
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
		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
		{
            if(Infrared[0].Edge == 0)//�������������
            {
                Infrared[0].t1 = HAL_TIM_ReadCapturedValue(&htim15,TIM_CHANNEL_1);
                
                //����Ϊ�½��ز���
                __HAL_TIM_SET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_1,TIM_INPUTCHANNELPOLARITY_FALLING);
                
                Infrared[0].Cnt = 0;//����������
                
                Infrared[0].Edge = 1;//�ɼ��½���
            }
            else if(Infrared[0].Edge == 1)
            {
                Infrared[0].t2 = HAL_TIM_ReadCapturedValue(&htim15,TIM_CHANNEL_1);
                
                Infrared[0].t2 += Infrared[0].Cnt * 65535;
                
                Infrared[0].T = Infrared[0].t2 - Infrared[0].t1;
                
                //����Ϊ�������ز���
                __HAL_TIM_SET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_1,TIM_INPUTCHANNELPOLARITY_RISING);
                
                Infrared[0].Distance = Infrared[0].T * 0.000001 * 300000; 
                if(Infrared[0].Distance>10000)
                {
                    Infrared[0].Distance = 10000;
                }
                Infrared[0].SSI_CNT = 0; // ��������
                
                Infrared[0].Edge = 0;//�ɼ�������
            }	 		     	    
		}
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
		{
            if(Infrared[1].Edge == 0)//�������������
            {
                Infrared[1].t1 = HAL_TIM_ReadCapturedValue(&htim15,TIM_CHANNEL_2);
                
                //����Ϊ�½��ز���
                __HAL_TIM_SET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_2,TIM_INPUTCHANNELPOLARITY_FALLING);
                
                Infrared[1].Cnt = 0;//����������
                
                Infrared[1].Edge = 1;//�ɼ��½���
            }
            else if(Infrared[1].Edge == 1)
            {
                Infrared[1].t2 = HAL_TIM_ReadCapturedValue(&htim15,TIM_CHANNEL_2);
                
                Infrared[1].t2 += Infrared[1].Cnt * 65535;
                
                Infrared[1].T = Infrared[1].t2 - Infrared[1].t1;
                
                //����Ϊ�������ز���
                __HAL_TIM_SET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_2,TIM_INPUTCHANNELPOLARITY_RISING);
                
                Infrared[1].Distance = Infrared[1].T * 0.000001 * 300000; 
                if(Infrared[1].Distance>10000)
                {
                    Infrared[1].Distance = 10000;
                }
                Infrared[1].SSI_CNT = 0; // ��������
                Infrared[1].Edge = 0;//�ɼ�������
            }  	    
		}
	}
}

/**
 * @brief ������(�Լ��ӵ�)
 * 
 * @param val 0��ͨ���� 1:ͨ��һ
 */
static void NEC_Send_Tail(uint8_t val)
{
	CARRIER_38KHz(val);
	Delay_us(200);
	NO_CARRIER(val);
	Delay_us(3000);//2.5<3ms<3.3ms
 
}

/**
 * @brief ����16λ��ַ�루18ms36ms����8λ�����루9ms18ms���Լ�8Ϊ���ݷ���
 * 
 * @param val 0��ͨ���� 1:ͨ��һ
 * @param addr ���͵ĵ�ַ
 * @param value ����
 * @param cnt ���� 
 */
void NEC_Send(uint8_t val)
{
	NEC_Send_Tail(val);//�����ظ��� 
}

/**
 * @brief ������
 * 
 * @param dT ��������
 */
void Check_Infrared(float dT)
{
    static float T;
    static float T1;
    
    if(Infrared[0].Distance > 1500&&Infrared[0].Distance<3000)
    {
        Infrared[0].Someone = 1;
    }
    
    if(Infrared[0].Someone == 1)
    {
        T += dT;
        if(Infrared[0].Distance > 1500&&Infrared[0].Distance<3000)
        {
            T = 0;
        }
        if(T >= 3.0f)
        { 
            Infrared[0].Someone = 0;
            T = 0;
        }
    }
 
    if(Infrared[1].Distance > 1500&&Infrared[1].Distance<3000)
    {
        Infrared[1].Someone = 1;
    }
    
    if(Infrared[1].Someone == 1)
    {
        T1 += dT;
        if(Infrared[1].Distance > 1500&&Infrared[1].Distance<3000)
        {
            T1 = 0;
        }
        if(T1 >= 3.0f)
        { 
            Infrared[1].Someone = 0;
            T1 = 0;
        }
    }
//    if(Infrared[0].Someone==0 && Infrared[1].Someone==0)
//    {
//        Speed.ADDMode = 2;
//    }
}

/**
 * @brief �������Ƿ��н���
 *
 * @param dT ��������
 */
void Check_Infrared_Rec(float dT)
{
    Infrared[0].SSI_CNT += dT;// ÿ50ms����
    Infrared[1].SSI_CNT += dT;// ÿ50ms����
    if (Infrared[0].SSI_CNT >= 1.0) // 0.5s����û�������벶��
    {
        Infrared[0].Distance = 10000;// ��������Ϊ10000
        Infrared[0].SSI_CNT = 0; // ��������
    }
    if (Infrared[1].SSI_CNT >= 1.0) // 0.5s����û�������벶��
    {
        Infrared[1].Distance = 10000;// ��������Ϊ10000
        Infrared[1].SSI_CNT = 0; // ��������
    }
}
