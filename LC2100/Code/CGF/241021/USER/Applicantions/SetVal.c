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
			if(Speed.Ctrl != Speed.Set)//�жϿ����ٶȺ��趨�ٶ��ǲ��ǲ�һ��
			{
				Speed.Ctrl = Speed.Set;//���趨�ٶȸ�ֵ�������ٶ�
				if(Speed.Unit == 0)
				{
					Param.P_Param[1] = Speed.Set;//ת��
				}
				else
				{
					Param.P_Param[2] = Speed.Set;//������
				}
			}          
			if(Time.Ctrl != Time.Set)//ʵ��ʱ�䲻�����趨ʱ��
			{
				Time.Ctrl = Time.Set;//���趨ʱ�丳ֵ������ʱ��
				Param.P_Param[0] = Time.Set;//ʱ��
			}  
			Save_Param_En = 1;//����
			SetOK_Flag = 0;
		}
    }
}
