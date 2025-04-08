#include "Drv_KEY.h"

/**********�ֲ���������******/
float Key_Cnt1,Key_Cnt2,Key_Cnt3;//����ʱ��
uint8_t Key_Flag1,Key_Flag2,Key_Flag3;//�������±�־
uint8_t LongPress1,LongPress2,LongPress3;//����������־

uint8_t Lock_Switch; // ��������

/**
 * @brief ����ɨ��
 * 
 * @param dT ִ������
 */
void Key_Scan(float dT)
{
	/************************************P��**************************************/
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
                if(Lock_Switch)
                {
                    Beep_Flash = 2;//���εΡ�����������
                    sys.Lock_Alarm = 2;
                }
                else if(sys.Run_Status)
                {
                    Beep_Flash = 2;//���εΡ�����������
                }
                else
                {
                    if (PMode.Status == 1) // �����Pģʽ
                    {
                        if(Pmode_Twinkle_Time)
                        {
                            PMode.Status = 0; // �ر�Pģʽ
                            PMode.Option = 0;
                            Param_Read();//��ȡ����
                            Pmode_Twinkle_Time = Speed_Twinkle_Time = Time_Twinkle_Time = 0;
                        }
                        else
                        {
                            Speed_Twinkle_Time = Time_Twinkle_Time = 0;
                            Pmode_Twinkle_Time = 2.0f;
                        }
                    }
                    else if (PMode.Status == 0)
                    {
                        PMode.Status = 1; // ��Pģʽ
                        PMode.Option = 1;
                        Param_Read();   // ��ȡ����
                        Speed_Twinkle_Time = Time_Twinkle_Time = 0;
                        Pmode_Twinkle_Time = 2.0f;
                    }
                    Beep_Time = 0.1f; // ��������0.1S
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
                Beep_Flash = 2;//���εΡ�����������
                if(Lock_Switch)
                {
                    sys.Lock_Alarm = 2;
                }
				LongPress1 = 1;//������־��һ
			}
		}
	}
    
	/**************************************������**************************************/
	if(KEY2 == KEY_DOWN)//���°���
	{	
		if(LongPress2 == 0)//û�г�����
		{
			Key_Cnt2 += dT;//����ʱ��++
			Key_Flag2 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag2 == 1)//����������
	{
		if(KEY2 == KEY_UP)//̧�𰴼�
		{   
			if(Key_Cnt2 > 0.1 && Key_Cnt2 < 1.5)//С��1.5S�ǵ���
			{
				if (Lock_Switch)
				{
					Lock_Switch = 0;
				}
				else
				{
					Lock_Switch = 1;
				}
				Beep_Time = 0.1f; // ��������0.1S
			}
			Key_Flag2 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress2 = 0;//������־����
			Key_Cnt2 = 0;//��ť��������		
		}
		if(Key_Cnt2 > 1.5 && Key_Cnt2 < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress2 == 0)//���û��һֱһֱ������
			{
				Beep_Flash = 2;//���εΡ�����������
				LongPress2 = 1;//������־��һ
			}
		}
	}
	/**************************************����ת��**************************************/
	if(KEY3 == KEY_DOWN)//���°���
	{	
		if(LongPress3 == 0)//û�г�����
		{
			Key_Cnt3 += dT;//����ʱ��++
			Key_Flag3 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag3 == 1)//����������
	{
		if(KEY3 == KEY_UP)//̧�𰴼�
		{   
			if(Key_Cnt3 > 0.1 && Key_Cnt3 < 1.5)//С��1.5S�ǵ���
			{
                if(Lock_Switch)
                {
                    Beep_Flash = 2;//���εΡ�����������
                    sys.Lock_Alarm = 2;
                }
                else
                {
                    if(!Speed.Cw)//�ı�ת��Ļ�
                    {
                        Speed.ADDMode = 2;//��ȥ������ʾ
                        sys.Motor_Stop = 1;//���ֹͣ
                        Speed.Cw = 1;//����ı�ת��
                        SpeedSet_Flag=TimeSet_Flag=1;//��������
                        Pmode_Twinkle_Time = Speed_Twinkle_Time = Time_Twinkle_Time = 0;//�ر���˸
                    }
                    Beep_Time = 0.1f; // ��������0.1S
                    Beep_Time = 0.1f;
                }
			}
			Key_Flag3 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress3 = 0;//������־����
			Key_Cnt3 = 0;//��ť��������		
		}
		if(Key_Cnt3 > 1.5 && Key_Cnt3 < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress3 == 0)//���û��һֱһֱ������
			{
                Beep_Flash = 2;//���εΡ�����������
                if(Lock_Switch)
                {
                    sys.Lock_Alarm = 2;
                }
				LongPress3 = 1;//������־��һ
			}
		}
	}
}
