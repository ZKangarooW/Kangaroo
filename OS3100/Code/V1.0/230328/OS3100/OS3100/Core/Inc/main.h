/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#define Beep_Pin GPIO_PIN_0
#define Beep_GPIO_Port GPIOA
#define DIG4_Pin GPIO_PIN_1
#define DIG4_GPIO_Port GPIOA
#define UC_C_Pin GPIO_PIN_2
#define UC_C_GPIO_Port GPIOA
#define DIG3_Pin GPIO_PIN_3
#define DIG3_GPIO_Port GPIOA
#define UC_B_Pin GPIO_PIN_4
#define UC_B_GPIO_Port GPIOA
#define DIG9_Pin GPIO_PIN_5
#define DIG9_GPIO_Port GPIOA
#define UC_A_Pin GPIO_PIN_6
#define UC_A_GPIO_Port GPIOA
#define DIG2_Pin GPIO_PIN_7
#define DIG2_GPIO_Port GPIOA
#define DIG1_Pin GPIO_PIN_0
#define DIG1_GPIO_Port GPIOB
#define DIG8_Pin GPIO_PIN_1
#define DIG8_GPIO_Port GPIOB
#define DIG7_Pin GPIO_PIN_2
#define DIG7_GPIO_Port GPIOB
#define UC_D_Pin GPIO_PIN_10
#define UC_D_GPIO_Port GPIOB
#define DIG6_Pin GPIO_PIN_11
#define DIG6_GPIO_Port GPIOB
#define DIG5_Pin GPIO_PIN_12
#define DIG5_GPIO_Port GPIOB
#define UC_E_Pin GPIO_PIN_13
#define UC_E_GPIO_Port GPIOB
#define UC_F_Pin GPIO_PIN_14
#define UC_F_GPIO_Port GPIOB
#define UC_G_Pin GPIO_PIN_15
#define UC_G_GPIO_Port GPIOB
#define DIG10_Pin GPIO_PIN_8
#define DIG10_GPIO_Port GPIOA
#define DIR_Pin GPIO_PIN_10
#define DIR_GPIO_Port GPIOA
#define BREAKEZ_Pin GPIO_PIN_11
#define BREAKEZ_GPIO_Port GPIOA
#define KEY1B_Pin GPIO_PIN_12
#define KEY1B_GPIO_Port GPIOA
#define KEY1B_EXTI_IRQn EXTI4_15_IRQn
#define KEY1A_Pin GPIO_PIN_6
#define KEY1A_GPIO_Port GPIOF
#define KEY1_Pin GPIO_PIN_7
#define KEY1_GPIO_Port GPIOF
#define KEY1_EXTI_IRQn EXTI4_15_IRQn
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
