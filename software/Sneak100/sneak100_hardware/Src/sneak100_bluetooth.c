/*
 * sneak100_bluetooth.c
 *
 *  Created on: Aug 27, 2021
 *      Author: ermoz
 */

#include "sneak100_bluetooth.h"

Bluetooth_StructTypeDef bluetooth;

void SNEAK100_Bluetooth_Init() {

	bluetooth.huart = huart6;
	bluetooth.EN_Port = BLUETOOTH_EN_GPIO_Port;
	bluetooth.EN_Pin = BLUETOOTH_EN_Pin;
	bluetooth.STATUS_Port = BLUETOOTH_STATUS_GPIO_Port;
	bluetooth.STATUS_Pin = BLUETOOTH_STATUS_Pin;
	Bluetooth_Init(&bluetooth);

	Bluetooth_ConfigTypeDef config = {0};
	config.name = "Sneak100";
	config.password = "7777";
	config.baudrate = 38400;
	Bluetooth_SetConfig(&bluetooth, config);

}
