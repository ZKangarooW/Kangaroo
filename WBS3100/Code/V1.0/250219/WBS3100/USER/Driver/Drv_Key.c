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
 * ��    �ܣ�����ɨ��
*****************************************************************
*/
void Key_Scan(float dT)
{
	/**************************************MENU��**************************************/
	if(Key1 == Key_Down)//���°���
	{
		if(Protect)
		{
			return;
		}
		if(LongPress1 == 0)//û�г�����
		{
			Key_Cnt1 += dT;//����ʱ��++
			Key_Flag1 = 1;//�������±�־��һ
		}
	}
	
	if(Key_Flag1)//����������
	{
		if(Key1 == Key_Up)//̧�𰴼�
		{   
			if(Key_Cnt1 > 0.05f && Key_Cnt1 < 1.5)//����ʱ�����0.05SС��1.5S�ǵ���
			{
                if(sys.Run_Status == 0 && Speed.Display_Rel != 0)
                {
                    Beep_Flash = 2;//��Ч����ʱ���������εΡ�
                }
                else
                {
                    #if(Type == 0)
                    sys.SetMode_Option++;
                    if(sys.SetMode_Option > 2)
                        sys.SetMode_Option = 0;
                    #elif(Type == 1)
                    sys.SetMode_Option++;
                    if(sys.SetMode_Option > 3)
                        sys.SetMode_Option = 0;
                    #endif
                    Twinkle_Time = 6.0f;//��˸ʱ��6S
                    Beep_Time = 0.1;//��������0.1S
                }
			}
			Key_Flag1 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress1 = 0;//������־����
			Key_Cnt1 = 0;//��ť��������
		}
		if(Key_Cnt1 > 1.5 && Key_Cnt1 < 3.0)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress1 == 0)//���û��һֱһֱ������
			{
                Beep_Flash = 2;//��Ч����ʱ���������εΡ�
				LongPress1 = 1;//������־��һ
			}
		}
	}
				
	/**************************************�Ӽ�**************************************/
	if(Key2 == Key_Down)//���°���
	{
		if(Protect)
		{
			return;
		}
		Key_Cnt2 += dT;//����ʱ��++
		Key_Flag2 = 1;//�������±�־��һ
	}
	if(Key_Flag2 == 1)//����������
	{
		if(Key2 == Key_Up)//̧�𰴼�
		{   
			if(Key_Cnt2 > 0.05f && Key_Cnt2 < 1.5)//����ʱ�����0.05SС��1.5S�ǵ���
			{
				if(sys.SetMode_Option == 1)
				{
					Temp.Set += 10;//�¶ȼ�1��
					if(Temp.Set > Temp_MAX)//�������Temp_MAX��
						Temp.Set = Temp_MAX;//�趨�¶�ΪTemp_MAX��
					Key_Status = 2.0f;//����ʱ����2S
					Twinkle_Time = 6.0f;//��˸ʱ��6S
				}
				else if(sys.SetMode_Option == 2)
				{
					#if(Type == 0)
					Time.Set += 60;//ʱ���1����
					if(Time.Set > Time_MAX)//���ʱ�����Time_Max
						Time.Set = Time_MAX;//�趨ʱ�����Time_Max
					Key_Status = 2.0f;//����ʱ����2S
					Twinkle_Time = 6.0f;//��˸ʱ��6S
					#elif(Type == 1)
					if(!Speed.Set)
						Speed.Set += 100;//�ٶȼ�100
					else
						Speed.Set += 50;//�ٶȼ�50
					if(Speed.Set > Speed_MAX)//����ٶȴ���Speed_MAX
						Speed.Set = Speed_MAX;//�趨�ٶȵ���Speed_MAX
					Key_Status = 2.0f;//����ʱ����2S
					Twinkle_Time = 6.0f;//��˸ʱ��6S
					#endif
				}
				else if(sys.SetMode_Option == 3)
				{
					Time.Set += 60;//ʱ���1����
					if(Time.Set > Time_MAX)//���ʱ�����Time_Max
						Time.Set = Time_MAX;//�趨ʱ�����Time_Max
					Key_Status = 2.0f;//����ʱ����2S
					Twinkle_Time = 6.0f;//��˸ʱ��6S
				}
                else
                {
                    Beep_Flash = 2;//��Ч����ʱ���������εΡ�
                }
			}
			Key_Flag2 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt2 = 0;//��ť��������		
		}
		if(Key_Cnt2 > 1.9 && Key_Cnt2 < 2.1)//����ʱ�����1.9SС��2.1S��ʾ����
		{
			if(sys.SetMode_Option == 1)
			{
				Temp.Set += 100;//�¶ȼ�10��
				if(Temp.Set > Temp_MAX)//�������Temp_MAX��
					Temp.Set = Temp_MAX;//�趨�¶�ΪTemp_MAX��
				Key_Status = 2.0f;//����ʱ����2S
				Twinkle_Time = 6.0f;//��˸ʱ��6S
			}
			else if(sys.SetMode_Option == 2)
			{
				#if(Type == 0)
				Time.Set += 1800;//ʱ���30����
				if(Time.Set > Time_MAX)//���ʱ�����Time_Max
					Time.Set = Time_MAX;//�趨ʱ�����Time_Max
				Key_Status = 2.0f;//����ʱ����2S
				Twinkle_Time = 6.0f;//��˸ʱ��6S
				#elif(Type == 1)
				Speed.Set += 100;//�ٶȼ�100
				if(Speed.Set > Speed_MAX)//����ٶȴ���Speed_MAX
					Speed.Set = Speed_MAX;//�趨�ٶȵ���Speed_MAX
				Key_Status = 2.0f;//����ʱ����2S
				Twinkle_Time = 6.0f;//��˸ʱ��6S
				#endif
			}
			else if(sys.SetMode_Option == 3)
			{
				Time.Set += 1800;//ʱ���30����
				if(Time.Set > Time_MAX)//���ʱ�����Time_Max
					Time.Set = Time_MAX;//�趨ʱ�����Time_Max
				Key_Status = 2.0f;//����ʱ����2S
				Twinkle_Time = 6.0f;//��˸ʱ��6S
			}
            else
            {
                Beep_Flash = 2;//��Ч����ʱ���������εΡ�
            }
			Key_Flag2 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt2 = 1.5;//��ť��������
		}
	}

	/**************************************����**************************************/
	if(Key3 == Key_Down)//���°���
	{
		if(Protect)
		{
			return;
		}
		Key_Cnt3 += dT;//����ʱ��++
		Key_Flag3 = 1;//�������±�־��һ
	}
	if(Key_Flag3 == 1)//����������
	{
		if(Key3 == Key_Up)//̧�𰴼�
		{   
			if(Key_Cnt3 > 0.05f && Key_Cnt3 < 1.5)//����ʱ�����0.05SС��1.5S�ǵ���
			{
				if(sys.SetMode_Option == 1)
				{
					if(Temp.Set)
						Temp.Set -= 10;//�¶ȼ�1��
					if(Temp.Set <= Temp_MIN)//���С�ڵ���Temp_MIN��
						Temp.Set = Temp_MIN;//�趨�¶�ΪTemp_MIN��
					Key_Status = 2.0f;//����ʱ����2S
					Twinkle_Time = 6.0f;//��˸ʱ��6S
				}
				else if(sys.SetMode_Option == 2)
				{
					#if(Type == 0)
					if(Time.Set)
						Time.Set -= 60;//ʱ���1����
					if(Time.Set <= Time_MIN)//���ʱ��С�ڵ���Time_MIN
						Time.Set = Time_MIN;//�趨ʱ�����Time_MIN
					Key_Status = 2.0f;//����ʱ����2S
					Twinkle_Time = 6.0f;//��˸ʱ��6S
					#elif(Type == 1)
					if(Speed.Set)
						Speed.Set -= 50;//�ٶȼ�50
					if(Speed.Set < Speed_MIN)//����ٶ�С��Speed_MIN
						Speed.Set = 0;//�趨�ٶȵ���0
					Key_Status = 2.0f;//����ʱ����2S
					Twinkle_Time = 6.0f;//��˸ʱ��6S
					#endif
				}
				else if(sys.SetMode_Option == 3)
				{
					if(Time.Set)
						Time.Set -= 60;//ʱ���1����
					if(Time.Set <= Time_MIN)//���ʱ��С�ڵ���Time_MIN
						Time.Set = Time_MIN;//�趨ʱ�����Time_MIN
					Key_Status = 2.0f;//����ʱ����2S
					Twinkle_Time = 6.0f;//��˸ʱ��6S
				}
                else
                {
                    Beep_Flash = 2;//��Ч����ʱ���������εΡ�
                }
			}
			Key_Flag3 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt3 = 0;//��ť��������		
		}
		if(Key_Cnt3 > 1.9 && Key_Cnt3 < 2.1)//����ʱ�����1.9SС��2.1S��ʾ����
		{
			if(sys.SetMode_Option == 1)
			{
				if(Temp.Set>100)//�¶ȴ���100
					Temp.Set -= 100;//�¶ȼ�10��
				else if(Temp.Set > 0 && Temp.Set<=100)
					Temp.Set -= 10;//�¶ȼ�1��
				if(Temp.Set <= Temp_MIN)//���С�ڵ���Temp_MIN��
					Temp.Set = Temp_MIN;//�趨�¶�ΪTemp_MIN��
				Key_Status = 2.0f;//����ʱ����2S
				Twinkle_Time = 6.0f;//��˸ʱ��6S
			}
			else if(sys.SetMode_Option == 2)
			{
				#if(Type == 0)
				if(Time.Set>1800)
					Time.Set -= 1800;//ʱ���30����
				else if(Time.Set > 600 && Time.Set <= 1800)
					Time.Set -= 600;//ʱ���10����
				else if(Time.Set >= 60 && Time.Set <= 600)
					Time.Set -= 60;//ʱ���1����
				if(Time.Set <= Time_MIN)//���ʱ��С�ڵ���Time_MIN
					Time.Set = Time_MIN;//�趨ʱ�����Time_MIN
				Key_Status = 2.0f;//����ʱ����2S
				Twinkle_Time = 6.0f;//��˸ʱ��6S
				#elif(Type == 1)
				if(Speed.Set > 100)
					Speed.Set -= 100;//�ٶȼ�100
				else if(Speed.Set > 50 && Speed.Set <= 100)
					Speed.Set -= 50;//�ٶȼ�50
				if(Speed.Set < Speed_MIN)//����ٶ�С��Speed_MIN
					Speed.Set = 0;//�趨�ٶȵ���0
				Key_Status = 2.0f;//����ʱ����2S
				Twinkle_Time = 6.0f;//��˸ʱ��6S
				#endif
			}
			else if(sys.SetMode_Option == 3)
			{
				if(Time.Set>1800)
					Time.Set -= 1800;//ʱ���30����
				else if(Time.Set > 600 && Time.Set <= 1800)
					Time.Set -= 600;//ʱ���10����
				else if(Time.Set >= 60 && Time.Set <= 600)
					Time.Set -= 60;//ʱ���1����
				if(Time.Set <= Time_MIN)//���ʱ��С�ڵ���Time_MIN
					Time.Set = Time_MIN;//�趨ʱ�����Time_MIN
				Key_Status = 2.0f;//����ʱ����2S
				Twinkle_Time = 6.0f;//��˸ʱ��6S
			}
            else
            {
                Beep_Flash = 2;//��Ч����ʱ���������εΡ�
            }
			Key_Flag3 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt3 = 1.5;//��ť��������
		}
	} 

	/**************************************Start��**************************************/
	if(Key4 == Key_Down)//���°���
	{
		if(Protect)
		{
			return;
		}
		if(LongPress4 == 0)//û�г�����
		{
			Key_Cnt4 += dT;//����ʱ��++
			Key_Flag4 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag4)//����������
	{
		if(Key4 == Key_Up)//̧�𰴼�
		{   
			if(Key_Cnt4 > 0.05f && Key_Cnt4 < 1.5)//����ʱ�����0.05SС��1.5S�ǵ���
			{
				if(sys.Run_Status)
				{
					sys.Run_Status = 0;
					Speed.DisplayMode = 2;//������ʾ
                    sys.SetMode_Option = 0;
                    SetOK_Flag = 1;
					Beep_Time = 0.1;//��������0.1S
				}
				else
				{
					if(Speed.Set || Temp.Set)//���3�����ܶ���������������ϵͳ
					{
						sys.Run_Status = 1;
						Speed_Val.Integral = 25;
						Judge_TempMode();//�¶���ʾģʽ���
						Judge_SpeedMode();//�ٶ���ʾģʽ���
						sys.SetMode_Option = 0;
                        SetOK_Flag = 1;
						Beep_Time = 0.1;//��������0.1S
					}
				}
			}
			Key_Flag4 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress4 = 0;//������־����
			Key_Cnt4 = 0;//��ť��������
		}
		if(Key_Cnt4 > 1.5 && Key_Cnt4 < 3.0)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress4 == 0)//���û��һֱһֱ������
			{
                Beep_Flash = 2;//��Ч����ʱ���������εΡ�
				LongPress4 = 1;//������־��һ
			}
		}
	}
}

