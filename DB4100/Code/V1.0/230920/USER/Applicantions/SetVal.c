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
        if(Temp.Ctrl != Temp.Set)
        {
            Temp.Ctrl = Temp.Set;
            Param.P_Param[PMode.Option][0] = Temp.Set;
        }
        if(Time.Rel != Time.Set)
        {
            Time.Rel = Time.Set;
            Param.P_Param[PMode.Option][1] = Time.Set;
        }
        Save_Param_En = 1;//����
        SetOK_Flag = 0;
    }
}
