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
 * ��    �ܣ����󰴼�ɨ��
*****************************************************************
*/
void Key_Scan(float dT)
{
	/**************************************����**************************************/
	if(KEY2 == 0)//���°���
	{
		Key_Cnt1 += dT;//����ʱ��++
		Key_Flag1 = 1;//�������±�־��һ
	}
	if(Key_Flag1 == 1)//����������
	{
		if(KEY2 == 1)//̧�𰴼�
		{   
			if(Key_Cnt1 < 1.5)//С��1.5S�ǵ���
			{
				if(CGF.Mode == 0)
                {
                    if(sys.SetMode_Option == 1)//�����ٶ�
                    {
                        if(Speed.Unit)
                        {
                            Speed.Set -= 50;//�����ʼ�50
                            if(Speed.Set < Xg_Min)//������С����Xg_Minʱ
                                Speed.Set = Xg_Min;//�����ʵ���Xg_Min
                        }
                        else
                        {
                            Speed.Set -= 100;//�ٶȼ�100
                            if(Speed.Set < Speed_Min)//�ٶ�С��Speed_Minʱ
                                Speed.Set = Speed_Min;//�ٶȵ���Speed_Min
                        }
                        Key_Status = 2;
                        Twinkle_Time = 6;//��˸ʱ��6S
                    }
                    else if(sys.SetMode_Option == 2)//����ʱ��
                    {
                        Time.Set -= 10;//ʱ���10S
                        if(Time.Set < Time_Min)//����ʱ��С��Time_Min
                            Time.Set = Time_Min;//����ʱ�����Time_Min
                        Key_Status = 2;
                        Twinkle_Time = 6;//��˸ʱ��6S
                    }
                    else
                    {
                        Beep_Flash = 2;//��Ч�������������������εΡ�
                    }
                }
                else
                {
//                    CGF.Mode --;
//                    if(CGF.Mode<1)
//                        CGF.Mode = 4;
                    Beep_Flash = 2;//��Ч�������������������εΡ�
                }
			}	
			Key_Flag1 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt1 = 0;//��ť��������
		}
		if(Key_Cnt1 > 1.9 && Key_Cnt1 < 2.1)//����ʱ�����1.9SС��2.1S��ʾ����
		{
            if(CGF.Mode == 0)
            {
                if(sys.SetMode_Option == 1)//�����ٶ�
                {
                    if(Speed.Unit)
                    {
                        Speed.Set -= 100;//�����ʼ�100
                        if(Speed.Set < Xg_Min)//������С����Xg_Minʱ
                            Speed.Set = Xg_Min;//�����ʵ���Xg_Min
                    }
                    else
                    {
                        Speed.Set -= 100;//�ٶȼ�100
                        if(Speed.Set < Speed_Min)//�ٶ�С��Speed_Minʱ
                            Speed.Set = Speed_Min;//�ٶȵ���Speed_Min
                    }
                    Key_Status = 2;
                    Twinkle_Time = 6;//��˸ʱ��6S
                }
                else if(sys.SetMode_Option == 2)//����ʱ��
                {
                    Time.Set -= 60;//ʱ���60S
                    if(Time.Set < Time_Min)//����ʱ��С��Time_Min
                        Time.Set = Time_Min;//����ʱ�����Time_Min
                    Key_Status = 2;
                    Twinkle_Time = 6;//��˸ʱ��6S
                }
                else
                {
                    Beep_Flash = 2;//��Ч�������������������εΡ�
                }
            }
            else
            {
//                CGF.Mode --;
//                if(CGF.Mode<1)
//                    CGF.Mode = 4;
                Beep_Flash = 2;//��Ч�������������������εΡ�
            }
			Key_Flag1 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt1 = 1.75;//��ť��������
		}
	}

	/**************************************MENU��**************************************/
	if(KEY4 == 0)//���°���
	{
		Key_Cnt2 += dT;//����ʱ��++
		Key_Flag2 = 1;//�������±�־��һ
	}
	if(Key_Flag2 == 1)//����������
	{
		if(KEY4 == 1)//̧�𰴼�
		{   
			if(Key_Cnt2 < 1.5)//С��1.5S�ǵ���
			{
                if(CGF.Mode==0)
                {
                    if(sys.Run_Status)
                    {
                        Beep_Flash = 2;//��Ч�������������������εΡ�
                    }
                    else
                    {
                        sys.SetMode_Option++;//����ģʽ++
                        if(sys.SetMode_Option > 2)//�˳�����
                            sys.SetMode_Option = 0;//����
                        Beep_Time = 0.1;//��������0.1S
                        Twinkle_Time = 6;//��˸ʱ��6S
                    }
                }
                else
                {
                    CGF.Mode++;
                    if(CGF.Mode>4)
                        CGF.Mode = 1;
                    if(CGF.Mode == 1)
						CGF.Option = 1;//����ģʽ1
					else if(CGF.Mode == 2)
						CGF.Option = 5;//����ģʽ5
					else if(CGF.Mode == 3)
						CGF.Option = 6;//����ģʽ6
					else if(CGF.Mode == 4)
						CGF.Option = 7;//����ģʽ7
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
                if(CGF.Mode == 0)
                {
                    CGF.Mode = 1;
                }
                else
                {
                    CGF.Mode = 0;
                }
                CGF.Option = 1;
				LongPress2 = 1;//������־��һ
			}
		}
	}
	
	/**************************************Start��**************************************/
	if(KEY1 == 0)//���°���
	{
		if(LongPress3 == 0)//û�г�����
		{
			Key_Cnt3 += dT;//����ʱ��++
			Key_Flag3 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag3 == 1)//����������
	{
		if(KEY1 == 1)//̧�𰴼�
		{   
			if(Key_Cnt3 < 1.5)/*����*///С��1.5S�ǵ���
			{
				if(HAL_GPIO_ReadPin(UC_IN_GPIO_Port,UC_IN_Pin)== 1)//�����1�պ�ʱ
				{
					if(sys.Run_Status == 0)
					{
						Speed_Val.Integral = 25;//������ ��ϵ��
						SetOK_Flag = 1;//�趨ֵ
						sys.Run_Status = 1;
						sys.SetMode_Option = 0;
						Speed.ADDMode = 0;
						Beep_Time = 0.1;//��������0.1S
					}
					else
					{
						sys.Motor_Stop = 1;//�����
						Speed.ADDMode = 2;//�������ģʽ��
						Beep_Time = 0.1;//��������0.1S
					}
				}
				else
				{
					Beep_Flash = 7;//��������7��
					sys.Lock_On = 1;//����ͼ����˸��־λ
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

	/**************************************�Ӽ�**************************************/
	if(KEY3 == 0)//���°���
	{
		Key_Cnt4 += dT;//����ʱ��++
		Key_Flag4 = 1;//�������±�־��һ
	}
	if(Key_Flag4 == 1)//����������
	{
		if(KEY3 == 1)//̧�𰴼�
		{   
			if(Key_Cnt4 < 1.5)//С��1.5S�ǵ���
			{
                if(CGF.Mode == 0)
                {
                    if(sys.SetMode_Option == 1)//�����ٶ�
                    {
                        if(Speed.Unit)
                        {
                            Speed.Set += 50;//�����ʼ�50
                            if(Speed.Set > Xg_MAX)//�����ʴ���2100ʱ
                                Speed.Set = Xg_MAX;//�����ʵ���2100
                        }
                        else
                        {
                            Speed.Set += 100;//�ٶȼ�100
                            if(Speed.Set > Speed_MAX)//�ٶȴ���2500ʱ
                                Speed.Set = Speed_MAX;//�ٶȵ���2500
                        }
                        Key_Status = 2;
                        Twinkle_Time = 6;//��˸ʱ��6S
                    }
                    else if(sys.SetMode_Option == 2)//����ʱ��
                    {
                        Time.Set += 10;//ʱ���10S
                        if(Time.Set > Time_MAX)//����ʱ�����59��50��ʱ
                            Time.Set = Time_MAX;//����ʱ�����59��50��ʱ
                        Key_Status = 2;
                        Twinkle_Time = 6;//��˸ʱ��6S
                    }
                    else
                    {
                        Beep_Flash = 2;//��Ч�������������������εΡ�
                    }
                }
                else
                {
//                    CGF.Mode ++;
//                    if(CGF.Mode>4)
//                        CGF.Mode = 1;
                    Beep_Flash = 2;//��Ч�������������������εΡ�
                }
			}
			Key_Flag4 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt4 = 0;//��ť��������		
		}
		if(Key_Cnt4 > 1.9 && Key_Cnt4 < 2.1)//����ʱ�����1.9SС��2.1S��ʾ����
		{
            if(CGF.Mode == 0)
            {
                if(sys.SetMode_Option == 1)//�����ٶ�
                {
                    if(Speed.Unit)
                    {
                        Speed.Set += 100;//�����ʼ�100
                        if(Speed.Set > Xg_MAX)//�����ʴ���2100ʱ
                            Speed.Set = Xg_MAX;//�����ʵ���2100
                    }
                    else
                    {
                        Speed.Set += 100;//�ٶȼ�100
                        if(Speed.Set > Speed_MAX)//�ٶȴ���2500ʱ
                            Speed.Set = Speed_MAX;//�ٶȵ���2500
                    }
                    Key_Status = 2;
                    Twinkle_Time = 6;//��˸ʱ��6S
                }
                else if(sys.SetMode_Option == 2)//����ʱ��
                {
                    Time.Set += 60;//ʱ���10S
                    if(Time.Set > Time_MAX)//����ʱ�����59��50��ʱ
                        Time.Set = Time_MAX;//����ʱ�����59��50��ʱ
                    Key_Status = 2;
                    Twinkle_Time = 6;//��˸ʱ��6S
                }
                else
                {
                    Beep_Flash = 2;//��Ч�������������������εΡ�
                }
            }
            else
            {
//                CGF.Mode ++;
//                if(CGF.Mode>4)
//                    CGF.Mode = 1;
                Beep_Flash = 2;//��Ч�������������������εΡ�
            }
			Key_Flag4 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt4 = 1.75;//��ť��������
		}
	}
    
	/**************************************OPEN��**************************************/
	if(KEY5 == 0)//���°���
	{
		Key_Cnt5 += dT;//����ʱ��++
		Key_Flag5 = 1;//�������±�־��һ
	}
	if(Key_Flag5 == 1)//����������
	{
		if(KEY5 == 1)//̧�𰴼�
		{   
			if(Key_Cnt5 < 1.5)//С��1.5S�ǵ���
			{
				if(sys.Run_Status)
				{
					Beep_Flash = 2;//��Ч�������������������εΡ�
				}
				else
				{
					if(HAL_GPIO_ReadPin(UC_IN_GPIO_Port,UC_IN_Pin)== 1)//�����1�պ�ʱ
					{
						Lock_Status = 1;//�򿪵����1
						Beep_Time = 0.1;//��������0.1S
						sys.Run_Status = 0;//�ر�ϵͳ
					}
					else
					{
						Beep_Flash = 2;//��Ч�������������������εΡ�
					}
				}
			}
			Key_Flag5 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt5 = 0;//��ť��������		
		}
		if(Key_Cnt5 > 1.9 && Key_Cnt5 < 2.1)//����ʱ�����1.9SС��2.1S��ʾ����
		{
			Beep_Flash = 2;//��Ч�������������������εΡ�
			Key_Flag5 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt5 = 1.5;//��ť��������
		}
	}
}

