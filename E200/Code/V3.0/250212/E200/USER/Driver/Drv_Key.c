#include "Drv_Key.h"

/**********ȫ�ֱ�������******/
uint8_t Key_Status;//�������±�־
uint8_t LongPress;//������³���

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
	/**************************************Temp_Set��**************************************/
	if(KEY1 == 0)//���°���
	{
		if(LongPress1 == 0)//û�г�����
		{
			Key_Cnt1 += dT;//����ʱ��++
			Key_Flag1 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag1 == 1)//����������
	{
		if(KEY1 == 1)//̧�𰴼�
		{   
			if(Key_Cnt1 < 1.5)//С��1.5S�ǵ���
			{
				if(sys.Calibration)//�����У׼����ʱ
				{
					if(Cool_Temp.ADDMode)
					{
						sys.Calibration_Step++;//У׼����Ӽ�
						if(sys.Calibration_Step>1)//���У׼���ߴ���1
						{
							sys.Calibration = 0;//�ر�У׼
							sys.Calibration_Step = 0;//��������
							sys.TempOption_Mun = 0;//������λ������
							Calibration(sys.Calibration_Temp1,sys.Calibration_Temp2);//�¶�У׼����
							sys.Calibration_Temp1 = 260;
							sys.Calibration_Temp2 = 400;
							sys.SetMode_Option = 0;
						}
						Cool_Temp.ADDMode = 0;//�¶���ʾ����Ϊ0
					}
				}
				else
				{
					sys.SetMode_Option++;
					if(sys.SetMode_Option > 2)
						sys.SetMode_Option = 1;
					sys.TempOption_Mun = 0;
                    Heat_Temp.ADDMode = 0;//�¶ȴ�������
                    Cool_Temp.ADDMode = 0;//�¶ȴ�������
                    if(Time.Count_Start)//������ڼ�ʱ
                    {
                        Time.Count_Start = 0;//�ر�����ʱ
                        Time.Count_Time = 0;//�������ʱʱ��
                        Time.TimeDisplay_Flag = 0;//��ʾ����ʱ
                    }
                    else if(Time.CountDown_Start)//������ڵ���ʱ
                    {
                        Time.TimeDisplay_Flag = 0;//��ʾ����ʱ
                        Time.CountDown_Start = 0;//�رյ���ʱ
                        Time.Rel_Time = Time.Set_Time;//��ֵ
                    }
                    else
                    {
                        Time.TimeDisplay_Flag = 0;//��ʾ����ʱ
                        Time.CountDown_Start = 0;
                        Time.Count_Time = 0;//�������ʱʱ��
                        Time.Rel_Time = Time.Set_Time;//��ֵ
                    }
					Twinkle_Time = 5;//��˸5S
				}
			}
			Key_Flag1 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress1 = 0;//������־����
			Key_Cnt1 = 0;//��ť��������
		}
		if(Key_Cnt1 > 1.5 && Key_Cnt1 < 3.1)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress1 == 0)//���û��һֱһֱ������
			{
				/*У׼�¶�*/
				if(sys.Calibration == 0)//û����У׼����ʱ
				{
					sys.Calibration = 1;//����У׼����
					sys.Calibration_Step = 0;//У׼��������
					sys.Calibration_Temp1 = 260;//�����¶�һΪ26��
					sys.Calibration_Temp2 = 400;//�����¶ȶ�Ϊ40��
					sys.SetMode_Option = 4;//����ģʽΪ��
					sys.TempOption_Mun = 2;//�¶�λ��Ϊ���һλ
					Heat_Temp.ADDMode = 0;//�¶���ʾ����Ϊ0
					Cool_Temp.ADDMode = 0;//�¶���ʾ����Ϊ0
				}
				LongPress1 = 1;//������־��һ
			}
		}
	}
	/**************************************Time_Set��**************************************/
	if(KEY2 == 0)//���°���
	{
		if(sys.Calibration)
			return;
		if(LongPress2 == 0)//û�г�����
		{
			Key_Cnt2 += dT;//����ʱ��++
			Key_Flag2 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag2 == 1)//����������
	{
		if(KEY2 == 1)//̧�𰴼�
		{   
			if(Key_Cnt2 < 1.5)//С��1.5S�ǵ���
			{
				if(sys.SetMode_Option == 0)
				{
					sys.SetMode_Option = 3;//����ʱ��
					Twinkle_Time = 5;//��˸5S
				}
			}
			Key_Flag2 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress2 = 0;//������־����
			Key_Cnt2 = 0;//��ť��������
		}
		if(Key_Cnt2 > 1.5 && Key_Cnt2 < 3.1)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress2 == 0)//���û��һֱһֱ������
			{

				LongPress2 = 1;//������־��һ
			}
		}
	}
	
	/**************************************�Ӽ�**************************************/
	if(KEY3 == 0)//���°���
	{
		if(!sys.SetMode_Option)
			return;
		Key_Cnt3 += dT;//����ʱ��++
		Key_Flag3 = 1;//�������±�־��һ
	}
	if(Key_Flag3 == 1)//����������
	{
		if(KEY3 == 1)//̧�𰴼�
		{   
			if(Key_Cnt3 < 1.5)//С��1.5S�ǵ���
			{
				if(sys.SetMode_Option == 1)//���ü�������ʱ
				{
					if(sys.TempOption_Mun == 0)
						Heat_Temp.Set_Temp += 10;
					else if(sys.TempOption_Mun == 1)
						Heat_Temp.Set_Temp += 100;
					else if(sys.TempOption_Mun == 2)
						Heat_Temp.Set_Temp += 1;
					if(Heat_Temp.Set_Temp > 600)
						Heat_Temp.Set_Temp = 600;
					Twinkle_Time = 5;//��˸5S
					Key_Status = 2.0f;//����ʱ����1S
				}
				else if(sys.SetMode_Option == 2)//������������ʱ
				{
					if(sys.TempOption_Mun == 0)
						Cool_Temp.Set_Temp += 10;
					else if(sys.TempOption_Mun == 1)
						Cool_Temp.Set_Temp += 100;
					else if(sys.TempOption_Mun == 2)
						Cool_Temp.Set_Temp += 1;
					if(Cool_Temp.Set_Temp > 500)
						Cool_Temp.Set_Temp = 500;
					Twinkle_Time = 5;//��˸5S
					Key_Status = 2.0f;//����ʱ����1S
				}
				else if(sys.SetMode_Option == 3)//����ʱ��ʱ
				{
					if(sys.TimeOption_Mun == 0)
						Time.Set_Time += 60;
					else if(sys.TimeOption_Mun == 1)
						Time.Set_Time += 600;
					else if(sys.TimeOption_Mun == 2)
						Time.Set_Time += 1;
					else if(sys.TimeOption_Mun == 3)
						Time.Set_Time += 10;
					if(Time.Set_Time > 5999)//�������99��59��
						Time.Set_Time = 5999;
					Twinkle_Time = 5;//��˸5S
					Key_Status = 2.0f;//����ʱ����1S
				}
				else if(sys.SetMode_Option == 4)//����У׼�¶�
				{
					if(sys.Calibration_Step == 0)
					{
						if(sys.TempOption_Mun == 2)
							sys.Calibration_Temp1 += 1;
						if(sys.Calibration_Temp1 > 800)
							sys.Calibration_Temp1 = 800;
					}
					if(sys.Calibration_Step == 1)
					{
						if(sys.TempOption_Mun == 2)
							sys.Calibration_Temp2 += 1;
						if(sys.Calibration_Temp2 > 800)
							sys.Calibration_Temp2 = 800;
					}
					Key_Status = 2.0f;//����ʱ����1S
				}
			}
			Key_Flag3 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt3 = 0;//��ť��������		
			LongPress = 0;//��������
		}
		if(Key_Cnt3 > 2.0 && Key_Cnt3 < 2.5)//����ʱ�����2.0С��2.5��ʾ����
		{	
			if(sys.SetMode_Option > 0 && sys.SetMode_Option <= 2)//�����¶�ʱ
			{
				sys.TempOption_Mun++;//�¶�λ��++
				if(sys.TempOption_Mun > 2)
					sys.TempOption_Mun = 0;
				LongPress = 1;//��ʾ�����Ӽ�
				Twinkle_Time = 5;//��˸5S
			}
			if(sys.SetMode_Option == 3)//����ʱ��ʱ
			{
				sys.TimeOption_Mun++;//ʱ��λ��++
				if(sys.TimeOption_Mun > 3)
					sys.TimeOption_Mun = 0;
				LongPress = 1;//��ʾ�����Ӽ�
				Twinkle_Time = 5;//��˸5S
			}
			Key_Flag3 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt3 = 1.5;//��ť��������
		}
	}
	
	/**************************************����**************************************/
	if(KEY4 == 0)//���°���
	{
		if(!sys.SetMode_Option)
			return;
		Key_Cnt4 += dT;//����ʱ��++
		Key_Flag4 = 1;//�������±�־��һ
	}
	if(Key_Flag4 == 1)//����������
	{
		if(KEY4 == 1)//̧�𰴼�
		{   
			if(Key_Cnt4 < 1.5)//С��1.5S�ǵ���
			{
				if(sys.SetMode_Option == 1)//���ü�������ʱ
				{
					if(sys.TempOption_Mun == 0)
						Heat_Temp.Set_Temp -= 10;
					else if(sys.TempOption_Mun == 1)
						Heat_Temp.Set_Temp -= 100;
					else if(sys.TempOption_Mun == 2)
						Heat_Temp.Set_Temp -= 1;
					if(Heat_Temp.Set_Temp < 300)
						Heat_Temp.Set_Temp = 300;
					Twinkle_Time = 5;//��˸5S
					Key_Status = 2.0f;//����ʱ����1S
				}
				else if(sys.SetMode_Option == 2)//������������ʱ
				{
					if(sys.TempOption_Mun == 0)
						Cool_Temp.Set_Temp -= 10;
					else if(sys.TempOption_Mun == 1)
						Cool_Temp.Set_Temp -= 100;
					else if(sys.TempOption_Mun == 2)
						Cool_Temp.Set_Temp -= 1;
					if(Cool_Temp.Set_Temp < 200)
						Cool_Temp.Set_Temp = 200;
					Twinkle_Time = 5;//��˸5S
					Key_Status = 2.0f;//����ʱ����1S
				}
				else if(sys.SetMode_Option == 3)//����ʱ��ʱ
				{
					if(sys.TimeOption_Mun == 0)
						Time.Set_Time -= 60;
					else if(sys.TimeOption_Mun == 1)
						Time.Set_Time -= 600;
					else if(sys.TimeOption_Mun == 2)
						Time.Set_Time -= 1;
					else if(sys.TimeOption_Mun == 3)
						Time.Set_Time -= 10;
					if(Time.Set_Time < 1)//���С��1��
						Time.Set_Time = 1;
					Twinkle_Time = 5;//��˸5S
					Key_Status = 2.0f;//����ʱ����1S
				}
				else if(sys.SetMode_Option == 4)//����У׼�¶�
				{
					if(sys.Calibration_Step == 0)
					{
						if(sys.TempOption_Mun == 2)
							sys.Calibration_Temp1 -= 1;
						if(sys.Calibration_Temp1 < 200)
							sys.Calibration_Temp1 = 200;
					}
					if(sys.Calibration_Step == 1)
					{
						if(sys.TempOption_Mun == 2)
							sys.Calibration_Temp2 -= 1;
						if(sys.Calibration_Temp2 < 200)
							sys.Calibration_Temp2 = 200;
					}
					Key_Status = 2.0f;//����ʱ����1S
				}
			}
			Key_Flag4 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt4 = 0;//��ť��������		
			LongPress = 0;//��������
		}
		if(Key_Cnt4 > 2.0 && Key_Cnt4 < 2.5)//����ʱ�����2.0SС��2.5��ʾ����
		{	
			if(sys.SetMode_Option > 0 && sys.SetMode_Option <= 2)//�����¶�ʱ
			{
				if(sys.TempOption_Mun)
					sys.TempOption_Mun--;//�¶�λ��--
				else
					sys.TempOption_Mun = 2;
				LongPress = 1;//��ʾ�����Ӽ�
				Twinkle_Time = 5;//��˸5S
			}
			if(sys.SetMode_Option == 3)//����ʱ��ʱ
			{
				if(sys.TimeOption_Mun)
					sys.TimeOption_Mun--;//�¶�λ��--
				else
					sys.TimeOption_Mun = 3;
				LongPress = 1;//��ʾ�����Ӽ�
				Twinkle_Time = 5;//��˸5S
			}
			Key_Flag4 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt4 = 1.5;//��ť��������
		}
	}
	
	/**************************************Count��**************************************/
	if(KEY5 == 0)//���°���
	{
		if(Heat_Temp.ADDMode == 0 || Cool_Temp.ADDMode == 0 || sys.Calibration == 1 || sys.SetMode_Option)
			return;
		if(LongPress5 == 0)//û�г�����
		{
			Key_Cnt5 += dT;//����ʱ��++
			Key_Flag5 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag5 == 1)//����������
	{
		if(KEY5 == 1)//̧�𰴼�
		{   
			if(Key_Cnt5 < 1.5)/*����*///С��1.5S�ǵ���
			{
				if(Time.CountDown_Start)//�������ʱҲ������
				{
					Time.CountDown_Start = 0;//�رյ���ʱ
					Time.Rel_Time = Time.Set_Time;//��ֵ
					Time.TimeDisplay_Flag = 0;//��ʾ����ʱ
				}
				else if(Time.Count_Start)//�������ʱ����
				{
					Time.Count_Start = 0;//�ر�����ʱ
					Time.Count_Time = 0;//�������ʱʱ��
					Time.TimeDisplay_Flag = 0;//��ʾ����ʱ
				}
				else//�������ʱû������
				{
					Time.TimeDisplay_Flag = 1;//��ʾ����ʱ
					Time.Count_Start = 1;//������ʱ
					Beep_Time = 0.2;//��������0.2S
				}
				Twinkle_Time = 0;//��˸5S
                Key_Status = 0.0f;//����ʱ����1S
                SetOK_Flag = 1;
			}
			Key_Flag5 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress5 = 0;//������־����
			Key_Cnt5 = 0;//��ť��������		
		}
		if(Key_Cnt5 > 1.5 && Key_Cnt5 < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress5 == 0)/*����*///���û��һֱһֱ������
			{
				Beep_Time = 0.1;//��������0.1S
				LongPress5 = 1;//������־��һ
			}
		}
	}
	
	/**************************************CountDown��**************************************/
	if(KEY6 == 0)//���°���
	{
		if(Heat_Temp.ADDMode == 0 || Cool_Temp.ADDMode == 0 || sys.Calibration == 1 || sys.SetMode_Option)
			return;
		if(LongPress6 == 0)//û�г�����
		{
			Key_Cnt6 += dT;//����ʱ��++
			Key_Flag6 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag6 == 1)//����������
	{
		if(KEY6 == 1)//̧�𰴼�
		{   
			if(Key_Cnt6 < 1.5)/*����*///С��1.5S�ǵ���
			{
				if(Time.Count_Start)//������ڼ�ʱ
				{
					Time.Count_Start = 0;//�ر�����ʱ
					Time.Count_Time = 0;//�������ʱʱ��
					Time.TimeDisplay_Flag = 0;//��ʾ����ʱ
				}
				else if(Time.CountDown_Start)//������ڵ���ʱ
				{
					Time.TimeDisplay_Flag = 0;//��ʾ����ʱ
					Time.CountDown_Start = 0;//�رյ���ʱ
					Time.Rel_Time = Time.Set_Time;//��ֵ
				}
				else
				{
					Time.TimeDisplay_Flag = 0;//��ʾ����ʱ
					Time.CountDown_Start = 1;
					Beep_Time = 0.2;//��������0.2S
				}
                Twinkle_Time = 0;//��˸5S
                Key_Status = 0.0f;//����ʱ����1S
                SetOK_Flag = 1;
                sys.SetMode_Option = 0;//ģʽѡ������
			}
			Key_Flag6 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress6 = 0;//������־����
			Key_Cnt6 = 0;//��ť��������				
		}
		if(Key_Cnt6 > 1.5 && Key_Cnt6 < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress6 == 0)/*����*///���û��һֱһֱ������
			{
				Beep_Time = 0.1;//��������0.1S
				LongPress6 = 1;//������־��һ
			}
		}
	}
}
