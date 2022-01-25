/*
 * sneak100_adc.c
 *
 *  Created on: Sep 10, 2021
 *      Author: ermoz
 */

#include "sneak100_adc.h"

/* ADC reading buffer for DMA
 * 0 -> right-far line sensor
 * 1 -> right-mid line sensor
 * 2 -> left-mid line sensor
 * 3 -> left-far line sensor
 * 4 -> battery sense
 * 5 -> internal temperature sensor
 * */
static uint16_t adc_dma_buffer[6] = {0};

LineSensor_StructTypeDef lineLL;
LineSensor_StructTypeDef lineLM;
LineSensor_StructTypeDef lineRM;
LineSensor_StructTypeDef lineRR;

void SNEAK100_ADC_Init() {

	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_dma_buffer, 6);

	Line_Init(&lineLL, &adc_dma_buffer[3], LINE_THRESHOLD);
	Line_Init(&lineLM, &adc_dma_buffer[2], LINE_THRESHOLD);
	Line_Init(&lineRM, &adc_dma_buffer[1], LINE_THRESHOLD);
	Line_Init(&lineRR, &adc_dma_buffer[0], LINE_THRESHOLD);
}

static float __SNEAK100_ADC_ConvertToVoltage(uint16_t read_raw) {
	return ((float)read_raw/4095.f)*3.3f;
}

float SNEAK100_ADC_GetSupplyVoltage() {
	const uint16_t raw = adc_dma_buffer[4];
	const float scale = (SUPPLY_VOLTAGE_DIVIDER_R1 + SUPPLY_VOLTAGE_DIVIDER_R2)/SUPPLY_VOLTAGE_DIVIDER_R2;
	return __SNEAK100_ADC_ConvertToVoltage(raw)*scale;
}

float SNEAK100_ADC_GetTemperature() {
	return __LL_ADC_CALC_TEMPERATURE(3270, adc_dma_buffer[5], LL_ADC_RESOLUTION_12B);
}

void SENAK100_Line_SetPolarity(Line_Polarity_EnumTypeDef polarity) {
	lineLL.polarity = polarity;
	lineLM.polarity = polarity;
	lineRM.polarity = polarity;
	lineRR.polarity = polarity;

	if(polarity==DYHLO_AUTO) {
		SENAK100_Line_SetPolarity(DYHLO_WHITE_WITH_BLACK_CIRCUMFERENCE);

		uint8_t state = SNEAK100_Line_GetState_ALL();

		if(state==0x00)
			SENAK100_Line_SetPolarity(DYHLO_BLACK_WITH_WHITE_CIRCUMFERENCE);
		else if(state==0x0F) {
			SENAK100_Line_SetPolarity(DYHLO_WHITE_WITH_BLACK_CIRCUMFERENCE);
		} else {
			// error
		}
	}
}

uint8_t SNEAK100_Line_GetState_ALL() {
	return (Line_GetState(&lineLL) << 3) |
			(Line_GetState(&lineLM) << 2) |
			(Line_GetState(&lineRM) << 1) |
			(Line_GetState(&lineRR) << 0);
}
