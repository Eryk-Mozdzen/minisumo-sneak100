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
static void SNEAK100_Display_Render_Overview(void *);
static void SNEAK100_Display_Render_Settings(void *);

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

	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_DESKTOP,		NULL, &SNEAK100_Display_Render_Desktop,		NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_OVERVIEW,	NULL, &SNEAK100_Display_Render_Overview,	NULL);
	FiniteStateMachine_DefineState(&gui.fsm, GUI_STATE_SETTINGS,	NULL, &SNEAK100_Display_Render_Settings,	NULL);

	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_DESKTOP, GUI_STATE_OVERVIEW, 0, NULL, &SNEAK100_Button_L_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_DESKTOP, GUI_STATE_SETTINGS, 0, NULL, &SNEAK100_Button_C_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_OVERVIEW, GUI_STATE_DESKTOP, 0, NULL, &SNEAK100_Button_R_ClickEvent);
	FiniteStateMachine_DefineTransition(&gui.fsm, GUI_STATE_SETTINGS, GUI_STATE_DESKTOP, 0, NULL, &SNEAK100_Button_R_ClickEvent);

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

	char top_bar[32] = {0};
	char bot_bar[32] = {0};

	sprintf(top_bar, "%1.2fV         %2.f*C", gui.battery_voltage, gui.temperature);
	sprintf(bot_bar, "view   sett");

	Display_WriteString(&oled, 0, 0, Font_7x10, top_bar);
	Display_DrawLine(&oled, 0, 10, 127, 10);

	Display_WriteString(&oled, 0, 53, Font_7x10, bot_bar);
	Display_DrawLine(&oled, 0, 53, 127, 53);

	Display_Update(&oled);
}

void SNEAK100_Display_Render_Overview(void *data) {
	ssd1306_Fill(0);

	Display_DrawBitmap(&oled, 0, 0, bitmap_sneak100_live_values_128_64, 128, 64);

	char buffer[10] = {0};

	sprintf(buffer, "%u", gui.line[0]);
	Display_WriteString(&oled, 2, 1, Font_7x10, buffer);
	sprintf(buffer, "%u", gui.line[1]);
	Display_WriteString(&oled, 34, 1, Font_7x10, buffer);
	sprintf(buffer, "%u", gui.line[2]);
	Display_WriteString(&oled, 66, 1, Font_7x10, buffer);
	sprintf(buffer, "%u", gui.line[3]);
	Display_WriteString(&oled, 98, 1, Font_7x10, buffer);

	sprintf(buffer, "%+.2f", gui.position[0]);
	Display_WriteString(&oled, 1, 18, Font_7x10, buffer);
	sprintf(buffer, "%+.2f", gui.velocity[0]);
	Display_WriteString(&oled, 1, 29, Font_7x10, buffer);

	sprintf(buffer, "%+.2f", gui.position[1]);
	Display_WriteString(&oled, 1, 42, Font_7x10, buffer);
	sprintf(buffer, "%+.2f", gui.velocity[1]);
	Display_WriteString(&oled, 1, 53, Font_7x10, buffer);

	sprintf(buffer, "%+.2f", gui.position[2]);
	Display_WriteString(&oled, 92, 18, Font_7x10, buffer);
	sprintf(buffer, "%+.2f", gui.velocity[2]);
	Display_WriteString(&oled, 92, 29, Font_7x10, buffer);

	sprintf(buffer, "%+.2f", gui.position[3]);
	Display_WriteString(&oled, 92, 42, Font_7x10, buffer);
	sprintf(buffer, "%+.2f", gui.velocity[3]);
	Display_WriteString(&oled, 92, 53, Font_7x10, buffer);

	Display_Update(&oled);
}

void SNEAK100_Display_Render_Settings(void *data) {
	ssd1306_Fill(0);

	char top_bar[32] = {0};
	char bot_bar[32] = {0};

	sprintf(top_bar, "Settings:");
	sprintf(bot_bar, "              ret");

	Display_WriteString(&oled, 0, 0, Font_7x10, top_bar);
	Display_DrawLine(&oled, 0, 10, 127, 10);

	Display_WriteString(&oled, 0, 53, Font_7x10, bot_bar);
	Display_DrawLine(&oled, 0, 53, 127, 53);

	Display_WriteString(&oled, 0, 40, Font_7x10, "work in progress");

	Display_Update(&oled);
}
