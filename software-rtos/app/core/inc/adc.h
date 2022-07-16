#ifndef ADC_H
#define ADC_H

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#define ADC_REFERENCE			3.3f
#define ADC_RESOLUTION			4095
#define ADC_CONVERSIONS_NUM		6

typedef enum {
	ADC_CHANNEL_LINE_RR = 10,
	ADC_CHANNEL_LINE_RM = 11,
	ADC_CHANNEL_LINE_LM = 12,
	ADC_CHANNEL_LINE_LL = 13,
	ADC_CHANNEL_BATT_V = 14,
	ADC_CHANNEL_TEMP_UC = 16
} adc_channel_t;

void adc_init();

float adc_get_voltage(const adc_channel_t);

void ADC_IRQHandler();

#endif