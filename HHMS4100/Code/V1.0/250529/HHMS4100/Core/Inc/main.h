/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "include.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define AD_T1_Pin GPIO_PIN_0
#define AD_T1_GPIO_Port GPIOC
#define AD_T2_Pin GPIO_PIN_1
#define AD_T2_GPIO_Port GPIOC
#define AD_T3_Pin GPIO_PIN_2
#define AD_T3_GPIO_Port GPIOC
#define AD_T4_Pin GPIO_PIN_3
#define AD_T4_GPIO_Port GPIOC
#define AD_T9_Pin GPIO_PIN_0
#define AD_T9_GPIO_Port GPIOA
#define AD_T10_Pin GPIO_PIN_1
#define AD_T10_GPIO_Port GPIOA
#define AD_T12_Pin GPIO_PIN_2
#define AD_T12_GPIO_Port GPIOA
#define AD_T11_Pin GPIO_PIN_3
#define AD_T11_GPIO_Port GPIOA
#define AD_T8_Pin GPIO_PIN_4
#define AD_T8_GPIO_Port GPIOA
#define AD_T7_Pin GPIO_PIN_5
#define AD_T7_GPIO_Port GPIOA
#define FG4_Pin GPIO_PIN_6
#define FG4_GPIO_Port GPIOA
#define FG3_Pin GPIO_PIN_7
#define FG3_GPIO_Port GPIOA
#define AD_T6_Pin GPIO_PIN_4
#define AD_T6_GPIO_Port GPIOC
#define AD_T5_Pin GPIO_PIN_5
#define AD_T5_GPIO_Port GPIOC
#define FG2_Pin GPIO_PIN_0
#define FG2_GPIO_Port GPIOB
#define FG1_Pin GPIO_PIN_1
#define FG1_GPIO_Port GPIOB
#define FG6_Pin GPIO_PIN_10
#define FG6_GPIO_Port GPIOB
#define FG5_Pin GPIO_PIN_11
#define FG5_GPIO_Port GPIOB
#define EC2B_Pin GPIO_PIN_8
#define EC2B_GPIO_Port GPIOD
#define EC2A_Pin GPIO_PIN_9
#define EC2A_GPIO_Port GPIOD
#define EC2A_EXTI_IRQn EXTI9_5_IRQn
#define KEY2_Pin GPIO_PIN_10
#define KEY2_GPIO_Port GPIOD
#define HEAT5_Pin GPIO_PIN_9
#define HEAT5_GPIO_Port GPIOA
#define HEAT6_Pin GPIO_PIN_10
#define HEAT6_GPIO_Port GPIOA
#define LED_ADJ_Pin GPIO_PIN_11
#define LED_ADJ_GPIO_Port GPIOA
#define KEY1_Pin GPIO_PIN_5
#define KEY1_GPIO_Port GPIOD
#define EC1B_Pin GPIO_PIN_6
#define EC1B_GPIO_Port GPIOD
#define EC1A_Pin GPIO_PIN_7
#define EC1A_GPIO_Port GPIOD
#define EC1A_EXTI_IRQn EXTI9_5_IRQn
#define HEAT1_Pin GPIO_PIN_6
#define HEAT1_GPIO_Port GPIOB
#define HEAT2_Pin GPIO_PIN_7
#define HEAT2_GPIO_Port GPIOB
#define HEAT3_Pin GPIO_PIN_8
#define HEAT3_GPIO_Port GPIOB
#define HEAT4_Pin GPIO_PIN_9
#define HEAT4_GPIO_Port GPIOB
#define Beep_Pin GPIO_PIN_0
#define Beep_GPIO_Port GPIOE
#define LED_POR_Pin GPIO_PIN_1
#define LED_POR_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
