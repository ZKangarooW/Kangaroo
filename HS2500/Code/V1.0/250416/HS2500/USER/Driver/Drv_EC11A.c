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
	EC11A[0].Key_GPIO = KEY1_GPIO_Port;//EC11A����GPIO�˿�
	
	EC11A[0].EC11A_Fast = EC11A_FastSpeed;//�ж���ת�ٶ���ֵ

	/**********EC11A_2**********/
	EC11A[1].EXTI_Pin = EC2A_Pin;//EC11A��ť�ж�����
	EC11A[1].EC11A_Pin = EC2B_Pin;//EC11A��ť��������
	EC11A[1].EC11A_GPIO = EC2B_GPIO_Port;//EC11A��ť����GPIO�˿�
	
	EC11A[1].Key_Pin = KEY2_Pin;//EC11A������������
	EC11A[1].Key_GPIO = KEY2_GPIO_Port;//EC11A����GPIO�˿�
	
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
	EC11A[0].EC11A_Speed = EC11A[0].EC11A_Cnt*60/20;//һ��һ�Ρ�תһȦ20�����壬һ���ӵ��ٶ�
	EC11A[0].EC11A_Cnt = 0;//���⵽���������
	
	/**********EC11A_2**********/
	EC11A[1].EC11A_Speed = EC11A[1].EC11A_Cnt*60/20;//һ��һ�Ρ�תһȦ20�����壬һ���ӵ��ٶ�
	EC11A[1].EC11A_Cnt = 0;//���⵽���������
}

/**
 * @brief ��ⰴ��״̬-500ms
 * 
 * @param dT ִ������
 */
void Check_Press(float dT)
{
    if(EC11A[0].EC11A_Knob) //��ť0��ת
    {
        EC11A[0].EC11A_Knob -= dT; //�ݼ�ʱ��
    }
    
    if(EC11A[1].EC11A_Knob) //��ť1��ת
    {
        EC11A[1].EC11A_Knob -= dT; //�ݼ�ʱ��
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
	if(HAL_GPIO_ReadPin(EC11A[0].Key_GPIO,EC11A[0].Key_Pin) == GPIO_PIN_RESET)//���°���
	{
        // if(sys.Display)
        // {
        //     return;
        // }
		if(EC11A[0].LongPress == 0)//û�г���
		{
			EC11A[0].Key_Cnt += dT;//����ʱ��++
			EC11A[0].Key_Flag = 1;//�������±�־��1
		}
	}
	if(EC11A[0].Key_Flag == 1)//�����Ѱ���
	{
		if(HAL_GPIO_ReadPin(EC11A[0].Key_GPIO,EC11A[0].Key_Pin) == GPIO_PIN_SET)//̧�𰴼�
		{   
			if(EC11A[0].Key_Cnt > 0.1 && EC11A[0].Key_Cnt < 1.5)//С��1.5S�ǵ���
			{
                if(sys.Lock)
				{
					Beep_Flash = 2;//�������̴�������
                    sys.Lock_Alarm = 2.0f;//��������������ͼ����˸����
				}
				else
				{
                    if (sys.Setting == 1) // ��������ģʽʱ
                    {
                        sys.Setting_Option++;
                        if(sys.Setting_Option > 4)
                            sys.Setting_Option = 0;
                    }
                    else//����ģʽ
                    {
                        if(sys.Run_Status != 1 && (Speed.Set || Temp.Set))//ϵͳû������ʱ
                        {
                            sys.Run_Status = 1;//����ϵͳ
                            Speed.ADDMode = 0;//����ٶ���ʾ��־
                            if(Speed.Up_Speed == 1)//����
                            {
                                Speed_Val.Integral = 30;//����ֵ
                            }
                            else if(Speed.Up_Speed == 2)//����
                            {
                                Speed_Val.Integral = 40;//����ֵ
                            }
                            else//����
                            {
                                Speed_Val.Integral = 30;//����ֵ
                            }
                        }
                        else//ϵͳ����ʱ
                        {
                            Speed.ADDMode = 2;//����ģʽ
                            sys.Motor_Stop = 1;//���ֹͣ
                        }
                    }
                    Beep_Time = 0.1;//����ʱ��0.1S
                }
			}
			EC11A[0].Key_Flag = 0;//��������¼����ȴ���һ�ΰ���
			EC11A[0].LongPress = 0;//������־����
			EC11A[0].Key_Cnt = 0;//��������������
		}
		if(EC11A[0].Key_Cnt > 3.0f && EC11A[0].Key_Cnt < 4.0f)//����ʱ�����3SС��4S��ʾ����
		{
			if(EC11A[0].LongPress == 0)//�����û��һֱ��ס
			{
                if(sys.Lock)
				{
					Beep_Flash = 2;//�������̴�������
                    sys.Lock_Alarm = 2.0f;//��������������ͼ����˸����
				}
				else
				{
                    if (sys.Setting == 1) // ��������ģʽʱ
                    {
                        sys.Setting = 0;//�˳����ý���
                        sys.Setting_Option = 0;
                        Param.Unit = Temp.Unit;//�¶ȵ�λ
                        Param.TempUp_Speed = Temp.Up_Speed;//�����ٶ�
                        Param.SpeedUp_Speed = Speed.Up_Speed;//�����ٶ�
                        Param.Safe_Temp = Temp.Safe_Temp;//��ȫ�¶�
                        Param.DownTime_Type = sys.DownTime_Type;//ͣ��ʱ������д��Flash
                        Save_Param_En = 1;//����
                    }
                    else if (sys.Setting == 0)
                    {
                        sys.Setting = 1;//�������ý���
                        sys.Setting_Option = 0;
                    }
                    Beep_Time = 0.1f; // ����ʱ��0.1S
                }
				EC11A[0].LongPress = 1;//������־��1
			}
		}
	}
	
	/**********EC11A_2**********/
	if(HAL_GPIO_ReadPin(EC11A[1].Key_GPIO,EC11A[1].Key_Pin) == GPIO_PIN_RESET)//���°���
	{
        // if(sys.Display)
        // {
        //     return;
        // }
		if(EC11A[1].LongPress == 0)//û�г���
		{
			EC11A[1].Key_Cnt += dT;//����ʱ��++
			EC11A[1].Key_Flag = 1;//�������±�־��1
		}
	}
	if(EC11A[1].Key_Flag == 1)//�����Ѱ���
	{
		if(HAL_GPIO_ReadPin(EC11A[1].Key_GPIO,EC11A[1].Key_Pin) == GPIO_PIN_SET)//̧�𰴼�
		{   
			if(EC11A[1].Key_Cnt > 0.1 && EC11A[1].Key_Cnt < 1.5)//С��1.5S�ǵ���
			{
                if(sys.Lock)
				{
					Beep_Flash = 2;//�������̴�������
                    sys.Lock_Alarm = 2.0f;//��������������ͼ����˸����
				}
				else
				{
                    if(sys.Run_Status != 1 && (Speed.Set || Temp.Set))//ϵͳû������ʱ
                    {
                        sys.Run_Status = 1;//����ϵͳ
                        Speed.ADDMode = 0;//����ٶ���ʾ��־
                        if(Speed.Up_Speed == 1)//����
                        {
                            Speed_Val.Integral = 30;//����ֵ
                        }
                        else if(Speed.Up_Speed == 2)//����
                        {
                            Speed_Val.Integral = 40;//����ֵ
                        }
                        else//����
                        {
                            Speed_Val.Integral = 30;//����ֵ
                        }
                    }
                    else//ϵͳ����ʱ
                    {
                        Speed.ADDMode = 2;//����ģʽ
                        sys.Motor_Stop = 1;//���ֹͣ
                    }
                    SpeedSet_Flag = TempSet_Flag = TimeSet_Flag=1;//���ñ�־
                    Speed_Twinkle_Time = Temp_Twinkle_Time = Time_Twinkle_Time = 0;//�ر���˸
                    Beep_Time = 0.1;//����ʱ��0.1S
                    sys.SetMode_Option = 0;
                }
			}
			EC11A[1].Key_Flag = 0;//��������¼����ȴ���һ�ΰ���
			EC11A[1].LongPress = 0;//������־����
			EC11A[1].Key_Cnt = 0;//��������������
		}
		if(EC11A[1].Key_Cnt > 1.5 && EC11A[1].Key_Cnt < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(EC11A[1].LongPress == 0)//�����û��һֱ��ס
			{
                if(sys.Lock)
				{
					Beep_Flash = 2;//�������̴�������
                    sys.Lock_Alarm = 2.0f;//��������������ͼ����˸����
				}
				else
				{
                    if(!Speed.Cw)//�ı�ת��ʱ
                    {
                        Speed.ADDMode = 2;//����ģʽ
                        sys.Motor_Stop = 1;//���ֹͣ
                        Speed.Cw = 1;//�ı�ת��
                        Speed.CwShow = 1;//ת��ͼ��ı䣬���¿�ʼ
                        SpeedSet_Flag = TempSet_Flag = TimeSet_Flag=1;//���ñ�־
                    }
                    Beep_Time = 0.1;//����ʱ��0.1S
                }
				EC11A[1].LongPress = 1;//������־��1
			}
		}
	}
}
