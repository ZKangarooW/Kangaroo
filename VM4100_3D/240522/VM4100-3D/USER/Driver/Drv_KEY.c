#include "Drv_KEY.h"

#include "Drv_Key.h"

/**********ȫ�ֱ�������******/
uint8_t Key_Status;//�������±�־
uint8_t SetMode_Option;//ѡ������ģʽ

/**********�ֲ���������******/
float Key_Cnt1,Key_Cnt2,Key_Cnt3,Key_Cnt4;//����ʱ��
uint8_t Key_Flag1,Key_Flag2,Key_Flag3,Key_Flag4;//�������±�־
uint8_t LongPress1,LongPress2,LongPress3,LongPress4;//����������־

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
uint8_t Beep_Flag;//�㶯������flag
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
				if(SetMode_Option == 1)//�������ٶ�ʱ
				{
					Set_Speed -= 1;//�ٶ�-1
					if(Set_Speed < 10)//�ٶ�С��10
						Set_Speed = 10;//�ٶ���СΪ10���²�ȥ��
                    Key_Status = 1;//����һ�룬��ʾ����ʱ��1s�ĵȴ�������˸
                    Twinkle_Time = 6;//һ����˸6S
				}
				else if(SetMode_Option == 2)//������ʱ��ʱ
				{
					#if(Type == 1)
					if(Time_Unit)//��СʱΪ��λʱ
					{
						if(Set_Time == 3600)
							Set_Time -= 60;
						else
							Set_Time -= 3600;//ʱ���һСʱ
					}
					else//����Ϊ��λʱ
						Set_Time -= 60;//ÿ��ʱ���һ����
					if(Set_Time < 60)//ʱ��С��һ����
						Set_Time = 0;//����ʱ��Ϊ0
					#elif(Type == 0)
					if(Set_Time <= 60)//����Ϊ��λʱ
						Set_Time -= 1;//ʱ��--
					else//����Ϊ��λʱ
						Set_Time -= 60;//ÿ��ʱ���һ����
					if(Set_Time < 1)//ʱ��С��һ��ʱ
						Set_Time = 0;//����ʱ��Ϊ0
					#endif
                    Key_Status = 1;//����һ�룬��ʾ����ʱ��1s�ĵȴ�������˸
                    Twinkle_Time = 6;//һ����˸6S
				}
                else
				{
					Beep_Flash = 2;
				}
			}
			Key_Flag1 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt1 = 0;//��ť��������
		}
		if(Key_Cnt1 > 1.9 && Key_Cnt1 < 2.1)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(SetMode_Option == 1)//�������ٶ�ʱ
			{
				Set_Speed -=10;//�ٶȼ�10
				if(Set_Speed < 10)//�ٶ�С��10
					Set_Speed = 10;//�ٶ���СΪ10���²�ȥ��
                Key_Status = 1;//����һ�룬��ʾ����ʱ��1s�ĵȴ�������˸
                Twinkle_Time = 6;//һ����˸6S
			}
			else if(SetMode_Option == 2)//������ʱ��ʱ
			{
				#if(Type == 1)
				if(Time_Unit)//��СʱΪ��λʱ
				{
					if(Set_Time == 3600)
						Set_Time -= 60;
					else
						Set_Time -= 3600;//ʱ���һСʱ
				}
				else//СʱΪ��λʱ
					Set_Time -= 600;//ÿ��ʱ���ʮ����
				if(Set_Time < 60)//ʱ��С��һ��ʱ
					Set_Time = 0;//����ʱ��Ϊ0
				#elif(Type == 0)
				if(Time_Unit == 0)//����Ϊ��λʱ
					Set_Time -= 10;//ʱ���10S
				else//����Ϊ��λʱ
					Set_Time -= 600;//ÿ��ʱ���ʮ����
				if(Set_Time < 1)//ʱ��С��һ��ʱ
					Set_Time = 0;//����ʱ��Ϊ0
				#endif
                Key_Status = 1;//����һ�룬��ʾ����ʱ��1s�ĵȴ�������˸
                Twinkle_Time = 6;//һ����˸6S
			}
            else
			{
				Beep_Flash = 2;
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
				if(SetMode_Option == 1)//�������ٶ�ʱ
				{
					Set_Speed +=1;//�ٶ�+1
					if(Set_Speed > 80)//�ٶȴ���80ʱ
						Set_Speed = 80;//�ٶ����Ϊ80���ϲ�ȥ��
                    Key_Status = 1;//����һ�룬��ʾ����ʱ��1s�ĵȴ�������˸
                    Twinkle_Time = 6;//һ����˸6S
				}
				else if(SetMode_Option == 2)//������ʱ��ʱ
				{
					#if(Type == 1)
					if(Time_Unit)//СʱΪ��λʱ
						Set_Time += 3600;//����ʱ���1Сʱ
					else//�ڷ���Ϊ��λʱ
						Set_Time += 60;//����ʱ���1����
					if(Set_Time>28800)//ʱ�����8Сʱ
						Set_Time = 28800;//ʱ�����Ϊ8Сʱ
					#elif(Type == 0)
					if(Set_Time == 0)//����ʱ��Ϊ0ʱ
						Set_Time += 59;//��һ�뿪ʼ��
					if(Time_Unit == 0)//����Ϊ��λʱ
						Set_Time += 1;//����ʱ���1��
					else//����Ϊ��λʱ
						Set_Time += 60;//����ʱ���1����
					if(Set_Time>5940)//ʱ�����5940��ʱ��99���ӣ�
						Set_Time = 5940;//ʱ�����Ϊ99����
					#endif
                    Key_Status = 1;//����һ�룬��ʾ����ʱ��1s�ĵȴ�������˸
                    Twinkle_Time = 6;//һ����˸6S
				}
                else
                {
                    Beep_Flash = 2;
                }
			}
			Key_Flag2 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt2 = 0;//��ť��������		
		}
		if(Key_Cnt2 > 1.9 && Key_Cnt2 < 2.1)//����ʱ�����1.9SС��2.1S��ʾ����
		{
			if(SetMode_Option == 1)//�������ٶ�ʱ
			{
				Set_Speed +=10;//�ٶȼ�10
				if(Set_Speed > 80)//�ٶȴ���80ʱ
					Set_Speed = 80;//�ٶ����Ϊ80���ϲ�ȥ��
                Key_Status = 1;//����һ�룬��ʾ����ʱ��1s�ĵȴ�������˸
                Twinkle_Time = 6;//һ����˸6S
			}
			else if(SetMode_Option == 2)//������ʱ��ʱ
			{
				#if(Type == 1)
				if(Time_Unit)//СʱΪ��λʱ
					Set_Time += 3600;//����ʱ���1Сʱ
				else//�ڷ���Ϊ��λʱ
				{
					Set_Time += 600;//����ʱ���1����
					if(Set_Time > 3600)//����1Сʱ
						Set_Time = 3600;
				}
				if(Set_Time>28800)//ʱ�����8Сʱ
					Set_Time = 28800;//ʱ�����Ϊ8Сʱ
				#elif(Type == 0)
				if(Set_Time == 0)//����ʱ��Ϊ0ʱ
					Set_Time += 60;//��һ�뿪ʼ��
				if(Time_Unit == 0)//����Ϊ��λʱ
				{
					Set_Time += 10;//����ʱ���1����
					if(Set_Time > 60)
						Set_Time = 60;
				}
				else//����Ϊ��λʱ
					Set_Time += 600;//����ʱ���10����
				if(Set_Time>5940)//ʱ�����5940��ʱ��99���ӣ�
					Set_Time = 5940;//ʱ�����Ϊ99����
				#endif
                Key_Status = 1;//����һ�룬��ʾ����ʱ��1s�ĵȴ�������˸
                Twinkle_Time = 6;//һ����˸6S
			}
            else
			{
				Beep_Flash = 2;
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
				if(sys.Run_Status ==0)
				{
					sys.Run_Status = 1;
					Speed_ADDMode = 0;//��Ļ��ʾģʽ
					Speed_Val.SumError = 0x5800;//���������壬�ܵ�10rpm
					Speed_New=0;//���ڵ��ٶ�����
					Speed_Last = 0;//֮ǰ���ٶȵ��ڵ�ǰ��ʾ�ٶ�
				}
				else
				{
					sys.Run_Status = 0;
				}
				SetMode_Option = 0;
				Beep_Time = 0.1;//��������0.1S
			}
			Key_Flag3 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress3 = 0;//������־����
			Key_Cnt3 = 0;//��ť��������		
		}
		if(Key_Cnt3 > 1.5 && Key_Cnt3 < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress3 == 0)/*����*///���û��һֱһֱ������
			{
				Beep_Flash = 2;
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
				SetMode_Option++;
				if(SetMode_Option > 2)
				{
					SetMode_Option = 0;
					
				}
				Twinkle_Time = 6000;
				Beep_Time = 0.1;//��������0.1S
			}
			Key_Flag4 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress4 = 0;//������־����
			Key_Cnt4 = 0;//��ť��������		
		}
		if(Key_Cnt4 > 1.5 && Key_Cnt4 < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress4 == 0)//���û��һֱһֱ������
			{
                Beep_Flash = 2;
				LongPress4 = 1;//������־��һ
			}
		}
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_Key(void)
 * ��    �ܣ���ⰴ��״̬-1s
*****************************************************************
*/
void Check_Key(void)
{
    if(Key_Status)
        Key_Status--;
}
