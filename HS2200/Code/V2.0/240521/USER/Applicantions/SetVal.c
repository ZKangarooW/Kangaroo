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
        SetOK_Flag = 1;//��⵽���ã��ȴ��˳�����ģʽ
    }
    if(SetOK_Flag)
    {
		if(!sys.SetMode_Option)//���趨�ú�
		{    
			if(Speed.Ctrl != Speed.Set)
			{
				Speed.Ctrl = Speed.Set;
				Param.Speed = Speed.Set;
                if(Speed.ADDMode != 0)//�ٶ���ʾģʽ��������ʱ
                    Speed.ADDMode = 0;//�ٶ���ʾģʽ����
			}
			if(Temp.Ctrl != Temp.Set)
			{
				Temp.Ctrl = Temp.Set;
				Param.Temp = Temp.Set;
                if(Temp.ADDMode != 0)//�¶���ʾģʽ��������ʱ
                        Temp.ADDMode= 0;//�¶���ʾģʽ����
			}
			if(Time.Rel != Time.Set)
			{
				Time.Rel = Time.Set;
				Param.Time = Time.Set;
			}
			Save_Param_En = 1;//����
			SetOK_Flag = 0;
		}
    }
}
