#include "SetVal.h"

/**********ȫ�ֱ�������******/
uint8_t SetOK_Flag;//����Ƿ��°���
uint16_t Rcf_Speed[13] = {1000,1500,2000,2500,3000,3500,4000,4500,5000,5500,6000,6500,7000};

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
			if(Speed.Speed_Mode==0)//�ٶ�	
			{
				if(Speed.Ctrl_Speed != Speed.Set_Speed)//�жϿ����ٶȺ��趨�ٶ��ǲ��ǲ�һ��
				{
					Speed.Ctrl_Speed = Speed.Set_Speed;//���趨�ٶȸ�ֵ�������ٶ�
					Param.Speed = Speed.Set_Speed;//ת��
				}
			}	
			else//������
			{
				Speed.Ctrl_Speed = Rcf_Speed[Speed.Speed_Rcf];//����������Ӧ��ת��ת��
				Param.Speed_Rcf = Speed.Speed_Rcf;//����������ѡ���
			}				
			if(Time.Ctrl_Time != Time.Set_Time)//ʵ��ʱ�䲻�����趨ʱ��
			{
				Time.Ctrl_Time = Time.Set_Time;//���趨ʱ�丳ֵ������ʱ��
				Param.Time = Time.Set_Time;//ʱ��
			}  
            SetOK_Flag = 0;//��ʾ�Ѿ����ú��ˣ������ñ�־λ����
			Save_Param_En = 1;//����
        } 
    }
}
