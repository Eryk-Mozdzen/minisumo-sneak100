/*
 * sneak100_display.c
 *
 *  Created on: Aug 21, 2021
 *      Author: ermoz
 */

#include "sneak100_display.h"
#include "sprites.h"

Display_StructTypeDef oled;
Sneak100_GUI_StructTypeDef gui;

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
static void __Display_DrawText(uint8_t, uint8_t, const char *, ...);

HAL_StatusTypeDef ssd1306_Write(uint16_t address, void *data, uint16_t len) {
	return HAL_I2C_Mem_Write(&hi2c1, SSD1306_I2C_ADDR, address, 1, data, len, 10);
}

void Display_ErrorHandler(const char *file, uint16_t line) {
	printf("Error in %s: %u\n", file, line);
	Error_Handler();
}

void SNEAK100_Display_Init() {
	gui.buttons[BUTTON_L] = (const GUI_ButtonState_StructTypeDef){0, 0};
	gui.buttons[BUTTON_C] = (const GUI_ButtonState_StructTypeDef){0, 0};
	gui.buttons[BUTTON_R] = (const GUI_ButtonState_StructTypeDef){0, 0};

	Display_Init(&oled, &hi2c1);

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
	gui.buttons[BUTTON_L].chenged = gui.buttons[BUTTON_L].pressed ^ !HAL_GPIO_ReadPin(USER_BUTTON_L_GPIO_Port, USER_BUTTON_L_Pin);
	gui.buttons[BUTTON_C].chenged = gui.buttons[BUTTON_C].pressed ^ !HAL_GPIO_ReadPin(USER_BUTTON_C_GPIO_Port, USER_BUTTON_C_Pin);
	gui.buttons[BUTTON_R].chenged = gui.buttons[BUTTON_R].pressed ^ !HAL_GPIO_ReadPin(USER_BUTTON_R_GPIO_Port, USER_BUTTON_R_Pin);

	gui.buttons[BUTTON_L].pressed = !HAL_GPIO_ReadPin(USER_BUTTON_L_GPIO_Port, USER_BUTTON_L_Pin);
	gui.buttons[BUTTON_C].pressed = !HAL_GPIO_ReadPin(USER_BUTTON_C_GPIO_Port, USER_BUTTON_C_Pin);
	gui.buttons[BUTTON_R].pressed = !HAL_GPIO_ReadPin(USER_BUTTON_R_GPIO_Port, USER_BUTTON_R_Pin);
}

static void __Display_DrawHeader(const char *title) {
	char top_bar[32] = {0};

	sprintf(top_bar, "%s       ", title);

	Display_WriteString(&oled, 0, 0, Font_7x10, top_bar);
	Display_DrawLine(&oled, 0, 10, 127, 10);
}

static void __Display_DrawText(uint8_t x, uint8_t y, const char *format, ...) {
	char buffer[32] = {0};

	va_list args;
	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	Display_WriteString(&oled, x, y, Font_7x10, buffer);
}

static void __Display_DrawFooter(const char *action_l, const char *action_c, const char *action_r) {
	char bot_bar[32] = {0};

	sprintf(bot_bar, "%.4s              ", action_l);
	sprintf(bot_bar + 7, "%.4s       ", action_c);
	sprintf(bot_bar + 14, "%.4s", action_r);

	Display_WriteString(&oled, 0, 53, Font_7x10, bot_bar);
	Display_DrawLine(&oled, 0, 53, 127, 53);
}

uint8_t SNEAK100_Button_L_ClickEvent(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	return (gui_ptr->buttons[BUTTON_L].pressed && gui_ptr->buttons[BUTTON_L].chenged);
}

uint8_t SNEAK100_Button_C_ClickEvent(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	return (gui_ptr->buttons[BUTTON_C].pressed && gui_ptr->buttons[BUTTON_C].chenged);
}

uint8_t SNEAK100_Button_R_ClickEvent(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	return (gui_ptr->buttons[BUTTON_R].pressed && gui_ptr->buttons[BUTTON_R].chenged);
}

void SNEAK100_Display_Render_Desktop(void *data) {
	ssd1306_Fill(0);

	Display_DrawBitmap(&oled, 0, 0, bitmap_sneak100_128_64, 128, 64);

	/*char top_bar[32] = {0};
	sprintf(top_bar, "%1.2fV         %2.f*C", gui.battery_voltage, gui.temperature);
	Display_WriteString(&oled, 0, 0, Font_7x10, top_bar);
	Display_DrawLine(&oled, 0, 10, 127, 10);*/

	__Display_DrawHeader("Menu");
	__Display_DrawFooter("view", "sett", "cred");

	Display_Update(&oled);
}

void SNEAK100_Display_Render_ViewMotors(void *data) {
	ssd1306_Fill(0);

	__Display_DrawHeader("Motors");
	__Display_DrawFooter("next", "prev", "esc");

	__Display_DrawText(0,  13, "FL:");
	__Display_DrawText(0,  23, "BL:");
	__Display_DrawText(0,  33, "FR:");
	__Display_DrawText(0,  43, "BR:");

	Display_Update(&oled);
}

void SNEAK100_Display_Render_ViewLine(void *data) {
	ssd1306_Fill(0);

	__Display_DrawHeader("Line");
	__Display_DrawFooter("next", "prev", "esc");

	__Display_DrawText(0,  13, "LL:");
	__Display_DrawText(0,  23, "LM:");
	__Display_DrawText(0,  33, "RM:");
	__Display_DrawText(0,  43, "RR:");

	Display_Update(&oled);
}

void SNEAK100_Display_Render_ViewProximity(void *data) {
	ssd1306_Fill(0);

	__Display_DrawHeader("Proximity");
	__Display_DrawFooter("next", "prev", "esc");

	__Display_DrawText(0,  13, "LL:");
	__Display_DrawText(0,  23, "FL:");
	__Display_DrawText(0,  33, "FR:");
	__Display_DrawText(0,  43, "RR:");

	Display_Update(&oled);
}

void SNEAK100_Display_Render_ViewOthers(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	ssd1306_Fill(0);

	__Display_DrawHeader("Others");
	__Display_DrawFooter("next", "prev", "esc");

	__Display_DrawText(0,  13, "Temp: %.0f*C", gui_ptr->temperature);
	__Display_DrawText(0,  23, "Batt: %.2fV", gui_ptr->battery_voltage);
	__Display_DrawText(0,  33, "RC5:  ");
	__Display_DrawText(0,  43, "HC05: ");

	Display_Update(&oled);
}

void SNEAK100_Display_Render_Settings(void *data) {
	ssd1306_Fill(0);

	__Display_DrawHeader("Settings");
	__Display_DrawFooter("", "", "esc");

	__Display_DrawText(0,  13, "mode: ");
	__Display_DrawText(0,  23, "strategy: ");
	__Display_DrawText(0,  33, "password: ");

	Display_Update(&oled);
}

void SNEAK100_Display_Render_Credits(void *data) {
	ssd1306_Fill(0);

	Display_DrawBitmap(&oled, 0, 0, bitmap_sneak100_128_64, 128, 64);

	__Display_DrawText(0, 0, "Minisumo Sneak100");
	__Display_DrawText(0, 53, "by E.Mozdzen 2022");

	Display_Update(&oled);
}
