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

#include "core.h"
#include "gui_events.h"
#include "finite_state_machine.h"

#define DISPLAY_LINE_1	12
#define DISPLAY_LINE_2	22
#define DISPLAY_LINE_3	32
#define DISPLAY_LINE_4	42

#define GUI_MENU_ROW_0	0
#define GUI_MENU_ROW_1	13
#define GUI_MENU_ROW_2	26
#define GUI_MENU_ROW_3	39

#define GUI_MENU_COL_0	0
#define GUI_MENU_COL_1	64

typedef enum {
	GUI_STATE_MENU,

	GUI_STATE_VIEW_MOTORS,
	GUI_STATE_VIEW_LINE,
	GUI_STATE_VIEW_PROXIMITY,
	GUI_STATE_VIEW_OTHERS,

	GUI_STATE_SETTINGS,
	GUI_STATE_TEST,
	GUI_STATE_FIGHT,

	GUI_STATE_INFO,
	GUI_STATE_CREDITS
} GUI_States_EnumtypeDef;

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

	uint8_t rc5_toggle;
	uint8_t rc5_address;
	uint8_t rc5_command;
} RobotState_StructTypeDef;

typedef struct {
	FiniteStateMachine_t fsm;
	GUI_ButtonState_StructTypeDef buttons[3];
	Display_StructTypeDef *display;
	Memory_StryctTypeDef *memory;

	uint8_t menu_selected;

	RobotState_StructTypeDef data;
	RobotSettings_StructTypeDef settings;
} Sneak100_GUI_StructTypeDef;

extern Sneak100_GUI_StructTypeDef gui;

void SNEAK100_Display_Init();
void SNEAK100_Display_Update();

#endif
