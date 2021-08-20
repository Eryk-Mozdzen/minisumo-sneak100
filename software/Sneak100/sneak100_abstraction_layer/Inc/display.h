/*
 * display.h
 *
 *  Created on: Aug 21, 2021
 *      Author: ermoz
 */

#ifndef SNEAK100_ABSTRACTION_LAYER_INC_DISPLAY_H_
#define SNEAK100_ABSTRACTION_LAYER_INC_DISPLAY_H_

#include "i2c.h"
#include <stdint.h>

typedef struct {
	I2C_HandleTypeDef *hi2c;
} Display_TypeDef;

void Display_Init(Display_TypeDef *, I2C_HandleTypeDef *, uint8_t, uint8_t);

#endif /* SNEAK100_ABSTRACTION_LAYER_INC_DISPLAY_H_ */
