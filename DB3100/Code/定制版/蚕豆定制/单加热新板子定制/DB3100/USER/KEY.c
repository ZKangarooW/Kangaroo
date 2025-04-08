#include "KEY.h"

/**********ȫ�ֱ���**********/
uint16_t run_mode = 0;//����ģʽ
uint16_t Key_Status;//�ڲ�������ʱ

/**********�ֲ�����**********/
float Key_Cnt1,Key_Cnt2,Key_Cnt3,Key_Cnt4,Key_Cnt5;//����ʱ��
uint8_t Key_Flag1,Key_Flag2,Key_Flag3,Key_Flag4,Key_Flag5;//�������±�־
uint8_t LongPress1,LongPress2,LongPress3,LongPress4,LongPress5;//����������־
float UPPress_Time, DownPress_Time;//������ʱ��

/*
*****************************************************************
 * ����ԭ�ͣ� void Key_Handle(float dT)
 * ��    �ܣ� ��������
*****************************************************************
*/
void Key_Handle(float dT)
{
    /**************************************����**************************************/
    if(!Key3)//���°���
    {
        DownPress_Time += dT;
        Key_Cnt3 += dT; // ����ʱ��++
        Key_Flag3 = 1;  // �������±�־��һ
    }
    if (Key_Flag3 == 1) // ����������
    {
        if(Key3)//̧�𰴼�
        {
            if (Key_Cnt3 < 1.5f) // ����ʱ��С��1.5S�ǵ���
            {
				if(set_time >= 600)
                    set_time -= 600;//ʱ���10����
                rel_time = set_time;//���趨ʱ�丳ֵ������ʱ��
                time_disable = 0;//��������ʱ
                Beep_Time = 0.1;//��������0.1S
                Key_Status = Run_Time;
            }
            Key_Flag3 = 0; // �����¼��������ȴ���һ�ΰ���
            Key_Cnt3 = 0;  // ��ť��������
        }
        else if (Key_Cnt3 > 1.9f && Key_Cnt3 < 2.1f) // ����ʱ�����1.9SС��2.1S��ʾ����
        {
            if(set_time >= 600)
                set_time -= 600;//ʱ���10����
            rel_time = set_time;//���趨ʱ�丳ֵ������ʱ��
            time_disable = 0;//��������ʱ
            Key_Status = Run_Time;
            Key_Cnt3 = 1.88f;
            Key_Flag3 = 0; // �����¼��������ȴ���һ�ΰ���
        }
    }
    else
    {
        DownPress_Time = 0;
        Key_Cnt3 = 0; // ������������
    }
   
    /******************************�Ӽ�******************************/
    if(!Key2)//���°���
    {
        UPPress_Time += dT; // ����ʱ��Ӽ�
        Key_Cnt2 += dT;     // ����ʱ��++
        Key_Flag2 = 1;      // �������±�־��һ
    }
    if (Key_Flag2) // ����������
    {
        if(Key2)//̧�𰴼�
        {
            if (Key_Cnt2 < 1.5f) // ����ʱ��С��1.5S�ǵ���
            {
                set_time += 600;//ʱ���10����
                if(set_time > 28800)//��߿ɶ�ʱ8Сʱ
                    set_time = 28800;
                rel_time = set_time;//���趨ʱ�丳ֵ������ʱ��
                time_disable = 0;//��������ʱ
                Key_Status = Run_Time;
                Beep_Time = 0.1;//��������0.1S
            }
            Key_Flag2 = 0; // �����¼��������ȴ���һ�ΰ���
            Key_Cnt2 = 0;  // ��ť��������
        }
        else if (Key_Cnt2 > 1.9f && Key_Cnt2 < 2.1f) // ����ʱ�����1.9SС��2.1S��ʾ����
        {
            set_time += 600;//ʱ���10����
                if(set_time > 28800)//��߿ɶ�ʱ8Сʱ
                    set_time = 28800;
            rel_time = set_time;//���趨ʱ�丳ֵ������ʱ��
                time_disable = 0;//��������ʱ
            Key_Cnt2 = 1.88f;
            Key_Status = Run_Time;
            Key_Flag2 = 0; // �����¼��������ȴ���һ�ΰ���
        }
    }
    else
    {
        UPPress_Time = 0;
        Key_Cnt2 = 0; // ������������
    }
    
    /*****************************�˵���*************************************/ 
    if(!Key1)//���°���
	{
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
                set_temp=990;//���������趨�¶�65��
                SetOK_Flag = 1;
                Run_Status = 1; //ϵͳ����         
                ADD_Mode = 0;//����״̬����
                Key_Status = Run_Time;
                Beep_Time = 0.1;//��������0.1S
			}
			Key_Flag1 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress1 = 0;//������־����
			Key_Cnt1 = 0;//��ť��������
		}
		if(Key_Cnt1 > 1.5 && Key_Cnt1 < 3.0)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress1 == 0)//���û��һֱһֱ������
			{
                Key_Status = Run_Time;
				Beep_Flash = 2;//��Ч����ʱ���������εΡ�
				LongPress1 = 1;//������־��һ
			}
		}
	}

/*******************************P��*************************************/ 
    if(!Key5)//���°���
	{
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
                set_temp=650;//���������趨�¶�65��
                SetOK_Flag = 1;
                Key_Status = Run_Time;
                Run_Status = 1; //ϵͳ����         
                ADD_Mode = 0;//����״̬����
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
                Key_Status = Run_Time;
				Beep_Flash = 2;//��Ч����ʱ���������εΡ�
				LongPress5 = 1;//������־��һ
			}
		}
	}    

    
/******************************��ʼ/ֹͣ********************************/  
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
                Key_Status = Run_Time;
                if(set_time)
                {
                    rel_time = set_time;//���趨ʱ�丳ֵ������ʱ��
                    if(time_disable)
                    {
                        time_disable = 0;//�رյ���ʱ
                    }
                    else
                    {
                        time_disable = 1;//��������ʱ
                    }
                }
                else
                    time_disable = 0;//��������ʱ
                Beep_Time = 0.1;//��������0.1S
			}
			Key_Flag4 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress4 = 0;//������־����
			Key_Cnt4 = 0;//��ť��������
		}
		if(Key_Cnt4 > 1.5 && Key_Cnt4 < 3.0)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress4 == 0)//���û��һֱһֱ������
			{
                Key_Status = Run_Time;
                Beep_Flash = 2;//��Ч����ʱ���������εΡ�
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
    if(Run_Status)
    {
        if(Key_Status)
            Key_Status--;
        if(Key_Status == 0)
        {
            set_time=0;//���������趨ʱ��Ϊ0
            set_temp=0;//���������趨�¶�0��
            Run_Status = 0;
            time_disable = 0;//�رյ���ʱ
            Key_Status = Run_Time;
            ADD_Mode = 0;
            Beep_Flash = 30;//��Ч����ʱ���������εΡ�
            SetOK_Flag = 1;
        }
    }
        
}
