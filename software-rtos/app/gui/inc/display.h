#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdlib.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "i2c1.h"

#define DISPLAY_ADDRESS			0x3C
#define DISPLAY_WIDTH			128		// px
#define DISPLAY_HEIGHT			64		// px
#define DISPLAY_UPDATE_FREQ		20		// Hz

typedef enum {
	DISPLAY_COLOR_BLACK,
	DISPLAY_COLOR_WHITE
} display_color_t;

void display_init();
void display_fill(const display_color_t);
void display_set_pixel(const int16_t, const int16_t, const display_color_t);
display_color_t display_get_pixel(const int16_t, const int16_t);
void display_line(int16_t, int16_t, const int16_t, const int16_t, const display_color_t);
void display_rect(const int16_t, const int16_t, const int16_t, const int16_t, const display_color_t);
void display_inverse(const int16_t, const int16_t, const int16_t, const int16_t);
void display_printf(const int16_t, const int16_t, const display_color_t, const char *, ...);
void display_bitmap(const int16_t, const int16_t, const uint8_t *);

#endif