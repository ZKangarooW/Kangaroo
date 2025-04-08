#include "Drv_KEY.h"

#if (Key_Type == 0)

/**********ȫ�ֱ�������******/
float Key_Status;//�������±�־

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
	/************************************MENU��**************************************/
	if(KEY1 == KEY_DOWN)//���°���
	{
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
				if(sys.Run_Status == 1)
				{
					Beep_Flash = 2;//��Ч�������������������εΡ�
				}
				else
				{
					sys.SetMode_Option++;
					if(sys.SetMode_Option > 3)
						sys.SetMode_Option = 0;
					Beep_Time = 0.1;//��������0.1S
					Twinkle_Time = 6;//��˸ʱ��6S
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
				Beep_Flash = 2;//��Ч�������������������εΡ�
				LongPress1 = 1;//������־��һ
			}
		}
	}
	/**************************************�Ӽ�**************************************/
	if(KEY2== KEY_DOWN)//���°���
	{
		Key_Cnt2 += dT;//����ʱ��++
		Key_Flag2 = 1;//�������±�־��һ
	}
	if(Key_Flag2 == 1)//����������
	{
		if(KEY2 == KEY_UP)//̧�𰴼�
		{   
			if(Key_Cnt2 < 1.4)//С��1.5S�ǵ���
			{
				if(sys.SetMode_Option == 1)//�����¶�
				{
					Temp.Set += 10;//�¶ȼ�1��
					if(Temp.Set > Temp_MAX)//�����¶ȴ���Temp_MAX��ʱ
						Temp.Set = Temp_MAX;//�¶ȵ���Temp_MAX��
					Key_Status = 2;//����ʱ2S����˸
					Twinkle_Time = 6;//��˸ʱ��6S
				}
				else if(sys.SetMode_Option == 2)//�����ٶ�
				{
					Speed.Set += 10;//ת�ټ�10ת
					if(Speed.Set == 10)//����ת��ʼ���Ϊ50ת���ж���10��
						Speed.Set = 50;//�趨ת��Ϊ50��ʼ
					if(Speed.Set > Speed_MAX)//����ת�ٴ���Speed_MAX
						Speed.Set = Speed_MAX;//ת�ٵ���Speed_MAX
					Key_Status = 2;//����ʱ2S����˸
					Twinkle_Time = 6;//��˸ʱ��6S
				}
				else if(sys.SetMode_Option == 3)//����ʱ��
				{
					Time.Set += 60;//ʱ���1����
					if(Time.Set > Time_MAX)//����ʱ�����Time_MAXʱ
						Time.Set = Time_MAX;//ʱ�����Time_MAX
					Key_Status = 2;//����ʱ2S����˸
					Twinkle_Time = 6;//��˸ʱ��6S
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
			if(sys.SetMode_Option == 1)//�����¶�
			{
				Temp.Set += 100;//�¶ȼ�10��
				if(Temp.Set > Temp_MAX)//�����¶ȴ���Temp_MAX��ʱ
					Temp.Set = Temp_MAX;//�¶ȵ���Temp_MAX��
				Key_Status = 2;//����ʱ2S����˸
				Twinkle_Time = 6;//��˸ʱ��6S
			}
			else if(sys.SetMode_Option == 2)//�����ٶ�
			{
				Speed.Set += 100;//ת�ټ�100ת
				if(Speed.Set > Speed_MAX)//����ת�ٴ���Speed_MAX
					Speed.Set = Speed_MAX;//ת�ٵ���Speed_MAX
				Key_Status = 2;//����ʱ2S����˸
				Twinkle_Time = 6;//��˸ʱ��6S
			}
			else if(sys.SetMode_Option == 3)//����ʱ��
			{
				Time.Set += 600;//ʱ���10����
				if(Time.Set > Time_MAX)//����ʱ�����Time_MAXʱ
					Time.Set = Time_MAX;//ʱ�����Time_MAX
				Key_Status = 2;//����ʱ2S����˸
				Twinkle_Time = 6;//��˸ʱ��6S
			}
			else
			{
				Beep_Flash = 2;//��Ч�������������������εΡ�
			}
			Key_Flag2 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt2 = 1.4;//��ť������1.4s��ʼ
		}
	}
	
	/**************************************����**************************************/
	if(KEY3 == KEY_DOWN)//���°���
	{
		Key_Cnt3 += dT;//����ʱ��++
		Key_Flag3 = 1;//�������±�־��һ
	}
	if(Key_Flag3 == 1)//����������
	{
		if(KEY3 == KEY_UP)//̧�𰴼�
		{   
			if(Key_Cnt3 < 1.4)/*����*///С��1.5S�ǵ���
			{
				if(sys.SetMode_Option == 1)//�����¶�
				{
					Temp.Set -= 10;//�¶ȼ�1��
					if(Temp.Set < 0)//�����¶�С��0��ʱ
						Temp.Set = 0;//�¶ȵ���0��
					Key_Status = 2;//����ʱ2S����˸
					Twinkle_Time = 6;//��˸ʱ��6S
				}
				else if(sys.SetMode_Option == 2)//�����ٶ�
				{
					Speed.Set -= 10;//ת�ټ�10ת
					if(Speed.Set < 50)//����ת��С��50ʱ
						Speed.Set = 0;//ת�ٵ���0
					Key_Status = 2;//����ʱ2S����˸
					Twinkle_Time = 6;//��˸ʱ��6S
				}
				else if(sys.SetMode_Option == 3)//����ʱ��
				{
					Time.Set -= 60;//ʱ���1����
					if(Time.Set < 0)//����ʱ��С��0ʱ
						Time.Set = 0;//ʱ�����0
					Key_Status = 2;//����ʱ2S����˸
					Twinkle_Time = 6;//��˸ʱ��6S
				}
				else
				{
					Beep_Flash = 2;//��Ч�������������������εΡ�
				}
			}
			Key_Flag3 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt3 = 0;//��ť��������		
		}
		if(Key_Cnt3 > 1.9 && Key_Cnt3 < 2.1)//����ʱ�����1.9SС��2.1S��ʾ����
		{
			if(sys.SetMode_Option == 1)//�����¶�
			{
				Temp.Set -= 100;//�¶ȼ�10��
				if(Temp.Set < 0)//�����¶�С��0��ʱ
					Temp.Set = 0;//�¶ȵ���0��
				Key_Status = 2;//����ʱ2S����˸
				Twinkle_Time = 6;//��˸ʱ��6S
			}
			else if(sys.SetMode_Option == 2)//�����ٶ�
			{
				Speed.Set -= 100;//ת�ټ�100ת
				if(Speed.Set < 50)//����ת��С��50ʱ
					Speed.Set = 0;//ת�ٵ���0
				Key_Status = 2;//����ʱ2S����˸
				Twinkle_Time = 6;//��˸ʱ��6S
			}
			else if(sys.SetMode_Option == 3)//����ʱ��
			{
				Time.Set -= 600;//ʱ���10����
				if(Time.Set < 0)//����ʱ��С��0ʱ
					Time.Set = 0;//ʱ�����0
				Key_Status = 2;//����ʱ2S����˸
				Twinkle_Time = 6;//��˸ʱ��6S
			}
			else
			{
				Beep_Flash = 2;//��Ч�������������������εΡ�
			}
			Key_Flag3 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt3 = 1.4;//��ť������1.5s��ʼ	
		}
	}
	
	/**************************************Start��**************************************/
	if(KEY4== KEY_DOWN)//���°���
	{	
		if(LongPress4 == 0)//û�г�����
		{
			Key_Cnt4 += dT;//����ʱ��++
			Key_Flag4 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag4 == 1)//����������
	{
		if(KEY4 == KEY_UP)//̧�𰴼�
		{   
			if(Key_Cnt4 > 0.1 && Key_Cnt4 < 1.5)//С��1.5S�ǵ���
			{
				if(sys.Run_Status != 1 && (Speed.Set || Temp.Set))//ϵͳû�����Ļ�
				{
					sys.Run_Status = 1;//����ϵͳ
					Speed_Val.Integral = 43;//������
					sys.SetMode_Option = 0;//�趨ģʽ����Ϊ0
					Temp_Val.Integral = 0;//���ȵĻ�������
				}
				else//ϵͳ�����Ļ�
				{
					Speed.ADDMode = 1;//�������ģʽ
					Speed.Ctrl = 0;//�������ٶ�����Ϊ0
				}
				Beep_Time = 0.1;//��������0.1S
				Twinkle_Time = 0;//��˸ʱ��6S
				sys.SetMode_Option = 0;
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
#endif
