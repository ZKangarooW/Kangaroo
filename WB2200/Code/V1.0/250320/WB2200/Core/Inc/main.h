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
#define FGS_Pin GPIO_PIN_2
#define FGS_GPIO_Port GPIOA
#define KEY2_Pin GPIO_PIN_2
#define KEY2_GPIO_Port GPIOB
#define KEY3_Pin GPIO_PIN_10
#define KEY3_GPIO_Port GPIOB
#define KEY1_Pin GPIO_PIN_11
#define KEY1_GPIO_Port GPIOB
#define TM1640_SCL_Pin GPIO_PIN_6
#define TM1640_SCL_GPIO_Port GPIOF
#define TM1640_SDA_Pin GPIO_PIN_7
#define TM1640_SDA_GPIO_Port GPIOF
#define HEAT_Pin GPIO_PIN_5
#define HEAT_GPIO_Port GPIOB
#define Beep_Pin GPIO_PIN_7
#define Beep_GPIO_Port GPIOB
#define KEY4_Pin GPIO_PIN_8
#define KEY4_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
