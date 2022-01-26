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
#define RECEIVER_OUT_Pin GPIO_PIN_13
#define RECEIVER_OUT_GPIO_Port GPIOC
#define RECEIVER_OUT_EXTI_IRQn EXTI15_10_IRQn
#define PROXIMITY_RR_Pin GPIO_PIN_14
#define PROXIMITY_RR_GPIO_Port GPIOC
#define PROXIMITY_FR_Pin GPIO_PIN_15
#define PROXIMITY_FR_GPIO_Port GPIOC
#define LINE_RR_Pin GPIO_PIN_0
#define LINE_RR_GPIO_Port GPIOC
#define LINE_RM_Pin GPIO_PIN_1
#define LINE_RM_GPIO_Port GPIOC
#define LINE_LM_Pin GPIO_PIN_2
#define LINE_LM_GPIO_Port GPIOC
#define LINE_LL_Pin GPIO_PIN_3
#define LINE_LL_GPIO_Port GPIOC
#define MOTOR_RB_A_Pin GPIO_PIN_0
#define MOTOR_RB_A_GPIO_Port GPIOA
#define MOTOR_RB_B_Pin GPIO_PIN_1
#define MOTOR_RB_B_GPIO_Port GPIOA
#define BLUETOOTH_ST_Pin GPIO_PIN_4
#define BLUETOOTH_ST_GPIO_Port GPIOA
#define BLUETOOTH_PWR_Pin GPIO_PIN_6
#define BLUETOOTH_PWR_GPIO_Port GPIOA
#define BLUETOOTH_EN_Pin GPIO_PIN_7
#define BLUETOOTH_EN_GPIO_Port GPIOA
#define BATTERY_SENSE_Pin GPIO_PIN_4
#define BATTERY_SENSE_GPIO_Port GPIOC
#define PROXIMITY_FL_Pin GPIO_PIN_0
#define PROXIMITY_FL_GPIO_Port GPIOB
#define PROXIMITY_LL_Pin GPIO_PIN_1
#define PROXIMITY_LL_GPIO_Port GPIOB
#define USER_LED_YELLOW_Pin GPIO_PIN_14
#define USER_LED_YELLOW_GPIO_Port GPIOB
#define USER_LED_GREEN_Pin GPIO_PIN_15
#define USER_LED_GREEN_GPIO_Port GPIOB
#define MOTOR_RB_IN1_Pin GPIO_PIN_6
#define MOTOR_RB_IN1_GPIO_Port GPIOC
#define MOTOR_RB_IN2_Pin GPIO_PIN_7
#define MOTOR_RB_IN2_GPIO_Port GPIOC
#define MOTOR_LB_IN1_Pin GPIO_PIN_8
#define MOTOR_LB_IN1_GPIO_Port GPIOA
#define MOTOR_LB_IN2_Pin GPIO_PIN_9
#define MOTOR_LB_IN2_GPIO_Port GPIOA
#define MOTOR_LF_IN1_Pin GPIO_PIN_10
#define MOTOR_LF_IN1_GPIO_Port GPIOA
#define MOTOR_LF_IN2_Pin GPIO_PIN_11
#define MOTOR_LF_IN2_GPIO_Port GPIOA
#define MOTOR_LF_A_Pin GPIO_PIN_15
#define MOTOR_LF_A_GPIO_Port GPIOA
#define USER_BUTTON_L_Pin GPIO_PIN_10
#define USER_BUTTON_L_GPIO_Port GPIOC
#define USER_BUTTON_L_EXTI_IRQn EXTI15_10_IRQn
#define USER_BUTTON_C_Pin GPIO_PIN_11
#define USER_BUTTON_C_GPIO_Port GPIOC
#define USER_BUTTON_C_EXTI_IRQn EXTI15_10_IRQn
#define USER_BUTTON_R_Pin GPIO_PIN_12
#define USER_BUTTON_R_GPIO_Port GPIOC
#define USER_BUTTON_R_EXTI_IRQn EXTI15_10_IRQn
#define MOTOR_LF_B_Pin GPIO_PIN_3
#define MOTOR_LF_B_GPIO_Port GPIOB
#define MOTOR_LB_A_Pin GPIO_PIN_4
#define MOTOR_LB_A_GPIO_Port GPIOB
#define MOTOR_LB_B_Pin GPIO_PIN_5
#define MOTOR_LB_B_GPIO_Port GPIOB
#define MOTOR_RF_A_Pin GPIO_PIN_6
#define MOTOR_RF_A_GPIO_Port GPIOB
#define MOTOR_RF_B_Pin GPIO_PIN_7
#define MOTOR_RF_B_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
