#include "Drv_EC11A.h"

/**********ȫ�ֱ�������******/
uint8_t Work_Option;//ѡ��λ��
uint8_t SetMode_Option;//ѡ������ģʽ
uint8_t EC11A_Knob1,EC11A_Knob2;//��������ťʱ
uint8_t Run_Status;//ϵͳ״̬
uint8_t Work_All;//��λ������ͬ

/**********�ֲ���������******/
uint8_t EC11A_Flag;//�����ж���ʱ��־
uint8_t Key1_Press,Key2_Press;//���°�ť
uint16_t KEY1_Count,KEY2_Count;//��¼KEY1,KEY2���µ�ʱ��

/*
*****************************************************************
 * ����ԭ�ͣ�void EC11A_FlagCheak(uint16_t dT)
 * ��    �ܣ������ʱ�����ʱ-2ms
 * ��    ��: dT ������
 * ��    ����uint16_t dT
*****************************************************************
*/
void EC11A_FlagCheak(uint16_t dT)
{
    static uint16_t T;
    T += dT;//���ڼӼ�
    if(T % 4 == 0)//��ʱ4ms
    {
        EC11A_Flag = 1;//�����ж�
		T = 0;//��ʱ����
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_Knob(void)
 * ��    �ܣ������ť״̬-500ms
*****************************************************************
*/
void Check_Knob(void)
{
    if(EC11A_Knob1)//��ť��ת��
	{
        EC11A_Knob1--;//1S����ʱ
		if(EC11A_Knob1 == 0)//��ť��ת��
		{
			Twinkle_Time1 = 2000;//��˸ʱ��
		}
	}
	if(EC11A_Knob2)//��ť��ת��
	{
        EC11A_Knob2--;//1S����ʱ
		if(EC11A_Knob2 == 0)//��ť��ת��
		{
			Twinkle_Time2 = 2000;//��˸ʱ��
		}
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ�void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
 * ��    �ܣ��ⲿ�ж�
*****************************************************************
*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(EC11A_Flag == 1)//�����ж�
    {
        /***********����ť***********/
        if(GPIO_Pin == KEY2B_Pin)//�ұ���ť����
        {
            if((HAL_GPIO_ReadPin(KEY2A_GPIO_Port,KEY2A_Pin)==0)&&(HAL_GPIO_ReadPin(KEY2B_GPIO_Port,KEY2B_Pin)==0))//���������ת
            {
                Set_Speed+=10;
				Set_Speed = (Set_Speed > 3000) ? 3000 : Set_Speed;//�ٶȲ�����3000ת
            }
            else if((HAL_GPIO_ReadPin(KEY2A_GPIO_Port,KEY2A_Pin)==1)&&(HAL_GPIO_ReadPin(KEY2B_GPIO_Port,KEY2B_Pin)==0))//���������ת
            {
                Set_Speed-=10;
				Set_Speed = (Set_Speed < 1500) ? 1500 : Set_Speed;//�ٶ�����С��1500תʱ����
            }
			EC11A_Knob1 = 1;
        }

        /***********����ת**********/
		if(GPIO_Pin == KEY1B_Pin)//�����ť����
		{
			if((HAL_GPIO_ReadPin(KEY1A_GPIO_Port,KEY1A_Pin)==0)&&(HAL_GPIO_ReadPin(KEY1B_GPIO_Port,KEY1B_Pin)==0))//���������ת
			{
				Set_Time += 60;
				Set_Time = (Set_Time > 28800) ? 28800 : Set_Time;//ʱ������趨8Сʱ
			}
			else if((HAL_GPIO_ReadPin(KEY1A_GPIO_Port,KEY1A_Pin)==1)&&(HAL_GPIO_ReadPin(KEY1B_GPIO_Port,KEY1B_Pin)==0))//���������ת
			{
				Set_Time -= 60;
				Set_Time = (Set_Time < 60) ? 0 : Set_Time;//ʱ��С��1���Ӳ��趨
			}
			Time_State  = (Set_Time < 60) ? 0 : 1;//�ж��Ƿ�������ʱ��
			EC11A_Knob2 = 1;
		}
        EC11A_Flag = 0;//�ر��ж� 
    }

    /**********��߰�ť�ж�**********/
    if(GPIO_Pin ==KEY1_Pin)
    {
        Key1_Press = 1;//���±�־����һ
    }

    /**********�ұ߰�ť�ж�**********/
    if(GPIO_Pin ==KEY2_Pin)
    {
        Key2_Press = 1;//���±�־����һ
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_KeyState(void)
 * ��    �ܣ��������
*****************************************************************
*/
void Check_KeyState(void)
{
    /**********KEY1**********/
    if(Key1_Press == 1)//��ť������
    {
        if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==0)//���KEY1����
            KEY1_Count++;//����ʱ��++
        if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==1)//���KEY1̧��
        {
            if(KEY1_Count < 200)//�̰�
            {
                if(sys.Run_Status == 0)
				{
					Speed_ADDMode = 0;
					sys.Run_Status = 1;
					SpeedSet_Flag = 1;
					TimeSet_Flag = 1;
					Twinkle_Time1 =0;
					EC11A_Knob1=0;
					Twinkle_Time2 =0; 
					EC11A_Knob2=0;
				}
				else
				{
					sys.Run_Status = 0;//�����
					Speed_ADDMode = 2;//�������ģʽ��
				}
            }
            else//����200ʱ������
            {
                KEY1_Count = 0;//��ť��������
                Key1_Press = 0;//��ť״̬Ϊ̧��
            }
			KEY1_Count = 0;//��ť��������
            Key1_Press = 0;//��ť״̬Ϊ̧��			
        }
        if(KEY1_Count > 200 && KEY1_Count < 400)//����
        {
            
            KEY1_Count = 400;//��ť��������200�������Ͳ�����̧���ٽ��뵥����
        }
    }
    /**********KEY2**********/
    if(Key2_Press == 1)//��ť������
    {
        if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==0)//���KEY2����
            KEY2_Count++;//����ʱ��++
        if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==1)//���KEY2̧��
        {
            if(KEY2_Count < 200)//�̰�
            {
				if(sys.Run_Status == 0)
				{
					Speed_ADDMode = 0;
					sys.Run_Status = 1;
					SpeedSet_Flag = 1;
					TimeSet_Flag = 1;
					Twinkle_Time1 =0;
					EC11A_Knob1=0;
					Twinkle_Time2 =0; 
					EC11A_Knob2=0;
				}
				else
				{
					sys.Run_Status = 0;//�����
					Speed_ADDMode = 2;//�������ģʽ��
				}
				KEY2_Count = 0;//��ť��������
                Key2_Press = 0;//��ť״̬Ϊ̧��
            }
            else//����200ʱ������
            {
                KEY2_Count = 0;//��ť��������
                Key2_Press = 0;//��ť״̬Ϊ̧��
            }
        }
        if(KEY2_Count > 200 && KEY2_Count < 400)//����
        {
			
			KEY2_Count = 400;//��ť��������200�������Ͳ�����̧���ٽ��뵥����
        }
    }
}
