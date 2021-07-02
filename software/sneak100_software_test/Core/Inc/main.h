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
#define MOTOR_FL_DIR_Pin GPIO_PIN_0
#define MOTOR_FL_DIR_GPIO_Port GPIOB
#define MOTOR_FR_DIR_Pin GPIO_PIN_1
#define MOTOR_FR_DIR_GPIO_Port GPIOB
#define MOTOR_BL_DIR_Pin GPIO_PIN_2
#define MOTOR_BL_DIR_GPIO_Port GPIOB
#define MOTOR_BR_DIR_Pin GPIO_PIN_10
#define MOTOR_BR_DIR_GPIO_Port GPIOB
#define PROXIMITY_TX_ADD0_Pin GPIO_PIN_12
#define PROXIMITY_TX_ADD0_GPIO_Port GPIOB
#define PROXIMITY_TX_ADD1_Pin GPIO_PIN_13
#define PROXIMITY_TX_ADD1_GPIO_Port GPIOB
#define PROXIMITY_TX_ADD2_Pin GPIO_PIN_14
#define PROXIMITY_TX_ADD2_GPIO_Port GPIOB
#define USER_BUTTON_Pin GPIO_PIN_15
#define USER_BUTTON_GPIO_Port GPIOB
#define IR_RX_Pin GPIO_PIN_6
#define IR_RX_GPIO_Port GPIOC
#define USER_LED0_Pin GPIO_PIN_7
#define USER_LED0_GPIO_Port GPIOC
#define USER_LED1_Pin GPIO_PIN_8
#define USER_LED1_GPIO_Port GPIOC
#define USER_LED2_Pin GPIO_PIN_9
#define USER_LED2_GPIO_Port GPIOC
#define PROXIMITY_RX_ADD0_Pin GPIO_PIN_10
#define PROXIMITY_RX_ADD0_GPIO_Port GPIOC
#define PROXIMITY_RX_ADD1_Pin GPIO_PIN_11
#define PROXIMITY_RX_ADD1_GPIO_Port GPIOC
#define PROXIMITY_RX_ADD2_Pin GPIO_PIN_12
#define PROXIMITY_RX_ADD2_GPIO_Port GPIOC
#define SMODULE_STR_Pin GPIO_PIN_4
#define SMODULE_STR_GPIO_Port GPIOB
#define SMODULE_KILL_Pin GPIO_PIN_5
#define SMODULE_KILL_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
