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
		if(sys.Run_Status)//�������ʾ��������ģʽ�¶����ܲ���
			return;
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
			if(Key_Cnt1 < 1.5)//С��1.5S�ǵ���
			{
				if(Show_Circle == 0)
				{
					Show_Circle = 1;//��ʾ����P-��ģʽ
					PMode_Option = 1;//����ģʽ1
					Param_Read();//��ȡ����
					SetOK_Flag = 1;//���ò���
					sys.SetMode_Option = 1;//��������Pֵģʽ
					Twinkle_Time = 6;//��˸ʱ��6S
				}
				else
				{
					Show_Circle = 0;//����ʾ����P-��ģʽ
					PMode_Option = 0;//����ģʽ0
					Param_Read();//��ȡ����
					sys.SetMode_Option = 0;//ģʽ����
					SetOK_Flag = 1;//���ò���
				}
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
				LongPress1 = 1;//������־��һ
			}
		}
	}
	/**************************************OPEN��**************************************/
	if(HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_Pin )== 0)//���°���
	{
		if(sys.Run_Status || sys.Motor_Stop)//�������ʾ��������ģʽ�¶����ܲ���
			return;
		Key_Cnt2 += dT;//����ʱ��++
		Key_Flag2 = 1;//�������±�־��һ
	}
	if(Key_Flag2 == 1)//����������
	{
		if(HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_Pin) == 1)//̧�𰴼�
		{   
			if(Key_Cnt2 < 1.5)//С��1.5S�ǵ���
			{
				if(HAL_GPIO_ReadPin(BREAKEZ_GPIO_Port,BREAKEZ_Pin)== 1)//������պ�ʱ
					Lock_Status = 1;//�򿪵����
				sys.Run_Status = 0;
				sys.Motor_Stop = 0;
				Beep_Time = 0.1;//��������0.1S
			}
			Key_Flag2 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress2 = 0;//������־����
			Key_Cnt2 = 0;//��ť��������		
		}
		if(Key_Cnt2 > 1.5 && Key_Cnt2 < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress2 == 0)//���û��һֱһֱ������
			{
				LongPress2 = 1;//������־��һ
			}
		}
	}
	ROW1_H;
	ROW2_L;
	ROW3_H;
	/**************************************MENU��**************************************/
	if(HAL_GPIO_ReadPin(COL1_GPIO_Port,COL1_Pin) == 0)//���°���
	{
		if(sys.Run_Status == 1)
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
				if(Show_Circle == 0)
				{
					sys.SetMode_Option++;//����ģʽ++
					if(sys.SetMode_Option > 4)//�˳�����
						sys.SetMode_Option = 0;//����
					if(sys.SetMode_Option == 1)
						sys.SetMode_Option = 2;
				}
				else
				{
					sys.SetMode_Option++;//����ģʽ++
					if(sys.SetMode_Option > 4)//�˳�����
						sys.SetMode_Option = 0;//����
					
				}
				Beep_Time = 0.1;//��������0.1S
				Twinkle_Time = 6;//��˸ʱ��6S
			}
			Key_Flag3 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress3 = 0;//������־����
			Key_Cnt3 = 0;//��ť��������		
		}
		if(Key_Cnt3 > 1.5 && Key_Cnt3 < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress3 == 0)/*����*///���û��һֱһֱ������
			{
				if(Speed_Mode)//��������������ģʽ��
				{
					Speed_Mode = 0;//�������Ƴ�
					Speed_Unit = 0;//��ʾ�ٶȵ�λ
					Param_Read();
				}	
				else
				{
					Speed_Mode = 1;//������������ʾģʽ
					Speed_Unit = 1;//��ʾ��������λ
					Param_Read();
				}
				Beep_Time = 0.1;//��������0.1S
				Twinkle_Time = 6;//��˸ʱ��6S
				LongPress3 = 1;//������־��һ
			}
		}
	}
	/**************************************Start��**************************************/
	if(HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_Pin )== 0)//���°���
	{
		if(sys.Run_Status == 0)
		{
			if(Safe_Rel_Temp + 50 >= Safe_Set_Temp)
			{
				Safe_Temp_Twinkleg = 1;//��ȫ�¶�ͼ����˸
				Beep_Flash = 5;//��������5��
				return;
			}
		}
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
				if(HAL_GPIO_ReadPin(BREAKEZ_GPIO_Port,BREAKEZ_Pin)== 1)//������պ�ʱ
				{
					if(sys.Run_Status == 0)
					{
						if(Show_Circle == 1)
							Circle_Run = 1;
						SetOK_Flag = 1;//�趨ֵ
						sys.Run_Status = 1;
						sys.SetMode_Option = 0;
						if(sys.Motor_Stop)//����ڽ��ٵ������
							sys.Motor_Stop = 0;
					}
					else
					{
						sys.Run_Status = 0;//�����
						sys.Motor_Stop = 1;//�����ֹͣ����
					}
				}
				else
				{
					Beep_Flash = 7;
					sys.Lock_On = 1;
				}
				Beep_Time = 0.1;//��������0.1S
			}
			Key_Flag4 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress4 = 0;//������־����
			Key_Cnt4 = 0;//��ť��������		
		}
		if(Key_Cnt4 > 1.5 && Key_Cnt4 < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress4 == 0)//���û��һֱһֱ������
			{
				Beep_Time = 0.1;//��������0.1S
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
		if(sys.Run_Status)
			return;
		Key_Cnt5 += dT;//����ʱ��++
		Key_Flag5 = 1;//�������±�־��һ
	}
	if(Key_Flag5 == 1)//����������
	{
		if(HAL_GPIO_ReadPin(COL1_GPIO_Port,COL1_Pin) == 1)//̧�𰴼�
		{   
			if(Key_Cnt5 < 1.5)//С��1.5S�ǵ���
			{
				if(sys.SetMode_Option == 2)//����ʱ��
				{
					if(Time_Unit == 0)
						Set_Time += 10;//ʱ���10S
					else
						Set_Time += 60;//ʱ���60S
					if(Set_Time > 3590)//����ʱ�����59��50��ʱ
						Set_Time = 3590;//����ʱ�����59��50��ʱ
				}
				else if(sys.SetMode_Option == 3)//�����ٶ�
				{
					#if(Type == 0)//10PRo
					if(Speed_Mode)
					{
						Val_xg += 1;//�ٶ������1
						if(Val_xg > 90)//�ٶ��������90
							Val_xg = 90;//�ٶ��������90
						Set_Speed = xg_Val[Val_xg];
					}
					else
					{
						Val_Speed += 1;//�ٶȼ�1������
						if(Val_Speed > 90)//�ٶ��������90ʱ
							Val_Speed = 90;//�ٶ��������90
						Set_Speed =  Speed_Val[Val_Speed];
					}
					#elif(Type == 1)//12PRO
					if(Speed_Mode)
					{
						Val_xg += 1;//�ٶ������1
						if(Val_xg > 110)//�ٶ��������110
							Val_xg = 110;//�ٶ��������110
						Set_Speed = xg_Val[Val_xg];
					}
					else
					{
						Val_Speed += 1;//�ٶȼ�1������
						if(Val_Speed > 110)//�ٶ��������110ʱ
							Val_Speed = 110;//�ٶ��������110
						Set_Speed = Speed_Val[Val_Speed];
					}
					#endif
				}
				else if(sys.SetMode_Option == 4)//�����¶�
				{
					Safe_Set_Temp += 10;//�¶ȼ�1��
					if(Safe_Set_Temp > 500)//�趨��ȫ�¶ȴ���50��ʱ
						Safe_Set_Temp = 500;//�趨��ȫ�¶ȵ���50��
				}
				if(Show_Circle == 1 && sys.SetMode_Option == 1)
				{
					PMode_Option++;
					if(PMode_Option > 9)
					{
						PMode_Option = 9;
					}
					Param_Read();
				}
				Key_Status = 2;//����ʱ2S����˸
//				Beep_Time = 0.1;//��������0.1S
				Twinkle_Time = 6;//��˸ʱ��6S
			}
			Key_Flag5 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt5 = 0;//��ť��������		
		}
		if(Key_Cnt5 > 1.9 && Key_Cnt5 < 2.1)//����ʱ�����1.9SС��2.1S��ʾ����
		{
			if(sys.SetMode_Option == 2)//����ʱ��
			{
				if(Time_Unit == 0)
						Set_Time += 60;//ʱ���60S
					else
						Set_Time += 600;//ʱ���600S
				if(Set_Time > 3590)//����ʱ�����59��50��ʱ
					Set_Time = 3590;//����ʱ�����59��50��ʱ
			}
			else if(sys.SetMode_Option == 3)//�����ٶ�
			{
				#if(Type == 0)//10PRo
				if(Speed_Mode)
				{
					Val_xg += 10;//�ٶ������10
					if(Val_xg > 90)//�ٶ��������90
						Val_xg = 90;//�ٶ��������90
					Set_Speed = xg_Val[Val_xg];
				}
				else
				{
					Val_Speed += 10;//�ٶȼ�10������
					if(Val_Speed > 90)//�ٶ��������90ʱ
						Val_Speed = 90;//�ٶ��������90
					Set_Speed =  Speed_Val[Val_Speed];
				}
				#elif(Type == 1)//12PRO
				if(Speed_Mode)
				{
					Val_xg += 10;//�ٶ������10
					if(Val_xg > 110)//�ٶ��������110
						Val_xg = 110;//�ٶ��������110
					Set_Speed = xg_Val[Val_xg];
				}
				else
				{
					Val_Speed += 10;//�ٶȼ�10������
					if(Val_Speed > 110)//�ٶ��������110ʱ
						Val_Speed = 110;//�ٶ��������110
					Set_Speed =  Speed_Val[Val_Speed];
				}
				#endif
			}
			else if(sys.SetMode_Option == 4)//�����¶�
			{
				Safe_Set_Temp += 100;//�¶ȼ�1��
				if(Safe_Set_Temp > 500)//�趨��ȫ�¶ȴ���50��ʱ
					Safe_Set_Temp = 500;//�趨��ȫ�¶ȵ���50��
			}
			Key_Status = 2;//����ʱ2S����˸
			Key_Flag5 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt5 = 1.5;//��ť��������
//			Beep_Time = 0.1;//��������0.1S
			Twinkle_Time = 6;//��˸ʱ��6S
		}
	}
	/**************************************����**************************************/
	if(HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_Pin )== 0)//���°���
	{
		if(sys.Run_Status)
			return;
		if(LongPress6 == 0)//û�г�����
		{
			Key_Cnt6 += dT;//����ʱ��++
			Key_Flag6 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag6 == 1)//����������
	{
		if(HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_Pin) == 1)//̧�𰴼�
		{   
			if(Key_Cnt6 < 1.5)//С��1.5S�ǵ���
			{
				if(sys.SetMode_Option == 2)//����ʱ��
				{
					if(Time_Unit == 0)//ʱ��״̬����Ϊ��λʱ
						Set_Time -= 10;//ʱ���10S
					else
						Set_Time -= 60;//ʱ���60S
					if(Set_Time < 30)//����ʱ��С��30Sʱ
						Set_Time = 30;//����ʱ�����30S
				}
				else if(sys.SetMode_Option == 3)//�����ٶ�
				{
					if(Speed_Mode)
					{
						Val_xg -= 1;//�ٶ������1
						if(Val_xg < 0)//�ٶ�����С��0
							Val_xg = 0;//�ٶ��������0
						Set_Speed = xg_Val[Val_xg];
					}
					else
					{
						Val_Speed -= 1;//�ٶ������1
						if(Val_Speed < 0)//�ٶ�����С��0
							Val_Speed = 0;//�ٶ��������0
						Set_Speed =  Speed_Val[Val_Speed];
					}
				}
				else if(sys.SetMode_Option == 4)//�����¶�
				{
					Safe_Set_Temp -= 10;//�¶ȼ�1��
					if(Safe_Set_Temp < (Safe_Rel_Temp+50))//�趨��ȫ�¶ȴ���ʵ�ʰ�ȫ�¶�+5��ʱ
						Safe_Set_Temp = Safe_Rel_Temp+50;//�趨��ȫ�¶ȵ���ʵ�ʰ�ȫ�¶�+5��
				}
				if(Show_Circle == 1 && sys.SetMode_Option == 1)
				{
					PMode_Option--;
					if(PMode_Option < 1)
					{
						PMode_Option = 1;
					}
					Param_Read();
				}
				Key_Status = 2;//����ʱ2S����˸
//				Beep_Time = 0.1;//��������0.1S
				Twinkle_Time = 6;//��˸ʱ��6S
			}
			Key_Flag6 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt6 = 0;//��ť��������
		}
		if(Key_Cnt6 > 1.9 && Key_Cnt6 < 2.1)//����ʱ�����1.9SС��2.1S��ʾ����
		{
			if(sys.SetMode_Option == 2)//����ʱ��
			{
				if(Time_Unit == 0)//ʱ��״̬����Ϊ��λʱ
						Set_Time -= 60;//ʱ���60S
					else
						Set_Time -= 600;//ʱ���600S
				if(Set_Time < 30)//����ʱ��С��30Sʱ
					Set_Time = 30;//����ʱ�����30S
			}
			else if(sys.SetMode_Option == 3)//�����ٶ�
			{
				if(Speed_Mode)
				{
					Val_xg -= 10;//�ٶ������1
					if(Val_xg < 0)//�ٶ�����С��0
						Val_xg = 0;//�ٶ��������0
					Set_Speed = xg_Val[Val_xg];
				}
				else
				{
					Val_Speed -= 10;//�ٶ������10
					if(Val_Speed < 0)//�ٶ�����С��0
						Val_Speed = 0;//�ٶ��������0
					Set_Speed =  Speed_Val[Val_Speed];
				}
			}
			else if(sys.SetMode_Option == 4)//�����¶�
			{
				Safe_Set_Temp -= 100;//�¶ȼ�10��
				if(Safe_Set_Temp < (Safe_Rel_Temp+50))//�趨��ȫ�¶ȴ���ʵ�ʰ�ȫ�¶�+5��ʱ
						Safe_Set_Temp = Safe_Rel_Temp+50;//�趨��ȫ�¶ȵ���ʵ�ʰ�ȫ�¶�+5��
			}
			Key_Status = 2;//����ʱ2S����˸
			Key_Flag6 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt6 = 1.5;//��ť��������
//			Beep_Time = 0.1;//��������0.1S
			Twinkle_Time = 6;//��˸ʱ��6S
		}
	}
}

