/*
 * proximity.h
 *
 *  Created on: Aug 22, 2021
 *      Author: ermoz
 */

#ifndef SNEAK100_ABSTRACTION_LAYER_INC_PROXIMITY_H_
#define SNEAK100_ABSTRACTION_LAYER_INC_PROXIMITY_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>

typedef struct {
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
} ProximitySensor_StructTypeDef;

uint8_t ProximitySensor_GetState(ProximitySensor_StructTypeDef *);

#endif /* SNEAK100_ABSTRACTION_LAYER_INC_PROXIMITY_H_ */
