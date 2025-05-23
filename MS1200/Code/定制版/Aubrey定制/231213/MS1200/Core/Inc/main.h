/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
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
#define Beep_Pin GPIO_PIN_6
#define Beep_GPIO_Port GPIOA
#define KEY1A_Pin GPIO_PIN_0
#define KEY1A_GPIO_Port GPIOB
#define KEY1A_EXTI_IRQn EXTI0_1_IRQn
#define KEY1B_Pin GPIO_PIN_1
#define KEY1B_GPIO_Port GPIOB
#define KEY1_Pin GPIO_PIN_2
#define KEY1_GPIO_Port GPIOB
#define DIG4_Pin GPIO_PIN_11
#define DIG4_GPIO_Port GPIOB
#define G_Pin GPIO_PIN_12
#define G_GPIO_Port GPIOB
#define C_Pin GPIO_PIN_13
#define C_GPIO_Port GPIOB
#define D_Pin GPIO_PIN_14
#define D_GPIO_Port GPIOB
#define E_Pin GPIO_PIN_15
#define E_GPIO_Port GPIOB
#define MO_Pin GPIO_PIN_11
#define MO_GPIO_Port GPIOA
#define B_Pin GPIO_PIN_15
#define B_GPIO_Port GPIOA
#define DIG3_Pin GPIO_PIN_3
#define DIG3_GPIO_Port GPIOB
#define DIG2_Pin GPIO_PIN_4
#define DIG2_GPIO_Port GPIOB
#define F_Pin GPIO_PIN_5
#define F_GPIO_Port GPIOB
#define A_Pin GPIO_PIN_6
#define A_GPIO_Port GPIOB
#define DIG1_Pin GPIO_PIN_7
#define DIG1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
