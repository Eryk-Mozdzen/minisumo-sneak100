/*
 * sneak100_display.c
 *
 *  Created on: Aug 21, 2021
 *      Author: ermoz
 */

#include <gui.h>
#include "sprites.h"

Sneak100_GUI_t gui;

static void GUI_ReadInputs();

static void GUI_Render_Menu(void *);
static void GUI_Render_ViewMotors(void *);
static void GUI_Render_ViewLine(void *);
static void GUI_Render_ViewProximity(void *);
static void GUI_Render_ViewOthers(void *);
static void GUI_Render_Settings(void *);
static void GUI_Render_Info(void *);
static void GUI_Render_Credits(void *);

static void GUI_DrawHeader(const char *);
static void GUI_DrawFooter(const char *, const char *, const char *);

static void GUI_WriteSettings(void *);

void SNEAK100_GUI_Init() {
	gui.buttons[BUTTON_L] = (const GUI_ButtonState_StructTypeDef){0};
	gui.buttons[BUTTON_C] = (const GUI_ButtonState_StructTypeDef){0};
	gui.buttons[BUTTON_R] = (const GUI_ButtonState_StructTypeDef){0};

	gui.display = &sneak100.display;
	gui.state = &sneak100.state;
	gui.settings = &sneak100.settings;

	FiniteStateMachine_Init(&gui.fsm, &gui);

	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_MENU,			NULL, &GUI_Render_Menu,			NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_VIEW_MOTORS,		NULL, &GUI_Render_ViewMotors,	NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_VIEW_LINE,		NULL, &GUI_Render_ViewLine,		NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_VIEW_PROXIMITY,	NULL, &GUI_Render_ViewProximity,NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_VIEW_OTHERS,		NULL, &GUI_Render_ViewOthers,	NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_SETTINGS,		NULL, &GUI_Render_Settings,		&GUI_WriteSettings);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_INFO,			NULL, &GUI_Render_Info,			NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_CREDITS,			NULL, &GUI_Render_Credits,		NULL);

	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_MENU,			GUI_STATE_VIEW_MOTORS,		0, NULL, &__GUI_Menu_Option0_SelectEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_MENU,			GUI_STATE_SETTINGS,			0, NULL, &__GUI_Menu_Option1_SelectEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_MENU,			GUI_STATE_TEST,				0, NULL, &__GUI_Menu_Option2_SelectEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_MENU,			GUI_STATE_FIGHT,			0, NULL, &__GUI_Menu_Option3_SelectEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_MENU,			GUI_STATE_INFO,				0, NULL, &__GUI_Menu_Option6_SelectEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_MENU,			GUI_STATE_CREDITS,			0, NULL, &__GUI_Menu_Option7_SelectEvent);

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
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_INFO, 			GUI_STATE_MENU,				0, NULL, &__Button_R_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_CREDITS, 		GUI_STATE_MENU,				0, NULL, &__Button_R_ClickEvent);

	FiniteStateMachine_Start(&gui.fsm, GUI_STATE_MENU);
}

void SNEAK100_GUI_Update() {
	GUI_ReadInputs();

	FiniteStateMachine_Update(&gui.fsm);
	FiniteStateMachine_Execute(&gui.fsm);
}

void GUI_ReadInputs() {
	gui.buttons[BUTTON_L].changed = gui.buttons[BUTTON_L].pressed ^ !HAL_GPIO_ReadPin(USER_BUTTON_L_GPIO_Port, USER_BUTTON_L_Pin);
	gui.buttons[BUTTON_C].changed = gui.buttons[BUTTON_C].pressed ^ !HAL_GPIO_ReadPin(USER_BUTTON_C_GPIO_Port, USER_BUTTON_C_Pin);
	gui.buttons[BUTTON_R].changed = gui.buttons[BUTTON_R].pressed ^ !HAL_GPIO_ReadPin(USER_BUTTON_R_GPIO_Port, USER_BUTTON_R_Pin);

	gui.buttons[BUTTON_L].pressed = !HAL_GPIO_ReadPin(USER_BUTTON_L_GPIO_Port, USER_BUTTON_L_Pin);
	gui.buttons[BUTTON_C].pressed = !HAL_GPIO_ReadPin(USER_BUTTON_C_GPIO_Port, USER_BUTTON_C_Pin);
	gui.buttons[BUTTON_R].pressed = !HAL_GPIO_ReadPin(USER_BUTTON_R_GPIO_Port, USER_BUTTON_R_Pin);
}

void GUI_DrawHeader(const char *title) {
	Display_DrawText(gui.display, 0, 0, "%s       ", title);
	Display_DrawLine(gui.display, 0, 10, 127, 10);
}

void GUI_DrawFooter(const char *action_l, const char *action_c, const char *action_r) {
	char bot_bar[32] = {0};

	sprintf(bot_bar, "%.4s              ", action_l);
	sprintf(bot_bar + 7, "%.4s       ", action_c);
	sprintf(bot_bar + 14, "%.4s", action_r);

	Display_DrawText(gui.display, 0, 53, "%s", bot_bar);
	Display_DrawLine(gui.display, 0, 52, 127, 52);
}

void GUI_Render_Menu(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	Display_Clear(gui_ptr->display);

	Display_DrawText(gui_ptr->display, GUI_MENU_COL_0,  GUI_MENU_ROW_0 + 2, "view");
	Display_DrawText(gui_ptr->display, GUI_MENU_COL_0,  GUI_MENU_ROW_1 + 2, "settings");
	Display_DrawText(gui_ptr->display, GUI_MENU_COL_0,  GUI_MENU_ROW_2 + 2, "test");
	Display_DrawText(gui_ptr->display, GUI_MENU_COL_0,  GUI_MENU_ROW_3 + 2, "fight");

	Display_DrawText(gui_ptr->display, GUI_MENU_COL_1,  GUI_MENU_ROW_0 + 2, "    ");
	Display_DrawText(gui_ptr->display, GUI_MENU_COL_1,  GUI_MENU_ROW_1 + 2, "    ");
	Display_DrawText(gui_ptr->display, GUI_MENU_COL_1,  GUI_MENU_ROW_2 + 2, "info");
	Display_DrawText(gui_ptr->display, GUI_MENU_COL_1,  GUI_MENU_ROW_3 + 2, "credits");

	GUI_DrawFooter("up", "down", "sel");

	Display_InvertColors(gui_ptr->display, (gui_ptr->menu_selected<4) ? GUI_MENU_COL_0 : GUI_MENU_COL_1, (gui_ptr->menu_selected%4)*13, 64, 13);

	if(gui_ptr->buttons[BUTTON_L].pressed && gui_ptr->buttons[BUTTON_L].changed)
		gui_ptr->menu_selected--;
	if(gui_ptr->buttons[BUTTON_C].pressed && gui_ptr->buttons[BUTTON_C].changed)
		gui_ptr->menu_selected++;

	gui_ptr->menu_selected %=8;

	Display_Update(gui_ptr->display);
}

void GUI_Render_ViewMotors(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	Display_Clear(gui_ptr->display);

	GUI_DrawHeader("Motors");
	GUI_DrawFooter("next", "prev", "esc");

	Display_DrawText(gui_ptr->display, 0,  DISPLAY_LINE_1, "LF: %u", gui_ptr->state->motor[0].position_raw);
	Display_DrawText(gui_ptr->display, 0,  DISPLAY_LINE_2, "LB: %u", gui_ptr->state->motor[1].position_raw);
	Display_DrawText(gui_ptr->display, 0,  DISPLAY_LINE_3, "RF: %u", gui_ptr->state->motor[2].position_raw);
	Display_DrawText(gui_ptr->display, 0,  DISPLAY_LINE_4, "RB: %u", gui_ptr->state->motor[3].position_raw);

	Display_DrawText(gui_ptr->display, 72,  DISPLAY_LINE_1, "%+.2f", gui_ptr->state->motor[0].velocity);
	Display_DrawText(gui_ptr->display, 72,  DISPLAY_LINE_2, "%+.2f", gui_ptr->state->motor[1].velocity);
	Display_DrawText(gui_ptr->display, 72,  DISPLAY_LINE_3, "%+.2f", gui_ptr->state->motor[2].velocity);
	Display_DrawText(gui_ptr->display, 72,  DISPLAY_LINE_4, "%+.2f", gui_ptr->state->motor[3].velocity);

	Display_Update(gui_ptr->display);
}

void GUI_Render_ViewLine(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	Display_Clear(gui_ptr->display);

	GUI_DrawHeader("Line");
	GUI_DrawFooter("next", "prev", "esc");

	Display_DrawText(gui_ptr->display, 0,  DISPLAY_LINE_1, "LL: %u", gui_ptr->state->line[0].value);
	Display_DrawText(gui_ptr->display, 0,  DISPLAY_LINE_2, "LM: %u", gui_ptr->state->line[1].value);
	Display_DrawText(gui_ptr->display, 0,  DISPLAY_LINE_3, "RM: %u", gui_ptr->state->line[2].value);
	Display_DrawText(gui_ptr->display, 0,  DISPLAY_LINE_4, "RR: %u", gui_ptr->state->line[3].value);

	Display_DrawText(gui_ptr->display, 64,  DISPLAY_LINE_1, "%u %c %u", gui_ptr->state->line[0].threshold, gui_ptr->state->line[0].polarity ? 'W' : 'B', gui_ptr->state->line[0].state);
	Display_DrawText(gui_ptr->display, 64,  DISPLAY_LINE_2, "%u %c %u", gui_ptr->state->line[1].threshold, gui_ptr->state->line[1].polarity ? 'W' : 'B', gui_ptr->state->line[1].state);
	Display_DrawText(gui_ptr->display, 64,  DISPLAY_LINE_3, "%u %c %u", gui_ptr->state->line[2].threshold, gui_ptr->state->line[2].polarity ? 'W' : 'B', gui_ptr->state->line[2].state);
	Display_DrawText(gui_ptr->display, 64,  DISPLAY_LINE_4, "%u %c %u", gui_ptr->state->line[3].threshold, gui_ptr->state->line[3].polarity ? 'W' : 'B', gui_ptr->state->line[3].state);

	Display_Update(gui_ptr->display);
}

void GUI_Render_ViewProximity(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	Display_Clear(gui_ptr->display);

	GUI_DrawHeader("Proximity");
	GUI_DrawFooter("next", "prev", "esc");

	Display_DrawText(gui_ptr->display, 0,  DISPLAY_LINE_1, "LL: %u", gui_ptr->state->proximity[0]);
	Display_DrawText(gui_ptr->display, 0,  DISPLAY_LINE_2, "FL: %u", gui_ptr->state->proximity[1]);
	Display_DrawText(gui_ptr->display, 0,  DISPLAY_LINE_3, "FR: %u", gui_ptr->state->proximity[2]);
	Display_DrawText(gui_ptr->display, 0,  DISPLAY_LINE_4, "RR: %u", gui_ptr->state->proximity[3]);

	Display_Update(gui_ptr->display);
}

void GUI_Render_ViewOthers(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	Display_Clear(gui_ptr->display);

	GUI_DrawHeader("Others");
	GUI_DrawFooter("next", "prev", "esc");

	Display_DrawText(gui_ptr->display, 0,  DISPLAY_LINE_1, "Temp: %.0f*C", gui_ptr->state->temperature);
	Display_DrawText(gui_ptr->display, 0,  DISPLAY_LINE_2, "Batt: %.2fV", gui_ptr->state->battery);
	Display_DrawText(gui_ptr->display, 0,  DISPLAY_LINE_3, "RC5:  %u 0x%02X 0x%02X",
			gui_ptr->state->rc5.message.toggle, gui_ptr->state->rc5.message.address, gui_ptr->state->rc5.message.command);
	Display_DrawText(gui_ptr->display, 0,  DISPLAY_LINE_4, "HC05: ");

	Display_Update(gui_ptr->display);
}

void GUI_Render_Settings(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	Display_Clear(gui_ptr->display);

	GUI_DrawHeader("Settings");
	GUI_DrawFooter("opt", "down", "save");

	const char *mode[] = {"module", "button", "RC RC5", "RC BT"};
	const char *dyhlo[] = {"black", "white", "auto"};
	const char *strategy[] = {"agressive", "defense", "passive"};

	Display_DrawText(gui_ptr->display, 0,  DISPLAY_LINE_1, "mode : %s", mode[gui_ptr->settings->mode]);
	Display_DrawText(gui_ptr->display, 0,  DISPLAY_LINE_2, "dyhlo: %s", dyhlo[gui_ptr->settings->dyhlo]);
	Display_DrawText(gui_ptr->display, 0,  DISPLAY_LINE_3, "strat: %s", strategy[gui_ptr->settings->strategy]);

	Display_InvertColors(gui_ptr->display, 0, DISPLAY_LINE_1 + (DISPLAY_LINE_2 - DISPLAY_LINE_1)*gui_ptr->menu_selected - 1, 128, DISPLAY_LINE_2 - DISPLAY_LINE_1 + 1);

	if(gui_ptr->buttons[BUTTON_C].pressed && gui_ptr->buttons[BUTTON_C].changed)
		gui_ptr->menu_selected++;

	if(gui_ptr->buttons[BUTTON_L].pressed && gui_ptr->buttons[BUTTON_L].changed && gui_ptr->menu_selected==0) {
		gui_ptr->settings->mode++;
		gui_ptr->settings->mode %=SETTINGS_MODE_NUM;
	} else if(gui_ptr->buttons[BUTTON_L].pressed && gui_ptr->buttons[BUTTON_L].changed && gui_ptr->menu_selected==1) {
		gui_ptr->settings->dyhlo++;
		gui_ptr->settings->dyhlo %=SETTINGS_DYHLO_NUM;
	} else if(gui_ptr->buttons[BUTTON_L].pressed && gui_ptr->buttons[BUTTON_L].changed && gui_ptr->menu_selected==2) {
		gui_ptr->settings->strategy++;
		gui_ptr->settings->strategy %=SETTINGS_STRATEGY_NUM;
	}

	gui_ptr->menu_selected %=3;

	Display_Update(gui_ptr->display);
}

void GUI_Render_Info(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	Display_Clear(gui_ptr->display);

	GUI_DrawHeader("Info");
	GUI_DrawFooter("", "", "esc");

	Display_DrawText(gui_ptr->display, 0,  DISPLAY_LINE_1, "build: %s", __DATE__);
	Display_DrawText(gui_ptr->display, 0,  DISPLAY_LINE_2, "pass: %s", "");

	Display_Update(gui_ptr->display);
}

void GUI_Render_Credits(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	Display_Clear(gui_ptr->display);

	Display_DrawBitmap(gui_ptr->display, 0, 0, bitmap_sneak100_128_64, 128, 64);

	Display_DrawText(gui_ptr->display, 0, 0, "Minisumo Sneak100");
	Display_DrawText(gui_ptr->display, 0, 53, "by E.Mozdzen 2022");

	Display_Update(gui_ptr->display);
}

void GUI_WriteSettings(void *data) {
	SNEAK100_Core_WriteSettings();
}
