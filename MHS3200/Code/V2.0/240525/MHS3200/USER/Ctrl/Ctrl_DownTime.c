#include "Ctrl_DownTime.h"

/*
*****************************************************************
 * ����ԭ�ͣ� void Cheak_TimeDown(uint16_t dT)
 * ��    �ܣ� ʱ�䵹��ʱ���
 * ��    ��:  dT:ִ������
 * ��    ���� uint16_t dT
*****************************************************************
*/
void Cheak_TimeDown(uint16_t dT)
{
    static uint16_t T;
    #if(Integration_TYPE == 0)//���ó�����ʱ
		if(Param.type == 0 || Param.type == 2)//����
		{
			if(DownTime_Over.L1==1&&DownTime_Over.L2==1&&DownTime_Over.L5==1&&DownTime_Over.L6==1)//�����ϵĹ�λ����ʱ����
			{    
				SetALL_int8(0,&DownTime_Over);//������ʱ�����ı�־λ����
				SetALL_TimeOver(&Ctrl_Time,&Set_Time);//������ʱ�����¸�ֵ������ʱ��  
				Beep_Flash = 5;//��������5��
				Run_Status = 0;//�ر�
			}
		}
		else if(Param.type == 1 || Param.type == 3)//����
		{
			if(DownTime_Over.L1==1&&DownTime_Over.L2==1&&DownTime_Over.L3==1&&DownTime_Over.L4==1&&DownTime_Over.L5==1&&DownTime_Over.L6==1)//�����ϵĹ�λ����ʱ����
			{    
				SetALL_int8(0,&DownTime_Over);//������ʱ�����ı�־λ����
				SetALL_TimeOver(&Ctrl_Time,&Set_Time);//������ʱ�����¸�ֵ������ʱ��
				Beep_Flash = 5;//��������5��
				Run_Status = 0;//�ر�
			}
		}
    #elif(Integration_TYPE == 1)//���óɾ���ʱ
        if(DownTime_Over.L1==1&&DownTime_Over.L2==1&&DownTime_Over.L3==1&&DownTime_Over.L4==1&&DownTime_Over.L5==1&&DownTime_Over.L6==1&&DownTime_Over.L7==1&&DownTime_Over.L8==1&&DownTime_Over.L9==1)//�����ϵĹ�λ����ʱ����
        {    
            SetALL_int8(0,&DownTime_Over);//������ʱ�����ı�־λ����
            SetALL_TimeOver(&Ctrl_Time,&Set_Time);//������ʱ�����¸�ֵ������ʱ��
            Beep_Flash = 5;//��������5��
            Run_Status = 0;//�ر�
        }
    #endif
    if(Run_Status)//����ϵͳ
    {
        T += dT;
        if(T == 1000)//1S
        {
            if(RelTime_State.L1 && DownTime_Over.L1 == 0 && Rel_Speed.L1)//���ʵ��ʱ����ʾ�͵���ʱû�н����ı�־����
            {
                if(Ctrl_Time.L1)
                    Ctrl_Time.L1--;//����ʱ��--
                else
                {
					Speed_ADDMode.L1 = 4;//���ٶ�����
                    DownTime_Over.L1= 1;//time1����ʱ����
                }
            }
            if(RelTime_State.L2 && DownTime_Over.L2 == 0 && Rel_Speed.L2)//���ʵ��ʱ����ʾ�͵���ʱû�н����ı�־����
            {
                if(Ctrl_Time.L2)
                    Ctrl_Time.L2--;//����ʱ��--
                else
                {
					Speed_ADDMode.L2 = 4;//���ٶ�����
                    DownTime_Over.L2= 1;//time1����ʱ����
                }
            }
            if(RelTime_State.L3 && DownTime_Over.L3 == 0 && Rel_Speed.L3)//���ʵ��ʱ����ʾ�͵���ʱû�н����ı�־����
            {
                if(Ctrl_Time.L3)
                    Ctrl_Time.L3--;//����ʱ��--
                else
                {
					Speed_ADDMode.L3 = 4;//���ٶ�����
                    DownTime_Over.L3= 1;//time1����ʱ����
                }
            }
            if(RelTime_State.L4 && DownTime_Over.L4 == 0 && Rel_Speed.L4)//���ʵ��ʱ����ʾ�͵���ʱû�н����ı�־����
            {
                if(Ctrl_Time.L4)
                    Ctrl_Time.L4--;//����ʱ��--
                else
                {
					Speed_ADDMode.L4 = 4;//���ٶ�����
                    DownTime_Over.L4= 1;//time1����ʱ����
                }
            }
            if(RelTime_State.L5 && DownTime_Over.L5 == 0 && Rel_Speed.L5)//���ʵ��ʱ����ʾ�͵���ʱû�н����ı�־����
            {
                if(Ctrl_Time.L5)
                    Ctrl_Time.L5--;//����ʱ��--
                else
                {
					Speed_ADDMode.L5 = 4;//���ٶ�����
                    DownTime_Over.L5= 1;//time1����ʱ����
                }
            }
            if(RelTime_State.L6 && DownTime_Over.L6 == 0 && Rel_Speed.L6)//���ʵ��ʱ����ʾ�͵���ʱû�н����ı�־����
            {
                if(Ctrl_Time.L6)
                    Ctrl_Time.L6--;//����ʱ��--
                else
                {
					Speed_ADDMode.L6 = 4;//���ٶ�����
                    DownTime_Over.L6= 1;//time1����ʱ����
                }
            }
            if(RelTime_State.L7 && DownTime_Over.L7 == 0 && Rel_Speed.L7)//���ʵ��ʱ����ʾ�͵���ʱû�н����ı�־����
            {
                if(Ctrl_Time.L7)
                    Ctrl_Time.L7--;//����ʱ��--
                else
                {
					Speed_ADDMode.L7 = 4;//���ٶ�����
                    DownTime_Over.L7= 1;//time1����ʱ����
                }
            }
            if(RelTime_State.L8 && DownTime_Over.L8 == 0 && Rel_Speed.L8)//���ʵ��ʱ����ʾ�͵���ʱû�н����ı�־����
            {
                if(Ctrl_Time.L8)
                    Ctrl_Time.L8--;//����ʱ��--
                else
                {
					Speed_ADDMode.L8 = 4;//���ٶ�����
                    DownTime_Over.L8= 1;//time1����ʱ����
                }
            }
			if(RelTime_State.L9 && DownTime_Over.L9 == 0 && Rel_Speed.L9)//���ʵ��ʱ����ʾ�͵���ʱû�н����ı�־����
            {
                if(Ctrl_Time.L9)
                    Ctrl_Time.L9--;//����ʱ��--
                else
                {
					Speed_ADDMode.L9 = 4;//���ٶ�����
                    DownTime_Over.L9= 1;//time1����ʱ����
                }
            }
            T = 0;//��������
        }    
    }
    else
    {
        SetALL_int8(0,&DownTime_Over);//��ʱ���־����
        SetALL_TimeOver(&Ctrl_Time,&Set_Time);//���趨ʱ�丳ֵ������ʱ�������ٴε���ʱ
    }
}
