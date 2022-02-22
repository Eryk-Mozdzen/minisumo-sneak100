/*
 * sneak100_display.c
 *
 *  Created on: Aug 21, 2021
 *      Author: ermoz
 */

#include "gui.h"

Sneak100_GUI_t gui;

static void GUI_ReadInputs();
static void GUI_WriteSettings(void *);

void SNEAK100_GUI_Init() {
	gui.buttons[BUTTON_L] = (const GUI_ButtonState_StructTypeDef){0};
	gui.buttons[BUTTON_C] = (const GUI_ButtonState_StructTypeDef){0};
	gui.buttons[BUTTON_R] = (const GUI_ButtonState_StructTypeDef){0};

	gui.update_request = 0;

	gui.sneak100_ptr = &sneak100;

	FiniteStateMachine_Init(&gui.fsm, &gui);

	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_MENU,			NULL,				&GUI_Render_Menu,			NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_VIEW_MOTORS,		NULL,				&GUI_Render_ViewMotors,		NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_VIEW_LINE,		NULL,				&GUI_Render_ViewLine,		NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_VIEW_PROXIMITY,	NULL,				&GUI_Render_ViewProximity,	NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_VIEW_OTHERS,		NULL,				&GUI_Render_ViewOthers,		NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_SETTINGS,		NULL,				&GUI_Render_Settings,		&GUI_WriteSettings);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_FIGHT,			GUI_Fight_Enter,	&GUI_Render_Fight,			NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_INFO,			NULL,				&GUI_Render_Info,			NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_CREDITS,			NULL,				&GUI_Render_Credits,		NULL);

	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_MENU,			GUI_STATE_VIEW_MOTORS,		0, NULL, &__GUI_Menu_Option0_SelectEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_MENU,			GUI_STATE_SETTINGS,			0, NULL, &__GUI_Menu_Option1_SelectEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_MENU,			GUI_STATE_FIGHT,			0, NULL, &__GUI_Menu_Option2_SelectEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_MENU,			GUI_STATE_INFO,				0, NULL, &__GUI_Menu_Option4_SelectEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_MENU,			GUI_STATE_CREDITS,			0, NULL, &__GUI_Menu_Option5_SelectEvent);

	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_VIEW_MOTORS,	GUI_STATE_VIEW_LINE,		0, NULL, &__Button_L_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_VIEW_LINE,		GUI_STATE_VIEW_PROXIMITY,	0, NULL, &__Button_L_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_VIEW_PROXIMITY,	GUI_STATE_VIEW_OTHERS,		0, NULL, &__Button_L_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_VIEW_OTHERS,	GUI_STATE_VIEW_MOTORS,		0, NULL, &__Button_L_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_VIEW_MOTORS,	GUI_STATE_VIEW_OTHERS,		0, NULL, &__Button_C_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_VIEW_OTHERS,	GUI_STATE_VIEW_PROXIMITY,	0, NULL, &__Button_C_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_VIEW_PROXIMITY,	GUI_STATE_VIEW_LINE,		0, NULL, &__Button_C_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_VIEW_LINE,		GUI_STATE_VIEW_MOTORS,		0, NULL, &__Button_C_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_VIEW_MOTORS,	GUI_STATE_MENU,				0, NULL, &__Button_R_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_VIEW_LINE,		GUI_STATE_MENU,				0, NULL, &__Button_R_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_VIEW_PROXIMITY,	GUI_STATE_MENU,				0, NULL, &__Button_R_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_VIEW_OTHERS,	GUI_STATE_MENU,				0, NULL, &__Button_R_ClickEvent);

	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_SETTINGS, 		GUI_STATE_MENU,				0, NULL, &__Button_R_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_FIGHT, 			GUI_STATE_MENU,				0, NULL, &__Button_R_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_INFO, 			GUI_STATE_MENU,				0, NULL, &__Button_R_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_CREDITS, 		GUI_STATE_MENU,				0, NULL, &__Button_R_ClickEvent);

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

void GUI_WriteSettings(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	Memory_Write(&gui_ptr->sneak100_ptr->memory, MEMORY_SETTINGS_ADDRESS, &gui_ptr->sneak100_ptr->settings, sizeof(RobotSettings_t));
}
