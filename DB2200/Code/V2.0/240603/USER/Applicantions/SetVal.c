#include "SetVal.h"

/**********ȫ�ֱ�������******/
uint8_t SetOK_Flag,CtrlMode;//����Ƿ��°���

/*
*****************************************************************
 * ����ԭ�ͣ� void Check_Set(void)
 * ��    �ܣ� �������
*****************************************************************
*/
void Check_Set(void)
{
    if(Key_Status != 0)
    {
        SetOK_Flag = 1;//��⵽������ť���ȴ��˳�����ģʽ
    }
    if(SetOK_Flag == 1)
    {
		if(sys.SetMode_Option == 0)//���趨�ú�
		{    
			if(PMode_Status == 1)
			{
				Param.P_Param[PMode_Option][1] = Set_Time;
				Param.P_Param[PMode_Option][0] = Set_Temp;
				Param_Save();
			}
			if(Ctrl_Temp != Set_Temp)//�жϿ����ٶȺ��趨�ٶ��ǲ��ǲ�һ��
			{
				Ctrl_Temp = Set_Temp;//���趨�ٶȸ�ֵ�������ٶ�
				if(Temp_ADDMode != 0)//���繤λֻ�������������������ٶȵ�����²�����0������δ����ģʽ��
					Temp_ADDMode = 0;//����δ�����жϼ��ٻ��Ǽ���
				Param.P_Param[PMode_Option][0] = Set_Temp;
				Param_Save();
			}          
			if(Ctrl_Time != Set_Time)//ʵ��ʱ�䲻�����趨ʱ��
			{
				Ctrl_Time = Set_Time;//���趨ʱ�丳ֵ������ʱ��
				Param.P_Param[PMode_Option][1] = Set_Time;
				Time = Set_Time;
				Param_Save();
			}  
			if(Set_Time > 0)
				Time_State = 0;
			else
				Time_State = 1;
			SetOK_Flag = 0;
		}
    }
}

void Check_CtrlTemp_Mode(void)
{
	if(CtrlMode == 1)
	{
		if(Ctrl_Temp > Rel_Temp)
		{
			sys.CtrlTemp_Mode = 1;
		}
		else
		{
			sys.CtrlTemp_Mode = 2;
		}
		CtrlMode = 0;
	}
}
