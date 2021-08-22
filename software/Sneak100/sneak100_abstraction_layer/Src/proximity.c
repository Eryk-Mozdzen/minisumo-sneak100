/*
 * proximity.c
 *
 *  Created on: Aug 22, 2021
 *      Author: ermoz
 */

#include "proximity.h"

uint8_t ProximitySensor_GetState(ProximitySensor_StructTypeDef *sensor) {
	return !HAL_GPIO_ReadPin(sensor->GPIOx, sensor->GPIO_Pin);
}
