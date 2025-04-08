#include "Drv_KEY.h"

/**********�ֲ���������******/
float Key_Cnt1,Key_Cnt2,Key_Cnt3;//����ʱ��
uint8_t Key_Flag1,Key_Flag2,Key_Flag3;//�������±�־
uint8_t LongPress1,LongPress2,LongPress3;//����������־

/*
*****************************************************************
 * ����ԭ�ͣ�void Key_Scan(float dT)
 * ��    �ܣ�����ɨ��
*****************************************************************
*/
void Key_Scan(float dT)
{
	/************************************������**************************************/
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
				if(sys.Lock)
					sys.Lock = 0;
				else
					sys.Lock = 1;
				Beep_Time = 0.1;//��������0.1S
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
    
	/**************************************��ʱ��**************************************/
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
				if(sys.Lock)
				{
					Beep_Flash = 2;//���εΡ�����������
				}
				else
				{
					if(sys.SetMode_Option != 3)
					{
						sys.SetMode_Option = 3;
						Time_Twinkle_Time = 6;//��˸ʱ��6S
					}
					else
					{
						sys.SetMode_Option = 0;
						EC11A[1].EC11A_Knob = EC11A[0].EC11A_Knob = 0;
						Time_Twinkle_Time = 0;
						TimeSet_Flag = 1;//����ʱ���趨
					}
					Beep_Time = 0.1;//��������0.1S
				}
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
				if(sys.Lock)
				{
					Beep_Flash = 2;//���εΡ�����������
				}
				else
				{
					if(!Speed.Cw)//�ı�ת��Ļ�
					{
						Speed.ADDMode = 2;//��ȥ������ʾ
						sys.Motor_Stop = 1;//���ֹͣ
						Speed.Cw = 1;//����ı�ת��
						Speed.CwShow = 1;//ת��ͼ��ı䣬������ʼ
						SpeedSet_Flag = TempSet_Flag = TimeSet_Flag=1;//��������
					}
					Beep_Time = 0.1;//��������0.1S
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
