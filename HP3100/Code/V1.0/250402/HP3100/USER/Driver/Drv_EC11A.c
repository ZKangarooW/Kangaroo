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
 * @param dT ִ������
 */
void EC11A_Speed(float dT)
{
	/**********EC11A_1**********/
	EC11A[0].EC11A_Speed = EC11A[0].EC11A_Cnt*60/20;//һ����һ�Ρ�תһȦ20��������һ���ӵ��ٶ�
	EC11A[0].EC11A_Cnt = 0;//����⵽�ļ�������
	
	/**********EC11A_2**********/
	EC11A[1].EC11A_Speed = EC11A[1].EC11A_Cnt*60/20;//һ����һ�Ρ�תһȦ20��������һ���ӵ��ٶ�
	EC11A[1].EC11A_Cnt = 0;//����⵽�ļ�������
}

/**
 * @brief ��ⰴ������״̬-500ms
 * 
 * @param dT ִ������
 */
void Check_Press(float dT)
{
    if(EC11A[0].EC11A_Knob)//��ť0��ת
        EC11A[0].EC11A_Knob -= dT;//����ʱ
	
	if(EC11A[1].EC11A_Knob)//��ť1��ת
        EC11A[1].EC11A_Knob -= dT;//����ʱ
}
uint8_t flagq1;
/**
 * @brief EC11A����ɨ��
 * 
 * @param dT ִ������
 */
void EC11AKey_Scan(float dT)
{
	/**********EC11A_1**********/
	if(HAL_GPIO_ReadPin(EC11A[0].Key_GPIO,EC11A[0].Key_Pin) == KEY_DOWN)//���°���
	{
        if(sys.Display)
        {
            return;
        }
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
                if(sys.Run_Status != 1 && (Temp.Set))//ϵͳû�����Ļ�
                {
                    sys.Run_Status = 1;//����ϵͳ
                    TempSet_Flag = TimeSet_Flag=1;//��������
                }
                else//ϵͳ�����Ļ�
                {
                    sys.Run_Status = 2;//�ر�
                    TempSet_Flag = TimeSet_Flag=1;//��������
                }
                Beep_Time = 0.1;//��������0.1S
			}
			EC11A[0].Key_Flag = 0;//�����¼��������ȴ���һ�ΰ���
			EC11A[0].LongPress = 0;//������־����
			EC11A[0].Key_Cnt = 0;//��ť��������
		}
		if(EC11A[0].Key_Cnt > 3.0f && EC11A[0].Key_Cnt < 4.0f)//����ʱ�����4SС��5S��ʾ����
		{
			if(EC11A[0].LongPress == 0)//���û��һֱһֱ������
			{
                
				EC11A[0].LongPress = 1;//������־��һ
			}
		}
	}
	
	/**********EC11A_2**********/
	if(HAL_GPIO_ReadPin(EC11A[1].Key_GPIO,EC11A[1].Key_Pin) == KEY_DOWN)//���°���
	{
        if(sys.Display)
        {
            return;
        }
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
                if(sys.Run_Status != 1 && (Temp.Set))//ϵͳû�����Ļ�
                {
                    sys.Run_Status = 1;//����ϵͳ
                    TempSet_Flag = TimeSet_Flag=1;//��������
                }
                else//ϵͳ�����Ļ�
                {
                    sys.Run_Status = 2;//�ر�
                    TempSet_Flag = TimeSet_Flag=1;//��������
                }
                Beep_Time = 0.1;//��������0.1S
			}
			EC11A[1].Key_Flag = 0;//�����¼��������ȴ���һ�ΰ���
			EC11A[1].LongPress = 0;//������־����
			EC11A[1].Key_Cnt = 0;//��ť��������
		}
		if(EC11A[1].Key_Cnt > 1.5 && EC11A[1].Key_Cnt < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(EC11A[1].LongPress == 0)//���û��һֱһֱ������
			{
                
				EC11A[1].LongPress = 1;//������־��һ
			}
		}
	}
    
    if(HAL_GPIO_ReadPin(Key_POR_GPIO_Port,Key_POR_Pin) == KEY_DOWN)//���°���
	{	
        flagq1 = 0;
        if(sys.Display == 1)
        {
            HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 200);//����pwm
            Lcd_All();
            Delay_ms(1000);
            Lcd_Clr();
            Beep_Time = 0.1;
            sys.Display = 0;
        }
	}
    else
    {
        flagq1 = 1;
		sys.Display = 1;
        Param.Unit = Temp.Unit;//�¶ȵ�λ
        Save_Param_En = 1;//����
        if(sys.Run_Status == 1)//ϵͳ�����Ļ�
        {
            sys.Run_Status = 2;//�ر�
            TempSet_Flag = TimeSet_Flag=1;//��������
        }
    }
}

/**
 * @brief �ⲿ�ж�
 * 
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	UNUSED(GPIO_Pin);
	
	/**********EC11A_1**********/
	if(GPIO_Pin == EC11A[0].EXTI_Pin)//A�����ش����ⲿ�ж�
	{
        if(sys.Display)
        {
            return;
        }
        if(GPIO_Pin == EC11A[0].EXTI_Pin)//��2ms�ڣ���⵽��ƽ�仯
        { 
            EC11A[0].EC11A_Cnt++;//��ť����
            EC11A[0].EC11A_Knob = 2.0f;//����ת��ťʱ
            if(HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO,EC11A[0].EC11A_Pin) == 0)//��
            {
                if(EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast)//���������ת
                {
                    if(Temp.Set < 1000)
                    {
                        Temp.Set += 5;
                    }
                    else
                    {
                        if (Temp.Set % 10)
                            Temp.Set = Temp.Set - (Temp.Set % 10);
                        Temp.Set += 10;
                    }
                }
                else
                {
                    Temp.Set += 20;
                    if (Temp.Set % 10 && Temp.Set > 1000)
                        Temp.Set = Temp.Set - (Temp.Set % 10);
                }
                if(Temp.Set > Temp_MAX)
                    Temp.Set = Temp_MAX;
                Temp_Twinkle_Time = 2;//��˸ʱ��2S
            }
            else if(HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO,EC11A[0].EC11A_Pin) == 1)//��
            {
                if(EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast)//���������ת
                {
                   if(Temp.Set < 1000)
                    {
                        Temp.Set -= 5;
                    }
                    else
                    {
                        if (Temp.Set % 10)
                            Temp.Set = Temp.Set - (Temp.Set % 10);
                        Temp.Set -= 10;
                    }
                }
                else
                {
                    Temp.Set -= 20;
                    if (Temp.Set % 10 && Temp.Set > 1000)
                        Temp.Set = Temp.Set - (Temp.Set % 10);
                }
                if(Temp.Set <= 0)
                    Temp.Set = 0;
                Temp_Twinkle_Time = 2;//��˸ʱ��2S
            }
        }
	}
	
	/**********EC11A_2**********/
	if(GPIO_Pin == EC11A[1].EXTI_Pin)//A�����ش����ⲿ�ж�
	{
        if(sys.Display)
        {
            return;
        }
        if(GPIO_Pin == EC11A[1].EXTI_Pin)//��2ms�ڣ���⵽��ƽ�仯
        { 
            EC11A[1].EC11A_Cnt++;//��ť����
            EC11A[1].EC11A_Knob = 2;//����ת��ťʱ
            if(HAL_GPIO_ReadPin(EC11A[1].EC11A_GPIO,EC11A[1].EC11A_Pin) == 0)//��
            {
                if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//���������ת
                {
                    if (Time.Set < 3600)
                        Time.Set += 5;
                    else
                    {
                        if (Time.Set % 60)
                            Time.Set = Time.Set - (Time.Set % 60);
                        else
                            Time.Set += 60;
                    }
                }
                else
                {
                    if (Time.Set < 3600)
                        Time.Set += 30;
                    else
                     {
                        if (Time.Set % 60)
                            Time.Set = Time.Set - (Time.Set % 60);
                        else
                            Time.Set += 300;
                    }
                }
                if(Time.Set > Time_MAX)
                    Time.Set = Time_MAX;
                Time_Twinkle_Time = 2;//��˸ʱ��2S
            }
            else if(HAL_GPIO_ReadPin(EC11A[1].EC11A_GPIO,EC11A[1].EC11A_Pin) == 1)//��
            {
                if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//���������ת
                {
                    if (Time.Set <= 3600)
                        Time.Set -= 5;
                    else
                    {
                        if (Time.Set % 60)
                            Time.Set = Time.Set - (Time.Set % 60);
                        else
                            Time.Set -= 60;
                    }
                }
                else
                {
                    if (Time.Set <= 3600)
                        Time.Set -= 30;
                    else
                    {
                        if (Time.Set % 60)
                            Time.Set = Time.Set - (Time.Set % 60);
                        else
                            Time.Set -= 300;
                    }
                }
                if(Time.Set < 0)
                    Time.Set = 0;
                Time_Twinkle_Time = 2;//��˸ʱ��2S
            }
        }
    }
}
