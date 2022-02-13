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

static void SNEAK100_Display_Render_Menu(void *);
static void SNEAK100_Display_Render_ViewMotors(void *);
static void SNEAK100_Display_Render_ViewLine(void *);
static void SNEAK100_Display_Render_ViewProximity(void *);
static void SNEAK100_Display_Render_ViewOthers(void *);
static void SNEAK100_Display_Render_Settings(void *);
static void SNEAK100_Display_Render_Info(void *);
static void SNEAK100_Display_Render_Credits(void *);

static void __Display_DrawHeader(const char *);
static void __Display_DrawFooter(const char *, const char *, const char *);

static void __Display_ReadSettings(void *);
static void __Display_WriteSettings(void *);

void SNEAK100_Display_Init() {
	gui.buttons[BUTTON_L] = (const GUI_ButtonState_StructTypeDef){0, 0};
	gui.buttons[BUTTON_C] = (const GUI_ButtonState_StructTypeDef){0, 0};
	gui.buttons[BUTTON_R] = (const GUI_ButtonState_StructTypeDef){0, 0};

	gui.memory = &memory;

	Display_Init(&gui.display, &hi2c1);

	FiniteStateMachine_Init(&gui.fsm, &gui);

	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_MENU,			NULL, &SNEAK100_Display_Render_Menu,			NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_VIEW_MOTORS,		NULL, &SNEAK100_Display_Render_ViewMotors,		NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_VIEW_LINE,		NULL, &SNEAK100_Display_Render_ViewLine,		NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_VIEW_PROXIMITY,	NULL, &SNEAK100_Display_Render_ViewProximity,	NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_VIEW_OTHERS,		NULL, &SNEAK100_Display_Render_ViewOthers,		NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_SETTINGS,		&__Display_ReadSettings, &SNEAK100_Display_Render_Settings,		&__Display_WriteSettings);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_INFO,			NULL, &SNEAK100_Display_Render_Info,			NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_CREDITS,			NULL, &SNEAK100_Display_Render_Credits,			NULL);

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

void SNEAK100_Display_Render_Menu(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	Display_Clear(&gui_ptr->display);

	Display_DrawText(&gui_ptr->display, GUI_MENU_COL_0,  GUI_MENU_ROW_0 + 2, "view");
	Display_DrawText(&gui_ptr->display, GUI_MENU_COL_0,  GUI_MENU_ROW_1 + 2, "settings");
	Display_DrawText(&gui_ptr->display, GUI_MENU_COL_0,  GUI_MENU_ROW_2 + 2, "test");
	Display_DrawText(&gui_ptr->display, GUI_MENU_COL_0,  GUI_MENU_ROW_3 + 2, "fight");

	Display_DrawText(&gui_ptr->display, GUI_MENU_COL_1,  GUI_MENU_ROW_0 + 2, "    ");
	Display_DrawText(&gui_ptr->display, GUI_MENU_COL_1,  GUI_MENU_ROW_1 + 2, "    ");
	Display_DrawText(&gui_ptr->display, GUI_MENU_COL_1,  GUI_MENU_ROW_2 + 2, "info");
	Display_DrawText(&gui_ptr->display, GUI_MENU_COL_1,  GUI_MENU_ROW_3 + 2, "credits");

	__Display_DrawFooter("up", "down", "sel");

	Display_InvertColors(&gui_ptr->display, (gui_ptr->menu_selected<4) ? GUI_MENU_COL_0 : GUI_MENU_COL_1, (gui_ptr->menu_selected%4)*13, 64, 13);

	if(gui_ptr->buttons[BUTTON_L].pressed && gui_ptr->buttons[BUTTON_L].changed)
		gui_ptr->menu_selected--;
	if(gui_ptr->buttons[BUTTON_C].pressed && gui_ptr->buttons[BUTTON_C].changed)
		gui_ptr->menu_selected++;

	gui_ptr->menu_selected %=8;

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
	__Display_DrawFooter("opt", "down", "save");

	const char *mode[] = {"module", "button", "RC RC5", "RC BT"};
	const char *dyhlo[] = {"black", "white", "auto"};
	const char *strategy[] = {"agressive", "defense", "passive"};

	Display_DrawText(&gui_ptr->display, 0,  DISPLAY_LINE_1, "mode : %s", mode[gui_ptr->settings.mode]);
	Display_DrawText(&gui_ptr->display, 0,  DISPLAY_LINE_2, "dyhlo: %s", dyhlo[gui_ptr->settings.dyhlo]);
	Display_DrawText(&gui_ptr->display, 0,  DISPLAY_LINE_3, "strat: %s", strategy[gui_ptr->settings.strategy]);

	Display_InvertColors(&gui_ptr->display, 0, DISPLAY_LINE_1 + (DISPLAY_LINE_2 - DISPLAY_LINE_1)*gui_ptr->menu_selected - 1, 128, DISPLAY_LINE_2 - DISPLAY_LINE_1 + 1);

	if(gui_ptr->buttons[BUTTON_C].pressed && gui_ptr->buttons[BUTTON_C].changed)
		gui_ptr->menu_selected++;

	if(gui_ptr->buttons[BUTTON_L].pressed && gui_ptr->buttons[BUTTON_L].changed && gui_ptr->menu_selected==0) {
		gui_ptr->settings.mode++;
		gui_ptr->settings.mode %=SETTINGS_MODE_NUM;
	} else if(gui_ptr->buttons[BUTTON_L].pressed && gui_ptr->buttons[BUTTON_L].changed && gui_ptr->menu_selected==1) {
		gui_ptr->settings.dyhlo++;
		gui_ptr->settings.dyhlo %=SETTINGS_DYHLO_NUM;
	} else if(gui_ptr->buttons[BUTTON_L].pressed && gui_ptr->buttons[BUTTON_L].changed && gui_ptr->menu_selected==2) {
		gui_ptr->settings.strategy++;
		gui_ptr->settings.strategy %=SETTINGS_STRATEGY_NUM;
	}

	gui_ptr->menu_selected %=3;

	Display_Update(&gui_ptr->display);
}

void SNEAK100_Display_Render_Info(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	Display_Clear(&gui_ptr->display);

	__Display_DrawHeader("Info");
	__Display_DrawFooter("", "", "esc");

	Display_DrawText(&gui_ptr->display, 0,  DISPLAY_LINE_1, "build: %s", __DATE__);
	Display_DrawText(&gui_ptr->display, 0,  DISPLAY_LINE_2, "pass: %s", "");

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

void __Display_ReadSettings(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	gui_ptr->settings = SNEAK100_Memory_ReadSettings();

	// if settings in eeprom are invalid set default parameters
	if(gui_ptr->settings.mode>=SETTINGS_MODE_NUM)
		gui_ptr->settings.mode = SETTINGS_MODE_MODULE;
	if(gui_ptr->settings.dyhlo>=SETTINGS_DYHLO_NUM)
		gui_ptr->settings.dyhlo = SETTINGS_DYHLO_AUTO;
	if(gui_ptr->settings.strategy>=SETTINGS_STRATEGY_NUM)
		gui_ptr->settings.strategy = SETTINGS_STRATEGY_AGRESSIVE;
}

void __Display_WriteSettings(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	SNEAK100_Memory_WriteSettings(gui_ptr->settings);
}
