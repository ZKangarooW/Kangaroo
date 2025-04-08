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
#define IR2_Pin GPIO_PIN_2
#define IR2_GPIO_Port GPIOA
#define IR1_Pin GPIO_PIN_3
#define IR1_GPIO_Port GPIOA
#define TM1650_SCL_Pin GPIO_PIN_4
#define TM1650_SCL_GPIO_Port GPIOA
#define TM1650_SDA_Pin GPIO_PIN_5
#define TM1650_SDA_GPIO_Port GPIOA
#define D1_Pin GPIO_PIN_6
#define D1_GPIO_Port GPIOA
#define D2_Pin GPIO_PIN_7
#define D2_GPIO_Port GPIOA
#define OUT3_Pin GPIO_PIN_12
#define OUT3_GPIO_Port GPIOB
#define OUT2_Pin GPIO_PIN_14
#define OUT2_GPIO_Port GPIOB
#define GRB_Pin GPIO_PIN_8
#define GRB_GPIO_Port GPIOA
#define GRB1_Pin GPIO_PIN_11
#define GRB1_GPIO_Port GPIOA
#define OUT1_Pin GPIO_PIN_12
#define OUT1_GPIO_Port GPIOA
#define Beep_Pin GPIO_PIN_15
#define Beep_GPIO_Port GPIOA
#define CW_Pin GPIO_PIN_3
#define CW_GPIO_Port GPIOB
#define PWM_Pin GPIO_PIN_8
#define PWM_GPIO_Port GPIOB
#define FG_Pin GPIO_PIN_9
#define FG_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
