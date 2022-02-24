/*
 * sneak100_display.c
 *
 *  Created on: Aug 21, 2021
 *      Author: ermoz
 */

#include "gui.h"

Sneak100_GUI_t gui;

void SNEAK100_GUI_Init() {
	gui.sneak100_ptr = &sneak100;
	gui.update_request = 0;

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
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_MENU,		GUI_STATE_INFO,			0, NULL, &__GUI_MenuOption6_Select_Event);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_MENU,		GUI_STATE_CREDITS,		0, NULL, &__GUI_MenuOption7_Select_Event);

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

	Button_Update(&gui.sneak100_ptr->buttons[BUTTON_L]);
	Button_Update(&gui.sneak100_ptr->buttons[BUTTON_C]);
	Button_Update(&gui.sneak100_ptr->buttons[BUTTON_R]);

	FiniteStateMachine_Update(&gui.fsm);
	FiniteStateMachine_Execute(&gui.fsm);

	gui.update_request = 0;
}

void SNEAK100_GUI_UpdateRequest() {
	gui.update_request = 1;
}
