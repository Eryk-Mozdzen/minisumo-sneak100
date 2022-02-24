/*
 * sneak100_display.c
 *
 *  Created on: Aug 21, 2021
 *      Author: ermoz
 */

#include "gui.h"

Sneak100_GUI_t gui;

static void GUI_ReadInputs();

void SNEAK100_GUI_Init() {
	gui.buttons[BUTTON_L] = (const GUI_ButtonState_t){0};
	gui.buttons[BUTTON_C] = (const GUI_ButtonState_t){0};
	gui.buttons[BUTTON_R] = (const GUI_ButtonState_t){0};
	gui.update_request = 0;

	gui.sneak100_ptr = &sneak100;

	FiniteStateMachine_Init(&gui.fsm, &gui);

	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_MENU,		NULL,				&__GUI_Menu_Execute,		NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_MOTORS,		NULL,				&__GUI_Motors_Execute,		NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_LINE,		NULL,				&__GUI_Line_Execute,		NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_PROXIMITY,	NULL,				&__GUI_Proximity_Execute,	NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_OTHERS,		NULL,				&__GUI_Others_Execute,		NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_SETTINGS,	NULL,				&__GUI_Settings_Execute,	&__GUI_Settings_Exit);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_FIGHT,		__GUI_Fight_Enter,	&__GUI_Fight_Execute,		NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_INFO,		NULL,				&__GUI_Info_Execute,		NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_CREDITS,		NULL,				&__GUI_Credits_Execute,		NULL);

	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_MENU,		GUI_STATE_MOTORS,		0, NULL, &__GUI_MenuOption0_Select_Event);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_MENU,		GUI_STATE_SETTINGS,		0, NULL, &__GUI_MenuOption1_Select_Event);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_MENU,		GUI_STATE_FIGHT,		0, NULL, &__GUI_MenuOption2_Select_Event);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_MENU,		GUI_STATE_INFO,			0, NULL, &__GUI_MenuOption4_Select_Event);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_MENU,		GUI_STATE_CREDITS,		0, NULL, &__GUI_MenuOption5_Select_Event);

	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_MOTORS,		GUI_STATE_LINE,			0, NULL, &__GUI_ButtonL_Click_Event);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_LINE,		GUI_STATE_PROXIMITY,	0, NULL, &__GUI_ButtonL_Click_Event);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_PROXIMITY,	GUI_STATE_OTHERS,		0, NULL, &__GUI_ButtonL_Click_Event);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_OTHERS,		GUI_STATE_MOTORS,		0, NULL, &__GUI_ButtonL_Click_Event);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_MOTORS,		GUI_STATE_OTHERS,		0, NULL, &__GUI_ButtonC_Click_Event);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_OTHERS,		GUI_STATE_PROXIMITY,	0, NULL, &__GUI_ButtonC_Click_Event);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_PROXIMITY,	GUI_STATE_LINE,			0, NULL, &__GUI_ButtonC_Click_Event);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_LINE,		GUI_STATE_MOTORS,		0, NULL, &__GUI_ButtonC_Click_Event);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_MOTORS,		GUI_STATE_MENU,			0, NULL, &__GUI_ButtonR_Click_Event);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_LINE,		GUI_STATE_MENU,			0, NULL, &__GUI_ButtonR_Click_Event);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_PROXIMITY,	GUI_STATE_MENU,			0, NULL, &__GUI_ButtonR_Click_Event);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_OTHERS,		GUI_STATE_MENU,			0, NULL, &__GUI_ButtonR_Click_Event);

	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_SETTINGS, 	GUI_STATE_MENU,			0, NULL, &__GUI_ButtonR_Click_Event);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_FIGHT, 		GUI_STATE_MENU,			0, NULL, &__GUI_ButtonR_Click_Event);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_INFO, 		GUI_STATE_MENU,			0, NULL, &__GUI_ButtonR_Click_Event);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_CREDITS, 	GUI_STATE_MENU,			0, NULL, &__GUI_ButtonR_Click_Event);

	FiniteStateMachine_Start(&gui.fsm, GUI_STATE_MENU);
}

void SNEAK100_GUI_Update() {
	if(!gui.update_request)
		return;

	GUI_ReadInputs();

	FiniteStateMachine_Update(&gui.fsm);
	FiniteStateMachine_Execute(&gui.fsm);

	gui.update_request = 0;
}

void SNEAK100_GUI_UpdateRequest() {
	gui.update_request = 1;
}

void GUI_ReadInputs() {
	gui.buttons[BUTTON_L].changed = gui.buttons[BUTTON_L].pressed ^ !HAL_GPIO_ReadPin(USER_BUTTON_L_GPIO_Port, USER_BUTTON_L_Pin);
	gui.buttons[BUTTON_C].changed = gui.buttons[BUTTON_C].pressed ^ !HAL_GPIO_ReadPin(USER_BUTTON_C_GPIO_Port, USER_BUTTON_C_Pin);
	gui.buttons[BUTTON_R].changed = gui.buttons[BUTTON_R].pressed ^ !HAL_GPIO_ReadPin(USER_BUTTON_R_GPIO_Port, USER_BUTTON_R_Pin);

	gui.buttons[BUTTON_L].pressed = !HAL_GPIO_ReadPin(USER_BUTTON_L_GPIO_Port, USER_BUTTON_L_Pin);
	gui.buttons[BUTTON_C].pressed = !HAL_GPIO_ReadPin(USER_BUTTON_C_GPIO_Port, USER_BUTTON_C_Pin);
	gui.buttons[BUTTON_R].pressed = !HAL_GPIO_ReadPin(USER_BUTTON_R_GPIO_Port, USER_BUTTON_R_Pin);
}
