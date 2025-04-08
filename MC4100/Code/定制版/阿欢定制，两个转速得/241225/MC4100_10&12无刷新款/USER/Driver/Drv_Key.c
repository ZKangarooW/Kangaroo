#include "Drv_Key.h"

/**********ȫ�ֱ�������******/
uint8_t Key_Status;//�������±�־

/**********�ֲ���������******/
float Key_Cnt1,Key_Cnt2,Key_Cnt3,Key_Cnt4,Key_Cnt5,Key_Cnt6;//����ʱ��
uint8_t Key_Flag1,Key_Flag2,Key_Flag3,Key_Flag4,Key_Flag5,Key_Flag6;//�������±�־
uint8_t LongPress1,LongPress2,LongPress3,LongPress4,LongPress5,LongPress6;//����������־

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
	/**************************************vial��**************************************/
	if(Key3 == 0)//���°���
	{
		Key_Cnt1 += dT;//����ʱ��++
		Key_Flag1 = 1;//�������±�־��һ
	}
	if(Key_Flag1 == 1)//����������
	{
		if(Key3 == 1)//̧�𰴼�
		{   
			if(Key_Cnt1 < 1.5)//С��1.5S�ǵ���
			{
				if(HAL_GPIO_ReadPin(BREAKEZ_GPIO_Port,BREAKEZ_Pin)== 1)//������պ�ʱ
				{
                    if(sys.Run_Status == 0)
					{
                        Set_Speed = 2000;
                        Set_Time = 10;
                        Speed_Val.SumError = 0x186A0;//������ ��ϵ��
                        SetOK_Flag = 1;//�趨ֵ
                        sys.Run_Status = 1;
                        sys.SetMode_Option = 0;
                        Speed_ADDMode = 0;
                        if(sys.Motor_Stop)//����ڽ��ٵ������
                            sys.Motor_Stop = 0;
                        Beep_Time = 0.1;//��������0.1S
                    }
                    else
                    {
                        Set_Time = 10;
                        SetOK_Flag = 1;//�趨ֵ
                        sys.SetMode_Option = 0;
                        Speed_ADDMode = 0;
                        if(sys.Motor_Stop)//����ڽ��ٵ������
                            sys.Motor_Stop = 0;
                        Beep_Time = 0.1;//��������0.1S
                    }
				}
                else
				{
					Beep_Flash = 7;
					sys.Lock_On = 1;
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

	/**************************************STOP��**************************************/
	if(Key2 == 0)//���°���
	{
		if(LongPress3 == 0)//û�г�����
		{
			Key_Cnt3 += dT;//����ʱ��++
			Key_Flag3 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag3 == 1)//����������
	{
		if(Key2 == 1)//̧�𰴼�
		{   
			if(Key_Cnt3 < 1.5)/*����*///С��1.5S�ǵ���
			{
				if(sys.Run_Status == 1)
                {
                    sys.Motor_Stop = 1;//�����
                    Speed_ADDMode = 2;//�������ģʽ��
                    Beep_Time = 0.1;//��������0.1S
                }
                else
                {
                    Beep_Flash = 2;//��Ч�������������������εΡ�
                }
			}
			Key_Flag3 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress3 = 0;//������־����
			Key_Cnt3 = 0;//��ť��������		
		}
		if(Key_Cnt3 > 1.5 && Key_Cnt3 < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress3 == 0)/*����*///���û��һֱһֱ������
			{
				Beep_Flash = 2;//��Ч�������������������εΡ�
				LongPress3 = 1;//������־��һ
			}
		}
	}
	/**************************************bubble��**************************************/
	if(Key4 == 0)//���°���
	{
		if(LongPress4 == 0)//û�г�����
		{
			Key_Cnt4 += dT;//����ʱ��++
			Key_Flag4 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag4 == 1)//����������
	{
		if(Key4 == 1)//̧�𰴼�
		{   
			if(Key_Cnt4 < 1.5)//С��1.5S�ǵ���
			{
				if(HAL_GPIO_ReadPin(BREAKEZ_GPIO_Port,BREAKEZ_Pin)== 1)//������պ�ʱ
				{
					if(sys.Run_Status == 0)
					{
                        Set_Speed = 2000;
                        Set_Time = 30;
						Speed_Val.SumError = 0x186A0;//������ ��ϵ��
						SetOK_Flag = 1;//�趨ֵ
						sys.Run_Status = 1;
						sys.SetMode_Option = 0;
						Speed_ADDMode = 0;
						if(sys.Motor_Stop)//����ڽ��ٵ������
							sys.Motor_Stop = 0;
                        Beep_Time = 0.1;//��������0.1S
					}
                    else
                    {
                        Set_Time = 30;
						SetOK_Flag = 1;//�趨ֵ
						sys.SetMode_Option = 0;
						Speed_ADDMode = 0;
						if(sys.Motor_Stop)//����ڽ��ٵ������
							sys.Motor_Stop = 0;
                        Beep_Time = 0.1;//��������0.1S
                    }
				}
				else
				{
					Beep_Flash = 7;
					sys.Lock_On = 1;
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
    
    /**************************************OPEN��**************************************/
	if(Key5 == 0)//���°���
	{
		Key_Cnt2 += dT;//����ʱ��++
		Key_Flag2 = 1;//�������±�־��һ
	}
	if(Key_Flag2 == 1)//����������
	{
		if(Key5 == 1)//̧�𰴼�
		{   
			if(Key_Cnt2 < 1.5)//С��1.5S�ǵ���
			{
                if(sys.Run_Status && sys.Motor_Stop==0)
                {
                    Beep_Flash = 2;
                }
                else
                {
                    if(HAL_GPIO_ReadPin(BREAKEZ_GPIO_Port,BREAKEZ_Pin)== 1)//������պ�ʱ
                        Lock_Status = 1;//�򿪵����
                    sys.Run_Status = 0;
                    sys.Motor_Stop = 0;
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
				Beep_Flash = 2;//��Ч�������������������εΡ�
				LongPress2 = 1;//������־��һ
			}
		}
	}
}
