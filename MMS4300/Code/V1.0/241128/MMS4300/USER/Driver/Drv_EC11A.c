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
	
	/**********EC11A_2**********/
	EC11A[1].EXTI_Pin = EC2A_Pin;//EC11A��ť�ж�����
	EC11A[1].EC11A_Pin = EC2B_Pin;//EC11A��ť��������
	EC11A[1].EC11A_GPIO = EC2B_GPIO_Port;//EC11A��ť����GPIO�˿�
	
	EC11A[1].Key_Pin = KEY2_Pin;//EC11A������������
	EC11A[1].Key_GPIO = KEY2_GPIO_Port;//EC11A��������GPIO�˿�
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
                }
                else
                {
                    sys.New_Work++;
                    if(sys.New_Work > 3)
                        sys.New_Work = 0;
                    sys.SetMode_Option = 0;
                    Twinkle_Time = 0;
                    EC11A[0].EC11A_Knob = 2.0f;//���л�ʱ�����������������Ŀǰ��ʲô��λ
                    Beep_Time = 0.1f;
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
                }
                else
                {
                    sys.SetMode_Option ++;
                    if(sys.SetMode_Option == 1 && Twinkle_Time > 0)//�������ת����ť�����º�ֱ�������ٶ�����
                        sys.SetMode_Option = 2;
                    if(sys.SetMode_Option > 2)
                        sys.SetMode_Option  = 1;
                    Beep_Time = 0.1f;
                    Twinkle_Time = 2.0f;
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
                EC11A[1].LongPress = 1;//������־��һ
            }
		}
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Set_Val(uint8_t flag,uint8_t Work_Option,uint8_t SetMode_Option,uint8_t EC11A_Fast)
 * ��    �ܣ� ������ֵ
 * ��    ��:  flag ��0�Ǽ� 1�Ǽ�  Work_Option����λ SetMode_Option������ģʽ EC11A_Fast ��ť�ٶ�
 * ��    ���� uint8_t flag,uint8_t Work_Option,uint8_t SetMode_Option
*****************************************************************
*/
void Set_Val(uint8_t flag,uint8_t Work_Option,uint8_t SetMode_Option,uint8_t EC11A_Fast)
{
    if(flag == 0)//��
    {
        if(EC11A_Fast < EC11A_FastSpeed)//���������ת
        {
            switch(SetMode_Option)//ģʽ
            {
                case 0:
                case 1:Work_Num[Work_Option].Speed.Set += 10;
                       if(Work_Num[Work_Option].Speed.Set == 10)//����ת��ʼ���Ϊ100ת���ж���30��
                            Work_Num[Work_Option].Speed.Set = 100;//�趨ת��Ϊ100��ʼ
                       if(Work_Num[Work_Option].Speed.Set > Speed_MAX)
							Work_Num[Work_Option].Speed.Set = Speed_MAX;
                       break;
                
                case 2:Work_Num[Work_Option].Time.Set += 60;
                        if(Work_Num[Work_Option].Time.Set > Time_MAX)
							Work_Num[Work_Option].Time.Set = Time_MAX;
                       break;
            }
        }
        else//����ת
        {
            switch(SetMode_Option)//ģʽ
            {
                case 0:
                case 1:Work_Num[Work_Option].Speed.Set += 30;
                       if(Work_Num[Work_Option].Speed.Set == 30)//����ת��ʼ���Ϊ100ת���ж���30��
                            Work_Num[Work_Option].Speed.Set = 100;//�趨ת��Ϊ100��ʼ
                       if(Work_Num[Work_Option].Speed.Set > Speed_MAX)
							Work_Num[Work_Option].Speed.Set = Speed_MAX;
                       break;
                
                case 2:Work_Num[Work_Option].Time.Set += 300;
                       if(Work_Num[Work_Option].Time.Set > Time_MAX)
							Work_Num[Work_Option].Time.Set = Time_MAX;
                       break;
            }
        }
    }
    else//��
    {
        if(EC11A_Fast < EC11A_FastSpeed)//���������ת
        {
            switch(SetMode_Option)//ģʽ
            {
                case 0:
                case 1:Work_Num[Work_Option].Speed.Set -= 10;
                       if(Work_Num[Work_Option].Speed.Set < Speed_MIN)
							Work_Num[Work_Option].Speed.Set = 0;
                       break;
                
                case 2:Work_Num[Work_Option].Time.Set -= 60;
                        if(Work_Num[Work_Option].Time.Set <= Time_MIN)
							Work_Num[Work_Option].Time.Set = Time_MIN;
                       break;
            }
        }
        else//����ת
        {
            switch(SetMode_Option)//ģʽ
            {
                case 0:
                case 1:Work_Num[Work_Option].Speed.Set -= 30;
                       if(Work_Num[Work_Option].Speed.Set < Speed_MIN)
							Work_Num[Work_Option].Speed.Set = 0;
                       break;
                       
                
                case 2:Work_Num[Work_Option].Time.Set -= 300;
                       if(Work_Num[Work_Option].Time.Set <= Time_MIN)
							Work_Num[Work_Option].Time.Set = Time_MIN;
                       break;
            }
        }
    }
    Twinkle_Time = 2.0f;
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
        if(Lock_Switch)
        {
            Beep_Flash = 2;//���εΡ�����������
            return;
        }
		EC11A[0].EC11A_Cnt++;//��ť����
		EC11A[0].EC11A_Knob = 1.0f;//����ת��ťʱ
		if(HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO,EC11A[0].EC11A_Pin) == 0)//��
		{
			sys.New_Work++;
            if(sys.New_Work > 3)
                sys.New_Work = 0;
            Beep_Time = 0.1f;
		}
		else if(HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO,EC11A[0].EC11A_Pin) == 1)//��
		{
			if(sys.New_Work == 0)
                sys.New_Work = 4;
            sys.New_Work--;
            Beep_Time = 0.1f;
		}
        sys.SetMode_Option = 0;
        Twinkle_Time = 0;
	}
    
	/**********EC11A_2**********/
	if(GPIO_Pin == EC11A[1].EXTI_Pin)//��2ms�ڣ���⵽��ƽ�仯
	{ 
        if(Lock_Switch)
        {
            Beep_Flash = 2;//���εΡ�����������
            return;
        }
		EC11A[1].EC11A_Cnt++;//��ť����
		EC11A[1].EC11A_Knob = 1.0f;//����ת��ťʱ
        sys.Sync = 0;
		if(HAL_GPIO_ReadPin(EC11A[1].EC11A_GPIO,EC11A[1].EC11A_Pin) == 0)//��
		{
			Set_Val(0,sys.New_Work,sys.SetMode_Option,EC11A[1].EC11A_Speed);
		}
		else if(HAL_GPIO_ReadPin(EC11A[1].EC11A_GPIO,EC11A[1].EC11A_Pin) == 1)//��
		{
			Set_Val(1,sys.New_Work,sys.SetMode_Option,EC11A[1].EC11A_Speed);
		}
	}
}
