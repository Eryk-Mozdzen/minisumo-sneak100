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

	LineSensor_Init(&lineLL, &adc_dma_buffer[3], LINE_THRESHOLD);
	LineSensor_Init(&lineLM, &adc_dma_buffer[2], LINE_THRESHOLD);
	LineSensor_Init(&lineRM, &adc_dma_buffer[1], LINE_THRESHOLD);
	LineSensor_Init(&lineRR, &adc_dma_buffer[0], LINE_THRESHOLD);
}

float SNEAK100_ADC_ConvertToVoltage(uint16_t read_raw) {
	return ((float)read_raw/4095.f)*3.3f;
}

float SNEAK100_ADC_GetSupplyVoltage() {
	return SNEAK100_ADC_ConvertToVoltage(adc_dma_buffer[4])*(SUPPLY_VOLTAGE_DIVIDER_R1 + SUPPLY_VOLTAGE_DIVIDER_R2)/SUPPLY_VOLTAGE_DIVIDER_R2;
}

float SNEAK100_ADC_GetTemperature() {
	return __LL_ADC_CALC_TEMPERATURE(3300, adc_dma_buffer[5], LL_ADC_RESOLUTION_12B);
}

void SENAK100_LineSensors_SetPolarity(LineSensor_PolarityTypeDef polarity) {
	lineLL.polarity = polarity;
	lineLM.polarity = polarity;
	lineRM.polarity = polarity;
	lineRR.polarity = polarity;

	if(polarity==DYHLO_AUTO) {
		SENAK100_LineSensors_SetPolarity(DYHLO_WHITE_WITH_BLACK_CIRCUMFERENCE);

		uint8_t state = SNEAK100_LineSensors_GetState_ALL();

		if(state==0x00)
			SENAK100_LineSensors_SetPolarity(DYHLO_BLACK_WITH_WHITE_CIRCUMFERENCE);
		else {
			// error
		}
	}
}

uint8_t SNEAK100_LineSensors_GetState_ALL() {
	return 0x00 |
			(LineSensor_GetState(&lineLL) << 3) |
			(LineSensor_GetState(&lineLM) << 2) |
			(LineSensor_GetState(&lineRM) << 1) |
			(LineSensor_GetState(&lineRR) << 0);
}
