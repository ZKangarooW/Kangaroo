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
			}
			if(Temp.Ctrl != Temp.Set)
			{
				Temp.Ctrl = Temp.Set;
				Param.Temp = Temp.Set;
			}
			if(Time.Rel != Time.Set)
			{
				Time.Rel = Time.Set;
				Param.Time = Time.Set;
			}
			if(sys.Run_Status && Speed.Ctrl)
			{
				Judge_SpeedMode();//�ٶ���ʾģʽ���
			}
			if(sys.Run_Status && Temp.Ctrl)
			{
				Judge_TempMode();//�¶���ʾģʽ���
			}
			Save_Param_En = 1;//����
			SetOK_Flag = 0;
		}
    }
}
