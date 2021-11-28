/*
 * sneak100_display.c
 *
 *  Created on: Aug 21, 2021
 *      Author: ermoz
 */

#include "sneak100_display.h"

Display_StructTypeDef oled;
Sneak100_GUI_StructTypeDef gui;

void SNEAK100_Display_Init() {

	Display_Init(&oled, &hi2c3);

}

void SNEAK100_Display_Render() {

	char battery_voltage_buffer[16] = {0};

	sprintf(battery_voltage_buffer, "%1.2fV", gui.battery_voltage);

	Display_SetCursor(&oled, 0, 0);
	Display_WriteString(&oled, Font_7x10, battery_voltage_buffer);
	Display_DrawLine(&oled, 0, 10, 127, 10);

	Display_Update(&oled);
}
