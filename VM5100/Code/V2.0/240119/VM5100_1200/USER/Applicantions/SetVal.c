#include "SetVal.h"

/**********ȫ�ֱ�������******/
uint8_t SpeedSet_Flag,TimeSet_Flag;//����ٶȺ�ʱ�����ñ�־λ

/*
*****************************************************************
 * ����ԭ�ͣ� void Check_Set(void)
 * ��    �ܣ� �������
*****************************************************************
*/
void Check_Set(void)
{
    if(Twinkle_Time1 == 0 && SpeedSet_Flag)
    {
		Ctrl_Speed = Set_Speed;
		Speed = Set_Speed;
		if(Speed_ADDMode != 0)//���繤λֻ�������������������ٶȵ�����²�����0������δ����ģʽ��
            Speed_ADDMode = 0;//����δ�����жϼ��ٻ��Ǽ���  
		Param.Speed = Set_Speed;//ת��
		Save_Param_En = 1;
        SpeedSet_Flag = 0;
    }
	if(Twinkle_Time2 == 0 && TimeSet_Flag)
    {
		Ctrl_Time = Set_Time;
		Time = Set_Time;
		Param.Time = Set_Time;//ʱ��
		Save_Param_En = 1;
        TimeSet_Flag = 0;
    }
}
