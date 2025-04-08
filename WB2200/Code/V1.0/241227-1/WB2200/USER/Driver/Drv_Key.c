#include "Drv_Key.h"

/**********ȫ�ֱ�������******/
float Key_Status;// �ڲ���������ʱ��

/**********�ֲ���������******/
float Key_Cnt1,Key_Cnt2,Key_Cnt3,Key_Cnt4;//����ʱ��
uint8_t Key_Flag1,Key_Flag2,Key_Flag3,Key_Flag4;//�������±�־
uint8_t LongPress1,LongPress2,LongPress3,LongPress4;//����������־
float UPPress_Time, DownPress_Time;// ������ʱ��

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_LongPress(float dT)
 * ��    �ܣ���ⳤ��
*****************************************************************
*/
void Check_LongPress(float dT)
{
    if(UPPress_Time>3.0f && DownPress_Time>3.0f)//��������
    {
        if(sys.SetMode_Option==0)
        {
            sys.DownTime_Mode = 1;
            TM1640_Clr();
        }
        else
        {
            sys.DownTime_Mode = 0;
            TM1640_Clr();
        }
        Beep_Time = 0.1;
        UPPress_Time = 0;
        DownPress_Time = 0;
    }
}

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
    if(Key_Status<=0)
        Key_Status = 0;
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
        if(sys.DownTime_Mode)
            return;
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
			if(Key_Cnt1 > 0.05f && Key_Cnt1 < 1.5f)//����ʱ�����0.05SС��1.5S�ǵ���
			{
                sys.SetMode_Option++;
                if(sys.SetMode_Option > 2)
                    sys.SetMode_Option = 0;
                Twinkle_Time = 6.0f;//��˸ʱ��6S
				Beep_Time = 0.1;
			}
			Key_Flag1 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress1 = 0;//������־����
			Key_Cnt1 = 0;//��ť��������
		}
		if(Key_Cnt1 > 1.5f && Key_Cnt1 < 3.0f)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress1 == 0)//���û��һֱһֱ������
			{
                Beep_Flash = 2;//��Ч����ʱ���������εΡ�
				LongPress1 = 1;//������־��һ
			}
		}
	}
				
	/**************************************����**************************************/
	if(Key2 == Key_Down)//���°���
	{
        DownPress_Time += dT;
		Key_Cnt2 += dT;//����ʱ��++
		Key_Flag2 = 1;//�������±�־��һ
	}
	if(Key_Flag2)//����������
	{
		if(Key2 == Key_Up)//̧�𰴼�
		{   
			if(Key_Cnt2 > 0.05f && Key_Cnt2 < 1.5f)//����ʱ�����0.05SС��1.5S�ǵ���
			{
                if(sys.DownTime_Mode)
                {
                    sys.DownTime_Type = C1;
                    Param.DownTime_Type = sys.DownTime_Type;//����ʱ���͸�ֵ��Flash��
                    Save_Param_En = 1;
                }
                else if(sys.SetMode_Option == 1)
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
			Key_Flag2 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt2 = 0;//��ť��������		
		}
		if(Key_Cnt2 > 1.9f && Key_Cnt2 < 2.1f)//����ʱ�����1.9SС��2.1S��ʾ����
		{
			if(sys.SetMode_Option == 1)
			{
				if (DownPress_Time > 5.0f)
                {
                    Temp.Set -= 50;
                }
                else
                {
                    Temp.Set -= 10;
                }
				if(Temp.Set <= Temp_MIN)//���С�ڵ���Temp_MIN��
					Temp.Set = Temp_MIN;//�趨�¶�ΪTemp_MIN��
				Key_Status = 2.0f;//����ʱ����2S
				Twinkle_Time = 6.0f;//��˸ʱ��6S
			}
			else if(sys.SetMode_Option == 2)
			{
				if (DownPress_Time > 5.0f)
                {
                    Time.Set -= 600;
                }
                else
                {
                    Time.Set -= 60;
                }
				if(Time.Set <= Time_MIN)//���ʱ��С�ڵ���Time_MIN
					Time.Set = Time_MIN;//�趨ʱ�����Time_MIN
				Key_Status = 2.0f;//����ʱ����2S
				Twinkle_Time = 6.0f;//��˸ʱ��6S
            }
            else if(UPPress_Time == 0)
            {
                Beep_Flash = 2;//��Ч����ʱ���������εΡ�
            }
			Key_Flag2 = 0;//�����¼��������ȴ���һ�ΰ���
			if (DownPress_Time > 5.0f)
            {
                Key_Cnt2 = 1.82f; // ��������ʱ�临λ
            }
            else
            {
                Key_Cnt2 = 1.88f;
            }
		}
	}
    else
    {
        DownPress_Time = 0;
        Key_Cnt2 = 0; // ������������
    }
    
	/**************************************�Ӽ�**************************************/
	if(Key3 == Key_Down)//���°���
	{
        UPPress_Time += dT; // ����ʱ��Ӽ�
		Key_Cnt3 += dT;//����ʱ��++
		Key_Flag3 = 1;//�������±�־��һ
	}
	if(Key_Flag3)//����������
	{
		if(Key3 == Key_Up)//̧�𰴼�
		{   
			if(Key_Cnt3 > 0.05f && Key_Cnt3 < 1.5f)//����ʱ�����0.05SС��1.5S�ǵ���
			{
                if(sys.DownTime_Mode)
                {
                    sys.DownTime_Type = C2;
                    Param.DownTime_Type = sys.DownTime_Type;//����ʱ���͸�ֵ��Flash��
                    Save_Param_En = 1;
                }
                else if(sys.SetMode_Option == 1)
				{
					Temp.Set += 10;//�¶ȼ�1��
					if(Temp.Set > Temp_MAX)//�������Temp_MAX��
						Temp.Set = Temp_MAX;//�趨�¶�ΪTemp_MAX��
					Key_Status = 2.0f;//����ʱ����2S
					Twinkle_Time = 6.0f;//��˸ʱ��6S
				}
				else if(sys.SetMode_Option == 2)
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
			Key_Flag3 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt3 = 0;//��ť��������		
		}
		if(Key_Cnt3 > 1.9f && Key_Cnt3 < 2.1f)//����ʱ�����1.9SС��2.1S��ʾ����
		{
			if(sys.SetMode_Option == 1)
			{
				if (UPPress_Time > 5.0f)
                {
                    Temp.Set += 50;
                }
                else
                {
                    Temp.Set += 10;
                }
				if(Temp.Set > Temp_MAX)//�������Temp_MAX��
					Temp.Set = Temp_MAX;//�趨�¶�ΪTemp_MAX��
				Key_Status = 2.0f;//����ʱ����2S
				Twinkle_Time = 6.0f;//��˸ʱ��6S
			}
			else if(sys.SetMode_Option == 2)
			{
				if (UPPress_Time > 5.0f)
                {
                    Time.Set += 600;
                }
                else
                {
                    Time.Set += 60;
                }
				if(Time.Set > Time_MAX)//���ʱ�����Time_Max
					Time.Set = Time_MAX;//�趨ʱ�����Time_Max
				Key_Status = 2.0f;//����ʱ����2S
				Twinkle_Time = 6.0f;//��˸ʱ��6S
            }
            else if(UPPress_Time == 0)
            {
                Beep_Flash = 2;//��Ч����ʱ���������εΡ�
            }
			Key_Flag3 = 0;//�����¼��������ȴ���һ�ΰ���
			if (UPPress_Time > 5.0f)
            {
                Key_Cnt3 = 1.82f; // ��������ʱ�临λ
            }
            else
            {
                Key_Cnt3 = 1.88f;
            }
		}
	} 
    else
    {
        UPPress_Time = 0;
        Key_Cnt3 = 0; // ������������
    }
    
	/**************************************Start��**************************************/
	if(Key4 == Key_Down)//���°���
	{
        if(sys.DownTime_Mode)
            return;
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
			if(Key_Cnt4 > 0.05f && Key_Cnt4 < 1.5f)//����ʱ�����0.05SС��1.5S�ǵ���
			{
                if(sys.Run_Status)
                {
                    sys.Run_Status = 0;
                    sys.SetMode_Option = 0;
                    Temp.ADDMode = 0;
                    SetOK_Flag = 1;
                }
                else
                {
                    sys.Run_Status = 1;
                    sys.SetMode_Option = 0;
                    Temp.ADDMode = 0;
                    SetOK_Flag = 1;
                }
                Beep_Time = 0.1;
			}
			Key_Flag4 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress4 = 0;//������־����
			Key_Cnt4 = 0;//��ť��������
		}
		if(Key_Cnt4 > 1.5f && Key_Cnt4 < 3.0f)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress4 == 0)//���û��һֱһֱ������
			{
                Beep_Flash = 2;//��Ч����ʱ���������εΡ�
				LongPress4 = 1;//������־��һ
			}
		}
	}
}

