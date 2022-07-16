#ifndef SENSORS_H
#define SENSORS_H

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "adc.h"

#include "uart2.h"

#define ADC_READ_FREQ		50
#define LINE_THRESHOLD		1.3f

void proximity_init();
void proximity_get_state(uint8_t *);

void line_init();
void line_get_state(uint8_t *);

#endif