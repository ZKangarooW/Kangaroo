#include "KEY.h"

/**********ȫ�ֱ���**********/
uint16_t run_mode = 0;//����ģʽ
uint8_t Key_Status;//�ڲ�������ʱ

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
                if(Param.Mode_Val)//��Bģʽ�£�����������ʱ
                {
                    Beep_Flash = 2;//��Ч����ʱ���������εΡ�
                }
                else
                {
                    if(Run_Status > 0) //�����в�������
                    {
                        Beep_Flash = 2;//��Ч����ʱ���������εΡ�
                    }
                    else
                    {
                        if(Select_Option == 2)//�������¶�ѡ��
                        {
                            set_temp--;//�¶�--��
                            if(set_temp < 0)//����趨�¶�С��0ʱ��������ֻ���Զ����£�
                            {
                                set_temp = 0;//���趨�¶ȱ�����0
                            }
                            Twinkle_On = 6000;//��˸����ʱ�����ֹͣ�������ã�6S��ֹͣ��˸
                            Key_Status = 2;//��������ʱ����˸��2s����˸
                        }
                        else if(Select_Option == 3)//������ʱ��ѡ��
                        {
                            if(time_status == 0)//���뵥λģʽ��
                            {
                                if(set_time)
                                    set_time -= 5;//ʱ���5s
                                if(set_time < 5)//С��5s���趨ֵʱ
                                {
                                    set_time = 0;
                                    time_Last = 1;//��������ʱ
                                    SetTime_State = 1;//�趨ʱ����ʾ��----��
                                }  				
                            }
                            else//�ڷ�Ϊ��λ��ģʽ��
                                set_time -= 60;//ʱ���1����
                            Twinkle_On = 6000;//��˸����ʱ�����ֹͣ�������ã�6S��ֹͣ��˸
                            Key_Status = 2;//��������ʱ����˸��2s����˸
                        }
                        else if(Select_Option == 1)//������ģʽѡ��
                        {
                            run_mode--;//P����λ��--
                            if(run_mode < 1)//С��1ʱ���ص��ھŸ�λ��
                            {
                                run_mode = 1;
                            }
                            Flash_Read((uint8_t *)(&Param),sizeof(Param));
                            set_time=Param.P_Param[run_mode][1];//���������趨ʱ��Ϊ20min
                            set_temp=Param.P_Param[run_mode][0];//���������趨�¶�37��
                            if(set_time > 0 )
                            {
                                SetTime_State = 0;//�趨ʱ���˳���ʾ��----��
                                time_Last = 0;
                            }
                            else
                            {
                                SetTime_State = 1;//�趨ʱ����ʾ��----��
                                time_Last = 1;
                            }
                            SetOK_Flag = 1;
                            Twinkle_On = 6000;//��˸����ʱ�����ֹͣ�������ã�6S��ֹͣ��˸
                            Key_Status = 2;//��������ʱ����˸��2s����˸
                        }
                        else
                        {
                            Beep_Flash = 2;//��Ч����ʱ���������εΡ�
                        }
                    }
                }
            }
            Key_Flag3 = 0; // �����¼��������ȴ���һ�ΰ���
            Key_Cnt3 = 0;  // ��ť��������
        }
        else if (Key_Cnt3 > 1.9f && Key_Cnt3 < 2.1f) // ����ʱ�����1.9SС��2.1S��ʾ����
        {
            if(Param.Mode_Val)//��Bģʽ�£�����������ʱ
            {
                Beep_Flash = 2;//��Ч����ʱ���������εΡ�
            }
            else
            {
                if(Run_Status > 0) //�����в�������
                {
                    Beep_Flash = 2;//��Ч����ʱ���������εΡ�
                }
                else
                {
                    if(Select_Option == 2)//�������¶�ѡ��
                    {
                        if (DownPress_Time > 5.0f)
                        {
                            set_temp -= 10;
                        }
                        else
                        {
                            set_temp--;
                        }
                        if(set_temp < 0)//����趨�¶�С��0ʱ��������ֻ���Զ����£�
                        {
                            set_temp = 0;//���趨�¶ȱ�����0
                        }
                        Twinkle_On = 6000;//��˸����ʱ�����ֹͣ�������ã�6S��ֹͣ��˸
                        Key_Status = 2;//��������ʱ����˸��2s����˸
                        if (DownPress_Time > 5.0f)
                        {
                            Key_Cnt3 = 1.82f; // ��������ʱ�临λ
                        }
                        else
                        {
                            Key_Cnt3 = 1.88f;
                        }
                    }
                    else if(Select_Option == 3)//������ʱ��ѡ��
                    {
                        if (DownPress_Time > 5.0f)
                        {
                            if(time_status == 0)//���뵥λģʽ��
                            {
                                if(set_time)
                                    set_time -= 60;//ʱ���5s
                                if(set_time < 5)//С��5s���趨ֵʱ
                                {
                                    set_time = 0;
                                    time_Last = 1;//��������ʱ
                                    SetTime_State = 1;//�趨ʱ����ʾ��----��
                                }   
                            }
                            else
                            {
                                if(set_time <  7200)
                                {
                                    if (set_time % 60)
                                        set_time = 3600;
                                    else
                                        set_time -= 600;
                                }
                                else
                                    set_time -= 600;
                            }
                        }
                        else
                        {
                            if(time_status == 0)//���뵥λģʽ��
                            {
                                if(set_time)
                                    set_time -= 5;//ʱ���5s
                                if(set_time < 5)//С��5s���趨ֵʱ
                                {
                                    set_time = 0;
                                    time_Last = 1;//��������ʱ
                                    SetTime_State = 1;//�趨ʱ����ʾ��----��
                                }   
                            }
                            else
                            {
                                if(set_time<  7200)
                                {
                                    if (set_time % 60)
                                        set_time = 3600;
                                    else
                                        set_time -= 60;
                                }
                                else
                                {
                                    set_time -= 60;
                                }
                            }
                        }
                        Twinkle_On = 6000;//��˸����ʱ�����ֹͣ�������ã�6S��ֹͣ��˸
                        Key_Status = 2;//��������ʱ����˸��2s����˸
                        if (DownPress_Time > 5.0f)
                        {
                            Key_Cnt3 = 1.82f; // ��������ʱ�临λ
                        }
                        else
                        {
                            Key_Cnt3 = 1.88f;
                        }
                    }
                    else if(Select_Option == 1)//������ģʽѡ��
                    {
                        run_mode--;//P����λ��--
                        if(run_mode < 1)//С��1ʱ���ص��ھŸ�λ��
                        {
                            run_mode = 1;
                        }
                        Flash_Read((uint8_t *)(&Param),sizeof(Param));
                        set_time=Param.P_Param[run_mode][1];//���������趨ʱ��Ϊ20min
                        set_temp=Param.P_Param[run_mode][0];//���������趨�¶�37��
                        if(set_time > 0 )
                        {
                            SetTime_State = 0;//�趨ʱ���˳���ʾ��----��
                            time_Last = 0;
                        }
                        else
                        {
                            SetTime_State = 1;//�趨ʱ����ʾ��----��
                            time_Last = 1;
                        }
                        SetOK_Flag = 1;
                        Twinkle_On = 6000;//��˸����ʱ�����ֹͣ�������ã�6S��ֹͣ��˸
                        Key_Status = 2;//��������ʱ����˸��2s����˸
                        Key_Cnt3 = 1.5f;
                    }
                    else
                    {
                        Beep_Flash = 2;//��Ч����ʱ���������εΡ�
                    }
                }
            }
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
                if(Param.Mode_Val)//��Bģʽ�£�����������ʱ
                {
                    Beep_Flash = 2;//��Ч����ʱ���������εΡ�
                }
                else
                {
                    if(Run_Status > 0) //�����в�������
                    {
                        Beep_Flash = 2;//��Ч����ʱ���������εΡ�
                    }
                    else
                    {
                        if(Select_Option == 2)//�������¶�ѡ��
                        {
                            set_temp++;//�¶�++��
                            if(set_temp > 1000)//����趨�¶���100��
                                set_temp = 1000;
                            Twinkle_On = 6000;//��˸����ʱ�����ֹͣ�������ã�6S��ֹͣ��˸
                            Key_Status = 2;//��������ʱ����˸��2s����˸
                        }
                        else if(Select_Option == 3)//������ʱ��ѡ��
                        {
                            if(time_status == 0)//���뵥λģʽ��
                            {
                                set_time += 5;//ʱ���5s
                                time_Last = 0;//���뵹��ʱ
                                SetTime_State = 0;//�趨ʱ���˳���ʾ��----��
                            }
                            else//�ڷֵ�λģʽ��
                                set_time += 60;//ʱ���60s
                            if(set_time > 86399)//��߿ɶ�ʱ23.59Сʱ
                                set_time = 86399;
                            Twinkle_On = 6000;//��˸����ʱ�����ֹͣ�������ã�6S��ֹͣ��˸
                            Key_Status = 2;//��������ʱ����˸��2s����˸
                        }
                        else if(Select_Option == 1)//������ģʽѡ��
                        {
                            run_mode++;//P����λ��++
                            if(run_mode > 9)//����9ʱ���ص���һ��λ��
                            {
                                run_mode = 9;
                            }
                            Flash_Read((uint8_t *)(&Param),sizeof(Param));
                            set_time=Param.P_Param[run_mode][1];//���������趨ʱ��Ϊ20min
                            set_temp=Param.P_Param[run_mode][0];//���������趨�¶�37��
                            if(set_time > 0 )
                            {
                                SetTime_State = 0;//�趨ʱ���˳���ʾ��----��
                                time_Last = 0;
                            }
                            else
                            {
                                SetTime_State = 1;//�趨ʱ����ʾ��----��
                                time_Last = 1;
                            }
                            SetOK_Flag = 1;
                            Twinkle_On = 6000;//��˸����ʱ�����ֹͣ�������ã�6S��ֹͣ��˸
                            Key_Status = 2;//��������ʱ����˸��2s����˸
                        }
                        else
                        {
                            Beep_Flash = 2;//��Ч����ʱ���������εΡ�
                        }
                    }
                }
            }
            Key_Flag2 = 0; // �����¼��������ȴ���һ�ΰ���
            Key_Cnt2 = 0;  // ��ť��������
        }
        else if (Key_Cnt2 > 1.9f && Key_Cnt2 < 2.1f) // ����ʱ�����1.9SС��2.1S��ʾ����
        {
            if(Param.Mode_Val)//��Bģʽ�£�����������ʱ
            {
                Beep_Flash = 2;//��Ч����ʱ���������εΡ�
            }
            else
            {
                if(Run_Status > 0) //�����в�������
                {
                    Beep_Flash = 2;//��Ч����ʱ���������εΡ�
                }
                else
                {
                    if(Select_Option == 2)//�������¶�ѡ��
                    {
                        if (UPPress_Time > 5.0f)
                        {
                            set_temp += 10;
                        }
                        else
                        {
                            set_temp++;//�¶�++��
                        }
                        if(set_temp > 1000)//����趨�¶���100��
                            set_temp = 1000;
                        Twinkle_On = 6000;//��˸����ʱ�����ֹͣ�������ã�6S��ֹͣ��˸
                        Key_Status = 2;//��������ʱ����˸��2s����˸
                        if (UPPress_Time > 5.0f)
                        {
                            Key_Cnt2 = 1.82f; // ��������ʱ�临λ
                        }
                        else
                        {
                            Key_Cnt2 = 1.88f;
                        }
                    }
                    else if(Select_Option == 3)//������ʱ��ѡ��
                    {
                        if (UPPress_Time > 5.0f)
                        {
                            if(time_status == 0)//���뵥λģʽ��
                            {
                                set_time += 60;//ʱ���60s
                                time_Last = 0;//���뵹��ʱ
                                SetTime_State = 0;//�趨ʱ���˳���ʾ��----��
                            }
                            else
                            {
                                if(set_time<  7200)
                                {
                                    if (set_time % 60)
                                        set_time = 3600;
                                    else
                                        set_time += 600;
                                }
                                else
                                {
                                    set_time += 600;
                                }
                            }
                        }
                        else
                        {
                            if(time_status == 0)//���뵥λģʽ��
                            {
                                set_time += 5;//ʱ���5s
                                time_Last = 0;//���뵹��ʱ
                                SetTime_State = 0;//�趨ʱ���˳���ʾ��----��
                            }
                            else
                            {
                                if(set_time<  7200)
                                {
                                    if (set_time % 60)
                                        set_time = 3600;
                                    else
                                        set_time += 60;
                                }
                                else
                                    set_time += 60;
                            }
                        }
                        if(set_time > 86399)//��߿ɶ�ʱ23.59Сʱ
                            set_time = 86399;
                        Twinkle_On = 6000;//��˸����ʱ�����ֹͣ�������ã�6S��ֹͣ��˸
                        Key_Status = 2;//��������ʱ����˸��2s����˸
                        if (UPPress_Time > 5.0f)
                        {
                            Key_Cnt2 = 1.82f; // ��������ʱ�临λ
                        }
                        else
                        {
                            Key_Cnt2 = 1.88f;
                        }
                    }
                    else if(Select_Option == 1)//������ģʽѡ��
                    {
                        run_mode++;//P����λ��++
                        if(run_mode > 9)//����9ʱ���ص���һ��λ��
                        {
                            run_mode = 9;
                        }
                        Flash_Read((uint8_t *)(&Param),sizeof(Param));
                        set_time=Param.P_Param[run_mode][1];//���������趨ʱ��Ϊ20min
                        set_temp=Param.P_Param[run_mode][0];//���������趨�¶�37��
                        if(set_time > 0 )
                        {
                            SetTime_State = 0;//�趨ʱ���˳���ʾ��----��
                            time_Last = 0;
                        }
                        else
                        {
                            SetTime_State = 1;//�趨ʱ����ʾ��----��
                            time_Last = 1;
                        }
                        SetOK_Flag = 1;
                        Twinkle_On = 6000;//��˸����ʱ�����ֹͣ�������ã�6S��ֹͣ��˸
                        Key_Status = 2;//��������ʱ����˸��2s����˸
                        Key_Cnt2 = 1.5f;
                    }
                    else
                    {
                        Beep_Flash = 2;//��Ч����ʱ���������εΡ�
                    }
                }
            }
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
                if(Param.Mode_Val)//��Bģʽ�£�����������ʱ
                {
                    Beep_Flash = 2;//��Ч����ʱ���������εΡ�
                }
                else
                {
                    if(Run_Status > 0) //�����в�������
                    {
                        Beep_Flash = 2;//��Ч����ʱ���������εΡ�
                    }
                    else
                    {
                        Select_Option++;//����ѡ���л�
                        if(Set_Mode_Enable == 0)
                        {
                            if(Select_Option == 1)//������pģʽ��һ��ֱ�ӽ����¶��趨
                            {
                                Select_Option = 2;
                            }
                            if(Select_Option > 3)//���¶Ⱥ�ʱ������ѡ��
                            {
                                Select_Option = 0;//����������    			
                            }
                            Twinkle_On = 6000;//��˸����ʱ�����ֹͣ�������ã�6S��ֹͣ��˸
                            Beep_Time = 0.1;//��������0.1S
                        }
                        else
                        {
                            if(Select_Option > 3)//���¶Ⱥ�ʱ���Pģʽ����ѡ��
                            {
                                Select_Option = 0;//����������    	
                            }
                            Twinkle_On = 6000;//��˸����ʱ�����ֹͣ�������ã�6S��ֹͣ��˸
                            Beep_Time = 0.1;//��������0.1S
                        }
                    }
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
                if(Param.Mode_Val && Run_Status && time_Last == 1)//��Bģʽ�£���������ϵͳ��
                {
                    time_Last = 0;
                    Beep_Time = 0.1;//��������0.1S
                }
                else
                {
                    if(Run_Status > 0) //�����в�������
                    {
                        Beep_Flash = 2;//��Ч����ʱ���������εΡ�
                    }
                    else if(Param.Mode_Val ) //�����в�������
                    {
                        Beep_Flash = 2;//��Ч����ʱ���������εΡ�
                    }
                    else
                    {
                        if(Set_Mode_Enable == 0)
                        {
                            Set_Mode_Enable = 1;//��ʾpģʽ�Ŀ�
                            Select_Option = 1;//�����趨p��λ��
                            run_mode = 1;
                            Flash_Read((uint8_t *)(&Param),sizeof(Param));
                            set_time=Param.P_Param[run_mode][1];//���������趨ʱ��Ϊ20min
                            set_temp=Param.P_Param[run_mode][0];//���������趨�¶�37��
                            if(set_time > 0 )
                            {
                                SetTime_State = 0;//�趨ʱ���˳���ʾ��----��
                                time_Last = 0;
                            }
                            else
                            {
                                SetTime_State = 1;//�趨ʱ����ʾ��----��
                                time_Last = 1;
                            }
                            SetOK_Flag = 1;	
                            Twinkle_On = 6000;//��˸����ʱ�����ֹͣ�������ã�6S��ֹͣ��˸
                            Beep_Time = 0.1;//��������0.1S
                        }
                        else
                        {
                            Set_Mode_Enable = 0;//����ʾPģʽ
                            run_mode_flag = 0;//����ʾPģʽ��
                            set_time=1200;//�˳�Pģʽ�����趨ʱ��Ϊ20min
                            rel_time=1200;//�˳�Pģʽ����ʵ��ʱ��Ϊ20min
                            set_temp=370;//�˳�Pģʽ�����趨�¶�37��
                            Select_Option = 0;//����˸����
                            run_mode = 0;
                            Flash_Read((uint8_t *)(&Param),sizeof(Param));
                            set_time=Param.P_Param[run_mode][1];//���������趨ʱ��Ϊ20min
                            set_temp=Param.P_Param[run_mode][0];//���������趨�¶�37��
                            SetOK_Flag = 1;
                            Beep_Time = 0.1;//��������0.1S
                        }
                    }
                }
			}
			Key_Flag5 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress5 = 0;//������־����
			Key_Cnt5 = 0;//��ť��������
		}
		if(Key_Cnt5 > 1.5 && Key_Cnt5 < 3.0)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress5 == 0)//���û��һֱһֱ������
			{
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
                if(Param.Mode_Val && Run_Status)//��Bģʽ�£�����������ʱ
                {
                    Beep_Flash = 2;//��Ч����ʱ���������εΡ�
                }
                else
                {
                    if(Run_Status == 0)//ϵͳû����
                    {
                        Select_Option = 0;//�趨ѡ������
                        Run_Status = 1; //ϵͳ����         
                        ADD_Mode = 0;//����״̬����
                        SetOK_Flag = 1;	
                    }
                    else
                    {
                        Run_Status = 0;//�ر�ϵͳ
                        ADD_Mode = 0;//����״̬����
                        SetOK_Flag = 1;
                    }
                    Beep_Time = 0.1;//��������0.1S
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
                if(Param.Mode_Val && time_Last == 1)//��Bģʽ�£�����û��������ʱ
                {
                    Param.Mode_Val = 0;
                    run_mode = 0;
                    SetOK_Flag = 1;
                    Save_Param_En = 1;
                    ADD_Mode = 0;//����״̬����
                    Run_Status = 0;//�ر�ϵͳ
                    time_Last = 0;
                    set_time=Param.P_Param[run_mode][1];//���������趨ʱ��Ϊ20min
                    set_temp=Param.P_Param[run_mode][0];//���������趨�¶�37��
                    Beep_Time = 0.1;//��������0.1S
                }
                else if(Param.Mode_Val == 0 && Run_Status == 0)//��Aģʽ�£�����û������ϵͳ
                {
                    Param.Mode_Val = 1;
                    run_mode = 10;
                    SetOK_Flag = 1;
                    Save_Param_En = 1;
                    ADD_Mode = 0;//����״̬����
                    Run_Status = 0;//�ر�ϵͳ
                    time_Last = 1;
                    Set_Mode_Enable = 0;//����ʾPģʽ
                    run_mode_flag = 0;//����ʾPģʽ��
                    Select_Option = 0;//����˸����
                    Twinkle_On = 0;
                    set_time=Param.P_Param[run_mode][1];//���������趨ʱ��Ϊ20min
                    set_temp=Param.P_Param[run_mode][0];//���������趨�¶�37��
                    Beep_Time = 0.1;//��������0.1S
                }
                else
                {
                    Beep_Flash = 2;//��Ч����ʱ���������εΡ�
                }
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
