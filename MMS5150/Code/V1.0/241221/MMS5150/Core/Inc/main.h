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
#define Ht162x_DAT_Pin GPIO_PIN_2
#define Ht162x_DAT_GPIO_Port GPIOE
#define Ht162x_WR_Pin GPIO_PIN_3
#define Ht162x_WR_GPIO_Port GPIOE
#define Ht162x_CS_Pin GPIO_PIN_5
#define Ht162x_CS_GPIO_Port GPIOE
#define MO1_Pin GPIO_PIN_1
#define MO1_GPIO_Port GPIOC
#define PWM1_Pin GPIO_PIN_2
#define PWM1_GPIO_Port GPIOC
#define MO2_Pin GPIO_PIN_3
#define MO2_GPIO_Port GPIOC
#define FG1_Pin GPIO_PIN_0
#define FG1_GPIO_Port GPIOA
#define FG2_Pin GPIO_PIN_1
#define FG2_GPIO_Port GPIOA
#define FG3_Pin GPIO_PIN_2
#define FG3_GPIO_Port GPIOA
#define FG4_Pin GPIO_PIN_3
#define FG4_GPIO_Port GPIOA
#define PWM2_Pin GPIO_PIN_4
#define PWM2_GPIO_Port GPIOA
#define MO3_Pin GPIO_PIN_5
#define MO3_GPIO_Port GPIOA
#define FG5_Pin GPIO_PIN_6
#define FG5_GPIO_Port GPIOA
#define FG6_Pin GPIO_PIN_7
#define FG6_GPIO_Port GPIOA
#define PWM3_Pin GPIO_PIN_4
#define PWM3_GPIO_Port GPIOC
#define MO4_Pin GPIO_PIN_5
#define MO4_GPIO_Port GPIOC
#define FG7_Pin GPIO_PIN_0
#define FG7_GPIO_Port GPIOB
#define FG8_Pin GPIO_PIN_1
#define FG8_GPIO_Port GPIOB
#define PWM4_Pin GPIO_PIN_9
#define PWM4_GPIO_Port GPIOE
#define MO5_Pin GPIO_PIN_10
#define MO5_GPIO_Port GPIOE
#define PWM5_Pin GPIO_PIN_11
#define PWM5_GPIO_Port GPIOE
#define MO6_Pin GPIO_PIN_12
#define MO6_GPIO_Port GPIOE
#define PWM6_Pin GPIO_PIN_13
#define PWM6_GPIO_Port GPIOE
#define MO7_Pin GPIO_PIN_14
#define MO7_GPIO_Port GPIOE
#define PWM7_Pin GPIO_PIN_15
#define PWM7_GPIO_Port GPIOE
#define MO8_Pin GPIO_PIN_10
#define MO8_GPIO_Port GPIOB
#define PWM8_Pin GPIO_PIN_11
#define PWM8_GPIO_Port GPIOB
#define MO9_Pin GPIO_PIN_12
#define MO9_GPIO_Port GPIOB
#define PWM9_Pin GPIO_PIN_13
#define PWM9_GPIO_Port GPIOB
#define MO10_Pin GPIO_PIN_14
#define MO10_GPIO_Port GPIOB
#define LED_ADJ_Pin GPIO_PIN_15
#define LED_ADJ_GPIO_Port GPIOB
#define PWM10_Pin GPIO_PIN_8
#define PWM10_GPIO_Port GPIOD
#define MO11_Pin GPIO_PIN_9
#define MO11_GPIO_Port GPIOD
#define PWM11_Pin GPIO_PIN_10
#define PWM11_GPIO_Port GPIOD
#define MO12_Pin GPIO_PIN_11
#define MO12_GPIO_Port GPIOD
#define PWM12_Pin GPIO_PIN_12
#define PWM12_GPIO_Port GPIOD
#define MO13_Pin GPIO_PIN_14
#define MO13_GPIO_Port GPIOD
#define PWM13_Pin GPIO_PIN_15
#define PWM13_GPIO_Port GPIOD
#define FG9_Pin GPIO_PIN_6
#define FG9_GPIO_Port GPIOC
#define FG10_Pin GPIO_PIN_7
#define FG10_GPIO_Port GPIOC
#define FG11_Pin GPIO_PIN_8
#define FG11_GPIO_Port GPIOC
#define FG12_Pin GPIO_PIN_9
#define FG12_GPIO_Port GPIOC
#define MO14_Pin GPIO_PIN_9
#define MO14_GPIO_Port GPIOA
#define PWM14_Pin GPIO_PIN_10
#define PWM14_GPIO_Port GPIOA
#define MO15_Pin GPIO_PIN_11
#define MO15_GPIO_Port GPIOA
#define PWM15_Pin GPIO_PIN_12
#define PWM15_GPIO_Port GPIOA
#define KEY2_Pin GPIO_PIN_0
#define KEY2_GPIO_Port GPIOD
#define EC2A_Pin GPIO_PIN_1
#define EC2A_GPIO_Port GPIOD
#define EC2A_EXTI_IRQn EXTI1_IRQn
#define EC2B_Pin GPIO_PIN_2
#define EC2B_GPIO_Port GPIOD
#define KEY1_Pin GPIO_PIN_3
#define KEY1_GPIO_Port GPIOD
#define EC1A_Pin GPIO_PIN_4
#define EC1A_GPIO_Port GPIOD
#define EC1A_EXTI_IRQn EXTI4_IRQn
#define EC1B_Pin GPIO_PIN_5
#define EC1B_GPIO_Port GPIOD
#define FG13_Pin GPIO_PIN_6
#define FG13_GPIO_Port GPIOB
#define FG14_Pin GPIO_PIN_7
#define FG14_GPIO_Port GPIOB
#define FG15_Pin GPIO_PIN_8
#define FG15_GPIO_Port GPIOB
#define Beep_Pin GPIO_PIN_9
#define Beep_GPIO_Port GPIOB
#define LED_KEY_Pin GPIO_PIN_1
#define LED_KEY_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
