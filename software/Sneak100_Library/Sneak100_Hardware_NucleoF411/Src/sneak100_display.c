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

void Display_ErrorHandler() {
	Error_Handler();
}

void SNEAK100_Display_Init() {
	Display_Init(&oled, &hi2c1);
}

void SNEAK100_Display_Render() {
	Display_DrawBitmap(&oled, 0, 0, bitmap_sneak100_128_64, 128, 64);

	char top_bar[32] = {0};
	char bot_bar[32] = {0};

	sprintf(top_bar, "%1.2fV         %2.f*C", gui.battery_voltage, gui.temperature);
	sprintf(bot_bar, "menu");

	Display_WriteString(&oled, 0, 0, Font_7x10, top_bar);
	Display_DrawLine(&oled, 0, 10, 127, 10);



	Display_WriteString(&oled, 0, 53, Font_7x10, bot_bar);
	Display_DrawLine(&oled, 0, 53, 127, 53);

	Display_Update(&oled);
}
