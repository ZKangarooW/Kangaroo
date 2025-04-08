#include "Drv_KEY.h"

/**********ȫ�ֱ���**********/
float Key_Status;//�ڲ�������ʱ

/**********�ֲ���������******/
float Key_Cnt1,Key_Cnt2,Key_Cnt3,Key_Cnt4,Key_Cnt5;//����ʱ��
uint8_t Key_Flag1,Key_Flag2,Key_Flag3,Key_Flag4,Key_Flag5;//�������±�־
uint8_t LongPress1,LongPress2,LongPress3,LongPress4,LongPress5;//����������־

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_Press(float dT)
 * ��    �ܣ���ⰴ��״̬-1s
*****************************************************************
*/
void Check_Press(float dT)
{
    if(Key_Status)
        Key_Status -= dT;
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
	if(!Key1)//���°���
	{
		if(sys.Run_Status == 1)
			return;
		if(LongPress1 == 0)//û�г�����
		{
			Key_Cnt1 += dT;//����ʱ��++
			Key_Flag1 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag1)//����������
	{
		if(Key1)//̧�𰴼�
		{   
			if(Key_Cnt1 > 0.05f && Key_Cnt1 < 1.5)//����ʱ�����0.05SС��1.5S�ǵ���
			{
				sys.SetMode_Option++;
                if(PMode.Show_Circle)
                {
                    if(sys.SetMode_Option > 3)
                    {
                        sys.SetMode_Option = 0;
                    }
                    Twinkle_Time = 6.0f;
                    Key_Status = 0;
                    Beep_Time = 0.1;
                }
                else
                {
                    if(sys.SetMode_Option > 2)
                    {
                        sys.SetMode_Option = 0;
                    }
                    Twinkle_Time = 6.0f;
                    Key_Status = 0;
                    Beep_Time = 0.1;
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
				
				LongPress1 = 1;//������־��һ
			}
		}
	}

	/**************************************�Ӽ�**************************************/
	if(!Key2)//���°���
	{
		if(sys.Run_Status == 1)
			return;
		Key_Cnt2 += dT;//����ʱ��++
		Key_Flag2 = 1;//�������±�־��һ
	}
	if(Key_Flag2 == 1)//����������
	{
		if(Key2)//̧�𰴼�
		{   
			if(Key_Cnt2 < 1.5)//С��1.5S�ǵ���
			{
				if(sys.SetMode_Option == 1)
                {
                    Temp.Set++;
                    if(Temp.Set > Temp_MAX)
                    {
                        Temp.Set = Temp_MAX;
                    }
                }
                else if(sys.SetMode_Option == 2)
                {
                    if(Time.Set < 3600)
                        Time.Set += 5;
                    else
                        Time.Set += 60;
                    if(Time.Set > Time_MAX)
                    {
                        Time.Set = Time_MAX;
                    }
                }
                else if(sys.SetMode_Option == 3)
                {
                    PMode.Option ++;
                    if(PMode.Option > 9)
                    {
                        PMode.Option = 1;
                    }
                    Param_Read();
                }
                Key_Status = 2.0f;
                Twinkle_Time = 6.0f;
			}
			Key_Flag2 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt2 = 0;//��ť��������		
		}
		if(Key_Cnt2 > 1.9 && Key_Cnt2 < 2.1)//����ʱ�����1.9SС��2.1S��ʾ����
		{
			if(sys.SetMode_Option == 1)
            {
                Temp.Set += 1;
                if(Temp.Set > Temp_MAX)
                {
                    Temp.Set = Temp_MAX;
                }
				if(Temp.Set % 10 == 0)
				{
					Key_Cnt2 = 1.8;//��ť��������
				}
				else
				{
					Key_Cnt2 = 1.88f;//��ť��������
				}
            }
            else if(sys.SetMode_Option == 2)
            {
                if(Time.Set < 3600)
                {
                    Time.Set += 5;
                    if(Time.Set>3600)
                        Time.Set = 3600;
					if(Time.Set % 60 == 0)
					{
						Key_Cnt2 = 1.84f;//��ť��������
					}
					else
					{
						Key_Cnt2 = 1.88f;//��ť��������
					}
                }
                else
				{
                    Time.Set += 300;
					if(Time.Set % 600 == 0)
					{
						Key_Cnt2 = 1.84f;//��ť��������
					}
					else
					{
						Key_Cnt2 = 1.88f;//��ť��������
					}
				}
                if(Time.Set > Time_MAX)
                {
                    Time.Set = Time_MAX;
                }
            }
            else if(sys.SetMode_Option == 3)
            {
                PMode.Option ++;
                if(PMode.Option > 9)
                {
                    PMode.Option = 1;
                }
				Key_Cnt2 = 1.66;//��ť��������
            }
            Key_Status = 2.0f;
            Twinkle_Time = 6.0f;
			Key_Flag2 = 0;//�����¼��������ȴ���һ�ΰ���
		}
	}
	else
		Key_Cnt2 = 0;//��ť��������

	/**************************************����**************************************/
	if(!Key3)//���°���
	{
		if(sys.Run_Status == 1)
			return;
		Key_Cnt3 += dT;//����ʱ��++
		Key_Flag3 = 1;//�������±�־��һ
	}
	if(Key_Flag3 == 1)//����������
	{
		if(Key3)//̧�𰴼�
		{   
			if(Key_Cnt3 < 1.5)//����ʱ�����0.05SС��1.5S�ǵ���
			{
				if(sys.SetMode_Option == 1)
                {
                    Temp.Set--;
                    if(Temp.Set < Temp_MIN)
                    {
                        Temp.Set = Temp_MIN;
                    }
                }
                else if(sys.SetMode_Option == 2)
                {
                    if(Time.Set < 3600)
                        Time.Set -= 5;
                    else
                    {
                        Time.Set -= 60;
                        if(Time.Set < 3600)
                            Time.Set = 3595;
                    }
                    if(Time.Set < Time_MIN)
                    {
                        Time.Set = Time_MIN;
                    }
                }
                else if(sys.SetMode_Option == 3)
                {
                    PMode.Option --;
                    if(PMode.Option < 1)
                    {
                        PMode.Option = 9;
                    }
                    Param_Read();
                }
                Key_Status = 2.0f;
                Twinkle_Time = 6.0f;
			}
			Key_Flag3 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt3 = 0;//��ť��������		
		}
		else if(Key_Cnt3 > 1.9 && Key_Cnt3 < 2.1)//����ʱ�����1.9SС��2.1S��ʾ����
		{
			if(sys.SetMode_Option == 1)
            {
                Temp.Set -= 1;
                if(Temp.Set < Temp_MIN)
                {
                    Temp.Set = Temp_MIN;
                }
				if(Temp.Set % 10 == 0)
				{
					Key_Cnt3 = 1.8;//��ť��������
				}
				else
				{
					Key_Cnt3 = 1.88f;//��ť��������
				}
            }
            else if(sys.SetMode_Option == 2)
            {
                if(Time.Set < 3600)
                {
                    Time.Set -= 5;
					if(Time.Set % 60 == 0)
					{
						Key_Cnt3 = 1.84f;//��ť��������
					}
					else
					{
						Key_Cnt3 = 1.88f;//��ť��������
					}
                }
                else
                {
                    Time.Set -= 300;
                    if(Time.Set < 3600)
                        Time.Set = 3540;
					if(Time.Set % 600 == 0)
					{
						Key_Cnt3 = 1.84f;//��ť��������
					}
					else
					{
						Key_Cnt3 = 1.88f;//��ť��������
					}
                }
                if(Time.Set < Time_MIN)
                {
                    Time.Set = Time_MIN;
                }
            }
            else if(sys.SetMode_Option == 3)
            {
                PMode.Option --;
                if(PMode.Option < 1)
                {
                    PMode.Option = 9;
                }
				Key_Cnt3 = 1.66;//��ť��������
            }
            Key_Status = 2.0f;
            Twinkle_Time = 6.0f;
			Key_Flag3 = 0;//�����¼��������ȴ���һ�ΰ���
		}
	} 
	else
		Key_Cnt3 = 0;//��ť��������

	/**************************************Start��**************************************/
	if(!Key4)//���°���
	{
		if(LongPress4 == 0)//û�г�����
		{
			Key_Cnt4 += dT;//����ʱ��++
			Key_Flag4 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag4)//����������
	{
		if(Key4)//̧�𰴼�
		{   
			if(Key_Cnt4 > 0.05f && Key_Cnt4 < 1.5)//����ʱ�����0.05SС��1.5S�ǵ���
			{
				if(sys.Run_Status != 1)
                {
                    sys.Run_Status = 1;//ϵͳ����
					sys.SetMode_Option = 0;//�������
                    Temp_Val.Integral = 40;//��ʼ��5��֮һ���ʼ���
                    SetOK_Flag = 1;//�ٶ����ã�ʱ������
                    Twinkle_Time = Key_Status =0;//��˸ʱ������
					Temp.Last_Set = Temp.Set;//��¼�趨ֵ
					Temp.Last_Mode = 0;//��¼�ر�ʱ����ʾģʽ
                    Beep_Time = 0.1;//��������0.1S
                }
                else
                {
                    sys.Run_Status = 2;//ϵͳ�ر�
					Temp.Last_Mode = Temp.ADDMode;//��¼�ر�ʱ����ʾģʽ
					Temp.ADD_Wait_Count = 0;//���������ʱ��
					SetOK_Flag = 1;//�ٶ����ã�ʱ������
                    Beep_Time = 0.1;//��������0.1S
                    Temp.ADDMode = 0;//������ʾģʽ����
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

				LongPress4 = 1;//������־��һ
			}
		}
	}
	/**************************************P��******************************************/
	if(!Key5)//���°���
	{
		if(sys.Run_Status == 1)
			return;
		if(LongPress5 == 0)//û�г�����
		{
			Key_Cnt5 += dT;//����ʱ��++
			Key_Flag5 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag5)//����������
	{
		if(Key5)//̧�𰴼�
		{   
			if(Key_Cnt5 > 0.05f && Key_Cnt5 < 1.5)//����ʱ�����0.05SС��1.5S�ǵ���
			{
				if(PMode.Show_Circle == 0)
				{
					PMode.Show_Circle = 1;//��ʾ����P-��ģʽ
					PMode.Option = 1;//����ģʽ1
					Param_Read();//��ȡ����
					SetOK_Flag = 1;//���ò���
					sys.SetMode_Option = 3;//��������Pֵģʽ
					Twinkle_Time = 6;//��˸ʱ��6S
				}
				else
				{
					PMode.Show_Circle = 0;//����ʾ����P-��ģʽ
					PMode.Option = 0;//����ģʽ0
					Param_Read();//��ȡ����
					sys.SetMode_Option = 0;//ģʽ����
					SetOK_Flag = 1;//���ò���
				}
				Beep_Time = 0.1;//��������0.1S
            }
			Key_Flag5 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress5 = 0;//������־����
			Key_Cnt5 = 0;//��ť��������
		}
		if(Key_Cnt5 > 1.5 && Key_Cnt5 < 3.0)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress5 == 0)//���û��һֱһֱ������
			{
				
				LongPress5 = 1;//������־��һ
			}
		}
	}
}
