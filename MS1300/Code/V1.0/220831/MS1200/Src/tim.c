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
uint16_t ms,ms2,ms3;
uint8_t CAPTURE_Status=0; //捕获状态
uint16_t  TIM1CH1_CAPTURE_STA=0;	//捕获周期数	    				
uint32_t	TIM1CH1_CAPTURE_VAL;	//捕获计数值
uint8_t   CAPTURE_First=0;//捕获第一个高电平
uint32_t P_Status;  //捕获周期计数状态  1开启 0关闭
uint16_t Speed1_Flag;//速度调0标志位
uint16_t rel_speed;
extern uint16_t set_speed;//设定速度
extern uint16_t dis_speed;//显示速度
extern uint8_t LOCK_time;
extern uint8_t Start_Time;//
extern uint16_t dis_blink;
extern uint16_t beep_time;
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
  htim3.Init.Prescaler = 32-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 1000-1;
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
    HAL_NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
    HAL_NVIC_SetPriority(TIM1_CC_IRQn, 0, 0);
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
    HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
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
uint16_t rel_speed_N,rel_speed_F;
uint16_t count;
extern uint16_t dis_speed;
extern  uint8_t Wise_Flag;
extern  uint8_t UP_Flag;
uint16_t T;
extern uint8_t ADD_Mode;
extern uint16_t KEY_Delay;
extern uint8_t Set_Dis;
uint16_t dis_flag=0;
uint16_t down_flag;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

	if(htim->Instance == TIM1)
  {
          if(P_Status)
					{

							 TIM1CH1_CAPTURE_STA++;
				  }
  }	
	if(htim->Instance == TIM3)
  {
		
		
		 if(ADD_Mode==1)
		 {
			 if(set_speed>rel_speed )
				 dis_speed =rel_speed;
			 else
			 {
				 dis_speed=set_speed;
				 ADD_Mode=3;
				 down_flag=200;
			 }
		 }
		 else if(ADD_Mode==0)
		 {
			 if(set_speed<rel_speed )
				 dis_speed =rel_speed;
			 else
			 {
				 dis_speed=set_speed;
				 ADD_Mode=3;
				 down_flag=200;
			 }
			 
		 }


			 
			 
			 
		  T++;
			if(T>9)
			{
				count++;
				 if(KEY_Delay)
					  KEY_Delay--;
				 
				 if(Set_Dis)
					Set_Dis--;
				 
				 //		 
				if(beep_time ) 
			 beep_time --;
		 if(beep_time ==0)
			   HAL_GPIO_WritePin(GPIOA, BEEP_Pin, GPIO_PIN_RESET);
				 
				 
				T=0;
				
			}
			
		 if( count%2==0)
     
			
		
			if( count%25==0)
			{
        PWM_Set();
				if(Wise_Flag)
				Wise_Flag--;
				if(UP_Flag)
				UP_Flag--;
				
       if(down_flag )
        down_flag--;
			}
			if(dis_blink)
			{	
		   if( count>50)
       dis_flag=0;
			 else
				dis_flag=1; 
					
				
					
			}
		if(count>100)
		{
			
				if(Start_Time)
		    Start_Time--;
				
				
				
								if(Speed1_Flag)
				Speed1_Flag--;
			if(Speed1_Flag==0)
				rel_speed=0;
			count=0;
		}
		
		
  }	
	
}
//输入捕获回调函数
uint16_t test=0;
long long temp=0;
uint16_t reltest=0;

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
		if(CAPTURE_Status)
		{
			__HAL_TIM_ENABLE(&htim1);
			CAPTURE_Status=0;
			TIM1CH1_CAPTURE_STA=0; 
		}
	if(CAPTURE_Status==0)
	{
		 Speed1_Flag=2;
		if(CAPTURE_First)		 		
			{	  		
				
				CAPTURE_Status=1;		//停止捕获计时
				CAPTURE_First=0;    //清除捕获第一个上升沿标志
				TIM1CH1_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_3);//获取当前捕获计数值
				
				
				temp=TIM1CH1_CAPTURE_STA;  
				temp*=50;	//一个周期100us	 	    
				temp+=TIM1CH1_CAPTURE_VAL; //一个周期所需的us数   
				temp=30000000/temp; //rpm
				
				if(ADD_Mode==3)
				{
					if(down_flag==0)
					{
					if(temp>set_speed)
					{
						if((temp-set_speed)>(set_speed/2))
							temp=set_speed;
					}
				}
				}
				else
				rel_speed_N=temp;
				
				rel_speed_N=temp;
				
		    reltest=temp;
				if((rel_speed_F>199))
				{
						if(rel_speed_N>rel_speed_F)
						{
							
							if((rel_speed_N-rel_speed_F)>(rel_speed_F-rel_speed_F/5))
							{
								rel_speed_N=rel_speed_F;
							}
							else
								rel_speed=rel_speed_N;
						}
						else
						rel_speed=rel_speed_N;
			} 
				
			      
			    rel_speed=rel_speed_N;
			if(rel_speed>390)
			{
				test=1;
			}
			
				rel_speed_F=rel_speed_N;
				P_Status=0;
				__HAL_TIM_SET_COUNTER(&htim1,0);
				__HAL_TIM_DISABLE(&htim1);      
			}
		else  								
			{
				TIM1CH1_CAPTURE_STA=0;//清除周期计数			
				TIM1CH1_CAPTURE_VAL=0;//清楚捕获寄存器
				CAPTURE_First=1;		 //已捕获第一个上升沿   
				CAPTURE_Status=0;    //捕获计时
				P_Status=1;    //捕获周期计数
			}		    
	}		

	
	
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
