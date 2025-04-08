#include "Drv_EC11A.h"

/**********ȫ�ֱ�������******/
uint8_t EC11A_Knob;//��������ťʱ

/**********�ֲ���������******/
uint8_t EC11A_Flag;//�����ж���ʱ��־
uint8_t Key1_Press;//���°�ť
uint16_t KEY1_Count;//��¼KEY1���µ�ʱ��

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
	if(sys.Run_Status == 0)
	{
		if(EC11A_Knob)//��ť��ת��
			EC11A_Knob--;//1S����ʱ
	}
	else
	{
		if(EC11A_Knob > 0)
		{
			EC11A_Knob--;//1S����ʱ
			if(EC11A_Knob <= 0)
			{
				Ctrl_Speed = Set_Speed;
				Speed_ADDMode = 0;		
				Beep_Time = 0.1;//��������0.1S
			}
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
        /***********����ת**********/
        if(GPIO_Pin == KEY1B_Pin)//�����ť����
        {
            if((HAL_GPIO_ReadPin(KEY1A_GPIO_Port,KEY1A_Pin)==1)&&(HAL_GPIO_ReadPin(KEY1B_GPIO_Port,KEY1B_Pin)==0))//���������ת
            {
				if(sys.Run_Status == 1 && sys.Motor_Stop == 0)
				{
					Speed = Rel_Speed/Tooth_Ratio; 
					Set_Speed -= 10;
                    if(Set_Speed <= MIN_Speed)
                        Set_Speed = MIN_Speed;
					EC11A_Knob = 2;//����ǲ�����������ť
				}
                if(sys.SetMode_Option == 1)
                {
                    Set_Speed -= 10;
                    if(Set_Speed <= MIN_Speed)
                        Set_Speed = MIN_Speed;
                    Ctrl_Speed = Set_Speed;
					EC11A_Knob = 1;//����ǲ�����������ť
                }
                if(sys.SetMode_Option == 2)
                {
                    Set_Time -= 60;
                    if(Set_Time <= 0)
                    {
                        Time_State = 1;//��ʾ��----��
                        Set_Time = 0;
                    }
                    Time = Set_Time;
                    Ctrl_Time = Set_Time;
					EC11A_Knob = 1;//����ǲ�����������ť
					
                }
                Twinkle_Time = 6000;//��˸��ʾ6S  
            }
            else if((HAL_GPIO_ReadPin(KEY1A_GPIO_Port,KEY1A_Pin)==0)&&(HAL_GPIO_ReadPin(KEY1B_GPIO_Port,KEY1B_Pin)==0))//���������ת
            {
				if(sys.Run_Status == 1 && sys.Motor_Stop == 0)
				{
					Speed = Rel_Speed/Tooth_Ratio; 
					Set_Speed += 10;
                    if(Set_Speed >= MAX_Speed)
                        Set_Speed = MAX_Speed;
					EC11A_Knob = 2;//����ǲ�����������ť
				}
                if(sys.SetMode_Option == 1)
                {
                    Set_Speed += 10;
                    if(Set_Speed >= MAX_Speed)
                        Set_Speed = MAX_Speed;
                    Ctrl_Speed = Set_Speed;
					EC11A_Knob = 1;//����ǲ�����������ť
                }
                if(sys.SetMode_Option == 2)
                {
                    Set_Time += 60;
                    Time_State = 0;//����ʾ��----��
                    if(Set_Time >= 86400)
                        Set_Time = 86400;
                    Time = Set_Time;
                    Ctrl_Time = Set_Time;
					EC11A_Knob = 1;//����ǲ�����������ť
					
                }
                Twinkle_Time = 6000;//��˸��ʾ6S  
            }
        }
        EC11A_Flag = 0;//�ر��ж� 
    }

    /**********��߰�ť�ж�**********/
    if(GPIO_Pin ==KEY1_Pin)
    {
        Key1_Press = 1;//���±�־����һ
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
                    sys.SetMode_Option++;//����ģʽ++
                    if(sys.SetMode_Option == 3)
                    {
                        sys.SetMode_Option = 0;
                    }
                }
                else//�����µ���������ֱ��ֹͣ
                {
                    sys.Motor_Stop = 1;//�ر�����
					Speed_ADDMode = 2;//�������ģʽ��
                }
                Beep_Time = 0.1;//��������0.1S
                Twinkle_Time = 6000;//��˸��ʾ6S
                KEY1_Count = 0;//��ť��������
                Key1_Press = 0;//��ť״̬Ϊ̧��
            }
            else//����200ʱ������
            {
                KEY1_Count = 0;//��ť��������
                Key1_Press = 0;//��ť״̬Ϊ̧��
            }
        }
        if(KEY1_Count > 200 && KEY1_Count < 400)//����
        {
            if(sys.Run_Status == 0)
            {
                sys.Run_Status = 1;
                sys.SetMode_Option = 0;
				Speed_ADDMode = 0;
				Speed_Val.SumError=0x2422;//�������ϵ��
				Speed = 0;
            } 
            else
            {
                sys.Motor_Stop = 1;//�����
				Speed_ADDMode = 2;//�������ģʽ��
            }   
            Beep_Time = 0.1;//��������0.1S
            KEY1_Count = 400;//��ť��������200�������Ͳ�����̧���ٽ��뵥����
        }
    }
}
