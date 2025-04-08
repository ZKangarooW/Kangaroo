#include "Speed.h"

/**********�ֲ���������******/
uint32_t P_Status;//�������ڼ���״̬  1���� 0�ر�
uint16_t TIM1CH3_CAPTURE_STA=0;//���������������	    				
uint32_t TIM1CH3_CAPTURE_VAL;//����δ����ļ���ֵ
uint8_t CAPTURE_First=0;//�����һ���ߵ�ƽ
uint8_t CAPTURE_Status=0;//����״̬
uint16_t Speed_Flag;//�ٶȵ�0��־λ

/*
*****************************************************************
 * ����ԭ�ͣ�void Encoder_Init(void)
 * ��    �ܣ���������ʼ�� 
*****************************************************************
*/
void Encoder_Init(void)
{   
    HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_3);//motor���벶��
	HAL_TIM_Base_Start_IT(&htim1);//������ʱ��1���ж�
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_Speed(float dT)
 * ��    �ܣ�����ٶ��Ƿ�ֹͣ
*****************************************************************
*/
void Check_Speed(float dT)
{
	if(Speed_Flag)
		Speed_Flag -= dT;
	if(Speed_Flag==0)
		Speed.Rel_Speed = 0;
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_Status(void)
 * ��    �ܣ���Ⲷ��״̬
*****************************************************************
*/
void Check_Status(void)
{
	if(CAPTURE_Status)//�������
	{	
		__HAL_TIM_ENABLE(&htim1);//���¿�ʼ����
		CAPTURE_Status=0;//��ʼ����
		TIM1CH3_CAPTURE_STA=0;//���ʱ������
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ�void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 * ��    �ܣ���ʱ���ж�
*****************************************************************
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM1)
	{
		if(P_Status)//�������ڼ���
		{
			TIM1CH3_CAPTURE_STA++;//�����1
		}
	}	
}

/*
*****************************************************************
 * ����ԭ�ͣ�void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
 * ��    �ܣ����벶��ص�����
*****************************************************************
*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(CAPTURE_Status==0)
	{
		 Speed_Flag=2;//ÿ�ν��붼��ֵ2�����2S�󲻽����ʾ�ٶ�Ϊ0
		if(CAPTURE_First)		 		
		{	  			
			CAPTURE_Status=1;//ֹͣ�����ʱ
			CAPTURE_First=0;//��������һ�������ر�־
			TIM1CH3_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_3);//��ȡ��ǰ�������ֵ
			long long temp=0;
			temp=TIM1CH3_CAPTURE_STA;//����Ĵ��������ڼ��������ٸ����ڣ�
			temp*=50;//һ�����������ʱ�䣨us������=��ʱ�����ڣ�1/��48000000/6��*400��=0.00005S=50us
			temp+=TIM1CH3_CAPTURE_VAL;//һ�����������us�����������ʱ�����û�������ʱ�䣩�ó�һ���������˶���us
			temp=60000000/temp/2;//һ������60000000us��һ�������ж��ٸ����壨���ڣ���2��һȦ�м�������ó�һ����ת�˶���Ȧ
			Speed.Rel_Speed = temp;
			P_Status=0;//�������ڼ����ر�
			__HAL_TIM_SET_COUNTER(&htim1,0);//��ʱ���Ĵ�������
			__HAL_TIM_DISABLE(&htim1);//�����붨ʱ���жϣ������������   
		}
		else  								
		{
			TIM1CH3_CAPTURE_STA=0;//������ڼ���			
			TIM1CH3_CAPTURE_VAL=0;//�������Ĵ���
			CAPTURE_First=1;//�Ѳ����һ��������   
			CAPTURE_Status=0;//�����ʱ
			P_Status=1;//�������ڼ�����ʼ
		}		    
	}			
}
