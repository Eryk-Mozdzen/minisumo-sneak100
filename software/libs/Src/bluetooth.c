/*
 * bluetooth.c
 *
 *  Created on: Aug 27, 2021
 *      Author: ermoz
 */

#include "bluetooth.h"

void Bluetooth_Init(Bluetooth_t *bluetooth, UART_HandleTypeDef *huart,
		GPIO_TypeDef *en_port, uint16_t en_pin, GPIO_TypeDef *st_port, uint16_t st_pin) {

	bluetooth->huart = huart;
	bluetooth->EN_Port = en_port;
	bluetooth->EN_Pin = en_pin;
	bluetooth->ST_Port = st_port;
	bluetooth->ST_Pin = st_pin;

	RxBufferUART_Init(&bluetooth->buffer, bluetooth->huart, 256);
}

HAL_StatusTypeDef Bluetooth_SetConfig(Bluetooth_t *bluetooth, Bluetooth_Config_t config) {

	if(__Bluetooth_EnterATMode(bluetooth)!=HAL_OK) {
		__Bluetooth_ExitATMode(bluetooth);
		return HAL_TIMEOUT;
	}

	// set values
	HAL_StatusTypeDef status = HAL_OK;

	if(__Bluetooth_WriteParameter(bluetooth, "AT+NAME=%s\r\n", config.name)!=HAL_OK) 			status = HAL_ERROR;
	if(__Bluetooth_WriteParameter(bluetooth, "AT+PSWD=\"%s\"\r\n", config.password)!=HAL_OK) 	status = HAL_ERROR;
	if(__Bluetooth_WriteParameter(bluetooth, "AT+UART=%u,0,0\r\n", config.baudrate)!=HAL_OK) 	status = HAL_ERROR;

	__Bluetooth_ExitATMode(bluetooth);

	return status;
}

Bluetooth_Status_t Bluetooth_GetStatus(Bluetooth_t *bluetooth) {

	/*HAL_StatusTypeDef test = __Bluetooth_EnterATMode(bluetooth);
	__Bluetooth_ExitATMode(bluetooth);

	if(test!=HAL_OK)
		return BLUETOOTH_STATUS_ERROR;*/

	return HAL_GPIO_ReadPin(bluetooth->ST_Port, bluetooth->ST_Pin) ? BLUETOOTH_STATUS_PAIRED : BLUETOOTH_STATUS_WAITING_FOR_CONNECTION;
}

HAL_StatusTypeDef __Bluetooth_WriteParameter(Bluetooth_t *bluetooth, const char *format, ...) {
	char buffer[64] = {0};

	va_list argptr;
	va_start(argptr, format);
	vsprintf(buffer, format, argptr);
	va_end(argptr);

	if(HAL_UART_Transmit(bluetooth->huart, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY)!=HAL_OK)
		return HAL_TIMEOUT;

	// OK\r\n (4 characters)
	if(HAL_UART_Receive(bluetooth->huart, (uint8_t*)buffer, 4, 1000)!=HAL_OK)
		return HAL_TIMEOUT;

	if(strncmp(buffer, "OK", 2)!=0)
		return HAL_ERROR;

	return HAL_OK;
}

HAL_StatusTypeDef __Bluetooth_EnterATMode(Bluetooth_t *bluetooth) {
	RxBufferUART_Stop(&bluetooth->buffer);

	HAL_GPIO_WritePin(bluetooth->EN_Port, bluetooth->EN_Pin, GPIO_PIN_SET);
	HAL_Delay(50);

	return __Bluetooth_WriteParameter(bluetooth, "AT\r\n");
}

HAL_StatusTypeDef __Bluetooth_ExitATMode(Bluetooth_t *bluetooth) {
	HAL_GPIO_WritePin(bluetooth->EN_Port, bluetooth->EN_Pin, GPIO_PIN_RESET);

	__Bluetooth_WriteParameter(bluetooth, "AT+RESET\r\n");

	RxBufferUART_Start(&bluetooth->buffer);

	return HAL_OK;
}

