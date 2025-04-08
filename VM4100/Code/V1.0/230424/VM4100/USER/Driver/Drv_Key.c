#include "Drv_Key.h"

/**********ȫ�ֱ�������******/
uint8_t Key_Status;//�������±�־

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
	static float T;
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
				if(sys.SetMode_Option == 1)//�������ٶ�ʱ
				{
					Set_Speed -= 100;//�ٶ�-100
					if(Set_Speed < 100)//�ٶ�С��100
						Set_Speed = 100;//�ٶ���СΪ100���²�ȥ��
					Beep_Time = 0.1;//��������0.1S
				}
				if(sys.SetMode_Option == 2)//������ʱ��ʱ
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
					Beep_Time = 0.1;//��������0.1S
				}
				Key_Status = 1;//����һ�룬��ʾ����ʱ��1s�ĵȴ�������˸
				Twinkle_Time = 6;//һ����˸6S
			}
			Key_Flag1 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt1 = 0;//��ť��������
		}
		if(Key_Cnt1 > 1.9 && Key_Cnt1 < 2.1)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(sys.SetMode_Option == 1)//�������ٶ�ʱ
			{
				Set_Speed -=500;//�ٶȼ�500
				if(Set_Speed < 100)//�ٶ�С��100
					Set_Speed = 100;//�ٶ���СΪ100���²�ȥ��
				Beep_Time = 0.1;//��������0.1S
			}
			if(sys.SetMode_Option == 2)//������ʱ��ʱ
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
				Beep_Time = 0.1;//��������0.1S
			}
			Key_Flag1 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt1 = 1.5;//��ť����
			Key_Status = 1;//����һ�룬��ʾ����ʱ��1s�ĵȴ�������˸
			Twinkle_Time = 6;//һ����˸6S
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
				if(sys.SetMode_Option == 1)//�������ٶ�ʱ
				{
					Set_Speed +=100;//�ٶ�+100
					if(Set_Speed > 3000)//�ٶȴ���3000ʱ
						Set_Speed = 3000;//�ٶ����Ϊ3000���ϲ�ȥ��
					Beep_Time = 0.1;//��������0.1S
				}
				if(sys.SetMode_Option == 2)//������ʱ��ʱ
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
					Beep_Time = 0.1;//��������0.1S
				}
				Key_Status = 1;//����һ�룬��ʾ����ʱ��1s�ĵȴ�������˸
				Twinkle_Time = 6;//һ����˸6S
			}
			Key_Flag2 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt2 = 0;//��ť��������		
		}
		if(Key_Cnt2 > 1.9 && Key_Cnt2 < 2.1)//����ʱ�����1.9SС��2.1S��ʾ����
		{
			if(sys.SetMode_Option == 1)//�������ٶ�ʱ
			{
				Set_Speed +=500;//�ٶȼ�500
				if(Set_Speed > 3000)//�ٶȴ���3000ʱ
					Set_Speed = 3000;//�ٶ����Ϊ3000���ϲ�ȥ��
				Beep_Time = 0.1;//��������0.1S
			}
			if(sys.SetMode_Option == 2)//������ʱ��ʱ
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
				Beep_Time = 0.1;//��������0.1S
			}
			Key_Status = 1;//����һ�룬��ʾ����ʱ��1s�ĵȴ�������˸
			Twinkle_Time = 6;//һ����˸6S
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
				if(sys.Run_Status == 1 && Start_Flag == 1)//ϵͳ�������Ұ���start���Ļ�
				{
					sys.Motor_Stop = 1;//�����
					Speed_ADDMode = 4;//�������ģʽ��
					Start_Flag = 0;//��������˿�ʼ����
					Beep_Time = 0.1;//��������0.1S
				}
				if(sys.Run_Status == 0 && Start_Flag == 0)//ϵͳû��������û����start���Ļ�
				{
					Speed_Val.SumError = 0xDD7D;//�������ϵ��
					SetOK_Flag = 1;//�趨��ֵ��־
					Ctrl_Time = Set_Time;//���趨ʱ�丳ֵ������ʱ��
					Param.Time = Set_Time;//ʱ��
					sys.Run_Status = 1;//����ϵͳ
					sys.SetMode_Option = 0;//����ѡ������
					Speed_ADDMode = 0;//���ݴ������¿�ʼ
					Start_Flag = 1;//�����˿�ʼ����
//					HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//����tim1ͨ��һ
					Beep_Time = 0.1;//��������0.1S
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
				
				LongPress3 = 1;//������־��һ
			}
		}
	}
	/**************************************MENU��**************************************/
	if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin )== 0)//���°���
	{
		if(sys.Motor_Stop)
			return;
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
			Key_Flag4 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress4 = 0;//������־����
			Key_Cnt4 = 0;//��ť��������		
		}
		if(Key_Cnt4 > 1.5 && Key_Cnt4 < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress4 == 0)//���û��һֱһֱ������
			{
				if(sys.Run_Status == 0)
				{
					if(Speed_Mode == 0)//�ڵ㶯ģʽ��
					{
						Speed_Mode = 1;//�򿪳���ģʽ
					}
					else//�ڵ㶯ģʽ��
					{
						Speed_Mode = 0;//�򿪵㶯ģʽ
					}
				}
				Beep_Time = 0.1;//��������0.1S
				LongPress4 = 1;//������־��һ
			}
		}
	}
	
	/**************************************T��**************************************/
	if(HAL_GPIO_ReadPin(KEY_T_GPIO_Port,KEY_T_Pin )== 0)//���°���
	{
		if(Speed_Mode == 1 || Start_Flag == 1 || DownTime_Over == 1)//����ڳ���ģʽ�²��Ұ�����start��������ʱ��������T��ʱ���ܻ��󴥷�������
			return;//����
		if(sys.Run_Status == 0)
		{
			Speed_Val.SumError = 0xDD7D;//�������ϵ��
			SetOK_Flag = 1;//�趨��ֵ��־
			sys.Run_Status = 1;//����ϵͳ
			sys.SetMode_Option = 0;//����ѡ������
			Speed_ADDMode = 0;//���ݴ������¿�ʼ
			Time_State = 1;//ʱ����ʾ��--��
			Beep_Flag = 1;//��ʾ���Խ����������
		}
		else
		{
			if(Beep_Flag == 1)//Ϊ������ʱ��һ��
			{
				Beep_Time = 0.1f;
				Beep_Flag = 0;
			}				
			if(sys.Motor_Stop == 1)
			{
				T = 0;//��������
				Time_State = 1;//ʱ����ʾ��--��
				sys.Motor_Stop = 0;//����Ѿ�ֹͣ
				Speed_ADDMode = 1;//���ݴ������¿�ʼ
			}
		}
	}
	if(HAL_GPIO_ReadPin(KEY_T_GPIO_Port,KEY_T_Pin )== 1)//�ſ�����
	{
		if(sys.Run_Status == 0)
			return;
		if((Speed_Mode == 1|| Start_Flag == 1) && Time_State == 0)
			return;
		T += dT;//���ǲ�����ſ���Ȼ���ʱ
		if(T > 0.5f)
		{
			sys.Motor_Stop = 1;//����Ѿ�ֹͣ
			Start_Flag = 0;//���¿�ʼ��������
			Speed_ADDMode = 4;//���ٴ���
			Beep_Flag = 1;//��ʾ���Խ����������
			T = 0;//��������
		}
	}
}

