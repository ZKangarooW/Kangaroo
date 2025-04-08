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
#define Ht162x_CS_Pin GPIO_PIN_1
#define Ht162x_CS_GPIO_Port GPIOA
#define Ht162x_WR_Pin GPIO_PIN_2
#define Ht162x_WR_GPIO_Port GPIOA
#define Ht162x_DAT_Pin GPIO_PIN_3
#define Ht162x_DAT_GPIO_Port GPIOA
#define LED_ADJ_Pin GPIO_PIN_4
#define LED_ADJ_GPIO_Port GPIOA
#define MO_Pin GPIO_PIN_5
#define MO_GPIO_Port GPIOA
#define FG1_Pin GPIO_PIN_6
#define FG1_GPIO_Port GPIOA
#define FG2_Pin GPIO_PIN_7
#define FG2_GPIO_Port GPIOA
#define FG3_Pin GPIO_PIN_0
#define FG3_GPIO_Port GPIOB
#define FG4_Pin GPIO_PIN_1
#define FG4_GPIO_Port GPIOB
#define KEY1A_Pin GPIO_PIN_12
#define KEY1A_GPIO_Port GPIOB
#define KEY1A_EXTI_IRQn EXTI4_15_IRQn
#define KEY1B_Pin GPIO_PIN_13
#define KEY1B_GPIO_Port GPIOB
#define KEY2A_Pin GPIO_PIN_14
#define KEY2A_GPIO_Port GPIOB
#define KEY2A_EXTI_IRQn EXTI4_15_IRQn
#define KEY2B_Pin GPIO_PIN_15
#define KEY2B_GPIO_Port GPIOB
#define PWM1_Pin GPIO_PIN_8
#define PWM1_GPIO_Port GPIOA
#define PWM2_Pin GPIO_PIN_9
#define PWM2_GPIO_Port GPIOA
#define PWM3_Pin GPIO_PIN_10
#define PWM3_GPIO_Port GPIOA
#define PWM4_Pin GPIO_PIN_11
#define PWM4_GPIO_Port GPIOA
#define KEY1_Pin GPIO_PIN_3
#define KEY1_GPIO_Port GPIOB
#define KEY2_Pin GPIO_PIN_5
#define KEY2_GPIO_Port GPIOB
#define Beep_Pin GPIO_PIN_7
#define Beep_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
