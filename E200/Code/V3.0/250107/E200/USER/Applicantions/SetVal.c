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
			if(Heat_Temp.Ctrl_Temp != Heat_Temp.Set_Temp)//�жϿ����¶Ⱥ��趨�¶��ǲ��ǲ�һ��
			{
				Heat_Temp.Ctrl_Temp = Heat_Temp.Set_Temp;//���趨�¶ȸ�ֵ�������¶�
				Param.Heat_Temp = Heat_Temp.Set_Temp;//��ֵ���������
				Heat_Temp.ADDMode = 0;//�¶ȴ�������
                tuning_complete = false;//�Զ���������Ϊfalse
                last_peak_time = 0.0;//��һ����������
                oscillation_count = 0;//������
			}    
			if(Cool_Temp.Ctrl_Temp != Cool_Temp.Set_Temp)//�жϿ����¶Ⱥ��趨�¶��ǲ��ǲ�һ��
			{
				Cool_Temp.Ctrl_Temp = Cool_Temp.Set_Temp;//���趨�¶ȸ�ֵ�������¶�
				Param.Cool_Temp = Cool_Temp.Set_Temp;//��ֵ���������
				Cool_Temp.ADDMode = 0;//�¶ȴ�������
                tuning_complete1 = false;//�Զ���������Ϊfalse
                last_peak_time1 = 0.0;//��һ����������
                oscillation_count1 = 0;//������
			}  			
			if(Time.Ctrl_Time != Time.Set_Time)//ʵ��ʱ�䲻�����趨ʱ��
			{
				Time.Ctrl_Time = Time.Set_Time;//���趨ʱ�丳ֵ������ʱ��
				Param.CountDown_Time = Time.Set_Time;//��ֵ���������
			}  
			Save_Param_En = 1;//����
			SetOK_Flag = 0;
		}
    }
}
