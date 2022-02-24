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
	GUI_STATE_MOTORS,
	GUI_STATE_LINE,
	GUI_STATE_PROXIMITY,
	GUI_STATE_OTHERS,
	GUI_STATE_SETTINGS,
	GUI_STATE_FIGHT,
	GUI_STATE_INFO,
	GUI_STATE_CREDITS
} GUI_State_t;

typedef struct {
	FiniteStateMachine_t fsm;
	Sneak100_Core_t *sneak100_ptr;

	uint8_t menu_selected;
	uint8_t update_request;
} Sneak100_GUI_t;

#endif
