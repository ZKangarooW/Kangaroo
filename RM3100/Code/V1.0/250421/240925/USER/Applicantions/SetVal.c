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
        if(sys.SetMode_Option == 0)//���趨�ú�
        {     
            if(Ctrl_Speed != Set_Speed)//�жϿ����ٶȺ��趨�ٶ��ǲ��ǲ�һ��
            {
                Ctrl_Speed = Set_Speed;//���趨�ٶȸ�ֵ�������ٶ�
                if(Speed_ADDMode != 0)//���繤λֻ�������������������ٶȵ�����²�����0������δ����ģʽ��
					Speed_ADDMode = 0;//����δ�����жϼ��ٻ��Ǽ��� 
				Param.Speed = Set_Speed;//ת��
            }    
			if(Ctrl_Time != Set_Time)//��û������������¿�������ʱ��
			{				
				if(Ctrl_Time != Set_Time)//ʵ��ʱ�䲻�����趨ʱ��
				{
					Ctrl_Time = Set_Time;//���趨ʱ�丳ֵ������ʱ��
                    Rel_Time = Ctrl_Time;
					Param.Time = Set_Time;//ʱ��
				}
			}
            if(sys.Run_Status)
            {
                if(Speed_ADDMode != 0)//���繤λֻ�������������������ٶȵ�����²�����0������δ����ģʽ��
					Speed_ADDMode = 0;//����δ�����жϼ��ٻ��Ǽ��� 
                Display_Speed = Rel_Speed;
            }
            SetOK_Flag = 0;//��ʾ�Ѿ����ú��ˣ������ñ�־λ����
			Save_Param_En = 1;//����
        } 
    }
}
