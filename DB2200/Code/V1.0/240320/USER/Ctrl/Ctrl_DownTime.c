#include "Ctrl_DownTime.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void Cheak_TimeDown(uint16_t dT)
 * ��    �ܣ�ʱ�䵹��ʱ���
 * ��    ��: dT:ִ������
 * ��    ����uint16_t dT
*****************************************************************
*/
void Cheak_TimeDown(uint16_t dT)
{
    static uint16_t T;
	if(sys.Run_Status == 1)
	{
		if(DownTime_Over ==1)//����ʱ����
		{   	
			if(PMode_Status == 2)
			{
				PMode_Option++;
				if(PMode_Option <= PMode_P2)
				{
					Flash_Read((uint8_t *)(&Param),sizeof(Param));
					Set_Time=Param.P_Param[PMode_Option][1];//���������趨ʱ��Ϊ20min
					Ctrl_Time=Param.P_Param[PMode_Option][1];//��������ʵ��ʱ��Ϊ20min
					Set_Temp=Param.P_Param[PMode_Option][0];//���������趨�¶�37��
					sys.DownTime_Status = 0;//�ر�
					DownTime_Over = 0;
					sys.SetMode_Option = 0;
					sys.SetP_Mode_Option = 0;
					Temp_ADDMode= 0;
					SetOK_Flag = 1;
					CtrlMode = 1;
				}
				else
				{
					PMode_Option = PMode_P1;
					Flash_Read((uint8_t *)(&Param),sizeof(Param));
					Set_Time=Param.P_Param[PMode_Option][1];//���������趨ʱ��Ϊ20min
					Ctrl_Time=Param.P_Param[PMode_Option][1];//��������ʵ��ʱ��Ϊ20min
					Set_Temp=Param.P_Param[PMode_Option][0];//���������趨�¶�37��
					SetOK_Flag = 1;	
					PMode_Mode = 1;//�ݶ�ģʽ
					sys.CtrlTemp_Mode = 0;
					sys.Run_Status = 0;
					Beep_Flash = 5;
				}
			}
			else
			{		
				Ctrl_Time = Time;				
				sys.DownTime_Status = 0;//�ر�
				sys.Run_Status = 0;//�ر�
				Beep_Flash = 5;
			}
		}
		if(sys.DownTime_Status)//��������ʱ
		{
			T += dT;
			if(T == 1000)//1S
			{
				if(Time_State == 0 && DownTime_Over == 0 && Ctrl_Time)//���ʵ��ʱ����ʾ�͵���ʱû�н����ı�־����
				{
					if(Ctrl_Time)
						Ctrl_Time--;//����ʱ��--
					if(Ctrl_Time == 0)
					{
						DownTime_Over = 1;//time1����ʱ����
					}
				}
				T = 0;//��������
			}    
		}
	}
	else
	{
		DownTime_Over = 0;//��ʱ���־����
		sys.DownTime_Status = 0;//�ر�
	}
}
