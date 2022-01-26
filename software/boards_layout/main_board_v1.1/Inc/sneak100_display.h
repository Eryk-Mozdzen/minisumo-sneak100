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

#include "finite_state_machine.h"

#define BUTTON_CLICK_TIME	100		// ms

typedef enum {
	GUI_STATE_DESKTOP,
	GUI_STATE_OVERVIEW,
	GUI_STATE_SETTINGS
} GUI_States_EnumtypeDef;

typedef enum {
	BUTTON_L,
	BUTTON_C,
	BUTTON_R
} GUI_Button_EnumTypeDef;

typedef struct {
	uint8_t pressed;
	uint8_t chenged;
} GUI_ButtonState_StructTypeDef;

typedef struct {
	FiniteStateMachine_t fsm;
	GUI_ButtonState_StructTypeDef buttons[3];

	float battery_voltage;
	float temperature;
	uint16_t line[4];
	float position[4];
	float velocity[4];
} Sneak100_GUI_StructTypeDef;

extern Display_StructTypeDef oled;
extern Sneak100_GUI_StructTypeDef gui;

HAL_StatusTypeDef ssd1306_Write(uint16_t, void *, uint16_t);
void Display_ErrorHandler(const char *, uint16_t);

void SNEAK100_Display_Init();
void SNEAK100_Display_Update();
void SNEAK100_Display_ReadInputs();

#endif /* SNEAK100_HARDWARE_INC_SNEAK100_DISPLAY_H_ */
