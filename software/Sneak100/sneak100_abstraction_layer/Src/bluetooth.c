/*
 * bluetooth.c
 *
 *  Created on: Aug 27, 2021
 *      Author: ermoz
 */

#include "bluetooth.h"

void Bluetooth_Init(Bluetooth_StructTypeDef *bluetooth) {

}

HAL_StatusTypeDef Bluetooth_SetConfig(Bluetooth_StructTypeDef *bluetooth, Bluetooth_ConfigTypeDef config) {

	// enter AT mode
	HAL_GPIO_WritePin(bluetooth->EN_Port, bluetooth->EN_Pin, GPIO_PIN_SET);
	HAL_Delay(50);

	// set values
	if(__Bluetooth_WriteATParameter(bluetooth, "AT\r\n")!=HAL_OK) 								return HAL_ERROR;
	if(__Bluetooth_WriteATParameter(bluetooth, "AT+NAME=%s\r\n", config.name)!=HAL_OK) 			return HAL_ERROR;
	if(__Bluetooth_WriteATParameter(bluetooth, "AT+PSWD=\"%s\"\r\n", config.password)!=HAL_OK) 	return HAL_ERROR;
	if(__Bluetooth_WriteATParameter(bluetooth, "AT+UART=%u,0,0\r\n", config.baudrate)!=HAL_OK) 	return HAL_ERROR;

	// exit AT mode
	HAL_GPIO_WritePin(bluetooth->EN_Port, bluetooth->EN_Pin, GPIO_PIN_RESET);
	HAL_Delay(50);

	if(__Bluetooth_WriteATParameter(bluetooth, "AT+RESET\r\n")!=HAL_OK) 						return HAL_ERROR;

	return HAL_OK;
}

Bluetooth_StatusTypeDef Bluetooth_GetStatus(Bluetooth_StructTypeDef *bluetooth) {
	return HAL_GPIO_ReadPin(bluetooth->STATUS_Port, bluetooth->STATUS_Pin) ? STATUS_PAIRED : STATUS_WAITING_FOR_CONNECTION;
}

HAL_StatusTypeDef __Bluetooth_WriteATParameter(Bluetooth_StructTypeDef *bluetooth, const char *format, ...) {
	HAL_StatusTypeDef error;
	char buffer[64] = {0};

	va_list argptr;
	va_start(argptr, format);
	vsprintf(buffer, format, argptr);
	va_end(argptr);

	error = HAL_UART_Transmit(bluetooth->huart, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);
	if(error!=HAL_OK)
		return error;

	// OK\r\n (4 characters)
	error = HAL_UART_Receive(bluetooth->huart, (uint8_t*)buffer, 4, 50);
	if(error!=HAL_OK)
		return error;

	buffer[2] = '\0';

	if(strcmp(buffer, "OK")!=0)
		return HAL_ERROR;

	return HAL_OK;
}
