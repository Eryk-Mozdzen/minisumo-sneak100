/*
 * bluetooth.h
 *
 *  Created on: Aug 27, 2021
 *      Author: ermoz
 */

#ifndef SNEAK100_ABSTRACTION_LAYER_INC_BLUETOOTH_H_
#define SNEAK100_ABSTRACTION_LAYER_INC_BLUETOOTH_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct {
	UART_HandleTypeDef huart;

	GPIO_TypeDef* EN_Port;
	uint16_t EN_Pin;

	GPIO_TypeDef* STATUS_Port;
	uint16_t STATUS_Pin;
} Bluetooth_StructTypeDef;

typedef struct {
	char *name;
	char *password;
	uint32_t baudrate;
} Bluetooth_ConfigTypeDef;

void Bluetooth_Init(Bluetooth_StructTypeDef *);
HAL_StatusTypeDef Bluetooth_SetConfig(Bluetooth_StructTypeDef *, Bluetooth_ConfigTypeDef);

#endif /* SNEAK100_ABSTRACTION_LAYER_INC_BLUETOOTH_H_ */
