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
    if(Key_Status)
    {
        SetOK_Flag = 1;//��⵽������ť���ȴ��˳�����ģʽ
    }
    if(SetOK_Flag)
    {
		if(!sys.SetMode_Option)//���趨�ú�
		{    
			if(Speed.Ctrl != Speed.Set)//�жϿ����ٶȺ��趨�ٶ��ǲ��ǲ�һ��
			{
				Speed.Ctrl = Speed.Set;//���趨�ٶȸ�ֵ�������ٶ�
				if(Speed.Unit == 0)
					Param.P_Param[PMode.Option][1] = Speed.Set;//ת��
				else
					Param.P_Param[PMode.Option][3] = Speed.Set;//������
			}          
			if(Time.Rel != Time.Set)//ʵ��ʱ�䲻�����趨ʱ��
			{
				Time.Rel = Time.Set;//���趨ʱ�丳ֵ������ʱ��
				Param.P_Param[PMode.Option][0] = Time.Set;//ʱ��
			}  
			Param.P_Param[PMode.Option][2] = SafeTemp.Set;//��ȫ�¶�
			Save_Param_En = 1;//����
			SetOK_Flag = 0;
		}
    }
}
