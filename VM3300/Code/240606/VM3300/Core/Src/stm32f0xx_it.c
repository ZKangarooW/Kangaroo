/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f0xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_tim1_ch1;
extern DMA_HandleTypeDef hdma_tim1_ch4_trig_com;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim15;
extern TIM_HandleTypeDef htim17;
extern UART_HandleTypeDef huart1;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */
	if(!sys.Init_ok) return;//开机初始化未完成不进入
		Loop_Check();//1ms执行一次
  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 channel 2 and 3 interrupts.
  */
void DMA1_Channel2_3_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel2_3_IRQn 0 */

  /* USER CODE END DMA1_Channel2_3_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_tim1_ch1);
  /* USER CODE BEGIN DMA1_Channel2_3_IRQn 1 */

  /* USER CODE END DMA1_Channel2_3_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel 4 and 5 interrupts.
  */
void DMA1_Channel4_5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel4_5_IRQn 0 */

  /* USER CODE END DMA1_Channel4_5_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_tim1_ch4_trig_com);
  /* USER CODE BEGIN DMA1_Channel4_5_IRQn 1 */

  /* USER CODE END DMA1_Channel4_5_IRQn 1 */
}

/**
  * @brief This function handles TIM6 global interrupt.
  */
void TIM6_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_IRQn 0 */

  /* USER CODE END TIM6_IRQn 0 */
  HAL_TIM_IRQHandler(&htim6);
  /* USER CODE BEGIN TIM6_IRQn 1 */

  /* USER CODE END TIM6_IRQn 1 */
}

/**
  * @brief This function handles TIM15 global interrupt.
  */
void TIM15_IRQHandler(void)
{
  /* USER CODE BEGIN TIM15_IRQn 0 */

  /* USER CODE END TIM15_IRQn 0 */
  HAL_TIM_IRQHandler(&htim15);
  /* USER CODE BEGIN TIM15_IRQn 1 */
//if(__HAL_TIM_GET_FLAG(&htim15, TIM_FLAG_UPDATE))      //定时器溢出中断
//    {
//        __HAL_TIM_CLEAR_FLAG(&htim15, TIM_FLAG_UPDATE);    //清除中断标记
//        TIM3_Over_Cnt++;
//    }
//    cnt0 = __HAL_TIM_GET_COUNTER(&htim15);
//    TIM3_Sum_Cnt = (TIM3_Over_Cnt << 16) + cnt0;//获取计数器的值
//    __HAL_TIM_SetCounter(&htim15,0);//清零重新计数
//    TIM3_Over_Cnt = 0;//清零重新计数
// 
//    if (__HAL_TIM_GET_FLAG(&htim15, TIM_FLAG_CC2) != RESET)//TIM3CH1捕获中断
//    {
//       if(StartRevFlag == 1)//接收到引导码，开始解码
//       {
//         if(TIM3_Sum_Cnt > 36000)//大于36ms认为是结束
//         {
//           RevComplete = 1;//解码完成
//           IR_Tick = 0;
//         }
//         else if(RevComplete == 0)
//         {
//           if(TIM3_Sum_Cnt > 1000 && TIM3_Sum_Cnt < 1300)//1ms~1.3ms认为是低电平
//            IR_Data[IR_Idx] = 0;
//           else  if(TIM3_Sum_Cnt > 2100 && TIM3_Sum_Cnt < 2400)//2.1ms~2.4ms认为是高电平
//            IR_Data[IR_Idx] = 1;
//           else //接收错误，重新开始
//             StartRevFlag = 0;
//           IR_Idx++;
//           if(IR_Idx > 59)
//             IR_Idx = 59;
//        }
// 
//       }
//       else
//       {
//         if(TIM3_Sum_Cnt > 13000 && TIM3_Sum_Cnt < 14000)//13~14ms引导码
//         {
//           StartRevFlag = 1;
//         }
//         IR_Tick = 0;
//         RevComplete = 0;//解码完成标志置零
//         IR_Idx = 0;//有效解码位
//         TIM3_Over_Cnt = 0;
//         TIM3_Sum_Cnt = 0;//定时器计数清零
//       }
//        __HAL_TIM_CLEAR_IT(&htim15, TIM_IT_CC1);
//    }

  /* USER CODE END TIM15_IRQn 1 */
}

/**
  * @brief This function handles TIM17 global interrupt.
  */
void TIM17_IRQHandler(void)
{
  /* USER CODE BEGIN TIM17_IRQn 0 */

  /* USER CODE END TIM17_IRQn 0 */
  HAL_TIM_IRQHandler(&htim17);
  /* USER CODE BEGIN TIM17_IRQn 1 */

  /* USER CODE END TIM17_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
