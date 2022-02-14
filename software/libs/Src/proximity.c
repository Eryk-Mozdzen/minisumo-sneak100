/*
 * proximity.c
 *
 *  Created on: Aug 22, 2021
 *      Author: ermoz
 */

#include "proximity.h"

void Proximity_Init(Proximity_t *sensor, GPIO_TypeDef *port, uint16_t pin) {
	sensor->GPIOx = port;
	sensor->GPIO_Pin = pin;
}

uint8_t Proximity_GetState(Proximity_t *sensor) {
	return !HAL_GPIO_ReadPin(sensor->GPIOx, sensor->GPIO_Pin);
}
