/*
 * sneak100_display.c
 *
 *  Created on: Aug 21, 2021
 *      Author: ermoz
 */

#include "sneak100_display.h"
#include "sprites.h"

Sneak100_GUI_StructTypeDef gui;

static void SNEAK100_Display_ReadInputs();

static uint8_t SNEAK100_Button_L_ClickEvent(void *);
static uint8_t SNEAK100_Button_C_ClickEvent(void *);
static uint8_t SNEAK100_Button_R_ClickEvent(void *);

static void SNEAK100_Display_Render_Desktop(void *);
static void SNEAK100_Display_Render_ViewMotors(void *);
static void SNEAK100_Display_Render_ViewLine(void *);
static void SNEAK100_Display_Render_ViewProximity(void *);
static void SNEAK100_Display_Render_ViewOthers(void *);
static void SNEAK100_Display_Render_Settings(void *);
static void SNEAK100_Display_Render_Credits(void *);

static void __Display_DrawHeader(const char *);
static void __Display_DrawFooter(const char *, const char *, const char *);

void SNEAK100_Display_Init() {
	gui.buttons[BUTTON_L] = (const GUI_ButtonState_StructTypeDef){0, 0};
	gui.buttons[BUTTON_C] = (const GUI_ButtonState_StructTypeDef){0, 0};
	gui.buttons[BUTTON_R] = (const GUI_ButtonState_StructTypeDef){0, 0};

	Display_Init(&gui.display, &hi2c1);

	FiniteStateMachine_Init(&gui.fsm, &gui);

	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_DESKTOP,			NULL, &SNEAK100_Display_Render_Desktop,			NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_VIEW_MOTORS,		NULL, &SNEAK100_Display_Render_ViewMotors,		NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_VIEW_LINE,		NULL, &SNEAK100_Display_Render_ViewLine,		NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_VIEW_PROXIMITY,	NULL, &SNEAK100_Display_Render_ViewProximity,	NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_VIEW_OTHERS,		NULL, &SNEAK100_Display_Render_ViewOthers,		NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_SETTINGS,		NULL, &SNEAK100_Display_Render_Settings,		NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_CREDITS,			NULL, &SNEAK100_Display_Render_Credits,		NULL);

	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_DESKTOP,		GUI_STATE_VIEW_MOTORS,		0, NULL, &SNEAK100_Button_L_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_DESKTOP,		GUI_STATE_SETTINGS,			0, NULL, &SNEAK100_Button_C_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_DESKTOP,		GUI_STATE_CREDITS,			0, NULL, &SNEAK100_Button_R_ClickEvent);

	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_VIEW_MOTORS,	GUI_STATE_VIEW_LINE,		0, NULL, &SNEAK100_Button_L_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_VIEW_LINE,		GUI_STATE_VIEW_PROXIMITY,	0, NULL, &SNEAK100_Button_L_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_VIEW_PROXIMITY,	GUI_STATE_VIEW_OTHERS,		0, NULL, &SNEAK100_Button_L_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_VIEW_OTHERS,	GUI_STATE_VIEW_MOTORS,		0, NULL, &SNEAK100_Button_L_ClickEvent);

	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_VIEW_MOTORS,	GUI_STATE_VIEW_OTHERS,		0, NULL, &SNEAK100_Button_C_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_VIEW_OTHERS,	GUI_STATE_VIEW_PROXIMITY,	0, NULL, &SNEAK100_Button_C_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_VIEW_PROXIMITY,	GUI_STATE_VIEW_LINE,		0, NULL, &SNEAK100_Button_C_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_VIEW_LINE,		GUI_STATE_VIEW_MOTORS,		0, NULL, &SNEAK100_Button_C_ClickEvent);

	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_VIEW_MOTORS,	GUI_STATE_DESKTOP,			0, NULL, &SNEAK100_Button_R_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_VIEW_LINE,		GUI_STATE_DESKTOP,			0, NULL, &SNEAK100_Button_R_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_VIEW_PROXIMITY,	GUI_STATE_DESKTOP,			0, NULL, &SNEAK100_Button_R_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_VIEW_OTHERS,	GUI_STATE_DESKTOP,			0, NULL, &SNEAK100_Button_R_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_SETTINGS, 		GUI_STATE_DESKTOP,			0, NULL, &SNEAK100_Button_R_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_CREDITS, 		GUI_STATE_DESKTOP,			0, NULL, &SNEAK100_Button_R_ClickEvent);

	FiniteStateMachine_Start(&gui.fsm, GUI_STATE_DESKTOP);
}

void SNEAK100_Display_Update() {
	SNEAK100_Display_ReadInputs();

	FiniteStateMachine_Update(&gui.fsm);
	FiniteStateMachine_Execute(&gui.fsm);
}

void SNEAK100_Display_ReadInputs() {
	gui.buttons[BUTTON_L].changed = gui.buttons[BUTTON_L].pressed ^ !HAL_GPIO_ReadPin(USER_BUTTON_L_GPIO_Port, USER_BUTTON_L_Pin);
	gui.buttons[BUTTON_C].changed = gui.buttons[BUTTON_C].pressed ^ !HAL_GPIO_ReadPin(USER_BUTTON_C_GPIO_Port, USER_BUTTON_C_Pin);
	gui.buttons[BUTTON_R].changed = gui.buttons[BUTTON_R].pressed ^ !HAL_GPIO_ReadPin(USER_BUTTON_R_GPIO_Port, USER_BUTTON_R_Pin);

	gui.buttons[BUTTON_L].pressed = !HAL_GPIO_ReadPin(USER_BUTTON_L_GPIO_Port, USER_BUTTON_L_Pin);
	gui.buttons[BUTTON_C].pressed = !HAL_GPIO_ReadPin(USER_BUTTON_C_GPIO_Port, USER_BUTTON_C_Pin);
	gui.buttons[BUTTON_R].pressed = !HAL_GPIO_ReadPin(USER_BUTTON_R_GPIO_Port, USER_BUTTON_R_Pin);
}

void __Display_DrawHeader(const char *title) {
	Display_DrawText(&gui.display, 0, 0, "%s       ", title);
	Display_DrawLine(&gui.display, 0, 10, 127, 10);
}

void __Display_DrawFooter(const char *action_l, const char *action_c, const char *action_r) {
	char bot_bar[32] = {0};

	sprintf(bot_bar, "%.4s              ", action_l);
	sprintf(bot_bar + 7, "%.4s       ", action_c);
	sprintf(bot_bar + 14, "%.4s", action_r);

	Display_DrawText(&gui.display, 0, 53, "%s", bot_bar);
	Display_DrawLine(&gui.display, 0, 52, 127, 52);
}

uint8_t SNEAK100_Button_L_ClickEvent(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	return (gui_ptr->buttons[BUTTON_L].pressed && gui_ptr->buttons[BUTTON_L].changed);
}

uint8_t SNEAK100_Button_C_ClickEvent(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	return (gui_ptr->buttons[BUTTON_C].pressed && gui_ptr->buttons[BUTTON_C].changed);
}

uint8_t SNEAK100_Button_R_ClickEvent(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	return (gui_ptr->buttons[BUTTON_R].pressed && gui_ptr->buttons[BUTTON_R].changed);
}

void SNEAK100_Display_Render_Desktop(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	Display_Clear(&gui_ptr->display);

	Display_DrawBitmap(&gui_ptr->display, 0, 0, bitmap_sneak100_128_64, 128, 64);

	__Display_DrawHeader("Menu");
	__Display_DrawFooter("view", "sett", "func");

	Display_Update(&gui_ptr->display);
}

void SNEAK100_Display_Render_ViewMotors(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	Display_Clear(&gui_ptr->display);

	__Display_DrawHeader("Motors");
	__Display_DrawFooter("next", "prev", "esc");

	Display_DrawText(&gui_ptr->display, 0,  DISPLAY_LINE_1, "LF: %u", gui_ptr->data.position[0]);
	Display_DrawText(&gui_ptr->display, 0,  DISPLAY_LINE_2, "LB: %u", gui_ptr->data.position[1]);
	Display_DrawText(&gui_ptr->display, 0,  DISPLAY_LINE_3, "RF: %u", gui_ptr->data.position[2]);
	Display_DrawText(&gui_ptr->display, 0,  DISPLAY_LINE_4, "RB: %u", gui_ptr->data.position[3]);

	Display_DrawText(&gui_ptr->display, 72,  DISPLAY_LINE_1, "%+.2f", gui_ptr->data.velocity[0]);
	Display_DrawText(&gui_ptr->display, 72,  DISPLAY_LINE_2, "%+.2f", gui_ptr->data.velocity[1]);
	Display_DrawText(&gui_ptr->display, 72,  DISPLAY_LINE_3, "%+.2f", gui_ptr->data.velocity[2]);
	Display_DrawText(&gui_ptr->display, 72,  DISPLAY_LINE_4, "%+.2f", gui_ptr->data.velocity[3]);

	Display_Update(&gui_ptr->display);
}

void SNEAK100_Display_Render_ViewLine(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	Display_Clear(&gui_ptr->display);

	__Display_DrawHeader("Line");
	__Display_DrawFooter("next", "prev", "esc");

	Display_DrawText(&gui_ptr->display, 0,  DISPLAY_LINE_1, "LL: %u", gui_ptr->data.line[0]);
	Display_DrawText(&gui_ptr->display, 0,  DISPLAY_LINE_2, "LM: %u", gui_ptr->data.line[1]);
	Display_DrawText(&gui_ptr->display, 0,  DISPLAY_LINE_3, "RM: %u", gui_ptr->data.line[2]);
	Display_DrawText(&gui_ptr->display, 0,  DISPLAY_LINE_4, "RR: %u", gui_ptr->data.line[3]);

	Display_DrawText(&gui_ptr->display, 64,  DISPLAY_LINE_1, "%u %c %u", gui_ptr->data.line_threshold[0], gui_ptr->data.line_polarity[0] ? 'W' : 'B', (gui_ptr->data.line_state & 0x08)>0);
	Display_DrawText(&gui_ptr->display, 64,  DISPLAY_LINE_2, "%u %c %u", gui_ptr->data.line_threshold[1], gui_ptr->data.line_polarity[1] ? 'W' : 'B', (gui_ptr->data.line_state & 0x04)>0);
	Display_DrawText(&gui_ptr->display, 64,  DISPLAY_LINE_3, "%u %c %u", gui_ptr->data.line_threshold[2], gui_ptr->data.line_polarity[2] ? 'W' : 'B', (gui_ptr->data.line_state & 0x02)>0);
	Display_DrawText(&gui_ptr->display, 64,  DISPLAY_LINE_4, "%u %c %u", gui_ptr->data.line_threshold[3], gui_ptr->data.line_polarity[3] ? 'W' : 'B', (gui_ptr->data.line_state & 0x01)>0);

	Display_Update(&gui_ptr->display);
}

void SNEAK100_Display_Render_ViewProximity(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	Display_Clear(&gui_ptr->display);

	__Display_DrawHeader("Proximity");
	__Display_DrawFooter("next", "prev", "esc");

	Display_DrawText(&gui_ptr->display, 0,  DISPLAY_LINE_1, "LL: %u", gui_ptr->data.proximity[0]);
	Display_DrawText(&gui_ptr->display, 0,  DISPLAY_LINE_2, "FL: %u", gui_ptr->data.proximity[1]);
	Display_DrawText(&gui_ptr->display, 0,  DISPLAY_LINE_3, "FR: %u", gui_ptr->data.proximity[2]);
	Display_DrawText(&gui_ptr->display, 0,  DISPLAY_LINE_4, "RR: %u", gui_ptr->data.proximity[3]);

	Display_Update(&gui_ptr->display);
}

void SNEAK100_Display_Render_ViewOthers(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	Display_Clear(&gui_ptr->display);

	__Display_DrawHeader("Others");
	__Display_DrawFooter("next", "prev", "esc");

	Display_DrawText(&gui_ptr->display, 0,  DISPLAY_LINE_1, "Temp: %.0f*C", gui_ptr->data.temperature);
	Display_DrawText(&gui_ptr->display, 0,  DISPLAY_LINE_2, "Batt: %.2fV", gui_ptr->data.battery);
	Display_DrawText(&gui_ptr->display, 0,  DISPLAY_LINE_3, "RC5:  %u 0x%02X 0x%02X", gui_ptr->data.rc5_toggle, gui_ptr->data.rc5_address, gui_ptr->data.rc5_command);
	Display_DrawText(&gui_ptr->display, 0,  DISPLAY_LINE_4, "HC05: ");

	Display_Update(&gui_ptr->display);
}

void SNEAK100_Display_Render_Settings(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	Display_Clear(&gui_ptr->display);

	__Display_DrawHeader("Settings");
	__Display_DrawFooter("", "", "esc");

	Display_DrawText(&gui_ptr->display, 0,  DISPLAY_LINE_1, "mode: ");
	Display_DrawText(&gui_ptr->display, 0,  DISPLAY_LINE_2, "dyhlo: ");
	Display_DrawText(&gui_ptr->display, 0,  DISPLAY_LINE_3, "strategy: ");
	Display_DrawText(&gui_ptr->display, 0,  DISPLAY_LINE_4, "password: ");

	Display_Update(&gui_ptr->display);
}

void SNEAK100_Display_Render_Credits(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	Display_Clear(&gui_ptr->display);

	Display_DrawBitmap(&gui_ptr->display, 0, 0, bitmap_sneak100_128_64, 128, 64);

	Display_DrawText(&gui_ptr->display, 0, 0, "Minisumo Sneak100");
	Display_DrawText(&gui_ptr->display, 0, 53, "by E.Mozdzen 2022");

	Display_Update(&gui_ptr->display);
}
