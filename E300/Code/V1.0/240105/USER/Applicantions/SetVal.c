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
        if(Temp.Ctrl != Temp.Set)//�����ٶȺ��趨�ٶȲ�ͬʱ
		{
			Temp.Ctrl = Temp.Set;
			Param.Temp = Temp.Set;
			if(Temp.ADDMode != 0)//�ٶ���ʾģʽ��������ʱ
				Temp.ADDMode = 0;//�ٶ���ʾģʽ����
			Save_Param_En = 1;//����
		}
		SpeedSet_Flag = 0;//���ñ�־λ����
    }
	
	if(TimeSet_Flag)//ʱ������
    {
        if(Time.Rel != Time.Set)//ʵ��ʱ����趨ʱ�䲻ͬʱ
		{
			Time.Rel = Time.Set;
			Param.Time = Time.Set;
			Save_Param_En = 1;//����
		}
		TimeSet_Flag = 0;//���ñ�־λ����
    }
}
