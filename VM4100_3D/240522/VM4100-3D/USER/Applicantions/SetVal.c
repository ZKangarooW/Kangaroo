#include "SetVal.h"

/**********ȫ�ֱ�������******/
uint8_t SetOK_Flag;//����Ƿ񲨶���ť�����ñ�־λ

/*
*****************************************************************
 * ����ԭ�ͣ� void Check_Set(void)
 * ��    �ܣ� �������
*****************************************************************
*/
void Check_Set(void)
{
    if(Key_Status != 0)
    {
        SetOK_Flag = 1;//��⵽������ť���ȴ��˳�����ģʽ
    }
    if(SetOK_Flag == 1)
    {
        if(SetMode_Option == 0)//���趨�ú�
        {     
            if(Ctrl_Speed != Set_Speed)//�жϿ����ٶȺ��趨�ٶ��ǲ��ǲ�һ��
            {
                Ctrl_Speed = Set_Speed;//���趨�ٶȸ�ֵ�������ٶ�
                if(Speed_ADDMode != 0)//���繤λֻ�������������������ٶȵ�����²�����0������δ����ģʽ��
					Speed_ADDMode = 0;//����δ�����жϼ��ٻ��Ǽ��� 
				Param.Speed = Set_Speed;//ת��
				
            }          
            if(Rel_Time != Set_Time)//ʵ��ʱ�䲻�����趨ʱ��
            {
                Rel_Time = Set_Time;//���趨ʱ�丳ֵ������ʱ��
				if(Set_Time == 0)
					Time_State = 0;
				else
					Time_State = 1;
				Param.Time = Set_Time;//ʱ��
            }  
            SetOK_Flag = 0;
			Save_Param_En = 1;
        } 
    }
}
