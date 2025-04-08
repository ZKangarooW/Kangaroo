#include "Drv_EC11A.h"

/**********�ṹ��************/
_EC11A_ EC11A[2];//��ť����

/*
*****************************************************************
 * ����ԭ�ͣ�void EC11A_Init(void)
 * ��    �ܣ�EC11A��ʼ����ʱ��
*****************************************************************
*/
void EC11A_Init(void)
{
	/**********EC11A_1**********/
	EC11A[0].EXTI_Pin = EC1A_Pin;//EC11A��ť�ж�����
	EC11A[0].EC11A_Pin = EC1B_Pin;//EC11A��ť��������
	EC11A[0].EC11A_GPIO = EC1B_GPIO_Port;//EC11A��ť����GPIO�˿�
	
	EC11A[0].Key_Pin = KEY1_Pin;//EC11A������������
	EC11A[0].Key_GPIO = KEY1_GPIO_Port;//EC11A��������GPIO�˿�
	
	EC11A[0].Tim = &EC11A_Tim_1;//��ʱ��ѡ��
	EC11A[0].EC11A_Fast = EC11A_FastSpeed;//�ж���ת�ٶ���ֵ
	
	/**********EC11A_2**********/
	EC11A[1].EXTI_Pin = EC2A_Pin;//EC11A��ť�ж�����
	EC11A[1].EC11A_Pin = EC2B_Pin;//EC11A��ť��������
	EC11A[1].EC11A_GPIO = EC2B_GPIO_Port;//EC11A��ť����GPIO�˿�
	
	EC11A[1].Key_Pin = KEY2_Pin;//EC11A������������
	EC11A[1].Key_GPIO = KEY2_GPIO_Port;//EC11A��������GPIO�˿�
	
	EC11A[1].Tim = &EC11A_Tim_2;//��ʱ��ѡ��
	EC11A[1].EC11A_Fast = EC11A_FastSpeed;//�ж���ת�ٶ���ֵ
}

/*
*****************************************************************
 * ����ԭ�ͣ�void EC11A_Speed(float dT)
 * ��    �ܣ�EC11A��ť�ٶȼ���
*****************************************************************
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

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_Press(float dT)
 * ��    �ܣ���ⰴ������״̬-500ms
*****************************************************************
*/
void Check_Press(float dT)
{
    if(EC11A[0].EC11A_Knob)//��ť0��ת
        EC11A[0].EC11A_Knob -= dT;//����ʱ
	
	if(EC11A[1].EC11A_Knob)//��ť1��ת
        EC11A[1].EC11A_Knob -= dT;//����ʱ
}

/*
*****************************************************************
 * ����ԭ�ͣ�void EC11AKey_Scan(float dT)
 * ��    �ܣ�EC11A����ɨ��
*****************************************************************
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
						Speed_Val.Integral = 43;//������
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
						Speed_Val.Integral = 43;//������
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
				Beep_Flash = 2;//���εΡ�����������
				EC11A[1].LongPress = 1;//������־��һ
			}
		}
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ�void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
 * ��    �ܣ��ⲿ�ж�
*****************************************************************
*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	UNUSED(GPIO_Pin);
	
	/**********EC11A_1**********/
	if(GPIO_Pin == EC11A[0].EXTI_Pin)//A�����ش����ⲿ�ж�
	{
		if(sys.Lock)
			return;
		HAL_TIM_Base_Start_IT(EC11A[0].Tim);//��ʼ��ʱ��
		while(EC11A[0].TIM_Cnt <= 2)//��ʱ��һ������1ms����ʱ2ms�ڿ���A��û�е�����
		{
			if(GPIO_Pin == EC11A[0].EXTI_Pin)//��2ms�ڣ���⵽��ƽ�仯
			{ 
                HAL_TIM_Base_Stop_IT(EC11A[0].Tim);//ֹͣ��ʱ��
				EC11A[0].TIM_Cnt = 0;//���TIM����
				EC11A[0].EC11A_Cnt++;//��ť����
				EC11A[0].EC11A_Knob = 2;//����ת��ťʱ
                if(sys.SetMode_Option != 3)
                    sys.SetMode_Option = 1;//�����¶�
				if(HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO,EC11A[0].EC11A_Pin) == 0)//��
				{
					if(sys.SetMode_Option == 1)
					{
						if(EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast)//���������ת
                        {
							if(Temp.Set < 1000)
                                Temp.Set += 5;
                            else
                                Temp.Set += 10;
                        }
						else
							Temp.Set += 20;
						if(Temp.Set > Temp_MAX)
							Temp.Set = Temp_MAX;
						Temp_Twinkle_Time = 2;//��˸ʱ��6S
					}
                    else if(sys.SetMode_Option == 3)
                    {
                        if(EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast)//���������ת
						{
							Time.Set += 60;
						}
						else
						{
							Time.Set += 300;
						}
						if(Time.Set > Time_MAX)
							Time.Set = Time_MAX;
						Time_Twinkle_Time = 6;//��˸ʱ��6S
                    }
					break;
				}
				else if(HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO,EC11A[0].EC11A_Pin) == 1)//��
				{
					if(sys.SetMode_Option == 1)
					{
						if(EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast)//���������ת
                        {
                            if(Temp.Set < 1000)
                                Temp.Set -= 5;
                            else
                                Temp.Set -= 10;
                        }
						else
							Temp.Set -= 20;
						if(Temp.Set <= 0)
							Temp.Set = 0;
						Temp_Twinkle_Time = 2;//��˸ʱ��2S
					}
                    else if(sys.SetMode_Option == 3)
                    {
                        if(EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast)//���������ת
						{
							Time.Set -= 60;
						}
						else
						{
							Time.Set -= 300;
						}
						if(Time.Set < 0)
							Time.Set = 0;
						Time_Twinkle_Time = 6;//��˸ʱ��6S
                    }
					break;
				}
				break;
			}
		}
		HAL_TIM_Base_Stop_IT(EC11A[0].Tim);//ֹͣ��ʱ��
		EC11A[0].TIM_Cnt = 0;//���TIM����
	}
	
	/**********EC11A_2**********/
	if(GPIO_Pin == EC11A[1].EXTI_Pin)//A�����ش����ⲿ�ж�
	{
		if(sys.Lock)
			return;
		HAL_TIM_Base_Start_IT(EC11A[1].Tim);//��ʼ��ʱ��
		while(EC11A[1].TIM_Cnt <= 2)//��ʱ��һ������1ms����ʱ2ms�ڿ���A��û�е�����
		{
			if(GPIO_Pin == EC11A[1].EXTI_Pin)//��2ms�ڣ���⵽��ƽ�仯
			{ 
				HAL_TIM_Base_Stop_IT(EC11A[1].Tim);//ֹͣ��ʱ��
				EC11A[1].TIM_Cnt = 0;//���TIM����
				EC11A[1].EC11A_Cnt++;//��ť����
				EC11A[1].EC11A_Knob = 2;//����ת��ťʱ
                if(sys.SetMode_Option != 3)
                    sys.SetMode_Option = 2;//�����ٶ�
				if(HAL_GPIO_ReadPin(EC11A[1].EC11A_GPIO,EC11A[1].EC11A_Pin) == 0)//��
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
						Speed_Twinkle_Time = 2;//��˸ʱ��6S
					}
                    else if(sys.SetMode_Option == 3)
                    {
                        if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//���������ת
						{
							Time.Set += 60;
						}
						else
						{
							Time.Set += 300;
						}
						if(Time.Set > Time_MAX)
							Time.Set = Time_MAX;
						Time_Twinkle_Time = 6;//��˸ʱ��6S
                    }
					break;
				}
				else if(HAL_GPIO_ReadPin(EC11A[1].EC11A_GPIO,EC11A[1].EC11A_Pin) == 1)//��
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
							Time.Set -= 60;
						}
						else
						{
							Time.Set -= 300;
						}
						if(Time.Set < 0)
							Time.Set = 0;
						Time_Twinkle_Time = 6;//��˸ʱ��6S
                    }
					break;
				}
				break;
			}
		}
		HAL_TIM_Base_Stop_IT(EC11A[1].Tim);//ֹͣ��ʱ��
		EC11A[1].TIM_Cnt = 0;//���TIM����
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ�void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 * ��    �ܣ���ʱ�������ж�
*****************************************************************
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == EC11A_Tim_1.Instance) 
	{
		EC11A[0].TIM_Cnt++;
	}
	
	if(htim->Instance == EC11A_Tim_2.Instance) 
	{
		EC11A[1].TIM_Cnt++;
	}
}
