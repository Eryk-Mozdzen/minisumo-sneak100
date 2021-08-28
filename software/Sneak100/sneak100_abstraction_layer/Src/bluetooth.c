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

	char buffer[64] = {0};
	UART_SetActive(bluetooth->huart);

	// ------------------------- enter AT mode --------------------------------

	HAL_GPIO_WritePin(bluetooth->EN_Port, bluetooth->EN_Pin, GPIO_PIN_SET);
	HAL_Delay(50);

	// ------------------------- set values -----------------------------------

	sprintf(buffer, "AT+NAME=%s\r\n", config.name);
	HAL_UART_Transmit(bluetooth->huart, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);
	HAL_Delay(50);

	sprintf(buffer, "AT+PSWD=\"%s\"\r\n", config.password);
	HAL_UART_Transmit(bluetooth->huart, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);
	HAL_Delay(50);

	sprintf(buffer, "AT+UART=%u,0,0\r\n", config.baudrate);
	HAL_UART_Transmit(bluetooth->huart, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);
	HAL_Delay(50);

	// -------------------------- exit AT mode --------------------------------

	HAL_GPIO_WritePin(bluetooth->EN_Port, bluetooth->EN_Pin, GPIO_PIN_RESET);

	sprintf(buffer, "AT+RESET\r\n");
	HAL_UART_Transmit(bluetooth->huart, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);
	HAL_Delay(50);

	return HAL_OK;
}

Bluetooth_StatusTypeDef Bluetooth_GetStatus(Bluetooth_StructTypeDef *bluetooth) {
	return HAL_GPIO_ReadPin(bluetooth->STATUS_Port, bluetooth->STATUS_Pin) ? STATUS_PAIRED : STATUS_WAITING_FOR_CONNECTION;
}
