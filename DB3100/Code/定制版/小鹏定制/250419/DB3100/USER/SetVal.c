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
		if(Select_Option < 2)//���趨�ú�
		{    
			if(Set_Mode_Enable == 1)
			{
				Param.P_Param[run_mode][1] = set_time;
				Param.P_Param[run_mode][0] = set_temp;
				Save_Param_En = 1;
			}
			if(ctrl_temp != set_temp)//�жϿ����ٶȺ��趨�ٶ��ǲ��ǲ�һ��
			{
				ctrl_temp = set_temp;//���趨�ٶȸ�ֵ�������ٶ�
				if(ADD_Mode != 0)//���繤λֻ�������������������ٶȵ�����²�����0������δ����ģʽ��
				ADD_Mode = 0;//����δ�����жϼ��ٻ��Ǽ���
				Param.P_Param[run_mode][0] = set_temp;
				Save_Param_En = 1;
			}          
			if(rel_time != set_time)//ʵ��ʱ�䲻�����趨ʱ��
			{
				rel_time = set_time;//���趨ʱ�丳ֵ������ʱ��
				Param.P_Param[run_mode][1] = set_time;
				Save_Param_En = 1;
			} 
            if(Param.Mode_Val == 0)    
            {                
                if(set_time > 0)
                {
                    SetTime_State = 0;//�趨ʱ���˳���ʾ��----��
                    time_Last = 0;
                }
                else
                {
                    SetTime_State = 1;//�趨ʱ����ʾ��----��
                    time_Last = 1;
                }
            }
			SetOK_Flag = 0;
		}
		
    }
}
