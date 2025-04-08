#include "Drv_KEY.h"

/**********ȫ�ֱ���**********/
uint8_t Key_Status;//�ڲ�������ʱ

/**********�ֲ���������******/
float Key_Cnt1,Key_Cnt2,Key_Cnt3,Key_Cnt4,Key_Cnt5;//����ʱ��
uint8_t Key_Flag1,Key_Flag2,Key_Flag3,Key_Flag4,Key_Flag5;//�������±�־
uint8_t LongPress1,LongPress2,LongPress3,LongPress4,LongPress5;//����������־

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

/*
*****************************************************************
 * ����ԭ�ͣ�void Key_Scan(float dT)
 * ��    �ܣ�����ɨ��
*****************************************************************
*/
void Key_Scan(float dT)
{
	/**************************************MENU��**************************************/
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
				if(sys.Run_Status)
				{
					Beep_Flash = 2;//��Ч����ʱ���������εΡ�
				}
				else
				{
					if(PMode_Mode == 0)
					{
						if(PMode_Status == 1)
						{
							sys.SetMode_Option++;//����ѡ���л�
							if(sys.SetMode_Option > 3)//���¶Ⱥ�ʱ������ѡ��
							{
								sys.SetMode_Option = 0;//����������    
							}
						}
						else
						{
							sys.SetMode_Option++;//����ѡ���л�
							if(sys.SetMode_Option == 1)//���¶Ⱥ�ʱ������ѡ��
							{
								sys.SetMode_Option = 2;//����������    
							}
							if(sys.SetMode_Option > 3)//���¶Ⱥ�ʱ������ѡ��
							{
								sys.SetMode_Option = 0;//����������    
							}
						}
                        Twinkle_Time = 6000;//��˸ʱ��6S
                        Beep_Time = 0.1;//��������0.1S
					}
					else
					{
						sys.SetP_Mode_Option++;
						if(sys.SetP_Mode_Option > 2)//��P1��P1���л�ѡ��
						{
							sys.SetP_Mode_Option = 0;//����������   
							PMode_Option = PMode_P1;
							Flash_Read((uint8_t *)(&Param),sizeof(Param));
							Set_Time=Param.P_Param[PMode_Option][1];//���������趨ʱ��Ϊ20min
							Ctrl_Time=Param.P_Param[PMode_Option][1];//��������ʵ��ʱ��Ϊ20min
							Set_Temp=Param.P_Param[PMode_Option][0];//���������趨�¶�37��
							Ctrl_Temp = Set_Temp;		
							if(Set_Time > 0)
								Time_State = 0;
							else
								Time_State = 1;				
						}
						if(sys.SetP_Mode_Option == 1)//����P1
						{
							PMode_Option = PMode_P1;
							Flash_Read((uint8_t *)(&Param),sizeof(Param));
							Set_Time=Param.P_Param[PMode_Option][1];//���������趨ʱ��Ϊ20min
							Ctrl_Time=Param.P_Param[PMode_Option][1];//��������ʵ��ʱ��Ϊ20min
							Set_Temp=Param.P_Param[PMode_Option][0];//���������趨�¶�37��
							Ctrl_Temp = Set_Temp;
							if(Set_Time > 0)
								Time_State = 0;
							else
								Time_State = 1;
						}
						else if(sys.SetP_Mode_Option == 2)//����P2
						{
							PMode_Option = PMode_P2;
							Flash_Read((uint8_t *)(&Param),sizeof(Param));
							Set_Time=Param.P_Param[PMode_Option][1];//���������趨ʱ��Ϊ20min
							Ctrl_Time=Param.P_Param[PMode_Option][1];//��������ʵ��ʱ��Ϊ20min
							Set_Temp=Param.P_Param[PMode_Option][0];//���������趨�¶�37��
							Ctrl_Temp = Set_Temp;
							if(Set_Time > 0)
								Time_State = 0;
							else
								Time_State = 1;
						}
                        Twinkle_Time = 6000;//��˸ʱ��6S
                        Beep_Time = 0.1;//��������0.1S
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

	/**************************************�Ӽ�**************************************/
	if(!Key2)//���°���
	{
		Key_Cnt2 += dT;//����ʱ��++
		Key_Flag2 = 1;//�������±�־��һ
	}
	if(Key_Flag2 == 1)//����������
	{
		if(Key2)//̧�𰴼�
		{   
			if(Key_Cnt2 > 0.05f && Key_Cnt2 < 1.5)//����ʱ�����0.05SС��1.5S�ǵ���
			{
				if(sys.Run_Status)
				{
					Beep_Flash = 2;//��Ч����ʱ���������εΡ�
				}
				else
				{
					if(sys.SetMode_Option == 2)//�������¶�ѡ��
					{
						Set_Temp++;//�¶�++��
						if(Set_Temp > 1000)//����趨�¶���100��
							Set_Temp = 1000;
                        Key_Status = 1;//��������ʱ����˸��2s����˸
                        Twinkle_Time = 6000;//��˸ʱ��6S
					}
					else if(sys.SetMode_Option == 3)//������ʱ��ѡ��
					{
						if(Time_Unit == 0)//���뵥λģʽ��
						{
							Set_Time += 5;//ʱ���5s
							Time_State = 0;//ʱ���˳���ʾ��----��
						}
						else//�ڷֵ�λģʽ��
							Set_Time += 60;//ʱ���60s
						if(Set_Time > 86399)//��߿ɶ�ʱ23.99Сʱ
							Set_Time = 86399;
                        Key_Status = 1;//��������ʱ����˸��2s����˸
                        Twinkle_Time = 6000;//��˸ʱ��6S
					}
					else if(sys.SetMode_Option == 1)
					{
						PMode_Option++;
						if(PMode_Option > 9)
							PMode_Option = 9;
						Flash_Read((uint8_t *)(&Param),sizeof(Param));
						Set_Temp=Param.P_Param[PMode_Option][0];//���������趨�¶�37��
						Ctrl_Temp = Set_Temp;
						Set_Time=Param.P_Param[PMode_Option][1];//���������趨ʱ��Ϊ20min
						Ctrl_Time=Param.P_Param[PMode_Option][1];//��������ʵ��ʱ��Ϊ20min
						if(Set_Time > 0)
							Time_State = 0;
						else
							Time_State = 1;
                        Key_Status = 1;//��������ʱ����˸��2s����˸
                        Twinkle_Time = 6000;//��˸ʱ��6S
					}
					else if(sys.SetP_Mode_Option == 1)//����P1
					{
						PMode_P1++;
						if(PMode_P1 > 9)
							PMode_P1 = 9;
						PMode_Option = PMode_P1;
						Flash_Read((uint8_t *)(&Param),sizeof(Param));
						Set_Time=Param.P_Param[PMode_Option][1];//���������趨ʱ��Ϊ20min
						Ctrl_Time=Param.P_Param[PMode_Option][1];//��������ʵ��ʱ��Ϊ20min
						Set_Temp=Param.P_Param[PMode_Option][0];//���������趨�¶�37��
						Ctrl_Temp = Set_Temp;
						if(Set_Time > 0)
							Time_State = 0;
						else
							Time_State = 1;
                        Key_Status = 1;//��������ʱ����˸��2s����˸
                        Twinkle_Time = 6000;//��˸ʱ��6S
					}
					else if(sys.SetP_Mode_Option == 2)//����P2
					{
						PMode_P2++;
						if(PMode_P2 > 9)
							PMode_P2 = 9;
						PMode_Option = PMode_P2;
						Flash_Read((uint8_t *)(&Param),sizeof(Param));
						Set_Time=Param.P_Param[PMode_Option][1];//���������趨ʱ��Ϊ20min
						Ctrl_Time=Param.P_Param[PMode_Option][1];//��������ʵ��ʱ��Ϊ20min
						Set_Temp=Param.P_Param[PMode_Option][0];//���������趨�¶�37��
						Ctrl_Temp = Set_Temp;
						if(Set_Time > 0)
							Time_State = 0;
						else
							Time_State = 1;
                        Key_Status = 1;//��������ʱ����˸��2s����˸
                        Twinkle_Time = 6000;//��˸ʱ��6S
					}
					else
					{
						Beep_Flash = 2;//��Ч����ʱ���������εΡ�
					}
                }
			}
			Key_Flag2 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt2 = 0;//��ť��������		
		}
		if(Key_Cnt2 > 1.9 && Key_Cnt2 < 2.1)//����ʱ�����1.9SС��2.1S��ʾ����
		{
			if(sys.Run_Status)
			{
				Beep_Flash = 2;//��Ч����ʱ���������εΡ�
			}
			else
			{
				if(sys.SetMode_Option == 2)//�������¶�ѡ��
				{
					Set_Temp++;//�¶�++��
					if(Set_Temp > 1000)//����趨�¶���100��
						Set_Temp = 1000;
                    Key_Status = 1;//��������ʱ����˸��2s����˸
                    Twinkle_Time = 6000;//��˸ʱ��6S
				}
				else if(sys.SetMode_Option == 3)//������ʱ��ѡ��
				{
					if(Time_Unit == 0)//���뵥λģʽ��
					{
						Set_Time += 5;//ʱ���5s
						Time_State = 0;//ʱ���˳���ʾ��----��
					}
					else//�ڷֵ�λģʽ��
						Set_Time += 60;//ʱ���60s
					if(Set_Time > 86399)//��߿ɶ�ʱ23.99Сʱ
						Set_Time = 86399;
                    Key_Status = 1;//��������ʱ����˸��2s����˸
                    Twinkle_Time = 6000;//��˸ʱ��6S
				}
				else if(sys.SetMode_Option == 1)
				{
					PMode_Option++;
					if(PMode_Option > 9)
						PMode_Option = 9;
					Flash_Read((uint8_t *)(&Param),sizeof(Param));
					Set_Temp=Param.P_Param[PMode_Option][0];//���������趨�¶�37��
					Ctrl_Temp = Set_Temp;
					Set_Time=Param.P_Param[PMode_Option][1];//���������趨ʱ��Ϊ20min
					Ctrl_Time=Param.P_Param[PMode_Option][1];//��������ʵ��ʱ��Ϊ20min
					if(Set_Time > 0)
						Time_State = 0;
					else
						Time_State = 1;
                    Key_Status = 1;//��������ʱ����˸��2s����˸
                    Twinkle_Time = 6000;//��˸ʱ��6S
				}
				else if(sys.SetP_Mode_Option == 1)//����P1
				{
					PMode_P1++;
					if(PMode_P1 > 9)
						PMode_P1 = 9;
					PMode_Option = PMode_P1;
					Flash_Read((uint8_t *)(&Param),sizeof(Param));
					Set_Time=Param.P_Param[PMode_Option][1];//���������趨ʱ��Ϊ20min
					Ctrl_Time=Param.P_Param[PMode_Option][1];//��������ʵ��ʱ��Ϊ20min
					Set_Temp=Param.P_Param[PMode_Option][0];//���������趨�¶�37��
					Ctrl_Temp = Set_Temp;
					if(Set_Time > 0)
						Time_State = 0;
					else
						Time_State = 1;
                    Key_Status = 1;//��������ʱ����˸��2s����˸
                    Twinkle_Time = 6000;//��˸ʱ��6S
				}
				else if(sys.SetP_Mode_Option == 2)//����P2
				{
					PMode_P2++;
					if(PMode_P2 > 9)
						PMode_P2 = 9;
					PMode_Option = PMode_P2;
					Flash_Read((uint8_t *)(&Param),sizeof(Param));
					Set_Time=Param.P_Param[PMode_Option][1];//���������趨ʱ��Ϊ20min
					Ctrl_Time=Param.P_Param[PMode_Option][1];//��������ʵ��ʱ��Ϊ20min
					Set_Temp=Param.P_Param[PMode_Option][0];//���������趨�¶�37��
					Ctrl_Temp = Set_Temp;
					if(Set_Time > 0)
						Time_State = 0;
					else
						Time_State = 1;
                    Key_Status = 1;//��������ʱ����˸��2s����˸
                    Twinkle_Time = 6000;//��˸ʱ��6S
				}
				else
				{
					Beep_Flash = 2;//��Ч����ʱ���������εΡ�
				}
			}
			Key_Flag2 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt2 = 1.88f;//��ť��������
		}
	}

	/**************************************����**************************************/
	if(!Key3)//���°���
	{
		Key_Cnt3 += dT;//����ʱ��++
		Key_Flag3 = 1;//�������±�־��һ
	}
	if(Key_Flag3 == 1)//����������
	{
		if(Key3)//̧�𰴼�
		{   
			if(Key_Cnt3 > 0.05f && Key_Cnt3 < 1.5)//����ʱ�����0.05SС��1.5S�ǵ���
			{
				if(sys.Run_Status)
				{
					Beep_Flash = 2;//��Ч����ʱ���������εΡ�
				}
				else
				{
					if(sys.SetMode_Option == 2)//�������¶�ѡ��
					{
						Set_Temp--;//�¶�--��
						if(Set_Temp < -50)//����趨�¶�С��0ʱ��������ֻ���Զ����£�
						{
							Set_Temp = -50;//���趨�¶ȱ�����0
						}
                        Key_Status = 1;//��������ʱ����˸��2s����˸
                        Twinkle_Time = 6000;//��˸ʱ��6S
					}
					else if(sys.SetMode_Option == 3)//������ʱ��ѡ��
					{
						if(Time_Unit == 0)//���뵥λģʽ��
						{
							if(Set_Time)
								Set_Time -= 5;//ʱ���5s
							if(Set_Time < 5)//С��5s���趨ֵʱ
							{
								Set_Time = 0;
								Time_State = 1;//ʱ����ʾ��----��
							}   
						}
						else//�ڷ�Ϊ��λ��ģʽ��
							Set_Time -= 60;//ʱ���1����
                        Key_Status = 1;//��������ʱ����˸��2s����˸
                        Twinkle_Time = 6000;//��˸ʱ��6S
					}
					else if(sys.SetMode_Option == 1)
					{
						PMode_Option--;
						if(PMode_Option < 1)
							PMode_Option = 1;
						Flash_Read((uint8_t *)(&Param),sizeof(Param));
						Set_Time=Param.P_Param[PMode_Option][1];//���������趨ʱ��Ϊ20min
						Ctrl_Time=Param.P_Param[PMode_Option][1];//��������ʵ��ʱ��Ϊ20min
						Set_Temp=Param.P_Param[PMode_Option][0];//���������趨�¶�37��
						Ctrl_Temp = Set_Temp;
						if(Set_Time > 0)
							Time_State = 0;
						else
							Time_State = 1;
                        Key_Status = 1;//��������ʱ����˸��2s����˸
                        Twinkle_Time = 6000;//��˸ʱ��6S
					}
					else if(sys.SetP_Mode_Option == 1)//����P1
					{
						PMode_P1--;
						if(PMode_P1 < 1)
							PMode_P1 = 1;
						PMode_Option = PMode_P1;
						Flash_Read((uint8_t *)(&Param),sizeof(Param));
						Set_Time=Param.P_Param[PMode_Option][1];//���������趨ʱ��Ϊ20min
						Ctrl_Time=Param.P_Param[PMode_Option][1];//��������ʵ��ʱ��Ϊ20min
						Set_Temp=Param.P_Param[PMode_Option][0];//���������趨�¶�37��
						Ctrl_Temp = Set_Temp;
						if(Set_Time > 0)
							Time_State = 0;
						else
							Time_State = 1;
                        Key_Status = 1;//��������ʱ����˸��2s����˸
                        Twinkle_Time = 6000;//��˸ʱ��6S
					}
					else if(sys.SetP_Mode_Option == 2)//����P2
					{
						PMode_P2--;
						if(PMode_P2 < 1)
							PMode_P2 = 1;
						PMode_Option = PMode_P2;
						Flash_Read((uint8_t *)(&Param),sizeof(Param));
						Set_Time=Param.P_Param[PMode_Option][1];//���������趨ʱ��Ϊ20min
						Ctrl_Time=Param.P_Param[PMode_Option][1];//��������ʵ��ʱ��Ϊ20min
						Set_Temp=Param.P_Param[PMode_Option][0];//���������趨�¶�37��
						Ctrl_Temp = Set_Temp;
						if(Set_Time > 0)
							Time_State = 0;
						else
							Time_State = 1;
                        Key_Status = 1;//��������ʱ����˸��2s����˸
                        Twinkle_Time = 6000;//��˸ʱ��6S
					}
					else
					{
						Beep_Flash = 2;//��Ч����ʱ���������εΡ�
					}
				}
			}
			Key_Flag3 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt3 = 0;//��ť��������		
		}
		if(Key_Cnt3 > 1.9 && Key_Cnt3 < 2.1)//����ʱ�����1.9SС��2.1S��ʾ����
		{
			if(sys.Run_Status)
			{
				Beep_Flash = 2;//��Ч����ʱ���������εΡ�
			}
			else
			{
				if(sys.SetMode_Option == 2)//�������¶�ѡ��
				{
					Set_Temp--;//�¶�--��
					if(Set_Temp < -50)//����趨�¶�С��0ʱ��������ֻ���Զ����£�
					{
						Set_Temp = -50;//���趨�¶ȱ�����0
					}
                    Key_Status = 1;//��������ʱ����˸��2s����˸
                    Twinkle_Time = 6000;//��˸ʱ��6S
				}
				else if(sys.SetMode_Option == 3)//������ʱ��ѡ��
				{
					if(Time_Unit == 0)//���뵥λģʽ��
					{
						if(Set_Time)
							Set_Time -= 5;//ʱ���5s
						if(Set_Time < 5)//С��5s���趨ֵʱ
						{
							Set_Time = 0;
							Time_State = 1;//ʱ����ʾ��----��
						}   
					}
					else//�ڷ�Ϊ��λ��ģʽ��
						Set_Time -= 60;//ʱ���1����
                    Key_Status = 1;//��������ʱ����˸��2s����˸
                    Twinkle_Time = 6000;//��˸ʱ��6S
				}
				else if(sys.SetMode_Option == 1)
				{
					PMode_Option--;
					if(PMode_Option < 1)
						PMode_Option = 1;
					Flash_Read((uint8_t *)(&Param),sizeof(Param));
					Set_Time=Param.P_Param[PMode_Option][1];//���������趨ʱ��Ϊ20min
					Ctrl_Time=Param.P_Param[PMode_Option][1];//��������ʵ��ʱ��Ϊ20min
					Set_Temp=Param.P_Param[PMode_Option][0];//���������趨�¶�37��
					Ctrl_Temp = Set_Temp;
					if(Set_Time > 0)
						Time_State = 0;
					else
						Time_State = 1;
                    Key_Status = 1;//��������ʱ����˸��2s����˸
                    Twinkle_Time = 6000;//��˸ʱ��6S
				}
				else if(sys.SetP_Mode_Option == 1)//����P1
				{
					PMode_P1--;
					if(PMode_P1 < 1)
						PMode_P1 = 1;
					PMode_Option = PMode_P1;
					Flash_Read((uint8_t *)(&Param),sizeof(Param));
					Set_Time=Param.P_Param[PMode_Option][1];//���������趨ʱ��Ϊ20min
					Ctrl_Time=Param.P_Param[PMode_Option][1];//��������ʵ��ʱ��Ϊ20min
					Set_Temp=Param.P_Param[PMode_Option][0];//���������趨�¶�37��
					Ctrl_Temp = Set_Temp;
					if(Set_Time > 0)
						Time_State = 0;
					else
						Time_State = 1;
                    Key_Status = 1;//��������ʱ����˸��2s����˸
                    Twinkle_Time = 6000;//��˸ʱ��6S
				}
				else if(sys.SetP_Mode_Option == 2)//����P2
				{
					PMode_P2--;
					if(PMode_P2 < 1)
						PMode_P2 = 1;
					PMode_Option = PMode_P2;
					Flash_Read((uint8_t *)(&Param),sizeof(Param));
					Set_Time=Param.P_Param[PMode_Option][1];//���������趨ʱ��Ϊ20min
					Ctrl_Time=Param.P_Param[PMode_Option][1];//��������ʵ��ʱ��Ϊ20min
					Set_Temp=Param.P_Param[PMode_Option][0];//���������趨�¶�37��
					Ctrl_Temp = Set_Temp;
					if(Set_Time > 0)
						Time_State = 0;
					else
						Time_State = 1;
                    Key_Status = 1;//��������ʱ����˸��2s����˸
                    Twinkle_Time = 6000;//��˸ʱ��6S
				}
				else
				{
					Beep_Flash = 2;//��Ч����ʱ���������εΡ�
				}
			}
			Key_Flag3 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt3 = 1.88f;//��ť��������
		}
	} 

	/**************************************Start��**************************************/
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
				if(sys.Run_Status == 1)
				{
					sys.Run_Status = 0;
					Ctrl_Time = Time;
					if(PMode_Status == 2)
					{
						PMode_Mode = 1;//�ݶ�ģʽ
						PMode_Option = PMode_P1;
						Flash_Read((uint8_t *)(&Param),sizeof(Param));
						Set_Time=Param.P_Param[PMode_Option][1];//���������趨ʱ��Ϊ20min
						Ctrl_Time=Param.P_Param[PMode_Option][1];//��������ʵ��ʱ��Ϊ20min
						Set_Temp=Param.P_Param[PMode_Option][0];//���������趨�¶�37��
						Ctrl_Temp = Set_Temp;
						if(Set_Time > 0)
							Time_State = 0;
						else
							Time_State = 1;
						SetOK_Flag = 1;
					}
					SetOK_Flag = 1;
				}
				else
				{
					sys.Run_Status = 1;
					sys.SetMode_Option = 0;
					sys.SetP_Mode_Option = 0;
					Temp_ADDMode= 0;
					CtrlMode = 1;
					Time = Set_Time;
					if(PMode_Status == 2)
					{
						PMode_Option = PMode_P1;
						Flash_Read((uint8_t *)(&Param),sizeof(Param));
						Set_Time=Param.P_Param[PMode_Option][1];//���������趨ʱ��Ϊ20min
						Ctrl_Time=Param.P_Param[PMode_Option][1];//��������ʵ��ʱ��Ϊ20min
						Set_Temp=Param.P_Param[PMode_Option][0];//���������趨�¶�37��
						Ctrl_Temp = Set_Temp;
						if(Set_Time > 0)
							Time_State = 0;
						else
							Time_State = 1;
					}
					SetOK_Flag = 1;
					if(PMode_P1 > PMode_P2)
					{
						sys.Run_Status = 0;
						if(Beep_Flash == 0)
							Beep_Flash = 5;
					}
				}
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
                Beep_Flash = 2;//��Ч����ʱ���������εΡ�
				LongPress4 = 1;//������־��һ
			}
		}
	}
	/**************************************P��******************************************/
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
				if(sys.Run_Status)
				{
					Beep_Flash = 2;//��Ч����ʱ���������εΡ�
				}
				else
				{
					if(PMode_Status == 0)
					{
						if(PMode_Mode == 0)
						{
							PMode_Status = 1;
							PMode_Option = 1;
							sys.SetMode_Option = 1;
							Flash_Read((uint8_t *)(&Param),sizeof(Param));
							Set_Time=Param.P_Param[PMode_Option][1];//���������趨ʱ��Ϊ20min
							Ctrl_Time=Param.P_Param[PMode_Option][1];//��������ʵ��ʱ��Ϊ20min
							Set_Temp=Param.P_Param[PMode_Option][0];//���������趨�¶�37��
							Ctrl_Temp = Set_Temp;
							if(Set_Time > 0)
								Time_State = 0;
							else
								Time_State = 1;
							Twinkle_Time = 6000;//��˸ʱ��6S
						}
					}
					else
					{
						if(PMode_Mode == 0)
						{
							PMode_Status = 0;
							PMode_Option = 0;
							sys.SetMode_Option = 0;
							Flash_Read((uint8_t *)(&Param),sizeof(Param));
							Set_Time=Param.P_Param[PMode_Option][1];//���������趨ʱ��Ϊ20min
							Ctrl_Time=Param.P_Param[PMode_Option][1];//��������ʵ��ʱ��Ϊ20min
							Set_Temp=Param.P_Param[PMode_Option][0];//���������趨�¶�37��
							Ctrl_Temp = Set_Temp;
							if(Set_Time > 0)
								Time_State = 0;
							else
								Time_State = 1;
							
						}
					}
					Beep_Time = 0.1;//��������0.1S
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
				if(sys.Run_Status)
				{
					Beep_Flash = 2;//��Ч����ʱ���������εΡ�
				}
				else
				{
					if(PMode_Mode == 0)
					{
						PMode_Mode = 1;//�ݶ�ģʽ
						PMode_Status = 2;//�ݶ�ģʽ
						PMode_P1 = 1;
						PMode_P2 = 1;
						PMode_Option = PMode_P1;
						Circle_Run = 1;
						sys.SetMode_Option = 0;
						sys.SetP_Mode_Option = 1;
						Flash_Read((uint8_t *)(&Param),sizeof(Param));
						Set_Time=Param.P_Param[PMode_Option][1];//���������趨ʱ��Ϊ20min
						Ctrl_Time=Param.P_Param[PMode_Option][1];//��������ʵ��ʱ��Ϊ20min
						Set_Temp=Param.P_Param[PMode_Option][0];//���������趨�¶�37��
						Ctrl_Temp = Set_Temp;
						if(Set_Time > 0)
								Time_State = 0;
							else
								Time_State = 1;
						Twinkle_Time = 6000;//��˸ʱ��6S
					}
					else
					{
						PMode_Mode = 0;//�ݶ�ģʽ
						PMode_Status = 1;//����ģʽ
						PMode_Option = 1;
						Circle_Run = 0;
						sys.SetMode_Option = 1;
						sys.SetP_Mode_Option = 0;
						Flash_Read((uint8_t *)(&Param),sizeof(Param));
						Set_Time=Param.P_Param[PMode_Option][1];//���������趨ʱ��Ϊ20min
						Ctrl_Time=Param.P_Param[PMode_Option][1];//��������ʵ��ʱ��Ϊ20min
						Set_Temp=Param.P_Param[PMode_Option][0];//���������趨�¶�37��
						Ctrl_Temp = Set_Temp;
						if(Set_Time > 0)
							Time_State = 0;
						else
							Time_State = 1;
						Twinkle_Time = 6000;//��˸ʱ��6S
					}
					Beep_Time = 0.1;//��������0.1S
				}
				LongPress5 = 1;//������־��һ
			}
		}
	}
}
