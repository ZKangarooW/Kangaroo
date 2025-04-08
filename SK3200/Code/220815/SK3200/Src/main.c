/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ht1623.h"
#include "lcd.h"
#include "user.h"
#include "key.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern uint16_t rel_speed;//实时速度
extern int rel_time;//实时时间
extern uint16_t set_speed;//设定速度
extern int set_time;//设定时间
extern uint8_t LOCK_Status;//安全锁标志 1：锁定 0：解锁
extern uint8_t CAPTURE_Status;//捕获状态 1：捕获中    0：捕获结束
extern uint16_t TIM1CH1_CAPTURE_STA;	//捕获周期数	
extern uint16_t dis_speed;	//显示速度
extern uint8_t Run_Status;//运行状态 1：run     0：stop 2:减速
extern uint16_t	dis_speed_N;
extern uint16_t	dis_speed_F;
extern uint16_t save_speed;
uint16_t Wise_Flag;//反转标志
uint16_t UP_Flag;//正转标志
uint32_t Set_Cnt1;//旋钮转速计数
uint32_t speed_set1;//旋钮转速
uint32_t next_cnt1;//旋钮时钟时间
uint32_t Set_Cnt2;//旋钮转速计数
uint32_t speed_set2;//旋钮转速
uint32_t next_cnt2;//旋钮时钟时间
uint8_t ADD_Mode;//显示增减模式
uint8_t  wise_blink=0;//运行闪烁
uint8_t time_disable;//关闭计时
//int     save_set_time;
//uint8_t save_time_dsisable;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
void speed_deal(void);
void status_up(void);
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim1); 
	HAL_TIM_Base_Start_IT(&htim3); 
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_3);
	Sys_Init();
	
	lcd_init();
	HAL_Delay (5);
  lcd_all();
	HAL_Delay(1000);
	lcd_clr();
	beep();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		Key_Handle();
		LCD_Display();
    speed_deal();
		 status_up();
		if(CAPTURE_Status)
		{
			
			__HAL_TIM_ENABLE(&htim1);
			CAPTURE_Status=0;
			TIM1CH1_CAPTURE_STA=0; 
		}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL4;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	   if (LOCK_Status)
			 return;
		 
		 if(Run_Status==2)
       return;
		 
		if(GPIO_Pin ==KEY1A_Pin)//时间设定旋钮
		{
			
			  Set_Cnt1++;
			  if(Set_Cnt1>3)
				{	
						uint32_t first1= HAL_GetTick();
						speed_set1=120000/(first1-next_cnt1);
						next_cnt1=first1;
						Set_Cnt1=0;
				}
			 if((HAL_GPIO_ReadPin(KEY1B_GPIO_Port,KEY1B_Pin)==0)&&(HAL_GPIO_ReadPin(KEY1A_GPIO_Port,KEY1A_Pin)==1))
			 {
				 if(Wise_Flag==0)
							{
								if(speed_set1>2000)
									set_time=set_time+600;
								else
								set_time=set_time+60;
								Wise_Flag =10;
								UP_Flag=100;
							}
					    
							if(set_time>86400)
								set_time=86400;
							
							if(set_time<60)
								set_time=0;
							
							time_disable=0;
							
			//			  save_set_time=set_time;
			//				save_time_dsisable=time_disable;
							
								
				}
				else if((HAL_GPIO_ReadPin(KEY1A_GPIO_Port,KEY1B_Pin)==1)&&(HAL_GPIO_ReadPin(KEY1A_GPIO_Port,KEY1A_Pin)==1))
				{
              if(UP_Flag==0)
							{
								if(speed_set1>2000)
								{
									if(set_time)
							    set_time=set_time-600;
									if(set_time<60)
									{
											set_time=0;
										  time_disable=1;
									}
								}
								else
								{
									if(set_time)
									set_time=set_time-60;	
									UP_Flag =10;
									Wise_Flag=100;
									time_disable=0;
									
									if(set_time<60)
									{
											set_time=0;
										  time_disable=1;
									}
						  	}	
                //save_set_time=set_time;
								//save_time_dsisable=time_disable;
								
								
							}
							

							
							
				}
				
				rel_time =set_time-1;
		}
		
		
			if(GPIO_Pin == KEY2A_Pin)//速度设定旋钮
	   {
			 
			  Set_Cnt2++;
			  if(Set_Cnt2>3)
				{	
						uint32_t first2= HAL_GetTick();
						speed_set2=120000/(first2-next_cnt2);
						next_cnt2=first2;
						Set_Cnt2=0;
				}
				if((HAL_GPIO_ReadPin(KEY2B_GPIO_Port,KEY2B_Pin)==0)&&(HAL_GPIO_ReadPin(KEY2A_GPIO_Port,KEY2A_Pin)==1))
				{
							if(Wise_Flag==0)
							{
								if(speed_set2>1000)
									set_speed=set_speed+20;
								else
								set_speed=set_speed+5;	
								if(set_speed>rel_speed)
						   	ADD_Mode =1;
						    else
						   	ADD_Mode =0;
								
								
								UP_Flag=100;
								Wise_Flag=10;
							}
					    
							if(set_speed>200)
								set_speed=200;
							
							if(set_speed<20)
								set_speed=20;
							
								
				}
				else if((HAL_GPIO_ReadPin(KEY2A_GPIO_Port,KEY2B_Pin)==1)&&(HAL_GPIO_ReadPin(KEY2A_GPIO_Port,KEY2A_Pin)==1))
				{
              if(UP_Flag==0)
							{
								if(speed_set2>1000)
								{
									if(set_speed)
								   set_speed=set_speed-20;
								}
								else
								{
									if(set_speed)
									set_speed=set_speed-5;	
						  	}	
               if(set_speed>rel_speed)
								ADD_Mode =1;
							  else
								ADD_Mode =0;
								
								Wise_Flag=100;
								UP_Flag=10;
							}
							
							//最小速度50
							if(set_speed<20)
								set_speed=20;
							
							
				}
	
     }
}


void speed_deal(void)
{
 if(ADD_Mode==1)
		 {
			 if(set_speed>rel_speed )
				 dis_speed =rel_speed;
			 else
			 {
				 dis_speed=set_speed;
				 ADD_Mode=4;
			 }
		 }
		 else
		 {
			 if(set_speed<rel_speed )
				 dis_speed =rel_speed;
			 else
			 {
				 dis_speed=set_speed;
				 ADD_Mode=4;
			 }
			 
		 }
		 if(Run_Status)
		 {
			// wise_blink=1;
		 }
		 else
			 wise_blink=0;
		 
		 
		 
	 }	 
extern int sumError1;
extern int lastError1;
extern uint32_t	TIM1CH1_CAPTURE_VAL;	//捕获计数值
void status_up(void)
{
	if(Run_Status ==2)
	{
		if(rel_speed <25)
		{
				Run_Status =0;
				ADD_Mode=0;
				rel_speed=0;
				set_speed=save_speed;
				dis_speed_N=0;
				dis_speed_F=0;
			  TIM1CH1_CAPTURE_STA=0;
			  TIM1CH1_CAPTURE_VAL=0;
				sumError1=0;
	      lastError1=0;
				HAL_GPIO_WritePin(MO_GPIO_Port, MO_Pin, GPIO_PIN_RESET);//电机guan
		}
	}
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
