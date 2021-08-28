/*
 * bluetooth.h
 *
 *  Created on: Aug 27, 2021
 *      Author: ermoz
 */

#ifndef SNEAK100_ABSTRACTION_LAYER_INC_BLUETOOTH_H_
#define SNEAK100_ABSTRACTION_LAYER_INC_BLUETOOTH_H_

#include "stm32f4xx_hal.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef enum {
	BAUDRATE_4800 = 4800,
	BAUDRATE_9600 = 9600,
	BAUDRATE_19200 = 19200,
	BAUDRATE_38400 = 38400,
	BAUDRATE_57600 = 57600,
	BAUDRATE_115200 = 115200,
	BAUDRATE_234000 = 234000,
	BAUDRATE_460800 = 460800,
	BAUDRATE_921600 = 921600,
	BAUDRATE_1382400 = 1382400
} Bluetooth_BaudrateEnumTypeDef;

typedef enum {
	STATUS_WAITING_FOR_CONNECTION,
	STATUS_PAIRED
} Bluetooth_StatusTypeDef;

typedef struct {
	UART_HandleTypeDef *huart;

	GPIO_TypeDef* EN_Port;
	uint16_t EN_Pin;

	GPIO_TypeDef* STATUS_Port;
	uint16_t STATUS_Pin;
} Bluetooth_StructTypeDef;

typedef struct {
	char *name;
	char *password;
	Bluetooth_BaudrateEnumTypeDef baudrate;
} Bluetooth_ConfigTypeDef;

void Bluetooth_Init(Bluetooth_StructTypeDef *);
HAL_StatusTypeDef Bluetooth_SetConfig(Bluetooth_StructTypeDef *, Bluetooth_ConfigTypeDef);

Bluetooth_StatusTypeDef Bluetooth_GetStatus(Bluetooth_StructTypeDef *);

#endif /* SNEAK100_ABSTRACTION_LAYER_INC_BLUETOOTH_H_ */
