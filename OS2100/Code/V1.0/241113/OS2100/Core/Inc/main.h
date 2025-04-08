/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#define KEY4_Pin GPIO_PIN_13
#define KEY4_GPIO_Port GPIOC
#define KEY3_Pin GPIO_PIN_14
#define KEY3_GPIO_Port GPIOC
#define KEY2_Pin GPIO_PIN_15
#define KEY2_GPIO_Port GPIOC
#define KEY1_Pin GPIO_PIN_5
#define KEY1_GPIO_Port GPIOA
#define Beep_Pin GPIO_PIN_6
#define Beep_GPIO_Port GPIOA
#define DIG10_Pin GPIO_PIN_7
#define DIG10_GPIO_Port GPIOA
#define DIG6_Pin GPIO_PIN_0
#define DIG6_GPIO_Port GPIOB
#define DIG7_Pin GPIO_PIN_1
#define DIG7_GPIO_Port GPIOB
#define DIG8_Pin GPIO_PIN_2
#define DIG8_GPIO_Port GPIOB
#define UC_D_Pin GPIO_PIN_10
#define UC_D_GPIO_Port GPIOB
#define DIG5_Pin GPIO_PIN_11
#define DIG5_GPIO_Port GPIOB
#define UC_E_Pin GPIO_PIN_12
#define UC_E_GPIO_Port GPIOB
#define UC_F_Pin GPIO_PIN_13
#define UC_F_GPIO_Port GPIOB
#define UC_G_Pin GPIO_PIN_14
#define UC_G_GPIO_Port GPIOB
#define DIG4_Pin GPIO_PIN_15
#define DIG4_GPIO_Port GPIOB
#define UC_C_Pin GPIO_PIN_8
#define UC_C_GPIO_Port GPIOA
#define FG_Pin GPIO_PIN_9
#define FG_GPIO_Port GPIOA
#define CW_Pin GPIO_PIN_10
#define CW_GPIO_Port GPIOA
#define MO_Pin GPIO_PIN_11
#define MO_GPIO_Port GPIOA
#define DIG3_Pin GPIO_PIN_12
#define DIG3_GPIO_Port GPIOA
#define UC_B_Pin GPIO_PIN_6
#define UC_B_GPIO_Port GPIOF
#define DIG9_Pin GPIO_PIN_7
#define DIG9_GPIO_Port GPIOF
#define UC_A_Pin GPIO_PIN_15
#define UC_A_GPIO_Port GPIOA
#define DIG2_Pin GPIO_PIN_3
#define DIG2_GPIO_Port GPIOB
#define DIG1_Pin GPIO_PIN_4
#define DIG1_GPIO_Port GPIOB
#define PWM_Pin GPIO_PIN_5
#define PWM_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
