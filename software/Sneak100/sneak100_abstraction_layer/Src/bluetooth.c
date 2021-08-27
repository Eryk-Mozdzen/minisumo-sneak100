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
	//HAL_StatusTypeDef error;

	sprintf(buffer, "AT+NAME=%s\r\n", config.name);
	HAL_UART_Transmit(&bluetooth->huart, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);

	//sprintf(buffer, "AT+NAME?\r\n");
	//HAL_UART_Transmit(&bluetooth->huart, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);
	//HAL_UART_Receive(&bluetooth->huart, (uint8_t*)buffer, 64, HAL_MAX_DELAY);
	//printf("%s\n", buffer);

	HAL_Delay(10);

	sprintf(buffer, "AT+PSWD=\"%s\"\r\n", config.password);
	HAL_UART_Transmit(&bluetooth->huart, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);

	return HAL_OK;
}
