/*
 * display.c
 *
 *  Created on: Aug 21, 2021
 *      Author: ermoz
 */

#include "display.h"

void Display_Init(Display_t *display, I2C_HandleTypeDef *hi2c) {
	display->hi2c = hi2c;
	display->status = HAL_OK;
	display->color = White;

	ssd1306_Init();
}

void Display_Update(Display_t *display) {
	if(Display_GetStatus(display)!=HAL_OK)
		return;

	ssd1306_UpdateScreen();
}

void Display_SetColor(Display_t *display, SSD1306_COLOR color) {
	display->color = color;
}

HAL_StatusTypeDef Display_GetStatus(Display_t *display) {
	return display->status;
}

void Display_Clear(Display_t *display) {
	ssd1306_Fill(Black);
}

void Display_DrawBitmap(Display_t *display, uint16_t x, uint16_t y, const uint8_t *bitmap, uint16_t w, uint16_t h) {
	ssd1306_DrawBitmap(x, y, bitmap, w, h, display->color);
}

void Display_DrawLine(Display_t *display, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
	ssd1306_Line(x0, y0, x1, y1, display->color);
}

void Display_DrawText(Display_t *display, uint8_t x, uint8_t y, const char *format, ...) {
	char buffer[32] = {0};

	va_list args;
	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	ssd1306_SetCursor(x, y);
	ssd1306_WriteString(buffer, Font_7x10, display->color);
}

void Display_DrawRect(Display_t *display, uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
	ssd1306_DrawRectangle(x, y, x + w, y + h, display->color);
}





