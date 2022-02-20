/*
 * sneak100_display.h
 *
 *  Created on: Aug 21, 2021
 *      Author: ermoz
 */

#ifndef SNEAK100_HARDWARE_INC_SNEAK100_DISPLAY_H_
#define SNEAK100_HARDWARE_INC_SNEAK100_DISPLAY_H_

#include <math.h>
#include <stdio.h>

#include "core.h"
#include "finite_state_machine.h"

#include "gui_def.h"
#include "gui_conf.h"
#include "gui_events.h"

typedef struct {
	FiniteStateMachine_t fsm;
	GUI_ButtonState_StructTypeDef buttons[3];
	Display_t *display;

	uint8_t menu_selected;
	uint8_t update_request;

	RobotState_t *state;
	RobotSettings_t *settings;
} Sneak100_GUI_t;

extern Sneak100_GUI_t gui;

void SNEAK100_GUI_Init();
void SNEAK100_GUI_Update();
void SNEAK100_GUI_UpdateRequest();

#endif
