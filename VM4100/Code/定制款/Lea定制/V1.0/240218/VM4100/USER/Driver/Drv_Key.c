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
void Key_Scan(float dT)
{
	/**************************************L��**************************************/
	if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin) == 0)//���°���
	{
		if(sys.Run_Status)
			return;
		Key_Cnt1 += dT;//����ʱ��++
		Key_Flag1 = 1;//�������±�־��һ
	}
	if(Key_Flag1 == 1)//����������
	{
		if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin) == 1)//̧�𰴼�
		{   
			if(Key_Cnt1 < 1.5)//С��1.5S�ǵ���
			{
				if(sys.SetMode_Option)
				{
					if(sys.SetMode_Option == 1 || sys.SetMode_Option == 3)
					{
						Set_Speed -= 100;//�ٶ�-100
						if(Set_Speed < 100)//�ٶ�С��100
							Set_Speed = 100;//�ٶ���СΪ100���²�ȥ��
					}
					else if(sys.SetMode_Option == 2 || sys.SetMode_Option == 4)
					{
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
					}
				}
				else
				{
					Speed_Mode = 1;//Lģʽ
					SetOK_Flag = 1;//��������
					Beep_Time = 0.1;
				}
			}
			Key_Flag1 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt1 = 0;//��ť��������
		}
		if(Key_Cnt1 > 5.0 && Key_Cnt1 < 5.2)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(sys.SetMode_Option)
			{
				Key_Flag1 = 0;//�����¼��������ȴ���һ�ΰ���
				Key_Cnt1 = 1.5;//��ť����
				return;
			}
			
			Speed_Mode = 1;//Lģʽ
			SetOK_Flag = 1;//��������
			sys.SetMode_Option = 1;//�����趨ģʽ
			Beep_Time = 0.1;
			Key_Flag1 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt1 = 1.5;//��ť����
		}
	}
	/**************************************S��**************************************/
	if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)== 0)//���°���
	{
		if(sys.Run_Status)
			return;
		Key_Cnt2 += dT;//����ʱ��++
		Key_Flag2 = 1;//�������±�־��һ
	}
	if(Key_Flag2 == 1)//����������
	{
		if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) == 1)//̧�𰴼�
		{   
			if(Key_Cnt2 < 1.5)//С��1.5S�ǵ���
			{
				if(sys.SetMode_Option)
				{
					if(sys.SetMode_Option == 1 || sys.SetMode_Option == 3)
					{
						Set_Speed +=100;//�ٶ�+100
						if(Set_Speed > 2000)//�ٶȴ���2000ʱ
							Set_Speed = 2000;//�ٶ����Ϊ2000���ϲ�ȥ��
					}
					else if(sys.SetMode_Option == 2 || sys.SetMode_Option == 4)
					{
						if(Time_Unit)//СʱΪ��λʱ
							Set_Time += 3600;//����ʱ���1Сʱ
						else//�ڷ���Ϊ��λʱ
							Set_Time += 60;//����ʱ���1����
						if(Set_Time>28800)//ʱ�����8Сʱ
							Set_Time = 28800;//ʱ�����Ϊ8Сʱ
					}
				}
				else
				{
					Speed_Mode = 0;//Sģʽ
					SetOK_Flag = 1;//��������
					Beep_Time = 0.1;
				}
			}
			Key_Flag2 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt2 = 0;//��ť��������		
		}
		if(Key_Cnt2 > 5.0 && Key_Cnt2 < 5.2)//����ʱ�����1.9SС��2.1S��ʾ����
		{
			if(sys.SetMode_Option)
			{
				Key_Flag2 = 0;//�����¼��������ȴ���һ�ΰ���
				Key_Cnt2 = 1.5;//��ť����
				return;
			}
			Speed_Mode = 0;//Sģʽ
			SetOK_Flag = 1;//��������
			sys.SetMode_Option = 1;//�����趨ģʽ
			Beep_Time = 0.1;
			Key_Flag2 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt2 = 1.5;//��ť����
		}
	}
	/**************************************Stop��**************************************/
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
				if(sys.SetMode_Option)
				{
					sys.SetMode_Option++;
					SetOK_Flag = 1;//��������
				}
				else
				{
					if(sys.Run_Status == 1)//ϵͳ����
					{
						sys.Motor_Stop = 1;//�����
						Speed_ADDMode = 4;//�������ģʽ��
						sys.Run_Step = 0;
						Set_Speed = Param.Speed[Speed_Mode][sys.Run_Step];
						Set_Time = Param.Speed[Speed_Mode][sys.Run_Step];
					}
				}
				Beep_Time = 0.1;
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
	/**************************************Start��**************************************/
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
				if(sys.SetMode_Option)
				{
					Beep_Flash = 5;//��������5��
				}
				else
				{
					if(sys.Run_Status == 0)//ϵͳû������
					{
						Speed_Val.SumError = 0xDD7D;//�������ϵ��
						SetOK_Flag = 1;//�趨��ֵ��־
						Ctrl_Speed = Set_Speed;//���趨�ٶȸ�ֵ�������ٶ�
						Ctrl_Time = Set_Time;//���趨ʱ�丳ֵ������ʱ��
						sys.Run_Status = 1;//����ϵͳ
						sys.SetMode_Option = 0;//����ѡ������
						Speed_ADDMode = 0;//���ݴ������¿�ʼ
					}	
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
				
				LongPress4 = 1;//������־��һ
			}
		}
	}
}

