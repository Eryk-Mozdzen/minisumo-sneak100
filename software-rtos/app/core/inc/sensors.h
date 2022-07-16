#ifndef SENSORS_H
#define SENSORS_H

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "adc.h"

#include "uart2.h"

#define LINE_READ_FREQ			50
#define LINE_THRESHOLD			1500
#define BATT_SCALE				0.357f
#define INTERNAL_V_25			0.76f
#define INTERNAL_AVG_SLOPE		0.0025f

void proximity_init();
void proximity_get_state(uint8_t *);

void line_init();
void line_get_state(uint8_t *);
void line_get_raw(uint16_t *);

float get_voltage();
float get_temperature();

#endif