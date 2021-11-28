/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "sneak100_motors.h"
#include "sneak100_bluetooth.h"
#include "sneak100_display.h"
#include "sneak100_proximity.h"
#include "sneak100_adc.h"
#include "sneak100_memory.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  MX_TIM4_Init();
  MX_ADC1_Init();
  MX_USART6_UART_Init();
  MX_TIM10_Init();
  MX_TIM9_Init();
  /* USER CODE BEGIN 2 */

  UART_SetSTDIN(&huart2);
  UART_SetSTDOUT(&huart2);

  /*printf("\n");
  uint8_t address = 0x00;
  for(uint16_t i=0; i<256; i++) {
	if(HAL_I2C_IsDeviceReady(&hi2c1, i, 1, 10)==HAL_OK) {
		address = i;
		printf("Found I2C device at: 0x%2X\n", address);
	}
  }*/

  SNEAK100_ADC_Init();
  SNEAK100_Memory_Init();
  SNEAK100_Display_Init();
  SNEAK100_Bluetooth_Init();
  SNEAK100_Motors_Init();
  SNEAK100_Proximity_Init();

  HAL_TIM_Base_Start_IT(&htim9);
  HAL_TIM_Base_Start_IT(&htim10);

  printf("\n");

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while(1) {

	  printf("(m - menu)$ ");
	  char buffer[10] = {0};
	  scanf("%s[^\n]", buffer);

	  switch(buffer[0]) {
	  	  case 'c': HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET); break;
	  	  case 'd': HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET); break;
	  	  case 'v': {
	  		  float value = SNEAK100_Memory_ReadFloat(MEMORY_ADDRESS_VALUE);
	  		  printf("value -> %f\n", value);
	  		  printf("value <- ");
	  		  scanf("%f", &value);
	  		  SNEAK100_Memory_WriteFloat(MEMORY_ADDRESS_VALUE, value);
	  		  printf("value -> %f\n", SNEAK100_Memory_ReadFloat(MEMORY_ADDRESS_VALUE));
	  	  } break;
	  	  case 'm': {
	  		printf("\nMenu:\n\
c - turn on led\n\
d - turn off led\n\
v - set value\n\
m - show menu\n\
	  			\n");
	  	  } break;
	  	  default: printf("Incorrect input\n"); break;
	  }

	  //gui.temperature = SNEAK100_Memory_ReadFloat(MEMORY_ADDRESS_VALUE);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

 /**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM11 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

	if(htim->Instance==TIM9) {
		gui.battery_voltage = SNEAK100_ADC_GetSupplyVoltage();
		gui.temperature = SNEAK100_ADC_GetTemperature();

		gui.line[0] = *lineLL.read_src;
		gui.line[1] = *lineLM.read_src;
		gui.line[2] = *lineRM.read_src;
		gui.line[3] = *lineRR.read_src;

		gui.position[0] = Encoder_GetPosition(&encoderFL);
		//gui.position[1] = Encoder_GetPosition(&encoderFR);
		//gui.position[2] = Encoder_GetPosition(&encoderBL);
		//gui.position[3] = Encoder_GetPosition(&encoderBR);

		gui.velocity[0] = Encoder_GetVelocity(&encoderFL);
		//gui.velocity[1] = Encoder_GetVelocity(&encoderFR);
		//gui.velocity[2] = Encoder_GetVelocity(&encoderBL);
		//gui.velocity[3] = Encoder_GetVelocity(&encoderBR);
	}

	if(htim->Instance==TIM10) {
		SNEAK100_Display_Render();
	}

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM11) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  //__disable_irq();

  printf("Enter error handler!\n");

  while(1) {
	  HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	  HAL_Delay(100);
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
