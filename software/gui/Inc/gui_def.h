/*
 * gui_def.h
 *
 *  Created on: Feb 14, 2022
 *      Author: emozdzen
 */

#ifndef INC_GUI_DEF_H_
#define INC_GUI_DEF_H_

#include "core_def.h"
#include "finite_state_machine.h"

typedef enum {
	GUI_STATE_MENU,

	GUI_STATE_VIEW_MOTORS,
	GUI_STATE_VIEW_LINE,
	GUI_STATE_VIEW_PROXIMITY,
	GUI_STATE_VIEW_OTHERS,

	GUI_STATE_SETTINGS,
	GUI_STATE_FIGHT,

	GUI_STATE_INFO,
	GUI_STATE_CREDITS
} GUI_States_t;

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
	FiniteStateMachine_t fsm;
	GUI_ButtonState_StructTypeDef buttons[3];
	Sneak100_t *sneak100_ptr;

	uint8_t menu_selected;
	uint8_t update_request;
} Sneak100_GUI_t;

#endif
