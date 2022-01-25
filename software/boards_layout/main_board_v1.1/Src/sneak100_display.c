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

HAL_StatusTypeDef ssd1306_Write(uint16_t address, void *data, uint16_t len) {
	return HAL_I2C_Mem_Write(&hi2c1, SSD1306_I2C_ADDR, address, 1, data, len, 10);
}

void Display_ErrorHandler(const char *file, uint16_t line) {
	printf("Error in %s: %u\n", file, line);
	Error_Handler();
}

void SNEAK100_Display_Init() {
	Display_Init(&oled, &hi2c1);
}

void live_values() {
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

	//live_values();

	Display_Update(&oled);
}
