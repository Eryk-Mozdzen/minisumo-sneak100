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

extern LineSensor_StructTypeDef lineLL;
extern LineSensor_StructTypeDef lineLM;
extern LineSensor_StructTypeDef lineRM;
extern LineSensor_StructTypeDef lineRR;

void SNEAK100_ADC_Init();
float SNEAK100_ADC_ConvertToVoltage(uint16_t);
float SNEAK100_ADC_GetSupplyVoltage();
float SNEAK100_ADC_GetTemperature();

void SENAK100_LineSensors_SetPolarity(LineSensor_PolarityTypeDef);
uint8_t SNEAK100_LineSensors_GetState_ALL();

#endif /* SNEAK100_HARDWARE_INC_SNEAK100_ADC_H_ */
