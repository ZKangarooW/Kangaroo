#include "Ctrl_Motor.h"

/*
*****************************************************************
 * ����ԭ�ͣ� void Motor_Check(float dT)
 * ��    �ܣ� ���ֹͣ���
*****************************************************************
*/
void Motor_Check(float dT)
{
    static float T1,T2; 
    if(Rel_Speed.L1 == 0)//�趨�ٶȲ���ʵ���ٶ�С��10
    {  
        T1 += dT;
        if(T1 >= 2)
        {
            Speed_Val_L1.SumError=0x12000;//�������ϵ��
        }
    }
    else
    {
        T1 = 0;
    }
    if(Rel_Speed.L2 == 0)//�趨�ٶȲ���ʵ���ٶ�С��10
    {  
        T2 += dT;
        if(T2 >= 2)
        {
            Speed_Val_L2.SumError=0x12000;//�������ϵ��
        }
    }
    else
    {
        T2 = 0;
    }
    #if (Integration_TYPE == 0)
		static float T3,T4,T5,T6;
		if(Param.type == 0 || Param.type == 2)//����
		{
			if(Rel_Speed.L5 == 0)//�趨�ٶȲ���ʵ���ٶ�С��10
			{  
				T5 += dT;
				if(T5 >= 2)
				{
					Speed_Val_L5.SumError=0x12000;//�������ϵ��
				}
			}
			else
			{
				T5 = 0;
			}
			if(Rel_Speed.L6 == 0)//�趨�ٶȲ���ʵ���ٶ�С��10
			{  
				T6 += dT;
				if(T6 >= 2)
				{
					Speed_Val_L6.SumError=0x12000;//�������ϵ��
				}
			}
			else
			{
				T6 = 0;
			}
		}
		else if(Param.type == 1 || Param.type == 3)//����
		{
			if(Rel_Speed.L3 == 0)//�趨�ٶȲ���ʵ���ٶ�С��10
			{  
				T3 += dT;
				if(T3 >= 2)
				{
					Speed_Val_L3.SumError=0x12000;//�������ϵ��
				}
			}
			else
			{
				T3 = 0;
			}
			if(Rel_Speed.L4 == 0)//�趨�ٶȲ���ʵ���ٶ�С��10
			{  
				T4 += dT;
				if(T4 >= 2)
				{
					Speed_Val_L4.SumError=0x12000;//�������ϵ��
				}
			}
			else
			{
				T4 = 0;
			}
			if(Rel_Speed.L5 == 0)//�趨�ٶȲ���ʵ���ٶ�С��10
			{  
				T5 += dT;
				if(T5 >= 2)
				{
					Speed_Val_L5.SumError=0x12000;//�������ϵ��
				}
			}
			else
			{
				T5 = 0;
			}
			if(Rel_Speed.L6 == 0)//�趨�ٶȲ���ʵ���ٶ�С��10
			{  
				T6 += dT;
				if(T6 >= 2)
				{
					Speed_Val_L6.SumError=0x12000;//�������ϵ��
				}
			}
			else
			{
				T6 = 0;
			}
		}
    #elif (Integration_TYPE == 1) 
    static float T3,T4,T5,T6,T7,T8,T9;
    if(Rel_Speed.L3 == 0)//�趨�ٶȲ���ʵ���ٶ�С��10
    {  
        T3 += dT;
        if(T3 >= 2)
        {
            Speed_Val_L3.SumError=0x12000;//�������ϵ��
        }
    }
    else
    {
        T3 = 0;
    }
    if(Rel_Speed.L4 == 0)//�趨�ٶȲ���ʵ���ٶ�С��10
    {  
        T4 += dT;
        if(T4 >= 2)
        {
            Speed_Val_L4.SumError=0x12000;//�������ϵ��
        }
    }
    else
    {
        T4 = 0;
    }
    if(Rel_Speed.L5 == 0)//�趨�ٶȲ���ʵ���ٶ�С��10
    {  
        T5 += dT;
        if(T5 >= 2)
        {
            Speed_Val_L5.SumError=0x12000;//�������ϵ��
        }
    }
    else
    {
        T5 = 0;
    }
    if(Rel_Speed.L6 == 0)//�趨�ٶȲ���ʵ���ٶ�С��10
    {  
        T6 += dT;
        if(T6 >= 2)
        {
            Speed_Val_L6.SumError=0x12000;//�������ϵ��
        }
    }
    else
    {
        T6 = 0;
    }
    if(Rel_Speed.L7 == 0)//�趨�ٶȲ���ʵ���ٶ�С��10
    {  
        T7 += dT;
        if(T7 >= 2)
        {
            Speed_Val_L7.SumError=0x12000;//�������ϵ��
        }
    }
    else
    {
        T7 = 0;
    }
    if(Rel_Speed.L8 == 0)//�趨�ٶȲ���ʵ���ٶ�С��10
    {  
        T8 += dT;
        if(T8 >= 2)
        {
            Speed_Val_L8.SumError=0x12000;//�������ϵ��
        }
    }
    else
    {
        T8 = 0;
    }
	if(Rel_Speed.L9 == 0)//�趨�ٶȲ���ʵ���ٶ�С��10
    {  
        T9 += dT;
        if(T9 >= 2)
        {
            Speed_Val_L9.SumError=0x12000;//�������ϵ��
        }
    }
    else
    {
        T9 = 0;
    }
    #endif
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Motor_Ctrl(void)
 * ��    �ܣ� �������
*****************************************************************
*/
void Motor_Ctrl(void)
{   
    if(Run_Status == 1)//����
    {
        Motor_Check(0.05);
		#if (Integration_TYPE == 0)//������
        /**********Speed_L1**********/
        if(Ctrl_Speed.L1 && ((DownTime_Over.L1 == 0)||(Ctrl_Time.L1)))//�ٶȴ���0�Ͷ�ʱ��û�н���
        {
            PID_Speed(Ctrl_Speed.L1,Rel_Speed.L1,&Speed_Arg,&Speed_Val_L1);//���PID����
			if(Param.type == 0 || Param.type == 2)//����
			{
				PWM_L3 = Speed_Val_L1.Out;//pid���
			}
			else if(Param.type == 1 || Param.type == 3)//����
			{
				PWM_L1 = Speed_Val_L1.Out;//pid���
			}
        }
        else
        {
			if(Param.type == 0 || Param.type == 2)//����
			{
				PWM_L3 = 0;//pwm�����
			}
			else if(Param.type == 1 || Param.type == 3)//����
			{
				PWM_L1 = 0;//pwm�����
			}
        }
        /**********Speed_L2**********/
        if(Ctrl_Speed.L2 && ((DownTime_Over.L2 == 0)||(Ctrl_Time.L2)))//�ٶȴ���0�Ͷ�ʱ��û�н���
        {
            PID_Speed(Ctrl_Speed.L2,Rel_Speed.L2,&Speed_Arg,&Speed_Val_L2);//���PID����
			if(Param.type == 0 || Param.type == 2)//����
			{
				PWM_L4 = Speed_Val_L2.Out;//pid���
			}
			else if(Param.type == 1 || Param.type == 3)//����
			{
				PWM_L2 = Speed_Val_L2.Out;//pid���
			}
        }
        else
        {
			if(Param.type == 0 || Param.type == 2)//����
			{
				PWM_L4 = 0;//pwm�����
			}
			else if(Param.type == 1 || Param.type == 3)//����
			{
				PWM_L2 = 0;//pwm�����
			}
        }
		if(Param.type == 0 || Param.type == 2)//����
		{
			/**********Speed_L5**********/
			if(Ctrl_Speed.L5 && ((DownTime_Over.L5 == 0)||(Ctrl_Time.L5)))//�ٶȴ���0�Ͷ�ʱ��û�н���
			{
				PID_Speed(Ctrl_Speed.L5,Rel_Speed.L5,&Speed_Arg,&Speed_Val_L5);//���PID����
				PWM_L5 = Speed_Val_L5.Out;//pid���
			}
			else
			{
				PWM_L5 = 0;//pwm�����
			}
			/**********Speed_L6**********/
			if(Ctrl_Speed.L6 && ((DownTime_Over.L6 == 0)||(Ctrl_Time.L6)))//�ٶȴ���0�Ͷ�ʱ��û�н���
			{
				PID_Speed(Ctrl_Speed.L6,Rel_Speed.L6,&Speed_Arg,&Speed_Val_L6);//���PID����
				PWM_L6 = Speed_Val_L6.Out;//pid���
			}
			else
			{
				PWM_L6 = 0;//pwm�����
			}
		}
		else if(Param.type == 1 || Param.type == 3)//����
		{
			/**********Speed_L3**********/
			if(Ctrl_Speed.L3 && ((DownTime_Over.L3 == 0)||(Ctrl_Time.L3)))//�ٶȴ���0�Ͷ�ʱ��û�н���
			{
				PID_Speed(Ctrl_Speed.L3,Rel_Speed.L3,&Speed_Arg,&Speed_Val_L3);//���PID����
				PWM_L3 = Speed_Val_L3.Out;//pid���
			}
			else
			{
				PWM_L3 = 0;//pwm�����
			}
			/**********Speed_L4**********/
			if(Ctrl_Speed.L4 && ((DownTime_Over.L4 == 0)||(Ctrl_Time.L4)))//�ٶȴ���0�Ͷ�ʱ��û�н���
			{
				PID_Speed(Ctrl_Speed.L4,Rel_Speed.L4,&Speed_Arg,&Speed_Val_L4);//���PID����
				PWM_L4 = Speed_Val_L4.Out;//pid���
			}
			else
			{
				PWM_L4 = 0;//pwm�����
			}
			/**********Speed_L5**********/
			if(Ctrl_Speed.L5 && ((DownTime_Over.L5 == 0)||(Ctrl_Time.L5)))//�ٶȴ���0�Ͷ�ʱ��û�н���
			{
				PID_Speed(Ctrl_Speed.L5,Rel_Speed.L5,&Speed_Arg,&Speed_Val_L5);//���PID����
				PWM_L5 = Speed_Val_L5.Out;//pid���
			}
			else
			{
				PWM_L5 = 0;//pwm�����
			}
			/**********Speed_L6**********/
			if(Ctrl_Speed.L6 && ((DownTime_Over.L6 == 0)||(Ctrl_Time.L6)))//�ٶȴ���0�Ͷ�ʱ��û�н���
			{
				PID_Speed(Ctrl_Speed.L6,Rel_Speed.L6,&Speed_Arg,&Speed_Val_L6);//���PID����
				PWM_L6 = Speed_Val_L6.Out;//pid���
			}
			else
			{
				PWM_L6 = 0;//pwm�����
			}
		}
        #elif (Integration_TYPE == 1)  
		/**********Speed_L1**********/
        if(Ctrl_Speed.L1 && ((DownTime_Over.L1 == 0)||(Ctrl_Time.L1)))//�ٶȴ���0�Ͷ�ʱ��û�н���
        {
            PID_Speed(Ctrl_Speed.L1,Rel_Speed.L1,&Speed_Arg,&Speed_Val_L1);//���PID����
            PWM_L1 = Speed_Val_L1.Out;//pid���
        }
        else
        {
            PWM_L1 = 0;//pwm�����
        }
        /**********Speed_L2**********/
        if(Ctrl_Speed.L2 && ((DownTime_Over.L2 == 0)||(Ctrl_Time.L2)))//�ٶȴ���0�Ͷ�ʱ��û�н���
        {
            PID_Speed(Ctrl_Speed.L2,Rel_Speed.L2,&Speed_Arg,&Speed_Val_L2);//���PID����
            PWM_L2 = Speed_Val_L2.Out;//pid���
        }
        else
        {
            PWM_L2 = 0;//pwm�����
        }
        /**********Speed_L3**********/
        if(Ctrl_Speed.L3 && ((DownTime_Over.L3 == 0)||(Ctrl_Time.L3)))//�ٶȴ���0�Ͷ�ʱ��û�н���
        {
            PID_Speed(Ctrl_Speed.L3,Rel_Speed.L3,&Speed_Arg,&Speed_Val_L3);//���PID����
            PWM_L3 = Speed_Val_L3.Out;//pid���
        }
        else
        {
            PWM_L3 = 0;//pwm�����
        }
        /**********Speed_L4**********/
        if(Ctrl_Speed.L4 && ((DownTime_Over.L4 == 0)||(Ctrl_Time.L4)))//�ٶȴ���0�Ͷ�ʱ��û�н���
        {
            PID_Speed(Ctrl_Speed.L4,Rel_Speed.L4,&Speed_Arg,&Speed_Val_L4);//���PID����
            PWM_L4 = Speed_Val_L4.Out;//pid���
        }
        else
        {
            PWM_L4 = 0;//pwm�����
        }
        /**********Speed_L5**********/
        if(Ctrl_Speed.L5 && ((DownTime_Over.L5 == 0)||(Ctrl_Time.L5)))//�ٶȴ���0�Ͷ�ʱ��û�н���
        {
            PID_Speed(Ctrl_Speed.L5,Rel_Speed.L5,&Speed_Arg,&Speed_Val_L5);//���PID����
            PWM_L5 = Speed_Val_L5.Out;//pid���
        }
        else
        {
            PWM_L5 = 0;//pwm�����
        }
        /**********Speed_L6**********/
        if(Ctrl_Speed.L6 && ((DownTime_Over.L6 == 0)||(Ctrl_Time.L6)))//�ٶȴ���0�Ͷ�ʱ��û�н���
        {
            PID_Speed(Ctrl_Speed.L6,Rel_Speed.L6,&Speed_Arg,&Speed_Val_L6);//���PID����
            PWM_L6 = Speed_Val_L6.Out;//pid���
        }
        else
        {
            PWM_L6 = 0;//pwm�����
        }
        /**********Speed_L7**********/
        if(Ctrl_Speed.L7 && ((DownTime_Over.L7 == 0)||(Ctrl_Time.L7)))//�ٶȴ���0�Ͷ�ʱ��û�н���
        {
            PID_Speed(Ctrl_Speed.L7,Rel_Speed.L7,&Speed_Arg,&Speed_Val_L7);//���PID����
            PWM_L7 = Speed_Val_L7.Out;//pid���
        }
        else
        {
            PWM_L7 = 0;//pwm�����
        }
        /**********Speed_L8**********/
        if(Ctrl_Speed.L8 && ((DownTime_Over.L8 == 0)||(Ctrl_Time.L8)))//�ٶȴ���0�Ͷ�ʱ��û�н���
        {
            PID_Speed(Ctrl_Speed.L8,Rel_Speed.L8,&Speed_Arg,&Speed_Val_L8);//���PID����
            PWM_L8 = Speed_Val_L8.Out;//pid���
        }
        else
        {
            PWM_L8 = 0;//pwm�����
        } 
		/**********Speed_L9**********/
        if(Ctrl_Speed.L9 && ((DownTime_Over.L9 == 0)||(Ctrl_Time.L9)))//�ٶȴ���0�Ͷ�ʱ��û�н���
        {
            PID_Speed(Ctrl_Speed.L9,Rel_Speed.L9,&Speed_Arg,&Speed_Val_L9);//���PID����
            PWM_L9 = Speed_Val_L9.Out;//pid���
        }
        else
        {
            PWM_L9 = 0;//pwm�����
        } 
        #endif
    }
    else
    {    
		#if (Integration_TYPE == 0)//������
			if(Param.type == 0 || Param.type == 2)//����
			{
				PWM_L3 = 0;//pwm�����
				PWM_L4 = 0;//pwm�����
			}
			else if(Param.type == 1 || Param.type == 3)//����
			{
				PWM_L1 = 0;//pwm�����
				PWM_L2 = 0;//pwm�����
			}		
			Speed_Val_L1.SumError=0;//�������ϵ��
			Speed_Val_L2.SumError=0;//�������ϵ��
			if(Param.type == 0 || Param.type == 2)//����
			{
				PWM_L5 = 0;//pwm�����
				PWM_L6 = 0;//pwm�����
				Speed_Val_L7.SumError=0;//�������ϵ��
				Speed_Val_L8.SumError=0;//�������ϵ��
			}
			else if(Param.type == 1 || Param.type == 3)//����
			{
				PWM_L3 = 0;//pwm�����
				PWM_L4 = 0;//pwm�����
				PWM_L5 = 0;//pwm�����
				PWM_L6 = 0;//pwm�����
				Speed_Val_L3.SumError=0;//�������ϵ��
				Speed_Val_L4.SumError=0;//�������ϵ��
				Speed_Val_L5.SumError=0;//�������ϵ��
				Speed_Val_L6.SumError=0;//�������ϵ��
			}
        #elif (Integration_TYPE == 1)
			PWM_L1 = 0;//pwm�����
			PWM_L2 = 0;//pwm�����
			PWM_L3 = 0;//pwm�����
			PWM_L4 = 0;//pwm�����
			PWM_L5 = 0;//pwm�����
			PWM_L6 = 0;//pwm�����
			PWM_L7 = 0;//pwm�����
			PWM_L8 = 0;//pwm�����
			PWM_L9 = 0;//pwm�����
			Speed_Val_L1.SumError=0;//�������ϵ��
			Speed_Val_L2.SumError=0;//�������ϵ��
			Speed_Val_L3.SumError=0;//�������ϵ��
			Speed_Val_L4.SumError=0;//�������ϵ��
			Speed_Val_L5.SumError=0;//�������ϵ��
			Speed_Val_L6.SumError=0;//�������ϵ��
			Speed_Val_L7.SumError=0;//�������ϵ��
			Speed_Val_L8.SumError=0;//�������ϵ��
			Speed_Val_L9.SumError=0;//�������ϵ��
        #endif
    }      
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Motor_Init(void)
 * ��    �ܣ� �����ʼ�� 
*****************************************************************
*/
void Motor_Init(void)
{
    #if (Integration_TYPE == 0) 
		if(Param.type == 0 || Param.type == 2)//����
		{
			HAL_GPIO_WritePin(MO1_GPIO_Port, MO1_Pin, GPIO_PIN_SET);//ʹ�ܵ��
			HAL_GPIO_WritePin(MO2_GPIO_Port, MO2_Pin, GPIO_PIN_SET);//ʹ�ܵ��  
			HAL_GPIO_WritePin(MO3_GPIO_Port, MO3_Pin, GPIO_PIN_SET);//ʹ�ܵ��
			HAL_GPIO_WritePin(MO4_GPIO_Port, MO4_Pin, GPIO_PIN_SET);//ʹ�ܵ��
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);//motor PWM���
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);//motor PWM���
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);//motor PWM���
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);//motor PWM���
		}
		else if(Param.type == 1 || Param.type == 3)//����
		{
			HAL_GPIO_WritePin(MO1_GPIO_Port, MO1_Pin, GPIO_PIN_SET);//ʹ�ܵ��
			HAL_GPIO_WritePin(MO2_GPIO_Port, MO2_Pin, GPIO_PIN_SET);//ʹ�ܵ��  
			HAL_GPIO_WritePin(MO3_GPIO_Port, MO3_Pin, GPIO_PIN_SET);//ʹ�ܵ��
			HAL_GPIO_WritePin(MO4_GPIO_Port, MO4_Pin, GPIO_PIN_SET);//ʹ�ܵ��
			HAL_GPIO_WritePin(MO5_GPIO_Port, MO5_Pin, GPIO_PIN_SET);//ʹ�ܵ��
			HAL_GPIO_WritePin(MO6_GPIO_Port, MO6_Pin, GPIO_PIN_SET);//ʹ�ܵ��
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);//motor PWM���
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);//motor PWM���
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);//motor PWM���
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);//motor PWM���
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);//motor PWM���
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);//motor PWM���
		}
    #elif (Integration_TYPE == 1) 
	HAL_GPIO_WritePin(MO1_GPIO_Port, MO1_Pin, GPIO_PIN_SET);//ʹ�ܵ��
    HAL_GPIO_WritePin(MO2_GPIO_Port, MO2_Pin, GPIO_PIN_SET);//ʹ�ܵ��
    HAL_GPIO_WritePin(MO3_GPIO_Port, MO3_Pin, GPIO_PIN_SET);//ʹ�ܵ��
    HAL_GPIO_WritePin(MO4_GPIO_Port, MO4_Pin, GPIO_PIN_SET);//ʹ�ܵ��   
    HAL_GPIO_WritePin(MO5_GPIO_Port, MO5_Pin, GPIO_PIN_SET);//ʹ�ܵ��
    HAL_GPIO_WritePin(MO6_GPIO_Port, MO6_Pin, GPIO_PIN_SET);//ʹ�ܵ��
    HAL_GPIO_WritePin(MO7_GPIO_Port, MO7_Pin, GPIO_PIN_SET);//ʹ�ܵ��
    HAL_GPIO_WritePin(MO8_GPIO_Port, MO8_Pin, GPIO_PIN_SET);//ʹ�ܵ�� 
	HAL_GPIO_WritePin(MO9_GPIO_Port, MO9_Pin, GPIO_PIN_SET);//ʹ�ܵ��
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);//motor PWM���
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2);//motor PWM��� 
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_3);//motor PWM���
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_4);//motor PWM���
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);//motor PWM���
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);//motor PWM���
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);//motor PWM���
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);//motor PWM���
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);//motor PWM���
    #endif
}
