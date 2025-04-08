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
#define Beep_Pin GPIO_PIN_13
#define Beep_GPIO_Port GPIOC
#define PWM4_Pin GPIO_PIN_0
#define PWM4_GPIO_Port GPIOA
#define PWM3_Pin GPIO_PIN_1
#define PWM3_GPIO_Port GPIOA
#define PWM2_Pin GPIO_PIN_2
#define PWM2_GPIO_Port GPIOA
#define PWM1_Pin GPIO_PIN_3
#define PWM1_GPIO_Port GPIOA
#define CW2_Pin GPIO_PIN_4
#define CW2_GPIO_Port GPIOA
#define CW1_Pin GPIO_PIN_5
#define CW1_GPIO_Port GPIOA
#define FG1_Pin GPIO_PIN_6
#define FG1_GPIO_Port GPIOA
#define FG2_Pin GPIO_PIN_7
#define FG2_GPIO_Port GPIOA
#define FG3_Pin GPIO_PIN_0
#define FG3_GPIO_Port GPIOB
#define FG4_Pin GPIO_PIN_1
#define FG4_GPIO_Port GPIOB
#define CW4_Pin GPIO_PIN_2
#define CW4_GPIO_Port GPIOB
#define CW3_Pin GPIO_PIN_10
#define CW3_GPIO_Port GPIOB
#define KEY2_Pin GPIO_PIN_11
#define KEY2_GPIO_Port GPIOB
#define EC2B_Pin GPIO_PIN_12
#define EC2B_GPIO_Port GPIOB
#define EC2A_Pin GPIO_PIN_13
#define EC2A_GPIO_Port GPIOB
#define RGB_Pin GPIO_PIN_14
#define RGB_GPIO_Port GPIOB
#define KEY3_Pin GPIO_PIN_15
#define KEY3_GPIO_Port GPIOB
#define KEY4_Pin GPIO_PIN_8
#define KEY4_GPIO_Port GPIOA
#define KEY5_Pin GPIO_PIN_9
#define KEY5_GPIO_Port GPIOA
#define Ht162x_DAT1_Pin GPIO_PIN_10
#define Ht162x_DAT1_GPIO_Port GPIOA
#define Ht162x_WR1_Pin GPIO_PIN_11
#define Ht162x_WR1_GPIO_Port GPIOA
#define Ht162x_CS1_Pin GPIO_PIN_12
#define Ht162x_CS1_GPIO_Port GPIOA
#define Ht162x_DAT2_Pin GPIO_PIN_15
#define Ht162x_DAT2_GPIO_Port GPIOA
#define Ht162x_WR2_Pin GPIO_PIN_3
#define Ht162x_WR2_GPIO_Port GPIOB
#define Ht162x_CS2_Pin GPIO_PIN_4
#define Ht162x_CS2_GPIO_Port GPIOB
#define EC1B_Pin GPIO_PIN_5
#define EC1B_GPIO_Port GPIOB
#define EC1A_Pin GPIO_PIN_6
#define EC1A_GPIO_Port GPIOB
#define KEY1_Pin GPIO_PIN_7
#define KEY1_GPIO_Port GPIOB
#define LED_ADJ_Pin GPIO_PIN_8
#define LED_ADJ_GPIO_Port GPIOB
#define LED_POR_Pin GPIO_PIN_9
#define LED_POR_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
