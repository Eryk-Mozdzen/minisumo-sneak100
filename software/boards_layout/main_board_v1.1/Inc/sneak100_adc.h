/*
 * sneak100_adc.h
 *
 *  Created on: Sep 10, 2021
 *      Author: ermoz
 */

#ifndef SNEAK100_HARDWARE_INC_SNEAK100_ADC_H_
#define SNEAK100_HARDWARE_INC_SNEAK100_ADC_H_

#include "stm32f4xx_hal.h"
#include "adc.h"

#include "line.h"

#define LINE_THRESHOLD				1500

#define SUPPLY_VOLTAGE_DIVIDER_R1	18000.f
#define SUPPLY_VOLTAGE_DIVIDER_R2	10000.f

typedef enum {
	LINE_LL,
	LINE_LM,
	LINE_RM,
	LINE_RR
} LineEnumtypeDef;

extern LineSensor_StructTypeDef lines[4];

void SNEAK100_ADC_Init();
float SNEAK100_ADC_GetSupplyVoltage();
float SNEAK100_ADC_GetTemperature();

void SENAK100_Line_SetPolarity(Line_Polarity_EnumTypeDef);
uint8_t SNEAK100_Line_GetState_ALL();

#endif /* SNEAK100_HARDWARE_INC_SNEAK100_ADC_H_ */
