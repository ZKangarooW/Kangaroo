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
    if(Key_Status != 0)//���¼Ӽ�����
    {
        SetOK_Flag = 1;//��⵽������ť���ȴ��˳�����ģʽ
    }
    if(SetOK_Flag == 1)//��⵽���¼Ӽ�������
    {
		if(sys.SetMode_Option)
		{
			if(Param.Mode != Speed_Mode)
			{
				Param.Mode = Speed_Mode;
				Set_Time = Param.Time[Speed_Mode][sys.Run_Step];//ʱ��
				Set_Speed = Param.Speed[Speed_Mode][sys.Run_Step];//ת��
			}
			Param.Speed[Speed_Mode][sys.Run_Step] = Set_Speed;
			Param.Time[Speed_Mode][sys.Run_Step] = Set_Time;
			if(sys.SetMode_Option > 4)
				sys.SetMode_Option = 0;
		}
		else
		{
			if(Param.Mode != Speed_Mode)
			{
				Param.Mode = Speed_Mode;
			}
		}
		if(sys.SetMode_Option<3)
		{
			sys.Run_Step = 0;
		}
		else
		{
			sys.Run_Step = 1;
		}	
		Set_Time = Param.Time[Speed_Mode][sys.Run_Step];//ʱ��
		Set_Speed = Param.Speed[Speed_Mode][sys.Run_Step];//ת��
        SetOK_Flag = 0;//��ʾ�Ѿ����ú��ˣ������ñ�־λ����
		Save_Param_En = 1;//����
    }
}
