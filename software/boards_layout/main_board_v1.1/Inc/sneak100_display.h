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
#include <stdlib.h>
#include <string.h>

#include "finite_state_machine.h"

#define DISPLAY_LINE_1	12
#define DISPLAY_LINE_2	22
#define DISPLAY_LINE_3	32
#define DISPLAY_LINE_4	42

typedef enum {
	GUI_STATE_DESKTOP,
	GUI_STATE_VIEW_MOTORS,
	GUI_STATE_VIEW_LINE,
	GUI_STATE_VIEW_PROXIMITY,
	GUI_STATE_VIEW_OTHERS,
	GUI_STATE_SETTINGS,
	GUI_STATE_CREDITS
} GUI_States_EnumtypeDef;

typedef enum {
	BUTTON_L,
	BUTTON_C,
	BUTTON_R
} GUI_Button_EnumTypeDef;

typedef struct {
	uint8_t pressed;
	uint8_t changed;
} GUI_ButtonState_StructTypeDef;

typedef struct {
	uint16_t position[4];
	float velocity[4];
	uint16_t line[4];
	uint16_t line_threshold[4];
	uint8_t line_polarity[4];
	uint8_t line_state;
	uint8_t proximity[4];

	float temperature;
	float battery;
} RobotState_StructTypeDef;

typedef struct {
	FiniteStateMachine_t fsm;
	GUI_ButtonState_StructTypeDef buttons[3];
	Display_StructTypeDef display;

	RobotState_StructTypeDef data;
} Sneak100_GUI_StructTypeDef;

extern Sneak100_GUI_StructTypeDef gui;

void SNEAK100_Display_Init();
void SNEAK100_Display_Update();

#endif /* SNEAK100_HARDWARE_INC_SNEAK100_DISPLAY_H_ */
