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
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define BLUETOOTH_NAME_MAX_LENGTH		31
#define BLUETOOTH_PASSWORD_MAX_LENGTH	16

typedef enum {
	BLUETOOTH_BAUDRATE_4800 = 4800,
	BLUETOOTH_BAUDRATE_9600 = 9600,
	BLUETOOTH_BAUDRATE_19200 = 19200,
	BLUETOOTH_BAUDRATE_38400 = 38400,
	BLUETOOTH_BAUDRATE_57600 = 57600,
	BLUETOOTH_BAUDRATE_115200 = 115200,
	BLUETOOTH_BAUDRATE_234000 = 234000,
	BLUETOOTH_BAUDRATE_460800 = 460800,
	BLUETOOTH_BAUDRATE_921600 = 921600,
	BLUETOOTH_BAUDRATE_1382400 = 1382400
} Bluetooth_Baudrate_t;

typedef enum {
	BLUETOOTH_STATUS_WAITING_FOR_CONNECTION,
	BLUETOOTH_STATUS_PAIRED,
	BLUETOOTH_STATUS_ERROR
} Bluetooth_Status_t;

typedef struct {
	char name[BLUETOOTH_NAME_MAX_LENGTH];
	char password[BLUETOOTH_PASSWORD_MAX_LENGTH];
	Bluetooth_Baudrate_t baudrate;
} Bluetooth_Config_t;

typedef struct {
	UART_HandleTypeDef *huart;
	RxBufferUART_t buffer;

	GPIO_TypeDef *EN_Port;
	uint16_t EN_Pin;

	GPIO_TypeDef *ST_Port;
	uint16_t ST_Pin;
} Bluetooth_t;

void Bluetooth_Init(Bluetooth_t *, UART_HandleTypeDef *, GPIO_TypeDef *, uint16_t, GPIO_TypeDef *, uint16_t);
HAL_StatusTypeDef Bluetooth_SetConfig(Bluetooth_t *, Bluetooth_Config_t);

Bluetooth_Status_t Bluetooth_GetStatus(Bluetooth_t *);

HAL_StatusTypeDef __Bluetooth_WriteParameter(Bluetooth_t *, const char *, ...);
HAL_StatusTypeDef __Bluetooth_EnterATMode(Bluetooth_t *);
HAL_StatusTypeDef __Bluetooth_ExitATMode(Bluetooth_t *);

#endif
