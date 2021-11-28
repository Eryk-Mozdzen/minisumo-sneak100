/*
 * display.c
 *
 *  Created on: Aug 21, 2021
 *      Author: ermoz
 */

#include "display.h"

void Display_Init(Display_StructTypeDef *display, I2C_HandleTypeDef *hi2c) {
	display->hi2c = hi2c;

	if(HAL_I2C_IsDeviceReady(display->hi2c, SSD1306_I2C_ADDR, 1, 100)!=HAL_OK)
		Display_ErrorHandler();

	ssd1306_Init(display->hi2c);
}

/*__attribute__((weak)) void Display_ErrorHandler() {
	printf("xd");
}*/

void Display_Update(Display_StructTypeDef *display) {
	if(HAL_I2C_IsDeviceReady(display->hi2c, SSD1306_I2C_ADDR, 1, 10)!=HAL_OK)
		Display_ErrorHandler();

	ssd1306_UpdateScreen(display->hi2c);
}

void Display_DrawBitmap(Display_StructTypeDef *display, uint16_t x, uint16_t y, const uint8_t *bitmap, uint16_t w, uint16_t h) {
	ssd1306_DrawBitmap(x, y, bitmap, w, h, White);
}

void Display_DrawLine(Display_StructTypeDef *display, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
	int16_t dx, dy, sx, sy, err, e2, i, tmp;

	/* Check for overflow */
	if (x0 >= SSD1306_WIDTH) {
		x0 = SSD1306_WIDTH - 1;
	}
	if (x1 >= SSD1306_WIDTH) {
		x1 = SSD1306_WIDTH - 1;
	}
	if (y0 >= SSD1306_HEIGHT) {
		y0 = SSD1306_HEIGHT - 1;
	}
	if (y1 >= SSD1306_HEIGHT) {
		y1 = SSD1306_HEIGHT - 1;
	}

	dx = (x0 < x1) ? (x1 - x0) : (x0 - x1);
	dy = (y0 < y1) ? (y1 - y0) : (y0 - y1);
	sx = (x0 < x1) ? 1 : -1;
	sy = (y0 < y1) ? 1 : -1;
	err = ((dx > dy) ? dx : -dy) / 2;

	if (dx == 0) {
		if (y1 < y0) {
			tmp = y1;
			y1 = y0;
			y0 = tmp;
		}

		if (x1 < x0) {
			tmp = x1;
			x1 = x0;
			x0 = tmp;
		}

		/* Vertical line */
		for (i = y0; i <= y1; i++) {
			ssd1306_DrawPixel(x0, i, White);
		}

		/* Return from function */
		return;
	}

	if (dy == 0) {
		if (y1 < y0) {
			tmp = y1;
			y1 = y0;
			y0 = tmp;
		}

		if (x1 < x0) {
			tmp = x1;
			x1 = x0;
			x0 = tmp;
		}

		/* Horizontal line */
		for (i = x0; i <= x1; i++) {
			ssd1306_DrawPixel(i, y0, White);
		}

		/* Return from function */
		return;
	}

	while(1) {
		ssd1306_DrawPixel(x0, y0, White);
		if (x0 == x1 && y0 == y1) {
			break;
		}
		e2 = err;
		if (e2 > -dx) {
			err -= dy;
			x0 += sx;
		}
		if (e2 < dy) {
			err += dx;
			y0 += sy;
		}
	}

}

void Display_WriteString(Display_StructTypeDef *display, uint16_t x, uint16_t y, FontDef font, char *str) {
	ssd1306_SetCursor(x, y);
	ssd1306_WriteString(str, font, White);
}
