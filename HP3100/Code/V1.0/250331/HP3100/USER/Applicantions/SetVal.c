#include "SetVal.h"

/**********ȫ�ֱ�������******/
uint8_t SpeedSet_Flag,TempSet_Flag,TimeSet_Flag;//�ٶ����ã��¶����ã�ʱ������

/**
 * @brief �������
 * 
 * @param dT ִ������
 */
void Check_Set(float dT)
{
	if(TempSet_Flag)//�¶�����
    {
        if(Temp.Ctrl != Temp.Set)//�����ٶȺ��趨�ٶȲ�ͬʱ
		{
			Temp.Ctrl = Temp.Set;
			Param.Temp = Temp.Set;
			if(Temp.ADDMode != 0)//�ٶ���ʾģʽ��������ʱ
				Temp.ADDMode = 0;//�ٶ���ʾģʽ����
			Save_Param_En = 1;//����
            if(sys.Run_Status == 1)
                Beep_Time = 0.1f;
		}
		TempSet_Flag = 0;//���ñ�־λ����
    }
	
	if(TimeSet_Flag)//ʱ������
    {
        if(Time.Rel != Time.Set)//ʵ��ʱ����趨ʱ�䲻ͬʱ
		{
			Time.Rel = Time.Set;
			Param.Time = Time.Set;
			Save_Param_En = 1;//����
            if(sys.Run_Status == 1)
                Beep_Time = 0.1f;
		}
		TimeSet_Flag = 0;//���ñ�־λ����
		sys.SetMode_Option = 0;
    }  
}
