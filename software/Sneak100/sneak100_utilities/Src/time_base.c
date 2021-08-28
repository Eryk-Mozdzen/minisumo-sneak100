/*
 * time_base.c
 *
 *  Created on: Aug 15, 2021
 *      Author: ermoz
 */

#include "time_base.h"

void TimeBase_Init(TimeBase_StructTypeDef *tbase) {
	tbase->time_start = HAL_GetTick();
}

void TimeBase_Start(TimeBase_StructTypeDef *tbase) {
	tbase->time_start = HAL_GetTick();
}

uint32_t TimeBase_Restart(TimeBase_StructTypeDef *tbase) {
	uint32_t time_elapsed = HAL_GetTick() - tbase->time_start;

	tbase->time_start = HAL_GetTick();

	return time_elapsed;
}

uint32_t TimeBase_GetTimeElapsed(TimeBase_StructTypeDef *tbase) {
	return HAL_GetTick() - tbase->time_start;
}

float TimeBase_GetScale(TimeBase_StructTypeDef *tbase) {
	HAL_TickFreqTypeDef freq = HAL_GetTickFreq();

	switch(freq) {
		case HAL_TICK_FREQ_10HZ: 	return 0.1f;
		case HAL_TICK_FREQ_100HZ: 	return 0.01f;
		case HAL_TICK_FREQ_1KHZ: 	return 0.001f;
	}

	return 1;
}
