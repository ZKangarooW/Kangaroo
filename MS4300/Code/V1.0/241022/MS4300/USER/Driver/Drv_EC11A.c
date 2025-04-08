#include "Drv_EC11A.h"

/**********�ṹ��************/
_EC11A_ EC11A[2];//��ť����

/**
 * @brief EC11A��ʼ����ʱ��
 * 
 */
void EC11A_Init(void)
{
	/**********EC11A_1**********/
	EC11A[0].EXTI_Pin = EC1A_Pin;//EC11A��ť�ж�����
	EC11A[0].EC11A_Pin = EC1B_Pin;//EC11A��ť��������
	EC11A[0].EC11A_GPIO = EC1B_GPIO_Port;//EC11A��ť����GPIO�˿�
	
	EC11A[0].Key_Pin = KEY1_Pin;//EC11A������������
	EC11A[0].Key_GPIO = KEY1_GPIO_Port;//EC11A��������GPIO�˿�
	EC11A[0].EC11A_Fast = EC11A_FastSpeed;//�ж���ת�ٶ���ֵ
	/**********EC11A_2**********/
	EC11A[1].EXTI_Pin = EC2A_Pin;//EC11A��ť�ж�����
	EC11A[1].EC11A_Pin = EC2B_Pin;//EC11A��ť��������
	EC11A[1].EC11A_GPIO = EC2B_GPIO_Port;//EC11A��ť����GPIO�˿�
	
	EC11A[1].Key_Pin = KEY2_Pin;//EC11A������������
	EC11A[1].Key_GPIO = KEY2_GPIO_Port;//EC11A��������GPIO�˿�
    EC11A[1].EC11A_Fast = EC11A_FastSpeed;//�ж���ת�ٶ���ֵ
}

/**
 * @brief EC11A��ť�ٶȼ���
 * 
 * @param dT ��������
 */
void EC11A_Speed(float dT)
{
	static float T;
	T+=dT;
	if(T>= 1.0f)
	{
		/**********EC11A_1**********/
		EC11A[0].EC11A_Speed = EC11A[0].EC11A_Cnt;//һ����һ�Ρ�תһȦ20��������һ���ӵ��ٶ�
		EC11A[0].EC11A_Cnt = 0;//����⵽�ļ�������
	
		/**********EC11A_2**********/
		EC11A[1].EC11A_Speed = EC11A[1].EC11A_Cnt;//һ����һ�Ρ�תһȦ20��������һ���ӵ��ٶ�
		EC11A[1].EC11A_Cnt = 0;//����⵽�ļ�������
        T = 0;
	}
}

/**
 * @brief ��ⰴ������״̬
 * 
 * @param dT ��������
 */
void Check_Press(float dT)
{
    if(EC11A[0].EC11A_Knob>0)//��ť0��ת
        EC11A[0].EC11A_Knob -= dT;//����ʱ
	
	if(EC11A[1].EC11A_Knob>0)//��ť1��ת
        EC11A[1].EC11A_Knob -= dT;//����ʱ
}

/**
 * @brief EC11A����ɨ��
 * 
 * @param dT ��������
 */
void EC11AKey_Scan(float dT)
{
	/**********EC11A_1**********/
	if(HAL_GPIO_ReadPin(EC11A[0].Key_GPIO,EC11A[0].Key_Pin) == KEY_DOWN)//���°���
	{
		if(EC11A[0].LongPress == 0)//û�г�����
		{
			EC11A[0].Key_Cnt += dT;//����ʱ��++
			EC11A[0].Key_Flag = 1;//�������±�־��һ
		}
	}
	if(EC11A[0].Key_Flag == 1)//����������
	{
		if(HAL_GPIO_ReadPin(EC11A[0].Key_GPIO,EC11A[0].Key_Pin) == KEY_UP)//̧�𰴼�
		{   
			if(EC11A[0].Key_Cnt > 0.1 && EC11A[0].Key_Cnt < 1.5)//С��1.5S�ǵ���
			{
                if(Lock_Switch)
                {
                    Beep_Flash = 2;//���εΡ�����������
                    sys.Lock_Alarm = 2;
                }
                else
                {
                    Beep_Time = 0.1f; // ��������0.1S
                }
                
			}
			EC11A[0].Key_Flag = 0;//�����¼��������ȴ���һ�ΰ���
			EC11A[0].LongPress = 0;//������־����
			EC11A[0].Key_Cnt = 0;//��ť��������
		}
		if(EC11A[0].Key_Cnt > 1.5 && EC11A[0].Key_Cnt < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(EC11A[0].LongPress == 0)//���û��һֱһֱ������
			{
                Beep_Flash = 2;//���εΡ�����������
                if(Lock_Switch)
                {
                    sys.Lock_Alarm = 2;
                }
				EC11A[0].LongPress = 1;//������־��һ
			}
		}
	}
	
	/**********EC11A_2**********/
	if(HAL_GPIO_ReadPin(EC11A[1].Key_GPIO,EC11A[1].Key_Pin) == KEY_DOWN)//���°���
	{
		if(EC11A[1].LongPress == 0)//û�г�����
		{
			EC11A[1].Key_Cnt += dT;//����ʱ��++
			EC11A[1].Key_Flag = 1;//�������±�־��һ
		}
	}
	if(EC11A[1].Key_Flag == 1)//����������
	{
		if(HAL_GPIO_ReadPin(EC11A[1].Key_GPIO,EC11A[1].Key_Pin) == KEY_UP)//̧�𰴼�
		{   
			if(EC11A[1].Key_Cnt > 0.1 && EC11A[1].Key_Cnt < 1.5)//С��1.5S�ǵ���
			{
                
                if(Lock_Switch)
                {
                    Beep_Flash = 2;//���εΡ�����������
                    sys.Lock_Alarm = 2;
                }
                else
                {
                    Beep_Time = 0.1f; // ��������0.1S
                }
                 
			}
			EC11A[1].Key_Flag = 0;//�����¼��������ȴ���һ�ΰ���
			EC11A[1].LongPress = 0;//������־����
			EC11A[1].Key_Cnt = 0;//��ť��������
		}
		if(EC11A[1].Key_Cnt > 1.5 && EC11A[1].Key_Cnt < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(EC11A[1].LongPress == 0)//���û��һֱһֱ������
			{
                Beep_Flash = 2;//���εΡ�����������
                if(Lock_Switch)
                {
                    sys.Lock_Alarm = 2;
                }
                EC11A[1].LongPress = 1;//������־��һ
            }
		}
	}
}

/**
 * @brief �ⲿ�ж�
 * 
 * @param GPIO_Pin ��������
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	UNUSED(GPIO_Pin);
	
	/**********EC11A_1**********/
    if(GPIO_Pin == EC11A[0].EXTI_Pin)//��2ms�ڣ���⵽��ƽ�仯
	{ 
		EC11A[0].EC11A_Cnt++;//��ť����
		EC11A[0].EC11A_Knob = 1.0f;//����ת��ťʱ
		if(HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO,EC11A[0].EC11A_Pin) == 0)//��
		{
            if (Pmode_Twinkle_Time) // ���������Pֵʱ
            {
                PMode.Option ++;
                if(PMode.Option > 9)
                    PMode.Option = 1;
                Param_Read(); // ��ȡ����
                Pmode_Twinkle_Time = 2.0f;
            }
            else
            {
                if(EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast)//���������ת
                    Time.Set += 60;//�趨ʱ���60S
                else
                    Time.Set += 600;//�趨ʱ���600S
                Time.Set = (Time.Set > Time_MAX) ? Time_MAX : Time.Set;//ʱ������趨24Сʱ
                Time_Twinkle_Time = 2.0f;//ʱ����˸2S
            }

		}
		else if(HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO,EC11A[0].EC11A_Pin) == 1)//��
		{
            if (Pmode_Twinkle_Time) // ���������Pֵʱ
            {
                PMode.Option --;
                if(PMode.Option < 1)
                    PMode.Option = 9;
                Param_Read(); // ��ȡ����
                Pmode_Twinkle_Time = 2.0f;
            }
            else
            {
                if(EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast)//���������ת
                    Time.Set -= 60;//�趨ʱ���60S
                else
                    Time.Set -= 600;//�趨ʱ���600S
                Time.Set = (Time.Set < Time_MIN) ? 0 : Time.Set;//ʱ��С��1���Ӳ��趨���趨ʱ��Ϊ0��������
                Time_Twinkle_Time = 2.0f;//ʱ����˸2S
            }

		}
	}
    
	/**********EC11A_2**********/
	if(GPIO_Pin == EC11A[1].EXTI_Pin)//��2ms�ڣ���⵽��ƽ�仯
	{
		EC11A[1].EC11A_Cnt++;//��ť����
		EC11A[1].EC11A_Knob = 1.0f;//����ת��ťʱ
		if(HAL_GPIO_ReadPin(EC11A[1].EC11A_GPIO,EC11A[1].EC11A_Pin) == 0)//��
		{
            if (Pmode_Twinkle_Time) // ���������Pֵʱ
            {
                PMode.Option ++;
                if(PMode.Option > 9)
                    PMode.Option = 1;
                Param_Read(); // ��ȡ����
                Pmode_Twinkle_Time = 2.0f;
            }
            else
            {
                if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//���������ת
                    Speed.Set += 5;//ת�ټ�5
                else
                    Speed.Set += 50;//ת�ټ�50
                Speed.Set = (Speed.Set > Speed_MAX) ? Speed_MAX : Speed.Set;//�ٶȲ��������ֵ
                Speed_Twinkle_Time = 2.0f;//�ٶ���˸2S
            }

		}
		else if(HAL_GPIO_ReadPin(EC11A[1].EC11A_GPIO,EC11A[1].EC11A_Pin) == 1)//��
		{
            if (Pmode_Twinkle_Time) // ���������Pֵʱ
            {
                PMode.Option --;
                if(PMode.Option < 1)
                    PMode.Option = 9;
                Param_Read(); // ��ȡ����
                Pmode_Twinkle_Time = 2.0f;
            }
            else
            {
                if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//���������ת
                    Speed.Set -= 5;//ת�ټ�5
                else
                    Speed.Set -= 50;//ת�ټ�50
                Speed.Set = (Speed.Set < Speed_MIN) ? Speed_MIN : Speed.Set;//�ٶȲ�С������ֵ
                Speed_Twinkle_Time = 2.0f;//�ٶ���˸2S
            }
		}
	}
}
