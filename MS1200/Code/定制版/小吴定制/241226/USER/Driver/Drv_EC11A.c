#include "Drv_EC11A.h"

/**********�ṹ��************/
_EC11A_ EC11A[1];//��ť����

/*
*****************************************************************
 * ����ԭ�ͣ�void EC11A_Init(void)
 * ��    �ܣ�EC11A��ʼ����ʱ��
*****************************************************************
*/
void EC11A_Init(void)
{
	EC11A[0].EXTI_Pin = KEY1A_Pin;//EC11A��ť�ж�����
	EC11A[0].EC11A_Pin = KEY1B_Pin;//EC11A��ť��������
	EC11A[0].EC11A_GPIO = KEY1B_GPIO_Port;//EC11A��ť����GPIO�˿�
	
	EC11A[0].Key_Pin = KEY1_Pin;//EC11A������������
	EC11A[0].Key_GPIO = KEY1_GPIO_Port;//EC11A��������GPIO�˿�
	
	EC11A[0].Tim = &EC11A_Tim_1;//��ʱ��ѡ��
	EC11A[0].EC11A_Fast = EC11A_Fast_1;//�ж���ת�ٶ���ֵ
}

/*
*****************************************************************
 * ����ԭ�ͣ�void EC11A_Speed(float dT)
 * ��    �ܣ�EC11A��ť�ٶȼ���
*****************************************************************
*/
void EC11A_Speed(float dT)
{
	EC11A[0].EC11A_Speed = EC11A[0].EC11A_Cnt*60/20;//һ����һ�Ρ�תһȦ20��������һ���ӵ��ٶ�
	EC11A[0].EC11A_Cnt = 0;//����⵽�ļ�������
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_Knob(float dT)
 * ��    �ܣ������ť״̬-500ms
*****************************************************************
*/
void Check_Knob(float dT)
{
	if(!EC11A[0].EC11A_Knob)
		return;
    if(EC11A[0].EC11A_Knob)//��ť��ת��
        EC11A[0].EC11A_Knob -=dT;//����ʱ
	if(!EC11A[0].EC11A_Knob)
	{
		Speed.Ctrl = Speed.Set;
		Param.Speed = Speed.Set;
		Speed.ADDMode = 0;
		Save_Param_En = 1;
		if(sys.Run_Status)
			Beep_Time = 0.1;//��������0.1S
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ�void EC11AKey_Scan(float dT)
 * ��    �ܣ�EC11A����ɨ��
*****************************************************************
*/
void EC11AKey_Scan(float dT)
{
	/************************************��ť��**************************************/
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
				if(!sys.Run_Status)
				{
					sys.Run_Status = 1;//����ϵͳ
					Speed_Val.Integral = 25;
					Speed.ADDMode = 0;
				}
				else
				{
					sys.Motor_Stop = 1;//���ֹͣ
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
}

/*
*****************************************************************
 * ����ԭ�ͣ�void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
 * ��    �ܣ��ⲿ�ж�
*****************************************************************
*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	UNUSED(GPIO_Pin);
	
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
				if(sys.Run_Status)
					EC11A[0].EC11A_Knob = 4.0f;//����ת��ťʱ
				else
					EC11A[0].EC11A_Knob = 2.0f;//����ת��ťʱ
				if(HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO,EC11A[0].EC11A_Pin) == 1)//��
				{
					if(EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast)//���������ת
						Speed.Set -= 10;
					else
						Speed.Set -= 30;
					if(Speed.Set <= Speed_MIN)
						Speed.Set = Speed_MIN;
					break;
				}
				else if(HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO,EC11A[0].EC11A_Pin) == 0)//��
				{
					if(EC11A[0].EC11A_Speed < EC11A[0].EC11A_Fast)//���������ת
						Speed.Set += 10;
					else
						Speed.Set += 30;
					if(Speed.Set > Speed_MAX)
						Speed.Set = Speed_MAX;
					break;
				}
				break;
			}
		}
		HAL_TIM_Base_Stop_IT(EC11A[0].Tim);//ֹͣ��ʱ��
		EC11A[0].TIM_Cnt = 0;//���TIM����
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ�void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 * ��    �ܣ���ʱ�������ж�
*****************************************************************
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == EC11A_Tim_1.Instance) 
	{
		EC11A[0].TIM_Cnt++;
	}
	if(htim->Instance == TIM1)
    {
        if(P_Status)//�������ڼ���״̬:����
        {    
            TIM1CH3_CAPTURE_STA++;//����������++
        }
    }
}
