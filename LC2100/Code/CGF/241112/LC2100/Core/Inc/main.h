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
#define LED_ADJ_Pin GPIO_PIN_4
#define LED_ADJ_GPIO_Port GPIOA
#define UC_DCT1_Pin GPIO_PIN_5
#define UC_DCT1_GPIO_Port GPIOA
#define UC_IN_Pin GPIO_PIN_6
#define UC_IN_GPIO_Port GPIOA
#define PWM_Pin GPIO_PIN_1
#define PWM_GPIO_Port GPIOB
#define Beep_Pin GPIO_PIN_11
#define Beep_GPIO_Port GPIOB
#define KEY5_Pin GPIO_PIN_15
#define KEY5_GPIO_Port GPIOB
#define FG_Pin GPIO_PIN_8
#define FG_GPIO_Port GPIOA
#define KEY1_Pin GPIO_PIN_9
#define KEY1_GPIO_Port GPIOA
#define KEY2_Pin GPIO_PIN_10
#define KEY2_GPIO_Port GPIOA
#define KEY3_Pin GPIO_PIN_11
#define KEY3_GPIO_Port GPIOA
#define KEY4_Pin GPIO_PIN_12
#define KEY4_GPIO_Port GPIOA
#define COL1_Pin GPIO_PIN_6
#define COL1_GPIO_Port GPIOF
#define COL2_Pin GPIO_PIN_7
#define COL2_GPIO_Port GPIOF
#define Ht1621_DAT_Pin GPIO_PIN_4
#define Ht1621_DAT_GPIO_Port GPIOB
#define Ht1621_WR_Pin GPIO_PIN_5
#define Ht1621_WR_GPIO_Port GPIOB
#define Ht1621_CS_Pin GPIO_PIN_7
#define Ht1621_CS_GPIO_Port GPIOB
#define UC_DCT_Pin GPIO_PIN_8
#define UC_DCT_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
