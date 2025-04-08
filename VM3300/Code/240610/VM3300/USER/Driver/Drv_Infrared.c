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
}

/**
 * @brief ��ʱ�����£�������жϻص�����
 *
 */
void Infrared_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM15)
    {
        if(Infrared[0].IRSta&0x80)//�ϴ������ݱ����յ���
        {	
            Infrared[0].IRSta&=~0X10;//ȡ���������Ѿ���������
            if((Infrared[0].IRSta&0X0F)==0X00)
            {
                Infrared[0].IRSta|=1<<6;//����Ѿ����һ�ΰ����ļ�ֵ��Ϣ�ɼ�
            }
            if((Infrared[0].IRSta&0X0F)<14)
            {
                Infrared[0].IRSta++;
            }
            else
            {
                Infrared[0].IRSta &= ~(1<<7);//���������ʶ
                Infrared[0].IRSta &= 0XF0;	//��ռ�����	
            }						 	   	
        }	
        if(Infrared[1].IRSta&0x80)//�ϴ������ݱ����յ���
        {	
            Infrared[1].IRSta&=~0X10;//ȡ���������Ѿ���������
            if((Infrared[1].IRSta&0X0F)==0X00)
            {
                Infrared[1].IRSta|=1<<6;//����Ѿ����һ�ΰ����ļ�ֵ��Ϣ�ɼ�
            }
            if((Infrared[1].IRSta&0X0F)<14)
            {
                Infrared[1].IRSta++;
            }
            else
            {
                Infrared[1].IRSta &= ~(1<<7);//���������ʶ
                Infrared[1].IRSta &= 0XF0;	//��ռ�����	
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
		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
		{
			if(IR2_IN)//�����ز���
            {
                TIM_RESET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_1);//һ��Ҫ�����ԭ�������ã���
                TIM_SET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);//CC1P=1 ����Ϊ�½��ز���
                __HAL_TIM_SET_COUNTER(&htim15,0);//��ն�ʱ��ֵ   	  
                Infrared[0].IRSta|=0X10;//����������Ѿ�������
            }
            else//�½��ز���
            {
                Infrared[0].Dval=HAL_TIM_ReadCapturedValue(&htim15,TIM_CHANNEL_1);//��ȡCCR1Ҳ������CC1IF��־λ
                TIM_RESET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_1);//һ��Ҫ�����ԭ�������ã���
                TIM_SET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);//����TIM5ͨ��1�����ز���
                if(Infrared[0].IRSta&0X10)//���һ�θߵ�ƽ���� 
                {
                    if(Infrared[0].IRSta&0X80)//���յ���������
                    {
                        if(Infrared[0].Dval > NEC_ZERO_MIN && Infrared[0].Dval < NEC_ZERO_MAX)//560Ϊ��׼ֵ,560us
                        {
                            Infrared[0].IRRec >>= 1;/* ����һλ. */
                            Infrared[0].IRRec &= ~0x80000000;/* ���յ�0 */                                
                        }
                        else if(Infrared[0].Dval > NEC_ONE_MIN && Infrared[0].Dval < NEC_ONE_MAX)	//1680Ϊ��׼ֵ,1680us
                        {
                            Infrared[0].IRRec >>= 1;/* ����һλ */
                            Infrared[0].IRRec |= 0x80000000;/* ���յ�1 */  
                        }
                        else if(Infrared[0].Dval > NEC_CONTINUE_MIN && Infrared[0].Dval < NEC_CONTINUE_MAX )	//�õ�������ֵ���ӵ���Ϣ 2500Ϊ��׼ֵ2.5ms
                        {
                            Infrared[0].IRCnt++;//������������1��
                            Infrared[0].IRSta&=0XF0;//��ռ�ʱ��                                 
                        }
                    }
                    else if(Infrared[0].Dval > NEC_HEAD_MIN && Infrared[0].Dval < NEC_HEAD_MAX)//4500Ϊ��׼ֵ4.5ms
                    {
                        Infrared[0].IRSta|=1<<7;//��ǳɹ����յ���������
                        Infrared[0].IRCnt=0;//�����������������  
                    }						 
                }
                Infrared[0].IRSta&=~(1<<4);
            }				 		     	    
		}
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
		{
			if(IR1_IN)//�����ز���
            {
                TIM_RESET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_2);//һ��Ҫ�����ԭ�������ã���
                TIM_SET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_2,TIM_ICPOLARITY_FALLING);//CC1P=1 ����Ϊ�½��ز���
                __HAL_TIM_SET_COUNTER(&htim15,0);//��ն�ʱ��ֵ   	  
                Infrared[1].IRSta|=0X10;//����������Ѿ�������
            }
            else//�½��ز���
            {
                Infrared[1].Dval=HAL_TIM_ReadCapturedValue(&htim15,TIM_CHANNEL_2);//��ȡCCR1Ҳ������CC1IF��־λ
                TIM_RESET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_2);//һ��Ҫ�����ԭ�������ã���
                TIM_SET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_2,TIM_ICPOLARITY_RISING);//����TIM5ͨ��1�����ز���
                if(Infrared[1].IRSta&0X10)//���һ�θߵ�ƽ���� 
                {
                    if(Infrared[1].IRSta&0X80)//���յ���������
                    {
                        if(Infrared[1].Dval > NEC_ZERO_MIN && Infrared[1].Dval < NEC_ZERO_MAX)//560Ϊ��׼ֵ,560us
                        {
                            Infrared[1].IRRec >>= 1;/* ����һλ. */
                            Infrared[1].IRRec &= ~0x80000000;/* ���յ�0 */                            
                        }
                        else if(Infrared[1].Dval > NEC_ONE_MIN && Infrared[1].Dval < NEC_ONE_MAX)//1680Ϊ��׼ֵ,1680us
                        {
                            Infrared[1].IRRec >>= 1;/* ����һλ */
                            Infrared[1].IRRec |= 0x80000000;/* ���յ�1 */ 
                        }
                        else if(Infrared[1].Dval > NEC_CONTINUE_MIN && Infrared[1].Dval < NEC_CONTINUE_MAX )//�õ�������ֵ���ӵ���Ϣ 2500Ϊ��׼ֵ2.5ms
                        {
                            Infrared[1].IRCnt++;//������������1��
                            Infrared[1].IRSta&=0XF0;//��ռ�ʱ��
                        }
                    }
                    else if(Infrared[1].Dval > NEC_HEAD_MIN && Infrared[1].Dval < NEC_HEAD_MAX)//4500Ϊ��׼ֵ4.5ms
                    {
                        Infrared[1].IRSta|=1<<7;//��ǳɹ����յ���������
                        Infrared[1].IRCnt=0;//�����������������  
                    }						 
                }
                Infrared[1].IRSta&=~(1<<4);
            }				 		     	    
		}
	}
}

/**
 * @brief һ���߼�0�Ĵ�����Ҫ 1.125ms��560us�ز�+560us���У���
 * 
 * @param val 0��ͨ���� 1:ͨ��һ
 */
static void NEC_Send_0(uint8_t val)
{
	CARRIER_38KHz(val);
	Delay_us(560);
	NO_CARRIER(val);
	Delay_us(560);
}

/**
 * @brief һ���߼�1������Ҫ2.25ms��560us�ز�+1680us���У�
 * 
 * @param val 0��ͨ���� 1:ͨ��һ
 */
static void NEC_Send_1(uint8_t val)
{
	CARRIER_38KHz(val);
	Delay_us(560);
	NO_CARRIER(val);
	Delay_us(1680);
 
}

/**
 * @brief NECЭ���ʽ�������룺����һ��9ms�ز��������룬֮����4.5ms�Ŀ���
 * 
 * @param val 0��ͨ���� 1:ͨ��һ
 */
static void NEC_Send_Head(uint8_t val)
{
    CARRIER_38KHz(val);
	Delay_us(9000);        //  ʵ��10.56ms    10usʵ��13us
	NO_CARRIER(val);
	Delay_us(4500);          // ʵ�ʽ���ʱ����5.24ms
 
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
 * @brief ����һ�ֽ�����
 * 
 * @param val 0��ͨ���� 1:ͨ��һ
 * @param value Ҫ���͵��ֽ�����
 */
static void NEC_Send_BYTE(uint8_t val,uint8_t value)
{
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		if (value & 0x01)
		{
			NEC_Send_1(val);
		}
		else
		{
			NEC_Send_0(val);
		}
		value>>= 1;
	}
}

/**
 * @brief ����������ظ���
 * 
 * @param val 0��ͨ���� 1:ͨ��һ
 * @param count �ظ��Ĵ�����0�ͱ�ʾ���ظ�
 */
static void NEC_Send_Repeat(uint8_t val, uint8_t count)
{
	uint8_t i = 0;
 
	if (count == 0)//���û���ظ����ֱ���������ز�������ܽ��п���״̬
	{
		NEC_Send_Tail(val);
	}
	else
	{
		for (i = 0; i < count; i++)
		{
			CARRIER_38KHz(val);
			Delay_us(9000);
			NO_CARRIER(val);
			Delay_us(2250);
		}
 
	}
}

/**
 * @brief ����16λ��ַ�루18ms36ms����8λ�����루9ms18ms���Լ�8Ϊ���ݷ���
 * 
 * @param val 0��ͨ���� 1:ͨ��һ
 * @param addr ���͵ĵ�ַ
 * @param value ����
 * @param cnt ���� 
 */
void NEC_Send(uint8_t val, uint8_t addr, uint8_t value, uint8_t cnt)
{
	NEC_Send_Head(val);                //������ʼ��
	NEC_Send_BYTE(val, addr);            //���͵�ַ��H
	NEC_Send_BYTE(val, ~addr);           //���͵�ַ��L
	NEC_Send_BYTE(val, value);           //����������H
	NEC_Send_BYTE(val, ~value);          //����������L
	NEC_Send_Repeat(val, cnt);           //�����ظ��� 
}

/**
 * @brief ����������
 * 
 * @param val 0��ͨ���� 1:ͨ��һ
 * @return uint8_t 0,û���κΰ������£�����,���µİ�����ֵ.
 */
uint8_t Remote_Scan(uint8_t val)
{        
	uint8_t sta=0;
    uint8_t t1,t2;    
    if(val)
    {
        if(Infrared[1].IRSta&(1 << 6))//�õ�һ��������������Ϣ��
        { 
            t1 = Infrared[1].IRRec;/* �õ���ַ�� */
            t2 = (Infrared[1].IRRec >> 8) & 0xff;/* �õ���ַ���� */
            if ((t1 == (uint8_t)~t2) && t1 == REMOTE_ID)   
            {   
                /* ����ң��ʶ����(ID)����ַ */
                t1 = (Infrared[1].IRRec >> 16) & 0xff;
                t2 = (Infrared[1].IRRec >> 24) & 0xff;
                if (t1 == (uint8_t)~t2)
                {
                    sta = t1;/* ��ֵ��ȷ */
                }
            }

            if ((sta == 0) || ((Infrared[1].IRSta & 0X80) == 0)) 
            {   /* �������ݴ���/ң���Ѿ�û�а����� */
                Infrared[1].IRSta &= ~(1 << 6);/* ������յ���Ч������ʶ */
                Infrared[1].IRCnt = 0;/* ����������������� */
            }
        }
    }
    else
    {
        if(Infrared[0].IRSta&(1 << 6))//�õ�һ��������������Ϣ��
        { 
            t1 = Infrared[0].IRRec;/* �õ���ַ�� */
            t2 = (Infrared[0].IRRec >> 8) & 0xff;/* �õ���ַ���� */
            if ((t1 == (uint8_t)~t2) && t1 == REMOTE_ID)   
            {   
                /* ����ң��ʶ����(ID)����ַ */
                t1 = (Infrared[0].IRRec >> 16) & 0xff;
                t2 = (Infrared[0].IRRec >> 24) & 0xff;
                if (t1 == (uint8_t)~t2)
                {
                    sta = t1;/* ��ֵ��ȷ */
                }
            }

            if ((sta == 0) || ((Infrared[0].IRSta & 0X80) == 0)) 
            {   /* �������ݴ���/ң���Ѿ�û�а����� */
                Infrared[0].IRSta &= ~(1 << 6);/* ������յ���Ч������ʶ */
                Infrared[0].IRCnt = 0;/* ����������������� */
            }
        }
    }
    return sta;
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
    uint8_t key,key1;

    key = Remote_Scan(1);
    key1 = Remote_Scan(0);	

    if(key)
    {
        if(key == 0x19)
        {
           Infrared[1].Someone = 1;
        }
    }
    
    if(Infrared[1].Someone  == 1)
    {
        T += dT;
        if(key == 0x19)
        {
            T = 0;
        }
        if(T >= 3.0f)
        { 
            Infrared[1].Someone = 0;
            T = 0;
        }
    }
    
    if(key1)
    {
        if(key1 == 0x19)
        {
           Infrared[0].Someone = 1;
        }
    }
    
    if(Infrared[0].Someone  == 1)
    {
        T1 += dT;
        if(key1 == 0x19)
        {
            T1 = 0;
        }
        if(T1 >= 3.0f)
        { 
            Infrared[0].Someone = 0;
            T1 = 0;
        }
    }
    
}
