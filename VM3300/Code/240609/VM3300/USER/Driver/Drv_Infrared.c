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
//        if(Infrared[0].IRSta&0x80)//�ϴ������ݱ����յ���
//        {	
//            Infrared[0].IRSta&=~0X10;//ȡ���������Ѿ���������
//            if((Infrared[0].IRSta&0X0F)==0X00)
//            {
//                Infrared[0].IRSta|=1<<6;//����Ѿ����һ�ΰ����ļ�ֵ��Ϣ�ɼ�
//            }
//            if((Infrared[0].IRSta&0X0F)<14)
//            {
//                Infrared[0].IRSta++;
//            }
//			else
//			{
//				Infrared[0].IRSta &= ~(1<<7);//���������ʶ
//				Infrared[0].IRSta &= 0XF0;	//��ռ�����	
//			}						 	   	
//		}	
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
uint8_t cntt;
uint16_t data1[100];
void Infrared_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM15)
	{
//		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
//		{
//			if(IR2_IN)//�����ز���
//            {
//                TIM_RESET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_1);//һ��Ҫ�����ԭ�������ã���
//                TIM_SET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);//CC1P=1 ����Ϊ�½��ز���
//                __HAL_TIM_SET_COUNTER(&htim15,0);//��ն�ʱ��ֵ   	  
//                Infrared[0].IRSta|=0X10;//����������Ѿ�������
//            }
//            else//�½��ز���
//            {
//                Infrared[0].Dval=HAL_TIM_ReadCapturedValue(&htim15,TIM_CHANNEL_1);//��ȡCCR1Ҳ������CC1IF��־λ
//                TIM_RESET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_1);//һ��Ҫ�����ԭ�������ã���
//                TIM_SET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);//����TIM5ͨ��1�����ز���
//                if(Infrared[0].IRSta&0X10)//���һ�θߵ�ƽ���� 
//                {
//                    if(Infrared[0].IRSta&0X80)//���յ���������
//                    {
//                        if(Infrared[0].Dval > NEC_ZERO_MIN && Infrared[0].Dval < NEC_ZERO_MAX)//560Ϊ��׼ֵ,560us
//                        {
//                            Infrared[0].IRRec >>= 1;/* ����һλ. */
//                            Infrared[0].IRRec &= ~0x80000000;/* ���յ�0 */                                
//                        }
//                        else if(Infrared[0].Dval > NEC_ONE_MIN && Infrared[0].Dval < NEC_ONE_MAX)	//1680Ϊ��׼ֵ,1680us
//                        {
//                            Infrared[0].IRRec >>= 1;/* ����һλ */
//                            Infrared[0].IRRec |= 0x80000000;/* ���յ�1 */  
//                        }
//                        else if(Infrared[0].Dval > NEC_CONTINUE_MIN && Infrared[0].Dval < NEC_CONTINUE_MAX )	//�õ�������ֵ���ӵ���Ϣ 2500Ϊ��׼ֵ2.5ms
//                        {
//                            Infrared[0].IRCnt++;//������������1��
//                            Infrared[0].IRSta&=0XF0;//��ռ�ʱ��                                 
//                        }
//                    }
//                    else if(Infrared[0].Dval > NEC_HEAD_MIN && Infrared[0].Dval < NEC_HEAD_MAX)//4500Ϊ��׼ֵ4.5ms
//                    {
//                        Infrared[0].IRSta|=1<<7;//��ǳɹ����յ���������
//                        Infrared[0].IRCnt=0;//�����������������  
//                    }						 
//                }
//                Infrared[0].IRSta&=~(1<<4);
//            }				 		     	    
//		}
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
                            data1[cntt] = Infrared[1].Dval;
                            cntt++;                               
                        }
                        else if(Infrared[1].Dval > NEC_ONE_MIN && Infrared[1].Dval < NEC_ONE_MAX)	//1680Ϊ��׼ֵ,1680us
                        {
                            Infrared[1].IRRec >>= 1;/* ����һλ */
                            Infrared[1].IRRec |= 0x80000000;/* ���յ�1 */
                            data1[cntt] = Infrared[1].Dval;
                            cntt++;   
                        }
                        else if(Infrared[1].Dval > NEC_CONTINUE_MIN && Infrared[1].Dval < NEC_CONTINUE_MAX )	//�õ�������ֵ���ӵ���Ϣ 2500Ϊ��׼ֵ2.5ms
                        {
                            Infrared[1].IRCnt++;//������������1��
                            Infrared[1].IRSta&=0XF0;//��ռ�ʱ��    
                            data1[cntt] = Infrared[1].Dval;
                            cntt++;                               
                        }
                    }
                    else if(Infrared[1].Dval > NEC_HEAD_MIN && Infrared[1].Dval < NEC_HEAD_MAX)//4500Ϊ��׼ֵ4.5ms
                    {
                        Infrared[1].IRSta|=1<<7;//��ǳɹ����յ���������
                        Infrared[1].IRCnt=0;//�����������������
                         cntt = 0;
                        data1[cntt] = Infrared[1].Dval;
                            cntt++;   
                    }						 
                }
                Infrared[1].IRSta&=~(1<<4);
            }				 		     	    
		}
	}
}

//����������
//����ֵ:
//	 0,û���κΰ�������
//����,���µİ�����ֵ.
uint8_t Remote_Scan(void)
{        
	uint8_t sta=0;       
    uint8_t t1,t2;
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
    return sta;
}
uint8_t  key;
uint8_t calaa;
uint8_t falg_ren;
void NEC_GetValue(float dT,uint8_t *addr, uint16_t *value)
{
    static float T;
    key=Remote_Scan();	
    if(key)
    {
        if(key == 0x98)
        {
            falg_ren = 1;
        }
    }
    
    
    if(falg_ren  == 1)
    {
        T += dT;
        if(key == 0x98)
        {
            calaa = 100;
            T = 0;
        }
        if(T >= 3.0f)
        { 
            calaa = 0;
            falg_ren = 0;
            T = 0;
        }
    }
//	uint8_t t1, t2;
//	*addr = 0;
//	*value = 0;
//	if (Infrared[0].RecFlag == 0x01)    //���յ�һ������
//	{
//		Infrared[0].RecFlag = 0x00;
//		t1 = Infrared[0].RmtRec >> 24;             //�õ���ַ��
//		t2 = (Infrared[0].RmtRec >> 16) & 0xff;    //�õ���ַ����
//		if (t1 == (uint8_t)~t2)             //����ң��ʶ����(ID)����ַ
//		{
//			*addr = t1;
//			t1 = 0;
//			t2 = 0;
//		}
//		else
//		{*addr = 0; }
//		t1 = (Infrared[0].RmtRec >> 8) & 0xff;  //�õ�����
//		t2 = Infrared[0].RmtRec & 0xff;         //�õ����ݷ���
//		if (t1 == (uint8_t)~t2)           //���������뼰���ݷ���
//		{*value = t1;}
//		else
//		{*value = 0; }
//		Infrared[0].RmtRec = 0;
//	}
}

//һ���߼�0�Ĵ�����Ҫ 1.125ms��560us�ز�+560us���У���
static void NEC_Send_0(void)
{
	Infrared_Send1 = 52;
//    Infrared_Send2 = 52;
	Delay_us(560);
	Infrared_Send1 = 0;
//    Infrared_Send2 = 0;
	Delay_us(560);
}
//һ���߼�1������Ҫ2.25ms��560us�ز�+1680us���У�
static void NEC_Send_1(void)
{
	Infrared_Send1 = 52;
    Infrared_Send2 = 52;
	Delay_us(560);
	Infrared_Send1 = 0;
    Infrared_Send2 = 0;
	Delay_us(1680);
 
}
//NECЭ���ʽ��//�����룺����һ��9ms�ز��������룬֮����4.5ms�Ŀ��У�
static void NEC_Send_Head(void)
{
    Infrared_Send1 = 52;
//    Infrared_Send2 = 52;
	Delay_us(9000);        //  ʵ��10.56ms    10usʵ��13us
	Infrared_Send1 = 0;
//    Infrared_Send2 = 0;
	Delay_us(4500);          // ʵ�ʽ���ʱ����5.24ms
 
}
//������(�Լ��ӵ�)
static void NEC_Send_Tail(void)
{
 
	Infrared_Send1 = 52;
//    Infrared_Send2 = 52;
	Delay_us(200);
	Infrared_Send1 = 0;
//    Infrared_Send2 = 0;
	Delay_us(3000);    //   2.5<3ms<3.3ms
 
}

//����һ�ֽ�����
static void NEC_Send_BYTE(uint8_t value)
{
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		if (value & 0x80)
		{
			NEC_Send_1();
		}
		else
		{
			NEC_Send_0();
		}
		value <<= 1;
	}
}


static void NEC_Send_Repeat(uint8_t count)
{
	uint8_t i = 0;
 
	if (count == 0)          //���û���ظ����ֱ���������ز�������ܽ��п���״̬
	{
		NEC_Send_Tail();
	}
	else
	{
		for (i = 0; i < count; i++)
		{
			CARRIER_38KHz();
			Delay_us(9000);
			NO_CARRIER();
			Delay_us(2250);
		}
 
	}
}


//����16λ��ַ�루18ms36ms����8λ�����루9ms18ms���Լ�8Ϊ���ݷ��롣
//���ڶ���108ms����������������ظ������ݣ������ȷ���9ms�ز�������2.5ms,
//�ٷ���0.56ms�ز����ɣ�ע��ÿ�η���ļ��ʱ�䡣
void NEC_Send(uint8_t addr, uint8_t value, uint8_t cnt)
{
	NEC_Send_Head();                //������ʼ��
	NEC_Send_BYTE(addr);            //���͵�ַ��H
	NEC_Send_BYTE(~addr);           //���͵�ַ��L
	NEC_Send_BYTE(value);           //����������H
	NEC_Send_BYTE(~value);          //����������L
	NEC_Send_Repeat(cnt);           //�����ظ���
    Delay_us(3000);
//    Infrared_Send1 = 52;
//     Infrared_Send2 = 52;
//    Delay_us(9000);
//    Infrared_Send1 = 0;
//    Delay_us(2250);
//    Infrared_Send1 = 52;
//    Delay_us(100);
//    Infrared_Send1 = 0;
//    Delay_us(90000);
    
}

void Check_Infrared(float dT)
{
    uint16_t data[1];
    uint8_t addr[1];
    NEC_GetValue(dT,addr, data);
}
