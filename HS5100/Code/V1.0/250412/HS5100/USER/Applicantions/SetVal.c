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
	if(SpeedSet_Flag)//�ٶ�����
    {
        if(Speed.Ctrl != Speed.Set)//�����ٶȺ��趨�ٶȲ�ͬʱ
		{
			Speed.Ctrl = Speed.Set;
			Param.P_Param[PMode.Option][1] = Speed.Set;
			if(Speed.ADDMode != 0)//�ٶ���ʾģʽ��������ʱ
				Speed.ADDMode = 0;//�ٶ���ʾģʽ����
			Save_Param_En = 1;//����
            if(sys.Run_Status == 1)
                Beep_Time = 0.1f;
		}
		SpeedSet_Flag = 0;//���ñ�־λ����
    }
	
	if(TempSet_Flag)//�¶�����
    {
        if(Temp.Ctrl != Temp.Set)//�����ٶȺ��趨�ٶȲ�ͬʱ
		{
			Temp.Ctrl = Temp.Set;
			Param.P_Param[PMode.Option][0] = Temp.Set;
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
			Param.P_Param[PMode.Option][2] = Time.Set;
			Save_Param_En = 1;//����
            if(sys.Run_Status == 1)
                Beep_Time = 0.1f;
		}
		TimeSet_Flag = 0;//���ñ�־λ����
		sys.SetMode_Option = 0;
    }
    
}
