#include "SetVal.h"

/**********ȫ�ֱ�������******/
uint8_t SpeedSet_Flag,TimeSet_Flag;//�ٶ����ã�ʱ������

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_Set(float dT)
 * ��    �ܣ��������
*****************************************************************
*/
void Check_Set(float dT)
{
	if(SpeedSet_Flag)//�ٶ�����
    {
        if(Speed.Ctrl != Speed.Set)//�����ٶȺ��趨�ٶȲ�ͬʱ
		{
			Speed.Ctrl = Speed.Set;
			Param.P_Param[PMode.Option][0] = Speed.Set;
			if(Speed.ADDMode != 0)//�ٶ���ʾģʽ��������ʱ
				Speed.ADDMode = 0;//�ٶ���ʾģʽ����
			Save_Param_En = 1;//����
		}
		SpeedSet_Flag = 0;//���ñ�־λ����
    }
	
	if(TimeSet_Flag)//ʱ������
    {
        if(Time.Rel != Time.Set)//ʵ��ʱ����趨ʱ�䲻ͬʱ
		{
			Time.Rel = Time.Set;
			Param.P_Param[PMode.Option][1] = Time.Set;
			Save_Param_En = 1;//����
		}
		TimeSet_Flag = 0;//���ñ�־λ����
    }
}
