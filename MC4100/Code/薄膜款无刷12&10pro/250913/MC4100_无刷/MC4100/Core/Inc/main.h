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
#define AD_T1_Pin GPIO_PIN_3
#define AD_T1_GPIO_Port GPIOA
#define Ht1621_CS_Pin GPIO_PIN_4
#define Ht1621_CS_GPIO_Port GPIOA
#define Ht1621_WR_Pin GPIO_PIN_5
#define Ht1621_WR_GPIO_Port GPIOA
#define Ht1621_DAT_Pin GPIO_PIN_7
#define Ht1621_DAT_GPIO_Port GPIOA
#define FG_Pin GPIO_PIN_0
#define FG_GPIO_Port GPIOB
#define Beep_Pin GPIO_PIN_15
#define Beep_GPIO_Port GPIOB
#define PWM_Pin GPIO_PIN_8
#define PWM_GPIO_Port GPIOA
#define BREAKEZ_Pin GPIO_PIN_9
#define BREAKEZ_GPIO_Port GPIOA
#define LED_ADJ_Pin GPIO_PIN_10
#define LED_ADJ_GPIO_Port GPIOA
#define DIR_Pin GPIO_PIN_11
#define DIR_GPIO_Port GPIOA
#define COL2_Pin GPIO_PIN_3
#define COL2_GPIO_Port GPIOB
#define COL1_Pin GPIO_PIN_4
#define COL1_GPIO_Port GPIOB
#define ROW3_Pin GPIO_PIN_5
#define ROW3_GPIO_Port GPIOB
#define ROW2_Pin GPIO_PIN_6
#define ROW2_GPIO_Port GPIOB
#define ROW1_Pin GPIO_PIN_7
#define ROW1_GPIO_Port GPIOB
#define UC_DCT_Pin GPIO_PIN_8
#define UC_DCT_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
