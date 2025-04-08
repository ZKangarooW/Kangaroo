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
	ROW1_L;
	ROW2_H;
	ROW3_H;
	/**************************************P��**************************************/
	if(HAL_GPIO_ReadPin(COL1_GPIO_Port,COL1_Pin) == 0)//���°���
	{
        if(sys.Run_Status) return;
		if(LongPress1 == 0)//û�г�����
		{
			Key_Cnt1 += dT;//����ʱ��++
			Key_Flag1 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag1 == 1)//����������
	{
		if(HAL_GPIO_ReadPin(COL1_GPIO_Port,COL1_Pin) == 1)//̧�𰴼�
		{   
			if(Key_Cnt1 < 1.5f)//С��1.5S�ǵ���
			{   
                sys.Run_Mode++;
                if(sys.Run_Mode>4)
                    sys.Run_Mode = 0;
                if(sys.Run_Mode == 0)
                    PMode.Option = 0;//����ģʽ0
                else if(sys.Run_Mode == 1)
                    PMode.Option = 1;//����ģʽ1
                else if(sys.Run_Mode == 2)
                    PMode.Option = 5;//����ģʽ5
                else if(sys.Run_Mode == 3)
                    PMode.Option = 6;//����ģʽ6
                else if(sys.Run_Mode == 4)
                    PMode.Option = 7;//����ģʽ7
                Speed.Unit = 0;//ת���ٶ�ģʽ
                Param_Read();//��ȡ����
                SetOK_Flag = 1;//���ò���
                sys.CGF_Step = 0;//CGF��������
                sys.SetMode_Option = 0;//�������趨ģʽ
                Beep_Time = 0.1f;//��������0.1S
			}
			Key_Flag1 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress1 = 0;//������־����
			Key_Cnt1 = 0;//��ť��������
		}
		if(Key_Cnt1 > 1.9f && Key_Cnt1 < 2.1f)//����ʱ�����1.9SС��2.1S��ʾ����
		{
			if(LongPress1 == 0)//���û��һֱһֱ������
			{
				
				LongPress1 = 1;//������־��һ
			}
		}
	}
	/**************************************����**************************************/
	if(HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_Pin )== 0)//���°���
	{
		Key_Cnt2 += dT;//����ʱ��++
		Key_Flag2 = 1;//�������±�־��һ
	}
	if(Key_Flag2 == 1)//����������
	{
		if(HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_Pin) == 1)//̧�𰴼�
		{   
			if(Key_Cnt2 < 1.5f)//С��1.5S�ǵ���
			{
				if(sys.SetMode_Option == 1)//����ʱ��
				{
					if(Time.Set < 3599)//����趨ʱ��С��59.59����ʱ
						Time.Set -= 10;//ʱ���10S
					else
						Time.Set += 60;//ʱ���60S
					if(Time.Set < 30)//����ʱ��С��30Sʱ
						Time.Set = 30;//����ʱ�����30S
				}
				else if(sys.SetMode_Option == 2)//�����ٶ�
				{
					if(Speed.Unit)
					{
						Speed.Set -= 100;//�����ʼ�100
						if(Speed.Set < 100)//�ٶ�С��100ʱ
							Speed.Set = 100;//�ٶ�С��100ʱ
					}
					else
					{
						Speed.Set -= 100;//�ٶȼ�100
						if(Speed.Set < 500)//�ٶ�С��500ʱ
							Speed.Set = 500;//�ٶȵ���500
					}
				}
				else if(sys.SetMode_Option == 3)//�����¶�
				{
					SafeTemp.Set -= 10;//�¶ȼ�1��
					if(SafeTemp.Set < (SafeTemp.Rel+50))//�趨��ȫ�¶ȴ���ʵ�ʰ�ȫ�¶�+5��ʱ
						SafeTemp.Set = SafeTemp.Rel+50;//�趨��ȫ�¶ȵ���ʵ�ʰ�ȫ�¶�+5��
                }
                Key_Status = 2.0f;//����ʱ2S����˸
                Twinkle_Time = 6.0f;//��˸ʱ��6S
            }
			Key_Flag2 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt2 = 0;//��ť��������		
		}
		if(Key_Cnt2 > 1.9f && Key_Cnt2 < 2.1f)//����ʱ�����1.9SС��2.1S��ʾ����
		{
			if(sys.SetMode_Option == 1)//����ʱ��
            {
                if(Time.Set < 3599)//����趨ʱ��С��59.59����ʱ
                    Time.Set -= 10;//ʱ���10S
                else
                    Time.Set += 60;//ʱ���60S
                if(Time.Set < 30)//����ʱ��С��30Sʱ
                    Time.Set = 30;//����ʱ�����30S
            }
            else if(sys.SetMode_Option == 2)//�����ٶ�
            {
                if(Speed.Unit)
                {
                    Speed.Set -= 100;//�����ʼ�100
                    if(Speed.Set < 100)//�ٶ�С��100ʱ
                        Speed.Set = 100;//�ٶ�С��100ʱ
                }
                else
                {
                    Speed.Set -= 100;//�ٶȼ�100
                    if(Speed.Set < 500)//�ٶ�С��500ʱ
                        Speed.Set = 500;//�ٶȵ���500
                }
            }
            else if(sys.SetMode_Option == 3)//�����¶�
            {
                SafeTemp.Set -= 10;//�¶ȼ�1��
                if(SafeTemp.Set < (SafeTemp.Rel+50))//�趨��ȫ�¶ȴ���ʵ�ʰ�ȫ�¶�+5��ʱ
                    SafeTemp.Set = SafeTemp.Rel+50;//�趨��ȫ�¶ȵ���ʵ�ʰ�ȫ�¶�+5��
            }
			Key_Status = 2.0f;//����ʱ2S����˸
            Twinkle_Time = 6.0f;//��˸ʱ��6S
			Key_Flag2 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt2 = 1.85f;//��ť��������
		}
	}
	ROW1_H;
	ROW2_L;
	ROW3_H;
	/**************************************MENU��**************************************/
	if(HAL_GPIO_ReadPin(COL1_GPIO_Port,COL1_Pin) == 0)//���°���
	{
        if(sys.Run_Mode || sys.Run_Status)
            return;
		if(LongPress3 == 0)//û�г�����
		{
			Key_Cnt3 += dT;//����ʱ��++
			Key_Flag3 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag3 == 1)//����������
	{
		if(HAL_GPIO_ReadPin(COL1_GPIO_Port,COL1_Pin) == 1)//̧�𰴼�
		{   
			if(Key_Cnt3 < 1.5)/*����*///С��1.5S�ǵ���
			{
				sys.SetMode_Option++;//����ģʽ++
                if(sys.SetMode_Option > 3)//�˳�����
                    sys.SetMode_Option = 0;//����
                Beep_Time = 0.1;//��������0.1S
				Twinkle_Time = 6;//��˸ʱ��6S
			}
			Key_Flag3 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress3 = 0;//������־����
			Key_Cnt3 = 0;//��ť��������		
		}
		if(Key_Cnt3 > 1.9f && Key_Cnt3 < 2.1f)//����ʱ�����1.9SС��2.1S��ʾ����
		{
			if(LongPress3 == 0)/*����*///���û��һֱһֱ������
			{
				if(Speed.Unit)//��������������ģʽ��
				{
					Speed.Unit = 0;//��ʾ�ٶȵ�λ
					Param_Read();
				}	
				else
				{
					Speed.Unit = 1;//��ʾ��������λ
					Param_Read();
				}
                sys.SetMode_Option = 0;
				Beep_Time = 0.1;//��������0.1S
				LongPress3 = 1;//������־��һ
			}
		}
	}
	/**************************************Start��**************************************/
	if(HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_Pin )== 0)//���°���
	{
		if(LongPress4 == 0)//û�г�����
		{
			Key_Cnt4 += dT;//����ʱ��++
			Key_Flag4 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag4 == 1)//����������
	{
		if(HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_Pin) == 1)//̧�𰴼�
		{   
			if(Key_Cnt4 < 1.5)//С��1.5S�ǵ���
			{
				if((HAL_GPIO_ReadPin(UC_IN1_GPIO_Port,UC_IN1_Pin)== 1)&&(HAL_GPIO_ReadPin(UC_IN2_GPIO_Port,UC_IN2_Pin)== 1))//�����1��2�պ�ʱ
				{
					if(sys.Run_Status == 0)
					{
						Speed_Val.Integral = 15;
						SetOK_Flag = 1;//�趨ֵ
						sys.Run_Status = 1;
						sys.SetMode_Option = 0;
						Speed.ADDMode = 0;//�ٶ���ʾģʽ����
					}
					else
					{
						sys.Motor_Stop = 1;//�����
						Speed.ADDMode = 2;//�������ģʽ��
					}
				}
				else
				{
					Beep_Flash = 7;//��������7��
					sys.Lock_On = 1;//����ͼ����˸
				}
				Beep_Time = 0.1f;//��������0.1S
			}
			Key_Flag4 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress4 = 0;//������־����
			Key_Cnt4 = 0;//��ť��������		
		}
		if(Key_Cnt4 > 1.9f && Key_Cnt4 < 2.1f)//����ʱ�����1.9SС��2.1S��ʾ����
		{
			if(LongPress4 == 0)//���û��һֱһֱ������
			{
               
				LongPress4 = 1;//������־��һ
			}
		}
	}
	ROW1_H;
	ROW2_H;
	ROW3_L;
	/**************************************�Ӽ�**************************************/
	if(HAL_GPIO_ReadPin(COL1_GPIO_Port,COL1_Pin) == 0)//���°���
	{
		Key_Cnt5 += dT;//����ʱ��++
		Key_Flag5 = 1;//�������±�־��һ
	}
	if(Key_Flag5 == 1)//����������
	{
		if(HAL_GPIO_ReadPin(COL1_GPIO_Port,COL1_Pin) == 1)//̧�𰴼�
		{   
			if(Key_Cnt5 < 1.5)//С��1.5S�ǵ���
			{
                if(sys.SetMode_Option == 1)//����ʱ��
				{
					if(Time.Set < 3599)//����趨ʱ��С��59.59����ʱ
						Time.Set += 10;//ʱ���10S
					else
						Time.Set += 60;//ʱ���60S
					if(Time.Set > 3590)//����ʱ�����59��50��ʱ
						Time.Set = 3590;//����ʱ�����59��50��ʱ
				}
				else if(sys.SetMode_Option == 2)//�����ٶ�
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
				}
				else if(sys.SetMode_Option == 3)//�����¶�
				{
					SafeTemp.Set += 10;//�¶ȼ�1��
					if(SafeTemp.Set > 500)//�趨��ȫ�¶ȴ���50��ʱ
						SafeTemp.Set = 500;//�趨��ȫ�¶ȵ���50��
				}
                Key_Status = 2.0f;//����ʱ2S����˸
                Twinkle_Time = 6.0f;//��˸ʱ��6S
			}
			Key_Flag5 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt5 = 0;//��ť��������		
		}
		if(Key_Cnt5 > 1.9 && Key_Cnt5 < 2.1)//����ʱ�����1.9SС��2.1S��ʾ����
		{
            if(sys.SetMode_Option == 1)//����ʱ��
            {
                if(Time.Set < 3599)//����趨ʱ��С��59.59����ʱ
                    Time.Set += 10;//ʱ���10S
                else
                    Time.Set += 60;//ʱ���60S
                if(Time.Set > 3590)//����ʱ�����59��50��ʱ
                    Time.Set = 3590;//����ʱ�����59��50��ʱ
            }
            else if(sys.SetMode_Option == 2)//�����ٶ�
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
            }
            else if(sys.SetMode_Option == 3)//�����¶�
            {
                SafeTemp.Set += 10;//�¶ȼ�1��
                if(SafeTemp.Set > 500)//�趨��ȫ�¶ȴ���50��ʱ
                    SafeTemp.Set = 500;//�趨��ȫ�¶ȵ���50��
            }
            Key_Status = 2.0f;//����ʱ2S����˸
            Twinkle_Time = 6.0f;//��˸ʱ��6S    
			Key_Flag5 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt5 = 1.85f;//��ť��������
		}
	}
	/**************************************OPEN��**************************************/
	if(HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_Pin )== 0)//���°���
	{
        if(sys.Run_Status) return;
		Key_Cnt6 += dT;//����ʱ��++
		Key_Flag6 = 1;//�������±�־��һ
	}
	if(Key_Flag6 == 1)//����������
	{
		if(HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_Pin) == 1)//̧�𰴼�
		{   
			if(Key_Cnt6 < 1.5)//С��1.5S�ǵ���
			{
				if(HAL_GPIO_ReadPin(UC_IN1_GPIO_Port,UC_IN1_Pin)== 1)//�����1�պ�ʱ
					Lock1_Status = 1;//�򿪵����1
				if(HAL_GPIO_ReadPin(UC_IN2_GPIO_Port,UC_IN2_Pin)== 1)//�����2�պ�ʱ
					Lock2_Status = 1;//�򿪵����2
                if((HAL_GPIO_ReadPin(UC_IN1_GPIO_Port,UC_IN1_Pin)== 1)||(HAL_GPIO_ReadPin(UC_IN2_GPIO_Port,UC_IN2_Pin)== 1))//�����1�պ�ʱ
                    Beep_Time = 0.1;//��������0.1S
			}
			Key_Flag6 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress6 = 0;//������־����
			Key_Cnt6 = 0;//��ť��������		
		}
		if(Key_Cnt6 > 1.9f && Key_Cnt6 < 2.1f)//����ʱ�����1.9SС��2.1S��ʾ����
		{
			if(LongPress6 == 0)//���û��һֱһֱ������
			{
                
				LongPress6 = 1;//������־��һ
			}
		}
	}
}
