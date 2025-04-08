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
    if(EC11A_Knob != 0)
    {
        SetOK_Flag = 1;//��⵽������ť���ȴ��˳�����ģʽ
    }
    if(SetOK_Flag == 1)
    {
        if(SetMode_Option == 0 && Twinkle_Time == 0)//���趨�ú�
        {     
            Set_Speeds(&Speed,&Set_Speed,&Ctrl_Speed,&Display_Speed,&Speed,&Param.Speed);//�Ƚ���ʱ�ٶȣ���ͬ�ͽ�����ֵ��ֵ
			
            Set_Times(&Time,&Set_Time,&Rel_Time,&Ctrl_Time,&Time,&Param.Time);//�Ƚ���ʱʱ�䣬��ͬ�ͽ�����ֵ��ֵ
           
            if(Temp != Set_Temp)//�Ƚ���ʱ�¶Ⱥ��趨�¶Ȳ�һ��
            {
                Ctrl_Temp = Set_Temp;//�������¶ȸ�ֵ�������¶�
                Temp = Ctrl_Temp;//�������¶ȸ�ֵ����ʱ�¶�
				Param.Temp = Ctrl_Temp;//�������¶ȸ�ֵ��Flash
				Save_Param_En = 1;
				if(Temp_ADDMode != 0)//���¶�״̬��
				{
					Temp_ADDMode = 0;//�����ж�
					ADD_Wait_Count = 0;	
				}
            }
            Check_Time_State(&SetTime_State,&Set_Time);//�ж�ʱ��״̬
			Check_Time_State(&RelTime_State,&Set_Time);//�ж�ʱ��״̬
			if(Set_Temp > 0)
				Temp_State = 1;
			else
				Temp_State = 0;
            SetOK_Flag = 0;
        } 
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Set_Val(uint8_t flag,uint8_t Work_Option,uint8_t SetMode_Option)
 * ��    �ܣ� ������ֵ
 * ��    ��:  flag ��0�Ǽ� 1�Ǽ�  Work_Option����λ SetMode_Option������ģʽ
 * ��    ���� uint8_t flag,uint8_t Work_Option,uint8_t SetMode_Option
*****************************************************************
*/
void Set_Val(uint8_t flag,uint8_t Work_Option,uint8_t SetMode_Option)
{
    if(flag == 0)//��
    {
        switch(Work_Option)//��λ
        {
            case 1:switch(SetMode_Option)//ģʽ
                   {
                        case 0:Set_Speed.L1 = Set_Speed.L1 + 10;//�ٶȼ�10
                               Set_Speed.L1 = (Set_Speed.L1 < 50) ? 50 : Set_Speed.L1;//С��50ʱ��50��ʼ��
                               break;
                        case 1:Set_Speed.L1 = Set_Speed.L1 + 10;//�ٶȼ�10
                               Set_Speed.L1 = (Set_Speed.L1 < 50) ? 50 : Set_Speed.L1;//С��50ʱ��50��ʼ��
                               break;
                        case 2:Set_Temp = Set_Temp + 10;//�¶ȼ�1��
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//���������ת
                               {
                                   Set_Time.L1 = Set_Time.L1 + 60;//ʱ���һ����
                               }
                               else
                               {
                                   Set_Time.L1 = Set_Time.L1 + 600;//ʱ���ʮ����
                               }
                               break;
                   }break;
            case 2:switch(SetMode_Option)//ģʽ
                   {
                        case 0:Set_Speed.L2 = Set_Speed.L2 + 10;//�ٶȼ�10
                                Set_Speed.L2 = (Set_Speed.L2 < 50) ? 50 : Set_Speed.L2;//С��50ʱ��50��ʼ��
                               break;
                        case 1:Set_Speed.L2 = Set_Speed.L2 + 10;//�ٶȼ�10
                                Set_Speed.L2 = (Set_Speed.L2 < 50) ? 50 : Set_Speed.L2;//С��50ʱ��50��ʼ��
                               break;
                        case 2:Set_Temp = Set_Temp + 10;//�¶ȼ�1��
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//���������ת
                               {
                                   Set_Time.L2 = Set_Time.L2 + 60;//ʱ���һ����
                               }
                               else
                               {
                                   Set_Time.L2 = Set_Time.L2 + 600;//ʱ���ʮ����
                               }
                               break;
                   }break;
            case 3:switch(SetMode_Option)//ģʽ
                   {
                        case 0:Set_Speed.L3 = Set_Speed.L3 + 10;//�ٶȼ�10
                                Set_Speed.L3 = (Set_Speed.L3 < 50) ? 50 : Set_Speed.L3;//С��50ʱ��50��ʼ��
                               break;
                        case 1:Set_Speed.L3 = Set_Speed.L3 + 10;//�ٶȼ�10
                                Set_Speed.L3 = (Set_Speed.L3 < 50) ? 50 : Set_Speed.L3;//С��50ʱ��50��ʼ��
                               break;
                        case 2:Set_Temp = Set_Temp + 10;//�¶ȼ�1��
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//���������ת
                               {
                                   Set_Time.L3 = Set_Time.L3 + 60;//ʱ���һ����
                               }
                               else
                               {
                                   Set_Time.L3 = Set_Time.L3 + 600;//ʱ���ʮ����
                               }
                               break;
                   }break;
            case 4:switch(SetMode_Option)//ģʽ
                   {
                        case 0:Set_Speed.L4 = Set_Speed.L4 + 10;//�ٶȼ�10
                                Set_Speed.L4 = (Set_Speed.L4 < 50) ? 50 : Set_Speed.L4;//С��50ʱ��50��ʼ��
                               break;
                        case 1:Set_Speed.L4 = Set_Speed.L4 + 10;//�ٶȼ�10
                                Set_Speed.L4 = (Set_Speed.L4 < 50) ? 50 : Set_Speed.L4;//С��50ʱ��50��ʼ��
                               break;
                        case 2:Set_Temp = Set_Temp + 10;//�¶ȼ�1��
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//���������ת
                               {
                                   Set_Time.L4 = Set_Time.L4 + 60;//ʱ���һ����
                               }
                               else
                               {
                                   Set_Time.L4 = Set_Time.L4 + 600;//ʱ���ʮ����
                               }
                               break;
                   }break;
            case 5:switch(SetMode_Option)//ģʽ
                   {
                        case 0:Set_Speed.L5 = Set_Speed.L5 + 10;//�ٶȼ�10
                                Set_Speed.L5 = (Set_Speed.L5 < 50) ? 50 : Set_Speed.L5;//С��50ʱ��50��ʼ��
                               break;
                        case 1:Set_Speed.L5 = Set_Speed.L5 + 10;//�ٶȼ�10
                                Set_Speed.L5 = (Set_Speed.L5 < 50) ? 50 : Set_Speed.L5;//С��50ʱ��50��ʼ��
                               break;
                        case 2:Set_Temp = Set_Temp + 10;//�¶ȼ�1��
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//���������ת
                               {
                                   Set_Time.L5 = Set_Time.L5 + 60;//ʱ���һ����
                               }
                               else
                               {
                                   Set_Time.L5 = Set_Time.L5 + 600;//ʱ���ʮ����
                               }
                               break;
                   }break;
            case 6:switch(SetMode_Option)//ģʽ
                   {
                        case 0:Set_Speed.L6 = Set_Speed.L6 + 10;//�ٶȼ�10
                                Set_Speed.L6 = (Set_Speed.L6 < 50) ? 50 : Set_Speed.L6;//С��50ʱ��50��ʼ��
                               break;
                        case 1:Set_Speed.L6 = Set_Speed.L6 + 10;//�ٶȼ�10
                                Set_Speed.L6 = (Set_Speed.L6 < 50) ? 50 : Set_Speed.L6;//С��50ʱ��50��ʼ��
                               break;
                        case 2:Set_Temp = Set_Temp + 10;//�¶ȼ�1��
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//���������ת
                               {
                                   Set_Time.L6 = Set_Time.L6 + 60;//ʱ���һ����
                               }
                               else
                               {
                                   Set_Time.L6 = Set_Time.L6 + 600;//ʱ���ʮ����
                               }

                               break;
                   }break;
            case 7:switch(SetMode_Option)//ģʽ
                   {
                        case 0:Set_Speed.L7 = Set_Speed.L7 + 10;//�ٶȼ�10
                                Set_Speed.L7 = (Set_Speed.L7 < 50) ? 50 : Set_Speed.L7;//С��50ʱ��50��ʼ��
                               break;
                        case 1:Set_Speed.L7 = Set_Speed.L7 + 10;//�ٶȼ�10
                                Set_Speed.L7 = (Set_Speed.L7 < 50) ? 50 : Set_Speed.L7;//С��50ʱ��50��ʼ��
                               break;
                        case 2:Set_Temp = Set_Temp + 10;//�¶ȼ�1��

                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//���������ת
                               {
                                   Set_Time.L7 = Set_Time.L7 + 60;//ʱ���һ����
                               }
                               else
                               {
                                   Set_Time.L7 = Set_Time.L7 + 600;//ʱ���ʮ����
                               }
                               break;
                   }break;
            case 8:switch(SetMode_Option)//ģʽ
                   {
                        case 0:Set_Speed.L8 = Set_Speed.L8 + 10;//�ٶȼ�10
                                Set_Speed.L8 = (Set_Speed.L8 < 50) ? 50 : Set_Speed.L8;//С��50ʱ��50��ʼ��
                               break;
                        case 1:Set_Speed.L8 = Set_Speed.L8 + 10;//�ٶȼ�10
                                Set_Speed.L8 = (Set_Speed.L8 < 50) ? 50 : Set_Speed.L8;//С��50ʱ��50��ʼ��
                               break;
                        case 2:Set_Temp = Set_Temp + 10;//�¶ȼ�1��
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//���������ת
                               {
                                   Set_Time.L8 = Set_Time.L8 + 60;//ʱ���һ����
                               }
                               else
                               {
                                   Set_Time.L8 = Set_Time.L8 + 600;//ʱ���ʮ����
                               }
                               break;
                   }break;
				   
			case 9:switch(SetMode_Option)//ģʽ
                   {
                        case 0:Set_Speed.L9 = Set_Speed.L9 + 10;//�ٶȼ�10
                                Set_Speed.L9 = (Set_Speed.L9 < 50) ? 50 : Set_Speed.L9;//С��50ʱ��50��ʼ��
                               break;
                        case 1:Set_Speed.L9 = Set_Speed.L9 + 10;//�ٶȼ�10
                                Set_Speed.L9 = (Set_Speed.L9 < 50) ? 50 : Set_Speed.L9;//С��50ʱ��50��ʼ��
                               break;
                        case 2:Set_Temp = Set_Temp + 10;//�¶ȼ�1��
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//���������ת
                               {
                                   Set_Time.L9 = Set_Time.L9 + 60;//ʱ���һ����
                               }
                               else
                               {
                                   Set_Time.L9 = Set_Time.L9 + 600;//ʱ���ʮ����
                               }
                               break;
                   }break;
        }
    }
    if(flag == 1)
    {
        switch(Work_Option)//��λ
        {
            case 1:switch(SetMode_Option)//ģʽ
                   {
                        case 0:Set_Speed.L1 = Set_Speed.L1 - 10;//�ٶȼ�10
                               break;
                        case 1:Set_Speed.L1 = Set_Speed.L1 - 10;//�ٶȼ�10
                               break;
                        case 2:Set_Temp = Set_Temp - 10;//�¶ȼ�1��
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//���������ת
                               {
                                   Set_Time.L1 = Set_Time.L1 - 60;//ʱ���һ����
                               }
                               else
                               {
                                   Set_Time.L1 = Set_Time.L1 - 600;//ʱ���ʮ����
                               }
                                break;
                   }break;
            case 2:switch(SetMode_Option)//ģʽ
                   {
                        case 0:Set_Speed.L2 = Set_Speed.L2 - 10;//�ٶȼ�10
                               break;
                        case 1:Set_Speed.L2 = Set_Speed.L2 - 10;//�ٶȼ�10
                               break;
                        case 2:Set_Temp = Set_Temp - 10;//�¶ȼ�1��
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//���������ת
                               {
                                   Set_Time.L2 = Set_Time.L2 - 60;//ʱ���һ����
                               }
                               else
                               {
                                   Set_Time.L2 = Set_Time.L2 - 600;//ʱ���ʮ����
                               }
                                break;
                   }break;
            case 3:switch(SetMode_Option)//ģʽ
                   {
                        case 0:Set_Speed.L3 = Set_Speed.L3 - 10;//�ٶȼ�10
                               break;
                        case 1:Set_Speed.L3 = Set_Speed.L3 - 10;//�ٶȼ�10
                               break;
                        case 2:Set_Temp = Set_Temp - 10;//�¶ȼ�1��
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//���������ת
                               {
                                   Set_Time.L3 = Set_Time.L3 - 60;//ʱ���һ����
                               }
                               else
                               {
                                   Set_Time.L3 = Set_Time.L3 - 600;//ʱ���ʮ����
                               }
                                break;
                   }break;
            case 4:switch(SetMode_Option)//ģʽ
                   {
                        case 0:Set_Speed.L4 = Set_Speed.L4 - 10;//�ٶȼ�10
                               break;
                        case 1:Set_Speed.L4 = Set_Speed.L4 - 10;//�ٶȼ�10
                               break;
                        case 2:Set_Temp = Set_Temp - 10;//�¶ȼ�1��
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//���������ת
                               {
                                   Set_Time.L4 = Set_Time.L4 - 60;//ʱ���һ����
                               }
                               else
                               {
                                   Set_Time.L4 = Set_Time.L4 - 600;//ʱ���ʮ����
                               }
                                break;
                   }break;
            case 5:switch(SetMode_Option)//ģʽ
                   {
                        case 0:Set_Speed.L5 = Set_Speed.L5 - 10;//�ٶȼ�10
                               break;
                        case 1:Set_Speed.L5 = Set_Speed.L5 - 10;//�ٶȼ�10
                               break;
                        case 2:Set_Temp = Set_Temp - 10;//�¶ȼ�1��
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//���������ת
                               {
                                   Set_Time.L5 = Set_Time.L5 - 60;//ʱ���һ����
                               }
                               else
                               {
                                   Set_Time.L5 = Set_Time.L5 - 600;//ʱ���ʮ����
                               }
                                break;
                   }break;
            case 6:switch(SetMode_Option)//ģʽ
                   {
                        case 0:Set_Speed.L6 = Set_Speed.L6 - 10;//�ٶȼ�10
                               break;
                        case 1:Set_Speed.L6 = Set_Speed.L6 - 10;//�ٶȼ�10
                               break;
                        case 2:Set_Temp = Set_Temp - 10;//�¶ȼ�1��
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//���������ת
                               {
                                   Set_Time.L6 = Set_Time.L6 - 60;//ʱ���һ����
                               }
                               else
                               {
                                   Set_Time.L6 = Set_Time.L6 - 600;//ʱ���ʮ����
                               }
                                break;
                   }break;
            case 7:switch(SetMode_Option)//ģʽ
                   {
                        case 0:Set_Speed.L7 = Set_Speed.L7 - 10;//�ٶȼ�10
                               break;
                        case 1:Set_Speed.L7 = Set_Speed.L7 - 10;//�ٶȼ�10
                               break;
                        case 2:Set_Temp = Set_Temp - 10;//�¶ȼ�1��
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//���������ת
                               {
                                   Set_Time.L7 = Set_Time.L7 - 60;//ʱ���һ����
                               }
                               else
                               {
                                   Set_Time.L7 = Set_Time.L7 - 600;//ʱ���ʮ����
                               }
                                break;
                   }break;
            case 8:switch(SetMode_Option)//ģʽ
                   {
                        case 0:Set_Speed.L8 = Set_Speed.L8 - 10;//�ٶȼ�10
                               break;
                        case 1:Set_Speed.L8 = Set_Speed.L8 - 10;//�ٶȼ�10
                               break;
                        case 2:Set_Temp = Set_Temp - 10;//�¶ȼ�1��
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//���������ת
                               {
                                   Set_Time.L8 = Set_Time.L8 - 60;//ʱ���һ����
                               }
                               else
                               {
                                   Set_Time.L8 = Set_Time.L8 - 600;//ʱ���ʮ����
                               }
                                break;
                   }break;		   
			case 9:switch(SetMode_Option)//ģʽ
                   {
                        case 0:Set_Speed.L9 = Set_Speed.L9 - 10;//�ٶȼ�10
                               break;
                        case 1:Set_Speed.L9 = Set_Speed.L9 - 10;//�ٶȼ�10
                               break;
                        case 2:Set_Temp = Set_Temp - 10;//�¶ȼ�1��
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//���������ת
                               {
                                   Set_Time.L9 = Set_Time.L9 - 60;//ʱ���һ����
                               }
                               else
                               {
                                   Set_Time.L9 = Set_Time.L9 - 600;//ʱ���ʮ����
                               }
                                break;
                   }break;
        }
    }
	Set_Speed.L1 = (Set_Speed.L1 > MAX_Speed) ? MAX_Speed : Set_Speed.L1;//�ٶȲ�����1500ת
	Set_Speed.L1 = (Set_Speed.L1 < 50) ? 0 : Set_Speed.L1;//�ٶ�����С��50תʱ����
	Set_Time.L1 = (Set_Time.L1 > MAX_Time) ? MAX_Time : Set_Time.L1;//ʱ������趨23Сʱ59����
	Set_Time.L1 = (Set_Time.L1 < 60) ? 0 : Set_Time.L1;//ʱ��С��1���Ӳ��趨
	SetTime_State.L1  = (Set_Time.L1 < 60) ? 0 : 1;//�ж��Ƿ�������ʱ��
	
	Set_Speed.L2 = (Set_Speed.L2 > MAX_Speed) ? MAX_Speed : Set_Speed.L2;//�ٶȲ�����1500ת
	Set_Speed.L2 = (Set_Speed.L2 < 50) ? 0 : Set_Speed.L2;//�ٶ�����С��50תʱ����
	Set_Time.L2 = (Set_Time.L2 > MAX_Time) ? MAX_Time : Set_Time.L2;//ʱ������趨23Сʱ59����
	Set_Time.L2 = (Set_Time.L2 < 60) ? 0 : Set_Time.L2;//ʱ��С��1���Ӳ��趨
	SetTime_State.L2  = (Set_Time.L2 < 60) ? 0 : 1;//�ж��Ƿ�������ʱ��
	
	Set_Speed.L3 = (Set_Speed.L3 > MAX_Speed) ? MAX_Speed : Set_Speed.L3;//�ٶȲ�����1500ת
	Set_Speed.L3 = (Set_Speed.L3 < 50) ? 0 : Set_Speed.L3;//�ٶ�����С��50תʱ����
	Set_Time.L3 = (Set_Time.L3 > MAX_Time) ? MAX_Time : Set_Time.L3;//ʱ������趨23Сʱ59����
	Set_Time.L3 = (Set_Time.L3 < 60) ? 0 : Set_Time.L3;//ʱ��С��1���Ӳ��趨
	SetTime_State.L3  = (Set_Time.L3 < 60) ? 0 : 1;//�ж��Ƿ�������ʱ��
	
	Set_Speed.L4 = (Set_Speed.L4 > MAX_Speed) ? MAX_Speed : Set_Speed.L4;//�ٶȲ�����1500ת
	Set_Speed.L4 = (Set_Speed.L4 < 50) ? 0 : Set_Speed.L4;//�ٶ�����С��50תʱ����
	Set_Time.L4 = (Set_Time.L4 > MAX_Time) ? MAX_Time : Set_Time.L4;//ʱ������趨23Сʱ59����
	Set_Time.L4 = (Set_Time.L4 < 60) ? 0 : Set_Time.L4;//ʱ��С��1���Ӳ��趨
	SetTime_State.L4  = (Set_Time.L4 < 60) ? 0 : 1;//�ж��Ƿ�������ʱ��
	
	Set_Speed.L5 = (Set_Speed.L5 > MAX_Speed) ? MAX_Speed : Set_Speed.L5;//�ٶȲ�����1500ת
	Set_Speed.L5 = (Set_Speed.L5 < 50) ? 0 : Set_Speed.L5;//�ٶ�����С��50תʱ����
	Set_Time.L5 = (Set_Time.L5 > MAX_Time) ? MAX_Time : Set_Time.L5;//ʱ������趨23Сʱ59����
	Set_Time.L5 = (Set_Time.L5 < 60) ? 0 : Set_Time.L5;//ʱ��С��1���Ӳ��趨
	SetTime_State.L5  = (Set_Time.L5 < 60) ? 0 : 1;//�ж��Ƿ�������ʱ��
	
	Set_Speed.L6 = (Set_Speed.L6 > MAX_Speed) ? MAX_Speed : Set_Speed.L6;//�ٶȲ�����1500ת
	Set_Speed.L6 = (Set_Speed.L6 < 50) ? 0 : Set_Speed.L6;//�ٶ�����С��50תʱ����
	Set_Time.L6 = (Set_Time.L6 > MAX_Time) ? MAX_Time : Set_Time.L6;//ʱ������趨23Сʱ59����
	Set_Time.L6 = (Set_Time.L6 < 60) ? 0 : Set_Time.L6;//ʱ��С��1���Ӳ��趨
	SetTime_State.L6  = (Set_Time.L6 < 60) ? 0 : 1;//�ж��Ƿ�������ʱ��
	
	Set_Speed.L7 = (Set_Speed.L7 > MAX_Speed) ? MAX_Speed : Set_Speed.L7;//�ٶȲ�����1500ת
	Set_Speed.L7 = (Set_Speed.L7 < 50) ? 0 : Set_Speed.L7;//�ٶ�����С��50תʱ����
	Set_Time.L7 = (Set_Time.L7 > MAX_Time) ? MAX_Time : Set_Time.L7;//ʱ������趨23Сʱ59����
	Set_Time.L7 = (Set_Time.L7 < 60) ? 0 : Set_Time.L7;//ʱ��С��1���Ӳ��趨
	SetTime_State.L7  = (Set_Time.L7 < 60) ? 0 : 1;//�ж��Ƿ�������ʱ��
	
	Set_Speed.L8 = (Set_Speed.L8 > MAX_Speed) ? MAX_Speed : Set_Speed.L8;//�ٶȲ�����1500ת
	Set_Speed.L8 = (Set_Speed.L8 < 50) ? 0 : Set_Speed.L8;//�ٶ�����С��50תʱ����
	Set_Time.L8 = (Set_Time.L8 > MAX_Time) ? MAX_Time : Set_Time.L8;//ʱ������趨23Сʱ59����
	Set_Time.L8 = (Set_Time.L8 < 60) ? 0 : Set_Time.L8;//ʱ��С��1���Ӳ��趨
	SetTime_State.L8  = (Set_Time.L8 < 60) ? 0 : 1;//�ж��Ƿ�������ʱ��
	
	Set_Speed.L9 = (Set_Speed.L9 > MAX_Speed) ? MAX_Speed : Set_Speed.L9;//�ٶȲ�����1500ת
	Set_Speed.L9 = (Set_Speed.L9 < 50) ? 0 : Set_Speed.L9;//�ٶ�����С��50תʱ����
	Set_Time.L9 = (Set_Time.L9 > MAX_Time) ? MAX_Time : Set_Time.L9;//ʱ������趨23Сʱ59����
	Set_Time.L9 = (Set_Time.L9 < 60) ? 0 : Set_Time.L9;//ʱ��С��1���Ӳ��趨
	SetTime_State.L9  = (Set_Time.L9 < 60) ? 0 : 1;//�ж��Ƿ�������ʱ�� 
    
    Set_Temp = (Set_Temp > 1200) ? 1200 : Set_Temp;//�¶Ȳ�����120��
    Set_Temp = (Set_Temp < 10) ? 0 : Set_Temp;//�¶�����С��1��ʱ����
    Temp_State = (Set_Temp < 10) ? 0 : 1;//�ж��Ƿ��������¶�
    
    Twinkle_Time = 2000;//��˸��ʾ6S  
    EC11A_Knob = 2;//����ǲ�����������ť
    Work_All = 0;//�˳�ͬ��ģʽ
}

/*
*****************************************************************
 * ����ԭ�ͣ� void SetALL_int(int Val,_Work_Num_ *Work_Num)
 * ��    �ܣ� ���ṹͼ�еĲ�����ֵ-int��
 * ��    ��:  Val �����ֵ  Work_Num���ṹ�壬Ҫ��&������
 * ��    ���� int Val,_Work_Num_ *Work_Num
*****************************************************************
*/
void SetALL_int(int Val,_Work_Num_ *Work_Num)
{
    Work_Num->L1 = Val;
    Work_Num->L2 = Val;
    Work_Num->L3 = Val;
    Work_Num->L4 = Val;
    Work_Num->L5 = Val;
    Work_Num->L6 = Val;
    Work_Num->L7 = Val;
    Work_Num->L8 = Val;
	Work_Num->L9 = Val;
}

/*
*****************************************************************
 * ����ԭ�ͣ� void SetALL_int8(uint8_t Val,_Work_Num_Flag *Work_Num)
 * ��    �ܣ� ���ṹͼ�еĲ�����ֵ-uint8_t��
 * ��    ��:  Val �����ֵ  Work_Num���ṹ�壬Ҫ��&������
 * ��    ���� uint8_t Val,_Work_Num_Flag *Work_Num
*****************************************************************
*/
void SetALL_int8(uint8_t Val,_Work_Num_Flag *Work_Num)
{
    Work_Num->L1 = Val;
    Work_Num->L2 = Val;
    Work_Num->L3 = Val;
    Work_Num->L4 = Val;
    Work_Num->L5 = Val;
    Work_Num->L6 = Val;
    Work_Num->L7 = Val;
    Work_Num->L8 = Val;
	Work_Num->L9 = Val;
}

/*
*****************************************************************
 * ����ԭ�ͣ� void SetALL_int32(uint32_t Val,_Work_Num_long *Work_Num)
 * ��    �ܣ� ���ṹͼ�еĲ�����ֵ-uint32_t��
 * ��    ��:  Val �����ֵ  Work_Num���ṹ�壬Ҫ��&������
 * ��    ���� uint32_t Val,_Work_Num_long *Work_Num
*****************************************************************
*/
void SetALL_int32(uint32_t Val,_Work_Num_long *Work_Num)
{
    Work_Num->L1 = Val;
    Work_Num->L2 = Val;
    Work_Num->L3 = Val;
    Work_Num->L4 = Val;
    Work_Num->L5 = Val;
    Work_Num->L6 = Val;
    Work_Num->L7 = Val;
    Work_Num->L8 = Val;
	Work_Num->L9 = Val;
}

/*
*****************************************************************
 * ����ԭ�ͣ� void SetALL_TimeOver(_Work_Num_long *Work_Num1,_Work_Num_long *Work_Num)
 * ��    �ܣ� //�������ṹ������Ĳ�����Ӧ��ֵ�����ڽ���ʱ�临ԭ
 * ��    ��:  Work_Num1 �ṹ�壬Ҫ��&������  Work_Num���ṹ�壬Ҫ��&������
 * ��    ���� _Work_Num_long *Work_Num1,_Work_Num_long *Work_Num
*****************************************************************
*/
void SetALL_TimeOver(_Work_Num_long *Work_Num1,_Work_Num_long *Work_Num)
{
    Work_Num1->L1 = Work_Num->L1;
    Work_Num1->L2 = Work_Num->L2;
    Work_Num1->L3 = Work_Num->L3;
    Work_Num1->L4 = Work_Num->L4;
    Work_Num1->L5 = Work_Num->L5;
    Work_Num1->L6 = Work_Num->L6;
    Work_Num1->L7 = Work_Num->L7;
    Work_Num1->L8 = Work_Num->L8;
	Work_Num1->L9 = Work_Num->L9;
}

/*
*****************************************************************
 * ����ԭ�ͣ� void SetALL_SpeedOver(_Work_Num_ *Work_Num1,_Work_Num_ *Work_Num)
 * ��    �ܣ� �������ṹ������Ĳ�����Ӧ��ֵ�����ڽ���ʱ���ٶȸ�ԭ
 * ��    ��:  Work_Num1 �ṹ�壬Ҫ��&������  Work_Num���ṹ�壬Ҫ��&������
 * ��    ���� _Work_Num_ *Work_Num1,_Work_Num_ *Work_Num
*****************************************************************
*/
void SetALL_SpeedOver(_Work_Num_ *Work_Num1,_Work_Num_ *Work_Num)
{
    Work_Num1->L1 = Work_Num->L1;
    Work_Num1->L2 = Work_Num->L2;
    Work_Num1->L3 = Work_Num->L3;
    Work_Num1->L4 = Work_Num->L4;
    Work_Num1->L5 = Work_Num->L5;
    Work_Num1->L6 = Work_Num->L6;
    Work_Num1->L7 = Work_Num->L7;
    Work_Num1->L8 = Work_Num->L8;
	Work_Num1->L9 = Work_Num->L9;
}
/*
*****************************************************************
 * ����ԭ�ͣ� void Speed_ALL(uint8_t work,_Work_Num_ *Work_Num,_Work_Num_ *Work_Num1)
 * ��    �ܣ� ͬ�����ܣ������й�λ���ٶ�ͬ��
 * ��    ��:  work ��λ�� Work_Num �ṹ�壬Ҫ��&������  Work_Num1���ṹ�壬Ҫ��&������
 * ��    ���� uint8_t work,_Work_Num_ *Work_Num,_Work_Num_ *Work_Num1
*****************************************************************
*/
void Speed_ALL(uint8_t work,_Work_Num_ *Work_Num,_Work_Num_ *Work_Num1)
{
    switch(work)
    {
        case 1: Work_Num->L1 = Work_Num1->L1;
                Work_Num->L2 = Work_Num1->L1;
                Work_Num->L3 = Work_Num1->L1;
                Work_Num->L4 = Work_Num1->L1;
                Work_Num->L5 = Work_Num1->L1;
                Work_Num->L6 = Work_Num1->L1;
                Work_Num->L7 = Work_Num1->L1;
                Work_Num->L8 = Work_Num1->L1;
				Work_Num->L9 = Work_Num1->L1;
                break;
        case 2:Work_Num->L2 = Work_Num1->L2;
                Work_Num->L1 = Work_Num1->L2;
                Work_Num->L3 = Work_Num1->L2;
                Work_Num->L4 = Work_Num1->L2;
                Work_Num->L5 = Work_Num1->L2;
                Work_Num->L6 = Work_Num1->L2;
                Work_Num->L7 = Work_Num1->L2;
                Work_Num->L8 = Work_Num1->L2;
				Work_Num->L9 = Work_Num1->L2;
                break;
        case 3:Work_Num->L3 = Work_Num1->L3;
                Work_Num->L1 = Work_Num1->L3;
                Work_Num->L2 = Work_Num1->L3;
                Work_Num->L4 = Work_Num1->L3;
                Work_Num->L5 = Work_Num1->L3;
                Work_Num->L6 = Work_Num1->L3;
                Work_Num->L7 = Work_Num1->L3;
                Work_Num->L8 = Work_Num1->L3;
				Work_Num->L9 = Work_Num1->L3;
                break;
        case 4:Work_Num->L4 = Work_Num1->L4;
                Work_Num->L1 = Work_Num1->L4;
                Work_Num->L2 = Work_Num1->L4;
                Work_Num->L3 = Work_Num1->L4;
                Work_Num->L5 = Work_Num1->L4;
                Work_Num->L6 = Work_Num1->L4;
                Work_Num->L7 = Work_Num1->L4;
                Work_Num->L8 = Work_Num1->L4;
				Work_Num->L9 = Work_Num1->L4;
                break;
        case 5:
                Work_Num->L5 = Work_Num1->L5;
                Work_Num->L1 = Work_Num1->L5;
                Work_Num->L2 = Work_Num1->L5;
                Work_Num->L3 = Work_Num1->L5;
                Work_Num->L4 = Work_Num1->L5;
                Work_Num->L6 = Work_Num1->L5;
                Work_Num->L7 = Work_Num1->L5;
                Work_Num->L8 = Work_Num1->L5;
				Work_Num->L9 = Work_Num1->L5;
                break;
        case 6:Work_Num->L6 = Work_Num1->L6;
                Work_Num->L1 = Work_Num1->L6;
                Work_Num->L2 = Work_Num1->L6;
                Work_Num->L3 = Work_Num1->L6;
                Work_Num->L4 = Work_Num1->L6;
                Work_Num->L5 = Work_Num1->L6;
                Work_Num->L7 = Work_Num1->L6;
                Work_Num->L8 = Work_Num1->L6;
				Work_Num->L9 = Work_Num1->L6;
                break;
        case 7:Work_Num->L7 = Work_Num1->L7;
                Work_Num->L1 = Work_Num1->L7;
                Work_Num->L2 = Work_Num1->L7;
                Work_Num->L3 = Work_Num1->L7;
                Work_Num->L4 = Work_Num1->L7;
                Work_Num->L5 = Work_Num1->L7;
                Work_Num->L6 = Work_Num1->L7;
                Work_Num->L8 = Work_Num1->L7;
				Work_Num->L9 = Work_Num1->L7;
                break;
        case 8:Work_Num->L8 = Work_Num1->L8;
                Work_Num->L1 = Work_Num1->L8;
                Work_Num->L2 = Work_Num1->L8;
                Work_Num->L3 = Work_Num1->L8;
                Work_Num->L4 = Work_Num1->L8;
                Work_Num->L5 = Work_Num1->L8;
                Work_Num->L6 = Work_Num1->L8;
                Work_Num->L7 = Work_Num1->L8;
				Work_Num->L9 = Work_Num1->L8;
                break;  
		case 9:Work_Num->L9 = Work_Num1->L9;
                Work_Num->L1 = Work_Num1->L9;
                Work_Num->L2 = Work_Num1->L9;
                Work_Num->L3 = Work_Num1->L9;
                Work_Num->L4 = Work_Num1->L9;
                Work_Num->L5 = Work_Num1->L9;
                Work_Num->L6 = Work_Num1->L9;
                Work_Num->L7 = Work_Num1->L9;
				Work_Num->L8 = Work_Num1->L9;
                break;  
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Time_ALL(uint8_t work,_Work_Num_long *Work_Num,_Work_Num_long *Work_Num1)
 * ��    �ܣ� ͬ�����ܣ������й�λ��ʱ��ͬ��
 * ��    ��:  work ��λ�� Work_Num �ṹ�壬Ҫ��&������  Work_Num1���ṹ�壬Ҫ��&������
 * ��    ���� uint8_t work,_Work_Num_long *Work_Num,_Work_Num_long *Work_Num1
*****************************************************************
*/
void Time_ALL(uint8_t work,_Work_Num_long *Work_Num,_Work_Num_long *Work_Num1)
{
    switch(work)
    {
        case 1: Work_Num->L1 = Work_Num1->L1;
                Work_Num->L2 = Work_Num1->L1;
                Work_Num->L3 = Work_Num1->L1;
                Work_Num->L4 = Work_Num1->L1;
                Work_Num->L5 = Work_Num1->L1;
                Work_Num->L6 = Work_Num1->L1;
                Work_Num->L7 = Work_Num1->L1;
                Work_Num->L8 = Work_Num1->L1;
				Work_Num->L9 = Work_Num1->L1;
                break;
        case 2:Work_Num->L2 = Work_Num1->L2;
                Work_Num->L1 = Work_Num1->L2;
                Work_Num->L3 = Work_Num1->L2;
                Work_Num->L4 = Work_Num1->L2;
                Work_Num->L5 = Work_Num1->L2;
                Work_Num->L6 = Work_Num1->L2;
                Work_Num->L7 = Work_Num1->L2;
                Work_Num->L8 = Work_Num1->L2;
				Work_Num->L9 = Work_Num1->L2;
                break;
        case 3:Work_Num->L3 = Work_Num1->L3;
                Work_Num->L1 = Work_Num1->L3;
                Work_Num->L2 = Work_Num1->L3;
                Work_Num->L4 = Work_Num1->L3;
                Work_Num->L5 = Work_Num1->L3;
                Work_Num->L6 = Work_Num1->L3;
                Work_Num->L7 = Work_Num1->L3;
                Work_Num->L8 = Work_Num1->L3;
				Work_Num->L9 = Work_Num1->L3;
                break;
        case 4:Work_Num->L4 = Work_Num1->L4;
                Work_Num->L1 = Work_Num1->L4;
                Work_Num->L2 = Work_Num1->L4;
                Work_Num->L3 = Work_Num1->L4;
                Work_Num->L5 = Work_Num1->L4;
                Work_Num->L6 = Work_Num1->L4;
                Work_Num->L7 = Work_Num1->L4;
                Work_Num->L8 = Work_Num1->L4;
				Work_Num->L9 = Work_Num1->L4;
                break;
        case 5:
                Work_Num->L5 = Work_Num1->L5;
                Work_Num->L1 = Work_Num1->L5;
                Work_Num->L2 = Work_Num1->L5;
                Work_Num->L3 = Work_Num1->L5;
                Work_Num->L4 = Work_Num1->L5;
                Work_Num->L6 = Work_Num1->L5;
                Work_Num->L7 = Work_Num1->L5;
                Work_Num->L8 = Work_Num1->L5;
				Work_Num->L9 = Work_Num1->L5;
                break;
        case 6:Work_Num->L6 = Work_Num1->L6;
                Work_Num->L1 = Work_Num1->L6;
                Work_Num->L2 = Work_Num1->L6;
                Work_Num->L3 = Work_Num1->L6;
                Work_Num->L4 = Work_Num1->L6;
                Work_Num->L5 = Work_Num1->L6;
                Work_Num->L7 = Work_Num1->L6;
                Work_Num->L8 = Work_Num1->L6;
				Work_Num->L9 = Work_Num1->L6;
                break;
        case 7:Work_Num->L7 = Work_Num1->L7;
                Work_Num->L1 = Work_Num1->L7;
                Work_Num->L2 = Work_Num1->L7;
                Work_Num->L3 = Work_Num1->L7;
                Work_Num->L4 = Work_Num1->L7;
                Work_Num->L5 = Work_Num1->L7;
                Work_Num->L6 = Work_Num1->L7;
                Work_Num->L8 = Work_Num1->L7;
				Work_Num->L9 = Work_Num1->L7;
                break;
        case 8:Work_Num->L8 = Work_Num1->L8;
                Work_Num->L1 = Work_Num1->L8;
                Work_Num->L2 = Work_Num1->L8;
                Work_Num->L3 = Work_Num1->L8;
                Work_Num->L4 = Work_Num1->L8;
                Work_Num->L5 = Work_Num1->L8;
                Work_Num->L6 = Work_Num1->L8;
                Work_Num->L7 = Work_Num1->L8;
				Work_Num->L9 = Work_Num1->L8;
                break;        
		case 9:Work_Num->L9 = Work_Num1->L9;
                Work_Num->L1 = Work_Num1->L9;
                Work_Num->L2 = Work_Num1->L9;
                Work_Num->L3 = Work_Num1->L9;
                Work_Num->L4 = Work_Num1->L9;
                Work_Num->L5 = Work_Num1->L9;
                Work_Num->L6 = Work_Num1->L9;
                Work_Num->L7 = Work_Num1->L9;
				Work_Num->L8 = Work_Num1->L9;
                break;    
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Flag_ALL(uint8_t work,_Work_Num_Flag *Work_Num,_Work_Num_Flag *Work_Num1)
 * ��    �ܣ� ͬ�����ܣ������й�λ��flagͬ��
 * ��    ��:  work ��λ�� Work_Num �ṹ�壬Ҫ��&������  Work_Num1���ṹ�壬Ҫ��&������
 * ��    ���� uint8_t work,_Work_Num_Flag *Work_Num,_Work_Num_Flag *Work_Num1
*****************************************************************
*/
void Flag_ALL(uint8_t work,_Work_Num_Flag *Work_Num,_Work_Num_Flag *Work_Num1)
{
    switch(work)
    {
        case 1: Work_Num->L1 = Work_Num1->L1;
                Work_Num->L2 = Work_Num1->L1;
                Work_Num->L3 = Work_Num1->L1;
                Work_Num->L4 = Work_Num1->L1;
                Work_Num->L5 = Work_Num1->L1;
                Work_Num->L6 = Work_Num1->L1;
                Work_Num->L7 = Work_Num1->L1;
                Work_Num->L8 = Work_Num1->L1;
				Work_Num->L9 = Work_Num1->L1;
                break;
        case 2:Work_Num->L2 = Work_Num1->L2;
                Work_Num->L1 = Work_Num1->L2;
                Work_Num->L3 = Work_Num1->L2;
                Work_Num->L4 = Work_Num1->L2;
                Work_Num->L5 = Work_Num1->L2;
                Work_Num->L6 = Work_Num1->L2;
                Work_Num->L7 = Work_Num1->L2;
                Work_Num->L8 = Work_Num1->L2;
				Work_Num->L9 = Work_Num1->L2;
                break;
        case 3:Work_Num->L3 = Work_Num1->L3;
                Work_Num->L1 = Work_Num1->L3;
                Work_Num->L2 = Work_Num1->L3;
                Work_Num->L4 = Work_Num1->L3;
                Work_Num->L5 = Work_Num1->L3;
                Work_Num->L6 = Work_Num1->L3;
                Work_Num->L7 = Work_Num1->L3;
                Work_Num->L8 = Work_Num1->L3;
				Work_Num->L9 = Work_Num1->L3;
                break;
        case 4:Work_Num->L4 = Work_Num1->L4;
                Work_Num->L1 = Work_Num1->L4;
                Work_Num->L2 = Work_Num1->L4;
                Work_Num->L3 = Work_Num1->L4;
                Work_Num->L5 = Work_Num1->L4;
                Work_Num->L6 = Work_Num1->L4;
                Work_Num->L7 = Work_Num1->L4;
                Work_Num->L8 = Work_Num1->L4;
				Work_Num->L9 = Work_Num1->L4;
                break;
        case 5:
                Work_Num->L5 = Work_Num1->L5;
                Work_Num->L1 = Work_Num1->L5;
                Work_Num->L2 = Work_Num1->L5;
                Work_Num->L3 = Work_Num1->L5;
                Work_Num->L4 = Work_Num1->L5;
                Work_Num->L6 = Work_Num1->L5;
                Work_Num->L7 = Work_Num1->L5;
                Work_Num->L8 = Work_Num1->L5;
				Work_Num->L9 = Work_Num1->L5;
                break;
        case 6:Work_Num->L6 = Work_Num1->L6;
                Work_Num->L1 = Work_Num1->L6;
                Work_Num->L2 = Work_Num1->L6;
                Work_Num->L3 = Work_Num1->L6;
                Work_Num->L4 = Work_Num1->L6;
                Work_Num->L5 = Work_Num1->L6;
                Work_Num->L7 = Work_Num1->L6;
                Work_Num->L8 = Work_Num1->L6;
				Work_Num->L9 = Work_Num1->L6;
                break;
        case 7:Work_Num->L7 = Work_Num1->L7;
                Work_Num->L1 = Work_Num1->L7;
                Work_Num->L2 = Work_Num1->L7;
                Work_Num->L3 = Work_Num1->L7;
                Work_Num->L4 = Work_Num1->L7;
                Work_Num->L5 = Work_Num1->L7;
                Work_Num->L6 = Work_Num1->L7;
                Work_Num->L8 = Work_Num1->L7;
				Work_Num->L9 = Work_Num1->L7;
                break;
        case 8:Work_Num->L8 = Work_Num1->L8;
                Work_Num->L1 = Work_Num1->L8;
                Work_Num->L2 = Work_Num1->L8;
                Work_Num->L3 = Work_Num1->L8;
                Work_Num->L4 = Work_Num1->L8;
                Work_Num->L5 = Work_Num1->L8;
                Work_Num->L6 = Work_Num1->L8;
                Work_Num->L7 = Work_Num1->L8;
				Work_Num->L9 = Work_Num1->L8;
                break;      
		case 9:Work_Num->L9 = Work_Num1->L9;
                Work_Num->L1 = Work_Num1->L9;
                Work_Num->L2 = Work_Num1->L9;
                Work_Num->L3 = Work_Num1->L9;
                Work_Num->L4 = Work_Num1->L9;
                Work_Num->L5 = Work_Num1->L9;
                Work_Num->L6 = Work_Num1->L9;
                Work_Num->L7 = Work_Num1->L9;
				Work_Num->L9 = Work_Num1->L9;
				Work_Num->L8 = Work_Num1->L9;
                break;   				
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Set_Speeds(_Work_Num_ *Work_Num,_Work_Num_ *Work_Num1,_Work_Num_ *Work_Num2,_Work_Num_ *Work_Num3,_Work_Num_ *Work_Num4,_Work_Num_ *Work_Num5)
 * ��    �ܣ� �ж������ٶ���ֵ�Ƿ�ı�
 * ��    ��:  Work_Num ��ʱ�洢���ٶȣ�Ҫ��&������  Work_Num1�����õ��ٶȣ�Ҫ��&������ Work_Num2��Ҫ��ֵ���ٶȣ�Ҫ��&������
 * ��    ���� _Work_Num_ *Work_Num,_Work_Num_ *Work_Num1,_Work_Num_ *Work_Num2
*****************************************************************
*/
void Set_Speeds(_Work_Num_ *Work_Num,_Work_Num_ *Work_Num1,_Work_Num_ *Work_Num2,_Work_Num_ *Work_Num3,_Work_Num_ *Work_Num4,_Work_Num_ *Work_Num5)
{
   if(Work_Num->L1 != Work_Num1->L1)
   {
       Work_Num2->L1 = Work_Num1->L1;
	   Work_Num3->L1 = Work_Num1->L1;
	   Work_Num4->L1 = Work_Num1->L1;
	   Work_Num5->L1 = Work_Num1->L1;
	   Save_Param_En = 1;
       if(Speed_ADDMode.L1 != 0)//���繤λֻ�������������������ٶȵ�����²�����0������δ����ģʽ��
            Speed_ADDMode.L1 = 0;//����δ�����жϼ��ٻ��Ǽ���
   }
   if(Work_Num->L2 != Work_Num1->L2)
   {
		Work_Num2->L2 = Work_Num1->L2;
		Work_Num3->L2 = Work_Num1->L2;
		Work_Num4->L2 = Work_Num1->L2;
		Work_Num5->L2 = Work_Num1->L2;
		Save_Param_En = 1;
		if(Speed_ADDMode.L2 != 0)//���繤λֻ�������������������ٶȵ�����²�����0������δ����ģʽ��
                Speed_ADDMode.L2 = 0;//����δ�����жϼ��ٻ��Ǽ���  
   }
   if(Work_Num->L3 != Work_Num1->L3)
   {
        Work_Num2->L3 = Work_Num1->L3;
	    Work_Num3->L3 = Work_Num1->L3;
	    Work_Num4->L3 = Work_Num1->L3;
	    Work_Num5->L3 = Work_Num1->L3;
		Save_Param_En = 1;
        if(Speed_ADDMode.L3 != 0)//���繤λֻ�������������������ٶȵ�����²�����0������δ����ģʽ��
            Speed_ADDMode.L3 = 0;//����δ�����жϼ��ٻ��Ǽ���  
   }
   if(Work_Num->L4 != Work_Num1->L4)
   {
		Work_Num2->L4 = Work_Num1->L4; 
		Work_Num3->L4 = Work_Num1->L4; 
		Work_Num4->L4 = Work_Num1->L4; 
		Work_Num5->L4 = Work_Num1->L4; 
		Save_Param_En = 1;
       if(Speed_ADDMode.L4 != 0)//���繤λֻ�������������������ٶȵ�����²�����0������δ����ģʽ��
                Speed_ADDMode.L4 = 0;//����δ�����жϼ��ٻ��Ǽ���  
   }
   if(Work_Num->L5 != Work_Num1->L5)
   {
		Work_Num2->L5 = Work_Num1->L5;
		Work_Num3->L5 = Work_Num1->L5;
		Work_Num4->L5 = Work_Num1->L5;
		Work_Num5->L5 = Work_Num1->L5;
		Save_Param_En = 1;
       if(Speed_ADDMode.L5 != 0)//���繤λֻ�������������������ٶȵ�����²�����0������δ����ģʽ��
                Speed_ADDMode.L5 = 0;//����δ�����жϼ��ٻ��Ǽ���  
   }
   if(Work_Num->L6 != Work_Num1->L6)
   {
        Work_Num2->L6 = Work_Num1->L6;
	    Work_Num3->L6 = Work_Num1->L6;
	    Work_Num4->L6 = Work_Num1->L6;
	    Work_Num5->L6 = Work_Num1->L6;
		Save_Param_En = 1;
       if(Speed_ADDMode.L6 != 0)//���繤λֻ�������������������ٶȵ�����²�����0������δ����ģʽ��
                Speed_ADDMode.L6 = 0;//����δ�����жϼ��ٻ��Ǽ���  
   }
   if(Work_Num->L7 != Work_Num1->L7)
   {
        Work_Num2->L7 = Work_Num1->L7;
		Work_Num3->L7 = Work_Num1->L7;
		Work_Num4->L7 = Work_Num1->L7;
		Work_Num5->L7 = Work_Num1->L7;
		Save_Param_En = 1;
        if(Speed_ADDMode.L7 != 0)//���繤λֻ�������������������ٶȵ�����²�����0������δ����ģʽ��
                Speed_ADDMode.L7 = 0;//����δ�����жϼ��ٻ��Ǽ���  
   }
   if(Work_Num->L8 != Work_Num1->L8)
   {
       Work_Num2->L8 = Work_Num1->L8;
	   Work_Num3->L8 = Work_Num1->L8;
	   Work_Num4->L8 = Work_Num1->L8;
	   Work_Num5->L8 = Work_Num1->L8;
	   Save_Param_En = 1;
       if(Speed_ADDMode.L8 != 0)//���繤λֻ�������������������ٶȵ�����²�����0������δ����ģʽ��
                Speed_ADDMode.L8 = 0;//����δ�����жϼ��ٻ��Ǽ���
   }
   if(Work_Num->L9 != Work_Num1->L9)
   {
       Work_Num2->L9 = Work_Num1->L9;
	   Work_Num3->L9 = Work_Num1->L9;
	   Work_Num4->L9 = Work_Num1->L9;
	   Work_Num5->L9 = Work_Num1->L9;
	   Save_Param_En = 1;
       if(Speed_ADDMode.L9 != 0)//���繤λֻ�������������������ٶȵ�����²�����0������δ����ģʽ��
                Speed_ADDMode.L9 = 0;//����δ�����жϼ��ٻ��Ǽ���
   }
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Set_Times(_Work_Num_long *Work_Num,_Work_Num_long *Work_Num1,_Work_Num_long *Work_Num2,_Work_Num_long *Work_Num3,_Work_Num_long *Work_Num4,_Work_Num_long *Work_Num5)
 * ��    �ܣ� �ж�����ʱ����ֵ�Ƿ�ı�
 * ��    ��:  Work_Num ��ʱ�洢��ʱ�䣬Ҫ��&������  Work_Num1�����õ�ʱ�䣬Ҫ��&������ Work_Num2��Ҫ��ֵ��ʱ�䣬Ҫ��&������
 * ��    ���� _Work_Num_long *Work_Num,_Work_Num_long *Work_Num1,_Work_Num_long *Work_Num2
*****************************************************************
*/
void Set_Times(_Work_Num_long *Work_Num,_Work_Num_long *Work_Num1,_Work_Num_long *Work_Num2,_Work_Num_long *Work_Num3,_Work_Num_long *Work_Num4,_Work_Num_long *Work_Num5)
{
   if(Work_Num->L1 != Work_Num1->L1)
   {
       Work_Num2->L1 = Work_Num1->L1;
	   Work_Num3->L1 = Work_Num1->L1;
	   Work_Num4->L1 = Work_Num1->L1;
	   Work_Num5->L1 = Work_Num1->L1;
	   Save_Param_En = 1;
       RelTime_State.L1 = SetTime_State.L1;//ͬ��ʱ��״̬
	   DownTime_Over.L1 = 0;
   }
   if(Work_Num->L2 != Work_Num1->L2)
   {
       Work_Num2->L2 = Work_Num1->L2;
	   Work_Num3->L2 = Work_Num1->L2;
	   Work_Num4->L2 = Work_Num1->L2;
	   Work_Num5->L2 = Work_Num1->L2;
	   Save_Param_En = 1;
       RelTime_State.L2 = SetTime_State.L2;//ͬ��ʱ��״̬
	   DownTime_Over.L2 = 0;
   }
   if(Work_Num->L3 != Work_Num1->L3)
   {
       Work_Num2->L3 = Work_Num1->L3;
	   Work_Num3->L3 = Work_Num1->L3;
	   Work_Num4->L3 = Work_Num1->L3;
	   Work_Num5->L3 = Work_Num1->L3;
		Save_Param_En = 1;
        RelTime_State.L3 = SetTime_State.L3;//ͬ��ʱ��״̬
	   DownTime_Over.L3 = 0;
   }
   if(Work_Num->L4 != Work_Num1->L4)
   {
       Work_Num2->L4 = Work_Num1->L4; 
	   Work_Num3->L4 = Work_Num1->L4; 
	   Work_Num4->L4 = Work_Num1->L4; 
	   Work_Num5->L4 = Work_Num1->L4;
		Save_Param_En = 1;
       RelTime_State.L4 = SetTime_State.L4;//ͬ��ʱ��״̬
	   DownTime_Over.L4 = 0;
   }
   if(Work_Num->L5 != Work_Num1->L5)
   {
       Work_Num2->L5 = Work_Num1->L5;
	   Work_Num3->L5 = Work_Num1->L5;
	   Work_Num4->L5 = Work_Num1->L5;
	   Work_Num5->L5 = Work_Num1->L5;
		Save_Param_En = 1;
       RelTime_State.L5 = SetTime_State.L5;//ͬ��ʱ��״̬
	   DownTime_Over.L5 = 0;
   }
   if(Work_Num->L6 != Work_Num1->L6)
   {
       Work_Num2->L6 = Work_Num1->L6;
	   Work_Num3->L6 = Work_Num1->L6;
	   Work_Num4->L6 = Work_Num1->L6;
	   Work_Num5->L6 = Work_Num1->L6;
		Save_Param_En = 1;
       RelTime_State.L6 = SetTime_State.L6;//ͬ��ʱ��״̬
	   DownTime_Over.L6 = 0;
   }
   if(Work_Num->L7 != Work_Num1->L7)
   {
       Work_Num2->L7 = Work_Num1->L7;
	   Work_Num3->L7 = Work_Num1->L7;
	   Work_Num4->L7 = Work_Num1->L7;
	   Work_Num5->L7 = Work_Num1->L7;
		Save_Param_En = 1;
       RelTime_State.L7 = SetTime_State.L7;//ͬ��ʱ��״̬
	   DownTime_Over.L7 = 0;
   }  
   if(Work_Num->L8 != Work_Num1->L8)
   {
       Work_Num2->L8 = Work_Num1->L8;
	   Work_Num3->L8 = Work_Num1->L8;
	   Work_Num4->L8 = Work_Num1->L8;
	   Work_Num5->L8 = Work_Num1->L8;
		Save_Param_En = 1;
       RelTime_State.L8 = SetTime_State.L8;//ͬ��ʱ��״̬
	   DownTime_Over.L8 = 0;
   }
   if(Work_Num->L9 != Work_Num1->L9)
   {
       Work_Num2->L9 = Work_Num1->L9;
	   Work_Num3->L9 = Work_Num1->L9;
	   Work_Num4->L9 = Work_Num1->L9;
	   Work_Num5->L9 = Work_Num1->L9;
		Save_Param_En = 1;
       RelTime_State.L9 = SetTime_State.L9;//ͬ��ʱ��״̬
	   DownTime_Over.L9 = 0;
   }
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_Time_State(_Work_Num_Flag *Work_Num,_Work_Num_long *Work_Num1);
 * ��    �ܣ��ж�ʱ��״̬
 * ��    ��: Work_Num ʵ��ʱ��״̬��Ҫ��&������  Work_Num1�����õ�ʱ�䣬Ҫ��&������
 * ��    ����_Work_Num_Flag *Work_Num,_Work_Num_long *Work_Num1
*****************************************************************
*/
void Check_Time_State(_Work_Num_Flag *Work_Num,_Work_Num_long *Work_Num1)
{
	if(Work_Num1->L1 > 0)
		Work_Num->L1 = 1;
	else
		Work_Num->L1 = 0;
	if(Work_Num1->L2 > 0)
		Work_Num->L2 = 1;
	else
		Work_Num->L2 = 0;
	if(Work_Num1->L3 > 0)
		Work_Num->L3 = 1;
	else
		Work_Num->L3 = 0;
	if(Work_Num1->L4 > 0)
		Work_Num->L4 = 1;
	else
		Work_Num->L4 = 0;
	if(Work_Num1->L5 > 0)
		Work_Num->L5 = 1;
	else
		Work_Num->L5 = 0;
	if(Work_Num1->L6 > 0)
		Work_Num->L6 = 1;
	else
		Work_Num->L6 = 0;
	if(Work_Num1->L7 > 0)
		Work_Num->L7 = 1;
	else
		Work_Num->L7 = 0;
	if(Work_Num1->L8 > 0)
		Work_Num->L8 = 1;
	else
		Work_Num->L8 = 0;
	if(Work_Num1->L9 > 0)
		Work_Num->L9 = 1;
	else
		Work_Num->L9 = 0;
}
