#include "Drv_EC11A.h"

/**********�ṹ��************/
_EC11A_ EC11A[2];//��ť����

/*
*****************************************************************
 * ����ԭ�ͣ�void EC11A_Init(void)
 * ��    �ܣ�EC11A��ʼ����ʱ��
*****************************************************************
*/
void EC11A_Init(void)
{
	/**********EC11A_1**********/
	EC11A[0].EXTI_Pin = KEY1A_Pin;//EC11A��ť�ж�����
	EC11A[0].EC11A_Pin = KEY1B_Pin;//EC11A��ť��������
	EC11A[0].EC11A_GPIO = KEY1B_GPIO_Port;//EC11A��ť����GPIO�˿�
	
	EC11A[0].Key_Pin = KEY1_Pin;//EC11A������������
	EC11A[0].Key_GPIO = KEY1_GPIO_Port;//EC11A��������GPIO�˿�
	
	EC11A[0].Tim = &EC11A_Tim_1;//��ʱ��ѡ��
	EC11A[0].EC11A_Fast = EC11A_FastSpeed;//�ж���ת�ٶ���ֵ
	
	/**********EC11A_2**********/
	EC11A[1].EXTI_Pin = KEY2A_Pin;//EC11A��ť�ж�����
	EC11A[1].EC11A_Pin = KEY2B_Pin;//EC11A��ť��������
	EC11A[1].EC11A_GPIO = KEY2B_GPIO_Port;//EC11A��ť����GPIO�˿�
	
	EC11A[1].Key_Pin = KEY2_Pin;//EC11A������������
	EC11A[1].Key_GPIO = KEY2_GPIO_Port;//EC11A��������GPIO�˿�
	
	EC11A[1].Tim = &EC11A_Tim_2;//��ʱ��ѡ��
	EC11A[1].EC11A_Fast = EC11A_FastSpeed;//�ж���ת�ٶ���ֵ
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_Knob(float dT)
 * ��    �ܣ������ť��״̬-500ms
*****************************************************************
*/
void Check_Knob(float dT)
{
    if(EC11A[0].EC11A_Knob)//��ť0��ת
        EC11A[0].EC11A_Knob -= dT;//����ʱ
	
	if(EC11A[1].EC11A_Knob)//��ť1��ת
        EC11A[1].EC11A_Knob -= dT;//����ʱ
}

/*
*****************************************************************
 * ����ԭ�ͣ�void EC11A_Speed(float dT)
 * ��    �ܣ�EC11A��ť�ٶȼ���
*****************************************************************
*/
void EC11A_Speed(float dT)
{
	/**********EC11A_1**********/
	EC11A[0].EC11A_Speed = EC11A[0].EC11A_Cnt*60/20;//һ����һ�Ρ�תһȦ20��������һ���ӵ��ٶ�
	EC11A[0].EC11A_Cnt = 0;//����⵽�ļ�������
	
	/**********EC11A_2**********/
	EC11A[1].EC11A_Speed = EC11A[1].EC11A_Cnt*60/20;//һ����һ�Ρ�תһȦ20��������һ���ӵ��ٶ�
	EC11A[1].EC11A_Cnt = 0;//����⵽�ļ�������
}

/*
*****************************************************************
 * ����ԭ�ͣ�void EC11AKey_Scan(float dT)
 * ��    �ܣ�EC11A����ɨ��
*****************************************************************
*/
void EC11AKey_Scan(float dT)
{
	/**********EC11A_1**********///����ť
	if(HAL_GPIO_ReadPin(EC11A[0].Key_GPIO,EC11A[0].Key_Pin) == KEY_DOWN)//���°���
	{
		if(EC11A[0].LongPress == 0)//û�г�����
		{
			EC11A[0].Key_Cnt += dT;//����ʱ��++
			EC11A[0].Key_Flag = 1;//�������±�־��һ
		}
	}
	if(EC11A[0].Key_Flag == 1)//����������
	{
		if(HAL_GPIO_ReadPin(EC11A[0].Key_GPIO,EC11A[0].Key_Pin) == KEY_UP)//̧�𰴼�
		{   
			if(EC11A[0].Key_Cnt > 0.1 && EC11A[0].Key_Cnt < 1.5)//С��1.5S�ǵ���
			{
				if(sys.Run_Status == 0)
				{
					Speed_ADDMode = 0;
					sys.Run_Status = 1;
					SpeedSet_Flag = 1;
					TimeSet_Flag = 1;
					Twinkle_Time1 =0;
					EC11A[0].EC11A_Knob=0;
					Twinkle_Time2 =0; 
					EC11A[1].EC11A_Knob=0;
				}
				else
				{
					sys.Run_Status = 0;//�����
					Speed_ADDMode = 2;//�������ģʽ��
				}
				Beep_Time = 0.1;//��������0.1S
			}
			EC11A[0].Key_Flag = 0;//�����¼��������ȴ���һ�ΰ���
			EC11A[0].LongPress = 0;//������־����
			EC11A[0].Key_Cnt = 0;//��ť��������
		}
		if(EC11A[0].Key_Cnt > 1.5 && EC11A[0].Key_Cnt < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(EC11A[0].LongPress == 0)//���û��һֱһֱ������
			{
				
				EC11A[0].LongPress = 1;//������־��һ
			}
		}
	}
	
	/**********EC11A_2**********///�ұ���ť
	if(HAL_GPIO_ReadPin(EC11A[1].Key_GPIO,EC11A[1].Key_Pin) == KEY_DOWN)//���°���
	{
		if(EC11A[1].LongPress == 0)//û�г�����
		{
			EC11A[1].Key_Cnt += dT;//����ʱ��++
			EC11A[1].Key_Flag = 1;//�������±�־��һ
		}
	}
	if(EC11A[1].Key_Flag == 1)//����������
	{
		if(HAL_GPIO_ReadPin(EC11A[1].Key_GPIO,EC11A[1].Key_Pin) == KEY_UP)//̧�𰴼�
		{   
			if(EC11A[1].Key_Cnt > 0.1 && EC11A[1].Key_Cnt < 1.5)//С��1.5S�ǵ���
			{
				if(sys.Run_Status == 0)
				{
					Speed_ADDMode = 0;
					sys.Run_Status = 1;
					SpeedSet_Flag = 1;
					TimeSet_Flag = 1;
					Twinkle_Time1 =0;
					EC11A[0].EC11A_Knob=0;
					Twinkle_Time2 =0; 
					EC11A[1].EC11A_Knob=0;
				}
				else
				{
					sys.Run_Status = 0;//�����
					Speed_ADDMode = 2;//�������ģʽ��
				}
				Beep_Time = 0.1;//��������0.1S
			}
			EC11A[1].Key_Flag = 0;//�����¼��������ȴ���һ�ΰ���
			EC11A[1].LongPress = 0;//������־����
			EC11A[1].Key_Cnt = 0;//��ť��������
		}
		if(EC11A[1].Key_Cnt > 1.5 && EC11A[1].Key_Cnt < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(EC11A[1].LongPress == 0)//���û��һֱһֱ������
			{

				EC11A[1].LongPress = 1;//������־��һ
			}
		}
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ�void EC11A_EXTI_Interrupt(uint16_t GPIO_Pin)
 * ��    �ܣ�EC11A��ť�жϺ���
 * ��    �룺GPIO_Pin:����������
 * ��    ����uint16_t GPIO_Pin
*****************************************************************
*/
void EC11A_EXTI_Interrupt(uint16_t GPIO_Pin)
{
	/**********EC11A_1**********/
	if(GPIO_Pin == EC11A[0].EXTI_Pin)//A�����ش����ⲿ�ж�
	{
		HAL_TIM_Base_Start_IT(EC11A[0].Tim);//��ʼ��ʱ��
		while(EC11A[0].TIM_Cnt <= 2)//��ʱ��һ������1ms����ʱ2ms�ڿ���A��û�е�����
		{
			if(GPIO_Pin == EC11A[0].EXTI_Pin)//��2ms�ڣ���⵽��ƽ�仯
			{ 
				HAL_TIM_Base_Stop_IT(EC11A[0].Tim);//ֹͣ��ʱ��
				EC11A[0].TIM_Cnt = 0;//���TIM����
				EC11A[0].EC11A_Cnt++;//��ť����
				if(sys.Motor_Stop)//���½��ٶȵ���������ò�����
					return;
				EC11A[0].EC11A_Knob = 1.0f;//����ת��ťʱ
				if(HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO,EC11A[0].EC11A_Pin) == 0)//��
				{	
					if(EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast)//���������ת
						Set_Time += 60;//�趨ʱ���60S
					else
						Set_Time += 600;//�趨ʱ���600S
					Set_Time = (Set_Time > Time_MAX) ? Time_MAX : Set_Time;//ʱ������趨24Сʱ
					Time_State  = (Set_Time < 60) ? 0 : 1;//�ж��Ƿ�������ʱ��
					Twinkle_Time2 = 2.0f;//ʱ����˸2S
					break;
				}
				else if(HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO,EC11A[0].EC11A_Pin) == 1)//��
				{
					if(EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast)//���������ת
						Set_Time -= 60;//�趨ʱ���60S
					else
						Set_Time -= 600;//�趨ʱ���600S
					Set_Time = (Set_Time < Time_MIN) ? 0 : Set_Time;//ʱ��С��1���Ӳ��趨���趨ʱ��Ϊ0��������
					Twinkle_Time2 = 2.0f;//ʱ����˸2S
					Time_State  = (Set_Time < 60) ? 0 : 1;//�ж��Ƿ�������ʱ��
					break;
				}
				break;
			}
		}
		HAL_TIM_Base_Stop_IT(EC11A[0].Tim);//ֹͣ��ʱ��
		EC11A[0].TIM_Cnt = 0;//���TIM����
	}
	
	/**********EC11A_2**********/
	if(GPIO_Pin == EC11A[1].EXTI_Pin)//A�����ش����ⲿ�ж�
	{
		HAL_TIM_Base_Start_IT(EC11A[1].Tim);//��ʼ��ʱ��
		while(EC11A[1].TIM_Cnt <= 2)//��ʱ��һ������1ms����ʱ2ms�ڿ���A��û�е�����
		{
			if(GPIO_Pin == EC11A[1].EXTI_Pin)//��2ms�ڣ���⵽��ƽ�仯
			{ 
				HAL_TIM_Base_Stop_IT(EC11A[1].Tim);//ֹͣ��ʱ��
				EC11A[1].TIM_Cnt = 0;//���TIM����
				EC11A[1].EC11A_Cnt++;//��ť����
				if(sys.Motor_Stop)//���½��ٶȵ���������ò�����
					return;
				EC11A[1].EC11A_Knob = 1.0f;//����ת��ťʱ
				if(HAL_GPIO_ReadPin(EC11A[1].EC11A_GPIO,EC11A[1].EC11A_Pin) == 0)//��
				{
                    if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//���������ת
						Set_Speed += 10;//ת�ټ�10
					else
						Set_Speed += 50;//ת�ټ�50
					Set_Speed = (Set_Speed > Speed_MAX) ? Speed_MAX : Set_Speed;//�ٶȲ��������ֵ
					Twinkle_Time1 = 2.0f;//�ٶ���˸2S
					break;
				}
				else if(HAL_GPIO_ReadPin(EC11A[1].EC11A_GPIO,EC11A[1].EC11A_Pin) == 1)//��
				{
                    if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//���������ת
						Set_Speed -= 10;//ת�ټ�10
					else
						Set_Speed -= 50;//ת�ټ�50
					Set_Speed = (Set_Speed < Speed_MIN) ? Speed_MIN : Set_Speed;//�ٶȲ�С������ֵ
					Twinkle_Time1 = 2.0f;//�ٶ���˸2S
					break;
				}
				break;
			}
		}
		HAL_TIM_Base_Stop_IT(EC11A[1].Tim);//ֹͣ��ʱ��
		EC11A[1].TIM_Cnt = 0;//���TIM����
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ�void EC11A_TIM_Interrupt(TIM_HandleTypeDef *htim)
 * ��    �ܣ�EC11A��ť��ʱ�����жϺ���
 * ��    �룺htim����ʱ��
 * ��    ����TIM_HandleTypeDef *htim
*****************************************************************
*/
void EC11A_TIM_Interrupt(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == EC11A_Tim_1.Instance) 
	{
		EC11A[0].TIM_Cnt++;
	}
	
	if(htim->Instance == EC11A_Tim_2.Instance) 
	{
		EC11A[1].TIM_Cnt++;
	}
}
