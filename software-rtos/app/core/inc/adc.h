#ifndef ADC_H
#define ADC_H

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#define ADC_REFERENCE			3.3f
#define ADC_RESOLUTION			4095

typedef enum {
	ADC_CHANNEL_LINE_RR = 10,
	ADC_CHANNEL_LINE_RM = 11,
	ADC_CHANNEL_LINE_LM = 12,
	ADC_CHANNEL_LINE_LL = 13,
	ADC_CHANNEL_BATT_V = 14,
	ADC_CHANNEL_TEMP_UC = 16
} adc_channel_t;

void adc_init();
uint16_t adc_get_raw(const adc_channel_t);
float adc_get_voltage(const adc_channel_t);

void ADC_IRQHandler();

#endif