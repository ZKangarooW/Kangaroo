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
    {
        EC11A[0].EC11A_Knob -= dT;//����ʱ
    }
	
	if(EC11A[1].EC11A_Knob)//��ť1��ת
    {
        EC11A[1].EC11A_Knob -= dT;//����ʱ
    }
}

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
                if(sys.Lock)
				{
					Beep_Flash = 2;//���εΡ�����������
                    sys.Lock_Alarm = 2.0f;//�����󴥣�ͼ����˸����
				}
				else
				{
                    if (sys.Setting == 1) // ���������ģʽ
                    {
                        sys.Setting_Option++;
                        if(sys.Setting_Option > 4)
                            sys.Setting_Option = 0;
                    }
                    else//����ģʽ
                    {
                        if(sys.Run_Status != 1 && (Speed.Set || Temp.Set))//ϵͳû�����Ļ�
                        {
                            sys.Run_Status = 1;//����ϵͳ
                            Speed.ADDMode = 0;//�����ж��ٶ���ʾ����
                            if(Speed.Up_Speed == 1)//����
                            {
                                Speed_Val.Integral = 30;//������
                            }
                            else if(Speed.Up_Speed == 2)//����
                            {
                                Speed_Val.Integral = 40;//������
                            }
                            else//����
                            {
                                Speed_Val.Integral = 30;//������
                            }
                        }
                        else//ϵͳ�����Ļ�
                        {
                            Speed.ADDMode = 2;//�������ģʽ
                            sys.Motor_Stop = 1;//���ֹͣ
                        }
                    }
                    Beep_Time = 0.1;//��������0.1S
                }
			}
			EC11A[0].Key_Flag = 0;//�����¼��������ȴ���һ�ΰ���
			EC11A[0].LongPress = 0;//������־����
			EC11A[0].Key_Cnt = 0;//��ť��������
		}
		if(EC11A[0].Key_Cnt > 3.0f && EC11A[0].Key_Cnt < 4.0f)//����ʱ�����4SС��5S��ʾ����
		{
			if(EC11A[0].LongPress == 0)//���û��һֱһֱ������
			{
                if(sys.Lock)
				{
					Beep_Flash = 2;//���εΡ�����������
                    sys.Lock_Alarm = 2.0f;//�����󴥣�ͼ����˸����
				}
				else
				{
                    if (sys.Setting == 1) // ���������ģʽ
                    {
                        sys.Setting = 0;//�Ƴ����ý���
                        sys.Setting_Option = 0;
                        Param.Unit = Temp.Unit;//�¶ȵ�λ
                        Param.TempUp_Speed = Temp.Up_Speed;//�����ٶ�
                        Param.SpeedUp_Speed = Speed.Up_Speed;//�����ٶ�
                        Param.Safe_Temp = Temp.Safe_Temp;//��ȫ�¶�
                        Param.DownTime_Type = sys.DownTime_Type;//����ʱ���͸�ֵ��Flash��
                        Save_Param_En = 1;//����
                    }
                    else if (sys.Setting == 0)
                    {
                        sys.Setting = 1;//�������ý���
                        sys.Setting_Option = 0;
                    }
                    Beep_Time = 0.1f; // ��������0.1S
                }
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
                if(sys.Lock)
				{
					Beep_Flash = 2;//���εΡ�����������
                    sys.Lock_Alarm = 2.0f;//�����󴥣�ͼ����˸����
				}
				else
				{
                    if(sys.Run_Status != 1 && (Speed.Set || Temp.Set))//ϵͳû�����Ļ�
                    {
                        sys.Run_Status = 1;//����ϵͳ
                        Speed.ADDMode = 0;//�����ж��ٶ���ʾ����
                        if(Speed.Up_Speed == 1)//����
                        {
                            Speed_Val.Integral = 30;//������
                        }
                        else if(Speed.Up_Speed == 2)//����
                        {
                            Speed_Val.Integral = 40;//������
                        }
                        else//����
                        {
                            Speed_Val.Integral = 30;//������
                        }
                    }
                    else//ϵͳ�����Ļ�
                    {
                        Speed.ADDMode = 2;//�������ģʽ
                        sys.Motor_Stop = 1;//���ֹͣ
                    }
                    SpeedSet_Flag = TempSet_Flag = TimeSet_Flag=1;//��������
                    Speed_Twinkle_Time = Temp_Twinkle_Time = Time_Twinkle_Time = 0;//�ر���˸
                    Beep_Time = 0.1;//��������0.1S
                    sys.SetMode_Option = 0;
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
                if(sys.Lock)
				{
					Beep_Flash = 2;//���εΡ�����������
                    sys.Lock_Alarm = 2.0f;//�����󴥣�ͼ����˸����
				}
				else
				{
                    if(!Speed.Cw)//�ı�ת��Ļ�
                    {
                        Speed.ADDMode = 2;//��ȥ������ʾ
                        sys.Motor_Stop = 1;//���ֹͣ
                        Speed.Cw = 1;//����ı�ת��
                        Speed.CwShow = 1;//ת��ͼ��ı䣬������ʼ
                        SpeedSet_Flag = TempSet_Flag = TimeSet_Flag=1;//��������
                    }
                    Beep_Time = 0.1;//��������0.1S
                }
				EC11A[1].LongPress = 1;//������־��һ
			}
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
        if(sys.Lock)
        {
            Beep_Flash = 2;//���εΡ�����������
            sys.Lock_Alarm = 2.0f;//�����󴥣�ͼ����˸����
            return;
        }
        if(GPIO_Pin == EC11A[0].EXTI_Pin)//��2ms�ڣ���⵽��ƽ�仯
        { 
            EC11A[0].EC11A_Cnt++;//��ť����
            EC11A[0].EC11A_Knob = 2.0f;//����ת��ťʱ
            if(sys.SetMode_Option != 3)
                sys.SetMode_Option = 1;//�����¶�
            if(HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO,EC11A[0].EC11A_Pin) == 0)//��
            {
                if(sys.Setting) //������ģʽ��
                {
                    if(sys.Setting_Option == 0)
                    {
                        if(Temp.Up_Speed == 0)
                            Temp.Up_Speed = 2;
                        else
                            Temp.Up_Speed--;
                        
                    }
                    else if(sys.Setting_Option == 1)
                    {
                        if(Speed.Up_Speed == 0)
                            Speed.Up_Speed = 2;
                        else
                            Speed.Up_Speed--;
                    }
                    else if(sys.Setting_Option == 2)
                    {
                        if(sys.DownTime_Type == 0)
                            sys.DownTime_Type = 2;
                        sys.DownTime_Type--;
                    }
                    else if(sys.Setting_Option == 3)
                    {
                        Temp.Safe_Temp-=100;
                        if(Temp.Safe_Temp < 500)
                            Temp.Safe_Temp = 500;
                        if(Temp.Safe_Temp-500<Temp.Set)
                        {
                            Temp.Set = Temp.Safe_Temp-500;
                            TempSet_Flag = 1;
                        }
                        for (uint8_t i = 0; i <= 9; i++)
                        {
                            if(Temp.Safe_Temp-500<Param.P_Param[i][0])
                                Param.P_Param[i][0] = Temp.Safe_Temp-500; // �¶�
                        }
                        Save_Param_En = 1;//����
                    }
                    else if(sys.Setting_Option == 4)
                    {
                        if(Temp.Unit == 0)
                            Temp.Unit = 1;
                        else
                            Temp.Unit--;
                    }
                }
                else if (Pmode_Twinkle_Time) // ���������Pֵʱ
                {
                    PMode.Option --;
                    if(PMode.Option < 1)
                        PMode.Option = 9;
                    Param_Read(); // ��ȡ����
                    Pmode_Twinkle_Time = 2.0f;
                }
                else if(PMode.Mode)//�ݶ�ģʽ
                {
                    PMode.P1--;
                    if (PMode.P1 < 1)
                        PMode.P1 = 8;
                    PMode.Option = PMode.P1;
                    Param_Read(); // ��ȡ����
                    PModeP1_Twinkle_Time = 2.0f;
                }
                else
                {
                    if(sys.SetMode_Option == 1)
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
                    else if(sys.SetMode_Option == 3)
                    {
                        if(EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast)//���������ת
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
            else if(HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO,EC11A[0].EC11A_Pin) == 1)//��
            {
                if(sys.Setting) //������ģʽ��
                {
                    if(sys.Setting_Option == 0)
                    {
                        Temp.Up_Speed++;
                        if(Temp.Up_Speed > 2)
                            Temp.Up_Speed = 0;
                    }
                    else if(sys.Setting_Option == 1)
                    {
                        Speed.Up_Speed++;
                        if(Speed.Up_Speed > 2)
                            Speed.Up_Speed = 0;
                    }
                    else if(sys.Setting_Option == 2)
                    {
                        sys.DownTime_Type++;
                        if(sys.DownTime_Type > 1)
                            sys.DownTime_Type = 0;
                    }
                    else if(sys.Setting_Option == 3)
                    {
                        Temp.Safe_Temp+=100;
                        if(Temp.Safe_Temp > Temp_MAX+500)
                            Temp.Safe_Temp = Temp_MAX+500;
                        if(Temp.Safe_Temp-500<Temp.Set)
                        {
                            Temp.Set = Temp.Safe_Temp-500;
                            TempSet_Flag = 1;
                        }
                        for (uint8_t i = 0; i <= 9; i++)
                        {
                            if(Temp.Safe_Temp-500<Param.P_Param[i][0])
                                Param.P_Param[i][0] = Temp.Safe_Temp-500; // �¶�
                        }
                        Save_Param_En = 1;//����
                    }
                    else if(sys.Setting_Option == 4)
                    {
                        Temp.Unit++;
                        if(Temp.Unit > 1)
                            Temp.Unit = 0;
                    }
                }
                else if (Pmode_Twinkle_Time) // ���������Pֵʱ
                {
                    PMode.Option ++;
                    if(PMode.Option > 9)
                        PMode.Option = 1;
                    Param_Read(); // ��ȡ����
                    Pmode_Twinkle_Time = 2.0f;
                }
                else if(PMode.Mode)//�ݶ�ģʽ
                {
                    PMode.P1++;
                    if (PMode.P1 > 8)
                        PMode.P1 = 1;
                    if(PMode.P1 >= PMode.P2)
                        PMode.P2 = PMode.P1 +1;
                    PMode.Option = PMode.P1;
                    Param_Read(); // ��ȡ����
                    PModeP1_Twinkle_Time = 2.0f;
                }
                else
                {
                    if(sys.SetMode_Option == 1)
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
                        if(Temp.Set > Temp.Safe_Temp - 500)
                            Temp.Set = Temp.Safe_Temp - 500;
                        Temp_Twinkle_Time = 2;//��˸ʱ��2S
                    }
                    else if(sys.SetMode_Option == 3)
                    {
                        if(EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast)//���������ת
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
                }
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
        if(sys.Lock)
        {
            Beep_Flash = 2;//���εΡ�����������
            sys.Lock_Alarm = 2.0f;//�����󴥣�ͼ����˸����
            return;
        }
        if(GPIO_Pin == EC11A[1].EXTI_Pin)//��2ms�ڣ���⵽��ƽ�仯
        { 
            EC11A[1].EC11A_Cnt++;//��ť����
            EC11A[1].EC11A_Knob = 2;//����ת��ťʱ
            if(sys.SetMode_Option != 3)
                sys.SetMode_Option = 2;//�����ٶ�
            if(HAL_GPIO_ReadPin(EC11A[1].EC11A_GPIO,EC11A[1].EC11A_Pin) == 0)//��
            {
                if (Pmode_Twinkle_Time) // ���������Pֵʱ
                {
                    PMode.Option ++;
                    if(PMode.Option > 9)
                        PMode.Option = 1;
                    Param_Read(); // ��ȡ����
                }
                else if(PMode.Mode)//�ݶ�ģʽ
                {
                    PMode.P2++;
                    if (PMode.P2 > 9)
                        PMode.P2 = 2;
                    if (PMode.P2 <= PMode.P1)
                        PMode.P2 = PMode.P1+1;
                    
                    PMode.Option = PMode.P2;
                    Param_Read(); // ��ȡ����
                    PModeP2_Twinkle_Time = 2.0f;
                }
                else
                {
                    if(sys.SetMode_Option == 2)
                    {
                        if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//���������ת
                        {
                            Speed.Set += 10;
                            if(Speed.Set == 10)//����ת��ʼ���Ϊ50ת���ж���10��
                                Speed.Set = 100;//�趨ת��Ϊ100��ʼ
                        }
                        else
                        {
                            Speed.Set += 30;
                            if(Speed.Set == 30)//����ת��ʼ���Ϊ50ת���ж���10��
                                Speed.Set = 100;//�趨ת��Ϊ100��ʼ
                        }
                        if(Speed.Set > Speed_MAX)
                            Speed.Set = Speed_MAX;
                        Speed_Twinkle_Time = 2;//��˸ʱ��2S
                    }
                    else if(sys.SetMode_Option == 3)
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
                }
                else if(PMode.Mode)//�ݶ�ģʽ
                {
                    PMode.P2--;
                    if (PMode.P2 < 2)
                        PMode.P2 = 9;
                    if (PMode.P2 <= PMode.P1)
                        PMode.P2 = PMode.P1+1;
                    PMode.Option = PMode.P2;
                    Param_Read(); // ��ȡ����
                    PModeP2_Twinkle_Time = 2.0f;
                }
                else
                {
                    if(sys.SetMode_Option == 2)
                    {
                        if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//���������ת
                        {
                            Speed.Set -= 10;
                        }
                        else
                        {
                            Speed.Set -= 30;
                        }
                        if(Speed.Set < Speed_MIN)
                            Speed.Set = 0;
                        Speed_Twinkle_Time = 2;//��˸ʱ��6S
                    }
                    else if(sys.SetMode_Option == 3)
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
    }
}
