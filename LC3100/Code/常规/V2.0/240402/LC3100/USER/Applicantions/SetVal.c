#include "SetVal.h"

/**********ȫ�ֱ�������******/
uint8_t SetOK_Flag;//����Ƿ��°���
 
/*
*****************************************************************
 * ����ԭ�ͣ�void Check_Set(float dT)
 * ��    �ܣ��������
*****************************************************************
*/
void Check_Set(float dT)
{
    if(Key_Status != 0)
    {
        SetOK_Flag = 1;//��⵽������ť���ȴ��˳�����ģʽ
    }
    if(SetOK_Flag == 1)
    {
		if(sys.SetMode_Option == 0)//���趨�ú�
		{    
			if(Ctrl_Speed != Set_Speed)//�жϿ����ٶȺ��趨�ٶ��ǲ��ǲ�һ��
			{
				Ctrl_Speed = Set_Speed;//���趨�ٶȸ�ֵ�������ٶ�
				if(Speed_Unit == 0)
					Param.P_Param[PMode_Option][1] = Set_Speed;//ת��
				else
					Param.P_Param[PMode_Option][3] = Set_Speed;//������
			}          
			if(Ctrl_Time != Set_Time)//ʵ��ʱ�䲻�����趨ʱ��
			{
				Ctrl_Time = Set_Time;//���趨ʱ�丳ֵ������ʱ��
				Param.P_Param[PMode_Option][0] = Set_Time;//ʱ��
			}  
			Param.P_Param[PMode_Option][2] = Safe_Set_Temp;//��ȫ�¶�
			Param.P_Param[0][4] = Speed_Mode;//������ģ��
			Xg_R(dT);//�������뾶
			Save_Param_En = 1;//����
			SetOK_Flag = 0;
		}
    }
}
