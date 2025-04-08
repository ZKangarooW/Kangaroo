#include "Speed.h"

/**********�ֲ���������******/
uint32_t P_Status;//�������ڼ���״̬  1���� 0�ر�
uint16_t TIM1CH1_CAPTURE_STA=0;//����������	    				
uint32_t TIM1CH1_CAPTURE_VAL;//�������ֵ
uint8_t CAPTURE_First=0;//�����һ���ߵ�ƽ
uint8_t CAPTURE_Status=0;//����״̬
uint16_t Speed_Flag;//�ٶȵ�0��־λ

/*
*****************************************************************
 * ����ԭ�ͣ� void Encoder_Init(void)
 * ��    �ܣ� ��������ʼ�� 
*****************************************************************
*/
void Encoder_Init(void)
{   
    HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_3);//motor���벶��
	HAL_TIM_Base_Start_IT(&htim1); 
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Check_Speed(void)
 * ��    �ܣ� ����ٶ��Ƿ�ֹͣ
*****************************************************************
*/
void Check_Speed(void)
{
	if(Speed_Flag)
		Speed_Flag--;
	if(Speed_Flag==0)
		Rel_Speed=0;
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Check_Status(void)
 * ��    �ܣ� ���״̬
*****************************************************************
*/
void Check_Status(void)
{
	if(CAPTURE_Status)
	{	
		__HAL_TIM_ENABLE(&htim1);
		CAPTURE_Status=0;
		TIM1CH1_CAPTURE_STA=0; 
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Check_Speed(void)
 * ��    �ܣ� ����ٶ��Ƿ�ֹͣ
*****************************************************************
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM1)
	{
		if(sys.Run_Status == 1)
		{
			if(P_Status)
			{
				TIM1CH1_CAPTURE_STA++;
			}
		}
	}	
}

/*
*****************************************************************
 * ����ԭ�ͣ� void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
 * ��    �ܣ� ���벶��ص�����
*****************************************************************
*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(sys.Run_Status == 1)
	{
		if(CAPTURE_Status==0)
		{
			 Speed_Flag=2;
			if(CAPTURE_First)		 		
			{	  			
				CAPTURE_Status=1;//ֹͣ�����ʱ
				CAPTURE_First=0;//��������һ�������ر�־
				TIM1CH1_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_3);//��ȡ��ǰ�������ֵ
				long long temp=0;
				temp=TIM1CH1_CAPTURE_STA;  
				temp*=100;//һ������100us	 	    
				temp+=TIM1CH1_CAPTURE_VAL;//һ�����������us��   
				temp=60000000/temp;//rpm
				Rel_Speed=temp*10/25;
				P_Status=0;
				__HAL_TIM_SET_COUNTER(&htim1,0);
				__HAL_TIM_DISABLE(&htim1);      
			}
			else  								
			{
				TIM1CH1_CAPTURE_STA=0;//������ڼ���			
				TIM1CH1_CAPTURE_VAL=0;//�������Ĵ���
				CAPTURE_First=1;//�Ѳ����һ��������   
				CAPTURE_Status=0;//�����ʱ
				P_Status=1;//�������ڼ���
			}		    
		}
	}
	else
	{
		TIM1CH1_CAPTURE_VAL = 0;
		TIM1CH1_CAPTURE_STA = 0;
	}
}
