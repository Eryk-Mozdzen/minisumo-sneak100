/*
 * display.h
 *
 *  Created on: Aug 21, 2021
 *      Author: ermoz
 */

#ifndef SNEAK100_ABSTRACTION_LAYER_INC_DISPLAY_H_
#define SNEAK100_ABSTRACTION_LAYER_INC_DISPLAY_H_

#include "stm32f4xx_hal.h"
#include "ssd1306.h"

#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	I2C_HandleTypeDef *hi2c;
} Display_StructTypeDef;

__weak void Display_ErrorHandler(const char *, uint16_t);

void Display_Init(Display_StructTypeDef *, I2C_HandleTypeDef *);
void Display_Update(Display_StructTypeDef *);

void Display_Clear(Display_StructTypeDef *);
void Display_DrawBitmap(Display_StructTypeDef *, uint16_t, uint16_t, const uint8_t*, uint16_t, uint16_t);
void Display_DrawLine(Display_StructTypeDef *, uint16_t, uint16_t, uint16_t, uint16_t);
void Display_DrawText(Display_StructTypeDef *, uint8_t, uint8_t, const char *, ...);
void Display_InvertColors(Display_StructTypeDef *, uint8_t, uint8_t, uint8_t, uint8_t);

#endif /* SNEAK100_ABSTRACTION_LAYER_INC_DISPLAY_H_ */
