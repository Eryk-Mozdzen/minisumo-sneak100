/*
 * sneak100_display.h
 *
 *  Created on: Aug 21, 2021
 *      Author: ermoz
 */

#ifndef SNEAK100_HARDWARE_INC_SNEAK100_DISPLAY_H_
#define SNEAK100_HARDWARE_INC_SNEAK100_DISPLAY_H_

#include "i2c.h"
#include "display.h"
#include <stdio.h>

typedef struct {
	float battery_voltage;
	float temperature;
} Sneak100_GUI_StructTypeDef;

extern Display_StructTypeDef oled;
extern Sneak100_GUI_StructTypeDef gui;

void Display_ErrorHandler();

void SNEAK100_Display_Init();
void SNEAK100_Display_Render();

#endif /* SNEAK100_HARDWARE_INC_SNEAK100_DISPLAY_H_ */
