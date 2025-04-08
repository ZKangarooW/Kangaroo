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
	/**************************************Start��**************************************/
	if(KEY3 == 0)//���°���
	{
		if(LongPress1 == 0)//û�г�����
		{
			Key_Cnt1 += dT;//����ʱ��++
			Key_Flag1 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag1 == 1)//����������
	{
		if(KEY3 == 1)//̧�𰴼�
		{   
			if(Key_Cnt1 < 1.5)//С��1.5S�ǵ���
			{
				if(sys.Run_Status == 0)//ϵͳû�������Ļ�
				{
					Speed_Val.SumError = 0x06B2;//�������ϵ��
					SetOK_Flag = 1;//�趨��ֵ��־
					Ctrl_Time = Set_Time;//���趨ʱ�丳ֵ������ʱ��
					Param.Time = Set_Time;//ʱ��
					sys.Run_Status = 1;//����ϵͳ
					sys.SetMode_Option = 0;//����ѡ������
					Speed_ADDMode = 0;//���ݴ������¿�ʼ
				}
				else//ϵͳ�����Ļ�
				{
					sys.Motor_Stop = 1;//�����
					Speed_ADDMode = 4;//�������ģʽ��
				}
				Beep_Time = 0.1;//��������0.1S
			}
			Key_Flag1 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress1 = 0;//������־����
			Key_Cnt1 = 0;//��ť��������
		}
		if(Key_Cnt1 > 1.5 && Key_Cnt1 < 3.0)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress1 == 0)/*����*///���û��һֱһֱ������
			{
				Beep_Flash = 2;//��Ч�������������������εΡ�
				LongPress1 = 1;//������־��һ
			}			
		}
	}
	/**************************************�Ӽ�**************************************/
	if(KEY2== 0)//���°���
	{
		Key_Cnt2 += dT;//����ʱ��++
		Key_Flag2 = 1;//�������±�־��һ
	}
	if(Key_Flag2 == 1)//����������
	{
		if(KEY2 == 1)//̧�𰴼�
		{   
			if(Key_Cnt2 < 1.5)//С��1.5S�ǵ���
			{
				if(sys.SetMode_Option == 1)//�������ٶ�ʱ
				{
					Set_Speed +=1;//�ٶ�++
					if(Set_Speed > 80)//�ٶȴ���80ʱ
						Set_Speed = 80;//�ٶ����Ϊ80���ϲ�ȥ��
					Key_Status = 1;//����һ�룬��ʾ����ʱ��1s�ĵȴ�������˸
					Twinkle_Time = 6;//һ����˸6S
				}
				else if(sys.SetMode_Option == 2)//������ʱ��ʱ
				{
					Set_Time += 60;//����ʱ���1����
					if(Set_Time>86399)//ʱ�����23Сʱ59��
						Set_Time = 86399;//ʱ�����Ϊ23Сʱ59��
					Key_Status = 1;//����һ�룬��ʾ����ʱ��1s�ĵȴ�������˸
					Twinkle_Time = 6;//һ����˸6S
				}
				else
				{
					Beep_Flash = 2;//��Ч�������������������εΡ�
				}
			}
			Key_Flag2 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt2 = 0;//��ť��������		
		}
		if(Key_Cnt2 > 1.9 && Key_Cnt2 < 2.1)//����ʱ�����1.9SС��2.1S��ʾ����
		{
			if(sys.SetMode_Option == 1)//�������ٶ�ʱ
			{
				Set_Speed +=10;//�ٶȼ�10
				if(Set_Speed > 80)//�ٶȴ���80ʱ
					Set_Speed = 80;//�ٶ����Ϊ80���ϲ�ȥ��
				Key_Status = 1;//����һ�룬��ʾ����ʱ��1s�ĵȴ�������˸
				Twinkle_Time = 6;//һ����˸6S
			}
			else if(sys.SetMode_Option == 2)//������ʱ��ʱ
			{
				Set_Time += 600;//����ʱ���10����
				if(Set_Time>86399)//ʱ�����23Сʱ59��
					Set_Time = 86399;//ʱ�����Ϊ23Сʱ59��
				Key_Status = 1;//����һ�룬��ʾ����ʱ��1s�ĵȴ�������˸
				Twinkle_Time = 6;//һ����˸6S
			}
			else
			{
				Beep_Flash = 2;//��Ч�������������������εΡ�
			}
			Key_Flag2 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt2 = 1.5;//��ť����
		}
	}

	/**************************************����**************************************/
	if(KEY4 == 0)//���°���
	{
		Key_Cnt3 += dT;//����ʱ��++
		Key_Flag3 = 1;//�������±�־��һ
	}
	if(Key_Flag3 == 1)//����������
	{
		if(KEY4 == 1)//̧�𰴼�
		{   
			if(Key_Cnt3 < 1.5)/*����*///С��1.5S�ǵ���
			{
				if(sys.SetMode_Option == 1)//�������ٶ�ʱ
				{
					Set_Speed -=1;//�ٶ�--
					if(Set_Speed < 20)//�ٶ�С��20
						Set_Speed = 20;//�ٶ���СΪ20���²�ȥ��
					Key_Status = 1;//����һ�룬��ʾ����ʱ��1s�ĵȴ�������˸
					Twinkle_Time = 6;//һ����˸6S
				}
				else if(sys.SetMode_Option == 2)//������ʱ��ʱ
				{
					Set_Time -= 60;//ÿ��ʱ���һ����
					if(Set_Time < 60)//ʱ��С��һ��ʱ
						Set_Time = 0;//����ʱ��Ϊ0
					Key_Status = 1;//����һ�룬��ʾ����ʱ��1s�ĵȴ�������˸
					Twinkle_Time = 6;//һ����˸6S
				}
				else
				{
					Beep_Flash = 2;//��Ч�������������������εΡ�
				}	
			}
			Key_Flag3 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt3 = 0;//��ť��������		
		}
		if(Key_Cnt3 > 1.9 && Key_Cnt3 < 2.1)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(sys.SetMode_Option == 1)//�������ٶ�ʱ
			{
				Set_Speed -=10;//�ٶȼ�10
				if(Set_Speed < 20)//�ٶ�С��20
					Set_Speed = 20;//�ٶ���СΪ20���²�ȥ��
				Key_Status = 1;//����һ�룬��ʾ����ʱ��1s�ĵȴ�������˸
				Twinkle_Time = 6;//һ����˸6S
			}
			else if(sys.SetMode_Option == 2)//������ʱ��ʱ
			{
				Set_Time -= 600;//ÿ��ʱ���ʮ����
				if(Set_Time < 60)//ʱ��С��һ��ʱ
					Set_Time = 0;//����ʱ��Ϊ0
				Key_Status = 1;//����һ�룬��ʾ����ʱ��1s�ĵȴ�������˸
				Twinkle_Time = 6;//һ����˸6S
			}
			else
			{
				Beep_Flash = 2;//��Ч�������������������εΡ�
			}
			Key_Flag3 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt3 = 1.5;//��ť����
		}
	}
	/**************************************MENU��**************************************/
	if(KEY1 == 0)//���°���
	{
		if(LongPress4 == 0)//û�г�����
		{
			Key_Cnt4 += dT;//����ʱ��++
			Key_Flag4 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag4 == 1)//����������
	{
		if(KEY1 == 1)//̧�𰴼�
		{   
			if(Key_Cnt4 < 1.5)//С��1.5S�ǵ���
			{
				if(sys.Motor_Stop)
				{
					Beep_Flash = 2;//��Ч�������������������εΡ�
				}
				else
				{
					sys.SetMode_Option++;//����ѡ��++
                    if(sys.SetMode_Option > 2)//����ѡ�����2
                    {
                        sys.SetMode_Option = 0;//����ѡ������
                        SetOK_Flag = 1;
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
				Beep_Flash = 2;//��Ч�������������������εΡ�
				LongPress4 = 1;//������־��һ
			}
		}
	}
}
