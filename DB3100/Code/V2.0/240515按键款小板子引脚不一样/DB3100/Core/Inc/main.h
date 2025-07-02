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
#include "adc.h"
#include "tim.h"
#include "gpio.h"
#include "HT1623.h"
#include "Show.h"
#include "Scheduler.h"
#include "Ntc.h"
#include "KEY.h"
#include "Flash.h"
#include "User.h"
#include "TimeDown.h"
#include "TempControl.h"
#include "Beep.h"
#include "Param.h"
#include "SetVal.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef struct
{
	uint8_t Init_ok;  			//系统初始化是否完成，完成为1
}_sys_;
extern _sys_ sys;
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
#define Ht1621_CS_Pin GPIO_PIN_4
#define Ht1621_CS_GPIO_Port GPIOA
#define Ht1621_WR_Pin GPIO_PIN_5
#define Ht1621_WR_GPIO_Port GPIOA
#define Ht1621_DAT_Pin GPIO_PIN_7
#define Ht1621_DAT_GPIO_Port GPIOA
#define KEY4_Pin GPIO_PIN_0
#define KEY4_GPIO_Port GPIOB
#define KEY3_Pin GPIO_PIN_1
#define KEY3_GPIO_Port GPIOB
#define KEY2_Pin GPIO_PIN_2
#define KEY2_GPIO_Port GPIOB
#define KEY1_Pin GPIO_PIN_10
#define KEY1_GPIO_Port GPIOB
#define KEY5_Pin GPIO_PIN_11
#define KEY5_GPIO_Port GPIOB
#define Beep_Pin GPIO_PIN_7
#define Beep_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
