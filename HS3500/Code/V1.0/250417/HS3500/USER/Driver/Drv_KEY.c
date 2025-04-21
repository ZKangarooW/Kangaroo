#include "Drv_KEY.h"

/**********�ֲ���������******/
float Key_Cnt1,Key_Cnt2,Key_Cnt3;//����ʱ��
uint8_t Key_Flag1,Key_Flag2,Key_Flag3;//�������±�־
uint8_t LongPress1,LongPress2,LongPress3;//����������־

/**
 * @brief ����ɨ��
 * 
 * @param dT ִ������
 */
void Key_Scan(float dT)
{
	/************************************P��**************************************/
	if(KEY1 == KEY_DOWN)//���°���
	{
        if(sys.Display)
        {
            return;
        }
		if(LongPress1 == 0)//û�г�����
		{
			Key_Cnt1 += dT;//����ʱ��++
			Key_Flag1 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag1 == 1)//����������
	{
		if(KEY1 == KEY_UP)//̧�𰴼�
		{   
			if(Key_Cnt1 > 0.1 && Key_Cnt1 < 1.5)//С��1.5S�ǵ���
			{
                if(sys.Lock)
				{
					Beep_Flash = 2;//���εΡ�����������
                    sys.Lock_Alarm = 2.0f;//�����󴥣�ͼ����˸����
				}
				else
				{
                    if(sys.Setting)
                    {
                        Beep_Flash = 2;
                    }
                    else
                    {
                        if (PMode.Status == 1) // �����Pģʽ
                        {
                            if(Pmode_Twinkle_Time)
                            {
                                PMode.Status = 0; // �ر�Pģʽ
                                PMode.Mode = 0;   // ����ģʽ�£���Ϊ����ֻ�ܽ���Pģʽ
                                PMode.Option = 0;
                                Param_Read();//��ȡ����
                                Pmode_Twinkle_Time = Speed_Twinkle_Time = Temp_Twinkle_Time = Time_Twinkle_Time = 0;
                            }
                            else
                            {
                                TimeSet_Flag = TempSet_Flag = SpeedSet_Flag = 1;//�����ٶ��趨
                                Speed_Twinkle_Time = Temp_Twinkle_Time = Time_Twinkle_Time = 0;
                                Pmode_Twinkle_Time = 2.0f;
                            }
                        }
                        else if (PMode.Status == 0)
                        {
                            PMode.Status = 1; // ��Pģʽ
                            PMode.Mode = 0;   // ����ģʽ�£���Ϊ����ֻ�ܽ���Pģʽ
                            PMode.Option = 1;
                            Param_Read();   // ��ȡ����
                            Speed_Twinkle_Time = Temp_Twinkle_Time = Time_Twinkle_Time = 0;
                            Pmode_Twinkle_Time = 2.0f;
                        }
                        Beep_Time = 0.1f; // ��������0.1S
                    }
                }
			}
			Key_Flag1 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress1 = 0;//������־����
			Key_Cnt1 = 0;//��ť��������
		}
		if(Key_Cnt1 > 1.5 && Key_Cnt1 < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress1 == 0)//���û��һֱһֱ������
			{
                if(sys.Lock)
				{
					Beep_Flash = 2;//���εΡ�����������
                    sys.Lock_Alarm = 2.0f;//�����󴥣�ͼ����˸����
				}
				else
				{
                    if(sys.Setting)
                    {
                        Beep_Flash = 2;
                    }
                    else
                    {
                        if (PMode.Mode) // ������ݶ�
                        {
                            PMode.Status = 1; // ��Pģʽ
                            PMode.Mode = 0;   // ����ģʽ�£���Ϊ����ֻ�ܽ���Pģʽ
                            PMode.Option = 1;
                            PMode.P1 = 0;
                            PMode.P2 = 0;
                            Param_Read(); // ��ȡ����
                            Pmode_Twinkle_Time = 2.0f;
                        }
                        else
                        {
                            PMode.Status = 2; // ��Pģʽ,ѡ���ݶȣ����ں������˸
                            PMode.Mode = 1;   // ����ģʽ�£���Ϊ����ֻ�ܽ���Pģʽ
                            PMode.P1 = 1;
                            PMode.P2 = 9;
                            PMode.Option = PMode.P1;
                            Param_Read();   // ��ȡ����
                        }
                        Beep_Time = 0.1f; // ��������0.1S
                    }
                }
				LongPress1 = 1;//������־��һ
			}
		}
	}
    
	/**************************************������**************************************/
	if(KEY2 == KEY_DOWN)//���°���
	{	
        if(sys.Display)
        {
            return;
        }
		if(LongPress2 == 0)//û�г�����
		{
			Key_Cnt2 += dT;//����ʱ��++
			Key_Flag2 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag2 == 1)//����������
	{
		if(KEY2 == KEY_UP)//̧�𰴼�
		{   
			if(Key_Cnt2 > 0.1 && Key_Cnt2 < 1.5)//С��1.5S�ǵ���
			{
                if(sys.Lock)
					sys.Lock = 0;
				else
					sys.Lock = 1;
				Beep_Time = 0.1;//��������0.1S
			}
			Key_Flag2 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress2 = 0;//������־����
			Key_Cnt2 = 0;//��ť��������		
		}
		if(Key_Cnt2 > 1.5 && Key_Cnt2 < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress2 == 0)//���û��һֱһֱ������
			{
				if(sys.Lock)
				{
					Beep_Flash = 2;//���εΡ�����������
                    sys.Lock_Alarm = 2.0f;//�����󴥣�ͼ����˸����
				}
                else
                {
                    Beep_Flash = 2;//���εΡ�����������
                }
				LongPress2 = 1;//������־��һ
			}
		}
	}
	/**************************************��ʱ��**************************************/
	if(KEY3 == KEY_DOWN)//���°���
	{	
        if(sys.Display)
        {
            return;
        }
		if(LongPress3 == 0)//û�г�����
		{
			Key_Cnt3 += dT;//����ʱ��++
			Key_Flag3 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag3 == 1)//����������
	{
		if(KEY3 == KEY_UP)//̧�𰴼�
		{   
			if(Key_Cnt3 > 0.1 && Key_Cnt3 < 1.5)//С��1.5S�ǵ���
			{
                if(sys.Lock)
				{
					Beep_Flash = 2;//���εΡ�����������
                    sys.Lock_Alarm = 2.0f;//�����󴥣�ͼ����˸����
				}
				else
				{
                    if(sys.Setting)
                    {
                        Beep_Flash = 2;
                    }
                    else
                    {
                        if(sys.SetMode_Option != 3)
                        {
                            sys.SetMode_Option = 3;
                            Time_Twinkle_Time = 6.0f;//��˸ʱ��6S
                            Temp_Twinkle_Time = 0;
                            Speed_Twinkle_Time = 0;
                            SpeedSet_Flag = 1;//�����ٶ��趨
                            TempSet_Flag = 1;//�����ٶ��趨
                        }
                        else
                        {
                            sys.SetMode_Option = 0;
                            EC11A[1].EC11A_Knob = EC11A[0].EC11A_Knob = 0;
                            Time_Twinkle_Time = 0;
                            TimeSet_Flag = 1;//����ʱ���趨
                        }
                        Beep_Time = 0.1;//��������0.1S
                    }
                }
			}
			Key_Flag3 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress3 = 0;//������־����
			Key_Cnt3 = 0;//��ť��������		
		}
		if(Key_Cnt3 > 1.5 && Key_Cnt3 < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress3 == 0)//���û��һֱһֱ������
			{
                if(sys.Lock)
				{
					Beep_Flash = 2;//���εΡ�����������
                    sys.Lock_Alarm = 2.0f;//�����󴥣�ͼ����˸����
				}
                else
                {
                    Beep_Flash = 2;//���εΡ�����������
                }
				LongPress3 = 1;//������־��һ
			}
		}
	}
    
    if(HAL_GPIO_ReadPin(Key_POR_GPIO_Port,Key_POR_Pin) == KEY_DOWN)//���°�����ʵ���ϸ������Ƿ��ģ����ڵ�DOWN��Ҫ���˹��޸ĺ�ģ�
	{	
		sys.Display = 1;
        /*�Ƴ����ý���*/
        sys.Setting = 0;
        sys.Setting_Option = 0;
        Param.Unit = Temp.Unit;//�¶ȵ�λ
        Param.TempUp_Speed = Temp.Up_Speed;//�����ٶ�
        Param.SpeedUp_Speed = Speed.Up_Speed;//�����ٶ�
        Param.Safe_Temp = Temp.Safe_Temp;//��ȫ�¶�
        Save_Param_En = 1;//����
        /*�Ƴ�Pģʽ*/
        PMode.Status = 0; // �ر�Pģʽ
        PMode.Mode = 0;   // ����ģʽ�£���Ϊ����ֻ�ܽ���Pģʽ
        PMode.Option = 0;
        Param_Read();//��ȡ����
        sys.Lock = 0;
        if(sys.Run_Status == 1)//ϵͳ�����Ļ�
        {
            Speed.ADDMode = 2;//�������ģʽ
            sys.Motor_Stop = 1;//���ֹͣ
        }
	}
    else
    {
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
}
