#include "Drv_EC11A.h"

/**********�ṹ��************/
_EC11A_ EC11A[1]; // ��ť����

/**
 * @brief EC11A��ʼ����ʱ��
 *
 */
void EC11A_Init(void)
{
	EC11A[0].EXTI_Pin = EC1A_Pin;		  // EC11A��ť�ж�����
	EC11A[0].EC11A_Pin = EC1B_Pin;		  // EC11A��ť��������
	EC11A[0].EC11A_GPIO = EC1B_GPIO_Port; // EC11A��ť����GPIO�˿�

	EC11A[0].Key_Pin = KEY1_Pin;		// EC11A������������
	EC11A[0].Key_GPIO = KEY1_GPIO_Port; // EC11A��������GPIO�˿�

	EC11A[0].Tim = &EC11A_Tim_1;		   // ��ʱ��ѡ��
	EC11A[0].EC11A_Fast = EC11A_FastSpeed; // �ж���ת�ٶ���ֵ
}

/**
 * @brief EC11A��ť�ٶȼ���
 *
 * @param dT ��������
 */
void EC11A_Speed(float dT)
{
	EC11A[0].EC11A_Speed = EC11A[0].EC11A_Cnt * 60 / 20; // һ����һ�Ρ�תһȦ20��������һ���ӵ��ٶ�
	EC11A[0].EC11A_Cnt = 0;								 // ����⵽�ļ�������
}

/**
 * @brief ��ⰴ������״̬-500ms
 *
 * @param dT ��������
 */
void Check_Press(float dT)
{
	if(sys.Run_Status == 0)
	{
		if(EC11A[0].EC11A_Knob)//��ť��ת��
			EC11A[0].EC11A_Knob-= 0.5; // ����ʱ
	}
	else
	{
		if(EC11A[0].EC11A_Knob)
		{
			EC11A[0].EC11A_Knob-= 0.5;//1S����ʱ
			if(EC11A[0].EC11A_Knob <= 0)
			{
				Ctrl_Speed = Set_Speed;
				Speed_ADDMode = 0;		
				Beep_Time = 0.1;//��������0.1S
			}
		}
	}
}

/**
 * @brief EC11A����ɨ��
 *
 * @param dT ��������
 */
void EC11AKey_Scan(float dT)
{
	if (HAL_GPIO_ReadPin(EC11A[0].Key_GPIO, EC11A[0].Key_Pin) == EC11A_DOWN) // ���°���
	{
		if (EC11A[0].LongPress == 0) // û�г�����
		{
			EC11A[0].Key_Cnt += dT; // ����ʱ��++
			EC11A[0].Key_Flag = 1;	// �������±�־��һ
		}
	}
	if (EC11A[0].Key_Flag == 1) // ����������
	{
		if (HAL_GPIO_ReadPin(EC11A[0].Key_GPIO, EC11A[0].Key_Pin) == EC11A_UP) // ̧�𰴼�
		{
			if (EC11A[0].Key_Cnt > 0.1f && EC11A[0].Key_Cnt < 1.5f) // С��1.5S�ǵ���
			{
				if(sys.Run_Status == 0)
                {
                    sys.SetMode_Option++;//����ģʽ++
                    if(sys.SetMode_Option == 3)
                    {
                        sys.SetMode_Option = 0;
                    }
                }
                else//�����µ���������ֱ��ֹͣ
                {
                    sys.Motor_Stop = 1;//�ر�����
					Speed_ADDMode = 2;//�������ģʽ��
                }
                Beep_Time = 0.1;//��������0.1S
                Twinkle_Time = 6000;//��˸��ʾ6S
			}
			EC11A[0].Key_Flag = 0;	// �����¼��������ȴ���һ�ΰ���
			EC11A[0].LongPress = 0; // ������־����
			EC11A[0].Key_Cnt = 0;	// ��ť��������
		}
		if (EC11A[0].Key_Cnt > 1.5f && EC11A[0].Key_Cnt < 3.0f) // ����ʱ�����1.5SС��3S��ʾ����
		{
			if (EC11A[0].LongPress == 0) // ���û��һֱһֱ������
			{
				if(sys.Run_Status == 0)
				{
					sys.Run_Status = 1;
					sys.SetMode_Option = 0;
					Speed_ADDMode = 0;
					Speed_Val.SumError=0x2422;//�������ϵ��
					Twinkle_Time = 0;
					EC11A[0].EC11A_Knob = 0;
					Speed = 0;
				} 
				else
				{
					sys.Motor_Stop = 1;//�����
					Speed_ADDMode = 2;//�������ģʽ��
				}   
				Beep_Time = 0.1;//��������0.1S
				EC11A[0].LongPress = 1; // ������־��һ
			}
		}
	}
}

/**
 * @brief �ⲿ�ж�
 *
 * @param GPIO_Pin
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	UNUSED(GPIO_Pin);

	if (GPIO_Pin == EC11A[0].EXTI_Pin) // A�����ش����ⲿ�ж�
	{
		HAL_TIM_Base_Start_IT(EC11A[0].Tim); // ��ʼ��ʱ��
		while (EC11A[0].TIM_Cnt <= 2)		 // ��ʱ��һ������1ms����ʱ2ms�ڿ���A��û�е�����
		{
			if (GPIO_Pin == EC11A[0].EXTI_Pin) // ��2ms�ڣ���⵽��ƽ�仯
			{
				HAL_TIM_Base_Stop_IT(EC11A[0].Tim);									// ֹͣ��ʱ��
				EC11A[0].TIM_Cnt = 0;												// ���TIM����
				EC11A[0].EC11A_Cnt++;												// ��ť����
				if (HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO, EC11A[0].EC11A_Pin) == 0) // ��
				{
					if(sys.Run_Status == 1 && sys.Motor_Stop == 0)
					{
						Speed = Rel_Speed/Tooth_Ratio; 
						if (EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast) // ���������ת
						{
							Set_Speed += 10;
						}
						else
						{
							Set_Speed += 30;
						}
						if(Set_Speed >= MAX_Speed)
							Set_Speed = MAX_Speed;
						EC11A[0].EC11A_Knob = 2;//����ǲ�����������ť
					}
					if(sys.SetMode_Option == 1)
					{
						if (EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast) // ���������ת
						{
							Set_Speed += 10;
						}
						else
						{
							Set_Speed += 30;
						}
						if(Set_Speed >= MAX_Speed)
							Set_Speed = MAX_Speed;
						Ctrl_Speed = Set_Speed;
						EC11A[0].EC11A_Knob = 1;//����ǲ�����������ť
					}
					if(sys.SetMode_Option == 2)
					{
						if (EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast) // ���������ת
						{
							Set_Time += 60;
						}
						else
						{
							Set_Time += 300;
						}
						Time_State = 0;//����ʾ��----��
						if(Set_Time >= 86400)
							Set_Time = 86400;
						Time = Set_Time;
						Ctrl_Time = Set_Time;
						EC11A[0].EC11A_Knob = 1;//����ǲ�����������ť
						
					}
					Twinkle_Time = 6000;//��˸��ʾ6S  
					break;
				}
				else if (HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO, EC11A[0].EC11A_Pin) == 1) // ��
				{
					if(sys.Run_Status == 1 && sys.Motor_Stop == 0)
					{
						Speed = Rel_Speed/Tooth_Ratio; 
						if (EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast) // ���������ת
						{
							Set_Speed -= 10;
						}
						else
						{
							Set_Speed -= 30;
						}
						if(Set_Speed <= MIN_Speed)
							Set_Speed = MIN_Speed;
						EC11A[0].EC11A_Knob = 2;//����ǲ�����������ť
					}
					if(sys.SetMode_Option == 1)
					{
						if (EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast) // ���������ת
						{
							Set_Speed -= 10;
						}
						else
						{
							Set_Speed -= 30;
						}
						if(Set_Speed <= MIN_Speed)
							Set_Speed = MIN_Speed;
						Ctrl_Speed = Set_Speed;
						EC11A[0].EC11A_Knob = 1;//����ǲ�����������ť
					}
					if(sys.SetMode_Option == 2)
					{
						if (EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast) // ���������ת
						{
							Set_Time -= 60;
						}
						else
						{
							Set_Time -= 300;
						}
						if(Set_Time <= 0)
						{
							Time_State = 1;//��ʾ��----��
							Set_Time = 0;
						}
						Time = Set_Time;
						EC11A[0].EC11A_Knob = 1;//����ǲ�����������ť
						
					}
					Twinkle_Time = 6000;//��˸��ʾ6S 
					break;
				}
				break;
			}
		}
		HAL_TIM_Base_Stop_IT(EC11A[0].Tim); // ֹͣ��ʱ��
		EC11A[0].TIM_Cnt = 0;				// ���TIM����
	}
}

/**
 * @brief ��ʱ�������ж�
 *
 * @param htim
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == EC11A_Tim_1.Instance)
	{
		EC11A[0].TIM_Cnt++;
	}
}
