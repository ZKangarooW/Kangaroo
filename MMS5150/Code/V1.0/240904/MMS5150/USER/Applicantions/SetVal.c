#include "SetVal.h"

/**********ȫ�ֱ�������******/
uint8_t SetOK_Flag;//����Ƿ񲨶���ť�����ñ�־λ

/*
*****************************************************************
 * ����ԭ�ͣ� void Check_Set(float dT)
 * ��    �ܣ� ������� 
*****************************************************************
*/
void Check_Set(float dT)
{
    if(EC11A[1].EC11A_Knob > 0)
    {
        SetOK_Flag = 1;//��⵽������ť���ȴ��˳�����ģʽ
    }
    if(SetOK_Flag == 1 && Twinkle_Time <= 0)
    {
        if(sys.SetMode_Option == 0 && Twinkle_Time == 0)//���趨�ú�
        {     
            for(uint8_t i = 0;i<15;i++)
            {
                if(Work_Num[i].Speed.Set != Work_Num[i].Speed.Ctrl)
                {
                    Work_Num[i].Speed.Ctrl = Work_Num[i].Speed.Set;
                    Param.Speed[i] = Work_Num[i].Speed.Set;
                    if(Work_Num[i].Speed.ADDMode != 0)
                        Work_Num[i].Speed.ADDMode = 0;
                }
                if(Work_Num[i].Time.Set != Work_Num[i].Time.Ctrl)
                {
                    Work_Num[i].Time.Ctrl = Work_Num[i].Time.Set;
                    Work_Num[i].Time.Rel = Work_Num[i].Time.Set;
                    Param.Time[i] = Work_Num[i].Time.Set;
                }
            }
            Save_Param_En = 1;//����
            SetOK_Flag = 0;
        } 
    }
}
