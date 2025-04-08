/**
  ******************************************************************************
  * File Name          : TIM.c
  * Description        : This file provides code for the configuration
  *                      of the TIM instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "tim.h"

/* USER CODE BEGIN 0 */
#include "user.h"
/* USER CODE END 0 */

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;

/* TIM1 init function */
void MX_TIM1_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 8-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 200-1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim1, &sConfigIC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_TIM_MspPostInit(&htim1);

}
/* TIM3 init function */
void MX_TIM3_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 31;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 1000;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(tim_baseHandle->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspInit 0 */

  /* USER CODE END TIM1_MspInit 0 */
    /* TIM1 clock enable */
    __HAL_RCC_TIM1_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**TIM1 GPIO Configuration    
    PA10     ------> TIM1_CH3 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* TIM1 interrupt Init */
    HAL_NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
    HAL_NVIC_SetPriority(TIM1_CC_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(TIM1_CC_IRQn);
  /* USER CODE BEGIN TIM1_MspInit 1 */

  /* USER CODE END TIM1_MspInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspInit 0 */

  /* USER CODE END TIM3_MspInit 0 */
    /* TIM3 clock enable */
    __HAL_RCC_TIM3_CLK_ENABLE();

    /* TIM3 interrupt Init */
    HAL_NVIC_SetPriority(TIM3_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
  /* USER CODE BEGIN TIM3_MspInit 1 */

  /* USER CODE END TIM3_MspInit 1 */
  }
}
void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(timHandle->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspPostInit 0 */

  /* USER CODE END TIM1_MspPostInit 0 */
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**TIM1 GPIO Configuration    
    PA8     ------> TIM1_CH1 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM1_MspPostInit 1 */

  /* USER CODE END TIM1_MspPostInit 1 */
  }

}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspDeInit 0 */

  /* USER CODE END TIM1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM1_CLK_DISABLE();
  
    /**TIM1 GPIO Configuration    
    PA8     ------> TIM1_CH1
    PA10     ------> TIM1_CH3 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_8|GPIO_PIN_10);

    /* TIM1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
    HAL_NVIC_DisableIRQ(TIM1_CC_IRQn);
  /* USER CODE BEGIN TIM1_MspDeInit 1 */

  /* USER CODE END TIM1_MspDeInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspDeInit 0 */

  /* USER CODE END TIM3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM3_CLK_DISABLE();

    /* TIM3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM3_IRQn);
  /* USER CODE BEGIN TIM3_MspDeInit 1 */

  /* USER CODE END TIM3_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
extern int rel_time;//ʵʱʱ��
extern uint16_t Wise_Flag;//��ת��־
extern uint16_t UP_Flag;//��ת��־
extern uint16_t rel_speed;//ʵʱ�ٶ�
extern uint8_t wise_task;//��תת������
extern int sumError1;
extern uint8_t Run_Status;//����״̬ 1��run     0��stop
uint16_t ms,ms2,ms3;
uint8_t CAPTURE_Status=0; //����״̬
uint16_t  TIM1CH1_CAPTURE_STA=0;	//����������	    				
uint32_t	TIM1CH1_CAPTURE_VAL;	//�������ֵ
uint8_t   CAPTURE_First=0;//�����һ���ߵ�ƽ
uint32_t P_Status;  //�������ڼ���״̬  1���� 0�ر�
uint16_t Speed1_Flag;//�ٶȵ�0��־λ
uint8_t dis_flag_wise;
uint8_t dis_flag_time;
uint8_t time_flag;
uint16_t save_time;
extern uint8_t LOCK_time;
extern uint8_t Start_Time;//
extern uint8_t ADD_Mode;//��ʾ����ģʽ
extern uint8_t Wise_Status;//���ת������ 0��˳ʱ�� 1����ʱ��
extern uint8_t  wise_blink;//������˸
extern uint16_t BEEP_Count;
extern uint16_t save_speed;
extern uint16_t set_speed;//�趨�ٶ�
extern uint8_t time_disable;//�رռ�ʱ
extern uint32_t speed_set1;//��ťת��
extern uint32_t speed_set2;//��ťת��
extern uint16_t Set_PWM;
extern int set_time;//�趨ʱ��
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim->Instance == TIM3)
  {
		ms++;
		ms2++;
		ms3++;
		
//		if((Run_Status)&&(rel_speed ==0))
//		{
//			       Start_Time=1;//
//						 sumError1=0x20000;
//		}
		
		
		
		
		
		
		if(Wise_Flag) Wise_Flag--;
		if(UP_Flag) UP_Flag--;
		
		
		if(wise_task&&(Run_Status==0))
		{
		       Run_Status =1; 
           if(Wise_Status ==0)	
            HAL_GPIO_WritePin(GPIOA, CW_Pin, GPIO_PIN_RESET);	
					 else if(Wise_Status==1)
						 HAL_GPIO_WritePin(GPIOA, CW_Pin, GPIO_PIN_SET);	
					 HAL_GPIO_WritePin(MO_GPIO_Port, MO_Pin, GPIO_PIN_SET);//���kai
			   	 ADD_Mode=1;
					 Start_Time=2;//
					 sumError1=0x20000;
			     wise_task=0;
		}
		
		if(ms2>20)
		{
			PWM_Set();
			ms2=0;
			if(LOCK_time)
				LOCK_time--;
			
			if(BEEP_Count)
				BEEP_Count--;
			if(BEEP_Count==0)
				HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET);
		}
		
		
		if(ms3>500)
		{
			if(Run_Status==2)
			{
				if(Set_PWM)
					Set_PWM=Set_PWM-2;
			}
       speed_set1=0;
			 speed_set2=0;
			
			if(wise_blink)
				dis_flag_wise=~dis_flag_wise;
			else
				dis_flag_wise=0;
			
			if(time_flag)
				dis_flag_time=~dis_flag_time;
			else
				dis_flag_time=0;
			
			if(wise_blink||time_flag)
			{
				wise_blink=time_flag;
			}
				
			
			
			ms3=0;
		}
		
		if(ms>999)
		{
			
			if(Speed1_Flag)
				Speed1_Flag--;
			if(Speed1_Flag==0)
				rel_speed=0;
			
			if(Run_Status ==1)
			{
				if(( ADD_Mode==4)||( ADD_Mode==1))
				{
					wise_blink=1;
					if((rel_time>0)&&(time_disable==0))
					{
					   rel_time--;
						 time_flag=1;
						
					}
					else
					{
						time_flag=0;
						if(time_disable==0)
						Run_Status=0;
						//rel_time=set_time;

	
						
						//wise_blink=0;
					}
			   }
				 else
				 {
				   time_flag=0; 
					 wise_blink=0;
				 }
	  	}
			else
			time_flag=0;
			
			if((rel_time==0)&&(time_disable==0))
			{
				if(Run_Status ==1)
				{
						Run_Status =2;
						ADD_Mode=0;
						save_speed=set_speed;
						set_speed=0;
				    //rel_time=save_time;
				}
			}
				
			
			if(Start_Time)
				Start_Time--;
			
//			uint32_t test1;
//				test1=TIM1CH1_CAPTURE_STA;
//				if(Speed1_Flag==test1) 
//				{
//						rel_speed =0;
//					
//				}
//				Speed1_Flag=test1;
				
				
			ms=0;
		}
		
		
		
	}
	if(htim->Instance == TIM1)
  {
          if(P_Status)
		{
			TIM1CH1_CAPTURE_STA++;
		}
  }	
}


//���벶��ص�����
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(Run_Status ==0)
		return;
	if(CAPTURE_Status==0)
	{
		 Speed1_Flag=2;
		if(CAPTURE_First)		 		
			{	  			
				CAPTURE_Status=1;		//ֹͣ�����ʱ
				CAPTURE_First=0;    //��������һ�������ر�־
				TIM1CH1_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_3);//��ȡ��ǰ�������ֵ
				
				long long temp=0;
				temp=TIM1CH1_CAPTURE_STA;  
				temp*=50;	//һ������50us	 	    
				temp+=TIM1CH1_CAPTURE_VAL; //һ�����������us��   
				temp=600000/temp; //rpm//temp=30000000/temp; //rpm
				rel_speed=temp;
				P_Status=0;
				__HAL_TIM_SET_COUNTER(&htim1,0);
				__HAL_TIM_DISABLE(&htim1);      
			}
		else  								
			{
				TIM1CH1_CAPTURE_STA=0;//������ڼ���			
				TIM1CH1_CAPTURE_VAL=0;//�������Ĵ���
				CAPTURE_First=1;		 //�Ѳ����һ��������   
				CAPTURE_Status=0;    //�����ʱ
				P_Status=1;    //�������ڼ���
			}		    
	}		
	
}



/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
