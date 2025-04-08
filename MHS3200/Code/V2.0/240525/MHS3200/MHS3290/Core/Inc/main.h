/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
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
#define Ht1621_WR_Pin GPIO_PIN_2
#define Ht1621_WR_GPIO_Port GPIOE
#define Ht1621_CS_Pin GPIO_PIN_3
#define Ht1621_CS_GPIO_Port GPIOE
#define Ht1621_DAT_Pin GPIO_PIN_5
#define Ht1621_DAT_GPIO_Port GPIOE
#define PWM1_Pin GPIO_PIN_0
#define PWM1_GPIO_Port GPIOA
#define PWM2_Pin GPIO_PIN_1
#define PWM2_GPIO_Port GPIOA
#define PWM3_Pin GPIO_PIN_2
#define PWM3_GPIO_Port GPIOA
#define PWM4_Pin GPIO_PIN_3
#define PWM4_GPIO_Port GPIOA
#define PWM7_Pin GPIO_PIN_6
#define PWM7_GPIO_Port GPIOA
#define PWM8_Pin GPIO_PIN_7
#define PWM8_GPIO_Port GPIOA
#define PWM5_Pin GPIO_PIN_0
#define PWM5_GPIO_Port GPIOB
#define PW6_Pin GPIO_PIN_1
#define PW6_GPIO_Port GPIOB
#define MO1_Pin GPIO_PIN_7
#define MO1_GPIO_Port GPIOE
#define MO2_Pin GPIO_PIN_8
#define MO2_GPIO_Port GPIOE
#define MO3_Pin GPIO_PIN_9
#define MO3_GPIO_Port GPIOE
#define MO4_Pin GPIO_PIN_10
#define MO4_GPIO_Port GPIOE
#define MO5_Pin GPIO_PIN_11
#define MO5_GPIO_Port GPIOE
#define MO6_Pin GPIO_PIN_12
#define MO6_GPIO_Port GPIOE
#define MO7_Pin GPIO_PIN_13
#define MO7_GPIO_Port GPIOE
#define MO8_Pin GPIO_PIN_14
#define MO8_GPIO_Port GPIOE
#define Beep_Pin GPIO_PIN_12
#define Beep_GPIO_Port GPIOB
#define KEY2A_Pin GPIO_PIN_8
#define KEY2A_GPIO_Port GPIOD
#define KEY2A_EXTI_IRQn EXTI9_5_IRQn
#define KEY2B_Pin GPIO_PIN_9
#define KEY2B_GPIO_Port GPIOD
#define KEY2_Pin GPIO_PIN_10
#define KEY2_GPIO_Port GPIOD
#define FG1_Pin GPIO_PIN_6
#define FG1_GPIO_Port GPIOC
#define FG2_Pin GPIO_PIN_7
#define FG2_GPIO_Port GPIOC
#define FG3_Pin GPIO_PIN_8
#define FG3_GPIO_Port GPIOC
#define FG4_Pin GPIO_PIN_9
#define FG4_GPIO_Port GPIOC
#define FG5_Pin GPIO_PIN_8
#define FG5_GPIO_Port GPIOA
#define FG6_Pin GPIO_PIN_9
#define FG6_GPIO_Port GPIOA
#define FG7_Pin GPIO_PIN_10
#define FG7_GPIO_Port GPIOA
#define FG8_Pin GPIO_PIN_11
#define FG8_GPIO_Port GPIOA
#define MO9_Pin GPIO_PIN_0
#define MO9_GPIO_Port GPIOD
#define KEY1_Pin GPIO_PIN_7
#define KEY1_GPIO_Port GPIOD
#define FG9_Pin GPIO_PIN_3
#define FG9_GPIO_Port GPIOB
#define PWM9_Pin GPIO_PIN_6
#define PWM9_GPIO_Port GPIOB
#define HEAT_Pin GPIO_PIN_7
#define HEAT_GPIO_Port GPIOB
#define LED_ADJ_Pin GPIO_PIN_8
#define LED_ADJ_GPIO_Port GPIOB
#define KEY1A_Pin GPIO_PIN_9
#define KEY1A_GPIO_Port GPIOB
#define KEY1A_EXTI_IRQn EXTI9_5_IRQn
#define KEY1B_Pin GPIO_PIN_0
#define KEY1B_GPIO_Port GPIOE
#define LED_KEY_Pin GPIO_PIN_1
#define LED_KEY_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
