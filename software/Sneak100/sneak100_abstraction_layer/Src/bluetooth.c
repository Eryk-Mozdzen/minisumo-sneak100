/*
 * bluetooth.c
 *
 *  Created on: Aug 27, 2021
 *      Author: ermoz
 */

#include "bluetooth.h"

void Bluetooth_Init(Bluetooth_StructTypeDef *bluetooth) {

	bluetooth->rx_buffer = (uint8_t *)malloc(BLUETOOTH_RX_BUFFER_SIZE * sizeof(uint8_t));

	bluetooth->rx_flag = 0;

	HAL_UART_Receive_IT(bluetooth->huart, bluetooth->rx_buffer, bluetooth->rx_data_size);
}

HAL_StatusTypeDef Bluetooth_SetConfig(Bluetooth_StructTypeDef *bluetooth, Bluetooth_ConfigTypeDef config) {

	HAL_UART_AbortReceive_IT(bluetooth->huart);

	// enter AT mode
	HAL_GPIO_WritePin(bluetooth->EN_Port, bluetooth->EN_Pin, GPIO_PIN_SET);
	HAL_Delay(1000);

	// connection test
	if(__Bluetooth_WriteParameter(bluetooth, "AT\r\n")!=HAL_OK) {
		// HC-05 not attached
		HAL_GPIO_WritePin(bluetooth->EN_Port, bluetooth->EN_Pin, GPIO_PIN_RESET);
		HAL_Delay(50);
		return HAL_TIMEOUT;
	}

	// set values
	HAL_StatusTypeDef status = HAL_OK;

	if(__Bluetooth_WriteParameter(bluetooth, "AT+NAME=%s\r\n", config.name)==HAL_ERROR) 			status = HAL_ERROR;
	if(__Bluetooth_WriteParameter(bluetooth, "AT+PSWD=\"%s\"\r\n", config.password)==HAL_ERROR) 	status = HAL_ERROR;
	if(__Bluetooth_WriteParameter(bluetooth, "AT+UART=%u,0,0\r\n", config.baudrate)==HAL_ERROR) 	status = HAL_ERROR;

	// exit AT mode
	HAL_GPIO_WritePin(bluetooth->EN_Port, bluetooth->EN_Pin, GPIO_PIN_RESET);
	HAL_Delay(50);

	__Bluetooth_WriteParameter(bluetooth, "AT+RESET\r\n");

	HAL_UART_Receive_IT(bluetooth->huart, bluetooth->rx_buffer, bluetooth->rx_data_size);

	return status;
}

Bluetooth_StatusTypeDef Bluetooth_GetStatus(Bluetooth_StructTypeDef *bluetooth) {
	return HAL_GPIO_ReadPin(bluetooth->STATUS_Port, bluetooth->STATUS_Pin) ? STATUS_PAIRED : STATUS_WAITING_FOR_CONNECTION;
}

void Bluetooth_RxCpltCallback(Bluetooth_StructTypeDef *bluetooth, UART_HandleTypeDef *huart) {
	if(huart!=bluetooth->huart)
		return;

	bluetooth->rx_flag = 1;

	HAL_UART_Receive_IT(bluetooth->huart, bluetooth->rx_buffer, bluetooth->rx_data_size);
}

uint8_t Bluetooth_IsDataReady(Bluetooth_StructTypeDef *bluetooth) {
	return bluetooth->rx_flag;
}

void Bluetooth_ReadData(Bluetooth_StructTypeDef *bluetooth, uint8_t *buffer) {
	memcpy(buffer, bluetooth->rx_buffer, bluetooth->rx_data_size);

	bluetooth->rx_flag = 0;
}

HAL_StatusTypeDef __Bluetooth_WriteParameter(Bluetooth_StructTypeDef *bluetooth, const char *format, ...) {
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
