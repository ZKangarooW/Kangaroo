/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32f0xx_hal.h"

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
#define G1_Pin GPIO_PIN_13
#define G1_GPIO_Port GPIOC
#define FG_Pin GPIO_PIN_4
#define FG_GPIO_Port GPIOA
#define EC1A_Pin GPIO_PIN_5
#define EC1A_GPIO_Port GPIOA
#define EC1A_EXTI_IRQn EXTI4_15_IRQn
#define EC1B_Pin GPIO_PIN_6
#define EC1B_GPIO_Port GPIOA
#define KEY1_Pin GPIO_PIN_7
#define KEY1_GPIO_Port GPIOA
#define RGB_Pin GPIO_PIN_0
#define RGB_GPIO_Port GPIOB
#define LED_ADJ_Pin GPIO_PIN_1
#define LED_ADJ_GPIO_Port GPIOB
#define OUT1_Pin GPIO_PIN_2
#define OUT1_GPIO_Port GPIOB
#define Ht162x_DAT_Pin GPIO_PIN_12
#define Ht162x_DAT_GPIO_Port GPIOB
#define Ht162x_WR_Pin GPIO_PIN_13
#define Ht162x_WR_GPIO_Port GPIOB
#define Ht162x_CS_Pin GPIO_PIN_15
#define Ht162x_CS_GPIO_Port GPIOB
#define Beep_Pin GPIO_PIN_8
#define Beep_GPIO_Port GPIOA
#define PWM_Pin GPIO_PIN_9
#define PWM_GPIO_Port GPIOA
#define OUT2_Pin GPIO_PIN_7
#define OUT2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
