#include "SetVal.h"

/**********ȫ�ֱ�������******/
uint8_t SetOK_Flag;//����Ƿ񲨶���ť�����ñ�־λ

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
        SetOK_Flag = 1;//��⵽���ñ�־��
    }
    if(SetOK_Flag == 1)
    {
        if(sys.SetMode_Option == 0)//���趨�ú�
        {    
			if(Temp.Ctrl_Temp != Temp.Set_Temp)//�����¶Ȳ������趨�¶ȵĻ�
			{
				Temp.Ctrl_Temp = Temp.Set_Temp;//�����¶ȵ����趨�¶�
				Param.P_Param[0] = Temp.Ctrl_Temp;//�������¶ȱ��浽Flash
			}
			
			if(Speed.Ctrl_Speed != Speed.Set_Speed)//�����ٶȲ������趨�ٶȵĻ�
			{
				Speed.Ctrl_Speed = Speed.Set_Speed;//�����ٶȵ����趨�ٶ�
				Param.P_Param[1] = Speed.Ctrl_Speed;//�������ٶȱ��浽Flash
			}
			
            if(Time.Ctrl_Time != Time.Set_Time)//����ʱ�䲻�����趨ʱ��Ļ�
			{
				Time.Ctrl_Time = Time.Set_Time;//����ʱ������趨ʱ��
				Param.P_Param[2] = Time.Ctrl_Time;//������ʱ�䱣�浽Flash
			}
			
            SetOK_Flag = 0;//�趨�ú������־λ
			Save_Param_En = 1;//����Flash��־λ��һ
        } 
    }
}
