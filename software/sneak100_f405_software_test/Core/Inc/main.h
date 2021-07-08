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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
#define MODULE_START_Pin GPIO_PIN_13
#define MODULE_START_GPIO_Port GPIOC
#define MODULE_KILL_Pin GPIO_PIN_14
#define MODULE_KILL_GPIO_Port GPIOC
#define LINE_LL_Pin GPIO_PIN_0
#define LINE_LL_GPIO_Port GPIOC
#define LINE_LM_Pin GPIO_PIN_1
#define LINE_LM_GPIO_Port GPIOC
#define LINE_RM_Pin GPIO_PIN_2
#define LINE_RM_GPIO_Port GPIOC
#define LINE_RR_Pin GPIO_PIN_3
#define LINE_RR_GPIO_Port GPIOC
#define BATTERY_SENSE_Pin GPIO_PIN_4
#define BATTERY_SENSE_GPIO_Port GPIOC
#define PROXIMITY_RX_READ_Pin GPIO_PIN_5
#define PROXIMITY_RX_READ_GPIO_Port GPIOC
#define PROXIMITY_TX_ENABLE_Pin GPIO_PIN_8
#define PROXIMITY_TX_ENABLE_GPIO_Port GPIOC
#define USER_LED1_Pin GPIO_PIN_15
#define USER_LED1_GPIO_Port GPIOA
#define USER_LED2_Pin GPIO_PIN_10
#define USER_LED2_GPIO_Port GPIOC
#define USER_LED3_Pin GPIO_PIN_11
#define USER_LED3_GPIO_Port GPIOC
#define USER_BUTTON_Pin GPIO_PIN_12
#define USER_BUTTON_GPIO_Port GPIOC
#define RECEIVER_OUT_Pin GPIO_PIN_2
#define RECEIVER_OUT_GPIO_Port GPIOD
#define PROXIMITY_ADD0_Pin GPIO_PIN_3
#define PROXIMITY_ADD0_GPIO_Port GPIOB
#define PROXIMITY_ADD1_Pin GPIO_PIN_4
#define PROXIMITY_ADD1_GPIO_Port GPIOB
#define PROXIMITY_ADD2_Pin GPIO_PIN_5
#define PROXIMITY_ADD2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
