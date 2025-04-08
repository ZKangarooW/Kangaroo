#include "Drv_Key.h"

/**********ȫ�ֱ�������******/
uint8_t Key_Status;//�������±�־

/**********�ֲ���������******/
float Key_Cnt1,Key_Cnt2,Key_Cnt3,Key_Cnt4;//����ʱ��
uint8_t Key_Flag1,Key_Flag2,Key_Flag3,Key_Flag4;//�������±�־
uint8_t LongPress1,LongPress2,LongPress3,LongPress4;//����������־
uint16_t Rcf[13] = {67,151,268,419,604,822,1073,1358,1677,2029,2415,2834,3286};

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_Press(float dT)
 * ��    �ܣ���ⰴ������״̬-500ms
*****************************************************************
*/
void Check_Press(float dT)
{
    if(Key_Status)//��������
        Key_Status -= dT;//����ʱ
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Key_Scan(float dT)
 * ��    �ܣ����󰴼�ɨ��
*****************************************************************
*/
void Key_Scan(float dT)
{
	/**************************************����**************************************/
	if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin) == 0)//���°���
	{
		Key_Cnt1 += dT;//����ʱ��++
		Key_Flag1 = 1;//�������±�־��һ
	}
	if(Key_Flag1 == 1)//����������
	{
		if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin) == 1)//̧�𰴼�
		{   
			if(Key_Cnt1 < 1.5)//С��1.5S�ǵ���
			{
				if(sys.Run_Status == 1|| Speed.Rel_Speed > 0)
				{
					Beep_Flash = 2;//��Ч����ʱ���������εΡ�
				}
				else
				{
					if(sys.SetMode_Option == 1)//�������ٶ�ʱ
					{
						if(Speed.Speed_Mode==0)//�ٶ�
						{
							Speed.Set_Speed -= 500;//�ٶ�-500
							if(Speed.Set_Speed < Speed_MIN)//�ٶ�С��Speed_MIN
								Speed.Set_Speed = Speed_MIN;//�ٶ���СΪSpeed_MIN���²�ȥ��
						}
						else//������
						{
							if(Speed.Speed_Rcf)
								Speed.Speed_Rcf--;
							Speed.Set_Speed = Rcf[Speed.Speed_Rcf];//������
						}
					}
					else if(sys.SetMode_Option == 2)//������ʱ��ʱ
					{
						if(Time.Set_Time <= 60)//����Ϊ��λʱ
							Time.Set_Time -= 1;//ʱ��--
						else//����Ϊ��λʱ
							Time.Set_Time -= 60;//ÿ��ʱ���һ����
						if(Time.Set_Time < Time_MIN)//ʱ��С��Time_MIN��ʱ
							Time.Set_Time = Time_MIN;//����ʱ��ΪTime_MIN
					}
					else 
					{
						Beep_Flash = 2;//��Ч����ʱ���������εΡ�
					}
					Key_Status = 1;//����һ�룬��ʾ����ʱ��1s�ĵȴ�������˸
					Twinkle_Time = 6;//һ����˸6S
				}
			}
			Key_Flag1 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt1 = 0;//��ť��������
		}
		if(Key_Cnt1 > 1.9 && Key_Cnt1 < 2.1)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(sys.Run_Status == 1|| Speed.Rel_Speed > 0)
			{
				Beep_Flash = 2;//��Ч����ʱ���������εΡ�
			}
			else
			{
				if(sys.SetMode_Option == 1)//�������ٶ�ʱ
				{
					if(Speed.Speed_Mode==0)//�ٶ�
					{
						Speed.Set_Speed -= 1000;//�ٶ�-1000
						if(Speed.Set_Speed < Speed_MIN)//�ٶ�С��Speed_MIN
							Speed.Set_Speed = Speed_MIN;//�ٶ���СΪSpeed_MIN���²�ȥ��
					}
					else//������
					{
						if(Speed.Speed_Rcf)
							Speed.Speed_Rcf--;
						Speed.Set_Speed = Rcf[Speed.Speed_Rcf];
					}
				}
				else if(sys.SetMode_Option == 2)//������ʱ��ʱ
				{
					if(Time.Time_Unit == 0)//����Ϊ��λʱ
						Time.Set_Time -= 10;//ʱ���10S
					else//����Ϊ��λʱ
					{
						Time.Set_Time -= 600;//ÿ��ʱ���һ����
						if(Time.Set_Time<60)
							Time.Set_Time = 59;
					}
					if(Time.Set_Time < Time_MIN)//ʱ��С��Time_MIN��ʱ
						Time.Set_Time = Time_MIN;//����ʱ��ΪTime_MIN
				}
				else 
				{
					Beep_Flash = 2;//��Ч����ʱ���������εΡ�
				}
				Key_Status = 1;//����һ�룬��ʾ����ʱ��1s�ĵȴ�������˸
				Twinkle_Time = 6;//һ����˸6S
			}
			Key_Flag1 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt1 = 1.5;//��ť����
		}
	}
	/**************************************�Ӽ�**************************************/
	if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)== 0)//���°���
	{
		Key_Cnt2 += dT;//����ʱ��++
		Key_Flag2 = 1;//�������±�־��һ
	}
	if(Key_Flag2 == 1)//����������
	{
		if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) == 1)//̧�𰴼�
		{   
			if(Key_Cnt2 < 1.5)//С��1.5S�ǵ���
			{
				if(sys.Run_Status == 1|| Speed.Rel_Speed > 0)
				{
					Beep_Flash = 2;//��Ч����ʱ���������εΡ�
				}
				else
				{
					if(sys.SetMode_Option == 1)//�������ٶ�ʱ
					{
						if(Speed.Speed_Mode==0)//�ٶ�
						{
							Speed.Set_Speed +=500;//�ٶ�+500
							if(Speed.Set_Speed > Speed_MAX)//�ٶȴ���Speed_MAXʱ
								Speed.Set_Speed = Speed_MAX;//�ٶ����ΪSpeed_MAX���ϲ�ȥ��
						}
						else//������
						{
							Speed.Speed_Rcf++;
							if(Speed.Speed_Rcf>Rcf_MAX)
								Speed.Speed_Rcf = Rcf_MAX;
							Speed.Set_Speed = Rcf[Speed.Speed_Rcf];
						}
					}
					else if(sys.SetMode_Option == 2)//������ʱ��ʱ
					{
						if(Time.Set_Time == 0)//����ʱ��Ϊ0ʱ
							Time.Set_Time += 59;//��һ�뿪ʼ��
						if(Time.Time_Unit == 0)//����Ϊ��λʱ
							Time.Set_Time += 1;//����ʱ���1��
						else//����Ϊ��λʱ
							Time.Set_Time += 60;//����ʱ���1����
						if(Time.Set_Time>Time_MAX)//ʱ�����Time_MAX��ʱ��99���ӣ�
							Time.Set_Time = Time_MAX;//ʱ�����Ϊ99����
					}
					else 
					{
						Beep_Flash = 2;//��Ч����ʱ���������εΡ�
					}
					Key_Status = 1;//����һ�룬��ʾ����ʱ��1s�ĵȴ�������˸
					Twinkle_Time = 6;//һ����˸6S
				}
			}
			Key_Flag2 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt2 = 0;//��ť��������		
		}
		if(Key_Cnt2 > 1.9 && Key_Cnt2 < 2.1)//����ʱ�����1.9SС��2.1S��ʾ����
		{
			if(sys.Run_Status == 1|| Speed.Rel_Speed > 0)
			{
				Beep_Flash = 2;//��Ч����ʱ���������εΡ�
			}
			else
			{
				if(sys.SetMode_Option == 1)//�������ٶ�ʱ
				{
					if(Speed.Speed_Mode==0)//�ٶ�
					{
						Speed.Set_Speed += 1000;//�ٶȼ�1000
						if(Speed.Set_Speed > Speed_MAX)//�ٶȴ���Speed_MAXʱ
							Speed.Set_Speed = Speed_MAX;//�ٶ����ΪSpeed_MAX���ϲ�ȥ��
					}
					else//������
					{
						Speed.Speed_Rcf++;
						if(Speed.Speed_Rcf>Rcf_MAX)
							Speed.Speed_Rcf = Rcf_MAX;
						Speed.Set_Speed = Rcf[Speed.Speed_Rcf];
					}
				}
				else if(sys.SetMode_Option == 2)//������ʱ��ʱ
				{
					if(Time.Set_Time == 0)//����ʱ��Ϊ0ʱ
						Time.Set_Time += 60;//��һ�뿪ʼ��
					if(Time.Time_Unit == 0)//����Ϊ��λʱ
					{
						Time.Set_Time += 10;//����ʱ���1����
						if(Time.Set_Time > 60)
							Time.Set_Time = 60;
					}
					else//����Ϊ��λʱ
						Time.Set_Time += 600;//����ʱ���10����
					if(Time.Set_Time>Time_MAX)//ʱ�����Time_MAX��ʱ��99���ӣ�
						Time.Set_Time = Time_MAX;//ʱ�����Ϊ99����
				}
				else 
				{
					Beep_Flash = 2;//��Ч����ʱ���������εΡ�
				}
				Key_Status = 1;//����һ�룬��ʾ����ʱ��1s�ĵȴ�������˸
				Twinkle_Time = 6;//һ����˸6S
			}
			Key_Flag2 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt2 = 1.5;//��ť����
		}
	}
	/**************************************Start��**************************************/
	if(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin) == 0)//���°���
	{
		if(LongPress3 == 0)//û�г�����
		{
			Key_Cnt3 += dT;//����ʱ��++
			Key_Flag3 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag3 == 1)//����������
	{
		if(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin) == 1)//̧�𰴼�
		{   
			if(Key_Cnt3 < 1.5)/*����*///С��1.5S�ǵ���
			{
				if(HAL_GPIO_ReadPin(KEY_UP_GPIO_Port,KEY_UP_Pin)== 1)//������պ�ʱ
				{
					if(sys.Run_Status)//ϵͳ����
					{
						sys.Run_Status = 0;//ϵͳ�ر�
						Beep_Time = 0.1;//��������0.1S
					}
					else//ϵͳû������
					{
						SetOK_Flag = 1;//�趨��ֵ��־
						sys.Run_Status = 1;//����ϵͳ
						sys.SetMode_Option = 0;//����ѡ������
						Beep_Time = 0.1;//��������0.1S
					}	
				}
				else
				{
					Beep_Flash = 7;
					sys.Lock_On = 1;
				}
			}
			Key_Flag3 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress3 = 0;//������־����
			Key_Cnt3 = 0;//��ť��������		
		}
		if(Key_Cnt3 > 1.5 && Key_Cnt3 < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress3 == 0)/*����*///���û��һֱһֱ������
			{
				Beep_Flash = 2;//��Ч����ʱ���������εΡ�
				LongPress3 = 1;//������־��һ
			}
		}
	}
	/**************************************MENU��**************************************/
	if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin )== 0)//���°���
	{
		if(LongPress4 == 0)//û�г�����
		{
			Key_Cnt4 += dT;//����ʱ��++
			Key_Flag4 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag4 == 1)//����������
	{
		if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin) == 1)//̧�𰴼�
		{   
			if(Key_Cnt4 < 1.5)//С��1.5S�ǵ���
			{
				if(sys.Run_Status == 1|| Speed.Rel_Speed > 0)
				{
					Beep_Flash = 2;//��Ч����ʱ���������εΡ�
				}
				else
				{
					sys.SetMode_Option++;//����ѡ��++
					if(sys.Run_Status == 0)//û�����������
					{
						if(sys.SetMode_Option > 2)//����ѡ�����2
						{
							sys.SetMode_Option = 0;//����ѡ������
						}
					}
					else//�����������
					{
						if(sys.SetMode_Option > 1)//����ѡ�����1
						{
							sys.SetMode_Option = 0;//����ѡ������
						}
					}
					Twinkle_Time = 6;//һ����˸6S
					Beep_Time = 0.1;//��������0.1S
				}
			}
			Key_Flag4 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress4 = 0;//������־����
			Key_Cnt4 = 0;//��ť��������		
		}
		if(Key_Cnt4 > 1.5 && Key_Cnt4 < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress4 == 0)//���û��һֱһֱ������
			{
				if(sys.Run_Status == 1|| Speed.Rel_Speed > 0)
				{
					Beep_Flash = 2;//��Ч����ʱ���������εΡ�
				}
				else
				{
					if(Speed.Speed_Mode)//��������������ģʽ��
					{
						Speed.Speed_Mode = 0;//������������ʾģʽ
						Speed.Speed_Unit = 0;//��ʾ��������λ
						Param_Read();
					}	
					else
					{
						Speed.Speed_Mode = 1;//�����ٶ���ʾģʽ
						Speed.Speed_Unit = 1;//��ʾ�ٶȵĵ�λ
						Param_Read();
					}
					Beep_Time = 0.1;//��������0.1S
				}
				LongPress4 = 1;//������־��һ
			}
		}
	}
}

