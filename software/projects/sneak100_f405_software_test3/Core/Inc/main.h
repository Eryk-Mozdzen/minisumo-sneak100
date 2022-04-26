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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define PROX4_Pin GPIO_PIN_13
#define PROX4_GPIO_Port GPIOC
#define PROX3_Pin GPIO_PIN_14
#define PROX3_GPIO_Port GPIOC
#define RECIV_Pin GPIO_PIN_15
#define RECIV_GPIO_Port GPIOC
#define LINE1_Pin GPIO_PIN_0
#define LINE1_GPIO_Port GPIOC
#define LINE2_Pin GPIO_PIN_1
#define LINE2_GPIO_Port GPIOC
#define LINE3_Pin GPIO_PIN_2
#define LINE3_GPIO_Port GPIOC
#define LINE4_Pin GPIO_PIN_3
#define LINE4_GPIO_Port GPIOC
#define MOT1_IN1_Pin GPIO_PIN_0
#define MOT1_IN1_GPIO_Port GPIOA
#define MOT1_IN2_Pin GPIO_PIN_1
#define MOT1_IN2_GPIO_Port GPIOA
#define MOT2_IN1_Pin GPIO_PIN_2
#define MOT2_IN1_GPIO_Port GPIOA
#define MOT2_IN2_Pin GPIO_PIN_3
#define MOT2_IN2_GPIO_Port GPIOA
#define PROX2_Pin GPIO_PIN_4
#define PROX2_GPIO_Port GPIOA
#define PROX1_Pin GPIO_PIN_5
#define PROX1_GPIO_Port GPIOA
#define LED_G_Pin GPIO_PIN_6
#define LED_G_GPIO_Port GPIOA
#define PROX_GEN_Pin GPIO_PIN_7
#define PROX_GEN_GPIO_Port GPIOA
#define BATTERY_Pin GPIO_PIN_4
#define BATTERY_GPIO_Port GPIOC
#define SW3_Pin GPIO_PIN_0
#define SW3_GPIO_Port GPIOB
#define SW2_Pin GPIO_PIN_1
#define SW2_GPIO_Port GPIOB
#define SW1_Pin GPIO_PIN_2
#define SW1_GPIO_Port GPIOB
#define MOT3_IN1_Pin GPIO_PIN_10
#define MOT3_IN1_GPIO_Port GPIOB
#define MOT3_IN2_Pin GPIO_PIN_11
#define MOT3_IN2_GPIO_Port GPIOB
#define BUTT1_Pin GPIO_PIN_12
#define BUTT1_GPIO_Port GPIOB
#define BUTT2_Pin GPIO_PIN_13
#define BUTT2_GPIO_Port GPIOB
#define BUTT3_Pin GPIO_PIN_14
#define BUTT3_GPIO_Port GPIOB
#define MOT1_A_Pin GPIO_PIN_6
#define MOT1_A_GPIO_Port GPIOC
#define MOT1_B_Pin GPIO_PIN_7
#define MOT1_B_GPIO_Port GPIOC
#define MOT2_A_Pin GPIO_PIN_8
#define MOT2_A_GPIO_Port GPIOA
#define MOT2_B_Pin GPIO_PIN_9
#define MOT2_B_GPIO_Port GPIOA
#define USB_DM_Pin GPIO_PIN_11
#define USB_DM_GPIO_Port GPIOA
#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA
#define MOT4_IN1_Pin GPIO_PIN_15
#define MOT4_IN1_GPIO_Port GPIOA
#define MTX_Pin GPIO_PIN_10
#define MTX_GPIO_Port GPIOC
#define MRX_Pin GPIO_PIN_11
#define MRX_GPIO_Port GPIOC
#define LED_Y_Pin GPIO_PIN_12
#define LED_Y_GPIO_Port GPIOC
#define MOT4_IN2_Pin GPIO_PIN_3
#define MOT4_IN2_GPIO_Port GPIOB
#define MOT3_A_Pin GPIO_PIN_4
#define MOT3_A_GPIO_Port GPIOB
#define MOT3_B_Pin GPIO_PIN_5
#define MOT3_B_GPIO_Port GPIOB
#define MOT4_A_Pin GPIO_PIN_6
#define MOT4_A_GPIO_Port GPIOB
#define MOT4_B_Pin GPIO_PIN_7
#define MOT4_B_GPIO_Port GPIOB
#define SCL_Pin GPIO_PIN_8
#define SCL_GPIO_Port GPIOB
#define SDA_Pin GPIO_PIN_9
#define SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
