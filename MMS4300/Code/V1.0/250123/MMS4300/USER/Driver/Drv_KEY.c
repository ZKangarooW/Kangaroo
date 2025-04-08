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
	/************************************SYNC��**************************************/
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
                }
                else
                {
                    for(uint8_t i = 0;i<4;i++)
                    {
                        Work_Num[i].Speed.Set= Param.Speed[i]= Work_Num[i].Speed.Ctrl= Work_Num[sys.New_Work].Speed.Set;
                        Work_Num[i].Time.Rel = Work_Num[i].Time.Set = Param.Time[i] = Work_Num[i].Time.Ctrl = Work_Num[sys.New_Work].Time.Set;
                        
                        if(Work_Num[i].Speed.ADDMode != 0)
                            Work_Num[i].Speed.ADDMode = 0;
                        
                        if(Work_Num[sys.New_Work].Run_Status)
                        {
                            Work_Num[i].Run_Status = 1;
                        }
                    }
                    sys.Sync = 1;
                    sys.SetMode_Option = 0;//�˳�����ģʽ
                    Twinkle_Time = 0;
                    Save_Param_En = 1;//����
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
	/**************************************start��**************************************/
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
                }
                else
                {
                    if(Work_Num[0].Run_Status != 1 && Work_Num[1].Run_Status != 1 
                    && Work_Num[2].Run_Status != 1 && Work_Num[3].Run_Status != 1
                        )//ϵͳû�����Ļ�
                    {
                        for(uint8_t i = 0;i<4;i++)
                        {
                            Work_Num[i].Run_Status = 1;//����ϵͳ
                        }
                    }
                    else//ϵͳ�����Ļ�
                    {
                        for(uint8_t i = 0;i<4;i++)
                        {
                            Work_Num[i].Speed.ADDMode = 2;
                            Work_Num[i].Motor_Stop = 1;//���ֹͣ
                        }
                    }
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
				LongPress3 = 1;//������־��һ
			}
		}
	}
}
